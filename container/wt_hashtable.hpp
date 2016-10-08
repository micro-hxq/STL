#ifndef _STL_WT_HASHTABLE_HPP_
#define _STL_WT_HASHTABLE_HPP_

namespace wt {

template <typename T>
struct hash_node {
    hash_node* next_;
    T          data_;
};

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
class hashtable;

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
class _Hashtable_const_iterator 
    : public wt::iterator<wt::forward_iterator_tag, Value> {
public:
    typedef wt::forward_iterator_tag            iterator_category;
    typedef Value                               value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef const value_type*                   pointer;
    typedef const value_type&                   reference;
    typedef hash_node<Value>                    _Node_type;
    typedef hashtable<Key, Value, KeyOfValue,
                Hash, Equal, Allocator>         _Hash_type;
    typedef _Hashtable_const_iterator<Key, Value, KeyOfValue,
                Hash, Equal, Allocator>         _Self;

    _Hashtable_const_iterator() 
    : m_ptr_(nullptr), m_phash_(nullptr) { }

    _Hashtable_const_iterator(_Node_type* _ptr, const _Hash_type* _phash)
    : m_ptr_(_ptr), m_phash_(_phash) { }

    _Hashtable_const_iterator(const _Hashtable_const_iterator& other)
    : m_ptr_(other.m_ptr_), m_phash_(other.m_phash_) { }

    ~_Hashtable_const_iterator() { }

    reference operator*() const noexcept
    {
        return m_ptr_->data_;
    }

    pointer operator->() const noexcept
    {
        return &(m_ptr_->data_);
    }

    _Self& operator++() noexcept;
    _Self operator++(int) noexcept;

    bool operator==(_Self& other) const noexcept
    {
        return m_ptr_ == other.m_ptr_ ;
    }

    bool operator!=(_Self& other) const noexcept
    {
        return m_ptr_ != other.m_ptr_;
    }

    _Node_type*     m_ptr_;
    const _Hash_type*     m_phash_;
};


template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
class _Hashtable_iterator : public _Hashtable_const_iterator<Key,
                         Value, KeyOfValue, Hash, Equal, Allocator> {
public:
    typedef _Hashtable_const_iterator<Key, Value, KeyOfValue,
            Hash, Equal, Allocator>         _Base;

    typedef wt::forward_iterator_tag        iterator_category;
    typedef Value                           value_type;
    typedef std::size_t                     difference_type;
    typedef value_type*                     pointer;
    typedef value_type&                     reference;
    typedef typename _Base::_Node_type      _Node_type;
    typedef typename _Base::_Hash_type      _Hash_type;

    typedef _Hashtable_iterator<Key, Value, KeyOfValue, 
                Hash, Equal, Allocator>     _Self;

    _Hashtable_iterator()
    : _Base() { }

    _Hashtable_iterator(_Node_type* _ptr, const _Hash_type* _phash)
    : _Base(_ptr, _phash) { }

    _Hashtable_iterator(const _Hashtable_iterator& other)
    : _Base(other) { }

    ~_Hashtable_iterator() { }

    reference operator*() const noexcept
    {
        return this->m_ptr_->data_;
    }

    pointer operator->() const noexcept
    {
        return &(this->m_ptr_->data_);
    }

    _Self& operator++() noexcept;
    _Self operator++(int) noexcept;

    bool operator==(const _Self& other) const noexcept
    {
        return this->m_ptr_ == other.m_ptr_;
    }

    bool operator!= (const _Self& other) const noexcept
    {
        return this->m_ptr_ != other.m_ptr_;
    }
};

static constexpr int kPrimes = 28;
static constexpr unsigned long wt_primes[kPrimes] = 
{
  53ul,         97ul,         193ul,       389ul,       769ul,
  1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
  49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
  1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
  50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
  1610612741ul, 3221225473ul, 4294967291ul
};

inline unsigned long wt_next_prime(unsigned long n)
{
    const unsigned long *last = wt_primes + kPrimes;
    const unsigned long *pos = wt::lower_bound(wt_primes, last, n);
    return pos == last ? wt_primes[kPrimes - 1] : *pos;
}

inline unsigned long wt_default_bucket_count()
{
    return wt_primes[0];
}

template <typename T>
class _Bucket_const_iterator 
        : public wt::iterator<wt::forward_iterator_tag, T> {
public:
    typedef wt::forward_iterator_tag            iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef const value_type*                   pointer;
    typedef const value_type&                   reference;
    typedef hash_node<T>                        _Node_type;
    typedef _Bucket_const_iterator<T>           _Self;

    _Bucket_const_iterator() : m_ptr_(nullptr) { }
    _Bucket_const_iterator(_Node_type* ptr) : m_ptr_(ptr) { }
    _Bucket_const_iterator(const _Self& other) : m_ptr_(other.m_ptr_) { }

    reference operator*() const noexcept
    {
        return m_ptr_->data_;
    }

    pointer operator->() const noexcept
    {
        return &(m_ptr_->data_);
    }

    _Self& operator++() noexcept
    {
        m_ptr_ = m_ptr_->next_;
        return *this;
    }

    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        ++*this;
        return temp;
    }

