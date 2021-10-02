#include <glog/logging.h>
#include "src/game.h"

Game::Game()
        : is_running(true) {
    LOG(INFO) << "Starting ProGen";


    window = std::make_unique<Window>("ProGen", BOARD_WIDTH, BOARD_HEIGHT);
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
    constexpr int GRID_WIDTH = BOARD_WIDTH / Grid::ELEMENT_SIZE;
    constexpr int GRID_HEIGHT = BOARD_HEIGHT / Grid::ELEMENT_SIZE;
    StochasticBinarySpacePartitioningLevelGenerator level_generator(BoundingBox2i::from_zero(GRID_WIDTH, GRID_HEIGHT));
    level_generator.run(*main_scene);
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
