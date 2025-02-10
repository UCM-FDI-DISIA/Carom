Consiste principalmente en un script que centraliza todo el input que recibe **tanto de teclado, ratón, y mando**, y lo traduce a acciones generales. Estas acciones globales se van a mandar por eventos, y los sistemas que estén suscritos a esos eventos en específico van a actuar en consecuencia.

Un ejemplo con nodos: 

![[Pasted image 20250208183842.png]]
En el que ***Convertidor de Input*** es el sistema que se encarga de recorrer todos los eventos de SDL de input y chequear si alguno ha sido accionado. Si ocurre esto, se llama a una clase Evento propio con **Patrón Observer**, que se encarga de llamar a todas las acciones de la Entidad que estén suscritas al evento, y que hagan lo que tengan que hacer.

Para ello se necesita la clase Evento, que como ya se ha dicho sigue el Patrón Observer. 

# Por qué esto es útil

Básicamente para facilitar la cantidad de controladores que se aceptan, ya que se usa un intermediario que traduce acciones individuales de input de distintos dispositivos a Eventos que son interpretados por el juego.

# Traducción de eventos
El InputHandler de Samir de TPV2 nos puede servir para esto.
Uso (ejercicio 1 TPV2):

```
#include "../sdlutils/InputHandler.h"

void FighterCtrl::handleInput(Container* o){
	InputHandler& ihdlr = ih();

	float thrust = 0.2f;
	float speedLimit = 3.0f;

	if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)) {
		o->setRotation(o->getRotation() - _rot);
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) {
		o->setRotation(o->getRotation() + _rot);
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_UP)) {
		Vector2D newVel = o->getVel() + Vector2D(0, -1).rotate(o->getRotation()) * thrust;
		if (newVel.magnitude() > speedLimit) {
			newVel = newVel.normalize() * speedLimit;
		}
		o->setVel(newVel);
	}
}
```

La traducción de los eventos según el diseño del juego podría ser de esta forma:
- Al hacer clic sobre UI u otro objeto clicable (ya sea con clic izquierdo o derecho).

- Arrastrar el ratón mientras haces clic, para la mecánica de darle a la bola con el palo (valdría también en caso de querer meterle un cursor a nuestro juego, ya que captura la posición del ratón).
- Teclas para habilidades, cosas del inventario (esto es en caso de necesitar otra tecla).