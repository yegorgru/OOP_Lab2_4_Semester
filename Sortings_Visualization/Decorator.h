#ifndef DECORATOR_H
#define DECORATOR_H

#include <Sorting.h>
#include <visualizer.h>
#include <QElapsedTimer>

namespace Sortings {

    class SortingAndTiming  {
    public:
        SortingAndTiming(Sortings::Sorting<std::vector<int>,Visualizer>* sorting)
            : m_Sorting(sorting) {}

        void SetSorting (Sortings::SortingName name, Visualizer& m_Visualizer) {
            if(m_Sorting){
                delete m_Sorting;
            }
            switch(name){
                case Sortings::SortingName::BUBBLESORT:{
                    m_Sorting = new Sortings::BubbleSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::INSERTIONSORT:{
                    m_Sorting = new Sortings::InsertionSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::SELECTIONSORT:{
                    m_Sorting = new Sortings::SelectionSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::CYCLESORT:{
                    m_Sorting = new Sortings::CycleSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::SHAKERSORT:{
                    m_Sorting = new Sortings::ShakerSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::COMBSORT:{
                    m_Sorting = new Sortings::CombSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::GNOMESORT:{
                    m_Sorting = new Sortings::GnomeSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::ODDEVENSORT:{
                    m_Sorting = new Sortings::OddEvenSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::QUICKSORT:{
                    m_Sorting = new Sortings::QuickSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::MERGESORT:{
                    m_Sorting = new Sortings::MergeSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::MERGESORTINPLACE:{
                    m_Sorting = new Sortings::MergeSortInPlace<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::HEAPSORT:{
                    m_Sorting = new Sortings::HeapSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::TIMSORT:{
                    m_Sorting = new Sortings::TimSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::INTROSORT:{
                    m_Sorting = new Sortings::IntroSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::SHELLSORT:{
                    m_Sorting = new Sortings::ShellSort<std::vector<int>,Visualizer>(&m_Visualizer);
                    break;
                }
                case Sortings::SortingName::PIGEONHOLESORT:{
                        m_Sorting = new Sortings::PigeonholeSort<std::vector<int>,Visualizer>(&m_Visualizer);
                        break;
                }
                }
        }

        qint64 Run(std::vector<int>& m_Numbers) {
            time.start();
            m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; });
            return time.nsecsElapsed();
        }

    private:
        QElapsedTimer time;
        Sortings::Sorting<std::vector<int>,Visualizer>* m_Sorting;
    };
}
#endif // DECORATOR_H
