En una ronda, la puntuación se obtiene de dos formas: *Efectos* y *colisiones.*

**Efectos**
Ciertas habilidades de los palos o [[Efectos]] de las bolas afectarán de forma directa a la puntuación (sumando o multiplicando el valor acumulado).

**Colisiones**
Existen tres tipos de colisiones entre bolas que añaden puntuación en una ronda:
- *Golpe:* La bola blanca golpea a una de color ($G$), esto otorga *1 punto* cada vez que sucede. 
- *Combo:* Una bola de color golpea a otra bola de color ($C$), esto *otorga 2 puntos* cada vez que sucede.
- ***Carambola:*** Una bola de color que ha pertenecido a un *Combo* y no a un *Golpe* colisiona con la blanca ($C \cap \overline G$), esto *otorga 4 puntos* cada vez que sucede.

La notación booleana debe verse como una referencia para programar la lógica de los golpes descritos.

>[!Respecto al Billar Francés]
>Los que conozcan el juego original sabrán que la puntuación no funciona de esta forma, la carambola final (la de la modalidad) es la que da los puntos, en nuestro caso hemos querido añadir más formas menos complicadas de puntuar sin perder turnos, básicamente porque si no el juego se convierte en algo que es tan complicado de base que no podríamos añadir los [[Efectos]] ni otros componentes pensados