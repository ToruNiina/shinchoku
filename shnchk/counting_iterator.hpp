#ifndef SHINCHOKU_COUNTING_ITERATOR_HPP
#define SHINCHOKU_COUNTING_ITERATOR_HPP
#include <type_traits>
#include <utility>
#include <iterator>

namespace shnchk
{

template<typename Integer, typename Difference = std::int64_t>
struct counting_iterator
{
    using value_type        = Integer;
    using difference_type   = Difference;
    using pointer           = value_type const*;
    using reference         = value_type const&;
    using iterator_category = std::random_access_iterator_tag;

    counting_iterator() = default;
    ~counting_iterator() = default;
    counting_iterator(counting_iterator const&) = default;
    counting_iterator(counting_iterator &&)     = default;
    counting_iterator& operator=(counting_iterator const&) = default;
    counting_iterator& operator=(counting_iterator &&)     = default;

    template<typename T, typename std::enable_if<
        std::is_convertible<T, value_type>::value, std::nullptr_t>::type = nullptr>
    counting_iterator(T&& c): count_(std::forward<T>(c)){}

    reference operator* () const noexcept {return count_;}
    pointer   operator->() const noexcept {return std::addressof(count_);}

    counting_iterator& operator++()    noexcept {++count_; return *this;}
    counting_iterator& operator--()    noexcept {--count_; return *this;}
    counting_iterator  operator++(int) noexcept {auto tmp(*this); ++count_; return tmp;}
    counting_iterator  operator--(int) noexcept {auto tmp(*this); --count_; return tmp;}

    counting_iterator& operator+=(difference_type d) noexcept {count_+=d; return *this;}
    counting_iterator& operator-=(difference_type d) noexcept {count_-=d; return *this;}

    counting_iterator operator+(difference_type d) const noexcept
    {auto tmp(*this); tmp += d; return *this;}
    counting_iterator operator-(difference_type d) const noexcept
    {auto tmp(*this); tmp -= d; return *this;}

    value_type operator[](difference_type d) const noexcept {return this->count_ + d;}
    value_type const& count() const noexcept {return count_;}

  private:
    value_type count_;
};

template<typename Integer, typename Difference>
bool operator==(const counting_iterator<Integer, Difference>& lhs,
                const counting_iterator<Integer, Difference>& rhs) noexcept
{return lhs.count() == rhs.count();}
template<typename Integer, typename Difference>
bool operator!=(const counting_iterator<Integer, Difference>& lhs,
                const counting_iterator<Integer, Difference>& rhs) noexcept
{return lhs.count() != rhs.count();}

template<typename Integer, typename Difference>
bool operator< (const counting_iterator<Integer, Difference>& lhs,
                const counting_iterator<Integer, Difference>& rhs) noexcept
{return lhs.count() <  rhs.count();}
template<typename Integer, typename Difference>
bool operator<=(const counting_iterator<Integer, Difference>& lhs,
                const counting_iterator<Integer, Difference>& rhs) noexcept
{return lhs.count() <= rhs.count();}

template<typename Integer, typename Difference>
bool operator> (const counting_iterator<Integer, Difference>& lhs,
                const counting_iterator<Integer, Difference>& rhs) noexcept
{return lhs.count() >  rhs.count();}
template<typename Integer, typename Difference>
bool operator>=(const counting_iterator<Integer, Difference>& lhs,
                const counting_iterator<Integer, Difference>& rhs) noexcept
{return lhs.count() >= rhs.count();}

template<typename Integer, typename Difference>
Difference operator-(const counting_iterator<Integer, Difference>& lhs,
                     const counting_iterator<Integer, Difference>& rhs) noexcept
{return lhs.count() - rhs.count();}
template<typename Integer, typename Difference>
counting_iterator<Integer, Difference>
operator+(const Difference lhs,
          const counting_iterator<Integer, Difference>& rhs) noexcept
{return rhs + lhs;}

template<typename Integer, typename Difference = std::int64_t>
counting_iterator<Integer, Difference>
make_counting_iterator(const Integer i) noexcept
{
    return counting_iterator<Integer, Difference>(i);
}

} // shnchk
#endif// SHINCHOKU_COUNTING_ITERATOR_HPP
