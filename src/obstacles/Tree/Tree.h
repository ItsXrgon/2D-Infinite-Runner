#ifndef TREEOBSTACLE_H
#define TREEOBSTACLE_H

#include "../Obstacle.h"
#include "../../utils/rect.h"

class Tree : public Obstacle {
public:
    Tree(float startY);

    void draw() const override;
    Rect getBoundingBox() const override;
};

#endif