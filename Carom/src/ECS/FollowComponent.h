#include "LogicComponent.h"
#include "Vector2D.h"
#include "ecs.h"

//Componente que copia ciertas propiedades de otra entidad, como la posición, rotación y escala.
class FollowComponent : public LogicComponent{
    Entity* _targetToCopy;
    bool _copyPosition = true;
    bool _copyRotation = true;
    bool _copyScale = true;
    Vector2D _relativeDistance = {0,0};
public:
__CMPID_DECL__(cmp::FOLLOW);

    //@param target Entidad a copiar propiedades
    //@param relativeDistance Si copia la posicion, distancia relativa a copiar (target.pos - relativeDistance = this.pos)
    FollowComponent(Entity* e, Entity* target, bool copyPosition, bool copyRotation, bool copyScale, 
        Vector2D relativeDistance);
    void update() override;
    inline void init() override {};

    //getters
    inline Vector2D getRelativeDistance(){return _relativeDistance;}
    inline bool getCopyPosition(){return _copyPosition;}
    inline bool getCopyRotation(){return _copyRotation;}
    inline bool getCopyScale(){return _copyScale;}
    inline Entity* getTarget() { return _targetToCopy; }

    //setters
    inline void setRelativeDistance(Vector2D newDistance){_relativeDistance = newDistance;}
    inline void setCopyPosition(bool boolean){_copyPosition = boolean;}
    inline void setCopyRotation(bool boolean){_copyRotation = boolean;}
    inline void setCopyScale(bool boolean){_copyScale = boolean;}
    inline void setTarget(entity_t newTarget) { _targetToCopy = newTarget; }
};
