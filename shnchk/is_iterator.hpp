#ifndef SHINCHOKU_IS_ITERATOR_HPP
#define SHINCHOKU_IS_ITERATOR_HPP
#include <type_traits>
#include <utility>
#include <iterator>

namespace shnchk
{
namespace detail
{

template<typename T>
std::false_type is_iterator_impl(long);

template<typename T,
    typename = typename std::iterator_traits<T>::difference_type,
    typename = typename std::iterator_traits<T>::pointer,
    typename = typename std::iterator_traits<T>::reference,
    typename = typename std::iterator_traits<T>::value_type,
    typename = typename std::iterator_traits<T>::iterator_category>
std::true_type is_iterator_impl(int);

template<typename T>
struct is_iterator : decltype(is_iterator_impl<T>(0)){};

} // detail
} // shnchk
#endif // SHINCHOKU_PROGRESS_ITERATOR
