#ifndef _STL_WT_ARRAY_HPP_
#define _STL_WT_ARRAY_HPP_

namespace wt{

template <typename T, std::size_t N>
struct array_traits {
    using Type = T[N];

    static constexpr T& ref(const Type& _arr, std::size_t _index) noexcept
    {
        return const_cast<T&>(_arr[_index]);
    }

    static constexpr T* ptr(const Type& _arr) noexcept
    {
        return const_cast<T*>(_arr);
    }
};

template <typename T>
struct array_traits<T, 0> {
    struct Type {};

    static constexpr T& ref(const Type&, std::size_t) noexcept
    {
        return *static_cast<T*>(nullptr);
    }

    static constexpr T* ptr(const Type&) noexcept
    {
        return nullptr;
    }
};

template <typename T, std::size_t N>
class array {
public:
    typedef T                                       value_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    typedef value_type*                             pointer;
    typedef const value_type*                       const_pointer;
    typedef pointer                                 iterator;
    typedef const_pointer                           const_iterator;
    typedef wt::reverse_iterator<iterator>          reverse_iterator;
    typedef wt::reverse_iterator<const_iterator>    const_reverse_iterator;

    typedef array_traits<T, N>  Traits;

    typename Traits::Type       m_array_;

    /**
     *  Element Access
     */
    constexpr reference at(size_type _pos)
    {
        if(_pos >= size())
            _throw_out_of_range();
        return Traits::ref(m_array_, _pos);
    }
    constexpr const_reference at(size_type _pos) const
    {
        return _pos < size() ? Traits::ref(m_array_, _pos)
            : (_throw_out_of_range(), Traits::ref(m_array_, 0));
    }

    constexpr reference operator[](size_type _pos)
    {
        return Traits::ref(m_array_, _pos);
    }
    constexpr const_reference operator[](size_type _pos) const
    {
        return Traits::ref(m_array_, _pos);
    }

    constexpr reference front()
    {
        return *begin();
    }
    constexpr const_reference front() const
    {
        return Traits::ref(m_array_, 0);
    }

    constexpr reference back()
    {
        return size() ? *(end() - 1) : *end();
    }
    constexpr const_reference back() const
    {
        return size() ? Traits::ref(m_array_, N - 1)
            : Traits::ref(m_array_, 0);
    }

    constexpr pointer data() noexcept
    {
        return Traits::ptr(m_array_);
    }
    constexpr const_pointer data() const noexcept
    {
        return Traits::ptr(m_array_);
    }

    /**
     *  Iterator
     */
    constexpr iterator begin() noexcept
    {
        return iterator(data());
    }
    constexpr const_iterator begin() const noexcept
    {
        return const_iterator(data());
    }
    constexpr const_iterator cbegin() const noexcept
    {
        return const_iterator(data());
    }

    constexpr iterator end() noexcept
    {
        return iterator(data() + size());
    }
    constexpr const_iterator end() const noexcept
    {
        return const_iterator(data() + size());
    }
    constexpr const_iterator cend() const noexcept
    {
        return const_iterator(data() + size());
    }

    constexpr reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }
    constexpr const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    constexpr const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    constexpr reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }
    constexpr const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }
    constexpr const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    /**
     *  Capacity Operations
     */
    constexpr bool empty() const noexcept
    {
        return N == 0;
    }

    constexpr size_type size() const noexcept
    {
        return N;
    }

    constexpr size_type max_size() const noexcept
    {
        return N;
    }

    /**
     *  Modify Operations
     */
    void fill(const T& _value)
    {
        wt::fill_n(begin(), size(), _value);
    }

    void swap(array& other)
    {
        wt::swap_ranges(begin(), end(), other.begin());
    }
private:
    void _throw_out_of_range()
    {
        throw std::out_of_range("array");
    }
};

template <typename T, std::size_t N>
bool operator==(const wt::array<T, N>& lhs, const wt::array<T, N>& rhs)
{
    return wt::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, std::size_t N>
bool operator<(const wt::array<T, N>& lhs, const wt::array<T, N>& rhs)
{
    return wt::lexicographical_compare(lhs.begin(), lhs.end(),
                                       rhs.begin(), rhs.end());
}

template <typename T, std::size_t N>
bool operator!=(const wt::array<T, N>& lhs, const wt::array<T, N>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, std::size_t N>
bool operator<=(const wt::array<T, N>& lhs, const wt::array<T, N>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, std::size_t N>
bool operator>(const wt::array<T, N>& lhs, const wt::array<T, N>& rhs)
{
    return rhs < lhs;
}

template <typename T, std::size_t N>
bool operator>=(const wt::array<T, N>& lhs, const wt::array<T, N>& rhs)
{
    return !(lhs < rhs);
}

template <typename T, std::size_t N>
void swap(wt::array<T, N>& lhs, wt::array<T, N>& rhs)
{
    lhs.swap(rhs);
}

template <std::size_t Index, typename T, std::size_t N>
constexpr T& get(wt::array<T, N>& _arr) noexcept
{
    static_assert(Index < N, "index is out of range");
    return wt::array_traits<T, N>::ref(_arr.m_array_, Index);
}

template <std::size_t Index, typename T, std::size_t N>
constexpr const T& get(const wt::array<T, N>& _arr) noexcept
{
    static_assert(Index < N, "index is out of range");
    return wt::array_traits<T, N>::ref(_arr.m_array_, Index);
}

// TODO: overload for rvalue



} // namespace wt

#endif