    bool operator==(const _Self& other) const noexcept
    {
        return m_ptr_ == other.m_ptr_;
    }

    bool operator!=(const _Self& other) const noexcept
    {
        return m_ptr_ != other.m_ptr_;
    }

    _Node_type*     m_ptr_;
};

template <typename T>
class _Bucket_iterator : public _Bucket_const_iterator<T> {
public:
    typedef _Bucket_const_iterator<T>           _Base;

    typedef wt::forward_iterator_tag            iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef value_type*                         pointer;
    typedef value_type&                         reference;
    typedef typename _Base::_Node_type          _Node_type;
    typedef _Bucket_iterator<T>                 _Self;

    _Bucket_iterator() : _Base() { }
    _Bucket_iterator(_Node_type* ptr) : _Base(ptr) { }
    _Bucket_iterator(const _Self& other) : _Base(other) { }

    reference operator*() const noexcept
    {
        return this->m_ptr_->data_;
    }

    pointer operator->() const noexcept
    {
        return &(this->m_ptr_->data_);
    }

    _Self& operator++() noexcept
    {
        this->m_ptr_ = this->m_ptr_->next_;
        return *this;
    }

    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        ++*this;
        return temp;
    }

    bool operator==(const _Self& other) const noexcept
    {
        return this->m_ptr_ == other.m_ptr_;
    }

    bool operator!=(const _Self& other) const noexcept
    {
        return this->m_ptr_ != other.m_ptr_;
    }

};

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
class hashtable {
public:
    typedef Key                             key_type;
    typedef Value                           value_type;
    typedef std::size_t                     size_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef Hash                            hasher;
    typedef Equal                           key_equal;
    typedef value_type&                     reference;
    typedef const value_type&               const_reference;
    typedef value_type*                     pointer;
    typedef const value_type*               const_pointer;

    typedef _Hashtable_iterator<Key, Value, KeyOfValue,
                Hash, Equal, Allocator>     iterator;
    typedef _Hashtable_const_iterator<Key, value_type, KeyOfValue,
                Hash, Equal, Allocator>     const_iterator;

    typedef _Bucket_iterator<Value>         local_iterator;
    typedef _Bucket_const_iterator<Value>   const_local_iterator;
    typedef hash_node<Value>                _Node_type;

    typedef typename Allocator::template rebind<_Node_type>::other allocator_type;

    allocator_type get_allocator() const
    {
        return m_alloc_;
    }

    hashtable(size_type _count, 
              const hasher& _hash,
              const key_equal& _equal,
              const KeyOfValue& _get_key ,
              const allocator_type& _alloc = allocator_type())
    : m_alloc_(_alloc), m_hash_(_hash), m_equal_(_equal),
      m_get_key_(_get_key), m_buckets_(_alloc), m_count_(0)
    {
        _initialize_hashtable(_count);
    }

    hashtable(size_type _count,
              const hasher& _hash,
              const key_equal& _equal,
              const allocator_type& _alloc = allocator_type())
    : m_alloc_(_alloc), m_hash_(_hash), m_equal_(_equal),
      m_get_key_(KeyOfValue()), m_buckets_(_alloc), m_count_(0)
    {
        _initialize_hashtable(_count);
    }

    // TODO

