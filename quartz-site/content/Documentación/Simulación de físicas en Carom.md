En nuestro juego hemos decidido que las escenas que necesiten físicas (Por el momento, únicamente la escena de juego) tendran un ``b2WorldId`` y un ``b2WorldDef``. 

En cada iteración del bucle de juego ***Antes de la lógica*** se llamará a la simulación de mundo tal y como se explica en [[Fundamentos box2D]]. Estando creadas de antes, por supuesto, todas las entidades que vayan a participar en la simulación dicha iteración.

## Entidades

Las entidades se añadirán a la simulación física de la escena añadiéndoles un [[RigidBody]] en lugar de un **TransformComponent** (Adecuado para entidades ajenas a la física).

## Eventos de físicas

Los [[Eventos al colisionar]] se gestionarán inmediatamente después de la simulación física, antes de ejecutar la lógica del resto de componentes. Recorre todas las colisiones y sensores ejecutando todos los métodos de gestión de colisiones de los [[RigidBody]] que estén involucrados en dichas interacciones.

