#include "mainwindow.h"

#include <QApplication>

#include <vector>
#include <iostream>
#include <algorithm>

#include "Sorting.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

template <typename T>
void TestSortingBasic(Sortings::Sorting<std::vector<T>>& sorting,
                      std::function<bool (T,T)> cmp =
                    [](T x, T y) -> bool { return x < y; }){
    std::vector<T> v = {5,2,1,4,3};
    std::vector<T> copy_v = v;
    sorting.Sort(v.begin(), v.end(), cmp);
    std::sort(copy_v.begin(), copy_v.end(), cmp);
    CHECK(v == copy_v);

    /*std::vector<int> vv = {5,2,1,4,3};
    std::vector<int> copy_vv = vv;
    sorting.Sort(vv.begin(), vv.end(), [](int x, int y){ return x > y;});
    std::sort(copy_vv.begin(), copy_vv.end(), [](int x, int y){ return x > y;});
    CHECK(vv == copy_vv);*/
}

template <typename T>
void TestSortingRandom(Sortings::Sorting<std::vector<T>>& sorting, T number,
                       std::function<bool (T,T)> cmp =
                     [](T x, T y) -> bool { return x < y; }){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<T>random_v;
    for(T i=0;i<number; i++){
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

template <typename T>
void TestSortingAlmostSorted(Sortings::Sorting<std::vector<T>>& sorting, T number,
                             std::function<bool (T,T)> cmp =
                           [](T x, T y) -> bool { return x < y; }){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<T>random_v;
    for(T i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.begin(), copy_random_v.end(), cmp);
    for(T i = 0; i < number/100; i++){
        std::swap(*(copy_random_v.begin() + mersenne()%copy_random_v.size()),
                  *(copy_random_v.begin() + mersenne()%copy_random_v.size()));
    }
    sorting.Sort(copy_random_v.begin(), copy_random_v.end(), cmp);

    std::sort(random_v.begin(), random_v.end(), cmp);

    CHECK(random_v == copy_random_v);
}

template <typename T>
void TestSortingAlmostReverseSorted(Sortings::Sorting<std::vector<T>>& sorting, T number,
                             std::function<bool (T,T)> cmp =
                           [](T x, T y) -> bool { return x < y; }){
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<T>random_v;
    for(T i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.rbegin(), copy_random_v.rend(), cmp);
    for(T i = 0; i < number/100; i++){
        std::swap(*(copy_random_v.begin() + mersenne()%copy_random_v.size()),
                  *(copy_random_v.begin() + mersenne()%copy_random_v.size()));
    }
    sorting.Sort(copy_random_v.begin(), copy_random_v.end(), cmp);

    std::sort(random_v.begin(), random_v.end(), cmp);

    CHECK(random_v == copy_random_v);
}

template <typename T>
void TestSorting(Sortings::Sorting<std::vector<T>>& sorting, T number,
                 std::function<bool (T,T)> cmp =
               [](T x, T y) -> bool { return x < y; }){
    TestSortingBasic<T>(sorting, cmp);
    TestSortingRandom<T>(sorting,number,cmp);
    TestSortingAlmostSorted<T>(sorting, number, cmp);
    TestSortingAlmostReverseSorted<T>(sorting, number, cmp);
}

TEST_CASE("testing sortings"){
    Sortings::BubbleSort<std::vector<long>>bubble;
    TestSorting<long>(bubble, 10000);
    TestSorting<long>(bubble, 10000, [](long x, long y){return x > y;});
    Sortings::InsertionSort<std::vector<long>>insertion;
    TestSorting<long>(insertion, 10000);
    TestSorting<long>(insertion, 10000, [](long x, long y){return x > y;});
    Sortings::SelectionSort<std::vector<long>>selection;
    TestSorting<long>(selection, 10000);
    TestSorting<long>(selection, 10000, [](long x, long y){return x > y;});
    Sortings::CycleSort<std::vector<long>>cycle;
    TestSorting<long>(cycle, 10000);
    TestSorting<long>(cycle, 10000, [](long x, long y){return x > y;});

    Sortings::ShakerSort<std::vector<long>>shaker;
    TestSorting<long>(shaker, 10000);
    TestSorting<long>(shaker, 10000, [](long x, long y){return x > y;});
    Sortings::CombSort<std::vector<long>>comb;
    TestSorting<long>(comb, 10000);
    TestSorting<long>(comb, 10000, [](long x, long y){return x > y;});
    Sortings::GnomeSort<std::vector<long>>gnome;
    TestSorting<long>(gnome, 10000);
    TestSorting<long>(gnome, 10000, [](long x, long y){return x > y;});
    Sortings::OddEvenSort<std::vector<long>>oddEven;
    TestSorting<long>(oddEven, 10000);
    TestSorting<long>(oddEven, 10000, [](long x, long y){return x > y;});
    Sortings::QuickSort<std::vector<long>>quick;
    TestSorting<long>(quick, 100000);
    TestSorting<long>(quick, 100000, [](long x, long y){return x > y;});

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
