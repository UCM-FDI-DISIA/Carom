// This file is part of the course TPV2@UCM - Samir Genaim

#include "SDLUtils.h"

#include <cassert>
#include <memory>

#include "JSON.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#define NANOSVG_IMPLEMENTATION	// Expands implementation
#include "nanosvg.h"
#include "nanosvgrast.h"

SDLUtils::SDLUtils() :
		_windowTitle("SDL2 Demo"), //
		_width(600), //
		_height(480), //
		_window(nullptr), //
		_renderer(nullptr), //
		_fontsAccessWrapper(_fonts, "Fonts Table"), //
		_imagesAccessWrapper(_images, "Images Table"), //
		_svgAccessWrapper_table(_svg_table, "SVG Table"), //
		_svgAccessWrapper_ballPos(_svg_ballPos, "SVG Ball Positions"), //
		_svgAccessWrapper_CowboyPool_shotHoles(_svg_CowboyPool_shotHoles, "SVG Cowboy Pool Shot hole positions"), //
		_msgsAccessWrapper(_msgs, "Messages Table"), //
		_soundsAccessWrapper(_sounds, "Sounds Table"), //
		_musicsAccessWrapper(_musics, "Musics Table"), //
		_currTime(0), //
		_deltaTime(0) //
{
}

bool SDLUtils::init(std::string windowTitle, int width, int height) {
	assert(width > 0);
	assert(height > 0);
	_windowTitle = windowTitle;
	_height = height;
	_width = width;

	initWindow();
	initSDLExtensions();

	// we always return true, because this class either exit or throws an
	// exception on error. If you want to avoid using exceptions you should
	// find a workaround using booleans.
	return true;
}

bool SDLUtils::init(std::string windowTitle, int width, int height, std::string filename, const char* svgFilename_table, const char* svgFilename_ballPos) {
	init(windowTitle, width, height);
	
	loadReasources(filename);
	loadSVG(_svg_table, svgFilename_table);
	loadSVG(_svg_ballPos, svgFilename_ballPos);

	// we always return true, because this class either exit or throws an
	// exception on error. If you want to avoid using exceptions you should
	// find a workaround using booleans.
	return true;
}

SDLUtils::~SDLUtils() {
	closeSDLExtensions();
	closeWindow();
}

