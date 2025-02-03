## Nombrado

**Requisitos:**

- Solo un verbo en infinitivo
- La frase no puede ser tan larga que *github projects* no pueda poner la previsualización entera

## Descripciones

**Incluye:**

- Descripción de la tarea
- Definition of done

La descripción de la tarea debe ser lo más extensa y detallada posible, de forma que quede claro cuál debe ser el resultado final.

## Definition of done

La definition of done debe ser una pequeña descripción (más pequeña que la descripción de la tarea) en la que se deja claro **al programador** qué es lo que tiene que hacer el código **a nivel de implementación**.

Ejemplo:

	"Al darle al botón de salto (barra espaciadora) se le aplicará a Mario una velocidad vertical positiva que lo impulsará durante el frame en el que se pulse el botón, ejecutando el salto"
	
	"Al darle al botón de salto (barra espaciadora) Mario va hacia arriba"
	
	En el primer caso (bien hecho) se específica al programador que es el body el que se mueve cuando se le aplica una fuerza al pulsar espacio. En el segundo caso (mal hecho) se especifica la mecánica sin explicar cómo está hecha, dejando la tarea a libre interpretación del programador, que puede mocer a Mario por física, o cambiando su posición a pelo o de una tercera y más siniestra forma en la que no quiero pensar demasiado. ES NECESARIO CONCRETAR LOS DEFINITION OF DONE PARA QUE NADA SE ROMPA EN EL JUEGO.

## Organización

- **Epics**: Un **Epic** es un grupo de **tasks**. En total conforman un cambio considerable dentro del juego. Debe ser un cambio que afecta al juego a gran escala para considerarse un **Epic** (mecánicas que cambien el flujo de juego, nuevos pisos...).
- **Task**: un task es una tarea atómica que contribuye a la implementación de un elemento del juego (es decir, un **Epic**)

Los **Epics** Tendrán su propia columna en el *project* y se irán marcando como completados cuando se implementen todas sus **tasks**.

## Tags

Tags que debe tener una task:

- **Categoría de Issue**: Epic, Story, Task
- **Tipo de tarea**: bug, feature
- **Categoría**: diseño, implementación, arte, gestión, comunicación interna, comunicación
- **Sprint**: número de sprint
- **Milestone**: número de hito
- **Coste estimado/real**: coste decidido en la reunión del domingo frente al que finalmente ha sido
- **Prioridad**: prioridad decidida en la reunión del domingo
- **Status**: Epics, Icebox, TODO, In progress, Testing, Done
## Tamaño

Potencias de 2 siendo dicho número la cantidad de horas (aproximadamente) que se tarda en realizar la tarea.

## Prioridad

Critic > High > Medium > Low

Siendo **Critic** un problema que, si no se soluciona, hace el juego injugable y **Low** una tarea con el objetivo de mejorar el juego pero que no es absolutamente necesaria.

## Metodología de pesado

10 minutos de las reuniones de los domingos ([[Metodología de trabajo]]) se dedicarán a pesar las tareas del sprint. 
El método de pesado consiste en que cada persona **presente** en la reunión diga qué **tamaño y prioridad** cree que debería tener cada tarea. Se escoge el tamaño y prioridad con más votos. En caso de empate se escoge el más alto.

## Asignación de tareas

**Normas de asignación de tareas:**

- **Iniciativa**: las tareas se cogen por iniciativa propia. Si alguien ve una tarea sin asignar y la quiere hacer, se la asigna en el *projects*. Al acabar la tarea, se coge una nueva.
- **Solo 1 tarea**: cada persona solo puede estar haciendo **1 única tarea** a la vez. Nadie puede asignarse una tarea nueva sin haber acabado la anterior.
- **Problemas**: Si apareciese alguna dificultad para terminar una tarea se devuelve a la columna de TODO, se le añade en la descripción: En qué rama estabas trabajando, qué cambios has hecho y por qué no has podido terminarla, y se avisa por el discord de que se abandona la tarea para que un compañero pueda terminarla.