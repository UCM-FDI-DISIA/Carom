**Box2D** tiene una funcionalidad a través de la que te permite obtener un array con todas las colisiones que ha habido en un loop de la simulación (explicado en [[Fundamentos box2D]]) utilizando

```cpp
// obtiene información de colisiones
b2ContactEvents contactEvents = b2World_GetContactEvents(myWorldId)

// obtiene información de sensores
b2SensorEvents sensorEvents = b2World_GetSensorEvents(myWorldId)

// con un bucle for podemos recorrer todos los inicios de colisiones 
// del loop haciendo que se ejecute código por cada una
for(int i = 0; i < contactEvents.beginCount; ++i){
	b2ContactBeginTouchEvent* beginEvt = contactEvents.beginEvents + i;
	// funcionalidad que queramos
}

// Lo mismo para cuando dejan de colisionar
for(int i = 0; i < contactEvents.endCount; ++i){
	b2ContactEndTouchEvent* endEvt = contactEvents.endEvents + i;
	// funcionalidad que queramos
}

// podemos hacer lo mismo para sensores
```