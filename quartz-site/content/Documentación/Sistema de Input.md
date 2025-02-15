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
Todo lo referente a los [joysticks](https://thuvienso.dau.edu.vn:88/bitstream/DHKTDN/7035/1/6353.SDL%20game%20development.pdf). Capítulo 4.

