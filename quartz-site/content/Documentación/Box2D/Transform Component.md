## b2 y transform component
Como podemos usar en nuestro componente
```cpp
struct TransformComponent { 
	// Referencia constante, pues box2D que se encarga de actualizar el transform
	const b2Transform* transform;
};
```

## Métodos útiles
```cpp
// Para update position si necesario
b2SetTransform(bodyId, position, angle);
// Transform: posición y rotación
b2Transform transform = b2Body_GetTransform(boduId);
// Coger el vector posición
b2Vec2 vecXY = b2Body_GetPosition(bodyId);
