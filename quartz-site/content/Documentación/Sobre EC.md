

>[!note] Sobre el nombrado en el código
>En el código tenemos definido el namespace ECS en vez de EC, esto se debe a que en un inicio íbamos a usar ECS, actualmente está ahí como residuo, se cambiará en el futuro.


---
## Managers

Lógica que ocurre de forma global (o no, pero normalmente si) fuera del sistema EC

---

### Entidad

Una entidad es un contenedor de componentes. Existen dentro de escenas y pueden estar agrupados. Tienen métodos para agregar y eliminar componentes y para activar y desactivar la entidad (ignorarla en el gameloop).

Algunas entidades pueden generadas mediante factories orientados a datos en JSONs.

#### Grupos

Los grupos son agrupaciones de componentes que sirven para acceder a componentes

Si por ejemplo tengo un sistema para mover todas las bolas porque las bolas se mueven de forma X pues mi sistema actuaría (e iteraría) sobre el grupo de bolas, en vez de actuar sobre todos los objetos y comprobar antes si son o no una bola para darle, esto es una alternativa a tener la funcionalidad en el componente, como en Unity, que nos evita tener duplicidad de métodos virtuales que son los que ocupan memoria y con eso hacemos una compilación y uso de memoria mas ligera.

---

### Componente



---

### Sistema

La lógica del juego está aquí, se acoplan los distintos componentes a los sistemas y con la info de estos componentes los sistemas ejecutan la lógica del juego y la actualizan en los componetes

---

## Conclusión

Podemos ver el conjunto total de los **componentes** como el **estado actual del juego**, los **sistemas** como la **lógica** para manipular a ese estado y las **entidades** (y grupos) como el mecanismo para **agrupar y acceder** a dicho estado.