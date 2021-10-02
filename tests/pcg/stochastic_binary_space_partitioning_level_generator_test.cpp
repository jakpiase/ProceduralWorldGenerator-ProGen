#include <gtest/gtest.h>
#include "src/pcg/stochastic_binary_space_partitioning_level_generator.h"

bool rooms_overlap(const BoundingBox2i& first, const BoundingBox2i& second) {
    // skip comparing walls, only floors are meaningful
    if (first.get_top_left().x == first.get_bottom_right().x ||
        first.get_top_left().y == first.get_bottom_right().y ||
        second.get_top_left().x == second.get_bottom_right().x ||
        second.get_top_left().y == second.get_bottom_right().y) return false;

    return !(first.get_top_left().x > second.get_bottom_right().x || 
           second.get_top_left().x > first.get_bottom_right().x || 
           first.get_top_left().y > second.get_bottom_right().y || 
           second.get_top_left().y > first.get_bottom_right().y);
}

TEST(SBSP_level_generator_tests, SBSP_level_generator_no_overlapping_rooms_test) {
    auto window = std::make_unique<Window>("ProGen", 640, 480);
    auto renderer = std::make_unique<Renderer>(*window);
    auto main_scene = std::make_unique<Scene>(*renderer);

    StochasticBinarySpacePartitioningLevelGenerator level_generator(BoundingBox2i::from_zero(640, 480));
    level_generator.run(*main_scene);
    main_scene->update();

    auto view = main_scene->get_registry().view<PhysicsComponent, TransformationComponent>();

    for (auto first_entity : view) {
        for (auto second_entity : view) {
            if (first_entity != second_entity) {
                PhysicsComponent& first_physics = view.get<PhysicsComponent>(first_entity);
                PhysicsComponent& second_physics = view.get<PhysicsComponent>(second_entity);
                TransformationComponent& first_transform = view.get<TransformationComponent>(first_entity);
                TransformationComponent& second_transform = view.get<TransformationComponent>(second_entity);

                ASSERT_FALSE(rooms_overlap(BoundingBox(first_transform.position, first_physics.dimensions),
                                           BoundingBox(second_transform.position, second_physics.dimensions)));          
            }
        }
    }
}
