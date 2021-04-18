#include "Decorator.h"

SortingAndTiming::SortingAndTiming(Visualizer* visualizer):
    m_Visualizer(visualizer),
    m_Sorting(new Sortings::BubbleSort<std::vector<int>,Visualizer>(m_Visualizer)),
    m_CurrentSortingName(Sortings::SortingName::BUBBLESORT) {}

void SortingAndTiming::SetSorting(Sortings::SortingName name){
    if(m_CurrentSortingName != name){
        if(m_Sorting){
            delete m_Sorting;
        }
        switch(name){
        case Sortings::SortingName::BUBBLESORT:{
            m_Sorting = new Sortings::BubbleSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::INSERTIONSORT:{
            m_Sorting = new Sortings::InsertionSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::SELECTIONSORT:{
            m_Sorting = new Sortings::SelectionSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::CYCLESORT:{
            m_Sorting = new Sortings::CycleSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::SHAKERSORT:{
            m_Sorting = new Sortings::ShakerSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::COMBSORT:{
            m_Sorting = new Sortings::CombSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::GNOMESORT:{
            m_Sorting = new Sortings::GnomeSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::ODDEVENSORT:{
            m_Sorting = new Sortings::OddEvenSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::QUICKSORT:{
            m_Sorting = new Sortings::QuickSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::MERGESORT:{
            m_Sorting = new Sortings::MergeSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::MERGESORTINPLACE:{
            m_Sorting = new Sortings::MergeSortInPlace<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::HEAPSORT:{
            m_Sorting = new Sortings::HeapSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::TIMSORT:{
            m_Sorting = new Sortings::TimSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::INTROSORT:{
            m_Sorting = new Sortings::IntroSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::SHELLSORT:{
            m_Sorting = new Sortings::ShellSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::PIGEONHOLESORT:{
            m_Sorting = new Sortings::PigeonholeSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::BUCKETSORT:{
            m_Sorting = new Sortings::BucketSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::COUNTINGSORT:{
            m_Sorting = new Sortings::CountingSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::RADIXSORT:{
            m_Sorting = new Sortings::RadixSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::FLASHSORT:{
            m_Sorting = new Sortings::FlashSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        case Sortings::SortingName::PANCAKESORT:{
            m_Sorting = new Sortings::PancakeSort<std::vector<int>,Visualizer>(m_Visualizer);
            break;
        }
        }
        m_CurrentSortingName = name;
    }
}

qint64 SortingAndTiming::Run(std::vector<int>& m_Numbers){
    time.start();
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; });
    return time.nsecsElapsed();
}
