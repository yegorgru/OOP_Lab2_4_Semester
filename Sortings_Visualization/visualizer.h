#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <vector>

class Visualizer
{
public:
    Visualizer(QGraphicsScene& scene);

    std::vector<QGraphicsRectItem*>& GetRects();
private:
    QGraphicsScene& m_Scene;
    std::vector<QGraphicsRectItem*>m_Rects;
};
