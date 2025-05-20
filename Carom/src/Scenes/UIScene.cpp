#include "UIScene.h"

#include <fstream>

#include "TextDisplayComponent.h"
#include "BallInfoDisplayComponent.h"
#include "UnpauseComponent.h"
#include "FollowComponent.h"
#include "StickInputComponent.h"
#include "ShadowComponent.h"


#include "ScenesManager.h"
#include "InventoryManager.h"

using body_t = BallInfoDisplayComponent::Body;


void UIScene::init()
{
    initFunctionalities();
    initObjects();

    _initialized = true;
}

void UIScene::createTable()
{
    // !---- TEXTURES ----//
    // Set scale (same for all)
    float svgSize = *&sdlutils().svgs().at("game").at("mesa_marco").width;
    float textureSize = sdlutils().images().at("mesa1").width();
    float scale = svgSize/textureSize;

    // Entidad marco
    entity_t e_marco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_m = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("mesa_marco").x, *&sdlutils().svgs().at("game").at("mesa_marco").y);
    addComponent<TransformComponent>(e_marco, pos_m);
    addComponent<RenderTextureComponent>(e_marco, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, scale);

    // Entidad suelo
    entity_t e_fondo = new Entity(*this, grp::TABLE_BACKGROUND);
    b2Vec2 pos_f = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("fondo_mesa").x, *&sdlutils().svgs().at("game").at("fondo_mesa").y);
    addComponent<TransformComponent>(e_fondo, pos_f);
    addComponent<RenderTextureComponent>(e_fondo, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, scale);

    // Entidad sombraMarco
    entity_t e_sombraMarco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_s = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("mesa_sombra").x, *&sdlutils().svgs().at("game").at("mesa_sombra").y);
    addComponent<TransformComponent>(e_sombraMarco, b2Vec2{pos_s.x - 0.2f, pos_s.y - 0.2f});
    addComponent<RenderTextureComponent>(e_sombraMarco, &sdlutils().images().at("mesa1_sombra"), renderLayer::TABLE_SHADOW, scale);
}

void UIScene::createText(std::string text, int x, int y, int size, SDL_Color color, layerId_t rlayer)
{
    entity_t winContainer = new Entity(*this, grp::grpId::SCORE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);

    winContainer->addComponent(new TransformComponent(winContainer, pos));
    TextDisplayComponent* currentDisplay = new TextDisplayComponent(
        winContainer,           // container
        rlayer,                 // capa renderizado
        size,                   // tamano fuente
        text,                   // text
        color,                  // color (blanco)
        "Basteleur-Moonlight60" // fuente
    );
    winContainer->addComponent(currentDisplay);
}

entity_t UIScene::createSVGImage(std::string svg, std::string tag, std::string image, 
    bool isButton, grp::grpId group, layerId_t renderlayer)
{
    entity_t e = new Entity(*this, group);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at(svg).at(tag).x,
        *&sdlutils().svgs().at(svg).at(tag).y
    );

    float scale = float(sdlutils().svgs().at(svg).at(tag).width) / float(sdlutils().images().at(image).width());

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at(image), renderlayer, scale);

    if(isButton){
        Button::TextureButton rButton = Button::TextureButton();
        addComponent<Button>(e, rButton);
    }

    return e;
}

void UIScene::createButton(int x, int y, std::string text, Texture* t, std::function<void ()> cb) {

        entity_t e = new Entity(*this, grp::UI);

        b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);
    
        float scale = float(sdlutils().svgs().at("pool").at("hole 0").width) / float(sdlutils().images().at("hole").width());
    
        addComponent<TransformComponent>(e, pos);
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("reward_description_box"), renderLayer::UI, scale);
    
        Button::TextureButton button = Button::TextureButton();
        Button* b = addComponent<Button>(e, button);

        b->setOnClick(cb);
}


std::string 
UIScene::getTextureName(BallId effect) {
    return "single_" + getEffectName(effect);
}

std::string 
UIScene::getEffectName(BallId effect) {
    switch(effect){
        case ABBACUS: return "AbacusEffect";
        case BOWLING: return "BowlingEffect";
        case CRISTAL: return "CristalEffect";
        case PETANQUE: return "PetanqueEffect";
        case POKEBALL: return "PokeballEffect";
        case QUANTIC: return "QuanticEffect";
        case X2: return "X2Effect";
        default: return "";
    }
}


