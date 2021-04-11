#include "visualizer.h"

Visualizer::Visualizer(std::vector<int>& data):
    m_Scene(new QGraphicsScene),
    m_Data(data){}

void Visualizer::Visualize(Sortings::Operation operation, size_t position){
    if(operation == Sortings::Operation::COMPARISON){
        m_Rects[position]->setBrush(QBrush(Qt::blue));
    }
    else if(operation == Sortings::Operation::ACCESS){
        m_Rects[position]->setBrush(QBrush(Qt::yellow));
    }
    else if(operation == Sortings::Operation::CHANGE){
        m_Rects[position]->setBrush(QBrush(Qt::green));
        double height = double(m_Data[position])/m_MaxValue*m_Scene->height()*0.9;
        auto rect = m_Rects[position]->boundingRect();
        m_Rects[position]->setRect(rect.x(), rect.y(), rect.width(), height);
    }
    m_Scene->update();
}

QGraphicsScene* Visualizer::GetScene(){
    return m_Scene;
}

void Visualizer::FormScene(QSize size){
    for(auto i:m_Rects){
        delete i;
    }
    double width = double(m_Scene->width())/m_Data.size();
    m_Rects.clear();
    for(size_t i=0;i<m_Data.size();i++){
        double height = double(m_Data[i])/m_MaxValue*m_Scene->height()*0.9;
        QGraphicsRectItem* cur =
                new QGraphicsRectItem(m_Rects.size()*width,m_Scene->height()*0.95,
                                      width, height);
        cur->setBrush(QBrush(Qt::red));
        m_Rects.push_back(cur);
        m_Scene->addItem(m_Rects.back());
    }
    m_Scene->update();
}

void Visualizer::UpdateScene(QSize size){
    m_Scene->setSceneRect ( 0,0,size.width()*0.95, size.height()*0.95);

    double width = double(m_Scene->width())/m_Rects.size();
    for(size_t i=0;i<m_Rects.size();i++){
        double height = double(m_Data[i])/m_MaxValue*m_Scene->height()*0.9;
        m_Rects[i]->setRect(i*width,m_Scene->height()*0.05, width, height);
    }
    m_Scene->update();
}

void Visualizer::SetMaxValue(int value){
    m_MaxValue = value;
}
