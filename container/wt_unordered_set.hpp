#ifndef _STL_WT_UNORDERED_SET_HPP_
#define _STL_WT_UNORDERED_SET_HPP_

namespace wt {

template <typename Key,
          typename Hash = wt::hash<Key>,
          typename KeyEqual = wt::equal_to<Key>,
          typename Allocator = wt::allocator<Key>>
class unordered_set;

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
class unordered_set {
public:
    typedef wt::hashtable<Key, Key, wt::_Identity<Key>, 
                Hash, KeyEqual, Allocator>              _Impl_type;
    typedef typename _Impl_type::key_type               key_type;
    typedef typename _Impl_type::value_type             value_type;
    typedef typename _Impl_type::size_type              size_type;
    typedef typename _Impl_type::difference_type        difference_type;
    typedef typename _Impl_type::hasher                 hasher;
    typedef typename _Impl_type::key_equal              key_equal;
    typedef typename _Impl_type::allocator_type         allocator_type;
    typedef typename _Impl_type::reference              reference;
    typedef typename _Impl_type::const_reference        const_reference;
    typedef typename _Impl_type::pointer                pointer;
    typedef typename _Impl_type::const_pointer          const_pointer;
    typedef typename _Impl_type::const_iterator         iterator;
    typedef typename _Impl_type::const_iterator         const_iterator;
    typedef typename _Impl_type::local_iterator         local_iterator;
    typedef typename _Impl_type::const_local_iterator   const_local_iterator;

    unordered_set() : unordered_set(wt_default_bucket_count()) { }
    explicit unordered_set(size_type _bcount,
                           const hasher& _hash = hasher(),
                           const key_equal& _equal = key_equal(),
                           const allocator_type& _alloc = allocator_type())
    : m_impl_(_bcount, _hash, _equal, _alloc) { }

    unordered_set(size_type _bcount, const allocator_type& _alloc)
    : m_impl_(_bcount, hasher(), key_equal(), _alloc) { }

    unordered_set(size_type _bcount, const hasher& _hash, 
                  const allocator_type& _alloc)
    : m_impl_(_bcount, _hash, key_equal(), _alloc) { }

    explicit unordered_set(const allocator_type& _alloc)
    : m_impl_(wt_default_bucket_count(), hasher(), key_equal(), _alloc) { }

    template <typename InputIter>
    unordered_set(InputIter _first, InputIter _last,
                  size_type _bcount = wt_default_bucket_count(),
                  const hasher& _hash = hasher(),
                  const key_equal& _equal = key_equal(),
                  const allocator_type& _alloc = allocator_type())
    : m_impl_(_bcount, _hash, _equal, _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    template <typename InputIter>
    unordered_set(InputIter _first, InputIter _last,
                  size_type _bcount, const allocator_type& _alloc)
    : m_impl_(_bcount, hasher(), key_equal(), _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    template <typename InputIter>
    unordered_set(InputIter _first, InputIter _last,
                  size_type _bcount, const hasher& _hash,
                  const allocator_type& _alloc)
    : m_impl_(_bcount, _hash, key_equal(), _alloc)
    {
        m_impl_.insert_unique(_first, _last);
    }

    unordered_set(const unordered_set& other)
    : m_impl_(other.m_impl_) { }

    unordered_set(const unordered_set& other, const allocator_type& _alloc)
    : m_impl_(other.m_impl_, _alloc) { }

    // unordered_set(unordered_set&& other)
    // : m_impl_(wt::move(other.m_impl_)) { }

    unordered_set(std::initializer_list<value_type> _ilist,
                  size_type _bcount = wt_default_bucket_count(),
                  const hasher& _hash = hasher(),
                  const key_equal& _equal = key_equal(),
                  const allocator_type& _alloc = allocator_type())
    : m_impl_(_bcount, _hash, _equal, _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    unordered_set(std::initializer_list<value_type> _ilist,
                  size_type _bcount, const allocator_type& _alloc)
    : m_impl_(_bcount, hasher(), key_equal(), _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    unordered_set(std::initializer_list<value_type> _ilist,
                 size_type _bcount, const hasher& _hash,
                 const allocator_type& _alloc)
    : m_impl_(_bcount, _hash, key_equal(), _alloc)
    {
        m_impl_.insert_unique(_ilist.begin(), _ilist.end());
    }

    ~unordered_set() { }

    unordered_set& operator=(const unordered_set& other)
    {
        m_impl_ = other.m_impl_;
        return *this;
    }

    // unordered_set& operator=(unordered_set&& other)
    // {
    //     m_impl_.swap(other.m_impl_);
    //     return *this;
    // }

    unordered_set& operator=(std::initializer_list<value_type> _ilist)
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

    // TODO: insert

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

    void swap(unordered_set& other) noexcept
    {
        m_impl_.swap(other.m_impl_);
    }

    /**
     *  Lookup Operations
     */
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

    void rehash(size_type _bcount)
    {
        return m_impl_.rehash(_bcount);
    }

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

    template <typename _K, typename _H, typename _KE, typename _A>
    friend bool operator==(const unordered_set<_K, _H, _KE, _A>&,
                           const unordered_set<_K, _H, _KE, _A>&);
private:
    _Impl_type  m_impl_;
};

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
bool
operator==(const unordered_set<Key, Hash, KeyEqual, Allocator>& lhs,
           const unordered_set<Key, Hash, KeyEqual, Allocator>& rhs)
{
    return lhs.m_impl_ == rhs.m_impl_;
}

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
bool
operator!=(const unordered_set<Key, Hash, KeyEqual, Allocator>& lhs,
           const unordered_set<Key, Hash, KeyEqual, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
swap(const unordered_set<Key, Hash, KeyEqual, Allocator>& lhs,
     const unordered_set<Key, Hash, KeyEqual, Allocator>& rhs)
{
    lhs.swap(rhs);
}

} // namespace wt

#endif