void
UIScene::instantiateInventory(){
    _ballsInfo = std::vector<BallInfo>(InventoryManager::Instance()->MAX_BALLS);

    //fondo del cajon
    entity_t fondo = new Entity(*this, grp::UI);
    b2Vec2 initialPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer_initial_pos").x, sdlutils().height()/2);
    auto tr = addComponent<TransformComponent>(fondo, initialPos);

    float drawerScale =sdlutils().svgs().at("inventory").at("drawer").height/(float) sdlutils().images().at("drawer").height();

    addComponent<RenderTextureComponent>(fondo, &sdlutils().images().at("drawer"), renderLayer::BACKGROUND, drawerScale);
    auto tween = addComponent<TweenComponent>(fondo);

    //animacion
    b2Vec2 finalPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer").x, sdlutils().height()/2);
    tween->easePosition(finalPos, .5f, tween::EASE_OUT_ELASTIC, false, [=](){
        //UNPAUSE ENTITY
        Entity* unpause = new Entity(*this, grp::PAUSE_UNPAUSE);
        addComponent<UnpauseComponent>(unpause, tween);
    });
    
    std::ifstream f(InventoryManager::Instance()->pathToInventory);
    json data = json::parse(f);
    //balls
    float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").width();

    for(int i = 0; i < InventoryManager::Instance()->MAX_BALLS; i++){
        std::string key = "ball_" + std::to_string(i+1);
        std::string slot = "slot" + std::to_string(i);

        //si no existe la bola en el slot i, no se renderiza
        if(data.find(slot) == data.end()) {
            _ballsInfo[i].free = false;
            continue;
        }

        // Guardar la información de las bolas del inventario en el vector _ballsInfo
        std::string textureKey = "bola_blanca";
        for(int j = 0; j < data[slot]["components"][0]["atributes"]["effects"].size(); ++j) {
            textureKey = data[slot]["components"][0]["atributes"]["effects"][j]["componentName"];

            if(textureKey == "BowlingEffect") _ballsInfo[i].effects.push_back(BOWLING);
            else if(textureKey == "X2Effect") _ballsInfo[i].effects.push_back(X2);
            else if(textureKey == "AbacusEffect") _ballsInfo[i].effects.push_back(ABBACUS);
            else if(textureKey == "CristalEffect") _ballsInfo[i].effects.push_back(CRISTAL);
            else if(textureKey == "PetanqueEffect") _ballsInfo[i].effects.push_back(PETANQUE);
            else if(textureKey == "PokeballEffect") _ballsInfo[i].effects.push_back(POKEBALL);
            else if(textureKey == "QuanticEffect") _ballsInfo[i].effects.push_back(QUANTIC);
            else _ballsInfo[i].effects.push_back(NORMAL_BALL); // Esto no ocurre nunca
        }

        // Guardamos el nombre del primer efecto de bola para renderizar esa textura
        if(textureKey != "bola_blanca")
            textureKey = "single_" + std::string(data[slot]["components"][0]["atributes"]["effects"][0]["componentName"]) ;


        auto ballPos = sdlutils().svgs().at("inventory").at(key);
        auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");

        b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(ballPos.x - drawerPos.x), PhysicsConverter::pixel2meter(ballPos.y - drawerPos.y)};

        Entity* ball = new Entity(*this, grp::UI);

        addComponent<TransformComponent>(ball, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(ball, &sdlutils().images().at(textureKey), renderLayer::EFFECT_BALL, ballScale);

        if(textureKey == "bola_blanca"){
            //colores
            auto color = sdlutils().inventorySlotColor[i];
            ball->getRenderer()->changeDefaultColorTint(color.r, color.g, color.b);
        }

        addComponent<FollowComponent>(ball, fondo, true, false, false, Vector2D(relativeDistance.x, -relativeDistance.y));
        createBallShadow(ball);

        Button::TextureButton rButton = Button::TextureButton();
        auto button = addComponent<Button>(ball, rButton);

        button->setOnHover([this, i]() {
            #ifdef _DEBUG
            std::cout << "Hovering effect ball " << i << std::endl; 
            #endif

            showBall(i);
        });

        button->setOnExit([this, i]() {
            #ifdef _DEBUG
            std::cout << "Exiting effect ball " << i << std::endl; 
            #endif
    
                hideBall(i);
            });

        button->setOnRightClick([this, i]() {
            scrollBallEffect(i);
        });
    }

    //palo
    entity_t palo = InventoryManager::Instance()->getStick(*this);
    removeComponent<StickInputComponent>(palo);
    
    auto renderText = getComponent<RenderTextureComponent>(palo);
    float stickTextScale = renderText->getTexture()->width();
    float stickSVGScale = sdlutils().svgs().at("inventory").at("stick").width;
    float stickScale = stickSVGScale/stickTextScale;

    renderText->setScale(stickScale);

    auto stickTextKey = data["stick"]["components"][0]["componentName"];

    if(stickTextKey == "DonutStickEffect") _stickID = DONUT;
    else if(stickTextKey == "MagicWandStickEffect") _stickID = WAND;
    else if(stickTextKey == "BoxingGloveStickEffect") _stickID = BOXING;
    else if(stickTextKey == "GrenadeLauncherStickEffect") _stickID = GRENADE;
    else _stickID = NORMAL_STICK;

    auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");
    auto stickPos = sdlutils().svgs().at("inventory").at("stick");
    b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(stickPos.x - drawerPos.x), PhysicsConverter::pixel2meter(stickPos.y - drawerPos.y)};

    addComponent<FollowComponent>(palo, fondo, true, false, false, Vector2D(relativeDistance.x, relativeDistance.y));

    for(auto shadow : getComponent<ShadowComponent>(palo)->getShadows()){
        getComponent<RenderTextureComponent>(shadow)->setScale(stickScale);
        auto follow = getComponent<FollowComponent>(shadow);
        follow->setRelativeDistance(follow->getRelativeDistance()/2);
    }

    Button::TextureButton rButton = Button::TextureButton();
    auto button = addComponent<Button>(palo, rButton);

    button->setOnHover([this]() {
        #ifdef _DEBUG
        std::cout << "Hovering stick " << std::endl; 
        #endif

        showStick();
    });

    button->setOnExit([this]() {
        #ifdef _DEBUG
        std::cout << "Exiting stick" << std::endl; 
        #endif
    
            hideStick();
        });

    createBallInfo();
    createStickInfo();
}

