#pragma once

#include "CaromScene.h"

namespace ecs{

    class TweenComponent;

    class CowboyPoolScene : public CaromScene {
        b2Vec2 startingHandPosition = {2, 3};
    public:
            CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss);

    protected:
        void initGimmick();
        void applyBossModifiers() override;

        void moveAndShoot(int index, std::vector<b2Vec2> bulletPos, TweenComponent* tween);
        void createBoss();

        // Gimmicks
        void createSandBank();

        // Boss modifiers
        void createBulletHole(const b2Vec2& pos);  
        std::vector<b2Vec2> generateBulletHolesPositions(int numPos);  

        bool canPlaceHole(entity_t e, b2Vec2 hole_pos, float hole_radius);
    };
}
