#pragma once

class Reward {
public:
    enum Instant {
        DEFAULT, // Empty reward
        FUSION,
        GUMBALL_MACHINE,
        STORAGE_ROOM,
        CAULDRON
    };

    struct Perma {
        int hitEase = 0, comboEase = 0, caromEase = 0;
        int charisma = 0;   // carisma
        int power = 0;      // poder
        float cunning = 1.0f;  // picardía
    };

    static constexpr Perma defaultPerma {0,0,0, 0, 0, 1.0f}; 

protected:
    Instant _instantReward;
    Perma _permanentReward;

    bool isDefaultPerma() {
        return (
            _permanentReward.hitEase == defaultPerma.hitEase &&
            _permanentReward.comboEase == defaultPerma.comboEase &&
            _permanentReward.caromEase == defaultPerma.caromEase &&
            _permanentReward.charisma == defaultPerma.charisma &&
            _permanentReward.power == defaultPerma.power &&
            _permanentReward.cunning == defaultPerma.cunning
        );
    }

public:
    Reward(Instant instant = Instant::DEFAULT, Perma perma = Perma()) 
    : _instantReward(instant)
    , _permanentReward(perma)
    {}

    inline bool isDefault() {
        return (_instantReward == Instant::DEFAULT && isDefaultPerma());
    }
    
};