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

    template <typename T>
    using Func = std::function<bool (T,T)>;

    template <typename T>
    T F(long double guess, long double tolerance, Func<T> f, Func<T> df);

    //typename std::iterator_traits<BidirIt>::value_type

    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class Sorting{
    public:
        virtual void Sort(typename Container::iterator begin, typename Container::iterator end) = 0;
    };

    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class BubbleSort : public Sorting<Container>{
    public:
        void Sort(typename Container::iterator begin, typename Container::iterator end) override{
            size_t size = end-begin;
            for (size_t i = 0; i < size-1; i++){
                for (size_t j = 0; j < size-i-1; j++){
                    if (*(begin +j) > *(begin + j + 1)){
                        std::swap(*(begin+j), *(begin + j + 1));
                    }
                }
            }
        }
    };
}
