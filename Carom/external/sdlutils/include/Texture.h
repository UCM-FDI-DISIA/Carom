// This file is part of the course TPV2@UCM - Samir Genaim
// With modifications from other people

#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include <string>
#include <cassert>
#include <iostream>
#include <vector>

#include "Font.h"

class Texture {
public:

	// cannot copy textures
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	// can be moved
	Texture& operator=(Texture &&other) noexcept;
	Texture(Texture &&other) noexcept;

	// Construct from image
	Texture(SDL_Renderer *renderer, const std::string &fileName);

	// Construct an image from a rect of an image
	Texture(SDL_Renderer *renderer, const std::string &fileName, const SDL_Rect& rect);

	// Construct an image from a rect of an image using custom alphamask
	Texture(SDL_Renderer *renderer, const std::string &fileName, const SDL_Rect& rect, const std::vector<uint8_t>& alphaMask);

	// Construct from text
	Texture(SDL_Renderer *renderer, const std::string &text, const Font &font,
			const SDL_Color &fgColor);

	// Construct from text with background
	Texture(SDL_Renderer *renderer, const std::string &text, const Font &font,
			const SDL_Color &fgColor, const SDL_Color &bgColor);

	// Construct from text with wrap
	Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor, const Uint32 &wrapLegth);


	virtual ~Texture() {
		if (_texture != nullptr)
			SDL_DestroyTexture(_texture); // delete the SDL texture
	}

	inline int width() const {
		return _width;
	}

	inline int height() const {
		return _height;
	}

	inline auto getRenderer() const{
		return _renderer;
	}

	// This rendering method corresponds to method SDL_RenderCopyEx.
	//
	// Renders part of the texture (src) to a destination rectangle (dest)
	// with a rotation (angle) around point p (of dest), and flips
	// according to the value of flip. If 'p'is nullptr, the rotation is done
	// wrt. the center
	//
	inline void render(const SDL_Rect &src, const SDL_Rect &dest, double angle,
			const SDL_Point *p = nullptr,
			SDL_RendererFlip flip = SDL_FLIP_NONE) {
		assert(_texture != nullptr);
		SDL_RenderCopyEx(_renderer, _texture, &src, &dest, angle, p, flip);
	}

	// This rendering method corresponds to method SDL_RenderCopy.
	//
	// Renders part of the texture (src) to a destination rectangle (dest).
	// It can be implemented by calling the previous render method as well,
	// but we use SDL_RenderCopy directly since it does less checks so it
	// saves some checks ...
	inline void render(const SDL_Rect &src, const SDL_Rect &dest) {
		assert(_texture != nullptr);
		SDL_RenderCopy(_renderer, _texture, &src, &dest);
	}

	// render the complete texture at position (x,y).
	inline void render(int x, int y) {
		SDL_Rect dest = { x, y, _width, _height };
		render(dest);
	}

	inline SDL_Rect getRect(int x, int y){
		return { x, y, _width, _height };
	}

	// Get rect with absolute position (x, y)
	inline SDL_Rect getRect(){
		return { _x, _y, _width, _height };
	}

	// renders the complete texture at a destination rectangle (dest)
	inline void render(const SDL_Rect &dest) {
		SDL_Rect src = { 0, 0, _width, _height };
		render(src, dest);
	}

	// renders the complete texture at a destination rectangle (dest),
	// with rotation
	inline void render(const SDL_Rect &dest, float rotation) {
		SDL_Rect src = { 0, 0, _width, _height };
		render(src, dest, rotation);
	}

	inline int render(const SDL_Rect& dest, SDL_Vertex* vertices, int verticesNumber, int* indexes, int indexesSize){
		return SDL_RenderGeometry(getRenderer(), _texture, vertices, verticesNumber, indexes, indexesSize);
	}

	inline void changeColorTint(int r, int g, int b){
		SDL_SetTextureColorMod(_texture, r, g, b);
	}

	inline void changeOpacity(uint8_t alpha){
		SDL_SetTextureAlphaMod(_texture, alpha);
	}

private:

	// Construct from text
	void constructFromText(SDL_Renderer *renderer, const std::string &text,
			const Font &font, const SDL_Color *fgColor,
			const SDL_Color *bgColor = nullptr);

	// Construct from text with wrap
	void constructFromTextWrap(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color *fgColor, const Uint32 &wrapLegth = 0);

	SDL_Texture *_texture;
	SDL_Renderer *_renderer;
	int _width;
	int _height;
	int _x = 0;
	int _y = 0;
};
