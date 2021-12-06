#include <glog/logging.h>
#include <entt/locator/locator.hpp>
#include "src/pcg/utils/grid_to_entity_parser.h"
#include "src/pcg/utils/registry_utils.h"
#include "src/pcg/stochastic_bsp_generator.h"
#include "src/pcg/agent_generators/agent_generator.h"
#include "src/pcg/agent_generators/agents/look_ahead/look_ahead_agent.h"
#include "src/pcg/agent_generators/agents/look_ahead/cross_corridor_look_ahead_agent.h"
#include "src/pcg/agent_generators/agents/look_ahead/recurring_look_ahead_agent.h"
#include "src/pcg/quests/templates/quest_templates.h"
#include "src/game.h"


Game::Game(std::shared_ptr<RoomContentProvider> room_content_provider)
        : is_running(true) {
    LOG(INFO) << "Starting ProGen";

    this->room_content_provider = room_content_provider;
    window = std::make_shared<Window>("ProGen", WINDOW_WIDTH, WINDOW_HEIGHT);
    renderer = std::make_shared<Renderer>(*window);
    register_singletons();
    main_scene = std::make_unique<Scene>();
    entt::service_locator<RegistryUtils>::ref().set_registry(&main_scene->get_registry());
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
    //TOP for SBSP: 2, 10
    LinearNumberGenerator linear_number_generator(5831214);
    AgentGenerator level_generator(std::make_unique<RecurringLookAheadAgent>(), BoundingBox2i::from_zero(100, 100),
                                   linear_number_generator);
    //StochasticBSPGenerator level_generator(BoundingBox2i::from_zero(100, 100), linear_number_generator);
    level_generator.run(*main_scene);

    RegistryUtils& registry_utils = entt::service_locator<RegistryUtils>::ref();

    Quests::Templates::EquipmentTakeover equipment_takeover;
    auto equipment_takeover_result = equipment_takeover.create_node(registry_utils, linear_number_generator);
    if (equipment_takeover_result) {
        equipment_takeover_result->post_construct();
        equipment_takeover_result->print_description(0);
    }

    Quests::Templates::HolyBath holy_bath;
    auto holy_bath_result = holy_bath.create_node(registry_utils, linear_number_generator);
    if (holy_bath_result) {
        holy_bath_result->post_construct();
        holy_bath_result->print_description(0);
    }

    Quests::Templates::MonumentMystery monument_mystery;
    auto monument_mystery_result = monument_mystery.create_node(registry_utils, linear_number_generator);
    if (monument_mystery_result) {
        monument_mystery_result->post_construct();
        monument_mystery_result->print_description(0);
    }

    Quests::Templates::DesecratedStatue desecrated_statue;
    auto desecrated_statue_result = desecrated_statue.create_node(registry_utils, linear_number_generator);
    if (desecrated_statue_result) {
        monument_mystery_result->post_construct();
        desecrated_statue_result->print_description(0);

    }

    std::cout.flush();
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
    entt::service_locator<RegistryUtils>::set<RegistryUtils>();
    entt::service_locator<EntityCreator>::set<EntityCreatorImpl>();
    entt::service_locator<RoomContentProvider>::set(room_content_provider);
}
