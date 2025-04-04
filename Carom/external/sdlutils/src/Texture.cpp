// This file is part of the course TPV2@UCM - Samir Genaim
// With modifications from other people

#include "Texture.h"

Texture::Texture(Texture &&other) noexcept {
    _texture = other._texture;
    other._texture = nullptr;
    _renderer = other._renderer;
    other._renderer = nullptr;
    _width = other._width;
    _height = other._height;
    _x = other._x;
    _y = other._y;
    other._x = 0;
    other._y = 0;
}

Texture& Texture::operator=(Texture &&other) noexcept {
    this->~Texture();
    _texture = other._texture;
    other._texture = nullptr;
    _renderer = other._renderer;
    other._renderer = nullptr;
    _width = other._width;
    _height = other._height;
    _x = other._x;
    _y = other._y;
    other._x = 0;
    other._y = 0;
    return *this;
}

Texture::Texture(SDL_Renderer *renderer, const std::string &fileName) {
	assert(renderer != nullptr);
	_renderer = renderer;

	SDL_Surface *surface = IMG_Load(fileName.c_str());

#ifdef _DEBUG
	if (surface == nullptr)
		std::cerr << "Couldn't load image: " << fileName;
#endif
	assert(surface != nullptr);

	_width = surface->w;
	_height = surface->h;

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	assert(_texture != nullptr);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &fileName, const SDL_Rect &rect)
{
	assert(renderer != nullptr);
	_renderer = renderer;

	// Load an image into a surface
    SDL_Surface* originalSurface = IMG_Load(fileName.c_str());
    if (!originalSurface) {
        printf("Error loading surface: %s\n", SDL_GetError());
    }

    SDL_Rect srcRect = rect;

    // Create a new surface for the portion
    SDL_Surface* portionSurface = SDL_CreateRGBSurface(0, srcRect.w, srcRect.h, originalSurface->format->BitsPerPixel,
	originalSurface->format->Rmask, originalSurface->format->Gmask,
	originalSurface->format->Bmask, originalSurface->format->Amask);

    SDL_BlitSurface(originalSurface, &srcRect, portionSurface, NULL);

    // Create a texture from the portion surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, portionSurface);
    if (!texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
    }

	assert(portionSurface != nullptr);

	_width = portionSurface->w;
	_height = portionSurface->h;
	// _x = rect.x;
	// _y = rect.y;

	_texture = SDL_CreateTextureFromSurface(renderer, portionSurface);
	SDL_FreeSurface(portionSurface);
	assert(_texture != nullptr);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &fileName, const SDL_Rect &rect, const std::vector<uint8_t> &alphaMask)
{
	assert(renderer != nullptr);
    _renderer = renderer;

    SDL_Surface* originalSurface = IMG_Load(fileName.c_str());
    if (!originalSurface) {
        printf("Error loading surface: %s\n", SDL_GetError());
        assert(false);
    }

    // Convert the surface to RGBA32 format to ensure alpha channel support
    SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(originalSurface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(originalSurface);
    if (!formattedSurface) {
        printf("Error converting surface format: %s\n", SDL_GetError());
        assert(false);
    }

    //  Create a new surface for the portion defined by rect
    SDL_Rect srcRect = rect;
    SDL_Surface* portionSurface = SDL_CreateRGBSurface(
        0, srcRect.w, srcRect.h, formattedSurface->format->BitsPerPixel,
        formattedSurface->format->Rmask, formattedSurface->format->Gmask,
        formattedSurface->format->Bmask, formattedSurface->format->Amask
    );
    if (!portionSurface) {
        printf("Error creating portion surface: %s\n", SDL_GetError());
        SDL_FreeSurface(formattedSurface);
        assert(false);
    }

    // Blit the specified rectangle from the original surface to the portion surface
    SDL_BlitSurface(formattedSurface, &srcRect, portionSurface, nullptr);
    SDL_FreeSurface(formattedSurface);

    // Lock the portion surface to modify its pixels
    if (SDL_LockSurface(portionSurface) != 0) {
        printf("Error locking surface: %s\n", SDL_GetError());
        SDL_FreeSurface(portionSurface);
        assert(false);
    }

    // Apply the alpha mask to the portion surface
    Uint32* pixels = static_cast<Uint32*>(portionSurface->pixels);
    SDL_PixelFormat* format = portionSurface->format;
    for (int y = 0; y < rect.h; ++y) {
        for (int x = 0; x < rect.w; ++x) {
            // Calculate pixel index
            int pixelIndex = y * (portionSurface->pitch / 4) + x;
            Uint32 pixel = pixels[pixelIndex];

            // Extract current RGBA values
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, format, &r, &g, &b, &a);

            // Get the new alpha value from the alphaMask
            Uint8 newAlpha = alphaMask[y * rect.w + x];

            // Update the pixel with the new alpha value
            pixels[pixelIndex] = SDL_MapRGBA(format, r, g, b, newAlpha);
        }
    }

    SDL_UnlockSurface(portionSurface);

    // Create the texture from the modified surface
    _width = portionSurface->w;
    _height = portionSurface->h;
	_x = rect.x;
	_y = rect.y;

    _texture = SDL_CreateTextureFromSurface(renderer, portionSurface);
    SDL_FreeSurface(portionSurface);
    if (!_texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
        assert(false);
    }
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor) {
	constructFromText(renderer, text, font, &fgColor);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor, const SDL_Color &bgColor) {
	constructFromText(renderer, text, font, &fgColor, &bgColor);
}

void Texture::constructFromText(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color *fgColor, const SDL_Color *bgColor) {

	assert(renderer != nullptr);
	_renderer = renderer;

	SDL_Surface *textSurface =
			bgColor == nullptr ?
					font.renderText(text, *fgColor) :
					font.renderText(text, *fgColor, *bgColor);
	assert(textSurface != nullptr);

	_width = textSurface->w;
	_height = textSurface->h;

	_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	assert(_texture != nullptr);
}
