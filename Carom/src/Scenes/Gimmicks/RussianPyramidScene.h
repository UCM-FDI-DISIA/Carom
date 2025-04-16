#pragma once

#include "CaromScene.h"


using Polygon = std::vector<b2Vec2>;

class TweenComponent;

class RussianPyramidScene : public CaromScene 
{
public:
    RussianPyramidScene(Game* g, GameScene* reward, bool isBoss);
    virtual ~RussianPyramidScene();

protected:
    virtual void initGimmick() override;
    virtual void initBoss() override;
    void applyBossModifiers() override;
    void clearBossModifiers() override;

    bool tryInitializeBallArray();

    void createBoss();

    virtual void createEffectBalls(int n) override;

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

    entity_t _indicator;
};

