#pragma once
#include "src/pcg/simple_generators/simple_level_generator.h"
#include "src/core/locator.h"
#include "game.h"
#include <glog/logging.h>
#include "src/core/entity.h"

std::shared_ptr<Window> locator::window;
std::shared_ptr<Renderer> locator::renderer;

Game::Game()
        : is_running(true) {
    LOG(INFO) << "Starting ProGen";

    register_singletons();
    mainScene = std::make_unique<Scene>();
}

Game::~Game() {
    locator::renderer = nullptr;
    locator::window = nullptr;
    LOG(INFO) << "ProGen exited succesfully";
}

void Game::register_singletons() {
    locator::window = std::make_shared<Window>("ProGen", 640, 480);
    locator::renderer = std::make_shared<Renderer>(*locator::window);
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
    levelGenerator.run(*mainScene);
}

void Game::update() {
    mainScene->update();
    locator::renderer->updateFrame();
    locator::renderer->clear(Colors::Black);

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

