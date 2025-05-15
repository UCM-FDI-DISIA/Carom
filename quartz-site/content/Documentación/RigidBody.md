Todos los objetos con físicas tienen un rigidbody encargado de crear su **shape** y **body** en **Box2D** e incluírlos en la simulación del mundo de [[Simulación de físicas en Carom]].

El rigidbody, en esencia, es un wrapper para acceder a la funcionalidad de los cuerpos de box2D de forma más intuitiva y cómoda. Desde el Rigidbody es posible pedirle a box2D que cambie propiedades como la fricción, que aplique un impulso en determinado punto, que se aplique una fuerza sobre el objeto, etc. Además, tiene almacenada toda esta información y es fácilmente accesible a través de getters

## Eventos de colisiones

El rigidBody también cuenta con una lista de [[PhysicComponent]]s obtenidos a través del patrón **listener**. El rigidbody cuenta con cuatro métodos a través de los que llama a los 4 tipos distintos de eventos de colisión que tienen este tipo de componentes, recorriendo la lista entera.

## Buffer de escala

La clase **Shape** de box2D nos suponía un problema y es que **no es posible eliminar, crear o modificar shapes mientras se está gestionando la simulación física**. Eso implica que cualquier cambio de escala que quisieramos hacer (Un cambio de escala implica eliminar la shape asociada a un cuerpo y rehacerla más grande) durante la comprobación de las colisiones, es decir, utilizando los [[Eventos al colisionar]], se cargaba el juego.

La solución que encontramos es que el cambio de escala se guardara en un buffer del rigidbody. La simulación sigue normalmente y al principio de la comprobación de la lógica se comprueba si el buffer tiene información nueva, y en caso de tenerla se rehace el shape, ahora sin problemas con la simulación.

## Tipos de RigidBody

Box2D usa distintos tipos de shape en función de la forma de la shape, es decir, crear una shape cuadrada y otra circular requerían métodos y un tipo de gestión distintos, tanto a la hora de crearlos como de cambiarle la escala (recordemos que un cambio de escala supone la destrucción y reemplazamiento de una shape). Por esta razón, y para facilitar su diferenciación y gestión, hemos hecho 5 tipos diferentes de rigidbody con un constructor y un cambio de escala distinto en función de su forma. Los tipos son

- BoxRBComponent (Caja, cuadrado)
- CapsuleRBComponent (Cápsula)
- CircleRBComponent (Círculo)
- PolygonRBComponent (Polígonos de cualquier tipo y forma)
- RectangleRBComponent (Rectángulo)