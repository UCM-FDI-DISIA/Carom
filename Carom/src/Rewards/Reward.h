#pragma once

#include <string>

class Reward {
public:
    enum Type {
        DEFAULT,
        INSTANT,
        PERMANENT,
        BOSS
    };

protected:
    std::string _name;
    Type _type;

    Reward() {
        _name = "default";
        _type = Type::DEFAULT;
    }
    
    Reward(std::string n, Type t) : _name(n), _type(t) {
        
    }
    
public:
    inline std::string getName() { return _name; }
    inline Type getType() { return _type; }

    virtual void applyReward() = 0;
};