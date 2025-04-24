#include "RussianPyramidScene.h"

#include "ecs.h"
#include "Entity.h"
#include "PhysicsUtils.h"
#include "GraphicsUtils.h"
#include "RNG_Manager.h"
#include "RandomItem.h"

#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "PolygonRBComponent.h"
#include "TweenComponent.h"
#include "CircleRBComponent.h"
#include "FollowComponent.h"
#include "PyramidComponent.h"
#include "StickInputComponent.h"
#include "ShadowComponent.h"
#include "ColorBallScorerComponent.h"
#include "WhiteBallScorerComponent.h"
#include "Button.h"
#include "InventoryManager.h"


RussianPyramidScene::RussianPyramidScene(Game* g, State* state, bool isBoss)
    : CaromScene(state, g)
    , _pyramidFilenameSVG("grp_pyramids")
    , _areaConstrainName("area")
    , _nAvailablePyramids(5)
    , _allBalls()
{
    _boss = RUSSIAN_PYRAMID;
}

RussianPyramidScene::~RussianPyramidScene()
{
}

void RussianPyramidScene::initGimmick(){
    //comportamiento (anyadir entidades de arena en la mesa)
    std::cout<< "RussianPyramidScene Gimmick Instantiated" << std::endl;

    int nPyramids = 1;
    generatePyramids(nPyramids);
}

void RussianPyramidScene::initBoss()
{
    _originalWhiteBall = getEntitiesOfGroup(grp::WHITEBALL)[0];

    getComponent<RenderTextureComponent>(getEntitiesOfGroup(grp::TABLE_BACKGROUND)[0])->changeColorTint(237, 191, 47);

    if(isBossMatch()) {
        _boss = Boss::RUSSIAN_PYRAMID;
        createBoss();
    }
}

void RussianPyramidScene::createBoss(){
    tryInitializeBallArray();

    //--Crear el indicador
    _indicator = new Entity(*this, grp::BOSS_MODIFIERS);
    addComponent<TransformComponent>(_indicator, b2Vec2_zero);
    addComponent<FollowComponent>(_indicator, _currentWhiteBall, true, false, true, Vector2D(0, 0));

    float wbScale = getEntitiesOfGroup(grp::WHITEBALL)[0]->getTransform()->getScale().x / 2;
    addComponent<RenderTextureComponent>(_indicator, &sdlutils().images().at("russian_indicator"), renderLayer::RUSSIAN_PYRAMID_INDICATOR, wbScale);

    //--Crear el jefe
    entity_t boss = new Entity(*this, grp::BOSS_HAND);
    addComponent<TransformComponent>(boss, startingHandPosition);

    float svgSize = *&sdlutils().svgs().at(_pyramidFilenameSVG).at("russian_boss_hand").width;
    float textureSize = sdlutils().images().at("russian_hand").width();
    float bossScale = (svgSize/textureSize) * 0.8;

    addComponent<RenderTextureComponent>(boss, &sdlutils().images().at("russian_hand"), renderLayer::BOSS_HAND, bossScale);
    addComponent<TweenComponent>(boss);

    // //sombra
    // // Entity* sombraJefe = new Entity(*this, grp::SHADOWS);
    // // addComponent<TransformComponent>(sombraJefe, b2Vec2{0,0});
    // // addComponent<RenderTextureComponent>(sombraJefe, &sdlutils().images().at("cowboy_hand_shadow"), renderLayer::BOSS_SHADOW_HAND, scale);
    // // addComponent<FollowComponent>(sombraJefe, boss, true,true,true, Vector2D{-0.05, -0.05});

    // CaromScene::instantiateBossTableShadow();
}

/// @brief Creates and randomly places as many effect balls as specified
/// @param n Number of balls to place
void 
RussianPyramidScene::createEffectBalls() 
{
    int npos = sdlutils().svgs().at("positions").size();

    std::vector<std::string> validPositions;

    for(int i = 1; i <= npos; ++i) 
    {
        std::string s = "bola";
        if(i > 1)
            s += ("_" + std::to_string(i));
        
        auto& eb = sdlutils().svgs().at("positions").at(s);
        auto ballPos = GraphisUtils::sdlrectToPolygon(
            GraphisUtils::getTopLeftRect({eb.x, eb.y}, {eb.width, eb.height})
        );

        bool overlap = false;
        for (int i = 0; i < _pyramidBasePolys.size() && !overlap; ++i)
            overlap = GraphisUtils::doPolygonsOverlap(ballPos, _pyramidBasePolys[i]);

        if (!overlap)
            validPositions.push_back(s);
    }

    std::vector<RandomItem<std::string>> validPositionsRandom;
    for(int i = 0; i < validPositions.size(); ++i)
        validPositionsRandom.push_back(RandomItem(validPositions[i], 1.0f));

    std::vector<std::string> eb_selected_pos = _rngManager->getRandomItems(validPositionsRandom, InventoryManager::Instance()->MAX_BALLS, false);
    std::vector<b2Vec2> physical_selected_pos;
    for(int i = 0; i < eb_selected_pos.size(); ++i) 
    {        
        auto& eb = sdlutils().svgs().at("positions").at(eb_selected_pos[i]);
        auto eb_pos = PhysicsConverter::pixel2meter(eb.x, eb.y);
        physical_selected_pos.push_back(eb_pos);
    }

    auto balls = InventoryManager::Instance()->getEffectBalls(*this, physical_selected_pos);

    for(entity_t ball : balls){
        if(ball != nullptr) {
            CaromScene::createBallShadow(ball);
        }
    }
}

