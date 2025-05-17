#include <cassert>
#include "State.h"
#include "CaromScene.h"
#include "Button.h"
#include "FollowComponent.h"


void State::setBallInputActive(bool active)
{
    if (active) {
        auto whiteBall = _scene->getEntitiesOfGroup(grp::WHITEBALL);
        assert(whiteBall.size() > 0);

        for (auto& e : whiteBall) {
            if(e->tryGetComponent<Button>()) {
                e->getComponent<Button>()->setEnabled(true);
            }
        }
        for (auto& e : _scene->getEntitiesOfGroup(grp::FEEDBACK)) {
            if(e->tryGetComponent<FollowComponent>()) {
                e->activate();
            }
        }
    }
    else {
        for (auto& e : _scene->getEntitiesOfGroup(grp::WHITEBALL)) {
            if(e->tryGetComponent<Button>()) {
                e->getComponent<Button>()->setEnabled(false);
            }
        }
        for (auto& e : _scene->getEntitiesOfGroup(grp::FEEDBACK)) {
            if(e->tryGetComponent<FollowComponent>()) {
                e->deactivate();
            }
        }
    }
}

void State::setAimLineActive(bool active)
{
    if (active) {
        for (auto& e : _scene->getEntitiesOfGroup(grp::AIM_LINE)) { 
            e->activate();
        }
    }
    else {
        for (auto& e : _scene->getEntitiesOfGroup(grp::AIM_LINE)) { 
            e->deactivate();
        }
    }
}

void State::setStickActive(bool active)
{
    if (active) {
        for (auto& e : _scene->getEntitiesOfGroup(grp::PALO)) {
            e->activate();
        }
    }
    else {
        for (auto& e : _scene->getEntitiesOfGroup(grp::PALO)) {
            e->deactivate();
        }
    }
}
