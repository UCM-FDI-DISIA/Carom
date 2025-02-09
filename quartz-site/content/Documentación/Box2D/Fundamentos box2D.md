# Descripción
Se debe "inicializar" el box2D creando un mundo. Luego, ponemos cosas en este mundo que tienen un cuerpo, una forma y propiedades. Box2D se encargará de la simulación de los rigid bodies y podemos acceder a los transform, aplicar impulso, fuerza, escuchar eventos de colisiones etc.

En este ejemplo que sigue tenemos la creación de un mundo con un objeto (ball) que se cae por gravedad.

>[!important] Coordenadas
>Las coordenadas de box2d son las cartesianas, así que hay que convertirlas a las de la pantalla a la hora de renderizar.
## Inicialización de mundo
 ```cpp
// Setup mundo ("The world definition is a temporary object that you can create on the stack")
b2WorldDef worldDef = b2DefaultWorldDef();
// worldDef.gravity = {0.0f, -10.0f}; // No va a ser necesario

// Creación
b2WorldId worldId = b2CreateWorld(&worldDef);
```

## Inicialización de objeto 
```cpp
// Se crea un objeto de definición de body (bodyDef)
b2BodyDef bodyDef_ball = b2DefaultBodyDef();
// Se le asigna un tipo (static, dynamic, kinematic)
bodyDef_ball.type = b2_dynamicBody;
// Se define una posición respecto al eje de coordenadas cartesiano (hay que hacer una conversión a coordenadas pantalla)
bodyDef_ball.position = {0.0f, 4.0f}; // Es un punto, o sea, body todavía no tiene una forma
// Con las definiciones hechas, creamos el body con su definición en el mundo 
b2BodyId ball = b2CreateBody(worldId, &bodyDef_ball);

// Se crea las propiedades de la forma (shapeDef)
b2ShapeDef shapeDef_ball = b2DefaultShapeDef();
shapeDef_ball.density = 1.0f;
shapeDef_ball.friction = 0.3f;
shapeDef_ball.restitution = 1.0f; // Rebote [0, 1], 1 = no se pierde energía

// La definición de body no dice sobre shape, por eso tenemos que definirlo
b2Circle circle_ball;
circle_ball.center = {0.0f, 0.0f}; // significa que no hay offset body-shape
circle_ball.radius = 0.5f; // Ahora body tiene una forma y puede tener un tamaño

// Juntamos todo: body + propiedades de shape + shape
b2CreateCircleShape(ball, &shapeDef_ball, &circle_ball);
```

## Simulación
```cpp
// Definición de del FPS (60)
float timeStep = 1.0f / 60.0f;
// Definición de cuantas iteraciones hechas por loop de simulación (precisión)
int subStepCount = 4; // 4 es lo recomendable

// En el gameloop
game_loop(){
	b2World_Step(worldId, timeStep, subStepCount); // simula 1/60s del estado del mundo iterando 4 veces
}
```

>[!note] Nota
>"Box2D includes a small vector math library including types b2Vec2, b2Rot, b2Transform, and b2AABB. This has been designed to suit the internal needs of Box2D and the interface. All the members are exposed, so you may use them freely in your application."


