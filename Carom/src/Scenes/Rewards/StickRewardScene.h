#pragma once

#include "InstantRewardScene.h"

/// @brief Recompensa que le da un palo al jugador
class StickRewardScene : public InstantRewardScene 
{    
public:
    StickRewardScene(Game* game, Reward reward);
    virtual ~StickRewardScene();

    void atRender() override;

    /// @brief añade el palo seleccionado al inventario
    virtual void applyReward() override;

    /// @brief Inicializa la recompensa y todos los items y botones
    virtual void initObjects() override; 
private:
    /// @brief ID del palo recompensa
    StickId _stickReward;

    /// @brief Auxiliar, matchea el id para devolver la textura correspondiente necesaria para
    ///        generar el botón de la recompensa
    /// @param id
    /// @return 
    Texture* idToTexture(StickId id);

    /// @brief indican si esta seleccionado el palo del inventario o el nuevo
    bool _invSelected = false, _newSelected = false;

    /// @brief Texturas de los botones para darle el efecto de oscurecimiento al ser seleccionados
    RenderTextureComponent* _newStickTextureComponent = nullptr;
    /// @brief Texturas de los botones para darle el efecto de oscurecimiento al ser seleccionados
    RenderTextureComponent* _oldStickTextureComponent = nullptr;
};