    hashtable(const hashtable& other)
    : m_alloc_(other.get_allocator()), m_hash_(other.m_hash_),
      m_equal_(other.m_equal_), m_get_key_(other.m_get_key_),
      m_buckets_(other.get_allocator()), m_count_(0)
    {
        copy_hashtable(other);
    }

    hashtable(const hashtable& other, const allocator_type& _alloc)
    : m_alloc_(_alloc), m_hash_(other.m_hash_),
      m_equal_(other.m_equal_), m_get_key_(other.m_get_key_),
      m_buckets_(_alloc), m_count_(0)
    {
        copy_hashtable(other);
    }

    hashtable(hashtable&& other) noexcept
    {
        this->swap(other);
    }

    hashtable& operator=(const hashtable& other)
    {
        if(this != &other)
        {
            clear();
            m_hash_     = other.m_hash_;
            m_equal_    = other.m_equal_;
            m_get_key_  = other.m_get_key_;
            copy_hashtable(other);
        }
        return *this;
    }

    hashtable& operator=(hashtable&& other) noexcept
    {
        this->swap(other);
        return *this;
    }

    ~hashtable() 
    {
        this->clear();
    }

    /**
     *  Iterator Operations
     */
    iterator begin() noexcept
    {
        size_type bkt_count = m_buckets_.size();
        for(size_type i = 0; i < bkt_count; ++i)
        {
            if(m_buckets_[i])
                return iterator(m_buckets_[i], this);
        }
        return iterator(nullptr, this);
    }
    const_iterator begin() const noexcept
    {
        size_type bkt_count = m_buckets_.size();
        for(size_type i = 0; i < bkt_count; ++i)
        {
            if(m_buckets_[i])
                return const_iterator(m_buckets_[i], this);
        }
        return const_iterator(nullptr, this);
    }
    const_iterator cbegin() const noexcept
    {
        return this->begin();
    }

    iterator end() noexcept
    {
        return iterator(nullptr, this);
    }
    const_iterator end() const noexcept
    {
        return const_iterator(nullptr, this);
    }
    const_iterator cend() const noexcept
    {
        return this->end();
    }

    /**
     *  Capacity Operations
     */
    bool empty() const noexcept
    {
        return m_count_ == 0;
    }

    size_type size() const noexcept
    {
        return m_count_;
    }

    size_type max_size() const noexcept
    {
        return static_cast<size_type>(-1);
    }

    /**
     *  Bucket Interface
     */
    local_iterator begin(size_type _idx) noexcept
    {
        return local_iterator(m_buckets_[_idx]);
    }
    const_local_iterator begin(size_type _idx) const noexcept
    {
        return const_local_iterator(m_buckets_[_idx]);
    }
    const_local_iterator cbegin(size_type _idx) const noexcept
    {
        return const_local_iterator(m_buckets_[_idx]);
    }

    local_iterator end(size_type _idx) noexcept
    {
        return local_iterator(nullptr);
    }
    const_local_iterator end(size_type _idx) const noexcept
    {
        return const_local_iterator(nullptr);
    }
    const_local_iterator cend(size_type _idx) const noexcept
    {
        return const_local_iterator(nullptr);
    }

    size_type bucket_count() const
    {
        return m_buckets_.size();
    }

    size_type max_bucket_count() const
    {
        return wt_primes[kPrimes - 1];
    }

    size_type bucket_size(size_type _bkt_idx) const
    {
        size_type count = 0;
        for(_Node_type* cur = m_buckets_[_bkt_idx]; cur; cur = cur->next_)
            ++count;
        return count;
    }
    size_type bucket(const key_type& _key) const
    {
        return get_bkt_idx_by_key(_key);
    }

    /**
     *  Hash Policy
     */
    float load_factor() const
    {
        return static_cast<float>(size()) / bucket_count();
    }

    //  TODO: max_load_factor

    void rehash(size_type n)
    {
        resize_request(n);
    }

    // TODO: reserve

    /**
     *  Modify Operations
     */
    void clear();

    
    wt::pair<iterator, bool> insert_unique(const value_type& _value)
    {
        resize_request(m_count_ + 1);
        return insert_unique_noresize(_value);
    }

