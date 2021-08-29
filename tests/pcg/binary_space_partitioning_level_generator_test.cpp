#include "gtest/gtest.h"
#include "src/pcg/binary_space_partitioning_level_generator.h"

bool rooms_overlap(const BoundingBox& first, const BoundingBox& second) {
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

TEST(BSP_level_generator_tests, BSP_level_generator_no_overlapping_rooms_test) {
    std::unique_ptr<Scene> main_scene = std::make_unique<Scene>();
    BinarySpacePartitioningLevelGenerator level_generator(BoundingBox::from_zero(800.0, 800.0));
    level_generator.run(*main_scene);
    main_scene->update();

    auto view = main_scene->get_registry().view<PhysicsComponent>();

    for(int i=0; i<view.size(); ++i) {
        for(int j=0; j<view.size(); ++j) {
            if(i != j) {
                PhysicsComponent& first = view.get<PhysicsComponent>(view[i]);
                PhysicsComponent& second = view.get<PhysicsComponent>(view[j]);
                ASSERT_FALSE(rooms_overlap(first.bounding_box, second.bounding_box));
            }
        }
    }
}
