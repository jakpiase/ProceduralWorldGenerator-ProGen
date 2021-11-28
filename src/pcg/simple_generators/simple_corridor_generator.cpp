#include <sstream>
#include <cassert>
#include "src/core/components/graphics_component.h"
#include "src/core/components/transformation_component.h"
#include "src/core/components/description_component.h"
#include "src/core/scene.h"
#include "src/core/entity.h"
#include "src/pcg/simple_generators/simple_corridor_generator.h"

void SimpleCorridorGenerator::run(Scene& scene) {
    DLOG(INFO) << "SimpleCorridorGenerator running";

    const BoundingBox2i corridor_box = create_corridor_box();

    std::stringstream corridor_description_stream;
    corridor_description_stream << "Corridor from " << corridor_box.get_top_left() << " to "
                                << corridor_box.get_top_right();

    Entity corridor = scene.create_entity();
    corridor.add_component<DescriptionComponent>(corridor_description_stream.str());
    corridor.add_component<TransformationComponent>(corridor_box.get_top_left());
    corridor.add_component<GraphicsComponent>(Colors::Blue, corridor_box.get_dimensions().cast<int>());

    DLOG(INFO) << "SimpleCorridorGenerator finished";
}

BoundingBox2i SimpleCorridorGenerator::create_corridor_box() const {
    assert((alignment == SimpleCorridorAlignment::Horizontal ? bounding_box.get_width() >= CORRIDOR_WIDTH :
            bounding_box.get_height() >= CORRIDOR_WIDTH));

    Point middle = bounding_box.get_middle();
    if (alignment == SimpleCorridorAlignment::Horizontal) {
        return BoundingBox(
                middle.shifted_by(-bounding_box.get_width() / 2.0f, -CORRIDOR_WIDTH / 2.0f),
                middle.shifted_by(bounding_box.get_width() / 2.0f, CORRIDOR_WIDTH / 2.0f)
        );
    } else {
        return BoundingBox(
                middle.shifted_by(-CORRIDOR_WIDTH / 2.0f, -bounding_box.get_height() / 2.0f),
                middle.shifted_by(CORRIDOR_WIDTH / 2.0f, bounding_box.get_height() / 2.0f)
        );
    }
}
