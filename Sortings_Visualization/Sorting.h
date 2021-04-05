#include <type_traits>
#include <iterator>
#include <algorithm>
#include <functional>

//https://www.javaer101.com/en/article/86426841.html

template<typename Container>
using IteratorCategoryOf =
    typename std::iterator_traits<typename Container::iterator>::iterator_category;

template<typename Container>
using HaveRandomAccessIterator =
    std::is_base_of<std::random_access_iterator_tag, IteratorCategoryOf<Container>>;

namespace Sortings{

    /*template<
        typename Container,
        typename std::enable_if<!HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class Sorting{
        //typename??
        void Sort(Container::iterator begin, Container::iterator end) {
            //do generic version of algorithm
        }
    };*/

    //typename std::iterator_traits<BidirIt>::value_type

    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class Sorting{
    public:
        virtual void Sort(typename Container::iterator begin, typename Container::iterator end,
                     std::function<bool (
                     typename std::iterator_traits<typename Container::iterator>::value_type,
                     typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) = 0;
    };

    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class BubbleSort : public Sorting<Container>{
    public:
        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            size_t size = end-begin;
            for (size_t i = 0; i < size-1; i++){
                for (size_t j = 0; j < size-i-1; j++){
                    if (cmp(*(begin + j + 1), *(begin +j))){
                        std::swap(*(begin+j), *(begin + j + 1));
                    }
                }
            }
        }
    };
}
