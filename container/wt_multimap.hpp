#ifndef _STL_WT_MULTIMAP_HPP_
#define _STL_WT_MULTIMAP_HPP_

namespace wt {

template <typename Key, typename T, typename Compare = wt::default_order_t<Key>,
          typename Allocator = wt::allocator<wt::pair<const Key, T>>>
class multimap;

template <typename Key, typename T, typename Compare, typename Allocator>
class multimap {
    typedef wt::Rb_tree<Key, wt::pair<const Key, T>,
         _Pair1st<wt::pair<const Key, T>>, Compare, Allocator>  _Impl_type;
public:
    typedef Key                                             key_type;
    typedef T                                               mapped_type;
    typedef wt::pair<const Key, T>                          value_type;
    typedef Compare                                         key_compare;
    typedef typename _Impl_type::size_type                  size_type;
    typedef typename _Impl_type::difference_type            difference_type;
    typedef typename _Impl_type::allocator_type             allocator_type;
    typedef typename _Impl_type::reference                  reference;
    typedef typename _Impl_type::const_reference            const_reference;
    typedef typename _Impl_type::pointer                    pointer;
    typedef typename _Impl_type::const_pointer              const_pointer;
    typedef typename _Impl_type::iterator                   iterator;
    typedef typename _Impl_type::const_iterator             const_iterator;
    typedef typename _Impl_type::reverse_iterator           reverse_iterator;
    typedef typename _Impl_type::const_reverse_iterator     const_reverse_iterator;

    //  nested class value_compare
    class value_compare {
        friend class multimap<key_type,value_type, key_compare, allocator_type>;
    public:
        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return m_comp_(lhs.first, rhs.first);
        }
    protected:
        value_compare(const key_compare& _comp)
        : m_comp_(_comp) { }

        key_compare m_comp_;
    };

    allocator_type get_allocator() const
    {
        return m_impl_.get_allocator();
    }

    multimap() : multimap(key_compare()) { }
    explicit multimap(const key_compare& _comp, 
                 const allocator_type& _alloc = allocator_type())
    : m_impl_(_comp, _alloc) { }

    explicit multimap(const allocator_type& _alloc)
    : m_impl_(key_compare(), _alloc) { }

    template <typename InputIter>
    multimap(InputIter _first, InputIter _last, 
        const key_compare& _comp = key_compare(),
        const allocator_type& _alloc = allocator_type())
    : m_impl_(_comp, _alloc)
    {
        m_impl_.insert_equal(_first, _last);
    }

    template <typename InputIter>
    multimap(InputIter _first, InputIter _last, const allocator_type& _alloc)
    : m_impl_(key_compare(), _alloc)
    {
        m_impl_.insert_equal(_first, _last);
    }

    multimap(const multimap& other)
    : m_impl_(other.m_impl_) { }

    multimap(const multimap& other, const allocator_type& _alloc)
    : m_impl_(other.m_impl_, _alloc) { }

    multimap(multimap&& other) noexcept
    {
        this->swap(other);
    }

    multimap(std::initializer_list<value_type> _ilist)
    : m_impl_(key_compare(), allocator_type())
    {
        m_impl_.insert_equal(_ilist.begin(), _ilist.end());
    }

    multimap(std::initializer_list<value_type> _ilist, const allocator_type& _alloc)
    : m_impl_(key_compare(), _alloc)
    {
        m_impl_.insert_equal(_ilist.begin(), _ilist.end());
    }

    ~multimap() { }

    multimap& operator=(const multimap& other)
    {
        m_impl_ = other.m_impl_;
        return *this;
    }

    multimap& operator=(multimap&& other) noexcept
    {
        this->swap(other);
        return *this;
    }

    multimap& operator=(std::initializer_list<value_type> _ilist)
    {
        m_impl_.clear();
        m_impl_.insert_equal(_ilist.begin(), _ilist.end());
        return *this;
    }

    /**
     *  Iterator Operations
     */
    iterator begin() noexcept
    {
        return m_impl_.begin();
    }
    const_iterator begin() const noexcept
    {
        return m_impl_.begin();
    }
    const_iterator cbegin() const noexcept
    {
        return m_impl_.cbegin();
    }

    iterator end() noexcept
    {
        return m_impl_.end();
    }
    const_iterator end() const noexcept
    {
        return m_impl_.end();
    }
    const_iterator cend() const noexcept
    {
        return m_impl_.cend();
    }

