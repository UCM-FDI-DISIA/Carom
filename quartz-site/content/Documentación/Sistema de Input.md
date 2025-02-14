Consiste principalmente en un script que centraliza todo el input que recibe **tanto de teclado, ratón, y mando**, y lo traduce parámetros genéricos que el juego puede usar para hacer acciones concretas.
# Por qué esto es útil

Básicamente para facilitar la cantidad de controladores que se aceptan, ya que se usa un intermediario que traduce acciones individuales de input de distintos dispositivos parámetros que pueden obtenerse de forma remota, para saber si se ha presionado una acción.

# Input resumido según GDD

| Acción                      | Input teclado y ratón                              | Mando (futura issue) | Contexto                  |
| --------------------------- | -------------------------------------------------- | -------------------- | ------------------------- |
| Reordenar bolas             | Clic izquierdo y arrastrar a una casilla           |                      | Inventario                |
| Destruir bolas              | Clic derecho sobre la bola                         |                      | Inventario                |
| Consultar bolas             | Pasar el ratón por encima de la bola               |                      | Inventario y partida      |
| Lanzar bola                 | Clic izquierdo sobre la bola, arrastrar y soltar   |                      | Partida                   |
| Abrir inventario            | Clic izquierdo sobre botón de inventario o tecla e |                      | Partida (UI)              |
| Abrir menú de pausa         | Clic izquierdo sobre botón de pausa o tecla esc    |                      | Inventario y partida (UI) |
| Aceptar botón / avanzar     | Clic izquierdo sobre él                            |                      | UI                        |
| Cancelar botón / retroceder | Presionar tecla esc                                |                      | UI                        |


# InputHandler TPV2
El InputHandler de Samir de TPV2 nos puede servir para esto.
Uso (ejercicio 1 TPV2):

```
// FighterCtrl.h:

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

- Al hacer clic sobre UI u otro objeto clicable. Habría que especificar si es con **clic izquierdo** o **derecho**
```
[...]

// InputHandler.h

// Si el ratón se clica o deja de clicarse.
inline bool mouseButtonEvent() {
	return _isMouseButtonUpEvent || _isMouseButtonDownEvent;
}

// Si el ratón deja de clicarse
inline bool mouseButtonUpEvent() {
	return _isMouseButtonUpEvent;
}

// Si el ratón se clica.
inline bool mouseButtonDownEvent() {
	return _isMouseButtonDownEvent;
}

[...]

// Aplicado:
#include "../sdlutils/InputHandler.h"

void Cosa::handleInput(Container* o){
	InputHandler& ihdlr = ih();

	if (ihdlr.mouseButtonDownEvent()) {
		// Al presionar el ratón.
		if(ihdlr.isKeyDown(SDL_BUTTON_RIGHT)){
			// Clic derecho.
		}
		else if(ihdlr.isKeyDown(SDL_BUTTON_LEFT)){
			// Clic izquierdo.
		}
	}
}
```

- **Arrastrar el ratón** mientras haces clic, para la mecánica de darle a la bola con el palo (valdría también en caso de querer meterle un cursor a nuestro juego, ya que captura la posición del ratón).
```
[...]

// InputHandler.h

// Si el ratón se mueve.
inline bool mouseMotionEvent() {
	return _isMouseMotionEvent;
}

// Si el ratón se clica.
inline bool mouseButtonDownEvent() {
	return _isMouseButtonDownEvent;
}

// Posición del ratón.
inline const std::pair<Sint32, Sint32>& getMousePos() {
	return _mousePos;
}

[...]

// Aplicado:
#include "../sdlutils/InputHandler.h"

void Cosa::handleInput(Container* o){
	InputHandler& ihdlr = ih();
	if (ihdlr.mouseMotionEvent() && mouseButtonDownEvent()) {
		// Si se mueve y se clica a la vez cuenta como arrastrando (?).
	}
}
```

- Teclas para habilidades, cosas del inventario (esto es en caso de necesitar otra tecla).
```
[...]

// InputHandler.h

// Se ha presionado tecla.
inline bool keyDownEvent() {
	return _isKeyDownEvent;
}

// Se ha soltado tecla.
inline bool keyUpEvent() {
	return _isKeyUpEvent;
}

// Qué tecla se ha presionado.
inline bool isKeyDown(SDL_Keycode key) {
	return isKeyDown(SDL_GetScancodeFromKey(key));
}

// Qué tecla se ha soltado.
inline bool isKeyUp(SDL_Keycode key) {
	return isKeyUp(SDL_GetScancodeFromKey(key));
}

[...]

// Aplicado:
#include "../sdlutils/InputHandler.h"

void Cosa::handleInput(Container* o){
	InputHandler& ihdlr = ih();
	if (ihdlr.isKeyDown(SDLK_ESCAPE)) {
		// Se presiona la tecla Esc para salir o lo que se asigne.
	}
}
```

- Todo lo referente a los [joysticks](https://docviewer.xdocs.net/view_v2.php). Capítulo 4.