void RussianPyramidScene::createPyramid(std::vector<b2Vec2> &points, std::vector<b2Vec2> &auxPoints, int polyId)
{
    // Covert all points to meters
    for (auto& point : points) {
        point = PhysicsConverter::pixel2meter(point.x, point.y);
    }

    // Covert all points to meters
    for (auto& auxPoint : auxPoints) {
        auxPoint = PhysicsConverter::pixel2meter(auxPoint.x, auxPoint.y);
    }

    // Triangle sensor entities that compose the piramid (n = 4 triangles)
    int n = auxPoints.size();
    for (int i = 0; i < n; ++i) {
        Entity* e = new Entity(*this, grp::GIMMICK);

        // points[0] = peak point
        Polygon a_triangle = {points[0], points[(i % n) + 1], points[((i + 1) % n) + 1]};
        addComponent<PolygonRBComponent>(e, b2Vec2_zero, b2_staticBody, a_triangle, 0, true);

        // Force direction
        b2Vec2 a_direction = auxPoints[i] - points[0];
        addComponent<PyramidComponent>(e, a_direction);
    }

    // Render entity for the piramid image
    // SCALE
    std::string name = "pyramid";
    std::string index = std::to_string(polyId);
    std::string id = name + index;

    float svgSize = *&sdlutils().svgs().at(_pyramidFilenameSVG).at(id).width;
    float textureSize = sdlutils().images().at(id).width();
    float scale = svgSize/textureSize;

    Entity* img = new Entity(*this, grp::GIMMICK);
    b2Vec2 pos = points[0]; // the peak is the center
    addComponent<TransformComponent>(img, pos);
    addComponent<RenderTextureComponent>(img, &sdlutils().images().at(id), renderLayer::GIMMICK, scale);

    // Render entity for the piramid SHADOW
    std::string nameS = "pyramid_shadow";
    std::string idS = nameS + index;

    float svgSizeS = *&sdlutils().svgs().at(_pyramidFilenameSVG).at(idS).width;
    float textureSizeS = sdlutils().images().at(idS).width();
    float scaleS = svgSizeS/textureSizeS;

    auto shadow = addComponent<ShadowComponent>(img);
    shadow->addShadow(pos, idS, renderLayer::PYRAMID_SHADOW, scaleS, false,false,false);
}

