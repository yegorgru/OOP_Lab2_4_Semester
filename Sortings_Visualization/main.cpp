#include "mainwindow.h"

#include <QApplication>

#include <vector>
#include <iostream>
#include <algorithm>

#include "Sorting.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

void TestSortingBasic(Sortings::Sorting<std::vector<int>>& sorting,
                      std::function<bool (int,int)> cmp =
                    [](int x, int y) -> bool { return x < y; }){
    std::vector<int> v = {5,2,1,4,3};
    std::vector<int> copy_v = v;
    sorting.Sort(v.begin(), v.end(), cmp);
    std::sort(copy_v.begin(), copy_v.end(), cmp);
    CHECK(v == copy_v);

    /*std::vector<int> vv = {5,2,1,4,3};
    std::vector<int> copy_vv = vv;
    sorting.Sort(vv.begin(), vv.end(), [](int x, int y){ return x > y;});
    std::sort(copy_vv.begin(), copy_vv.end(), [](int x, int y){ return x > y;});
    CHECK(vv == copy_vv);*/
}

void TestSortingRandom(Sortings::Sorting<std::vector<int>>& sorting, uint32_t number,
                       std::function<bool (int,int)> cmp =
                     [](int x, int y) -> bool { return x < y; }){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<int>random_v;
    for(uint32_t i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.begin(), copy_random_v.end(), cmp);
    sorting.Sort(random_v.begin(), random_v.end(), cmp);
    CHECK(random_v == copy_random_v);

    /*std::vector<int>random_vv;
    for(uint32_t i=0;i<number; i++){
        random_vv.push_back(mersenne() % number);
    }
    auto copy_random_vv = random_vv;
    std::sort(copy_random_vv.begin(), copy_random_vv.end(), [](int x, int y){ return x > y;});
    sorting.Sort(random_vv.begin(), random_vv.end(), [](int x, int y){ return x > y;});
    CHECK(random_vv == copy_random_vv);*/

    /*for(auto i:v){
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
    for(auto i:vv){
        std::cout << i << std::endl;
    }*/
}

void TestSortingAlmostSorted(Sortings::Sorting<std::vector<int>>& sorting, uint32_t number,
                             std::function<bool (int,int)> cmp =
                           [](int x, int y) -> bool { return x < y; }){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<int>random_v;
    for(uint32_t i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.begin(), copy_random_v.end(), cmp);
    for(uint32_t i = 0; i < number/100; i++){
        std::swap(*(copy_random_v.begin() + mersenne()%copy_random_v.size()),
                  *(copy_random_v.begin() + mersenne()%copy_random_v.size()));
    }
    sorting.Sort(copy_random_v.begin(), copy_random_v.end(), cmp);

    std::sort(random_v.begin(), random_v.end(), cmp);

    CHECK(random_v == copy_random_v);
}

void TestSortingAlmostReverseSorted(Sortings::Sorting<std::vector<int>>& sorting, uint32_t number,
                             std::function<bool (int,int)> cmp =
                           [](int x, int y) -> bool { return x < y; }){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<int>random_v;
    for(uint32_t i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.rbegin(), copy_random_v.rend(), cmp);
    for(uint32_t i = 0; i < number/100; i++){
        std::swap(*(copy_random_v.begin() + mersenne()%copy_random_v.size()),
                  *(copy_random_v.begin() + mersenne()%copy_random_v.size()));
    }
    sorting.Sort(copy_random_v.begin(), copy_random_v.end(), cmp);

    std::sort(random_v.begin(), random_v.end(), cmp);

    CHECK(random_v == copy_random_v);
}

void TestSorting(Sortings::Sorting<std::vector<int>>& sorting, uint32_t number,
                 std::function<bool (int,int)> cmp =
               [](int x, int y) -> bool { return x < y; }){
    TestSortingBasic(sorting, cmp);
    TestSortingRandom(sorting,number,cmp);
    TestSortingAlmostSorted(sorting, number, cmp);
    TestSortingAlmostReverseSorted(sorting, number, cmp);
}

TEST_CASE("testing sortings"){
    Sortings::BubbleSort<std::vector<int>>bubble;
    TestSorting(bubble, 1000);
    TestSorting(bubble, 1000, [](int x, int y){return x > y;});
    Sortings::InsertionSort<std::vector<int>>insertion;
    TestSorting(insertion, 1000);
    TestSorting(insertion, 1000, [](int x, int y){return x > y;});
    Sortings::SelectionSort<std::vector<int>>selection;
    TestSorting(selection, 1000);
    TestSorting(selection, 1000, [](int x, int y){return x > y;});
    Sortings::CycleSort<std::vector<int>>cycle;
    TestSorting(cycle, 1000);
    TestSorting(cycle, 1000, [](int x, int y){return x > y;});
    Sortings::ShakerSort<std::vector<int>>shaker;
    TestSorting(shaker, 1000);
    TestSorting(shaker, 1000, [](int x, int y){return x > y;});
    Sortings::CombSort<std::vector<int>>comb;
    TestSorting(comb, 1000);
    TestSorting(comb, 1000, [](int x, int y){return x > y;});
    Sortings::GnomeSort<std::vector<int>>gnome;
    TestSorting(gnome, 1000);
    TestSorting(gnome, 1000, [](int x, int y){return x > y;});
    Sortings::OddEvenSort<std::vector<int>>oddEven;
    TestSorting(oddEven, 1000);
    TestSorting(oddEven, 1000, [](int x, int y){return x > y;});
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
