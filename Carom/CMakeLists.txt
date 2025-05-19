 cmake_minimum_required(VERSION 3.15...3.30)

project(Carom VERSION 0.1 LANGUAGES CXX)

# Force dynamic runtime (/MD for Release, /MDd for Debug)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Memory leak
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_CRTDBG_MAP_ALLOC)
endif()

# Box2D
add_subdirectory(${CMAKE_SOURCE_DIR}/external/box2d)

# Force Box2D to use dynamic runtime
set_target_properties(box2d PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# nlohmann_json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${CMAKE_SOURCE_DIR}/external/nlohmann_json-3.12.0)

# Compila con la biblioteca SDL
if (CMAKE_HOST_WIN32)
    include_directories(
        external/SDL2-2.30.12/include
        external/SDL2_image-2.8.4/include
        external/SDL2_mixer-2.8.0/include
        external/SDL2_ttf-2.24.0/include
    )

    link_directories(
        external/SDL2-2.30.12/lib/x64
        external/SDL2_image-2.8.4/lib/x64
        external/SDL2_mixer-2.8.0/lib/x64
        external/SDL2_ttf-2.24.0/lib/x64
    )

    link_libraries(
        SDL2.lib
        SDL2main.lib
        SDL2_image.lib
        SDL2_mixer.lib
        SDL2_ttf.lib
    )
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS})
    link_libraries(${SDL2_LIBRARIES})
endif()

# Incluir directorios
include_directories(
    ${CMAKE_SOURCE_DIR}/include

    ${CMAKE_SOURCE_DIR}/external/sdlutils/include
    ${CMAKE_SOURCE_DIR}/external/utils/include
    ${CMAKE_SOURCE_DIR}/external/json/include
    ${CMAKE_SOURCE_DIR}/external/svg/include
    ${CMAKE_SOURCE_DIR}/external/clipper2/include

    ${CMAKE_SOURCE_DIR}/src

    ${CMAKE_SOURCE_DIR}/src/EC
    ${CMAKE_SOURCE_DIR}/src/EC/Components
    ${CMAKE_SOURCE_DIR}/src/EC/Components/GimmicksCmps
    ${CMAKE_SOURCE_DIR}/src/EC/Components/GimmicksCmps/Cowboy
    ${CMAKE_SOURCE_DIR}/src/EC/Components/GimmicksCmps/Russian
    ${CMAKE_SOURCE_DIR}/src/EC/Components/HandleEvent
    ${CMAKE_SOURCE_DIR}/src/EC/Components/Info
    ${CMAKE_SOURCE_DIR}/src/EC/Components/Info/Transforms
    ${CMAKE_SOURCE_DIR}/src/EC/Components/Info/Transforms/Rigidbodies
    ${CMAKE_SOURCE_DIR}/src/EC/Components/Logic
    ${CMAKE_SOURCE_DIR}/src/EC/Components/Physics
    ${CMAKE_SOURCE_DIR}/src/EC/Components/Render
    ${CMAKE_SOURCE_DIR}/src/EC/Components/StickEffects
    ${CMAKE_SOURCE_DIR}/src/Physics
    ${CMAKE_SOURCE_DIR}/src/SceneSystem
    ${CMAKE_SOURCE_DIR}/src/StateMachine
    ${CMAKE_SOURCE_DIR}/src/Scenes
    ${CMAKE_SOURCE_DIR}/src/Scenes/Gimmicks
	${CMAKE_SOURCE_DIR}/src/Scenes/EndScenes
	${CMAKE_SOURCE_DIR}/src/HitManager
	${CMAKE_SOURCE_DIR}/src/RNG
	${CMAKE_SOURCE_DIR}/src/Inventory
	${CMAKE_SOURCE_DIR}/src/Animator
	${CMAKE_SOURCE_DIR}/src/Ball
	${CMAKE_SOURCE_DIR}/src/Tweens
    ${CMAKE_SOURCE_DIR}/src/Scenes/MenuScenes
	${CMAKE_SOURCE_DIR}/src/Graphics
    ${CMAKE_SOURCE_DIR}/src/JSON
	${CMAKE_SOURCE_DIR}/src/Text
    ${CMAKE_SOURCE_DIR}/src/Audio
    ${CMAKE_SOURCE_DIR}/src/Progression
    ${CMAKE_SOURCE_DIR}/src/Scenes/Rewards
)