/// @brief Crea todos los carteles con la info de las bolas y los esconde. También añade eventos para mostrarlos al pasar el ratón por encima
void
UIScene::createBallInfo() {
    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("inventory_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("inventory").at("ball_Info_0").width) / texture->width();

    // Cargamos primero las bolas
    for(int i = 0; i < InventoryManager::Instance()->MAX_BALLS; ++i) {
        // FONDO
        description = new Entity(*this, grp::BALL_INFO_BG);

        auto svgElem = *&sdlutils().svgs().at("inventory").at("ball_Info_" + std::to_string(i));
        pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale * 1.5f);

        description->deactivate();


        // --------- TEXTO ---------
        Text ballName, ballDesc;

        std::string ballEffect;

        if(!_ballsInfo[i].free) {
            ballEffect = "empty";
        }
        else {
            if(_ballsInfo[i].effects.size() > 0) 
            {
                switch(_ballsInfo[i].effects[_ballsInfo[i].scrollIndex]) {
                    case ABBACUS: 
                        ballEffect= "abbacus";
                        break;
                    case BOWLING: 
                        ballEffect = "bowling";
                        break;
                    case CRISTAL: 
                        ballEffect = "cristal";
                        break;
                    case PETANQUE: 
                        ballEffect = "petanque";
                        break;
                    case POKEBALL: 
                        ballEffect = "poke";
                        break;
                    case QUANTIC: 
                        ballEffect = "quantic";
                        break;
                    case X2: 
                        ballEffect = "x2";
                        break;
                }
            }
            else ballEffect = "normal";

        }
        
        ballName = sdlutils().texts().at(ballEffect + "_ballName_pool");
        ballDesc = sdlutils().texts().at(ballEffect + "_ballDesc_pool");

        // usa rewardInfoDisplayComponent porque en esencia es para lo mismo.
        description = new Entity(*this, grp::BALL_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        BallInfoDisplayComponent* a_desc = addComponent<BallInfoDisplayComponent>(description, renderLayer::UI, 
                body_t{ballName.text, ballName.font, ballName.color, scale*1.5f},
                body_t{ballDesc.text, ballDesc.font, ballDesc.color, scale*2.f}
                , texture->width() * scale - 25
                , -texture->width()/2 * scale + 15, -texture->height()/2 * scale + 35
            );
        description->deactivate();

        _ballEffectBoxes.push_back(a_desc);

    
    }

    // El texto de ayuda se guarda al final del grupo BALL_INFO_TEXT
    createHints();
}

/// @brief Crea un texto con información extra
void
UIScene::createHints() 
{
    // Texto de ayuda para scroll de efectos
    entity_t help_text = new Entity(*this, grp::BALL_HELP_TEXT);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("inventory").at("hintText").x,
        *&sdlutils().svgs().at("inventory").at("hintText").y
    );

    auto tr = addComponent<TransformComponent>(help_text, pos);

    TextDisplayComponent* a_textDisplay = new TextDisplayComponent(help_text, renderLayer::UI, 1.0, 
        "Consejo: haz click derecho para mostrar más efectos", {255, 255, 255, 255}, "Aladin-Regular24");
    help_text->addComponent(a_textDisplay); 
    
    help_text->deactivate();
}


