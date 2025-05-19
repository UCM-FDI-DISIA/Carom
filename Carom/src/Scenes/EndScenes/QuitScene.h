#pragma once 

#include "UIScene.h"
#include <string>

/// @brief La escena de overlay cuando se pulsa esc para salir del juego
class QuitScene : public UIScene {
std::shared_ptr<GameScene> _bottomScene;
void createTextObject(std::string text, std::string svg, std::string key);
public:
    /// @brief La constructora del menú de salida
    /// @param game El puntero al juego
    /// @param sceneToRenderBelow La escena que se ve bajo el fondo traslúcido
    QuitScene(Game* game, std::shared_ptr<GameScene> sceneToRenderBelow);

    ~QuitScene();

    void render() override;
    void initObjects() override;
};