    reverse_iterator rbegin() noexcept
    {
        return m_impl_.rbegin();
    }
    const_reverse_iterator rbegin() const noexcept
    {
        return m_impl_.rbegin();
    }
    const_reverse_iterator crbegin() const noexcept
    {
        return m_impl_.crbegin();
    }

    reverse_iterator rend() noexcept
    {
        return m_impl_.rend();
    }
    const_reverse_iterator rend() const noexcept
    {
        return m_impl_.rend();
    }
    const_reverse_iterator crend() const noexcept
    {
        return m_impl_.crend();
    }

    /**
     *  Capacity Operations
     */
    bool empty() const noexcept
    {
        return m_impl_.empty();
    }
    size_type size() const noexcept
    {
        return m_impl_.size();
    }
    size_type max_size() const noexcept
    {
        return m_impl_.max_size();
    }

    /**
     *  Modify Operations
     */
    void clear()
    {
        m_impl_.clear();
    }

    wt::pair<iterator, bool> insert(const value_type& _value)
    {
        return m_impl_.insert_equal(_value);
    }
    iterator insert(const_iterator _hint, const value_type& _value)
    {
        return m_impl_.insert_equal(_hint, _value);
    }
    template <typename InputIter>
    void insert(InputIter _first, InputIter _last)
    {
        m_impl_.insert_equal(_first, _last);
    }
    void insert(std::initializer_list<value_type> _ilist)
    {
        m_impl_.insert_equal(_ilist.begin(), _ilist.end());
    }

    iterator erase(const_iterator _pos)
    {
        return m_impl_.eraes(_pos);
    }
    iterator erase(const_iterator _first, const_iterator _last)
    {
        return m_impl_.erase(_first, _last);
    }
    size_type erase(const key_type& _key)
    {
        return m_impl_.erase(_key);
    }

    void swap(multimap& other) noexcept
    {
        m_impl_.swap(other.m_impl_);
    }

    /**
     *  Lookup Operations
     */
    size_type count(const key_type& _key) const
    {
        return m_impl_.find(_key) == m_impl_.end() ? 0 : 1;
    }

    iterator find(const key_type& _key)
    {
        return m_impl_.find(_key);
    }
    const_iterator find(const key_type& _key) const
    {
        return m_impl_.find(_key);
    }

    iterator lower_bound(const key_type& _key)
    {
        return m_impl_.lower_bound(_key);
    }
    const_iterator lower_bound(const key_type& _key) const
    {
        return m_impl_.lower_bound(_key);
    }

    iterator upper_bound(const key_type& _key)
    {
        return m_impl_.upper_bound(_key);
    }
    const_iterator upper_bound(const key_type& _key) const
    {
        return m_impl_.upper_bound(_key);
    }

    wt::pair<iterator, iterator> equal_range(const key_type& _key) 
    {
        return m_impl_.equal_range(_key);
    }
    wt::pair<const_iterator, const_iterator> 
    equal_range(const key_type& _key) const
    {
        return m_impl_.equal_range(_key);
    }

    key_compare key_comp() const
    {
        return m_impl_.key_comp();
    }
    value_compare value_comp() const
    {
        return value_compare(m_impl_.key_comp());
    }

    template <typename _K, typename _T, typename _C, typename _A>
    friend bool 
    operator==(const multimap<_K, _T, _C, _A>&, const multimap<_K, _T, _C, _A>&);
    template <typename _K, typename _T, typename _C, typename _A>
    friend bool
    operator<(const multimap<_K, _T, _C, _A>&, const multimap<_K, _T, _C, _A>&);

private:
    _Impl_type  m_impl_;
};

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator==(const multimap<Key, T, Compare, Allocator>& lhs,
           const multimap<Key, T, Compare, Allocator>& rhs)
{
    return lhs.m_impl_ == rhs. m_impl_;
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator<(const multimap<Key, T, Compare, Allocator>& lhs, 
          const multimap<Key, T, Compare, Allocator>& rhs)
{
    return lhs.m_impl_ < rhs.m_impl_;
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator!=(const multimap<Key, T, Compare, Allocator>& lhs,
           const multimap<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator>(const multimap<Key, T, Compare, Allocator>& lhs,
          const multimap<Key, T, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator<=(const multimap<Key, T, Compare, Allocator>& lhs,
           const multimap<Key, T, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator>=(const multimap<Key, T, Compare, Allocator>& lhs, 
           const multimap<Key, T, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
void
swap(multimap<Key, T, Compare, Allocator>& lhs, 
     multimap<Key, T, Compare, Allocator>& rhs) noexcept
{
    lhs.swap(rhs);
}

} // namespace wt

#endif