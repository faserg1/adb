#pragma once

#include <iterator>
#include <concepts>
#include <numeric>

namespace adb::types
{
    template <std::signed_integral Integral>
    class Range
    {
    public:
        class Iterator;

        Range(Integral min = 0, Integral max = 0) : min_(min), max_(max) {}

        Iterator begin()
        {
            return Iterator(min_, min_, max_);
        }
        Iterator end()
        {
            return Iterator(max_, min_, max_);
        }
    private:
        Integral min_;
        Integral max_;
    };

    template <std::signed_integral Integral>
    class Range<Integral>::Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Integral;
        using difference_type = Integral;
        using pointer = Integral*;
        using reference = Integral&;

        Iterator() = default;
        Iterator(Integral val, Integral min, Integral max) : cur_(val), min_(min), max_(max) {}
        Iterator(const Iterator& iter) = default;
        ~Iterator(){}

        operator bool() const
        {
            return cur_ >= min_ && cur_ < max_;
        }

        bool operator==(const Iterator& iter) const
        {
            return iter.cur_ == cur_;
        }
        bool operator!=(const Iterator& iter) const
        {
            return iter.cur_ != cur_;
        }

        Iterator& operator+=(const difference_type& movement)
        {
            cur_ += movement;
            return (*this);
        }
        Iterator& operator-=(const difference_type& movement)
        {
            cur_ -= movement;
            return (*this);
        }
        Iterator& operator++()
        {
            ++cur_;
            return (*this);
        }
        Iterator& operator--()
        {
            --cur_;
            return (*this);
        }
        Iterator  operator++(int)
        {
            auto temp(*this);
            ++cur_;
            return temp;
        }
        Iterator  operator--(int)
        {
            auto temp(*this);
            --cur_;
            return temp;
        }
        Iterator  operator+(const difference_type& movement)
        {
            auto oldPtr = cur_;
            cur_ += movement;
            auto temp(*this);
            cur_ = oldPtr;
            return temp;
        }
        Iterator  operator-(const difference_type& movement)
        {
            auto oldPtr = cur_;
            cur_ -= movement;
            auto temp(*this);
            cur_ = oldPtr;
            return temp;
        }

        difference_type operator-(const Iterator& iter)
        {
            return cur_ - iter.cur_;
        }

        const Integral& operator*() const
        {
            return cur_;
        }
        const Integral& operator->()const
        {
            return cur_;
        }
    private:
        Integral cur_ = std::numeric_limits<Integral>::min();
        Integral min_ = std::numeric_limits<Integral>::min();
        Integral max_ = std::numeric_limits<Integral>::min();
    };
}
