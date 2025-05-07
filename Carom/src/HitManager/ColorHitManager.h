#pragma once
#include <unordered_map>
#include "Singleton.h"
#include <unordered_set>


class CaromScene;
class Entity;
class InventoryManager;

class ColorHitManager {
    protected:
    CaromScene* _mainScene;
    std::unordered_map<Entity*, std::unordered_set<Entity*>> _positionsRegistered;
    
    InventoryManager* _inventory;
    const int baseComboScore = 2;
public:
    //Recibe un puntero a la mainScene, que es la que lo crea
    ColorHitManager(CaromScene* mainScene);
    //Reinicia todo el set de posiciones, normalmente se llama al principio del nuevo frame de la escena para registrar los nuevos choques
    void clearAllHits();
    //Comprueba que la posicion de hit que se le pasa está o no en el set de posiciones
    //- Si no está, hace acciones determinadas y lo añade al set
    //- Si está, no hace nada ya que quiere decir que la otra bola ya ha hecho la acción que debería pasar
    bool processHitEntities(Entity* first, Entity* second);
};
