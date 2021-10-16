#ifdef USE_MOCKS

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <entt/locator/locator.hpp>
#include "src/pcg/utils/entity_creator.h"
#include "src/pcg/utils/grid_to_entity_parser.h"


class EntityCreatorMock : public EntityCreator {
public:
    MOCK_METHOD(void, create_corridor_floor, (Scene & scene, const BoundingBox2i& corridor_box), (const override));
    MOCK_METHOD(void, create_room_floor, (Scene & scene, const BoundingBox2i& room_box), (const override));
};

TEST(Grid_to_entity_parser, should_parse_entities_properly) {
    entt::service_locator<EntityCreator>::set<EntityCreatorMock>();
    EntityCreatorMock& entity_creator = entt::service_locator<EntityCreatorMock>::ref();

    Scene scene;
    Grid grid(10, 10);
    grid.fill(BoundingBox2i(Point2i(3, 2), Point2i(7, 5)), GridElement::ROOM);
    grid.fill(BoundingBox2i(Point2i(6, 1), Point2i(7, 7)), GridElement::ROOM);
    grid.fill(BoundingBox2i(Point2i(4, 6), Point2i(5, 8)), GridElement::CORRIDOR);

    GridToEntityParser grid_to_entity_parser(grid, scene);
    grid_to_entity_parser.parse();

    EXPECT_CALL(entity_creator, create_room_floor(testing::Ref(scene), BoundingBox2i(Point2i(6, 1), Point2i(7, 7))))
            .Times(1);
    EXPECT_CALL(entity_creator, create_room_floor(testing::Ref(scene), BoundingBox2i(Point2i(3, 2), Point2i(5, 5))))
            .Times(1);
    EXPECT_CALL(entity_creator, create_corridor_floor(testing::Ref(scene), BoundingBox2i(Point2i(4, 6), Point2i(5, 8))))
            .Times(1);
}

#endif
