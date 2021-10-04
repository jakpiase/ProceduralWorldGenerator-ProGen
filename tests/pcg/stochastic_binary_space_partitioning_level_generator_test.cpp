#include <gtest/gtest.h>
#include "src/pcg/stochastic_binary_space_partitioning_level_generator.h"



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

                ASSERT_FALSE(BoundingBox(first_transform.position, first_physics.dimensions).collides_with(
                                           BoundingBox(second_transform.position, second_physics.dimensions)));          
            }
        }
    }
}
