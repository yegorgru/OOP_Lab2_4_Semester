#pragma once

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>

#include <vector>

#include "Sorting.h"

class Visualizer : public QObject
{
    Q_OBJECT

public:
    Visualizer(std::vector<int>& data);

    bool Visualize(Sortings::Operation operation, size_t first, size_t second = INT_MAX);

    void FormScene(QSize size);
    void UpdateScene(QSize size);

    void SetMaxValue(int value);

    void Play(int speedOfVisualization);
    void PlayItem();

    void ClearQueue();

    QGraphicsScene* GetScene();
    QTimer* GetTimer();

signals:
    void Sorted();
private:
    struct VisualizeItem{
        Sortings::Operation operation;
        size_t first;
        size_t second;
        double firstHeight;
        double secondHeight;
    };

    QGraphicsScene* m_Scene;
    std::vector<QGraphicsRectItem*>m_Rects;
    std::vector<int>&m_Data;
    int m_MaxValue;
    double m_Width;
    size_t m_CurPos;

    std::vector<VisualizeItem>m_VisualizeQueue;
    QTimer *m_Timer;
};