    iterator insert_equal(const value_type& _value)
    {
        resize_request(m_count_ + 1);
        return insert_equal_noresize(_value);
    }

    template <typename InputIter>
    void insert_unique(InputIter _first, InputIter _last)
    {
        _insert_unique(_first, _last, _ITERATOR_CATEGORY(_first));
    }

    template <typename InputIter>
    void insert_equal(InputIter _first, InputIter _last)
    {
        _insert_equal(_first, _last, _ITERATOR_CATEGORY(_first));
    }

    iterator erase(const_iterator _pos);
    iterator erase(const_iterator _first, const_iterator _last);
    size_type erase(const key_type& _key);

    void swap(hashtable& other) noexcept
    {
        wt::swap(m_hash_, other.m_hash_);
        wt::swap(m_equal_, other.m_equal_);
        wt::swap(m_get_key_, other.m_get_key_);
        wt::swap(m_buckets_, other.m_buckets_);
        wt::swap(m_count_, other.m_count_);
    }

    /**
     *  Lookup Operations
     */
    iterator find(const key_type& _key)
    {
        size_type bkt_idx = get_bkt_idx_by_key(_key);
        for(auto cur = m_buckets_[bkt_idx]; cur; cur = cur->next_)
        {
            if(m_equal_(m_get_key_(cur->data_), _key))
                return iterator(cur, this);
        }
        return iterator(nullptr, this);
    }
    const_iterator find(const key_type& _key) const
    {
        size_type bkt_idx = get_bkt_idx_by_key(_key);
        for(auto cur = m_buckets_[bkt_idx]; cur; cur = cur->next_)
        {
            if(m_equal_(m_get_key_(cur->data_), _key))
                return const_iterator(cur, this);
        }
        return const_iterator(nullptr, this); 
    }

    reference find_or_insert(const value_type& _value);

    size_type count(const key_type& _key) const;

    wt::pair<iterator, iterator>
    equal_range(const key_type& _key);
    wt::pair<const_iterator, const_iterator> 
    equal_range(const key_type& _key) const;
    /**
     *  Oberver
     */

    hasher hash_function() const
    {
        return m_hash_;
    }

    key_equal key_eq() const
    {
        return m_equal_;
    }
private:
    friend struct _Hashtable_iterator<Key, Value, KeyOfValue,
                                    Hash, Equal, Allocator>;
    friend struct _Hashtable_const_iterator<Key, value_type, KeyOfValue,
                                    Hash, Equal, Allocator>;
    template <typename _K, typename _V, typename _KV, typename _H,
              typename _E, typename _A>
    friend bool operator==(const hashtable<_K, _V, _KV, _H, _E, _A>&,
                           const hashtable<_K, _V, _KV, _H, _E, _A>&);                                
    
    _Node_type* _alloc_node()
    {
        return m_alloc_.allocate(1);
    }

    void _dealloc_node(_Node_type* _p)
    {
        m_alloc_.deallocate(_p, 1);
    }

    _Node_type* _create_node(const value_type& _value)
    {
        _Node_type* pnode = _alloc_node();
        try {
            wt::construct(&pnode->data_, _value);
        } catch(...) {
            _dealloc_node(pnode);
            throw;
        }
        pnode->next_ = nullptr;
        return pnode;
    }

    void _delete_node(_Node_type* _p)
    {
        wt::destroy(&_p->data_);
        _dealloc_node(_p);
    }

    size_type _next_size(size_type _n) const
    {
        return wt_next_prime(_n);
    }

    size_type get_bkt_idx_by_key(const key_type& _key, size_type _n) const
    {
        return m_hash_(_key) % _n;
    }

    size_type get_bkt_idx_by_key(const key_type& _key) const
    {
        return get_bkt_idx_by_key(_key, m_buckets_.size());
    }

    size_type get_bkt_idx(const value_type& _value) const
    {
        return get_bkt_idx_by_key(m_get_key_(_value), m_buckets_.size());
    }

    size_type get_bkt_idx(const value_type& _value, size_type _n) const
    {
        return get_bkt_idx_by_key(m_get_key_(_value), _n);
    }

    void _initialize_hashtable(size_type _n)
    {
        size_type bkt_count = _next_size(_n);
        m_buckets_.reserve(bkt_count);
        m_buckets_.insert(m_buckets_.cend(), bkt_count, nullptr);
        m_count_ = 0;
    }

