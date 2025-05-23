#include "RigidBodyComponent.h"
#include "TransformComponent.h"

#include "Entity.h"
#include "CaromScene.h"

#include "ITransform.h"

#include "Vector2D.h"

#include <exception>
#include <typeinfo>
#include <cmath>
#include <math.h>

/// @brief Constructor of RigidBody. Receives a Shape class as a parameter depending on which shape is needed (circle, capsule or polygon)
/// @param ent The owner of the component
/// @param type The type of the component (kinematic, dynamic or static)
/// @param density The density of the object
/// @param friction The friction of the object
/// @param restitution The restitution of the object
/// @param shape The shape of the rigid body. Can be CircleShape, CapsuleShape or PolygonShape.
RigidBodyComponent::RigidBodyComponent(Entity* ent) : InfoComponent(ent), ITransform()
{
    _myProps.sleepThreshold = 0.2f;
}

/// @brief Destructor of the Rigidbody. Also destroys box2d bodies.
RigidBodyComponent::~RigidBodyComponent()
{
    delete _myB2ShapeDef;
    b2DestroyBody(_myB2BodyId);
}

/// @brief The update changes the scale if a scale change is buffered.
void RigidBodyComponent::update()
{
    if(_scaleBuffer.first){
        updateScale();
        _scaleBuffer.first = false;
    }
}

/// @brief Generates box2d body and shapes to ensure the physics work without problems
void
RigidBodyComponent::generateBodyAndShape(){
    // entity_t ent, const b2Vec2& vec, b2BodyType bodyType, float density, float friction, float restitution, bool sensor){

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = _myProps.bodyType;
    bodyDef.gravityScale = 0.0f;
    bodyDef.position = _myProps.initialPos;
    bodyDef.userData = _myEntity;
    bodyDef.sleepThreshold = _myProps.sleepThreshold; // velocidad mínima para dormir (aunque no funcione muy bien)
    bodyDef.isBullet = _myProps.isBullet; // para collisiones rápidas
    bodyDef.linearDamping = _myProps.linearDamping; // friccíon con el suelo
    bodyDef.rotation = _myProps.rotation;

    _myB2BodyId = dynamic_cast<CaromScene*>(&_myEntity->getScene())->addBodyToWorld(bodyDef);

    _myB2ShapeDef = new b2ShapeDef(b2DefaultShapeDef());
    _myB2ShapeDef->density = _myProps.density;
    _myB2ShapeDef->friction = _myProps.friction;
    _myB2ShapeDef->restitution = _myProps.restitution;
    _myB2ShapeDef->enableContactEvents = _myProps.enableContactEvents;
    _myB2ShapeDef->userData = _myEntity;
    _myB2ShapeDef->isSensor = _myProps.isSensor;

}

/// @brief Accesor de posición
/// @return Vector posición en el mundo físico
b2Vec2
RigidBodyComponent::getPosition() const {
    return b2Body_GetPosition(_myB2BodyId);
}

/// @brief Accesor de escala
/// @return Escala en x y en Y como multiplicadores
ITransform::Scale
RigidBodyComponent::getScale() const {
    return _myScale;
}

/// @brief Accesor de rotación
/// @return Rotación en radianes
double
RigidBodyComponent::getRotation() const {
    b2Rot a_b2r = b2Body_GetRotation(_myB2BodyId);
    return b2Atan2(a_b2r.s, a_b2r.c) * 180. / B2_PI;
}

/// @brief Returns a bool indicating whether the body is moving
bool
RigidBodyComponent::isMoving() {
    b2Vec2 vel = getVelocity();

    float currentSpeed = std::sqrt(std::pow(vel.x, 2) + std::pow(vel.y, 2));
    if(currentSpeed > TERMINAL_VELOCITY) return true;

    b2Body_SetLinearVelocity(_myB2BodyId, b2Vec2_zero);
    b2Body_SetAngularVelocity(_myB2BodyId, .0f);
    return false;
}

/// @brief Returns the speed of the body
float
RigidBodyComponent::getVelocityMag() {
    b2Vec2 vel = getVelocity();
    return std::sqrt(std::pow(vel.x, 2) + std::pow(vel.y, 2));
}

/// @brief Recoloca el objeto físico
/// @param newPos Posición cartesiana
void
RigidBodyComponent::setPosition(const b2Vec2& newPos) {
    b2Body_SetTransform(_myB2BodyId, {newPos.x, newPos.y}, b2Body_GetRotation(_myB2BodyId));
}

/// @brief Asigna la rotación del objeto físico
/// @param newRot 
void
RigidBodyComponent::setRotation(const double& newRot) {
    b2Body_SetTransform(_myB2BodyId, b2Body_GetPosition(_myB2BodyId), {(float)std::cos(newRot), (float)std::sin(newRot)});
}

/// @brief Buffers the new scale to change it later
/// @param newScale the new scale
void
RigidBodyComponent::setScale(const Scale& newScale){
    _scaleBuffer = {true, newScale};
}

/// @brief Changes the body type.
/// @param newType New type of the RigidBody.
void
RigidBodyComponent::setBodyType(b2BodyType newType){
    b2Body_SetType(_myB2BodyId, newType);
}

/// @brief Applies force at the specified offset origin point
/// @param force the vector force to apply
/// @param origin the offset. {0,0} is the center of the object
void
RigidBodyComponent::applyForceToObject(b2Vec2 force, b2Vec2 origin){
    b2Vec2 a_b2t = b2Body_GetPosition(_myB2BodyId);
    b2Body_ApplyForce(_myB2BodyId, force, origin + a_b2t, true);
}

