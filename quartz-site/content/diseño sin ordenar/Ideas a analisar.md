## Bolas amigas

| **Nombre del Efecto** | **Ventaja**                                                                                                                                                                                     | **Desventaja**                                                                                       |
| --------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------- |
| *Numérica*            | Numerada *X* de *\[1, Nbolas]*. Añade *X* al combo                                                                                                                                              | Puntuación _flat_                                                                                    |
| *Patrón*              | Posee un patrón de textura. Añade *X* _multiplier_ al combo                                                                                                                                     | No añade puntos, sólo _multiplier_                                                                   |
| *Hinchable*           | Aumenta de tamaño *Y%* a cada choque hasta *X* diámetro                                                                                                                                         | Su masa también aumenta dejándola más lenta                                                          |
| *Simpatizante*        | Sigue la bola más próxima trás un choque                                                                                                                                                        | La bola más próxima puede que no sea la mejor para un combo y que la blanca esté entre la dos bolas. |
| *Fisión*              | Divide su diámetro en *Y%* a cada choque hasta *X* diámetro                                                                                                                                     | Incompatible con *Hinchable*. Disminuye su masa.                                                     |
| *Inviolable*          | No sufre cualquier efecto                                                                                                                                                                       | Incluye efetos buenos de otras bolas                                                                 |
| *Aguejera*            | Posee un campo de atracción de radio *X*                                                                                                                                                        | El desvío de la bola blanca puede que no sea deseable                                                |
| *Persistente*         | Sigue moviéndose durante x segundos                                                                                                                                                             |                                                                                                      |
| *Estática*            | Las bolas que se colisionan con ella ganan *Y%* velocidad                                                                                                                                       | Esta bola no se mueve                                                                                |
| *Invisible*           | Le da *X* _multiplier_ grande a la bola que le golpea                                                                                                                                           | No se ve                                                                                             |
| *Falsa Blanca*        | Vale como una blanca para hacer carambolas                                                                                                                                                      | No tiene _multipliers_                                                                               |
| *Clone*               | Copia otra bola del kit aleatoriamente                                                                                                                                                          | Aleatorio                                                                                            |
| *Copia*               | Copia la primera bola que colisiona en una ronda hasta el fin                                                                                                                                   | Si no hay buenas bolas de efecto no tiene mucha ventaja                                              |
| *Endemoniada*         | No respeta las leyes de la física. Sigue una dirección que le da la gana con una velocidad que la da la gana. Tiene un buen bonus multiplier por ser mala.                                      | Es mala                                                                                              |
| *Etérea*              | No se colisiona con los bordes, aunque lo cuente para puntuación. Sale de un lado e aparece en el otro como _Pacman_                                                                            | Dificultad de jugar                                                                                  |
| *Mímica*              | Se mueve al mismo tiempo que la bola blanca. Es como si fuera la bola blanca. Va en la misma dirección y velocidade que la blanca                                                               | Dificultad de jugar                                                                                  |
| *N*                   | Es de cualquier número (par, impar, 0 < n < Nbolas)                                                                                                                                             | Comba com bolas numeradas solamente                                                                  |
| *Arcoíris*            | Es de cualquier color (menos blanca)                                                                                                                                                            | Comba com bolas coloridas solamente                                                                  |
| *Bomba*               | Cuando colisiona explota en *X* bolas                                                                                                                                                           | Introduce caos                                                                                       |
| *Listrada*            | Es una bola *Patrón*. Su choque con otra *Listrada* multiplica el _multiplier_ actual en *X*                                                                                                    | Necesita dos slots para dos bolas iguales                                                            |
| *Agotada*             | Transfiere todo su momento trás un choque con otra bola                                                                                                                                         | No contribuye directamente a la puntuación                                                           |
| *Delatora*            | Antes de una tirada, la bola encende si va a colisionar en algún momento en esta configuración de tiro (difícil de impementar)                                                                  | No contribuye directamente a la puntuación                                                           |
| *Nuclear*             | Explota al colisionar liberando *X* bolas que desaparecen al final de la jugada                                                                                                                 | Se destruye                                                                                          |
| *Schrödinger*         | Al colisionar se divide en dos iguales. Al final de la jugada una de ellas desaparece                                                                                                           |                                                                                                      |
| *Tanque*              | Guarda la puntuación actual en el momento de un choque (no la quita). La próxima jugada, al colisionar, añade esa puntuación guardada a la actual y actualiza su valor.                         |                                                                                                      |
| *Perseverante*        | No sufre desvío de dirección al colisionar con otras bolas, sólo bordes                                                                                                                         |                                                                                                      |
| *Fantasma*            | No produce la dinámica física del choque. Al "chocarse" con otras bolas, todas las otras dinámicas son iguales (efectos, puntuaciones etc), pero no hay interacción física salvo con los bordes |                                                                                                      |
>[!Sobre bolas numeradas y daltonismo]
>Numeradas: por la vista ser desde arriba, las numeradas tienen que tener una textura con el número repetido como patrón, vários 3 por exemplo, que se puede ver en cualquier angulación.
>Coloridas: daltonismo es un problema. Se puede pensar en patrones y colores: las bolas amarillas siempre tiene el mismo patrón, por ejemplo varios x en la textura. Las personas daltónicas siguen los patrones y el resto color o patrón. 



