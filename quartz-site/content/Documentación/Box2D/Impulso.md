### Como en el mundo concreto, el palo va aplicar un impulso a la bola:
```cpp
// Impulso aplicado al centro de massa (recomendo)
void b2Body_ApplyLinearImpulseToCenter(b2BodyId bodyId, b2Vec2 impulse, bool wake)
// Ejemplo:
b2Body_ApplyLinearImpulseToCenter(ball, {0.0f, 3.0f}, true); // Un impulso hacia arriba con 3 N.s de magnitud

// Impulso aplicado en un punto arbitrario de objeto. No sé si nos sirve, pues genera momento angular por el torque.
void b2Body_ApplyLinearImpulse(b2BodyId bodyId, b2Vec2 impulse, b2Vec2 point, bool wake)
```