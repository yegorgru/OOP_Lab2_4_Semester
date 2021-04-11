#include "visualizer.h"

#include <QTimeLine>

#include <iostream>

Visualizer::Visualizer(std::vector<int>& data):
    m_Scene(new QGraphicsScene),
    m_Data(data),
    m_CurPos(0){}

void Visualizer::Visualize(Sortings::Operation operation, size_t first, size_t second){
    m_VisualizeQueue.push_back({operation, first, second,
                                double(m_Data[first])/m_MaxValue*m_Scene->height()*0.9,
                                double(m_Data[second])/m_MaxValue*m_Scene->height()*0.9});
    /*if(operation == Sortings::Operation::COMPARISON){
        m_Rects[position]->setBrush(QBrush(Qt::blue));
    }
    else if(operation == Sortings::Operation::ACCESS){
        m_Rects[position]->setBrush(QBrush(Qt::yellow));
    }
    else if(operation == Sortings::Operation::CHANGE){
        m_Rects[position]->setBrush(QBrush(Qt::green));
        double height = double(m_Data[position])/m_MaxValue*m_Scene->height()*0.9;
        auto rect = m_Rects[position]->boundingRect();
        m_Rects[position]->setRect(rect.x(), 10, rect.width(), height);
    }
    m_Scene->update();*/
}

void Visualizer::Play(){
    m_CurPos = 0;
    timeLine = new QTimeLine(m_VisualizeQueue.size()*100);
    timeLine->setFrameRange(0, m_VisualizeQueue.size());
    connect (timeLine,&QTimeLine::frameChanged,this,&Visualizer::PlayItem);
    //connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(&Visualizer::PlayItem));
    timeLine->start();
}

void Visualizer::PlayItem(){
    std::cout<<m_CurPos<<std::endl;
    auto& item = m_VisualizeQueue[m_CurPos++];
    if(item.operation == Sortings::Operation::COMPARISON){
        m_Rects[item.first]->setBrush(QBrush(Qt::blue));
        m_Rects[item.second]->setBrush(QBrush(Qt::blue));
    }
    else if(item.operation == Sortings::Operation::ACCESS){
        m_Rects[item.first]->setBrush(QBrush(Qt::yellow));
    }
    else if(item.operation == Sortings::Operation::CHANGE){
        m_Rects[item.first]->setBrush(QBrush(Qt::green));
        auto firstRect = m_Rects[item.first]->boundingRect();
        m_Rects[item.first]->setRect(firstRect.x(), 10,
                                     firstRect.width(), item.firstHeight);

        m_Rects[item.second]->setBrush(QBrush(Qt::green));
        auto secondRect = m_Rects[item.second]->boundingRect();
        m_Rects[item.second]->setRect(secondRect.x(), 10,
                                     secondRect.width(), item.secondHeight);
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
                new QGraphicsRectItem(m_Rects.size()*width,10,
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
        m_Rects[i]->setRect(i*width,10, width, height);
    }
    m_Scene->update();
}

void Visualizer::SetMaxValue(int value){
    m_MaxValue = value;
}
