#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <vector>

#include "Sorting.h"

class Visualizer
{
public:
    Visualizer(QGraphicsScene& scene);

    void Visualize(Sortings::Operation operation, size_t position);

    std::vector<QGraphicsRectItem*>& GetRects();
private:
    QGraphicsScene& m_Scene;
    std::vector<QGraphicsRectItem*>m_Rects;
};