void UIScene::createBallShadow(entity_t entity){
    addComponent<ShadowComponent>(entity);
    ShadowComponent* comp = getComponent<ShadowComponent>(entity);

    //sombra de reflejo de la bola
    float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").getRect().w;

    comp->addShadow({0,0}, "bola_cast_sombra", renderLayer::BALL_SHADOW_ON_BALL, ballScale, true, false, true);

    //sombra de la bola
    float a_imgScale = sdlutils().images().at("bola_cast_sombra").width();

    float a_svg_scale = sdlutils().svgs().at("game").at("bola_cast_sombra 1").width;
    float normal_ball_scale = a_svg_scale/a_imgScale;
    float scaleFactor = ballScale/normal_ball_scale;

    //sombra de la bola
    a_imgScale = sdlutils().images().at("bola_sombra").width();
    a_svg_scale = sdlutils().svgs().at("game").at("bola_sombra 1").width;
    float cast_scale = a_svg_scale/a_imgScale;
    cast_scale *= scaleFactor;


    Vector2D a_relPos{
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").x - sdlutils().svgs().at("game").at("bola_sombra 1").x - 10) *scaleFactor,
        
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").y - sdlutils().svgs().at("game").at("bola_sombra 1").y)*scaleFactor
    };
    comp->addShadow({a_relPos.getX(), a_relPos.getY()}, "bola_sombra", renderLayer::BALL_SHADOW_ON_TABLE, cast_scale, true, false, true);

}

/// @brief muestra la info de determinada bola
/// @param i el id de la bola cuya info que queremos enseñar
void
UIScene::showBall(int i) {
    if(_ballsInfo[i].free) {
        auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
        descriptions[i]->activate();

        descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
        descriptions[i]->activate();

        // mostrar texto de ayuda si tiene varios efectos
        if(_ballsInfo[i].effects.size() > 1) {
            descriptions = getEntitiesOfGroup(grp::BALL_HELP_TEXT);
            for(auto e : descriptions) e->activate();
        }

    }

}

/// @brief esconde la info de determinada bola
/// @param i el id de la bola cuya info que queremos esconder
void
UIScene::hideBall(int i) {
    if(_ballsInfo[i].free) {
        auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
        descriptions[i]->deactivate();
        
        descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
        descriptions[i]->deactivate();

        // mostrar texto de ayuda si tiene varios efectos
        if(_ballsInfo[i].effects.size() > 1) {
            descriptions = getEntitiesOfGroup(grp::BALL_HELP_TEXT);
            for(auto e : descriptions) e->deactivate();
        }
    }
}


