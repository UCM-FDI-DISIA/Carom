#include "FollowComponent.h"
#include "ITransform.h"
#include "Entity.h"

namespace ecs{
    FollowComponent::FollowComponent(Entity* e, Entity* target, bool copyPosition, bool copyRotation, bool copyScale, 
        Vector2D relativeDistance): 
        LogicComponent(e),
        _targetToCopy(target), 
        _copyPosition(copyPosition), 
        _copyRotation(copyRotation), 
        _copyScale(copyScale),
        _relativeDistance(relativeDistance){}
    
    void FollowComponent::update(){
        ITransform* _targetTransform = _targetToCopy->getTransform();
        ITransform* _myTransform = _myEntity->getTransform();

        if(_copyPosition){
            b2Vec2 newPos = _targetTransform->getPosition() + b2Vec2{_relativeDistance.getX(), _relativeDistance.getY()};
            _myTransform->setPosition(newPos);
        }

        if(_copyRotation){
            _myTransform->setRotation(_targetTransform->getRotation());
        }

        if(_copyScale){
            _myTransform->setScale(_targetTransform->getScale());
        }

    }
}