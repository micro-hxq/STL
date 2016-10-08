#ifndef _STL_WT_UNORDERED_MAP_HPP_
#define _STL_WT_UNORDERED_MAP_HPP_

namespace wt {

template <typename Key, typename T,
          typename Hash = wt::hash<Key>,
          typename KeyEqual = wt::equal_to<Key>,
          typename Allocator = wt::allocator<wt::pair<const Key, T>>>
class unordered_map;

template <typename Key, typename T, typename Hash,
          typename KeyEqual, typename Allocator>
class unordered_map {
    typedef wt::hashtable<Key, wt::pair<const Key, T>,
                          _Pair1st<wt::pair<const Key, T>>,
                          Hash, KeyEqual, Allocator>        _Impl_type;
public:
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef wt::pair<const Key, T>                      value_type;
    typedef typename _Impl_type::size_type              size_type;
    typedef typename _Impl_type::difference_type        difference_type;
    typedef typename _Impl_type::hasher                 hasher;
    typedef typename _Impl_type::key_equal              key_equal;
    typedef typename _Impl_type::allocator_type         allocator_type;
    typedef typename _Impl_type::reference              reference;
    typedef typename _Impl_type::const_reference        const_reference;
    typedef typename _Impl_type::pointer                pointer;
    typedef typename _Impl_type::const_pointer          const_pointer;
    typedef typename _Impl_type::iterator               iterator;
    typedef typename _Impl_type::const_iterator         const_iterator;
    typedef typename _Impl_type::local_iterator         local_iterator;
    typedef typename _Impl_type::const_local_iterator   const_local_iterator;

    unordered_map() 
    : unordered_map(wt_default_bucket_count()) 
    { }

    explicit unordered_map(size_type _bcount,
                           const hasher& _hash = hasher(),
                           const key_equal& _equal = key_equal(),
                           const allocator_type& _alloc = allocator_type())
    : m_impl_(_bcount, _hash, _equal, _alloc) 
    { }

    unordered_map(size_type _bcount, const allocator_type& _alloc)
    : m_impl_(_bcount, hasher(), key_equal(), _alloc) 
    { }

    unordered_map(size_type _bcount, const hasher& _hash, 
                  const allocator_type& _alloc)
    : m_impl_(_bcount, _hash, key_equal(), _alloc) 
    { }

    explicit unordered_map(const allocator_type& _alloc)
    : m_impl_(wt_default_bucket_count(), hasher(), key_equal(), _alloc) 
    { }

