#include "visualizer.h"

Visualizer::Visualizer(QGraphicsScene& scene):
    m_Scene(scene)
{

}

std::vector<QGraphicsRectItem*>& Visualizer::GetRects(){
    return m_Rects;
}
