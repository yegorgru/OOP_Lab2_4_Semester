#include "Decorator.h"

SortingAndTiming::SortingAndTiming(Visualizer* visualizer):
    m_Visualizer(visualizer),
    m_Sorting(new Sortings::BubbleSort<std::vector<uint32_t>,Sortings::DefaultVisualizer<std::vector<uint32_t>>>(m_Visualizer)),
    m_CurrentSortingName(Sortings::SortingName::BUBBLESORT) {}

void SortingAndTiming::SetSorting(Sortings::SortingName name, bool isVisualization){
    if(m_CurrentSortingName != name){
        if(m_Sorting){
            delete m_Sorting;
        }
        switch(name){
        case Sortings::SortingName::BUBBLESORT:{
            m_Sorting = new Sortings::BubbleSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::INSERTIONSORT:{
            m_Sorting = new Sortings::InsertionSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::SELECTIONSORT:{
            m_Sorting = new Sortings::SelectionSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::CYCLESORT:{
            m_Sorting = new Sortings::CycleSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::SHAKERSORT:{
            m_Sorting = new Sortings::ShakerSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::COMBSORT:{
            m_Sorting = new Sortings::CombSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::GNOMESORT:{
            m_Sorting = new Sortings::GnomeSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::ODDEVENSORT:{
            m_Sorting = new Sortings::OddEvenSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::QUICKSORT:{
            m_Sorting = new Sortings::QuickSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::MERGESORT:{
            m_Sorting = new Sortings::MergeSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::MERGESORTINPLACE:{
            m_Sorting = new Sortings::MergeSortInPlace<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::HEAPSORT:{
            m_Sorting = new Sortings::HeapSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::TIMSORT:{
            m_Sorting = new Sortings::TimSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::INTROSORT:{
            m_Sorting = new Sortings::IntroSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::SHELLSORT:{
            m_Sorting = new Sortings::ShellSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::PIGEONHOLESORT:{
            m_Sorting = new Sortings::PigeonholeSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::BUCKETSORT:{
            m_Sorting = new Sortings::BucketSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::COUNTINGSORT:{
            m_Sorting = new Sortings::CountingSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::RADIXSORT:{
            m_Sorting = new Sortings::RadixSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::FLASHSORT:{
            m_Sorting = new Sortings::FlashSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::PANCAKESORT:{
            m_Sorting = new Sortings::PancakeSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::BOGOSORT:{
            m_Sorting = new Sortings::BogoSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::STOOGESORT:{
            m_Sorting = new Sortings::StoogeSort<std::vector<uint32_t>>();
            break;
        }
        case Sortings::SortingName::SLOWSORT:{
            m_Sorting = new Sortings::SlowSort<std::vector<uint32_t>>();
            break;
        }
        }
        m_CurrentSortingName = name;
    }
    if(isVisualization){
        m_Sorting->SetVisualizer(m_Visualizer);
    }
    else{
        m_Sorting->SetVisualizer(&m_DefaultVisualizer);
    }
}

float SortingAndTiming::Run(std::vector<uint32_t>& m_Numbers, std::function<bool (uint32_t,uint32_t)> cmp){
    time.start();
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), cmp);
    return (float)time.nsecsElapsed()/1000000;
}

QString SortingAndTiming::ComplexityCheck(Sortings::SortingName name)
{
    if ((name == Sortings::SortingName::BUBBLESORT ) || (name == Sortings::SortingName::INSERTIONSORT) ||
            (name == Sortings::SortingName::SELECTIONSORT) || (name == Sortings::SortingName::SHAKERSORT) || (name == Sortings::SortingName::GNOMESORT)
            || (name == Sortings::SortingName::ODDEVENSORT) || (name == Sortings::SortingName::PANCAKESORT) || (name == Sortings::SortingName::STOOGESORT))
    {
        return "O(n²)";
    }
    else if ((name == Sortings::SortingName::COMBSORT) || (name == Sortings::SortingName::QUICKSORT) || (name == Sortings::SortingName::MERGESORT)
               || (name == Sortings::SortingName::MERGESORTINPLACE) || (name == Sortings::SortingName::HEAPSORT) || (name == Sortings::SortingName::TIMSORT)
               || (name == Sortings::SortingName::INTROSORT) || (name == Sortings::SortingName::SHELLSORT) || (name == Sortings::SortingName::BUCKETSORT))
    {
        return "O(n log(n))";
    }
    else if((name == Sortings::SortingName::PIGEONHOLESORT) || (name == Sortings::SortingName::COUNTINGSORT) || (name == Sortings::SortingName::RADIXSORT)
              )
    {
        return "O(n + Range)";
    }
    else if(name == Sortings::SortingName::FLASHSORT)
    {
        return "O(n)";
    }
    else if(name == Sortings::SortingName::BOGOSORT)
    {
        return "O((n+1)!)";
    }
    else if(name == Sortings::SortingName::BOGOSORT)
    {
        return "O(>n²)";
    }
    return "Unrecognised";
}
