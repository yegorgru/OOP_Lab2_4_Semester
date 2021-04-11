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
    m_VisualizeQueue.push_back({Sortings::Operation::END, 0, 0, 0, 0});
    m_CurPos = 0;
    timeLine = new QTimeLine(m_VisualizeQueue.size()*100);
    timeLine->setFrameRange(0, m_VisualizeQueue.size());
    connect (timeLine,&QTimeLine::frameChanged,this,&Visualizer::PlayItem);
    //connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(&Visualizer::PlayItem));
    timeLine->start();
}

void Visualizer::PlayItem(){
    if(m_CurPos > 0){
        auto& lastItem = m_VisualizeQueue[m_CurPos-1];
        if(lastItem.operation == Sortings::Operation::ACCESS){
            m_Rects[lastItem.first]->setBrush(QBrush(Qt::red));
        }
        else {
            m_Rects[lastItem.first]->setBrush(QBrush(Qt::red));
            m_Rects[lastItem.second]->setBrush(QBrush(Qt::red));
        }
    }
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
        m_Rects[item.first]->setRect(item.first*m_Width, 10,
                                     m_Width, item.firstHeight);

        m_Rects[item.second]->setBrush(QBrush(Qt::green));
        m_Rects[item.second]->setRect(item.second*m_Width, 10,
                                     m_Width, item.secondHeight);
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
    m_Width = double(m_Scene->width())/m_Data.size();
    m_Rects.clear();
    for(size_t i=0;i<m_Data.size();i++){
        double height = double(m_Data[i])/m_MaxValue*m_Scene->height()*0.9;
        QGraphicsRectItem* cur =
                new QGraphicsRectItem(m_Rects.size()*m_Width,10,
                                      m_Width, height);
        cur->setBrush(QBrush(Qt::red));
        m_Rects.push_back(cur);
        m_Scene->addItem(m_Rects.back());
    }
    m_Scene->update();
}

void Visualizer::UpdateScene(QSize size){
    m_Scene->setSceneRect ( 0,0,size.width()*0.95, size.height()*0.95);

    m_Width = double(m_Scene->width())/m_Rects.size();
    for(size_t i=0;i<m_Rects.size();i++){
        double height = double(m_Data[i])/m_MaxValue*m_Scene->height()*0.9;
        m_Rects[i]->setRect(i*m_Width,10, m_Width, height);
    }
    m_Scene->update();
}

void Visualizer::SetMaxValue(int value){
    m_MaxValue = value;
}