/// @brief Applies force at the specified world origin point
/// @param force the vector force to apply
/// @param origin the world point. {0,0} is the point {0,0} of the world
void
RigidBodyComponent::applyForceToWorld(b2Vec2 force, b2Vec2 origin){
    b2Body_ApplyForce(_myB2BodyId, force, origin, true);
}

/// @brief Applies force at the center of the object
/// @param force the vector force to aplly
void
RigidBodyComponent::applyForceToCenter(b2Vec2 force){
    b2Body_ApplyForceToCenter(_myB2BodyId, force, true);
}

/// @brief Applies impulse at the specified offset origin point
/// @param impulse the vector impulse to apply
/// @param origin the offset. {0,0} is the center of the object
void
RigidBodyComponent::applyImpulseToObject(b2Vec2 impulse, b2Vec2 origin){
    b2Vec2 a_b2t = b2Body_GetPosition(_myB2BodyId);
    b2Body_ApplyLinearImpulse(_myB2BodyId, impulse, origin + a_b2t, true);
}

/// @brief Applies impulse at the specified world origin point
/// @param impulse the vector impulse to apply
/// @param origin the world point. {0,0} is the point {0,0} of the world
void
RigidBodyComponent::applyImpulseToWorld(b2Vec2 impulse, b2Vec2 origin){
    b2Body_ApplyLinearImpulse(_myB2BodyId, impulse, origin, true);
}

/// @brief Applies impulse at the center of the object
/// @param impulse the vector impulse to aplly
void
RigidBodyComponent::applyImpulseToCenter(b2Vec2 impulse){
    b2Body_ApplyLinearImpulseToCenter(_myB2BodyId, impulse, true);
}

/// @brief Changes the density of every Shape of the object
/// @param density the new density for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setDensity(float density, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(_myB2BodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetDensity(shapes[i], density, true);
    }
}

/// @brief Changes the density of an object
/// @param density the new density for the shape
void RigidBodyComponent::setDensity(float density)
{
    _myProps.density = density;
    calculateMass();
    b2Shape_SetDensity(_myB2ShapeId, density, true);
}

/// @brief Changes the friction of every Shape of the object
/// @param density the new friction for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setFriction(float friction, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(_myB2BodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetFriction(shapes[i], friction);
    }

}

/// @brief Changes the friction of an object
/// @param density the new friction for the shape
void RigidBodyComponent::setFriction(float friction)
{
    _myProps.friction = friction;
    b2Shape_SetFriction(_myB2ShapeId, friction);
}

/// @brief Changes the restitution of every Shape of the object
/// @param density the new restitution for the shapes
/// @param nShapes the number of shapes the object has (Will throw an error if there's no match)
void
RigidBodyComponent::setRestitution(float restitution, int nShapes){
    b2ShapeId shapes[10];
    b2Body_GetShapes(_myB2BodyId, shapes, nShapes);
    
    for(int i = 0; 9 < nShapes; ++i){
        b2Shape_SetRestitution(shapes[i], restitution);
    }
}

/// @brief Changes the restitution of an object
/// @param density the new restitution for the shape
void RigidBodyComponent::setRestitution(float restitution)
{
    _myProps.restitution = restitution;
    b2Shape_SetRestitution(_myB2ShapeId, restitution);
}

/// @brief Changes the linear damping of an object
/// @param damping the new linear damping of the shape
void RigidBodyComponent::setLinearDamping(float damping)
{
    _myProps.linearDamping = damping;
    b2Body_SetLinearDamping(_myB2BodyId, damping);
}

/// @brief Enables/Disables the rigidbody in box2d
/// @param enabled if the body will be enabled or not
void RigidBodyComponent::setBodyEnabled(bool enabled)
{
    if(enabled)
        b2Body_Enable(_myB2BodyId);
    else 
        b2Body_Disable(_myB2BodyId);
}

/// @brief overrided method to enable/disable the component
/// @param state if the component will be enabled or not
void
RigidBodyComponent::setEnabled(bool state) {
    _isEnable = state;
    setBodyEnabled(state);
}

/// @brief Function called everytime object enters a collision
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onCollisionEnter(entity_t ent, b2Manifold& contactData){
    for(PhysicsComponent* PC : _collisionEnter){
        PC->onCollisionEnter(ent, contactData);
    }
}

/// @brief Function called everytime object exits a collision
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onCollisionExit(entity_t ent){
    for(PhysicsComponent* PC : _collisionExit){
        PC->onCollisionExit(ent);
    }
}

/// @brief Function called everytime object enters a sensor
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onTriggerEnter(entity_t ent){
    for(PhysicsComponent* PC : _triggerEnter){
        PC->onTriggerEnter(ent);
    }
}

/// @brief Function called everytime object exits a sensor
/// @param ent object that collides with this rigidbody
void 
RigidBodyComponent::onTriggerExit(entity_t ent){
    for(PhysicsComponent* PC : _triggerExit){
        PC->onTriggerExit(ent);
    }
}

/// @brief adds a physics component to the trigger and collision events lists, as a listener
/// @param PC The physicsComponent/listener
void
RigidBodyComponent::suscribePhysicsComponent(PhysicsComponent* PC){
    _triggerExit.push_back(PC);
    _triggerEnter.push_back(PC);
    _collisionExit.push_back(PC);
    _collisionEnter.push_back(PC);

    PC->setOnDestroy([this]() -> void {
        if (!_triggerExit.empty()) {
            _triggerExit.erase(--_triggerExit.end());
        }
        if (!_triggerEnter.empty()) {
            _triggerEnter.erase(--_triggerEnter.end());
        }
        if (!_collisionExit.empty()) {
            _collisionExit.erase(--_collisionExit.end());
        }
        if (!_collisionEnter.empty()) {
            _collisionEnter.erase(--_collisionEnter.end());
        }        
    });
}