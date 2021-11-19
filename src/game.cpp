#include <glog/logging.h>
#include <entt/locator/locator.hpp>
#include <src/pcg/utils/grid_to_entity_parser.h>
#include "src/pcg/agent_generators/agent_generator.h"
#include "src/pcg/agent_generators/agents/look_ahead/look_ahead_agent.h"
#include "src/pcg/agent_generators/agents/look_ahead/basic_look_ahead_agent.h"
#include "src/pcg/agent_generators/agents/look_ahead/cross_corridor_look_ahead_agent.h"
#include "src/game.h"

Game::Game()
        : is_running(true) {
    LOG(INFO) << "Starting ProGen";


    window = std::make_shared<Window>("ProGen", WINDOW_WIDTH, WINDOW_HEIGHT);
    renderer = std::make_shared<Renderer>(*window);
    register_singletons();
    main_scene = std::make_unique<Scene>();
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
    LinearNumberGenerator linear_number_generator(3);
    AgentGenerator level_generator(std::make_unique<CrossCorridorLookAheadAgent>(), BoundingBox2i::from_zero(100, 100), linear_number_generator);
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

void Game::register_singletons() {
    entt::service_locator<Renderer>::set(renderer);
    entt::service_locator<Window>::set(window);
    entt::service_locator<EntityCreator>::set<EntityCreatorImpl>();
}
