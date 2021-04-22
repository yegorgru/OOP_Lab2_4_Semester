#pragma once

#include "Sorting.h"

template<
    typename Container, typename Sorting,
    typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
class SortingFactory{
public:
    static Sorting* CreateSorting(Sortings::DefaultVisualizer<Container>* visualizer = nullptr){
        return new Sorting(visualizer);
    }
};

template<
    typename Container,
    typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
class Factory{
public:
    static Sortings::Sorting<Container>* CreateSorting(Sortings::SortingName name,
                    Sortings::DefaultVisualizer<Container>* visualizer = nullptr){
        switch(name){
        case Sortings::SortingName::BUBBLESORT:{
            return SortingFactory<Container,Sortings::BubbleSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::INSERTIONSORT:{
            return SortingFactory<Container,Sortings::InsertionSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::SELECTIONSORT:{
            return SortingFactory<Container,Sortings::SelectionSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::CYCLESORT:{
            return SortingFactory<Container,Sortings::CycleSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::SHAKERSORT:{
            return SortingFactory<Container,Sortings::ShakerSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::COMBSORT:{
            return SortingFactory<Container,Sortings::CombSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::GNOMESORT:{
            return SortingFactory<Container,Sortings::GnomeSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::ODDEVENSORT:{
            return SortingFactory<Container,Sortings::OddEvenSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::QUICKSORTPIVOTFIRST:{
            return SortingFactory<Container,Sortings::QuickSortPivotFirst<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::MERGESORT:{
            return SortingFactory<Container,Sortings::MergeSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::MERGESORTINPLACE:{
            return SortingFactory<Container,Sortings::MergeSortInPlace<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::HEAPSORT:{
            return SortingFactory<Container,Sortings::HeapSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::TIMSORT:{
            return SortingFactory<Container,Sortings::TimSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::INTROSORT:{
            return SortingFactory<Container,Sortings::IntroSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::SHELLSORT:{
            return SortingFactory<Container,Sortings::ShellSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::PIGEONHOLESORT:{
            return SortingFactory<Container,Sortings::PigeonholeSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::BUCKETSORT:{
            return SortingFactory<Container,Sortings::BucketSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::COUNTINGSORT:{
            return SortingFactory<Container,Sortings::CountingSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::RADIXSORT:{
            return SortingFactory<Container,Sortings::RadixSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::FLASHSORT:{
            return SortingFactory<Container,Sortings::RadixSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::PANCAKESORT:{
            return SortingFactory<Container,Sortings::PancakeSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::BOGOSORT:{
            return SortingFactory<Container,Sortings::BogoSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::STOOGESORT:{
            return SortingFactory<Container,Sortings::StoogeSort<Container>>::CreateSorting(visualizer);
        }
        case Sortings::SortingName::SLOWSORT:{
            return SortingFactory<Container,Sortings::SlowSort<Container>>::CreateSorting(visualizer);
        }
        }
    }
};