    void copy_hashtable(const hashtable& _ht);
    void resize_request(size_type cap);

    wt::pair<iterator, bool> insert_unique_noresize(const value_type& _value);

    iterator insert_equal_noresize(const value_type& _value);

    template <typename InputIter>
    void _insert_unique(InputIter _first, InputIter _last, 
                        wt::input_iterator_tag)
    {
        for(; _first != _last; ++_first)
            insert_unique(*_first);
    }

    template <typename ForwardIter>
    void _insert_unique(ForwardIter _first, ForwardIter _last, 
                        wt::forward_iterator_tag)
    {
        size_type count = wt::distance(_first, _last);
        resize_request(m_count_ + count);
        for(; count > 0; --count, ++_first)
            insert_unique_noresize(*_first);
    }

    template <typename InputIter>
    void _insert_equal(InputIter _first, InputIter _last,
                       wt::input_iterator_tag)
    {
        for(; _first != _last; ++_first)
            insert_equal(*_first);
    }

    template <typename ForwardIter>
    void _insert_equal(ForwardIter _first, ForwardIter _last,
                       wt::forward_iterator_tag)
    {
        size_type count = wt::distance(_first, _last);
        resize_request(m_count_ + count);
        for(; count > 0; --count, ++_first)
            insert_equal_noresize(*_first);
    }

    void _erase_bucket_element(size_type _idx, _Node_type* _first, 
                               _Node_type* _last);

    
private:
    allocator_type  m_alloc_;