# Crear ejecutable
add_executable(Carom
    src/main.cpp

    external/sdlutils/src/SDLUtils.cpp
    external/sdlutils/src/SDLUtilsError.cpp
    external/sdlutils/src/SoundEffect.cpp
    external/sdlutils/src/Texture.cpp

    external/utils/src/Collisions.cpp
    external/utils/src/Vector2D.cpp
    external/sdlutils/src/SDLUtils.cpp
    external/sdlutils/src/SDLUtilsError.cpp
    external/sdlutils/src/SoundEffect.cpp
    external/sdlutils/src/Texture.cpp

    external/json/src/json_demo.cpp
    external/json/src/JSON.cpp
    external/json/src/JSONValue.cpp

    external/clipper2/src/clipper.engine.cpp
    external/clipper2/src/clipper.offset.cpp
    external/clipper2/src/clipper.rectclip.cpp

    src/Game.cpp

    src/SceneSystem/GameScene.cpp
    src/SceneSystem/ScenesManager.cpp

    src/EC/Component.cpp
    src/EC/Entity.cpp

    src/EC/Components/DialogueTextComponent.cpp
    src/EC/Components/PhysicsComponent.cpp
    src/EC/Components/RenderComponent.cpp

    src/EC/Components/GimmicksCmps/ForceFieldComponent.cpp
    src/EC/Components/GimmicksCmps/ForceAreaComponent.cpp
    src/EC/Components/GimmicksCmps/Cowboy/FrictionComponent.cpp
    src/EC/Components/GimmicksCmps/Cowboy/HoleComponent.cpp
    src/EC/Components/GimmicksCmps/Russian/PyramidComponent.cpp

    src/EC/Components/HandleEvent/Button.cpp
    src/EC/Components/HandleEvent/PauseComponent.cpp
    src/EC/Components/HandleEvent/StickInputComponent.cpp
    src/EC/Components/HandleEvent/UnpauseComponent.cpp

    src/EC/Components/Info/CameraComponent.cpp
    src/EC/Components/Info/ShadowComponent.cpp

    src/EC/Components/Info/Transforms/RigidBodyComponent.cpp
    src/EC/Components/Info/Transforms/TransformComponent.cpp

    src/EC/Components/Info/Transforms/Rigidbodies/BoxRBComponent.cpp
    src/EC/Components/Info/Transforms/Rigidbodies/CapsuleRBComponent.cpp
    src/EC/Components/Info/Transforms/Rigidbodies/CircleRBComponent.cpp
    src/EC/Components/Info/Transforms/Rigidbodies/PolygonRBComponent.cpp
    src/EC/Components/Info/Transforms/Rigidbodies/RectangleRBComponent.cpp

    src/EC/Components/Logic/AnimatorComponent.cpp
    src/EC/Components/Logic/BallRollerAnimatorComponent.cpp
    src/EC/Components/Logic/FollowComponent.cpp
    src/EC/Components/Logic/RandomVibrationComponent.cpp
    src/EC/Components/Logic/RoundScoreAnimComponent.cpp
    src/EC/Components/Logic/TweenComponent.cpp

    src/EC/Components/Physics/ColorBallScorerComponent.cpp
    src/EC/Components/Physics/EventOnCollision.cpp
    src/EC/Components/Physics/WhiteBallScorerComponent.cpp

    src/EC/Components/Render/BallInfoDisplayComponent.cpp
    src/EC/Components/Render/RenderArrayComponent.cpp
    src/EC/Components/Render/RenderSpritesheetComponent.cpp
    src/EC/Components/Render/RenderTextureComponent.cpp
    src/EC/Components/Render/RewardInfoDisplayComponent.cpp
    src/EC/Components/Render/TextDisplayComponent.cpp

    src/EC/Components/StickEffects/BoxingGloveStickEffect.cpp
    src/EC/Components/StickEffects/DonutStickEffect.cpp
    src/EC/Components/StickEffects/GranadeLauncherStickEffect.cpp
    src/EC/Components/StickEffects/MagicWandStickEffect.cpp
    src/EC/Components/StickEffects/WobblyRenderTextureComponent.cpp

    src/JSON/JsonEntityParser.cpp

	src/HitManager/ColorHitManager.cpp

	src/Scenes/PoolScene.cpp
	src/Scenes/PauseScene.cpp

	src/Scenes/EndScenes/EndGameScene.cpp
	src/Scenes/Rewards/RewardScene.cpp
    src/Scenes/Rewards/InstantRewardScene.cpp
    src/Scenes/Rewards/FusionRewardScene.cpp
    src/Scenes/Rewards/CauldronRewardScene.cpp
    src/Scenes/Rewards/BossRewardScene.cpp
    src/Scenes/Rewards/PermanentRewardScene.cpp
    src/Scenes/Rewards/StickRewardScene.cpp

	src/Inventory/InventoryManager.cpp

 	src/Ball/AbacusEffect.cpp
	src/Ball/PetanqueEffect.cpp
	src/Ball/BallEffect.cpp
	src/Ball/BallHandler.cpp
	src/Ball/QuanticEffect.cpp
    src/Ball/CristalEffect.cpp
    src/Ball/X2Effect.cpp
	src/Ball/PokeballEffect.cpp
	src/Ball/BowlingEffect.cpp
	src/Ball/SubdivisionEffect.cpp
	src/Ball/ExplosiveEffect.cpp
	src/Ball/FrictionMultiplierEffect.cpp
	src/Ball/PopToOppositeSideEffect.cpp

    src/Physics/PhysicsUtils.cpp
	src/Graphics/GraphicsUtils.cpp

    src/Scenes/CaromScene.cpp
    src/Scenes/PoolScene.cpp

	src/Scenes/UIScene.cpp
    src/Scenes/MenuScenes/MainMenuScene.cpp
    src/Scenes/MenuScenes/ControlsScene.cpp
    
    src/StateMachine/State.cpp
    src/StateMachine/StartMatchState.cpp
    src/StateMachine/HitState.cpp
    src/StateMachine/ScoringState.cpp
    src/StateMachine/AddScoreState.cpp
    src/StateMachine/WinMatchState.cpp
    src/StateMachine/LoseMatchState.cpp
    src/StateMachine/BossState.cpp

    src/Scenes/Gimmicks/CowboyPoolScene.cpp
    src/Scenes/Gimmicks/RussianPyramidScene.cpp

    src/Audio/AudioManager.cpp

    src/Scenes/TutorialScene.cpp
    src/Scenes/EndScenes/QuitScene.cpp

    src/StateMachine/TutorialOneHitState.cpp
    src/StateMachine/TutorialOneScoringState.cpp
    src/StateMachine/TutorialOneStartMatchState.cpp

    src/StateMachine/TutorialTwoHitState.cpp
    src/StateMachine/TutorialTwoScoringState.cpp
    src/StateMachine/TutorialTwoStartMatchState.cpp

    src/Scenes/HelperScene.cpp
    src/Scenes/TextHelperScene.cpp
    src/Progression/ProgressionManager.cpp
)

# Link Box2D
target_link_libraries(Carom PRIVATE box2d)

# Link nlohmann_json
target_link_libraries(Carom PRIVATE nlohmann_json::nlohmann_json)

# Ensure consistent runtime for Carom
if (CMAKE_HOST_WIN32)
    set_target_properties(Carom PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

set_target_properties(box2d PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/external/box2d/build/src/$<CONFIG>)

# Definir directorios de salida
set_target_properties(Carom PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)

if (CMAKE_HOST_WIN32)
    set(DLL_DIR ${CMAKE_SOURCE_DIR}/dlls)

    add_custom_command(TARGET Carom POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${DLL_DIR} $<TARGET_FILE_DIR:Carom>
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(PDB_DIR ${CMAKE_SOURCE_DIR}/pdbs)

        add_custom_command(TARGET Carom POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PDB_DIR} $<TARGET_FILE_DIR:Carom>
        )
    endif()
endif()

if (WIN32)
set_target_properties(Carom PROPERTIES
    WIN32_EXECUTABLE TRUE
)
endif()