#pragma once
#include <string>
#include "ecs.h"
#include "AbacusEffect.h"
#include "PetanqueEffect.h"
#include "BowlingEffect.h"
#include "CristalEffect.h"
#include "X2Effect.h"
#include "QuanticEffect.h"
#include "PokeballEffect.h"

#include "BoxingGloveStickEffect.h"
#include "DonutStickEffect.h"
#include "MagicWandStickEffect.h"
#include "GranadeLauncherStickEffect.h"

namespace IdUtils{
static std::string getEffectStringFromId(effectId_t id){
    switch(id) {
            case effect::ABBACUS: return "AbaccusEffect"; break;
            case effect::BOWLING: return "BowlingEffect"; break;
            case effect::CRYSTAL: return "CrystalEffect"; break;
            case effect::PETANQUE: return "PetanqueEffect"; break;
            case effect::POKEBALL: return "PokeballEffect"; break;
            case effect::QUANTIC: return "QuanticEffect"; break;
            case effect::X2: return "X2Effect"; break;
    }
    return "";
}

static BallEffect* getEffectFromId(effectId_t id, BallHandler* h){
    switch(id){
            case effect::ABBACUS: return new AbacusEffect(h); break;
            case effect::BOWLING: return new BowlingEffect(h); break;
            case effect::CRYSTAL: return new CristalEffect(h); break;
            case effect::QUANTIC: return new QuanticEffect(h); break;
            case effect::PETANQUE: return new PetanqueEffect(h); break;
            case effect::X2: return new X2Effect(h); break;
            case effect::POKEBALL: return new PokeballEffect(h); break;
        }
        return nullptr;
}

static std::string getStickStringFromId(stickId_t id){
    switch(id) {
                case stick::NORMAL_STICK: return "NormalStick"; break;
                case stick::BOXING: return "BoxingStick"; break;
                case stick::DONUT: return "DonutStick"; break;
                case stick::GRENADE: return "GrenadeStick"; break;
                case stick::WAND: return "WandStick"; break;
        }
        return "";
}

static Component* applyStickEffectFromId(stickId_t id, entity_t e){
        switch(id) {
                case stick::BOXING: return new BoxingGloveStickEffect(e); break;
                case stick::DONUT: return new DonutStickEffect(e); break;
                case stick::GRENADE: return new GranadeLauncherStickEffect(e); break;
                case stick::WAND: return new MagicWandStickEffect(e); break;
        }
        return nullptr;
}
}