    hasher          m_hash_;
    key_equal       m_equal_;
    KeyOfValue      m_get_key_;
    wt::vector<_Node_type*, Allocator>  m_buckets_;
    size_type       m_count_;
};

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
_Hashtable_const_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>&
_Hashtable_const_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::operator++() noexcept
{
    const _Node_type* cur = m_ptr_;
    m_ptr_ = m_ptr_->next_;
    if(!m_ptr_)
    {
        auto bkt_idx = m_phash_->get_bkt_idx(cur->data_);
        while(!m_ptr_ && ++bkt_idx < m_phash_->m_buckets_.size())
            m_ptr_ = m_phash_->m_buckets_[bkt_idx];
    }
    return *this;
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
_Hashtable_const_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>
_Hashtable_const_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::operator++(int) noexcept
{
    _Self temp = *this;
    ++*this;
    return temp;
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
_Hashtable_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>&
_Hashtable_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::operator++() noexcept
{
    _Node_type* cur = this->m_ptr_;
    this->m_ptr_ = this->m_ptr_->next_;
    if(!this->m_ptr_)
    {
        auto bkt_idx = this->m_phash_->get_bkt_idx(cur->data_);
        while(!this->m_ptr_ && ++bkt_idx < this->m_phash_->m_buckets_.size())
            this->m_ptr_ = this->m_phash_->m_buckets_[bkt_idx];
    }
    return *this;
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
_Hashtable_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>
_Hashtable_iterator<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::operator++(int) noexcept
{
    _Self temp = *this;
    ++*this;
    return temp;
}

/**
 *  Implementation
 */

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
void
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::copy_hashtable(const hashtable& _ht)
{
    m_buckets_.clear();
    size_type bkt_count = _ht.m_buckets_.size();
    m_buckets_.reserve(bkt_count);
    m_buckets_.insert(m_buckets_.cend(), bkt_count, nullptr);
    try {
        for(size_type i = 0; i < bkt_count; ++i)
        {
            _Node_type* cur = _ht.m_buckets_[i];
            if(cur)
            {
                auto node = _create_node(cur->data_);
                m_buckets_[i] = node;
                for(cur = cur->next_; cur; cur = cur->next_)
                {
                    node->next_ = _create_node(cur->data_);
                    node = node->next_;
                }
            }
        }
        m_count_ = _ht.m_count_;
    } catch(...) {
        clear();
        throw;
    }
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
wt::pair<typename hashtable<Key, Value, KeyOfValue, Hash,
    Equal, Allocator>::iterator, bool>
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::insert_unique_noresize(const value_type& _value)
{
    size_type bkt_idx = get_bkt_idx(_value);
    auto cur = m_buckets_[bkt_idx];
    while(cur)
    {
        if(m_equal_(m_get_key_(cur->data_), m_get_key_(_value)))
            return wt::make_pair(iterator(cur, this), false);
        cur = cur->next_;
    }
    auto node = _create_node(_value);
    node->next_ = m_buckets_[bkt_idx];
    m_buckets_[bkt_idx] = node;
    ++m_count_;
    return wt::make_pair(iterator(node, this), true);
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
typename hashtable<Key, Value, KeyOfValue, Hash,
                   Equal, Allocator>::iterator
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::insert_equal_noresize(const value_type& _value)
{
    size_type bkt_idx = get_bkt_idx(_value);
    auto cur = m_buckets_[bkt_idx];
    auto node = _create_node(_value);
    while(cur)
    {
        if(m_equal_(m_get_key_(cur->data_), m_get_key_(_value)))
        {
            node->next_ = cur->next_;
            cur->next_ = node;
            ++m_count_;
            return iterator(node, this);
        }
        cur = cur->next_;
    }
    node->next_ = m_buckets_[bkt_idx];
    m_buckets_[bkt_idx] = node;
    ++m_count_;
    return iterator(node, this);
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
void
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::resize_request(size_type cap)
{
    size_type old_size = m_buckets_.size();
    if(cap > old_size)
    {
        size_type new_bkt_num = _next_size(cap);
        wt::vector<_Node_type*, Allocator> temp(new_bkt_num, nullptr,
                                                m_buckets_.get_allocator());
        for(size_type i = 0; i < old_size; ++i)
        {
            auto first = m_buckets_[i];
            while(first)
            {
                m_buckets_[i] = first->next_;
                auto new_bkt_idx = get_bkt_idx(first->data_, new_bkt_num);
                first->next_ = temp[new_bkt_idx];
                temp[new_bkt_idx] = first;
                first = m_buckets_[i];
            }
        }
        m_buckets_.swap(temp);
    }
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
void
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::_erase_bucket_element(size_type _idx, _Node_type* _first, _Node_type* _last)
{
    auto cur = m_buckets_[_idx];
    if(cur == _first)
    {
        while(cur != _last)
        {
            auto next = cur->next_;
            _delete_node(cur);
            --m_count_;
            cur = next;
            m_buckets_[_idx] = cur;
        }
    }
    else
    {
        while(cur->next_ != _first)
            cur = cur->next_;
        for(auto next = cur->next_; next != _last; next = cur->next_)
        {
            cur->next_ = next->next_;
            _delete_node(next);
            --m_count_;
        }
    }
}

/**
 *  Interface
 */

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
void
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::clear()
{
    size_type bkt_count = m_buckets_.size();
    for(size_type i = 0; i < bkt_count; ++i)
    {
        auto cur = m_buckets_[i];
        while(cur)
        {
            auto next = cur->next_;
            _delete_node(cur);
            cur = next;
        }
        m_buckets_[i] = nullptr;
    }
    m_count_ = 0;
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
typename hashtable<Key, Value, KeyOfValue, Hash, 
                   Equal, Allocator>::iterator
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::erase(const_iterator _pos)
{
    auto ptr = _pos.m_ptr_;
    if(ptr) {
        size_type bkt_idx = get_bkt_idx(ptr->data_);
        auto cur = m_buckets_[bkt_idx];
        if(cur == ptr)
            m_buckets_[bkt_idx] = cur->next_;
        else
        {
            while(cur->next_ != ptr)
                cur = cur->next_;
            cur->next_ = ptr->next_;
            cur = ptr;
        }
        ptr = ptr->next_;
        _delete_node(cur);
        --m_count_;
    }
    return iterator(ptr, this);
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
typename hashtable<Key, Value, KeyOfValue, Hash, 
                   Equal, Allocator>::iterator
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::erase(const_iterator _first, const_iterator _last)
{
    if(_first == _last)
        return iterator(_first.m_ptr_, this);
    auto first = _first.m_ptr_;
    auto last = _last.m_ptr_;
    size_type idx1 = first ? get_bkt_idx(first->data_) : m_buckets_.size();
    size_type idx2 = last  ? get_bkt_idx(last->data_)  : m_buckets_.size();

    if(idx1 == idx2)
        _erase_bucket_element(idx1, first, last);
    else
    {
        _erase_bucket_element(idx1, first, nullptr);
        for(auto cur_idx = idx1 + 1; cur_idx < idx2; ++cur_idx)
            _erase_bucket_element(cur_idx, m_buckets_[cur_idx], nullptr);
        if(idx2 != m_buckets_.size())
            _erase_bucket_element(idx2, m_buckets_[idx2], last);
    }
    return iterator(last, this);
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
typename hashtable<Key, Value, KeyOfValue, Hash, 
                   Equal, Allocator>::size_type
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::erase(const key_type& _key)
{
    size_type bkt_idx = get_bkt_idx_by_key(_key);
    size_type result = 0;
    auto first = m_buckets_[bkt_idx];
    if(first)
    {
        auto cur = first;
        for(auto next = cur->next_; next; cur = next, next = cur->next_)
        {
            if(m_equal_(m_get_key_(next->data_), _key))
            {
                do {
                    ++result;
                    cur->next_ = next->next_;
                    _delete_node(next);
                    next = cur->next_;
                    --m_count_;
                } while(m_equal_(m_get_key_(next->data_), _key));

                break;
            }
        }

        if(m_equal_(m_get_key_(first->data_), _key))
        {
            ++result;
            m_buckets_[bkt_idx] = first->next_;
            _delete_node(first);
            --m_count_;
        }
    }
    return result;
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
typename hashtable<Key, Value, KeyOfValue, Hash,
                   Equal, Allocator>::reference
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::find_or_insert(const value_type& _value)
{
    resize_request(m_count_ + 1);
    size_type bkt_idx = get_bkt_idx(_value);
    auto first = m_buckets_[bkt_idx];

    for(auto cur = first; cur; cur = cur->next_)
        if(m_equal_(m_get_key_(cur->data_), m_get_key_(_value)))
            return cur->data_;

    auto temp = _create_node(_value);
    temp->next_ = first;
    m_buckets_[bkt_idx] = temp;
    ++m_count_;
    return temp->data_;
}


template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
typename hashtable<Key, Value, KeyOfValue, Hash,
                   Equal, Allocator>::size_type
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::count(const key_type& _key) const
{
    size_type bkt_idx = get_bkt_idx_by_key(_key);
    for(auto cur = m_buckets_[bkt_idx]; cur; cur = cur->next_)
    {
        if(m_equal_(m_get_key_(cur->data_), _key))
        {
            size_type result = 0;
            do {
                ++result;
                cur = cur->next_;
            } while(m_equal_(m_get_key_(cur->data_), _key));
            return result;
        }
    }
    return 0;
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
wt::pair<typename hashtable<Key, Value, KeyOfValue, Hash, 
                            Equal, Allocator>::iterator,
         typename hashtable<Key, Value, KeyOfValue, Hash,
                            Equal, Allocator>::iterator>
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::equal_range(const key_type& _key)
{
    auto first = this->find(_key);
    if(first == end())
        return wt::make_pair(end(), end());
    auto last = first;
    for(++last; last != end() && m_equal_(m_get_key_(*last)); ++last)
        ;
    return wt::make_pair(first, last);
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
wt::pair<typename hashtable<Key, Value, KeyOfValue, Hash, 
                            Equal, Allocator>::const_iterator,
         typename hashtable<Key, Value, KeyOfValue, Hash,
                            Equal, Allocator>::const_iterator>
hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>
::equal_range(const key_type& _key) const
{
    auto first = this->find(_key);
    if(first == end())
        return wt::make_pair(end(), end());
    auto last = first;
    for(++last; last != end() && m_equal_(m_get_key_(*last)); ++last)
        ;
    return wt::make_pair(first, last);
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
bool 
operator==(const hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>& lhs,
           const hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>& rhs)
{
    if(lhs.size() != rhs.size() 
                    || lhs.m_buckets_.size() != rhs.m_buckets_.size())
        return false;

    return wt::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
inline bool 
operator!=(const hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>& lhs,
           const hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
void
swap(const hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>& lhs,
     const hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>& rhs)
{
    lhs.swap(rhs);
}

} // namespace wt

#endif