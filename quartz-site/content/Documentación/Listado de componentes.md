
## Resumen

En esta página se listan todos los componentes y una pequeña descripción de para que se usan, si los componentes pertenecen a un conjunto específico de funcionalidades se puede agrupar por clases padre (por ejemplo Render Component)

---
### Render Components
#### RenderSpritesheetComponent

Sirve para renderizar una imagen en base a unas filas y columnas asignadas en la creación del componente. Tiene funcionalidad para cambiar que casilla se renderiza

---

### Logic Component

#### AnimatorComponent

En base a la información en el struct auxiliar *Animation* va cambiando la casilla renderizada por el [[#RenderSpritesheetComponent]] de su entidad. Se puede acceder a las animaciones mediante sdlutils, las animaciones se escriben en resources. Todas las animaciones tienen un tipo que condiciona que ocurre cuando la termina (ver implementación de animation end).

---
### Estados de CaromScene

---

### PhysicsUtils

En este scripts hay métodos estáticos que hacen una conversión entre píxeles en pantalla y unidades físicas de box2d. Como siempre usamos unidades físicas en vez de píxeles, se usa en la mayor parte de los scripts que se necesita instanciar un objeto en la escena.

### InputHandler

Singleton. Es un wrapper en el cual se reciben los eventos de SDL, y que el resto de componentes pueden usar si quieren detectar que se ha pulsado una tecla, se ha dado click, o para saber la posición del ratón.


---
## Detección de golpes


#### WhiteBallScorerComponent

Componente de la bola blanca. Detecta si ha chocado con paredes o con bolas de color, y hace en consecuencia lo escrito en [[Sistema de puntuación]]. 

#### ColorBallScorerComponent

Componente de bolas distintas a la bola blanca. Detecta únicamente si ha chocado con bolas de color, y si ocurre, notifican al ColorHitManager del choque con la bola correspondiente.

#### ColorHitManager

Se encuentra en la escena. Recibe los choques de las bolas de color y filtra los choques iguales (ya que le van a notificar las dos bolas por separado de los mismos choques). Después, con cada choque, añade los puntos escritos en [[Sistema de puntuación]].

---
### CameraComponent

Componente que tiene la entidad de **Cámara**. Todas las entidades se renderizan en base a la cámara, es decir, dependiendo de la posición de la cámara las entidades se van a renderizan en una posición u otra de la pantalla.

### TweenComponent

Componente que habilita poder hacer interpolaciones lineales en atributos de la Entidad. Contiene métodos para poder interpolar su posición, su escala, y su rotación. También contiene uno para cambiar floats por referencia. 
Se usa principalmente para añadir animaciones a las entidades.

### FollowComponent

Componente que ***copia*** ciertas propiedades de otra entidad, como la posición, rotación y escala. 

### ShadowComponent

Componente que actúa como un contenedor de referencias a entidades. Se usa como un wrapper, ya que en el método de addShadow se crea una entidad, se le añade TransformComponent, RenderTextureComponent, y FollowComponent, y se añade al vector de ShadowComponent. Se trata de una abstracción.

