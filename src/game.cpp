#include <glog/logging.h>
#include "src/pcg/agent_generators/agent_generator.h"
#include "src/pcg/agent_generators/agents/look_ahead_agent.h"
#include "src/game.h"

Game::Game()
        : is_running(true) {
    LOG(INFO) << "Starting ProGen";


    window = std::make_unique<Window>("ProGen", WINDOW_WIDTH, WINDOW_HEIGHT);
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
    LinearNumberGenerator linear_number_generator;
    AgentGenerator level_generator(std::make_unique<LookAheadAgent>(), BoundingBox2i::from_zero(100, 100), linear_number_generator);
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
