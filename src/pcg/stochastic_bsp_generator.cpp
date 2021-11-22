#include <iostream>
#include "src/pcg/utils/grid_to_entity_parser.h"
#include "src/pcg/stochastic_bsp_generator.h"
#include "src/pcg/utils/grid_utils.h"


void StochasticBSPGenerator::run(Scene& scene) {
    DLOG(INFO) << "StochasticBSPGenerator running";

    split_space(bounding_box);
    GridToEntityParser(*grid, scene).parse();

    DLOG(INFO) << "StochasticBSPGenerator finished";
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

void StochasticBSPGenerator::split_space(const BoundingBox2i& bounding_box) {
    if (can_be_split(bounding_box)) {
        std::pair<BoundingBox2i, BoundingBox2i> new_bounding_boxes = calculate_new_bounding_boxes(bounding_box);
        DLOG(INFO) << "Splitting space from " << bounding_box << " into " << new_bounding_boxes.first << " and "
                   << new_bounding_boxes.second;

        split_space(new_bounding_boxes.first);
        split_space(new_bounding_boxes.second);
        connect_spaces_with_corridor(new_bounding_boxes.first, new_bounding_boxes.second);
    } else {
        generate_room(bounding_box);
    }
}

#pragma clang diagnostic pop

std::pair<BoundingBox2i, BoundingBox2i> StochasticBSPGenerator::calculate_new_bounding_boxes(const BoundingBox2i& box) {
    const Point2i first_top_left = box.get_top_left();
    const Point2i second_bottom_right = box.get_bottom_right();
    const bool isSplitHorizontal = get_split_orientation(box);

    Point2i first_bottom_right, second_top_left;

    if (isSplitHorizontal) {
        int split_height = box.get_top() + MINIMAL_CHUNK_SIZE - 1 +
                           static_cast<int>(rng.random(box.get_height() - 2 * MINIMAL_CHUNK_SIZE + 1));

        first_bottom_right = Point2i(box.get_right(), split_height);
        second_top_left = Point2i(box.get_left(), split_height + 1);
    } else {
        int split_width = box.get_left() + MINIMAL_CHUNK_SIZE - 1 +
                          static_cast<int>(rng.random(box.get_width() - 2 * MINIMAL_CHUNK_SIZE + 1));

        first_bottom_right = Point2i(split_width, box.get_bottom());
        second_top_left = Point2i(split_width + 1, box.get_top());
    }

    return std::make_pair(BoundingBox2i(first_top_left, first_bottom_right),
                          BoundingBox2i(second_top_left, second_bottom_right));
}


void StochasticBSPGenerator::generate_room(const BoundingBox2i& bounding_box) {
    const BoundingBox2i box = bounding_box.shrunk_by(CHUNK_PADDING);

    //KEEP_IN_MIND: BBOX of width n has represents n+1 columns on grid (0, 1, ..., n)
    const int min_width = std::max(MINIMAL_ROOM_SIZE - 1, (box.get_width() + 1) / 2);
    const int min_height = std::max(MINIMAL_ROOM_SIZE - 1, (box.get_height() + 1) / 2);

    Dimensions2i room_dimensions;
    if (box.get_width() > box.get_height()) {
        int height = rng.random(min_height, box.get_height() + 1);

        int max_width = std::min(static_cast<int>(height * ROOM_PROPORTION), box.get_width() + 1);
        int width = rng.random(height, max_width);

        room_dimensions = Dimensions2i(width, height);
    } else {
        int width = rng.random(min_width, box.get_width() + 1);

        int max_height = std::min(static_cast<int>(width * ROOM_PROPORTION), box.get_height() + 1);
        int height = rng.random(width, max_height);

        room_dimensions = Dimensions2i(width, height);
    }

    /*Point2i room_left_top = Point2i(
            box.get_left() + box.get_width() / 2 -
            rng.random(std::max(room_dimensions.width - box.get_width() / 2, 0), std::min(box.get_width() + 1/ 2, room_dimensions.width) + 1),
            box.get_top() + box.get_height() / 2 -
            rng.random(std::max(room_dimensions.height - box.get_height() / 2, 0), std::min(box.get_height() + 1/ 2, room_dimensions.height) + 1));*/
    int half_width = (box.get_width() + 1)/2;
    int half_height = (box.get_height() + 1)/2;


    Point2i room_left_top = Point2i(
        room_dimensions.width <= half_width ?
            box.get_left() + half_width - rng.random(room_dimensions.width + 1)
            : box.get_left() + rng.random(box.get_width() - room_dimensions.width + 1),
        room_dimensions.height <= half_height ?
            box.get_top() + half_height - rng.random(room_dimensions.height + 1)
            : box.get_top() + rng.random(box.get_height() - room_dimensions.height + 1)
    );


    BoundingBox2i room_box = BoundingBox2i::from_dimensions(room_left_top, room_dimensions);
    grid->fill(room_box, GridElement::ROOM);

    DLOG(INFO) << "Chunk of" << bounding_box << " generated room of size" << room_box;
}

bool StochasticBSPGenerator::can_be_split(const BoundingBox2i& bounding_box) {
    if (maximum_splitting)
        return can_be_split_horizontally(bounding_box) || can_be_split_vertically(bounding_box);
    else
        return can_be_split_horizontally(bounding_box) && can_be_split_vertically(bounding_box);
}

bool StochasticBSPGenerator::can_be_split_vertically(const BoundingBox2i& bounding_box) {
    return bounding_box.get_width() >= 2 * MINIMAL_CHUNK_SIZE;
}

bool StochasticBSPGenerator::can_be_split_horizontally(const BoundingBox2i& bounding_box) {
    return bounding_box.get_height() >= 2 * MINIMAL_CHUNK_SIZE;
}

// returns true if horizontal
bool StochasticBSPGenerator::get_split_orientation(const BoundingBox2i& bounding_box) {
    if (maximum_splitting) {
        if (can_be_split_horizontally(bounding_box) && can_be_split_vertically(bounding_box))
            return rng.random_bool();
        else
            return can_be_split_horizontally(bounding_box);
    }

    return rng.random_bool();
}

void StochasticBSPGenerator::connect_spaces_with_corridor(const BoundingBox2i& a, const BoundingBox2i& b) {
    DLOG(INFO) << "Connecting " << a << " and " << b << " with middles in " << a.get_middle() << " and "
               << b.get_middle();
    GridUtils::create_straight_corridor(*grid, a.get_middle(), b.get_middle());
}
