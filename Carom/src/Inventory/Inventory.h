#pragma once

#include <vector>

#include "Singleton.h"
#include "ecs.h"
#include <box2d/box2d.h>
#include <string.h>
#include <SDL_filesystem.h>


class GameScene;

struct SlotInfo{
    bool used = false;
    std::vector<effectId_t> ballEffects;
}

class Inventory : public Singleton<Inventory> {

	friend Singleton<Inventory> ;
public:
    static const int MAX_BALLS = 6;
private:
	Inventory();
	virtual ~Inventory();

    inline bool init() {
        return true;
    }

    //inventory
    int _ease, _charisma, _combo, _hitEase, _power;
    float _cunning;
    SlotInfo _slots[MAX_BALLS];
    stickId_t _stick;

public:
    void setEase(int e);
    void setCharisma(int c);
    void setCombo(int c);
    void setHitEase(int h);
    void setPow(int p);
    void setCunning(float c);
    void setStick(stick::stickId id);

    int getEase();
    int getCharisma();
    int getCombo();
    int getHitEase();
    int getPow();
    float getCunning();
    stickId_t getStickType();

    int getNumberOfEffectBalls();
    void removeStick();
    void removeAllBalls();
    void removeBall(int index);

    bool addBall(std::vector<effectId_t> ids);

    std::vector<effectId_t>getEffectsFromBall(int index);
};