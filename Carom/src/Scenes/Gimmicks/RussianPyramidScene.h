#pragma once

#include "CaromScene.h"


using Polygon = std::vector<b2Vec2>;

class TweenComponent;

/// @brief Escena de partida del piso RussianPyramid
class RussianPyramidScene : public CaromScene 
{
public:
    /// @brief La constructora de russian pyramid
    /// @param g El puntero al juego
    /// @param isBoss Booleano que indica si es la escena de boss
    /// @param state El estado en el que empieza la escena
    RussianPyramidScene(Game* g, bool isBoss, State* state = nullptr);
    virtual ~RussianPyramidScene();

protected:
    virtual void initGimmick() override;
    virtual void initBoss() override;
    void applyBossModifiers() override;
    void clearBossModifiers() override;

    /// @brief Método para obtener todas las bolas que se pueden convertir en bola blanca
    bool tryInitializeBallArray();

    /// @brief Método auxiliar para instanciar todo lo que necesita el boss
    void createBoss();

    /// @brief Método auxiliar para que las bolas no estén en la misma posición que una pirámide al comenzar una ronda
    virtual void createEffectBalls() override;

    // Gimmicks
    void createPyramid(std::vector<b2Vec2> &points, std::vector<b2Vec2> &auxPoints, int polyId);
    void pickAndPositionPyramidPolygons(
        int numPolys
        , const SDL_Rect& areaConstrain
        , std::vector<Polygon> &choosenPolygons
        , std::vector<std::vector<b2Vec2>> &auxPoints
        , std::vector<int> &polyIds);
    std::vector<b2Vec2> getAuxPoints(int n, int polyId, const b2Vec2 &offset);
    std::vector<Polygon> getPyramidsPolygons(int n, int polyId);
    void generatePyramids(int n);

    // Boss modifiers
private:
    std::string _pyramidFilenameSVG;
    std::string _areaConstrainName;
    int _nAvailablePyramids;
    std::vector<Polygon> _pyramidBasePolys;

    std::vector<entity_t> _allBalls;
    entity_t _currentWhiteBall;
    entity_t _originalWhiteBall;

    b2Vec2 startingHandPosition = {2, 3};

    void changeWhiteBallAnimation();
};