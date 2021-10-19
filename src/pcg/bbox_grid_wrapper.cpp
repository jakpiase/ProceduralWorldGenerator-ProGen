#include "src/pcg/bbox_grid_wrapper.h"

BBoxGridWrapper::BBoxGridWrapper(Grid &grid) :grid(grid) {}

std::vector<GridBox>::iterator BBoxGridWrapper::begin() {
    return grid_boxes.begin();
}

std::vector<GridBox>::iterator BBoxGridWrapper::end() {
    return grid_boxes.end();
}

void BBoxGridWrapper::add(const BoundingBox2i &box, GridElement element) {
    grid_boxes.emplace_back(box, element);
}
