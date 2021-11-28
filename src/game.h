#pragma once
#include <memory>
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/graphics/renderer.h"
#include "src/io/window.h"
#include "src/pcg/utils/room_content_provider.h"

class Game {
    bool is_running;
    std::unique_ptr<Scene> main_scene;
    std::shared_ptr<Window> window;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<RoomContentProvider> room_content_provider;

public:
    static constexpr int WINDOW_WIDTH = 500;
    static constexpr int WINDOW_HEIGHT = 500;

    Game(std::shared_ptr<RoomContentProvider> room_content_provider);
    ~Game();
    int run();

private:
    void generate_content();
    void register_singletons();

    void process_events();
    void update();

};



