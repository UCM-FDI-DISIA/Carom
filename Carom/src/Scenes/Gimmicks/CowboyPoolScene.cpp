#include "CowboyPoolScene.h"
#include "Entity.h"
#include "PhysicsUtils.h"
#include "GraphicsUtils.h"
#include "ecs.h"
#include "RNG_Manager.h"

#include <format>

#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "PolygonRBComponent.h"
#include "TweenComponent.h"
#include "BoxRBComponent.h"
#include "CircleRBComponent.h"
#include "ForceAreaComponent.h"
#include "FrictionComponent.h"
#include "HoleComponent.h"
#include "RNG_Manager.h"
#include "RandomItem.h"
#include "FollowComponent.h"




CowboyPoolScene::CowboyPoolScene(Game* g, GameScene* reward, bool isBoss)
    : CaromScene(g, reward)
    , _sandBanks(0)
    , _arenaFilenameSVG("grp_arena")
    , _sandConstrainName("arenaArea")
    , _sandFriction(2.0f)
    , _nAvailablePolygons(8)
    , _nVertices(8)
{
    _isBoss = isBoss;
}

CowboyPoolScene::~CowboyPoolScene()
{
    std::cout << "DESTRUCTOR COWBOY" << std::endl;
    // SDLUtils borra las imágenes, pero si hay reload de la escena necesita estar todo borrado
    for (int i = 0; i < _sandBanks; ++i) {
        sdlutils().deleteImage(std::to_string(i));
    }
}

void CowboyPoolScene::createBoss(){
    std::cout << "creando jefe y sombra" << std::endl;
    
    //crear jefe
    Entity* boss = new Entity(*this, grp::BOSS_HAND);
    addComponent<TransformComponent>(boss, startingHandPosition);

    float svgSize = *&sdlutils().svgs().at("grp_cowboy").at("cowboy_hand 1").width;
    float textureSize = sdlutils().images().at("cowboy_hand").width();
    float scale = svgSize/textureSize;

    addComponent<RenderTextureComponent>(boss, &sdlutils().images().at("cowboy_hand"), renderLayer::BOSS_HAND, scale);
    addComponent<TweenComponent>(boss);

    //sombra
    // Entity* sombraJefe = new Entity(*this, grp::SHADOWS);
    // addComponent<TransformComponent>(sombraJefe, b2Vec2{0,0});
    // addComponent<RenderTextureComponent>(sombraJefe, &sdlutils().images().at("cowboy_hand_shadow"), renderLayer::BOSS_SHADOW_HAND, scale);
    // addComponent<FollowComponent>(sombraJefe, boss, true,true,true, Vector2D{-0.05, -0.05});

    CaromScene::instantiateBossTableShadow();
}

void CowboyPoolScene::initGimmick(){
    //comportamiento (anyadir entidades de arena en la mesa)
    std::cout<< "CowboyPool Gimmick Instantiated" << std::endl;

    int nBanks = 3; // Number of sandbanks to be generated
    generateSandBanks(nBanks, _sandFriction);
}

void CowboyPoolScene::initBoss()
{
    getComponent<RenderTextureComponent>(getEntitiesOfGroup(grp::TABLE_BACKGROUND)[0])->changeColorTint(206, 38, 0);

    if(_isBoss) {
        _boss = Boss::COWBOY_POOL;
        createBoss();
    }
}

void CowboyPoolScene::createSandBank(Polygon& vertices, float friction, float scale, SDL_Rect sandRect) 
{
    Entity* e = new Entity(*this, grp::GIMMICK);

    for (auto& vertex : vertices) {
        vertex = PhysicsConverter::pixel2meter(vertex.x, vertex.y);
    }

    addComponent<PolygonRBComponent>(e, b2Vec2_zero, b2_staticBody, vertices, 0, true);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at(std::to_string(_sandBanks)), renderLayer::GIMMICK, scale, sandRect);
    addComponent<FrictionComponent>(e, friction);

    _sandBanks++;
}

