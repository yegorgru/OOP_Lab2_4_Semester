#pragma once

#include <QMainWindow>
#include <QGraphicsScene>

#include <vector>
#include <random>

#include "Sorting.h"
#include "visualizer.h"

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
    void showEvent(QShowEvent* event);

private slots:

    void on_SortButton_clicked();

private:
    void VisualizeChanges(Sortings::Operation operation, size_t pos);
    void FormRandomScene(int numberOfRectangles);

    Ui::MainWindow *ui;

    QGraphicsScene *m_Scene;

    Visualizer m_Visualizer;

    Sortings::Sorting<std::vector<int>,Visualizer>* m_Sorting;

    std::vector<int>m_Numbers;
    int m_MaxValue;

    std::random_device rd;
    std::mt19937 mersenne;
};
