El inventario se compone de dos partes fundamentales: el JSON del inventario y el InventoryManager

## JSON

El JSON contiene la información del inventario, y se va a operar siempre sobre este para sacar y meter toda la información. Contiene:

* Soltura
* Carisma
* Poder
* Picardía
* Bolas con efectos 
* Palo con efecto
## InventoryManager

Singleton que opera con el JSON del inventario. 

>[!Importante]
>**Siempre** opera sobre inventory.json, que es el inventario de la partida. El resto de inventarios disponibles se van a copiar a inventory.json para asi retocarlo sin sobreescribir los demás.


Se va a tratar desde fuera como una caja negra, ya que proporciona las suficientes operaciones como para retocar todo lo que se quiera del inventario. 
También cuenta con funciones como loadInventoryFromPath(), que copia a inventory.json el json que se le ponga. 