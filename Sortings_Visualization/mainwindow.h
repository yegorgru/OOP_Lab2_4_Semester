#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include <vector>

#include "Sorting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:


    void on_SortButton_clicked();

private:
    void VisualizeChanges(Sortings::Operation operation, size_t pos){
        if(operation == Sortings::Operation::ACCESS){

        }
        else if(operation == Sortings::Operation::COMPARISON){

        }
        else if(operation == Sortings::Operation::CHANGE){

        }
    }

    Ui::MainWindow *ui;

    QGraphicsScene *m_Scene;

    Sortings::Sorting<std::vector<int>>* m_Sorting;

    std::vector<QGraphicsRectItem*>m_Rects;
    std::vector<int>m_Numbers;
};