void CowboyPoolScene::pickAndPositionSandPolygons(
        int                   numPolys
    , SDL_Rect              areaConstrain
    , std::vector<Polygon> &choosenPolygons
    , std::vector<PolyID>  &choosenPolyIDs
    , std::vector<b2Vec2>  &offsets)
{
    // In PIXELS, floats
    std::vector<Polygon> sandBanksPolygons = GraphisUtils::extractPolygons(_nAvailablePolygons, _nVertices);

    // Getting a random polygon from svg
    std::vector<RandomItem<int>> polygons;
    for(int i = 1; i <= _nAvailablePolygons; ++i)
        polygons.emplace_back(i, 1.0f);

    // numPolys = number of sand banks to generate
    for (int i = 0; i < numPolys; ++i)
    {
        bool found = false;
        int attempts = 50;
        // std::cout<< "attempts: " << attempts <<std::endl;

        // Try a polygon
        int polyId = _rngManager.getRandomItem(polygons, true);
        // std::cout << "polyid: " << polyId <<std::endl; 
        std::vector<b2Vec2> candidatePoly = sandBanksPolygons[polyId - 1];

        // Get center
        b2Vec2 polyCenter = GraphisUtils::calculatePolygonCenter(candidatePoly);

        while (!found && attempts > 0)
        {
            // Generate a radom center in PIXELS
            b2Vec2 genRandomCenter = {
                static_cast<float>
                (_rngManager.randomRange(areaConstrain.x, areaConstrain.x + areaConstrain.w)),
                static_cast<float>
                (_rngManager.randomRange(areaConstrain.y, areaConstrain.y + areaConstrain.h))
            };

            // Update vertices positions by offset (distance between gen and original centers)
            // PIXELS
            b2Vec2 offset = genRandomCenter - polyCenter;
            // std::cout << "offsetX: " << offset.x << " offsetY: " << offset.y << std::endl;

            for (auto& vert : candidatePoly){
                // std::cout << "Before offset vertX : " << vert.x << " Before offset vertY : " << vert.y << std::endl;
                vert += offset;
                // std::cout << "After vertX : " << vert.x << " After vertY : " << vert.y << std::endl;
            }
            
            // First polygon
            if (choosenPolygons.empty()){
                found = true;
            }
            else { // Try to put it in the table
                int j = 0;
                bool overlap = false;
                while (j < choosenPolygons.size() && !overlap){
                    overlap = GraphisUtils::doPolygonsOverlap(candidatePoly, choosenPolygons[j]);
                    ++j;
                }
                found = !overlap;
            }

            if (found){
                choosenPolygons.push_back(candidatePoly);
                choosenPolyIDs.push_back(polyId);
                offsets.push_back(offset);
            }
            else { // Revert update vertices positions by offset (distance between gen and original centers)
                for (auto& vert : candidatePoly){
                    vert -= offset;
                }
                attempts--;                    
            }
        }
    }
}

float CowboyPoolScene::processSandTexture(b2Vec2 offset, SDL_Rect areaConstrain, int imgId, SDL_Rect& sandRectCenter)
{
    auto svgElem = sdlutils().svgs().at(_arenaFilenameSVG).at(std::format("sand{}", imgId));
    auto texture = &sdlutils().images().at(std::format("sand{}", imgId));
    float svgSize = svgElem.width;
    float textureSize = sdlutils().images().at(std::format("sand{}", imgId)).width();
    float scale = svgSize / textureSize;

    // Offseted by polygon center
    // TOP LEFT PIXELS
    SDL_Rect originalSvgRectAbsTL = GraphisUtils::getTopLeftRect({svgElem.x, svgElem.y}, {svgElem.width, svgElem.height});
    originalSvgRectAbsTL.x += offset.x;
    originalSvgRectAbsTL.y += offset.y;

    // Offseted by polygon center
    // CENTER PIXELS
    SDL_Rect originalSvgRectAbsCenter = GraphisUtils::getCenterRect(originalSvgRectAbsTL);

    // For render texture
    // TOP LEFT PIXELS
    SDL_Rect partialSvgRectLocal = GraphisUtils::generatePartialRect(originalSvgRectAbsTL, areaConstrain);
    SDL_Rect partialTextureRectLocal = {
        (int)(partialSvgRectLocal.x / scale),
        (int)(partialSvgRectLocal.y / scale),
        (int)(partialSvgRectLocal.w / scale),
        (int)(partialSvgRectLocal.h / scale),
    };

    SDL_Rect partialSvgRectLocalCentered = GraphisUtils::getCenterRect(partialSvgRectLocal);

    SDL_Rect sandRectTL = {
        originalSvgRectAbsTL.x + partialSvgRectLocal.x,
        originalSvgRectAbsTL.y + partialSvgRectLocal.y,
        partialSvgRectLocal.w,
        partialSvgRectLocal.h
    };
    sandRectCenter = GraphisUtils::getCenterRect(sandRectTL);

    std::string imagePath = std::format("../../resources/images/sand{}.png", imgId);
    sdlutils().addImage(std::to_string(_sandBanks), imagePath, partialTextureRectLocal);

    return scale;
}

