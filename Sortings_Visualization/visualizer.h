#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <vector>

#include "Sorting.h"

class Visualizer
{
public:
    Visualizer(std::vector<int>& data);

    void Visualize(Sortings::Operation operation, size_t position);

    void FormScene(QSize size);
    void UpdateScene(QSize size);

    void SetMaxValue(int value);

    QGraphicsScene* GetScene();
private:
    QGraphicsScene* m_Scene;
    std::vector<QGraphicsRectItem*>m_Rects;
    std::vector<int>&m_Data;
    int m_MaxValue;
};
