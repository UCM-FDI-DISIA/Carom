#pragma once

#include "UIScene.h"
#include "ItemIDs.h"
#include "Button.h"

/// @brief La clase abstracta de una escena de recompensa
class RewardScene : public UIScene 
{
public:

    struct ButtonWithSlot {
        Button* button = nullptr;
        /// @brief el slot 0 es el palo ojo cuidao
        int slot = -1;
    };

    /// @brief Una recompensa de cara a la UI
    class Reward 
    {
    public:
    enum Type {
        INSTANT,
        PERMANENT,
        BOSS
    };

    protected:
        std::string _name;
        Type _type;
        
    public:
        Reward(std::string n, Type t) : _name(n), _type(t) {}

        inline std::string getName() { return _name; }
        inline Type getType() { return _type; }

        std::string translateName(std::string s){
            if(s == "default"){ s = "Por defecto"; }
            else if(s == "fusion") { s = "Fusion"; }
            else if(s == "gumball") { s = "Maquina de chicles"; }
            else if(s == "stick") { s = "Desvan"; }
            else if(s == "cauldron") { s = "Caldero"; }
            else if(s == "skill") { s = "Soltura"; }
            else if(s == "charisma") { s = "Carisma"; }
            else if(s == "power") { s = "Poder"; }
            else if(s == "cunning") { s = "Picardia"; }
            return s;
        }

        std::string translateType(Type t){
            std::string s;
            switch (t) {
            case INSTANT: s = "Instantanea"; break;
            case PERMANENT: s = "Permanente"; break;
            case BOSS: s = "Jefe"; break;
            default: break;}
            return s;
        }
    };

    RewardScene(Game* game, Reward reward);
    virtual ~RewardScene();

protected:
    void init() override;
    virtual void initObjects() override; 
    virtual void initFunctionalities() override {}

    /// @brief Método que se llama el primer frame del render, por si se ha de alterar la apariencia del inventario
    virtual void atRender();
    void render() override;

    /// @brief El método que le da la recompensa al jugador
    virtual void applyReward() {}

    //Métodos del botón de salir:
    void moveExitButtonToRight();
    void showExitButton();
    void hideExitButton();
    virtual void exitCallback();

    /// @brief Renderiza el cajón abriendose con las bolas y palos de inventario
    std::vector<ButtonWithSlot> openInventory();

    /// @brief  Crea todos los carteles con la info de las bolas y los esconde. 
    ///         También añade eventos para mostrarlos al pasar el ratón por encima
    void createBallInfo();

    void createBallShadow(entity_t e);
    void showBall(int i);
    void hideBall(int i);
    // Stick info handling
    void createStickInfo();
    void showStick();
    void hideStick();

    void selectBall(int i);
    void changeStick(int i);

    inline Reward getReward() { return _reward; }



protected:
    Reward _reward;
    entity_t _exitButton;
    entity_t _exitBttText;
    bool _atReward; // bool para saber la primera vez que se renderiza reward

    std::vector<BallId> _ballIDs;
    StickId _stickID;
    int previousTheme;
};
