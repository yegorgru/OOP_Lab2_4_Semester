#include "mainwindow.h"

#include <QApplication>

#include <vector>
#include <iostream>
#include <algorithm>

#include "Sorting.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

void TestSorting(Sortings::Sorting<std::vector<int>>& sorting){
    std::vector<int> v = {5,2,1,4,3};
    std::vector<int> copy_v = v;
    sorting.Sort(v.begin(), v.end());
    std::sort(copy_v.begin(), copy_v.end());
    CHECK(v == copy_v);

    std::vector<int> vv = {5,2,1,4,3};
    std::vector<int> copy_vv = vv;
    sorting.Sort(vv.begin(), vv.end(), [](int x, int y){ return x > y;});
    std::sort(copy_vv.begin(), copy_vv.end(), [](int x, int y){ return x > y;});
    CHECK(vv == copy_vv);

    /*for(auto i:v){
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
    for(auto i:vv){
        std::cout << i << std::endl;
    }*/
}

TEST_CASE("testing sortings"){
    Sortings::BubbleSort<std::vector<int>>bubble;
    TestSorting(bubble);
    Sortings::InsertionSort<std::vector<int>>insertion;
    TestSorting(insertion);
    Sortings::SelectionSort<std::vector<int>>selection;
    TestSorting(selection);
    Sortings::CycleSort<std::vector<int>>cycle;
    TestSorting(cycle);
    Sortings::ShakerSort<std::vector<int>>shaker;
    TestSorting(shaker);
    Sortings::CombSort<std::vector<int>>comb;
    TestSorting(comb);
    Sortings::GnomeSort<std::vector<int>>gnome;
    TestSorting(gnome);
    Sortings::OddEvenSort<std::vector<int>>oddEven;
    TestSorting(oddEven);
}

int main(int argc, char *argv[])
{
    doctest::Context context;
    int res = context.run();

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}