void SDLUtils::initWindow() {

#ifdef _DEBUG
	std::cout << "Initializing SDL" << std::endl;
#endif

	// Initialize SDL
	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

#ifdef _DEBUG
	std::cout << "Creating SDL window" << std::endl;
#endif

	// Create window
	_window = SDL_CreateWindow(_windowTitle.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
	assert(_window != nullptr);

#ifdef _DEBUG
	std::cout << "Creating SDL renderer" << std::endl;
#endif
	// Create the renderer
	_renderer = SDL_CreateRenderer(_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(_renderer != nullptr);

	// hide cursor by default
	hideCursor();

}

void SDLUtils::closeWindow() {

	// destroy renderer and window
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);

	SDL_Quit(); // quit SDL
}

void SDLUtils::initSDLExtensions() {

#ifdef _DEBUG
	std::cout << "Initializing SDL_ttf" << std::endl;
#endif
	// initialize SDL_ttf
	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);

#ifdef _DEBUG
	std::cout << "Initializing SDL_img" << std::endl;
#endif
	// initialize SDL_image
	int imgInit_ret = IMG_Init(
			IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	assert(imgInit_ret != 0);

#ifdef _DEBUG
	std::cout << "Initializing SDL_Mixer" << std::endl;
#endif
	// initialize SDL_Mixer
	int mixOpenAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	assert(mixOpenAudio == 0);
	int mixInit_ret = Mix_Init(
			MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	assert(mixInit_ret != 0);
	SoundEffect::setNumberofChannels(8); // we start with 8 channels

#ifdef _DEBUG
	std::cout << "Initializing the InputHandler" << std::endl;
#endif

}

void SDLUtils::loadReasources(std::string filename) {
	// TODO check the correctness of values and issue a corresponding
	// exception. Now we just do some simple checks, and assume input
	// is correct.

	// Load JSON configuration file. We use a unique pointer since we
	// can exit the method in different ways, this way we guarantee that
	// it is always deleted
	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

	// check it was loaded correctly
	// the root must be a JSON object
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jValueRoot->AsObject();
	JSONValue *jValue = nullptr;

	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	// load fonts
	jValue = root["fonts"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			_fonts.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
					uint8_t size =
							static_cast<uint8_t>(vObj["size"]->AsNumber());
#ifdef _DEBUG
					std::cout << "Loading font with id: " << key << std::endl;
#endif
					_fonts.emplace(key, Font(file, size));
				} else {
					throw "'fonts' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'fonts' is not an array in '" + filename + "'";
		}
	}

	// load images
	jValue = root["images"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			_images.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading image with id: " << key << std::endl;
#endif
					_images.emplace(key, Texture(renderer(), file));
				} else {
					throw "'images' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'images' is not an array in '" + filename + "'";
		}
	}

	// load messages
	jValue = root["messages"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			_msgs.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string txt = vObj["text"]->AsString();
					auto &font = _fonts.at(vObj["font"]->AsString());
#ifdef _DEBUG
					std::cout << "Loading message with id: " << key
							<< std::endl;
#endif
					if (vObj["bg"] == nullptr)
						_msgs.emplace(key,
								Texture(renderer(), txt, font,
										build_sdlcolor(
												vObj["color"]->AsString())));
					else
						_msgs.emplace(key,
								Texture(renderer(), txt, font,
										build_sdlcolor(
												vObj["color"]->AsString()),
										build_sdlcolor(
												vObj["bg"]->AsString())));
				} else {
					throw "'messages' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'messages' is not an array in '" + filename + "'";
		}
	}

	// load sounds
	jValue = root["sounds"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			_sounds.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading sound effect with id: " << key
							<< std::endl;
#endif
					_sounds.emplace(key, SoundEffect(file));
				} else {
					throw "'sounds' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'sounds' is not an array";
		}
	}

	// load musics
	jValue = root["musics"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			_musics.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
#ifdef _DEBUG
					std::cout << "Loading music with id: " << key << std::endl;
#endif
					_musics.emplace(key, Music(file));
				} else {
					throw "'musics' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'musics' is not an array";
		}
	}

}

void SDLUtils::loadSVG(auto& svgMap, const char* filename){
	struct NSVGimage* image = nsvgParseFromFile(filename, "px", 96.0f);
    if (!image) {
        std::cerr << "Failed to load SVG: " << filename << std::endl;
        return;
    }
	
	// Clear the existing SVG elements (if any)
	svgMap.clear();

	// Iterate through the shapes in the SVG
	for (NSVGshape* shape = image->shapes; shape != nullptr; shape = shape->next) {
		// Create an svgElem structure for the current shape
		svgElem elem;

		elem.width = static_cast<int>(shape->bounds[2] - shape->bounds[0]);  // Width
		elem.height = static_cast<int>(shape->bounds[3] - shape->bounds[1]); // Height
		elem.x = static_cast<int>(shape->bounds[0]) + elem.width/2;      // X position
		elem.y = static_cast<int>(shape->bounds[1]) + elem.height/2;      // Y position

		// Use the shape's ID as the key in the map
		std::string id = shape->id;
		svgMap.emplace(id, elem);
	}

	// Free the SVG image
	nsvgDelete(image);

	std::cout << "SVG loaded and parsed successfully!" << std::endl;

}

void SDLUtils::closeSDLExtensions() {

	_musics.clear();
	_sounds.clear();
	_msgs.clear();
	_images.clear();
	_fonts.clear();

	Mix_Quit(); // quit SDL_mixer
	IMG_Quit(); // quit SDL_image
	TTF_Quit(); // quit SDL_ttf
}

