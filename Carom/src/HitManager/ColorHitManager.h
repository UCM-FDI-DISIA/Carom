#pragma once
#include <unordered_set>
#include "Singleton.h"
#include "Vector2D.h"

class GameScene;

namespace ecs{
    class ColorHitManager : public Singleton<ColorHitManager>{
    protected:
        GameScene* _mainScene;
        std::unordered_set<Vector2D> _positionsRegistered;
    public:
        //Recibe un puntero a la mainScene, que es la que lo crea
        ColorHitManager(GameScene* mainScene);
        //Reinicia todo el set de posiciones, normalmente se llama al principio del nuevo frame de la escena para registrar los nuevos choques
        void clearAllPositions();
        //Comprueba que la posicion de hit que se le pasa está o no en el set de posiciones
        //- Si no está, hace acciones determinadas y lo añade al set
        //- Si está, no hace nada ya que quiere decir que la otra bola ya ha hecho la acción que debería pasar
        bool checkForHitPosition(Vector2D hitPos);
    };
}