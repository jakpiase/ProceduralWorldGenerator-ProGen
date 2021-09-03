#include <glog/logging.h>
#include "src/pcg/simple_generators/simple_level_generator.h"
#include "src/game.h"
#include "src/core/entity.h"

Game::Game()
        : is_running(true) {
    LOG(INFO) << "Starting ProGen";


    window = std::make_unique<Window>("ProGen", 640, 480);
    renderer = std::make_unique<Renderer>(*window);
    main_scene = std::make_unique<Scene>(*renderer);
}

Game::~Game() {
    LOG(INFO) << "ProGen exited succesfully";
}

int Game::run() {
    generate_content();

    while (is_running) {
        update();
        SDL_Delay(1000 / 30);
    }

    return 0;
}

void Game::generate_content() {
    SimpleLevelGenerator levelGenerator(BoundingBox::from_zero(200.0, 200.0));
    levelGenerator.run(*main_scene);
}

void Game::update() {
    main_scene->update();
    renderer->updateFrame();
    renderer->clear(Colors::Black);

    process_events();
}

void Game::process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        }
    }
}