void RussianPyramidScene::pickAndPositionPyramidPolygons(int numPolys, const SDL_Rect& areaConstrain, std::vector<Polygon> &choosenPolygons, std::vector<std::vector<b2Vec2>> &auxPoints, std::vector<int> &polyIds)
{
        // In PIXELS, floats
        std::vector<Polygon> pyramidPolygons = getPyramidsPolygons(_nAvailablePyramids, 0);
        std::vector<b2Vec2>  pyramidPeaks = GraphisUtils::extractPointsFromSVG(_nAvailablePyramids, 0, "peak", "grp_pyramids"); // search for keyword
        std::vector<b2Vec2>  offsets;
        Polygon areaPolygon = GraphisUtils::sdlrectToPolygon(areaConstrain);
        
        // Getting a random polygon from svg
        std::vector<RandomItem<int>> polygons;
        for(int i = 0; i < _nAvailablePyramids; ++i)
            polygons.emplace_back(i, 1.0f);
    
        // numPolys = number of pyramids to generate
        for (int i = 0; i < numPolys; ++i)
        {
            bool found = false;
            int attempts = 100;
    
            // Try a polygon
            int polyId = _rngManager->getRandomItem(polygons, true);
            std::vector<b2Vec2> candidatePoly = pyramidPolygons[polyId];
    
            // Get peak ("center")
            b2Vec2& polyCenter = pyramidPeaks[polyId];
    
            while (!found && attempts > 0)
            {
                assert(attempts > 1);

                // Generate a radom center in PIXELS
                // GraphisUtils::coutRect(areaConstrain);
                b2Vec2 genRandomPosition = {
                    static_cast<float>
                    (_rngManager->randomRange(areaConstrain.x, areaConstrain.x + areaConstrain.w)),
                    static_cast<float>
                    (_rngManager->randomRange(areaConstrain.y, areaConstrain.y + areaConstrain.h))
                };

                // Update vertices positions by offset (distance between gen and original centers)
                // PIXELS
                b2Vec2 offset = genRandomPosition - polyCenter;
                polyCenter = genRandomPosition;
    
                for (auto& vert : candidatePoly)
                    vert += offset;
                
                // Check if all of the pyramid is inside area
                if (GraphisUtils::arePointsInsideArea(candidatePoly, areaPolygon))
                {
                    int j = 0;
                    bool overlap = false;
                    // Check if pyramid overlap with previous ones
                    while (j < choosenPolygons.size() && !overlap) {
                        overlap = GraphisUtils::doPolygonsOverlap(candidatePoly, choosenPolygons[j]);
                        ++j;
                    }
                    found = !overlap;
                }
    
                if (found){
                    _pyramidBasePolys.push_back(candidatePoly);
                    candidatePoly.insert(candidatePoly.begin(), polyCenter); // pushes front the peak
                    choosenPolygons.push_back(candidatePoly);
                    auxPoints.push_back(getAuxPoints(4, polyId, offset)); // TODO: hardcoded n=4
                    polyIds.push_back(polyId);
                    offsets.push_back(offset);
                }
                else { // Revert update vertices positions by offset (distance between gen and original centers)
                    for (auto& vert : candidatePoly){
                        vert -= offset;
                    }
                    polyCenter -= offset;
                    attempts--;                    
                }
            }

        }
}

std::vector<b2Vec2> RussianPyramidScene::getAuxPoints(int n, int polyId, const b2Vec2 &offset)
{
    std::string id = std::to_string(polyId);
    std::string prefix = "aux";
    std::string name = id + prefix;

    std::vector<b2Vec2> auxPoints = GraphisUtils::extractPointsFromSVG(n, 0, name, "grp_pyramids");
    
    for (auto& p : auxPoints){
        p += offset; // offset of a single pyramid
    }

    return auxPoints;
}

std::vector<Polygon> RussianPyramidScene::getPyramidsPolygons(int n, int startPolyId)
{
    std::vector<Polygon> polygons;
    polygons.reserve(n);

    for (int idx = startPolyId; idx < n + startPolyId; ++idx){

        std::string id = std::to_string(idx);
        std::string prefix = "b";
        std::string name = id + prefix;
    
        polygons.push_back(GraphisUtils::extractPointsFromSVG(4, 0, name, "grp_pyramids")); // TODO: hardcoded 4 base points
    }

    return polygons;
}

void RussianPyramidScene::generatePyramids(int n)
{
        // Top-Left in pixels
        IntPair areaPos_PX = 
        {
            *&sdlutils().svgs().at(_pyramidFilenameSVG).at(_areaConstrainName).x - *&sdlutils().svgs().at(_pyramidFilenameSVG).at(_areaConstrainName).width/2,
            *&sdlutils().svgs().at(_pyramidFilenameSVG).at(_areaConstrainName).y - *&sdlutils().svgs().at(_pyramidFilenameSVG).at(_areaConstrainName).height/2
        };
        IntPair areaSize_PX = 
        {
            *&sdlutils().svgs().at(_pyramidFilenameSVG).at(_areaConstrainName).width, 
            *&sdlutils().svgs().at(_pyramidFilenameSVG).at(_areaConstrainName).height
        };
        SDL_Rect areaConstrain = {areaPos_PX.first, areaPos_PX.second, areaSize_PX.first, areaSize_PX.second};
    
        std::vector<Polygon> choosenPolygons;
        std::vector<std::vector<b2Vec2>> auxPoints;
        std::vector<int> polyIds;
        int pyramidSides = 4;
    
        pickAndPositionPyramidPolygons(n, areaConstrain, choosenPolygons, auxPoints, polyIds);
    
        for (int i = 0; i < choosenPolygons.size(); ++i) {
            createPyramid(choosenPolygons[i], auxPoints[i], polyIds[i]);
        }

        std::cout << "PYRAMIDS CREATED" << std::endl;
}

