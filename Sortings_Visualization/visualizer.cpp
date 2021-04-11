#include "visualizer.h"

Visualizer::Visualizer(QGraphicsScene& scene):
    m_Scene(scene) {}

void Visualizer::Visualize(Sortings::Operation operation, size_t position){
    if(operation == Sortings::Operation::COMPARISON){
        m_Rects[position]->setBrush(QBrush(Qt::blue));
    }
    else if(operation == Sortings::Operation::ACCESS){
        m_Rects[position]->setBrush(QBrush(Qt::yellow));
    }
    else if(operation == Sortings::Operation::CHANGE){
        m_Rects[position]->setBrush(QBrush(Qt::green));
    }
    m_Scene.update();
}

std::vector<QGraphicsRectItem*>& Visualizer::GetRects(){
    return m_Rects;
}
