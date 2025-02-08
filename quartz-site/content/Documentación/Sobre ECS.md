## Managers (Gestores)

Lógica que ocurre de forma global (o no, pero normalmente si) fuera del sistema ECS

---

## Sistema ECS

Llamamos sistema ECS al contexto sobre el que existen entidades, componentes y sistemas (si, es redundante). Tenemos que determinar que existe este concepto porque tenemos cosas en nuestro juego fuera de esta arquitectura (AKA managers)

### Entidad

Una entidad es simple y llanamente un contenedor de componentes. Suelen existir dentro de escenas y estar agrupados. También deberían tener métodos para instanciarlos de forma prefabricada (AKA JSONs), para agregar y eliminar componentes y para activar y desactivar la entidad (es decir hacerla "inexistente" en la ejecución)

#### Grupos

Los grupos son como su nombre indica agrupaciones de componentes que sirven para manejar componentes principales de forma general en vez de uno a uno.

Si por ejemplo tengo un sistema para mover todas las bolas porque las bolas se mueven de forma X pues mi sistema actuaría (e iteraría) sobre el grupo de bolas, en vez de actuar sobre todos los objetos y comprobar antes si son o no una bola para darle, esto es una alternativa a tener la funcionalidad en el componente, como en Unity, que nos evita tener duplicidad de métodos virtuales que son los que ocupan memoria y con eso hacemos una compilación y uso de memoria mas ligera.

---

### Componente

Los componentes son datos, sin mas, el mejor símil es el de un struct plano.

Sería conveniente ver mas a fondo el papel de los componentes en ECS para ver si es necesario crear un struct padre abstracto Component o mas funcionalidades generales que nos puedan solucionar la vida

---

### Sistema

La lógica del juego está aquí, se acoplan los distintos componentes a los sistemas y con la info de estos componentes los sistemas ejecutan la lógica del juego y la actualizan en los componetes

---

## Conclusión

Podemos ver el conjunto total de los **componentes** como el **estado actual del juego**, los **sistemas** como la **lógica** para manipular a ese estado y las **entidades** (y grupos) como el mecanismo para **agrupar y acceder** a dicho estado.