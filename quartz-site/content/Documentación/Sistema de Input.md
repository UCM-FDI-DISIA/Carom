Consiste principalmente en un script que centraliza el input que recibe **tanto de teclado, ratón, y mando**, y lo traduce parámetros genéricos que el juego puede usar para hacer acciones concretas.
# Por qué esto es útil

Básicamente para facilitar la cantidad de controladores que se aceptan, ya que se usa un intermediario que traduce acciones individuales de input de distintos dispositivos parámetros que pueden obtenerse de forma remota, para saber si se ha presionado una acción.
# Input de la bola blanca
En primer lugar, tenemos una bola, con un **radio**, que es un área sobre la que se puede clicar para que aparezca el palo (*viñetas 1, 2, 3*). El palo permanece en la posición clicada a menos que se **suelte**, siempre y cuando no se pase del **radio hasta donde se está permitido el arrastre** del clic (*viñetas 4, 5 y dibujo con fondo azul*). Al soltar el ratón dentro del área permitida, se le aplicará una fuerza a la bola correspondiente a la magnitud con la que se ha arrastrado el palo: *a **más** se haya arrastrado, con **más** fuerza se dispara la bola blanca*, respetando además la el vector de dónde viene el palo, **disparándose en dicha dirección** (*viñeta 6 y dibujo con fondo azul*).
Todo esto se puede encontrar en el componente ==`StickInputComponent`==.
![[Pasted image 20250226172259.png]]
![[Pasted image 20250226172249.png]]
# Input del inventario y de la interfaz
El input del inventario puede gestionarse con los métodos incluidos en ==`InputHandler`== de sdlutils modificado.

| Acción                      | Input teclado y ratón                              | Mando (futura issue) | Contexto                  |
| --------------------------- | -------------------------------------------------- | -------------------- | ------------------------- |
| Reordenar bolas             | Clic izquierdo y arrastrar a una casilla           |                      | Inventario                |
| Destruir bolas              | Clic derecho sobre la bola                         |                      | Inventario                |
| Consultar bolas             | Pasar el ratón por encima de la bola               |                      | Inventario y partida      |
| Abrir inventario            | Clic izquierdo sobre botón de inventario o tecla e |                      | Partida (UI)              |
| Abrir menú de pausa         | Clic izquierdo sobre botón de pausa o tecla esc    |                      | Inventario y partida (UI) |
| Aceptar botón / avanzar     | Clic izquierdo sobre él                            |                      | UI                        |
| Cancelar botón / retroceder | Presionar tecla esc                                |                      | UI                        |
Todo lo referente a los [joysticks](https://thuvienso.dau.edu.vn:88/bitstream/DHKTDN/7035/1/6353.SDL%20game%20development.pdf). Capítulo 4.

