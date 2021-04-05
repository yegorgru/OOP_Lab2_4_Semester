#include "mainwindow.h"

#include <QApplication>

#include <vector>
#include <iostream>

#include "Sorting.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::vector<int> v = {5,2,1,4,3};
    Sortings::BubbleSort<std::vector<int>>bubble;
    bubble.Sort(v.begin(), v.end());
    for(auto i : v){
        std::cout << i << std::endl;
    }

    std::vector<int> vv = {5,2,1,4,3};
    bubble.Sort(vv.begin(), vv.end(), [](int a, int b){return a > b;});
    for(auto i : vv){
        std::cout << i << std::endl;
    }
    w.show();
    return a.exec();
}
