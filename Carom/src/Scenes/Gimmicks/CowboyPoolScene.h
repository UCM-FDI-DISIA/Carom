#pragma once

#include "CaromScene.h"

#include <memory>

using IntPair = std::pair<int,int>;
using Polygon = std::vector<b2Vec2>;
using PolyID = int;



class TweenComponent;

/// @brief Escena de partida del piso Cowboy Pool
class CowboyPoolScene : public CaromScene {
    b2Vec2 startingHandPosition = {2, 3};
public:
        CowboyPoolScene(Game* g, bool isBoss, State* state = nullptr);
        virtual ~CowboyPoolScene();

protected:

    void initGimmick() override; // Inicialización de la gimmick
    void initBoss() override; // Inicialización del boss
    void applyBossModifiers() override; // Aplica los modificadores al comienzo del turno del boss
    void clearBossModifiers() override; // Quita los modificadores del turno anterior

    // Creación y animación del brazo y sombra de boss
    void moveAndShoot(int index, std::vector<b2Vec2> bulletPos, TweenComponent* tween);
    void createBoss();

    // Creación de Gimmicks (Bancos de arena)
    void createSandBank(Polygon& vertices, float friction, float scale, SDL_Rect sandRect);
    void pickAndPositionSandPolygons(
        int numPolys
        , SDL_Rect areaConstrain
        , std::vector<Polygon> &choosenPolygons
        , std::vector<PolyID>  &choosenPolyIDs
        , std::vector<b2Vec2>  &offsets);
    float processSandTexture(b2Vec2 offset, SDL_Rect areaConstrain, int imgId, SDL_Rect& sandRectCenter);
    void generateSandBanks(int n, float friction);

    // Creación de modificadores de boss (Agujeros de bala)
    void createBulletHole(const b2Vec2& pos);  
    bool canPlaceHole(entity_t e, b2Vec2 hole_pos, float hole_radius);
    std::vector<b2Vec2> generateBulletHolesPositions(int numPos);  

private:
    int _sandBanks;
    std::string _arenaFilenameSVG;
    std::string _sandConstrainName;
    float _sandFriction;
    int _nAvailablePolygons;
    int _nVertices;
};

