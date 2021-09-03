#pragma once
#include <memory>
#include "src/core/scene.h"
#include "src/graphics/renderer.h"
#include "src/io/window.h"

class Game {
    bool is_running;
    std::unique_ptr<Scene> main_scene;
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;

public:
    Game();
    ~Game();
    int run();

private:
    void register_singletons();
    void generate_content();

    void process_events();
    void update();

};



