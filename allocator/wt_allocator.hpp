#ifndef _STL_WT_ALLOCATOR_HPP_
#define _STL_WT_ALLOCATOR_HPP_

// depend on utility.hpp (forward)

namespace wt{

template <typename T>
class allocator {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    template <typename U>
    struct rebind {
        typedef allocator<U> other;
    };

    allocator() {}
    allocator(const allocator& ) {}

    template <typename U>
    allocator(const allocator<U>& other) {}

    ~allocator() {}

    pointer address(reference x) const
    {
        return &x;
    }

    const_pointer address(const_reference x) const
    {
        return &x;
    }

    pointer allocate(size_type n, const void* hint = 0)
    {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type)
    {
        ::operator delete(p);
    }

    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        ::new((void*)p) U(wt::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p)
    {
        p->~U();
    }
};

template <>
struct allocator<void> {
public:
    typedef void           value_type;
    typedef void*          pointer;
    typedef const void*    const_pointer;

    template <typename U>
    struct rebind {
        typedef allocator<U> other;
    };
};


template <typename T1, typename T2>
bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept
{
    return true;
}

template <typename T1, typename T2>
bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept
{
    return false;
}



} // namespace wt

#endif