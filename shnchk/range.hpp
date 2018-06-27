#ifndef SHINCHOKU_RANGE_HPP
#define SHINCHOKU_RANGE_HPP
#include <iterator>

namespace shnchk
{

template<typename Iterator>
struct iterator_range
{
    using iterator        = Iterator;
    using traits          = std::iterator_traits<iterator>;
    using value_type      = typename traits::value_type;
    using reference       = typename traits::reference;
    using pointer         = typename traits::pointer;
    using difference_type = typename traits::difference_type;

    iterator_range(Iterator f, Iterator l)
        : first(f), last(l), dist(std::distance(first, last))
    {}
    ~iterator_range() = default;
    iterator_range(iterator_range const&) = default;
    iterator_range(iterator_range &&)     = default;
    iterator_range& operator=(iterator_range const&) = default;
    iterator_range& operator=(iterator_range &&)     = default;

    Iterator begin() const noexcept {return first;}
    Iterator end()   const noexcept {return last;}

    difference_type distance() const noexcept {return dist;}

    Iterator first, last;
    difference_type dist;
};

template<typename Iterator>
inline iterator_range<Iterator> make_range(Iterator first, Iterator last)
{
    return iterator_range<Iterator>(first, last);
}

} // shnchk
#endif// SHINCHOKU_RANGE_HPP
