#include "CowboyPoolScene.h"
#include "Entity.h"
#include "PhysicsUtils.h"
#include "GraphicsUtils.h"
#include "ecs.h"
#include "RNG_Manager.h"

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


namespace ecs{

    CowboyPoolScene::CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss): CaromScene(state, g, reward){
        if(isBoss) _boss = Boss::COWBOY_POOL;

        createBoss();
        initGimmick();
    }

    CowboyPoolScene::~CowboyPoolScene()
    {
        for (int i = 0; i < _sandBanks; ++i) {
            sdlutils().deleteImage(std::to_string(i));
        }
    }

    void CowboyPoolScene::createBoss(){
        //crear jefe
        Entity* boss = new Entity(*this, grp::BOSS_HAND);
        addComponent<TransformComponent>(boss, startingHandPosition);

        float svgSize = *&sdlutils().svgs().at("grp_cowboy").at("cowboy_hand 1").width;
        float textureSize = sdlutils().images().at("cowboy_hand").width();
        float scale = svgSize/textureSize;

        addComponent<RenderTextureComponent>(boss, &sdlutils().images().at("cowboy_hand"), renderLayer::BOSS_HAND, scale);
        addComponent<TweenComponent>(boss);

        //sombra
        Entity* sombraJefe = new Entity(*this, grp::SHADOWS);
        addComponent<TransformComponent>(sombraJefe, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(sombraJefe, &sdlutils().images().at("cowboy_hand_shadow"), renderLayer::BOSS_SHADOW, scale);
        addComponent<FollowComponent>(sombraJefe, boss, true,true,true, Vector2D{-0.05, -0.05});
    }

    void CowboyPoolScene::initGimmick(){
        //comportamiento (anyadir entidades de arena en la mesa)
        std::cout<< "CowboyPool Gimmick Instantiated" << std::endl;

        generateSandBanks(3, 2, 100, 200);
    }

    void CowboyPoolScene::createSandBank(const std::vector<b2Vec2>& vertices, const SDL_Rect& rect, const b2Vec2& unclampedCenter, float friction) 
    {
        int id = _sandBanks;
        Entity* e = new Entity(*this, grp::GIMMICK);
    
        // Skip if the SDL_Rect has zero width or height
        if (rect.w <= 0 || rect.h <= 0) {
            std::cout << "Skipping sandbank: SDL_Rect has zero width or height" << std::endl;
            return;
        }
    
        // Use the unclamped center as the position of the physics body (in meters)
        b2Vec2 pos = unclampedCenter;
    
        // Convert vertices to local coordinates by subtracting the body's position
        std::vector<b2Vec2> localVertices = vertices;
        for (auto& vertex : localVertices) {
            vertex -= pos;
        }
    
        // Create the physics body with the adjusted local vertices
        addComponent<PolygonRBComponent>(e, pos, b2_staticBody, localVertices, 0, true);
    
        // Render the texture using the SDL_Rect
        std::vector<uint8_t> alphaMask = GraphisUtils::computeAlphaMask(vertices, rect, 0.01f);
        sdlutils().addImage(std::to_string(id), "../../resources/images/arenatest.jpg", rect, alphaMask);
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at(std::to_string(id)), renderLayer::GIMMICK, 1);
        auto renderCmp =  e->getComponent<RenderTextureComponent>();
        renderCmp->setPortion(true);

        addComponent<FrictionComponent>(e, friction);
    
        _sandBanks++;
    }

    // float minRadius, float maxRadius are in pixels
    void CowboyPoolScene::generateSandBanks(int n, float friction, float minRadius, float maxRadius)
    {
        std::pair<int, int> areaPos = {*&sdlutils().svgs().at("grp_cowboy").at("arenaArea").x - *&sdlutils().svgs().at("grp_cowboy").at("arenaArea").width/2  , *&sdlutils().svgs().at("grp_cowboy").at("arenaArea").y - *&sdlutils().svgs().at("grp_cowboy").at("arenaArea").height/2};
        auto [areaPosX, areaPosY] = areaPos;

        std::pair<int, int> areaSize = {*&sdlutils().svgs().at("grp_cowboy").at("arenaArea").width, *&sdlutils().svgs().at("grp_cowboy").at("arenaArea").height};
        auto [areaWidth, areaHeight] = areaSize;

        int numPoints = 8; // number of points that define the polygon (box2d max = 8!)
        std::vector<std::vector<b2Vec2>> sandBanksPolygons = GraphisUtils::generateNonOverlappingPolygons(
            minRadius, maxRadius, n, numPoints, areaPosX, areaPosY, areaWidth, areaHeight, _rngManager
        );
    
        // Get bounding boxes to make a rect that won't exceed area limits
        auto [boundingBoxes, unclampedCenters] = GraphisUtils::generatePolygonBoundingBoxes(
            sandBanksPolygons, areaPosX, areaPosY, areaWidth, areaHeight
        );
    
        for (int i = 0; i < sandBanksPolygons.size(); ++i) {
            createSandBank(sandBanksPolygons[i], boundingBoxes[i], unclampedCenters[i], friction);
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
            int id = _rngManager->getRandomItem(positions, true) ;

            std::string s = "shot_hole";
            if(id > 1)
                s += ("_" + std::to_string(id));
            
            auto& hole = sdlutils().svgs().at("shot_positions").at(s);
            b2Vec2 hole_pos = PhysicsConverter::pixel2meter(hole.x, hole.y);
            float hole_radius = PhysicsConverter::pixel2meter(static_cast<float>(sdlutils().svgs().at("shot_positions").at("shot_hole").width)/2) ;

            // Comprobar si es válido
            bool valid = true;

            auto balls = (getEntitiesOfGroup(ecs::grp::WHITEBALL));
            for(auto& e : balls) {
                if(e->tryGetComponent<CircleRBComponent>()) { // TODO: cambiar esto cuando se mergee con la rama de Diego el tryGetComponent
                    if(!canPlaceHole(e, hole_pos, hole_radius)) {
                        valid = false;
                        break;
                    }
                }
            }
            
            if(!valid) continue; // No seguir comprobando si no es válido

            balls = getEntitiesOfGroup(ecs::grp::EFFECTBALLS);
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

        float halfHandMag = PhysicsConverter::pixel2meter(getComponent<RenderTextureComponent>(boss)->getRect().h/2);

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
        // // Reset hole changes on balls and deactivate it
        // for(auto& e: getEntitiesOfGroup(ecs::grp::BOSS_MODIFIERS)){
        //     if (e->tryGetComponent<HoleComponent>()){
        //         auto hole = e->getComponent<HoleComponent>();
        //         hole->resetChanges();
        //         e->deactivate();
        //     }
        // }
    }

    bool
    CowboyPoolScene::canPlaceHole(entity_t e, b2Vec2 hole_pos, float hole_radius) {
        auto ball_tr = e->getComponent<CircleRBComponent>();
        auto ball_pos = ball_tr->getPosition();
        auto ball_radius = ball_tr->getRadius();
        
        return !PhysicsConverter::circleOverlap(hole_pos, hole_radius, ball_pos, ball_radius);
    }
}
