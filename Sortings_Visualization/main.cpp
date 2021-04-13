#include "mainwindow.h"

#include <QApplication>

#include <vector>
#include <iostream>
#include <algorithm>

#include "Sorting.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

void TestSorting(Sortings::Sorting<std::vector<int>>& sorting, uint32_t number){
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

    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<int>random_v;
    for(uint32_t i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.begin(), copy_random_v.end());
    sorting.Sort(random_v.begin(), random_v.end());
    CHECK(random_v == copy_random_v);

    std::vector<int>random_vv;
    for(uint32_t i=0;i<number; i++){
        random_vv.push_back(mersenne() % number);
    }
    auto copy_random_vv = random_vv;
    std::sort(copy_random_vv.begin(), copy_random_vv.end(), [](int x, int y){ return x > y;});
    sorting.Sort(random_vv.begin(), random_vv.end(), [](int x, int y){ return x > y;});
    CHECK(random_vv == copy_random_vv);

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
    TestSorting(bubble, 1000);
    Sortings::InsertionSort<std::vector<int>>insertion;
    TestSorting(insertion, 1000);
    Sortings::SelectionSort<std::vector<int>>selection;
    TestSorting(selection, 1000);
    /*Sortings::CycleSort<std::vector<int>>cycle;
    TestSorting(cycle);
    Sortings::ShakerSort<std::vector<int>>shaker;
    TestSorting(shaker);
    Sortings::CombSort<std::vector<int>>comb;
    TestSorting(comb);
    Sortings::GnomeSort<std::vector<int>>gnome;
    TestSorting(gnome);
    Sortings::OddEvenSort<std::vector<int>>oddEven;
    TestSorting(oddEven);*/
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