void
RussianPyramidScene::applyBossModifiers() {
    #if defined (_DEBUG)
    std::cout << "Aplicando modificadores de RussianPyramid" << std::endl;
    #endif

    //--Make sure the balls array is not null
    if(_currentWhiteBall == nullptr && !tryInitializeBallArray()) return;

    //--Asignar la nueva bola blanca
    entity_t newWhiteBall = nullptr;
    do {
        newWhiteBall = _allBalls[_rngManager->randomRange(0, _allBalls.size())];
    } while(newWhiteBall == _currentWhiteBall || newWhiteBall == _originalWhiteBall);
    _stickInput->registerWhiteBall(newWhiteBall);
    newWhiteBall->stealComponent<Button>(_currentWhiteBall);
    _currentWhiteBall = newWhiteBall;
    getEntitiesOfGroup(grp::WHITEBALL)[0] = _currentWhiteBall;

    //--Alterar los componentes de la nueva bola blanca
    _currentWhiteBall->deactivateComponentsOfType<BallEffect>();
    _currentWhiteBall->deactivateComponentsOfType<ColorBallScorerComponent>();
    addComponent<WhiteBallScorerComponent>(_currentWhiteBall);

    //--Tween del jefe
    changeWhiteBallAnimation();
}

void RussianPyramidScene::clearBossModifiers()
{
    #if defined(_DEBUG)
    std::cout<< "Eliminando modificadores de RussianPyramid" << std::endl;
    #endif

    if(_currentWhiteBall == nullptr) return;

    //--Devolver la bola a su estado original
    _currentWhiteBall->activateComponentsOfType<BallEffect>();
    _currentWhiteBall->activateComponentsOfType<ColorBallScorerComponent>();

    //Esto para asegurarnos de que no rompemos la bola blanca original (aunque no debería elegirse)
    if(_currentWhiteBall != getEntitiesOfGroup(grp::WHITEBALL)[0]) 
        _currentWhiteBall->removeComponent<WhiteBallScorerComponent>();

    //--Hacer desaparecer el indicador
    _indicator->deactivateComponentsOfType<RenderComponent>();
}

bool 
RussianPyramidScene::tryInitializeBallArray() {
    auto whiteBallgroup = getEntitiesOfGroup(grp::WHITEBALL);
    if(whiteBallgroup.size() == 0) return false;

    _currentWhiteBall = whiteBallgroup[0];
    _allBalls = getEntitiesOfGroup(grp::EFFECTBALLS);
    _allBalls.push_back(_currentWhiteBall);

    _stickInput = getComponent<StickInputComponent>(getEntitiesOfGroup(grp::PALO)[0]);
    
    return true;
}

void 
RussianPyramidScene::changeWhiteBallAnimation() {
    entity_t boss = getEntitiesOfGroup(grp::BOSS_HAND)[0];
    auto tween = boss->getComponent<TweenComponent>();
    auto whiteBallPos = _currentWhiteBall->getTransform()->getPosition();

    float halfHandMag = PhysicsConverter::pixel2meter(getComponent<RenderTextureComponent>(boss)->getRenderRect().h/2);

    Vector2D dir = Vector2D{startingHandPosition.x - whiteBallPos.x, startingHandPosition.y - whiteBallPos.y}.normalize();
    b2Vec2 handPos = whiteBallPos + b2Vec2{dir.getX() * halfHandMag , dir.getY() * halfHandMag};

    //Tween hacia la nueva bola
    tween->easePosition(handPos, .5f, tween::EASE_IN_OUT_CUBIC, false, [=]() {
        tween->easePosition(handPos, .2f, tween::EASE_IN_OUT_CUBIC, false, [=]() {
        getCamera()->shakeCamera(.2f, .3f, dir*-1);

        auto follow = getComponent<FollowComponent>(_indicator);
        follow->setTarget(_currentWhiteBall);
        _indicator->activateComponentsOfType<RenderComponent>();

        tween->easePosition(startingHandPosition, 1.0f, tween::EASE_IN_OUT_CUBIC, false, [=]() {_currentState->finish();});
        });}, 
    [=](){
        float radiansConversion = M_PI/180.0f;
        float handRot = (boss->getTransform()->getRotation()-90) * radiansConversion;
        Vector2D handDir = Vector2D{float(cos(handRot)), float(sin(handRot))}.normalize();

        b2Vec2 handEndPos = boss->getTransform()->getPosition() + b2Vec2{handDir.getX() * halfHandMag, handDir.getY()*halfHandMag};

        Vector2D dir = Vector2D{handEndPos.x - startingHandPosition.x, handEndPos.y - startingHandPosition.y}.normalize();
        //en radianes
        float angle = atan(dir.getX()/dir.getY());
        //en grados
        angle = angle * (180/M_PI);

        boss->getTransform()->setRotation(angle);
    });

    

    
}
