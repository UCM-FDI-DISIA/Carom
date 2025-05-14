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

    std::string translateName(std::string s){
        if(s == "default"){ s = "Por defecto"; }
        else if(s == "fusion") { s = "Fusion"; }
        else if(s == "gumball") { s = "Maquina de chicles"; }
        else if(s == "stick") { s = "Desvan"; }
        else if(s == "cauldron") { s = "Caldero"; }
        else if(s == "skill") { s = "Soltura"; }
        else if(s == "charisma") { s = "Carisma"; }
        else if(s == "power") { s = "Poder"; }
        else if(s == "cunning") { s = "Picardia"; }
        return s;
    }

    std::string translateType(Type t){
        std::string s;
        switch (t) {
        case DEFAULT: s = "Por defecto"; break;
        case INSTANT: s = "Instantanea"; break;
        case PERMANENT: s = "Permanente"; break;
        case BOSS: s = "Jefe"; break;
        default: break;}
        return s;
    }
    
    virtual void applyReward() = 0;
};