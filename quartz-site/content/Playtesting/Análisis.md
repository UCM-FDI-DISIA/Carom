
# Muestra

**TODO**

### Enlace a la plantilla de análisis:
[Playtesting Carom - Hojas de cálculo de Google](https://docs.google.com/spreadsheets/d/1kO3TXSgIrMQQ1YXdM0qgFCgBMQKkF8bjtNB6bne5XQU/edit?gid=1545766014#gid=1545766014)

# Resultados por apartados

  
## Menú principal:

Todos los jugadores, independientemente de su edad o la frecuencia con la que jueguen a videojuegos, parecen entender sin problemas cómo funciona el menú principal.

## Mesa de pool:

En la mesa de pool los datos demuestran que los jugadores no se paran a leer lo que hacen las recompensas demasiado. Esto a raíz de otro dato contemplado en el testing, y es que a los jugadores le confunden la duplicidad de descripciones o entrar a una ronda clicando tanto la bola como el agujero. Además, los datos demuestran que la mayoría de jugadores no entienden que jugar una ronda implica una recompensa y no jugarlo te da la bola asociada a dicha ronda. Lo que al final provoca que se juegue al azar y se pierda parte de la esencia del juego. La gente que lo ha entendido, sin embargo, si que procuraba hacer estrategias con las recompensas que obtenían.

## Primera ronda de Carom:

En general, los jugadores parecen entender el funcionamiento de una ronda de juego, siendo lo más problemático el sistema de puntuación, que se ha manifestado que es confuso. En cuanto a la tasa de victorias, es superior al 50% lo que significa que la mayoría de jugadores pueden ganar una partida sin problemas. Hay constancia de gente sin experiencia que se lo ha pasado sin problemas.

## Primera recompensa:

De forma general, la gente con más experiencia en videojuegos parece entender que la recompensa se le da por haber pasado la ronda, mientras que gente con menos experiencia parece no entenderlo a la primera. Una vez obtenida, la mayoría de jugadores hacen uso de ella conscientemente (y mucho de los que no ha sido a raíz de un fallo en las primeras versiones de la build de pruebas.

## Misceláneo:

Todos los jugadores ganan al menos una partida y todos pasan al siguiente piso lo que denota una buena dificultad pues tanto la gente con experiencia como la que no es capaz de completar al menos el primer piso. Con respecto a las recompensas la mayoría no prioriza ningún tipo de recompensa en concreto y cuando se consigue algún efecto de palo o recompensa algo más de la mitad de los jugadores lo incorporan a su estrategia mientras que el resto o no lo entienden o siguen jugando normalmente.

## Ronda con gimmick:

Los resultados para las gimmicks son positivos. La mayoría de jugadores, con experiencia o no, entienden los efectos de los gimmicks sobre el juego con un par de tiros y juegan teniéndolo en cuenta.

## Ronda de boss:

Todos los jugadores han entendido las mecánicas de ambos jefes de piso, algunos no han cambiado de estrategia sino que han seguido jugando como normalmente pero todos han ganado la escena de boss.

## Inventario:

Algo menos de la mitad de los jugadores abren el inventario, mientras que el resto o bien no saben como hacerlo o no ven la necesidad de hacerlo. La gran mayoría lee la descripción de los objetos lo que significa que le dan importancia a estos, sin embargo casi nadie entiende que se puede deshacer de sus bolas y el la mayoría de los casos eliminan alguna por accidente.


## Conclusiones por apartados

### Menú principal:

El menú principal está bien hecho y no requiere modificaciones.

### Mesa de pool:

Las confusiones surgen por las opciones y la falta de explicación de sus consecuencias, por lo que, para evitar este tipo de problemas, hemos decidido que el jugador no pueda entrar a una ronda clicando en su bola (obligándolo a leer la recompensa que obtiene si elige dicha ronda) y se ha decidido cambiar el tutorial para que sea más explicativo en este apartado.

### Primera ronda de Carom:

Los carteles, sin nada que explique su funcionamiento, son confusos. Para clarificar el significado de los carteles que aparecen encima de la mesa de carambola con las puntuaciones, se ha decidido poner un texto de “Puntuación” y “Puntuación a batir” en la base de dichos carteles.

### Primera recompensa:

En ocasiones, no se entiende bien por qué el jugador recibe una recompensa. Para aclarar la razón de su obtención hemos propuesto poner un texto en la escena de recompensa que diga “recompensa por victoria”.

### Misceláneo:

Aunque muchos jugadores crean estrategias, no todos lo hacen. Se ha supuesto que esto surge a raíz de no entender cómo funcionan las recompensas y su obtención. Se espera que los datos sean diferentes con los cambios ya hechos.

### Ronda con gimmick:

Las gimmicks se entienden sin problema y no necesitan ser modificadas.

### Ronda de boss:

Los bosses no suponen un cambio tan sustancial como para hacer un cambio en la estrategia de juego. Se propone aumentar el castigo que se le impone al jugador en pisos como el cowboy.

### Inventario:

No está suficientemente claro como se abre el inventario ni como se eliminan bolas. Se propone alguna indicación en la UI para mostrar el botón con el que se abre el inventario. Así mismo también convendría indicar en la escena de recompensa del boss con una leyenda que las bolas que se marcan en rojo se van a eliminar y las verdes se van a incorporar.