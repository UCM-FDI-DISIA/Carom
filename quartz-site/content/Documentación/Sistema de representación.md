
Tanto el componente transform como el transform de la simulación física tienen la misma coordenada, esto es por razones de coherencia.

El origen del mundo corresponde al centro de la pantalla y la y es positiva hacia arriba y negativa hacia abajo.

Siempre que se manipulen coordenadas se hará respecto a ese sistema de representación.

A la hora de renderizar se utiliza la función estática PhysicsUtils::physicsConverter para convertir de puntos a mundo a puntos.