    template <typename InputIter>
    unordered_map(InputIter _first, InputIter _last,
                  size_type _bcount = wt_default_bucket_count(),
                  const hasher& _hash = hasher(),
                  const key_equal& _equal = key_equal(),
                  const allocator_type& _alloc = allocator_type())
    : m_impl_(_bcount, _hash, _equal, _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    template <typename InputIter>
    unordered_map(InputIter _first, InputIter _last,
                  size_type _bcount, const allocator_type& _alloc)
    : m_impl_(_bcount, hasher(), key_equal(), _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    template <typename InputIter>
    unordered_map(InputIter _first, InputIter _last,
                  size_type _bcount, const hasher& _hash,
                  const allocator_type& _alloc)
    : m_impl_(_bcount, _hash, key_equal(), _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    unordered_map(const unordered_map& other)
    : m_impl_(other.m_impl_)
    { }

    unordered_map(const unordered_map& other, const allocator_type& _alloc)
    : m_impl_(other.m_impl_, _alloc)
    { }

    // TODO: unordered_map(unordered_map&&)

    unordered_map(std::initializer_list<value_type> _ilist,
                  size_type _bcount = wt_default_bucket_count(),
                  const hasher& _hash = hasher(),
                  const key_equal& _equal = key_equal(),
                  const allocator_type& _alloc = allocator_type())
    : m_impl_(_bcount, _hash, _equal, _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    unordered_map(std::initializer_list<value_type>& _ilist,
                  size_type _bcount, const allocator_type& _alloc)
    : m_impl_(_bcount, hasher(), key_equal(), _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    unordered_map(std::initializer_list<value_type> _ilist,
                  size_type _bcount, const hasher& _hash,
                  const allocator_type& _alloc)
    : m_impl_(_bcount, _hash, key_equal(), _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    ~unordered_map()
    { }

    unordered_map& operator=(const unordered_map& other)
    {
        m_impl_ = other.m_impl_;
        return *this;
    }

    // TODO: operator=(unordered_map&&)
    
    unordered_map& operator=(std::initializer_list<value_type> _ilist)
    {
        m_impl_.clear();
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
        return *this;
    }

    allocator_type get_allocator() const
    {
        return m_impl_.get_allocator();
    }

    /**
     *  Iterator
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

    /**
     *  Capacity
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
     *  Modify
     */
    void clear()
    {
        m_impl_.clear();
    }

    wt::pair<iterator, bool>
    insert(const value_type& _value)
    {
        return m_impl_.insert_unique(_value);
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

    void swap(unordered_map& other)
    {
        m_impl_.swap(other.m_impl_);
    }

    /**
     *  Lookup
     */
    mapped_type& at(const key_type& _key)
    {
        auto iter = find(_key);
        if(iter == end())
            throw std::out_of_range("unordered_map");
        return iter->second;
    }

    const mapped_type& at(const key_type& _key) const
    {
        auto iter = find(_key);
        if(iter == end())
            throw std::out_of_range("unordered_map");
        return iter->second;
    }

    mapped_type& operator[](const key_type& _key)
    {
        return m_impl_.find_or_insert(value_type(_key, mapped_type())).second;
    }
    
    // TODO: operator[](key_type&&)

    size_type count(const key_type& _key) const
    {
        return m_impl_.count(_key);
    }

    iterator find(const key_type& _key) 
    {
        return m_impl_.find(_key);
    }

    const_iterator find(const key_type& _key) const
    {
        return m_impl_.find(_key);
    }

    wt::pair<iterator, iterator>
    equal_range(const key_type& _key)
    {
        return m_impl_.equal_range(_key);
    }

    wt::pair<const_iterator, const_iterator>
    equal_range(const key_type& _key) const
    {
        return m_impl_.equal_range(_key);
    }

    /**
     *  Bucket Interface
     */
    local_iterator begin(size_type _index)
    {
        return m_impl_.begin(_index);
    }
    const_local_iterator begin(size_type _index) const
    {
        return m_impl_.begin(_index);
    }
    const_local_iterator cbegin(size_type _index) const
    {
        return m_impl_.cbegin(_index);
    }

    local_iterator end(size_type _index)
    {
        return m_impl_.end(_index);
    }
    const_local_iterator end(size_type _index) const
    {
        return m_impl_.end(_index);
    }
    const_local_iterator cend(size_type _index) const
    {
        return m_impl_.cend(_index);
    }

    size_type bucket_count() const
    {
        return m_impl_.bucket_count();
    }

    size_type max_bucket_count() const
    {
        return m_impl_.max_bucket_count();
    }

    size_type bucket_size(size_type _index) const
    {
        return m_impl_.bucket_size(_index);
    }

    size_type bucket(const key_type& _key) const
    {
        return m_impl_.bucket(_key);
    }

    /**
     *  Hash Policy
     */
    float load_factor() const
    {
        return m_impl_.load_factor();
    }

    // TODO: max_load_factor()

    void rehash(size_type _bcount)
    {
        m_impl_.rehash(_bcount);
    }

    // TODO: reserve

    /**
     *  Observer
     */
    hasher hash_function() const
    {
        return m_impl_.hash_function();
    }

    key_equal key_eq() const 
    {
        return m_impl_.key_eq();
    }

    template <typename _K, typename _T, typename _H, typename _KE, typename _A>
    friend bool operator==(const unordered_map<_K, _T, _H, _KE, _A>& lhs,
                           const unordered_map<_K, _T, _H, _KE, _A>& rhs);
private:
    _Impl_type      m_impl_;
};

template <typename Key, typename T, typename Hash,
          typename KeyEqual, typename Allocator>
bool
operator==(const unordered_map<Key, T, Hash, KeyEqual, Allocator>& lhs,
           const unordered_map<Key, T, Hash, KeyEqual, Allocator>& rhs)
{
    return lhs.m_impl_ == rhs.m_impl_;
}

template <typename Key, typename T, typename Hash,
          typename KeyEqual, typename Allocator>
bool
operator!=(const unordered_map<Key, T, Hash, KeyEqual, Allocator>& lhs,
           const unordered_map<Key, T, Hash, KeyEqual, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename T, typename Hash,
          typename KeyEqual, typename Allocator>
void
swap(const unordered_map<Key, T, Hash, KeyEqual, Allocator>& lhs,
     const unordered_map<Key, T, Hash, KeyEqual, Allocator>& rhs)
{
    lhs.swap(rhs);
}

} // namespace wt

#endif