#pragma once

#include "UIScene.h"

class RewardScene : public UIScene 
{
public:
    enum ballID{
        NORMAL_BALL,
        CRISTAL,
        BOWLING,
        POKEBALL,
        X2,
        ABBACUS,
        QUANTIC,
        PETANQUE
    };
    enum stickID{
        NORMAL_STICK,
        GRENADE,
        DONUT,
        BOXING,
        WAND
    };

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

    virtual void atRender();
    void render() override;

    virtual void applyReward() {}

    void showExitButton();
    virtual void exitCallback();

    /// @brief Renderiza el cajón abriendose con las bolas y palos de inventario
    void openInventory();

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

    std::vector<ballID> _ballIDs;
    stickID _stickID;
    int previousTheme;
};
