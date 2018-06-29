#ifndef SHINCHOKU_PROGRESS_ITERATOR_HPP
#define SHINCHOKU_PROGRESS_ITERATOR_HPP
#include "is_iterator.hpp"
#include "format.hpp"
#include "range.hpp"
#include <iostream>
#include <functional>

namespace shnchk
{

template<typename Iterator, std::size_t N = 40>
struct progress_iterator
{
    using self_type         = progress_iterator<Iterator, N>;
    using iterator          = Iterator;
    using traits            = std::iterator_traits<iterator>;
    using value_type        = typename traits::value_type;
    using reference         = typename traits::reference;
    using pointer           = typename traits::pointer;
    using difference_type   = typename traits::difference_type;
    using iterator_category = typename traits::iterator_category;

    progress_iterator(iterator base, double dratio, std::ptrdiff_t count,
                      std::ptrdiff_t max_count)
        : out_(nullptr), dratio_(dratio), count_(count), max_count_(max_count),
          base_(base)
    {}
    progress_iterator(std::ostream& os, iterator base, double dratio,
                      std::ptrdiff_t count, std::ptrdiff_t max_count)
        : out_(std::addressof(os)), dratio_(dratio), count_(count),
          max_count_(max_count), base_(base)
    {}
    progress_iterator(const progress_iterator&) = default;
    progress_iterator(progress_iterator&&     ) = default;
    progress_iterator& operator=(const progress_iterator&) = default;
    progress_iterator& operator=(progress_iterator&&     ) = default;

    ~progress_iterator()
    {
        output();
    }

    reference operator* () const noexcept {return base_.operator* ();}
    pointer   operator->() const noexcept {return base_.operator->();}

    progress_iterator& operator++()
    {
        ++count_;
        output();
        ++base_;
        return *this;
    }
    progress_iterator& operator++(int)
    {
        const auto tmp(*this);
        ++(*this);
        return tmp;
    }

    typename std::enable_if<std::is_convertible<iterator_category,
        std::bidirectional_iterator_tag>::value, self_type>::type&
    operator--()
    {
        --count_;
        output();
        --base_;
        return *this;
    }
    typename std::enable_if<std::is_convertible<iterator_category,
        std::bidirectional_iterator_tag>::value, self_type>::type&
    operator--(int)
    {
        const auto tmp(*this);
        --(*this);
        return tmp;
    }

    typename std::enable_if<std::is_convertible<iterator_category,
        std::random_access_iterator_tag>::value, self_type>::type&
    operator+=(difference_type d)
    {
        count_ += d;
        output();
        base_ += d;
        return *this;
    }
    typename std::enable_if<std::is_convertible<iterator_category,
        std::random_access_iterator_tag>::value, self_type>::type&
    operator-=(difference_type d)
    {
        count_ -= d;
        output();
        base_ -= d;
        return *this;
    }

    typename std::enable_if<std::is_convertible<iterator_category,
        std::random_access_iterator_tag>::value, self_type>::type
    operator+(const difference_type d) const noexcept
    {
        auto tmp(*this);
        tmp += d;
        return tmp;
    }
    typename std::enable_if<std::is_convertible<iterator_category,
        std::random_access_iterator_tag>::value, self_type>::type
    operator-(const difference_type d) const noexcept
    {
        auto tmp(*this);
        tmp -= d;
        return tmp;
    }
    typename std::enable_if<std::is_convertible<iterator_category,
        std::random_access_iterator_tag>::value, difference_type>::type
    operator-(const progress_iterator& rhs) const noexcept
    {
        return this->base_ - rhs.base_;
    }

    typename std::enable_if<std::is_convertible<iterator_category,
        std::random_access_iterator_tag>::value, reference>::type
    operator[](difference_type d) const noexcept {return this->base_[d];}

    bool operator==(const self_type& rhs) const noexcept {return this->base_ == rhs.base_;}
    bool operator!=(const self_type& rhs) const noexcept {return this->base_ != rhs.base_;}
    bool operator< (const self_type& rhs) const noexcept {return this->base_ <  rhs.base_;}
    bool operator<=(const self_type& rhs) const noexcept {return this->base_ <= rhs.base_;}
    bool operator> (const self_type& rhs) const noexcept {return this->base_ >  rhs.base_;}
    bool operator>=(const self_type& rhs) const noexcept {return this->base_ >= rhs.base_;}

    iterator const& base() const noexcept {return base_;}

  private:

    void output()
    {
        if(!out_){return;}
        double ratio = dratio_ * count_;
        if(count_ == max_count_)
        {
            ratio = 1.0;
        }
        *out_ << formatter_.invoke(ratio);
        out_->flush();
    }

  private:

    std::ostream*  out_;
    double         dratio_;
    std::ptrdiff_t count_;
    std::ptrdiff_t max_count_;
    iterator       base_;
    format_impl<N> formatter_;
};

template<typename Iterator, std::size_t N = 40>
inline progress_iterator<Iterator, N>
make_progress_iterator(Iterator iter,
        const std::size_t d, const std::size_t maxd) noexcept
{
    return progress_iterator<Iterator, N>(std::cerr, iter, 1.0 / d, d, maxd);
}

template<typename Iterator, std::size_t N = 40, typename std::enable_if<
    detail::is_iterator<Iterator>::value, std::nullptr_t>::type = nullptr>
inline iterator_range<progress_iterator<Iterator, N>>
range(Iterator first, Iterator last) noexcept
{
    const auto   dist = std::distance(first, last);
    const double dratio = 1.0 / dist;
    return iterator_range<progress_iterator<Iterator, N>>(
        progress_iterator<Iterator, N>(std::cerr, first, dratio, 0, dist),
        progress_iterator<Iterator, N>(last,  dratio, 0, dist));
}

template<typename Integer, std::size_t N = 40, typename std::enable_if<
    std::is_integral<Integer>::value, std::nullptr_t>::type = nullptr>
inline iterator_range<progress_iterator<counting_iterator<Integer>, N>>
range(Integer first, Integer last) noexcept
{
    const auto   dist = last - first;
    const double dratio = 1.0 / dist;
    return iterator_range<progress_iterator<counting_iterator<Integer>, N>>(
        progress_iterator<counting_iterator<Integer>, N>(std::cerr, first, dratio, 0, dist),
        progress_iterator<counting_iterator<Integer>, N>(last,  dratio, 0, dist));
}

} // shnchk
#endif // SHINCHOKU_PROGRESS_ITERATOR