void 
UIScene::scrollBallEffect(int i) {

    if(_ballsInfo[i].effects.size() > 1) 
    {
        if(_ballsInfo[i].scrollIndex == (_ballsInfo[i].effects.size() - 1)) _ballsInfo[i].scrollIndex = 0;
        else _ballsInfo[i].scrollIndex += 1; //No pongo ++ porque se me hacía ilegible
        
        std::string ballEffect;
        
        switch(_ballsInfo[i].effects[_ballsInfo[i].scrollIndex]) {
            case ABBACUS: 
                ballEffect= "abbacus";
                break;
            case BOWLING: 
                ballEffect = "bowling";
                break;
            case CRISTAL: 
                ballEffect = "cristal";
                break;
            case PETANQUE: 
                ballEffect = "petanque";
                break;
            case POKEBALL: 
                ballEffect = "poke";
                break;
            case QUANTIC: 
                ballEffect = "quantic";
                break;
            case X2: 
                ballEffect = "x2";
                break;
            }


        auto texture = &sdlutils().images().at("reward_description_box");
        float scale = static_cast<float>(*&sdlutils().svgs().at("reward").at("boss_reward_info").width) / texture->width();

        Text ballName = sdlutils().texts().at(ballEffect + "_ballName_pool");
        Text ballDesc = sdlutils().texts().at(ballEffect + "_ballDesc_pool");

        

        body_t nameBody = {ballName.text, ballName.font, ballName.color, scale * 1.5f};
        _ballEffectBoxes[i]->setBallName(nameBody);

        body_t descBody = {ballDesc.text, ballDesc.font, ballDesc.color, scale * 2.0f};
        _ballEffectBoxes[i]->setBallDesc(descBody);

    }

}


/// @brief Crea el cartel con la info del palo y lo esconde. También añade eventos para mostrarlo al pasar el ratón por encima
void 
UIScene::createStickInfo(){

    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("inventory_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("inventory").at("ball_Info_0").width) / texture->width();

    // FONDO
    description = new Entity(*this, grp::STICK_INFO_BG);

    auto svgElem = *&sdlutils().svgs().at("inventory").at("stick_info");
    pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

    addComponent<TransformComponent>(description, pos);
    addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale * 1.5f);

    description->deactivate();

    // TEXTO
    // Añadir texto de recompensa / TODO: texto de partida de boss
    // en función de _floorRewards[i]
    Text title, desc;

    switch(_stickID){
        case GRENADE:
            title = sdlutils().texts().at("grenade_stickName_pool");
            desc = sdlutils().texts().at("grenade_stickDesc_pool");
            break;
        case DONUT:
            title = sdlutils().texts().at("donut_stickName_pool");
            desc = sdlutils().texts().at("donut_stickDesc_pool");
            break;
        case BOXING:
            title = sdlutils().texts().at("boxing_stickName_pool");
            desc = sdlutils().texts().at("boxing_stickDesc_pool");
            break;
        case WAND:
            title = sdlutils().texts().at("wand_stickName_pool");
            desc = sdlutils().texts().at("wand_stickDesc_pool");
            break;
        default:
            title = sdlutils().texts().at("normal_stickName_pool");
            desc = sdlutils().texts().at("normal_stickDesc_pool");
            break;
        }

        description = new Entity(*this, grp::STICK_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<BallInfoDisplayComponent>(description, 101, 
                body_t{title.text, title.font, title.color, scale*1.5f},
                body_t{desc.text, desc.font, desc.color, scale*1.5f}
                , texture->width() * scale - 60
                , -texture->width()/2 * scale, -texture->height()/2 * scale
            );
        description->deactivate();
}


/// @brief muestra la info del palo
void
UIScene::showStick(){
    auto stickInfo = getEntitiesOfGroup(grp::STICK_INFO_BG);
    stickInfo[0]->activate();

    stickInfo = getEntitiesOfGroup(grp::STICK_INFO_TEXT);
    stickInfo[0]->activate();
}

/// @brief esconde la info del palo
void
UIScene::hideStick(){
    auto stickInfo = getEntitiesOfGroup(grp::STICK_INFO_BG);
    stickInfo[0]->deactivate();

    stickInfo = getEntitiesOfGroup(grp::STICK_INFO_TEXT);
    stickInfo[0]->deactivate();
}
