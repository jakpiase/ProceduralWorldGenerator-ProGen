#pragma once
#include <memory>
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/graphics/renderer.h"
#include "src/io/window.h"

class Game {
    bool is_running;
    std::unique_ptr<Scene> main_scene;
    std::shared_ptr<Window> window;
    std::shared_ptr<Renderer> renderer;

public:
    static constexpr int WINDOW_WIDTH = 500;
    static constexpr int WINDOW_HEIGHT = 500;

    Game();
    ~Game();
    int run();

private:
    void generate_content();
    void register_singletons();

    void process_events();
    void update();

};



