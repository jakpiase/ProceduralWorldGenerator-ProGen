#pragma once
#include "src/core/scene.h"
#include <memory>
#include <src/io/renderer.h>
#include "src/io/window.h"

class Game {
    bool is_running;
    std::unique_ptr<Scene> mainScene;

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



