#ifndef _STL_WT_ALLOCATOR_TRAITS_HPP_
#define _STL_WT_ALLOCATOR_TRAITS_HPP_

// depend on "utility.hpp" : forward

namespace wt{

template <typename Alloc>
struct allocator_traits {
    typedef Alloc                           allocator_type;
    typedef typename Alloc::value_type      value_type;
    typedef typename Alloc::pointer         pointer;
    typedef typename Alloc::const_pointer   const_pointer;
    typedef typename Alloc::difference_type difference_type;
    typedef typename Alloc::size_type       size_type;

    template <typename T>
    using rebind_alloc = typename Alloc::template rebind<T>::other;

    template <typename T>
    using rebind_traits = typename wt::allocator_traits<rebind_alloc<T>>;

    static pointer  allocate(Alloc& a, size_type n);
    static pointer  allocate(Alloc& a, size_type n, const void* hint);
    static void     deallocate(Alloc& a, pointer p, size_type n);

    template <typename T, typename... Args>
    static void construct(Alloc& a, T* p, Args&&... args);

    template <typename T>
    static void destroy(Alloc& a, T* p);

    static size_type max_size(Alloc& a) noexcept;
};

template <typename Alloc>
typename allocator_traits<Alloc>::pointer 
allocator_traits<Alloc>::allocate(Alloc& a, size_type n)
{
    return a.allocate(n);
}

template <typename Alloc>
typename allocator_traits<Alloc>::pointer 
allocator_traits<Alloc>::allocate(Alloc& a, size_type n, const void* hint)
{
    return a.allocate(n,hint);
}

template <typename Alloc>
void allocator_traits<Alloc>::deallocate(Alloc& a, pointer p, size_type n)
{
    a.deallocate(p,n);
}

template <typename Alloc>
template <typename T, typename... Args>
void allocator_traits<Alloc>::construct(Alloc& a, T* p, Args&&... args)
{
    a.construct(p,wt::forward<Args>(args)...);
}

template <typename Alloc>
template <typename T>
void allocator_traits<Alloc>::destroy(Alloc& a, T* p)
{
    a.destroy(p);
}

template <typename Alloc>
typename allocator_traits<Alloc>::size_type 
allocator_traits<Alloc>::max_size(Alloc& a) noexcept
{
    return a.max_size();
}

} // namespace wt

#endif