void CowboyPoolScene::generateSandBanks(int n, float friction)
{

    // Top-Left in pixels
    IntPair areaPos_PX = 
    {
        *&sdlutils().svgs().at(_arenaFilenameSVG).at(_sandConstrainName).x - *&sdlutils().svgs().at(_arenaFilenameSVG).at(_sandConstrainName).width/2,
        *&sdlutils().svgs().at(_arenaFilenameSVG).at(_sandConstrainName).y - *&sdlutils().svgs().at(_arenaFilenameSVG).at(_sandConstrainName).height/2
    };
    IntPair areaSize_PX = 
    {
        *&sdlutils().svgs().at(_arenaFilenameSVG).at(_sandConstrainName).width, 
        *&sdlutils().svgs().at(_arenaFilenameSVG).at(_sandConstrainName).height
    };
    SDL_Rect areaConstrain = {areaPos_PX.first, areaPos_PX.second, areaSize_PX.first, areaSize_PX.second};

    std::vector<Polygon> choosenPolygons;
    std::vector<PolyID> choosenPolyIDs;
    std::vector<b2Vec2> offsets;

    pickAndPositionSandPolygons(n, areaConstrain, choosenPolygons, choosenPolyIDs, offsets);

    for (int i = 0; i < choosenPolygons.size(); ++i) {
        SDL_Rect sandRect;
        float scale = processSandTexture(offsets[i], areaConstrain, choosenPolyIDs[i], sandRect);
        createSandBank(choosenPolygons[i], friction, scale, sandRect);
    }
}

void CowboyPoolScene::createBulletHole(const b2Vec2& pos){

    // SCALE
    float svgSize = *&sdlutils().svgs().at("game").at("hole1").width;
    float textureSize = sdlutils().images().at("hole").width();
    float scale = svgSize/textureSize;

    Entity* e = new Entity(*this, grp::BOSS_MODIFIERS);

    float radius = PhysicsConverter::pixel2meter(svgSize/2);
    addComponent<CircleRBComponent>(e, pos, b2_staticBody, radius, true);

    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);

    addComponent<HoleComponent>(e, 0.4f);
}

