#ifndef _STL_WT_SET_HPP_
#define _STL_WT_SET_HPP_

namespace wt {

template <typename Key, typename Compare = wt::default_order_t<Key>,
          typename Allocator = wt::allocator<Key>>
class set {
    typedef wt::Rb_tree<Key, Key, _Identity<Key>, Compare, Allocator> _Impl_type;
public:
    typedef Key                                         key_type;
    typedef Key                                         value_type;
    typedef Compare                                     key_compare;
    typedef Compare                                     value_compare;
    typedef typename _Impl_type::size_type              size_type;
    typedef typename _Impl_type::difference_type        difference_type;
    typedef typename _Impl_type::allocator_type         allocator_type;
    typedef typename _Impl_type::reference              reference;
    typedef typename _Impl_type::const_reference        const_reference;
    typedef typename _Impl_type::pointer                pointer;
    typedef typename _Impl_type::const_pointer          const_pointer;
    typedef typename _Impl_type::const_iterator         iterator;
    typedef typename _Impl_type::const_iterator         const_iterator;
    typedef typename _Impl_type::const_reverse_iterator reverse_iterator;
    typedef typename _Impl_type::const_reverse_iterator const_reverse_iterator;

    allocator_type get_allocator() const
    {
        return m_impl_.get_allocator();
    }
    set() : set(key_compare()) { }
    explicit set(const key_compare& _comp, 
                 const allocator_type& _alloc = allocator_type())
    : m_impl_(_comp, _alloc) { }
    explicit set(const allocator_type& _alloc)
    : m_impl_(key_compare(), _alloc) { }

    template <typename InputIter>
    set(InputIter _first, InputIter _last, 
        const key_compare& _comp = key_compare(), 
        const allocator_type& _alloc = allocator_type())
    : m_impl_(_comp, _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    template <typename InputIter>
    set(InputIter _first, InputIter _last, const allocator_type& _alloc)
    : m_impl_(key_compare(), _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    set(const set& other) : m_impl_(other.m_impl_) { }
    set(const set& other, const allocator_type& _alloc)
    : m_impl_(other.m_impl_, _alloc) { }

    set(set&& other)
    {
        this->swap(other);
    }

    //  TODO : Move Operations
    set(std::initializer_list<value_type> _ilist, 
        const key_compare& _comp = key_compare(),
        const allocator_type& _alloc = allocator_type())
    : m_impl_(_comp, _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }
    set(std::initializer_list<value_type> _ilist, const allocator_type& _alloc)
    : m_impl_(key_compare(), _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    ~set() { }

    set& operator=(const set& other)
    {
        m_impl_ = other.m_impl_;
        return *this;
    }
    set& operator=(set&& other) noexcept
    {
        this->swap(other);
        return *this;
    }

    set& operator=(std::initializer_list<value_type> _ilist)
    {
        m_impl_.clear();
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
        return *this;
    }

    /**
     *  Iterator  Operations
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
        auto p = m_impl_.insert_unique(_value);
        return wt::pair<iterator, bool>(p.first, p.second);
    }
    iterator insert(const_iterator _hint, 
                    const value_type& _value)
    {
        return m_impl_.insert_unique(_hint, _value);
    }
    template <typename InputIter>
    void insert(InputIter _first, InputIter _last)
    {
        m_impl_.insert_unique(_first, _last);
    }
    void insert(std::initializer_list<value_type> _ilist)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    iterator erase(const_iterator _pos)
    {
        return m_impl_.erase(_pos);
    }
    iterator erase(const_iterator _first, const_iterator _last)
    {
        return m_impl_.erase(_first, _last);
    }
    size_type erase(const key_type& _key)
    {
        return m_impl_.erase(_key);
    }

    void swap(set& other) noexcept
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

    iterator find(const key_type& _key) const
    {
        return m_impl_.find(_key);
    }

    iterator lower_range(const key_type& _key) const
    {
        return m_impl_.lower_range(_key);
    }

    iterator upper_range(const key_type& _key) const
    {
        return m_impl_.upper_range(_key);
    }

    wt::pair<iterator, iterator> equal_range(const key_type& _key) const
    {
        auto p = m_impl_.equal_range(_key);
        return wt::pair<iterator, iterator>(p.first, p.second);
    }

    key_compare key_comp() const
    {
        return m_impl_.key_comp();
    }

    value_compare value_comp() const
    {
        return key_comp();
    }

    template <typename K, typename C, typename A>
    friend bool operator==(const set<K, C, A>& , const set<K, C, A>&);
    template <typename K, typename C, typename A>
    friend bool operator<(const set<K, C, A>&, const set<K, C, A>&);

private:
    _Impl_type  m_impl_;
};

template <typename Key, typename Compare, typename Allocator>
inline bool
operator==(const set<Key, Compare, Allocator>& lhs,
           const set<Key, Compare, Allocator>& rhs)
{
    return lhs.m_impl_ == rhs. m_impl_;
}

template <typename Key, typename Compare, typename Allocator>
inline bool
operator<(const set<Key, Compare, Allocator>& lhs, 
          const set<Key, Compare, Allocator>& rhs)
{
    return lhs.m_impl_ < rhs.m_impl_;
}

template <typename Key, typename Compare, typename Allocator>
inline bool
operator!=(const set<Key, Compare, Allocator>& lhs,
           const set<Key, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Compare, typename Allocator>
inline bool
operator>(const set<Key, Compare, Allocator>& lhs,
          const set<Key, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename Compare, typename Allocator>
inline bool
operator<=(const set<Key, Compare, Allocator>& lhs,
           const set<Key, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename Compare, typename Allocator>
inline bool
operator>=(const set<Key, Compare, Allocator>& lhs, 
           const set<Key, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <typename Key, typename Compare, typename Allocator>
void
swap(set<Key, Compare, Allocator>& lhs, 
     set<Key, Compare, Allocator>& rhs) noexcept
{
    lhs.swap(rhs); 
}

} // namespace wt

#endif