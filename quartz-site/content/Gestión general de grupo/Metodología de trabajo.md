
## Reunión de sprint

Al final de cada semana (Domingo - Lunes) se realizará una reunión breve (30-40 mins) en la que estarán presentes los miembros que puedan asistir. En dicha reunión se llevará a cabo:

- El cierre del sprint actual
- Los preparativos necesarios para el nuevo sprint

## Build bisemanal

Se intentará hacer una build compilada y ejecutable con lo que tengamos dos días antes de la finalización de cada semana par a partir de que empezemos el desarrollo del juego (Los viernes de las semanas 2, 4, 6, 8...).
Hacer esto será una tarea que hará un miembro del equipo como task. La persona que se asigne esta tarea se dedicará, a lo largo de esos dos días, a hacer que todo lo implementado encaje y se pueda buildear.
## Ramas

- **main**: para las releases y builds bisemanales.
- **development**: donde se desarrolla del juego entre sprints.
- **sub-ramas de development**: para implementación de tasks. Al acabar se hace un pull request a development.

## Roadmap

Se definirá el tiempo en el que se desarrollará cada tarea. Esto se hará con el objetivo de evitar problemas de dependencia entre tareas y definir tiempos.

## Bucle de trabajo individual

- Me asigno task por iniciativa ([[Convención de tasks]])
- Leo la descripción, valoro si puedo asumir la task y elijo si cogerla o no
- Pienso si conviene desarrollar/extender la descripción de la tarea y hacerlo si es así
- Se mueve la tarea a “In progress” y se informa por discord
- Se hace una rama para trabajar en la task (si no existe ya) y se empieza a implementar (**hacer git pull antes por favor**)
- Se modifica el definition of done si es necesario en la task
- Cuando terminas con la task, se mueve en el *projects* y se hace pull request
## Testing

Entre medias del bucle de trabajo o entre bucles, los miembros del equipo harán **testing**. Se hará un seguimiento de los testings exitosos que ha llevado a cabo cada miembro del equipo. La idea es que todos los miembros del equipo testeen de forma equitativa. Los testings se deben hacer siguiendo esta metodología:

- Miras en las Pull Request a ver si hay alguna
- Si la hay y tienes un número de testings parecido o por debajo al resto, se avisa y se coge
- Se testea siguiendo las indicaciones del definition of done
- Si la tarea se puede aprobar se avisa y se mueve a done
- Si la tarea no se puede aprobar se avisa, se escribe en la descripción por qué no se puede aprobar y se devuelve a TODO para que **lo arregle la persona responsable de la tarea**
- Si la tarea se ha aprobado selecciona el check de tu nombre en el draft superior de testing yapruebas la pull request mergeando a develop.

Nota: *Si no estás seguro de si lo que has testeado está bien, pide ayuda a un tercero.*

## Bucle de trabajo grupal

**Reunión de estatus**: Viernes a las 11. 15 minutos de hablar del estado del juego con los cambios relevantes de cada uno.

**Durante la semana**: Se trabaja intentando seguir las deadlines del roadmap.

**Cierre de sprint**: Domingo

**Apertura de nuevo sprint**: Domingo y lunes (en caso de que el domingo nos falte tiempo)