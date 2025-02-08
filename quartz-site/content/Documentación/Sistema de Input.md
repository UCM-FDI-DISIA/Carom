Consiste principalmente en un script que centraliza todo el input que recibe **tanto de teclado, ratón, y mando**, y lo traduce a acciones generales. Estas acciones globales se van a mandar por eventos, y los sistemas que estén suscritos a esos eventos en específico van a actuar en consecuencia.

Un ejemplo con nodos: 

![[Pasted image 20250208183842.png]]
En el que ***Convertidor de Input*** es el sistema que se encarga de recorrer todos los eventos de SDL de input y chequear si alguno ha sido accionado. Si ocurre esto, se llama a una clase Evento propio con **Patrón Observer**, que se encarga de llamar a todas las acciones de la Entidad que estén suscritas al evento, y que hagan lo que tengan que hacer.

Para ello se necesita la clase Evento, que como ya se ha dicho sigue el Patrón Observer. 

# Por qué esto es útil

Básicamente para facilitar la cantidad de controladores que se aceptan, ya que se usa un intermediario que traduce acciones individuales de input de distintos dispositivos a Eventos que son interpretados por el juego.