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


RussianPyramidScene::RussianPyramidScene(State* state, Game* g, GameScene* reward, bool isBoss)
    : CaromScene(state, g, reward)
    , _pyramidFilenameSVG("grp_pyramids")
    , _areaConstrainName("area")
    , _nAvailablePyramids(1)

{
    if(isBoss) {
        _boss = Boss::RUSSIAN_PYRAMID;
        createBoss();
    }

    initGimmick();

    getComponent<RenderTextureComponent>(getEntitiesOfGroup(grp::TABLE_BACKGROUND)[0])->changeColorTint(206, 38, 0);
}

RussianPyramidScene::~RussianPyramidScene()
{
}

void RussianPyramidScene::createBoss(){
    // std::cout << "creando jefe y sombra" << std::endl;
    
    // //crear jefe
    // Entity* boss = new Entity(*this, grp::BOSS_HAND);
    // addComponent<TransformComponent>(boss, startingHandPosition);

    // float svgSize = *&sdlutils().svgs().at("grp_cowboy").at("cowboy_hand 1").width;
    // float textureSize = sdlutils().images().at("cowboy_hand").width();
    // float scale = svgSize/textureSize;

    // addComponent<RenderTextureComponent>(boss, &sdlutils().images().at("cowboy_hand"), renderLayer::BOSS_HAND, scale);
    // addComponent<TweenComponent>(boss);

    // //sombra
    // // Entity* sombraJefe = new Entity(*this, grp::SHADOWS);
    // // addComponent<TransformComponent>(sombraJefe, b2Vec2{0,0});
    // // addComponent<RenderTextureComponent>(sombraJefe, &sdlutils().images().at("cowboy_hand_shadow"), renderLayer::BOSS_SHADOW_HAND, scale);
    // // addComponent<FollowComponent>(sombraJefe, boss, true,true,true, Vector2D{-0.05, -0.05});

    // CaromScene::instantiateBossTableShadow();
}

void RussianPyramidScene::initGimmick(){
    //comportamiento (anyadir entidades de arena en la mesa)
    std::cout<< "RussianPyramidScene Gimmick Instantiated" << std::endl;

    int nPyramids = 1; // TODO
    generatePyramids(nPyramids);
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
            int attempts = 50;
            std::cout<< "attempts: " << attempts <<std::endl;
    
            // Try a polygon
            int polyId = _rngManager->getRandomItem(polygons, true);
            std::vector<b2Vec2> candidatePoly = pyramidPolygons[polyId];
    
            // Get peak ("center")
            b2Vec2& polyCenter = pyramidPeaks[polyId];
    
            while (!found && attempts > 0)
            {
                // Generate a radom center in PIXELS
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
                // std::cout << "offsetX: " << offset.x << " offsetY: " << offset.y << std::endl;
    
                for (auto& vert : candidatePoly){
                    // std::cout << "Before offset vertX : " << vert.x << " Before offset vertY : " << vert.y << std::endl;
                    vert += offset;
                    // std::cout << "After vertX : " << vert.x << " After vertY : " << vert.y << std::endl;
                }
                
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
    // std::cout << "aplicando modificador de boss desde RussianPyramidScene" << std::endl;

    // int n = sdlutils().rand().nextInt(1,4);
    // std::vector<b2Vec2> bulletPositions = generateBulletHolesPositions(n);
    // TweenComponent* t = getComponent<TweenComponent>(getEntitiesOfGroup(grp::BOSS_HAND)[0]);
    // moveAndShoot(0, bulletPositions, t);
}

void RussianPyramidScene::clearBossModifiers()
{
    // std::cout<< "ClearBossModifiers" << std::endl;
    // // Reset hole changes on balls and deactivate it
    // for(auto& e: getEntitiesOfGroup(grp::BOSS_MODIFIERS)){
    //     if (e->tryGetComponent<HoleComponent>())
    //         e->getComponent<HoleComponent>()->resetChanges();
    //     e->setAlive(false);
    // }
}
