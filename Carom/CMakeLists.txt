 cmake_minimum_required(VERSION 3.15...3.30)

project(Carom VERSION 0.1 LANGUAGES CXX)

# Force dynamic runtime (/MD for Release, /MDd for Debug)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Box2D
add_subdirectory(${CMAKE_SOURCE_DIR}/external/box2d)

# Force Box2D to use dynamic runtime
set_target_properties(box2d PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

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

    ${CMAKE_SOURCE_DIR}/src/ECS
    ${CMAKE_SOURCE_DIR}/src/ECS/GimmicksCmps
    ${CMAKE_SOURCE_DIR}/src/ECS/GimmicksCmps/Cowboy
    ${CMAKE_SOURCE_DIR}/src/Physics
    ${CMAKE_SOURCE_DIR}/src/SceneSystem
    ${CMAKE_SOURCE_DIR}/src/StateMachine
    ${CMAKE_SOURCE_DIR}/src/Scenes
    ${CMAKE_SOURCE_DIR}/src/Scenes/Gimmicks
	${CMAKE_SOURCE_DIR}/src/Scenes/EndScenes
	${CMAKE_SOURCE_DIR}/src/Physics
	${CMAKE_SOURCE_DIR}/src/HitManager
	${CMAKE_SOURCE_DIR}/src/RNG
	${CMAKE_SOURCE_DIR}/src/Inventory
	${CMAKE_SOURCE_DIR}/src/Animator
	${CMAKE_SOURCE_DIR}/src/Ball
	${CMAKE_SOURCE_DIR}/src/Tweens
    ${CMAKE_SOURCE_DIR}/src/Scenes/MenuScenes
	${CMAKE_SOURCE_DIR}/src/Graphics
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
    src/ECS/CameraComponent.cpp

	src/ECS/TransformComponent.cpp
	src/ECS/RigidBodyComponent.cpp
	src/ECS/JsonEntityParser.cpp
	src/ECS/StickInputComponent.cpp
	src/ECS/Button.cpp
	src/ECS/BoxRBComponent.cpp
	src/ECS/RectangleRBComponent.cpp
	src/ECS/PolygonRBComponent.cpp
	src/ECS/CircleRBComponent.cpp
	src/ECS/CapsuleRBComponent.cpp
    src/ECS/Entity.cpp
    src/ECS/Component.cpp
    src/ECS/RenderTextureComponent.cpp

    src/ECS/TransformComponent.cpp
    src/ECS/RigidBodyComponent.cpp
    src/ECS/StickInputComponent.cpp
    src/ECS/Button.cpp
    src/ECS/BoxRBComponent.cpp
    src/ECS/RectangleRBComponent.cpp
    src/ECS/PolygonRBComponent.cpp
    src/ECS/CircleRBComponent.cpp
    src/ECS/CapsuleRBComponent.cpp

    src/ECS/ColorBallScorerComponent.cpp
    src/ECS/WhiteBallScorerComponent.cpp
	src/ECS/TextDisplayComponent.cpp
	src/ECS/FollowComponent.cpp
    src/ECS/EventOnCollision.cpp
    src/ECS/PhysicsComponent.cpp
	
	src/Animator/RenderSpriteSheetComponent.cpp
	src/Animator/AnimatorComponent.cpp

	src/HitManager/ColorHitManager.cpp

    src/ECS/FollowComponent.cpp

    src/ECS/GimmicksCmps/ForceFieldComponent.cpp
    src/ECS/GimmicksCmps/ForceAreaComponent.cpp
    src/ECS/GimmicksCmps/Cowboy/FrictionComponent.cpp
    src/ECS/GimmicksCmps/Cowboy/HoleComponent.cpp

    src/HitManager/ColorHitManager.cpp

	src/Scenes/PrefabTestScene.cpp
	src/Scenes/PoolScene.cpp
	src/Scenes/PauseScene.cpp

	src/Scenes/EndScenes/EndGameScene.cpp
	src/Scenes/EndScenes/RewardScene.cpp
	
	src/StateMachine/StartMatchState.cpp
	src/StateMachine/HitState.cpp
	src/StateMachine/ScoringState.cpp
	src/StateMachine/WinMatchState.cpp
	src/StateMachine/LoseMatchState.cpp

	src/Inventory/InventoryManager.cpp

 	src/Ball/AbacusEffect.cpp
	src/Ball/PetanqueEffect.cpp
	src/Ball/BallEffect.cpp
	src/Ball/BallHandler.cpp
	src/Ball/QuanticEffect.cpp
    src/Ball/X2Effect.cpp
	src/Ball/PokeballEffect.cpp
	src/Ball/BowlingEffect.cpp
	src/Ball/SubdivisionEffect.cpp
	src/Ball/ExplosiveEffect.cpp
	src/Ball/FrictionMultiplierEffect.cpp
	src/Ball/PopToOppositeSideEffect.cpp


	src/ECS/BoxingGloveStickEffect.cpp
	src/ECS/MagicWandStickEffect.cpp
	src/ECS/GranadeLauncherStickEffect.cpp
	src/ECS/DonutStickEffect.cpp
	src/StateMachine/BossState.cpp
    src/Physics/PhysicsUtils.cpp
	src/Graphics/GraphicsUtils.cpp

    src/Scenes/CaromScene.cpp
    src/Scenes/PoolScene.cpp

	src/Scenes/UIScene.cpp
    src/Scenes/MenuScenes/MainMenuScene.cpp
    
    src/StateMachine/StartMatchState.cpp
    src/StateMachine/HitState.cpp
    src/StateMachine/ScoringState.cpp
    src/StateMachine/WinMatchState.cpp
    src/StateMachine/LoseMatchState.cpp
    src/StateMachine/BossState.cpp

    src/Scenes/Gimmicks/CowboyPoolScene.cpp

    src/ECS/TweenComponent.cpp
    src/ECS/ShadowComponent.cpp
    src/ECS/PauseComponent.cpp
    src/ECS/UnpauseComponent.cpp

    src/ECS/RandomVibrationComponent.cpp
)

# Link Box2D
target_link_libraries(Carom PRIVATE box2d)

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