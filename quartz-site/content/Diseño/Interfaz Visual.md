Se creará una UI con una forma *mínima* y *diegética*. Esto quiere decir que habrá pocos elementos en pantalla aparte de la zona de juego y, además, que los elementos estarán integrados como si fueran parte del mundo del juego.

## Durante el juego
Se va a buscar una disposición parecida a la siguiente imagen:

![[interfaz.png]]

Los elementos de arriba de la pantalla son **los puntos del jugador y los puntos a conseguir en la ronda**. Se encuentran separados por un "/". Los puntos del jugador se van a ir actualizando conforme se puntúe en la partida, y se podrán añadir elementos externos como multiplicación de puntuaje para mostrar efectos de las bolas.

**Arriba a la derecha** se encontrarán las jugadas que te quedan en la partida para alcanzar la puntuación deseada.

En la parte de la izquierda se muestran "botones" de distintas opciones del juego. Si se pulsa algún botón de estos, se muestra un desplegable con el contenido de cada menú correspondiente.

Artísticamente, se va a representar como unos cajones que hay al lado del jugador, siendo cada botón un nivel del cajón que guarda distintas cosas.

A continuación se muestran ejemplos de cada menú desplegable:
### Menú de inventario
![[interfaz-inventario.png]]
El jugador almacena un maletín de juego, donde están representadas las bolas con las que cuenta y el palo con el que juega.

### Menú de configuración
![[interfaz-opciones.png]]
Se podrá ir a la configuración del juego o salir al menú principal, además de todo tipo de funcionalidades extra que se necesiten añadir.