#pragma once
#include <SDL.h>
#include "src/graphics/texture.h"
#include "src/core/common/bounding_box.h"
#include "src/graphics/color.h"
#include "src/io/window.h"

class Renderer {
    SDL_Renderer* handle;

public:

    explicit Renderer(Window& window);
    ~Renderer();

    void render(Texture& texture, const BoundingBox2f& box);
    void render(const Color& color, const BoundingBox2f& box);
    void clear(const Color& color);
    void updateFrame();

    [[nodiscard]] SDL_Renderer* get_handle();

private:
    void set_drawing_color(const Color& color);

    static SDL_Rect convert_to_sdl_rect(const BoundingBox2f& box);
};



