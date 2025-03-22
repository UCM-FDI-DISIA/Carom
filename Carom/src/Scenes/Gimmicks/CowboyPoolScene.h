#pragma once

#include "CaromScene.h"

namespace ecs{

    class TweenComponent;

    class CowboyPoolScene : public CaromScene {
        b2Vec2 startingHandPosition = {2, 3};
    public:
            CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss);
            virtual ~CowboyPoolScene();

    protected:
        void initGimmick();
        void applyBossModifiers() override;
        void clearBossModifiers() override;

        void moveAndShoot(int index, std::vector<b2Vec2> bulletPos, TweenComponent* tween);
        void createBoss();

        // Gimmicks
        void createSandBank(const std::vector<b2Vec2>& vertices, const SDL_Rect& rect, const b2Vec2& unclampedCenter, float friction);
        void generateSandBanks(int n, float friction, float minRadius, float maxRadius);

        // Boss modifiers
        void createBulletHole(const b2Vec2& pos);  
        bool canPlaceHole(entity_t e, b2Vec2 hole_pos, float hole_radius);
        std::vector<b2Vec2> generateBulletHolesPositions(int numPos);  

    private:
        int _sandBanks = 0;
    };
}
