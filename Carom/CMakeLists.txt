cmake_minimum_required(VERSION 3.15...3.30)

project(Carom VERSION 0.1 LANGUAGES CXX)

# Force dynamic runtime (/MD for Release, /MDd for Debug)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fix runtime conflicts between static and dynamic linking
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Box2D
add_subdirectory(${CMAKE_SOURCE_DIR}/external/box2d)

# Force Box2D (if needed) to use dynamic runtime:
set_target_properties(box2d PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Compila con la biblioteca SDL
if (CMAKE_HOST_WIN32)
	# Utiliza las bibliotecas compiladas que van incluidas
	# en el paquete con el proyecto de Visual Studio
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
	# En otros sistemas operativos utiliza find_package
	# para encontrar las bibliotecas instaladas aparte

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

	${CMAKE_SOURCE_DIR}/src/ECS
	${CMAKE_SOURCE_DIR}/src/SceneSystem
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
	external/sdlutils/src/sdlutils_demo.cpp
	external/sdlutils/src/SDLUtils.cpp
	external/sdlutils/src/SDLUtilsError.cpp
	external/sdlutils/src/SoundEffect.cpp
	external/sdlutils/src/Texture.cpp

	external/json/src/json_demo.cpp
	external/json/src/JSON.cpp
	external/json/src/JSONValue.cpp

	src/Game.cpp

	src/SceneSystem/GameScene.cpp

	src/ECS/Entity.cpp
	src/Physics/B2Manager.cpp

)

# Link Box2D
target_link_libraries(Carom PRIVATE box2d)

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