std::vector<b2Vec2>
CowboyPoolScene::generateBulletHolesPositions(int n) {
    int npos = sdlutils().svgs().at("shot_positions").size();
    assert(n <= npos);

    std::vector<b2Vec2> resPositions(n);

    std::vector<RandomItem<int>> positions;
    for(int i = 1; i <= npos; ++i)
        positions.push_back(RandomItem(i, 1.0f));
    
    
    while(n > 0 && positions.size() > 0) {
        // Obtener posición aleatoria para el agujero
        int id = _rngManager.getRandomItem(positions, true) ;

        std::string s = "shot_hole";
        if(id > 1)
            s += ("_" + std::to_string(id));
        
        auto& hole = sdlutils().svgs().at("shot_positions").at(s);
        b2Vec2 hole_pos = PhysicsConverter::pixel2meter(hole.x, hole.y);
        float hole_radius = PhysicsConverter::pixel2meter(static_cast<float>(sdlutils().svgs().at("shot_positions").at("shot_hole").width)/2) ;

        // Comprobar si es válido
        bool valid = true;

        auto balls = (getEntitiesOfGroup(grp::WHITEBALL));
        for(auto& e : balls) {
            if(e->tryGetComponent<CircleRBComponent>()) { // TODO: cambiar esto cuando se mergee con la rama de Diego el tryGetComponent
                if(!canPlaceHole(e, hole_pos, hole_radius)) {
                    valid = false;
                    break;
                }
            }
        }
        
        if(!valid) continue; // No seguir comprobando si no es válido

        balls = getEntitiesOfGroup(grp::EFFECTBALLS);
        for(auto& e : balls) {
            if(e->tryGetComponent<CircleRBComponent>()) { // TODO: cambiar esto cuando se mergee con la rama de Diego el tryGetComponent
                if(!canPlaceHole(e, hole_pos, hole_radius)) {
                    valid = false;
                    break;
                }
            }
        }
        
        // Si la posición es válida, crear agujero
        if(valid) {
            //createBulletHole(hole_pos);
            resPositions[n-1] = hole_pos;
            --n;
        }

    }

    return resPositions;
}

void
CowboyPoolScene::applyBossModifiers() {
    std::cout << "aplicando modificador de boss desde CowboyPoolScene" << std::endl;

    int n = sdlutils().rand().nextInt(1,4);
    std::vector<b2Vec2> bulletPositions = generateBulletHolesPositions(n);
    TweenComponent* t = getComponent<TweenComponent>(getEntitiesOfGroup(grp::BOSS_HAND)[0]);
    moveAndShoot(0, bulletPositions, t);
}

void CowboyPoolScene::moveAndShoot(int index, std::vector<b2Vec2> bulletPos, TweenComponent* tween){
    Entity* boss = getEntitiesOfGroup(grp::BOSS_HAND)[0];

    if(index >= bulletPos.size()) {
        tween->easePosition(startingHandPosition, .8f, tween::EASE_OUT_QUINT, false, [=]() {_currentState->finish();});
        return;
    }

    b2Vec2 pos = bulletPos[index];

    float halfHandMag = PhysicsConverter::pixel2meter(getComponent<RenderTextureComponent>(boss)->getRenderRect().h/2);

    Vector2D dir = Vector2D{startingHandPosition.x - pos.x, startingHandPosition.y - pos.y}.normalize();

    b2Vec2 handPos = pos + b2Vec2{dir.getX() * halfHandMag , dir.getY() * halfHandMag};

    tween->easePosition(handPos, .3f, tween::EASE_IN_OUT_CUBIC, false, [=](){
        createBulletHole(pos);
        getCamera()->shakeCamera(.2f, .3f, dir*-1);

        //efecto patras
        tween->easePosition({handPos.x, handPos.y + .3f}, .1f, tween::EASE_OUT_QUINT, false, [=](){
            tween->easePosition({handPos.x, handPos.y}, .3f, tween::EASE_OUT_ELASTIC, false, [=](){
                moveAndShoot(index+1, bulletPos, tween);
            });
        });

        
    }, 
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

void CowboyPoolScene::clearBossModifiers()
{
    std::cout<< "ClearBossModifiers" << std::endl;
    // Reset hole changes on balls and deactivate it
    for(auto& e: getEntitiesOfGroup(grp::BOSS_MODIFIERS)){
        if (e->tryGetComponent<HoleComponent>())
            e->getComponent<HoleComponent>()->resetChanges();
        e->setAlive(false);
    }
}

bool
CowboyPoolScene::canPlaceHole(entity_t e, b2Vec2 hole_pos, float hole_radius) {
    auto ball_tr = e->getComponent<CircleRBComponent>();
    auto ball_pos = ball_tr->getPosition();
    auto ball_radius = ball_tr->getRadius();
    
    return !PhysicsConverter::circleOverlap(hole_pos, hole_radius, ball_pos, ball_radius);
}

