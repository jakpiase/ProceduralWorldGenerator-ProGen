#pragma once
#include <memory>
#include "src/io/window.h"
#include "src/io/renderer.h"

struct locator {
    static std::shared_ptr<Window> window;
    static std::shared_ptr<Renderer> renderer;
};



