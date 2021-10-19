#pragma once
#include <vector>
#include "src/pcg/grid.h"

struct GridBox{
    BoundingBox2i box;
    GridElement element;
};

class BBoxGridWrapper {
    Grid& grid;
    std::vector<GridBox> grid_boxes;

public:
    BBoxGridWrapper(Grid& grid);

    void add(const BoundingBox2i& box, GridElement element);

    std::vector<GridBox>::iterator begin();

    std::vector<GridBox>::iterator end();
};
