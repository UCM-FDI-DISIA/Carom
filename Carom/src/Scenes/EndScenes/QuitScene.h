#pragma once 

#include "UIScene.h"
#include <string>

class QuitScene : public UIScene {
std::shared_ptr<GameScene> _bottomScene;
void createTextObject(std::string text, std::string svg, std::string key);
public:
    QuitScene(Game* game, std::shared_ptr<GameScene> sceneToRenderBelow);

    ~QuitScene();

    void render() override;
    void initObjects() override;
};