## Bolas enemigas
| **Nombre del Efecto** | **Efecto**                                                                                              |
| --------------------- | ------------------------------------------------------------------------------------------------------- |
| *NOmérica*            | Numerada *X* de *\[1, Nbolas]*. Quitas *X* al combo                                                     |
| *Borradora*           | Quita toda la puntuación hasta su choque en una jugada                                                  |
| *Multiplicadolor*     | Divide el _multiplier_ en *X*                                                                           |
| *Pegadora*            | Se pega a las bolas con las cuales colisiona. Sigue existiendo momento.                                 |
| *Bloqueante*          | Empieza posicionada justo delante de la blanca obstaculizando la tirada inicial                         |
| *Chupadora*           | La bola que se colisiona con ella pierde todo el momento. Es como la *Pegadora*, pero se quedan paradas |
| *Impostora*           | Se pasa, visualmente, por una bola del jugador                                                          |
| *Antibola*            | Se destruye junto a otra bola que se choca con ella. Esa bola puede que sea una enemiga también         |
>[!Presencia de las bolas enemigas]
>Las bolas enemigas pueden ser:
>- características de *Boss* específicos
>- mecánicas introducidas por *Boss*
>- mecánicas introducidas por piso
>



## Boss
| **Nombre del Efecto** | **Efecto**                                                                                            |
| --------------------- | ----------------------------------------------------------------------------------------------------- |
| *Cuanta Atrás*        | *X* tiempo para acabar la _run_                                                                       |
| *Mayor que*           | Sólo vale jugada con más de *X* puntos                                                                |
| *Blanco*              | Sólo vale jugada que la bola blanca se choca más de una vez                                           |
| *No _multipliers_*    | _Multipliers_ no valen                                                                                |
| *Aleatorio*           | Toda jugada empieza con las bolas en posiciones aleatorias                                            |
| *Bordes restrictos*   | En una misma juagada toda bola que se choca con el borde desaparece. La próxima tirada es *Aleatoria* |



## Palo

| **Nombre del Efecto** | **Efecto**                                                                                      |
| --------------------- | ----------------------------------------------------------------------------------------------- |
| *Predicción Nv.1*     | Línea de predicción hasta el primer choque                                                      |
| *Predicción Nv.2*     | Línea de predicción hasta el según choque                                                       |
| *Predicción Nv.3*     | Línea de predicción hasta el tercer choque                                                      |
| *Fuerza*              | Más velocidad a la bola blanca                                                                  |
| *Doble*               | Dispara dos bolas blancas en secuencia. La segunda bola blanca desaparece al final de la jugada |
| *Magnificar*          | Todas las bolas amigas aumentan *%Y* de diámetro                                                |
