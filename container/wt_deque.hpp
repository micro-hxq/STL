#ifndef _STL_WT_DEQUE_HPP_
#define _STL_WT_DEQUE_HPP_

namespace wt{

//  set node size
static constexpr size_t deque_node_size()
{
    return static_cast<size_t>(64);
}

template <typename T>
class _Deque_const_iterator 
        : public iterator<wt::random_access_iterator_tag, T> {
public:
    typedef typename wt::random_access_iterator_tag iterator_categroy;
    typedef T                                       value_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef const T*                                pointer;
    typedef const T&                                reference;
    typedef T**                                     _Node_pointer;

    _Deque_const_iterator() : m_cur_(nullptr), m_first_(nullptr), 
                              m_last_(nullptr), m_node_(nullptr) {}
    _Deque_const_iterator(T* _cur, _Node_pointer _node)
     : m_cur_(_cur), m_first_(*_node), m_last_(*_node + deque_node_size()),
       m_node_(_node) {}
    _Deque_const_iterator(const _Deque_const_iterator& other)
     : m_cur_(other.m_cur_), m_first_(other.m_first_), m_last_(other.m_last_),
       m_node_(other.m_node_) {}

    reference operator*() const noexcept
    {
        return *m_cur_;
    }
    reference operator->() const noexcept
    {
        return m_cur_;
    }

    _Deque_const_iterator& operator++() noexcept
    {
        ++m_cur_;
        if(m_cur_ == m_last_)
        {
            set_node(m_node_ + 1);
            m_cur_ = m_first_;
        }
        return *this;
    }
    _Deque_const_iterator operator++(int) noexcept
    {
        _Deque_const_iterator temp(*this);
        ++*this;
        return temp;
    }
    _Deque_const_iterator& operator--() noexcept
    {
        if(m_cur_ == m_first_)
        {
            set_node(m_node_ - 1);
            m_cur_ = m_last_;
        }
        --m_cur_;
        return *this;
    }
    _Deque_const_iterator operator--(int) noexcept
    {
        _Deque_const_iterator temp(*this);
        --*this;
        return temp;
    }

    _Deque_const_iterator& operator+=(difference_type _n)
    {
        difference_type count = _n + (m_cur_ - m_first_);
        if(count >= 0 && count < static_cast<difference_type>(deque_node_size()))
        {
            m_cur_ += _n;
        }
        else
        {
            difference_type node_offset = count > 0 
             ? count / static_cast<difference_type>(deque_node_size())
             : -((-count - 1) / static_cast<difference_type>(deque_node_size())) - 1;
            set_node(m_node_ + node_offset);
            m_cur_ = m_first_ + (count - node_offset * 
                     static_cast<difference_type>(deque_node_size()));
        }
        return *this;
    }

    _Deque_const_iterator& operator-=(difference_type _n)
    {
        return *this += -_n;
    }

    reference operator[](difference_type _n) const
    {
        return *(*this + _n);
    }

    inline friend _Deque_const_iterator 
    operator+(const _Deque_const_iterator& iter, difference_type _n) noexcept
    {
        _Deque_const_iterator temp(iter);
        return temp += _n;
    }

    inline friend _Deque_const_iterator 
    operator+(difference_type _n, const _Deque_const_iterator& iter)
    {
        return iter + _n;
    }

    inline friend difference_type operator-(const _Deque_const_iterator& lhs, 
                                    const _Deque_const_iterator& rhs) noexcept
    {
        return static_cast<difference_type>(deque_node_size()) *
                (lhs.m_node_ - rhs.m_node_ - 1) + (lhs.m_cur_ - lhs.m_first_) +
                (rhs.m_last_ - rhs.m_cur_);
    }

    inline friend _Deque_const_iterator 
    operator-(const _Deque_const_iterator& iter, difference_type _n) noexcept
    {
        return iter + (-_n);
    }

    inline friend bool operator==(const _Deque_const_iterator& lhs,
                                  const _Deque_const_iterator& rhs) noexcept
    {
        return lhs.m_cur_ == rhs.m_cur_;
    }

    inline friend bool operator!=(const _Deque_const_iterator& lhs,
                                  const _Deque_const_iterator& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline friend bool operator<(const _Deque_const_iterator& lhs,
                                 const _Deque_const_iterator& rhs) noexcept
    {
        return (lhs.m_node_ == rhs.m_node_) ?
                (lhs.m_cur_ < rhs.m_cur_) : (lhs.m_node_ < rhs.m_node_);
    }

    inline friend bool operator>(const _Deque_const_iterator& lhs,
                                 const _Deque_const_iterator& rhs) noexcept
    {
        return rhs < lhs;
    }

    inline friend bool operator<=(const _Deque_const_iterator& lhs,
                                  const _Deque_const_iterator& rhs) noexcept
    {
        return !(rhs < lhs);
    }

    inline friend bool operator>=(const _Deque_const_iterator& lhs,
                                  const _Deque_const_iterator& rhs) noexcept
    {
        return !(lhs < rhs);
    }

    void set_node(_Node_pointer _next_node) noexcept
    {
        m_node_  = _next_node;
        m_first_ = *_next_node;
        m_last_  = m_first_ + static_cast<difference_type>(deque_node_size());
    }

    T*              m_cur_;
    T*              m_first_;
    T*              m_last_;
    _Node_pointer   m_node_;
};

template <typename T>
class _Deque_iterator : public _Deque_const_iterator<T> {
public:
    typedef typename wt::random_access_iterator_tag iterator_categroy;
    typedef T                                       value_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef T*                                      pointer;
    typedef T&                                      reference;
    typedef T**                                     _Node_pointer;

    typedef _Deque_const_iterator<T>                _Base;
    using _Base::set_node;
    using _Base::m_cur_;
    using _Base::m_first_;
    using _Base::m_last_;
    using _Base::m_node_;

    _Deque_iterator() : _Base() {}
    _Deque_iterator(T* _cur, _Node_pointer _node)
     : _Base(_cur, _node) {}
    _Deque_iterator(const _Deque_iterator& other)
     : _Base(other) {}

    reference operator*() const noexcept
    {
        return *m_cur_;
    }
    reference operator->() const noexcept
    {
        return m_cur_;
    }

    _Deque_iterator& operator++() noexcept
    {
        ++m_cur_;
        if(m_cur_ == m_last_)
        {
            set_node(m_node_ + 1);
            m_cur_ = m_first_;
        }
        return *this;
    }
    _Deque_iterator operator++(int) noexcept
    {
        _Deque_iterator temp(*this);
        ++*this;
        return temp;
    }
    _Deque_iterator& operator--() noexcept
    {
        if(m_cur_ == m_first_)
        {
            set_node(m_node_ - 1);
            m_cur_ = m_last_;
        }
        --m_cur_;
        return *this;
    }
    _Deque_iterator operator--(int) noexcept
    {
        _Deque_iterator temp(*this);
        --*this;
        return temp;
    }

    _Deque_iterator& operator+=(difference_type _n)
    {
        difference_type count = _n + (m_cur_ - m_first_);
        if(count >= 0 && count < static_cast<difference_type>(deque_node_size()))
        {
            m_cur_ += _n;
        }
        else
        {
            difference_type node_offset = count > 0 
             ? count / static_cast<difference_type>(deque_node_size())
             : -((-count - 1) / static_cast<difference_type>(deque_node_size())) - 1;
            set_node(m_node_ + node_offset);
            m_cur_ = m_first_ + (count - node_offset * 
                     static_cast<difference_type>(deque_node_size()));
        }
        return *this;
    }

    _Deque_iterator& operator-=(difference_type _n)
    {
        return *this += -_n;
    }

    reference operator[](difference_type _n) const
    {
        return *(*this + _n);
    }

    inline friend _Deque_iterator 
    operator+(const _Deque_iterator& iter, difference_type _n) noexcept
    {
        _Deque_iterator temp(iter);
        return temp += _n;
    }

    inline friend _Deque_iterator 
    operator+(difference_type _n, const _Deque_iterator& iter)
    {
        return iter + _n;
    }

    inline friend difference_type operator-(const _Deque_iterator& lhs, 
                                           const _Deque_iterator& rhs) noexcept
    {
        return static_cast<difference_type>(deque_node_size()) *
                (lhs.m_node_ - rhs.m_node_ - 1) + (lhs.m_cur_ - lhs.m_first_) +
                (rhs.m_last_ - rhs.m_cur_);
    }

    inline friend _Deque_iterator 
    operator-(const _Deque_iterator& iter, difference_type _n) noexcept
    {
        return iter + (-_n);
    }

    inline friend bool operator==(const _Deque_iterator& lhs,
                                  const _Deque_iterator& rhs) noexcept
    {
        return lhs.m_cur_ == rhs.m_cur_;
    }

    inline friend bool operator!=(const _Deque_iterator& lhs,
                                  const _Deque_iterator& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline friend bool operator<(const _Deque_iterator& lhs,
                                 const _Deque_iterator& rhs) noexcept
    {
        return (lhs.m_node_ == rhs.m_node_) ?
                (lhs.m_cur_ < rhs.m_cur_) : (lhs.m_node_ < rhs.m_node_);
    }

    inline friend bool operator>(const _Deque_iterator& lhs,
                                 const _Deque_iterator& rhs) noexcept
    {
        return rhs < lhs;
    }

    inline friend bool operator<=(const _Deque_iterator& lhs,
                                  const _Deque_iterator& rhs) noexcept
    {
        return !(rhs < lhs);
    }

    inline friend bool operator>=(const _Deque_iterator& lhs,
                                  const _Deque_iterator& rhs) noexcept
    {
        return !(lhs < rhs);
    }
};

template <typename T, typename Allocator, bool IsStatic>
class _Deque_alloc_base {
public:
    typedef typename wt::allocator_traits<Allocator>::allocator_type allocator_type;

    allocator_type get_allocator() const
    {
        return m_node_allocator_;
    }

    _Deque_alloc_base(const allocator_type& _a)
     : m_node_allocator_(_a), m_map_allocator_(_a),
       m_map_(nullptr), m_map_size_(0) {}

protected:
    typedef typename wt::_Alloc_traits<T*, Allocator>::allocator_type 
            Map_allocator_type;
    T*  _allocate_node()
    {
        return m_node_allocator_.allocate(deque_node_size());
    }
    void _deallocate_node(T* _p) 
    {
        m_node_allocator_.deallocate(_p, deque_node_size());
    }
    T** _allocate_map(size_t _n)
    {
        return m_map_allocator_.allocate(_n);
    }
    void _deallocate_map(T** _p, size_t _n)
    {
        m_map_allocator_.deallocate(_p, _n);
    }
protected:
    allocator_type      m_node_allocator_;
    Map_allocator_type  m_map_allocator_;
    T**                 m_map_;
    size_t              m_map_size_;
};

template <typename T, typename Allocator>
class _Deque_alloc_base<T, Allocator, true> {
public:
    typedef typename wt::allocator_traits<Allocator>::allocator_type
            allocator_type;

    allocator_type get_allocator() const
    {
        return allocator_type();
    }
    _Deque_alloc_base(const allocator_type& _a) 
     : m_map_(nullptr), m_map_size_(0) {}

protected:
    typedef typename wt::_Alloc_traits<T, Allocator>::_Alloc_type
            Node_alloc_type;
    typedef typename wt::_Alloc_traits<T*, Allocator>::_Alloc_type
            Map_alloc_type;
    T*   _allocate_node()
    {
        return Node_alloc_type::allocate(deque_node_size());
    }
    void _deallocate_node(T* _p)
    {
        Node_alloc_type::deallocate(_p, deque_node_size());
    }
    T**  _allocate_map(size_t _n)
    {
        return Map_alloc_type::allocate(_n);
    }
    void _deallocate_map(T** _p, size_t _n)
    {
        Map_alloc_type::deallocate(_p, _n);
    }
protected:
    T**     m_map_;
    size_t  m_map_size_;
};

template <typename T, typename Allocator>
class Deque_base
    : public _Deque_alloc_base<T, Allocator,
                               wt::_Alloc_traits<T, Allocator>::isStatic> {
public:
    typedef _Deque_alloc_base<T, Allocator,
                              wt::_Alloc_traits<T, Allocator>::isStatic>
            _Base;

    typedef typename _Base::allocator_type  allocator_type;
    typedef _Deque_const_iterator<T>        const_iterator;
    typedef _Deque_iterator<T>              iterator;

    Deque_base(const allocator_type& _a, size_t _count)
     : _Base(_a), m_start_(), m_finish_()
    {
        _initialize_map(_count);
    }
    Deque_base(const allocator_type& _a)
     : _Base(_a), m_start_(), m_finish_() {}
    ~Deque_base();
protected:
    enum class MapSize {
        kInitMapSize = 8
    };
    using _Base::_allocate_node;
    using _Base::_deallocate_node;
    using _Base::_allocate_map;
    using _Base::_deallocate_map;
    using _Base::m_map_;
    using _Base::m_map_size_;
    
    void _initialize_map(size_t _n);
    void _create_nodes(T** _start, T** _finish);
    void _destroy_nodes(T** _start, T** _finish);

 protected:
    iterator m_start_;  // begin at m_start_.m_cur_
    iterator m_finish_; // end at m_finish_.m_cur_
};

template <typename T, typename Allocator>
Deque_base<T, Allocator>::~Deque_base()
{
    if(m_map_)
    {
        _destroy_nodes(m_start_.m_node_, m_finish_.m_node_ + 1); // past the last element
        _deallocate_map(m_map_, m_map_size_);
    }
}

template <typename T, typename Allocator>
void Deque_base<T, Allocator>::_initialize_map(size_t _n)
{
    size_t node_count = _n / deque_node_size() + 1;
    m_map_size_ = wt::max(static_cast<size_t>(MapSize::kInitMapSize), node_count);
    m_map_ = _allocate_map(m_map_size_);
    T** start = m_map_ + (m_map_size_ - node_count) / 2;
    T** finish = start + node_count;
    try {
        _create_nodes(start, finish);
    } 
    catch(...) {
        _destroy_nodes(start, finish);
        m_map_ = nullptr;
        m_map_size_ = 0;
        throw;
    }
    m_start_.set_node(start);
    m_finish_.set_node(finish - 1);
    m_start_.m_cur_  = m_start_.m_first_;
    m_finish_.m_cur_ = m_finish_.m_first_ + _n % deque_node_size();
}

template <typename T, typename Allocator>
void Deque_base<T, Allocator>::_create_nodes(T** _start, T** _finish)
{
    T** current = _start;
    try {
        for(; current < _finish; ++current)
            *current = _allocate_node();
    }
    catch(...) {
        _destroy_nodes(_start, _finish);
        throw;
    }
}

template <typename T, typename Allocator>
void Deque_base<T, Allocator>::_destroy_nodes(T** _start, T** _finish)
{
    for(; _start < _finish; ++_start)
        _deallocate_node(*_start);
}

template <typename T, typename Allocator = wt::allocator<T>>
class deque : protected Deque_base<T, Allocator> {
protected:
    typedef Deque_base<T, Allocator>   _Base;
    typedef T**                        Map_pointer;
    using _Base::_allocate_node;
    using _Base::_deallocate_node;
    using _Base::_allocate_map;
    using _Base::_deallocate_map;
    using _Base::_initialize_map;
    using _Base::_create_nodes;
    using _Base::_destroy_nodes;
    using _Base::m_map_;
    using _Base::m_map_size_;
    using _Base::m_start_;
    using _Base::m_finish_;
public:
    typedef typename _Base::allocator_type          allocator_type;
    typedef T                                       value_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef const value_type&                       const_reference;
    typedef value_type&                             reference;
    typedef const value_type*                       const_pointer;
    typedef value_type*                             pointer;
    typedef typename _Base::const_iterator          const_iterator;
    typedef typename _Base::iterator                iterator;
    typedef typename wt::reverse_iterator<const_iterator> 
            const_reverse_iterator;
    typedef typename wt::reverse_iterator<iterator> reverse_iterator;

    allocator_type get_allocator() const
    {
        return _Base::get_allocator();
    }

    deque() : deque(allocator_type()) {}
    explicit deque(const allocator_type& _a) : _Base(_a, 0) {}
    deque(size_type _count, const T& _value, 
          const allocator_type& _a = allocator_type()) : _Base(_a, _count)
    {
        _fill_initialize(_value);
    }
    explicit deque(size_type _count, const allocator_type& _a = allocator_type())
     : deque(_count, T(), _a) {}
    template <typename InputIterator>
    deque(InputIterator _first, InputIterator _last,
          const allocator_type& _a = allocator_type())
     : _Base(_a)
    {
        _initialize_dispatch(_first, _last, wt::is_integral<InputIterator>());
    }
    deque(const deque& other) : deque(other, other.get_allocator()) {}
    deque(const deque& other, const allocator_type& _a) : _Base(_a, other.size())
    {
        wt::uninitialized_copy(other.begin(), other.end(), m_start_);
    }
    deque(deque&& other) noexcept : _Base(other.get_allocator())
    {
        this->swap(other);
    }
    deque(deque&& other, const allocator_type& _a) noexcept : _Base(_a)
    {
        this->swap(other);
    }
    ~deque()
    {
        wt::destroy(m_start_, m_finish_);
    }
    deque& operator=(const deque& other)
    {
        if(this != &other)
        {
            const size_type len = other.size();
            if(size() > len)
            {
                erase(wt::copy(other.begin(), other.end(), m_start_), m_finish_);
            }
            else
            {
                iterator mid = 
                         other.begin() + static_cast<difference_type>(size());
                wt::copy(other.begin(), mid, m_start_);
                insert(m_finish_, mid, other.end());
            }
        }
        return *this;
    }
    deque& operator=(deque&& other) noexcept
    {
        this->swap(other);
        return *this;
    }

    void assign(size_type _count, const T& _value)
    {
        _fill_assign(_count, _value);
    }
    template <typename InputIterator>
    void assign(InputIterator _first, InputIterator _last)
    {
        _assign_dispatch(_first, _last, wt::is_integral<InputIterator>());
    }
    /**
     *  Element Access
     */
    reference at(size_type _pos)
    {
        _range_check(_pos);
        return (*this)[_pos];
    }
    const_reference at(size_type _pos) const
    {
        _range_check(_pos);
        return (*this)[_pos];
    }

    reference operator[](size_type _pos)
    {
        return (*this)[_pos];
    }
    const_reference operator[](size_type _pos) const
    {
        return (*this)[_pos];
    }

    reference front()
    {
        return *m_start_;
    }
    const_reference front() const
    {
        return *m_start_;
    }

    reference back()
    {
        iterator temp = m_finish_;
        --temp;
        return *temp;
    }
    const_reference back() const
    {
        const_iterator temp = m_finish_;
        --temp;
        return *temp;
    }
    /**
     *  Iterator Operations
     */
    iterator begin() noexcept
    {
        return m_start_;
    }
    const_iterator begin() const noexcept
    {
        return m_start_;
    }
    const_iterator cbegin() const noexcept
    {
        return m_start_;
    }
    iterator end() noexcept
    {
        return m_finish_;
    }
    const_iterator end() const noexcept
    {
        return m_finish_;
    }
    const_iterator cend() const noexcept
    {
        return m_finish_;
    }
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(cend());
    }
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(cbegin());
    }
    /**
     *  Capacity Operations
     */
    bool empty() const noexcept
    {
        return m_start_ == m_finish_;
    }

    size_type size() const noexcept
    {
        return m_finish_ - m_start_;
    }

    size_type max_size() const noexcept
    {
        return static_cast<size_type>(-1);
    }
    void shrink_to_fit()
    {
        // TODO
    }
    /**
     *  Modify Operations
     */
    void clear();
    void push_front(const T& _value);
    void push_back(const T& _value);
    void pop_front();
    void pop_back();

    iterator erase(const_iterator _pos)
    {
        iterator current(_pos.m_cur_, _pos.m_node_);
        const difference_type elem_before = current - m_start_;
        if(elem_before < m_finish_ - current)
        {
            wt::copy_backward(m_start_, current, current + 1);
            pop_front();
        }
        else
        {
            wt::copy(current + 1, m_finish_, current);
            pop_back();
        }
        return m_start_ + elem_before;
    }
    iterator erase(const_iterator _first, const_iterator _last);

    iterator insert(const_iterator _pos, const T& _value)
    {
        iterator pos(_pos.m_cur_, _pos.m_node_);
        if(pos.m_cur_ == m_start_.m_cur_)
        {
            push_front(_value);
            return m_start_;
        }
        else if(pos.m_cur_ == m_finish_.m_cur_)
        {
            push_back(_value);
            return m_finish_ - 1;
        }
        else
            return _insert_aux(pos, _value);
    }
    iterator insert(const_iterator _pos, size_type _count, const T& _value)
    {
        return _fill_insert(_pos, _count, _value);
    }
    template <typename InputIterator>
    iterator insert(const_iterator _pos, InputIterator _first,
                    InputIterator _last)
    {
        const difference_type elem_before = iterator(_pos.m_cur_, _pos.m_node_)
                                            - m_start_;
        _insert_dispatch(_pos, _first, _last, wt::is_integral<InputIterator>());
        return m_start_ + elem_before;
    }

    template <typename... Args>
    reference emplace_front(Args&&... args);
    template <typename... Args>
    reference emplace_back(Args&&... args);
    template <typename... Args>
    iterator emplace(const_iterator _pos, Args&&... args)
    {
        iterator pos(_pos.m_cur_, _pos.m_node_);
        if(pos.m_cur_ == m_start_.m_cur_)
        {
            emplace_front(wt::forward<Args>(args)...);
            return m_start_;
        }
        else if(pos.m_cur_ == m_finish_.m_cur_)
        {
            emplace_back(wt::forward<Args>(args)...);
            return m_finish_ - 1;
        }
        else
            return _emplace_aux(pos, wt::forward<Args>(args)...);
    }

    void resize(size_type _count)
    {
        resize(_count, T());
    }
    void resize(size_type _count, const T& _value)
    {
        const size_type len = size();
        if(len < _count)
            insert(m_finish_, _count - size(), _value);
        else
            erase(m_start_ + static_cast<difference_type>(_count), m_finish_);
    }

    void swap(deque& other) noexcept
    {
        wt::swap(m_start_, other.m_start_);
        wt::swap(m_finish_, other.m_finish_);
        wt::swap(m_map_, other.m_map_);
        wt::swap(m_map_size_, other.m_map_size_);
    }
protected:
    void _range_check(size_type _n) const
    {
        if(_n >= size())
            throw std::out_of_range("deque");
    }
    void _fill_initialize(const T& _value);
    template <typename Integer>
    void _initialize_dispatch(Integer _count, Integer _value, wt::true_type)
    {
        _initialize_map(static_cast<size_type>(_count));
        _fill_initialize(static_cast<T>(_value));
    }
    template <typename InputIterator>
    void _initialize_dispatch(InputIterator _first, InputIterator _last,
                              wt::false_type)
    {
        _range_initialize(_first, _last, _ITERATOR_CATEGORY(_first));
    }
    template <typename InputIterator>
    void _range_initialize(InputIterator _first, InputIterator _last,
                           wt::input_iterator_tag);
    template <typename ForwardIterator>
    void _range_initialize(ForwardIterator _first, ForwardIterator _last,
                           wt::forward_iterator_tag);

    void _reverse_map_front(size_type _node_count = 1)
    {
        if(_node_count > static_cast<size_type>(m_start_.m_node_ - m_map_))
            _reallocate_map(_node_count, true);
    }
    void _reverse_map_back(size_type _node_count = 1)
    {
        if(_node_count + 1 > m_map_size_ - (m_finish_.m_node_ - m_map_))
            _reallocate_map(_node_count, false);
    }
    void _reallocate_map(size_type _node_count, bool _at_front);

    iterator _reverse_elem_front(size_type _count)
    {
        const size_type vacant = 
            static_cast<size_type>(m_start_.m_cur_ - m_start_.m_first_);
        if(_count > vacant)
            _new_nodes_elem_front(_count - vacant);
        return m_start_ - static_cast<difference_type>(_count);
    }
    iterator _reverse_elem_back(size_type _count)
    {
        const size_type vacant = 
            static_cast<size_type>(m_finish_.m_last_ - m_finish_.m_cur_ - 1);
        if(_count > vacant)
            _new_nodes_elem_back(_count - vacant);
        return m_finish_ + static_cast<difference_type>(_count);
    }
    void _new_nodes_elem_front(size_type _count);
    void _new_nodes_elem_back(size_type _count);

    //  assign
    template <typename Integer>
    void _assign_dispatch(Integer _count, Integer _value, wt::true_type)
    {
        _fill_assign(static_cast<size_type>(_count), static_cast<T>(_value));
    }
    template <typename InputIterator>
    void _assign_dispatch(InputIterator _first, InputIterator _last,
                          wt::false_type)
    {
        _assign(_first, _last, _ITERATOR_CATEGORY(_first));
    }
    void _fill_assign(size_type _count, const T& _value);
    template <typename InputIterator>
    void _assign(InputIterator _first, InputIterator _last,
                 wt::input_iterator_tag);
    template <typename ForwardIterator>
    void _assign(ForwardIterator _first, ForwardIterator _last,
                 wt::forward_iterator_tag);

    // insert
    iterator _insert_aux(iterator _pos, const T& _value);
    iterator _insert_aux(iterator _pos, size_type _count, const T& _value);
    template <typename ForwardIterator>
    void     _insert_aux(iterator _pos, ForwardIterator _first,
                         ForwardIterator _last, difference_type _count);
    iterator _fill_insert(const_iterator _pos, size_type _count, const T& _value);
    template <typename Integer>
    void _insert_dispatch(const_iterator _pos, Integer _count, Integer _value,
                          wt::true_type)
    {
        _fill_insert(_pos, static_cast<size_type>(_count), 
                     static_cast<T>(_value));
    }
    template <typename InputIterator>
    void _insert_dispatch(const_iterator _pos, InputIterator _first, 
                          InputIterator _last, wt::false_type)
    {
        _insert(_pos, _first, _last, _ITERATOR_CATEGORY(_first));
    }
    template <typename InputIterator>
    void _insert(const_iterator _pos, InputIterator _first,
                 InputIterator _last, wt::input_iterator_tag)
    {
        iterator pos(_pos.m_cur_, _pos.m_node_);
        for(;_first != _last; ++_first)
            pos = insert(pos, *_first);
    }
    template <typename ForwardIterator>
    void _insert(const_iterator _pos, ForwardIterator _first,
                 ForwardIterator _last, wt::forward_iterator_tag);

    // emplace
    template <typename... Args>
    iterator _emplace_aux(iterator _pos, Args&&... args);
}; // end class deque

template <typename T, typename Allocator>
void deque<T, Allocator>::_fill_initialize(const T& _value)
{
    Map_pointer current = m_start_.m_node_;
    try {
        for(; current < m_finish_.m_node_; ++current)
            wt::uninitialized_fill(*current, *current + deque_node_size(), _value);
        wt::uninitialized_fill(m_finish_.m_first_, m_finish_.m_cur_, _value);
    }
    catch(...) {
        wt::destroy(m_start_, iterator(*current, current));
        throw;
    }
}

template <typename T, typename Allocator>
template <typename InputIterator>
void deque<T, Allocator>::_range_initialize(InputIterator _first,
                                            InputIterator _last,
                                            wt::input_iterator_tag)
{
    _initialize_map(0);
    try {
        for(; _first != _last; ++_first)
            push_back(*_first);
    }
    catch(...) {
        clear();
        throw;
    }
}

template <typename T, typename Allocator>
template <typename ForwardIterator>
void deque<T,Allocator>::_range_initialize(ForwardIterator _first,
                                           ForwardIterator _last,
                                           wt::forward_iterator_tag)
{
    size_type count = static_cast<size_type>(wt::distance(_first, _last));
    _initialize_map(count);

    // exception unsafe
    // wt::uninitialized_copy(_first, _last, m_start_);

    // exception safe
    Map_pointer current = m_start_.m_node_;
    try {
        for(; current < m_finish_.m_node_; ++current)
        {
            ForwardIterator mid = _first;
            wt::advance(mid, deque_node_size());
            wt::uninitialized_copy(_first, mid, *current);
            _first = mid;
        }
        wt::uninitialized_copy(_first, _last, m_finish_.m_first_);
    }
    catch(...) {
        wt::destroy(m_start_, iterator(*current, current));
        throw;
    }
}

template <typename T, typename Allocator>
void deque<T, Allocator>::_reallocate_map(size_type _node_count, bool _at_front)
{
    size_type old_count = m_finish_.m_node_ - m_start_.m_node_ + 1;
    size_type new_count = old_count + _node_count;
    Map_pointer new_start;
    if(m_map_size_ > 2 * new_count)
    {
        new_start = m_map_ + (m_map_size_ - new_count) / 2
                    + (_at_front ? _node_count : 0);
        if(new_start < m_start_.m_node_)
            wt::copy(m_start_.m_node_, m_finish_.m_node_ + 1, new_start);
        else
            wt::copy_backward(m_start_.m_node_, m_finish_.m_node_ + 1,
                              new_start + old_count);
    }
    else
    {
        size_type new_map_size = m_map_size_ + 
                                 wt::max(m_map_size_, _node_count) + 2;
        Map_pointer new_map = _allocate_map(new_map_size);
        new_start = new_map + (new_map_size - new_count) / 2
                    + (_at_front ? _node_count : 0);
        wt::copy(m_start_.m_node_, m_finish_.m_node_ + 1, new_start);
        _deallocate_map(m_map_, m_map_size_);
        m_map_ = new_map;
        m_map_size_ = new_map_size;
    }
    m_start_.set_node(new_start);
    m_finish_.set_node(new_start + old_count - 1);
}

template <typename T, typename Allocator>
void deque<T, Allocator>::_new_nodes_elem_front(size_type _count)
{
    const size_type node_count = 
                    (_count + deque_node_size() - 1) / deque_node_size();
    _reverse_map_front(node_count);
    size_type offset;
    try {
        for(offset = 1; offset <= node_count; ++offset)
            *(m_start_.m_node_ - offset) = _allocate_node();
    }
    catch(...) {
        for(size_type i = 1; i < offset; ++i)
            _deallocate_node(*(m_start_.m_node_ - i));
        throw;
    }
}

template <typename T, typename Allocator>
void deque<T,Allocator>::_new_nodes_elem_back(size_type _count)
{
    const size_type node_count = 
                    (_count + deque_node_size() - 1) / deque_node_size();
    _reverse_map_back(node_count);
    size_type offset;
    try {
        for(offset = 1; offset <= node_count; ++offset)                
            *(m_finish_.m_node_ + offset) = _allocate_node();
    }
    catch(...) {
        for(size_type i = 1; i < offset; ++i)
            _deallocate_node(*(m_finish_.m_node_ + i));
        throw;
    }
}

template <typename T, typename Allocator>
void deque<T, Allocator>::_fill_assign(size_type _count, const T& _value)
{
    if(size() > _count)
    {
        erase(wt::fill_n(m_start_, _count, _value), m_finish_);
    }
    else
    {
        wt::fill_n(m_start_, size(), _value);
        insert(m_finish_, _count - size(), _value);
    }
}

template <typename T, typename Allocator>
template <typename InputIterator>
void deque<T, Allocator>::_assign(InputIterator _first, InputIterator _last,
                                  wt::input_iterator_tag)
{
    iterator current = m_start_;
    while(current != m_finish_ && _first != _last)
    {
        *current = *_first;
        ++current;
        ++_first;
    }
    if(_first != _last)
        insert(m_finish_, _first, _last);
    else
        erase(current, m_finish_);
}

template <typename T, typename Allocator>
template <typename ForwardIterator>
void deque<T, Allocator>::_assign(ForwardIterator _first, ForwardIterator _last,
                                  wt::forward_iterator_tag)
{
    const auto len = static_cast<size_type>(wt::distance(_first, _last));
    if(size() > len)
    {
        erase(wt::copy(_first, _last, m_start_), m_finish_);
    }
    else
    {
        ForwardIterator mid = _first;
        wt::advance(mid, size());
        wt::copy(_first, mid, m_start_);
        insert(m_finish_, mid, _last);
    }
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator
deque<T, Allocator>::_insert_aux(iterator _pos, const T& _value)
{
    const difference_type elem_before = _pos - m_start_;
    if(elem_before < static_cast<difference_type>(size() / 2))
    {
        push_front(front());
        iterator front1 = m_start_;
        ++front1;
        iterator front2 = front1;
        ++front2;
        _pos = m_start_ + elem_before;
        iterator new_pos = _pos;
        ++_pos;
        wt::copy(front2, new_pos, front1);
    }
    else
    {
        push_back(back());
        iterator back1 = m_finish_;
        --back1;
        iterator back2 = back1;
        --back2;
        _pos = m_start_ + elem_before;
        wt::copy_backward(_pos, back2, back1);
    }
    *_pos = _value;
    return _pos;
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator
deque<T, Allocator>::_insert_aux(iterator _pos, size_type _count,
                                 const T& _value)
{
    const difference_type elem_before = _pos - m_start_;
    if(elem_before < static_cast<difference_type>(size() / 2))
    {
        iterator new_start = _reverse_elem_front(_count);
        _pos = m_start_ + elem_before;
        try {
            if(elem_before > static_cast<difference_type>(_count))
            {
                iterator mid = m_start_ + _count;
                wt::uninitialized_copy(m_start_, mid, new_start);
                wt::copy(mid, _pos, m_start_);
                wt::fill_n(_pos - static_cast<difference_type>(_count),
                           _count, _value);
            }
            else
            {
                iterator mid = new_start + elem_before;
                wt::uninitialized_copy(m_start_, _pos, new_start);
                wt::uninitialized_fill(mid, m_start_, _value);
                wt::fill_n(m_start_, static_cast<size_type>(elem_before),
                           _value);
            }
        }
        catch(...) {
            _destroy_nodes(new_start.m_node_, m_start_.m_node_);
            throw;
        }
        m_start_ = new_start;
    }
    else
    {
        const difference_type elem_after = m_finish_ - _pos;
        iterator new_finish = _reverse_elem_back(_count);
        _pos = m_start_ + elem_before;
        try {
            if(elem_after > static_cast<difference_type>(_count))
            {
                iterator mid = m_finish_ - _count;
                wt::uninitialized_copy(mid, m_finish_, m_finish_);
                wt::copy_backward(_pos, mid, m_finish_);
                wt::fill_n(_pos, _count, _value);
            }
            else
            {
                iterator mid = new_finish - elem_after;
                wt::uninitialized_copy(_pos, m_finish_, mid);
                wt::uninitialized_fill(m_finish_, mid, _value);
                wt::fill_n(_pos, static_cast<size_type>(elem_after), _value);
            }
        }
        catch(...) {
            _destroy_nodes(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
        m_finish_ = new_finish;
    }
    return _pos;
}

template <typename T, typename Allocator>
template <typename ForwardIterator>
void deque<T, Allocator>::_insert_aux(iterator _pos, ForwardIterator _first,
                              ForwardIterator _last, difference_type _count)
{
    const difference_type elem_before = _pos - m_start_;
    if(elem_before < static_cast<difference_type>(size() / 2))
    {
        iterator new_start = 
                    _reverse_elem_front(static_cast<size_type>(_count));
        _pos = m_start_ + elem_before;
        try {
            if(elem_before > _count)
            {
                iterator mid = m_start_ + _count;
                wt::uninitialized_copy(m_start_, mid, new_start);
                mid = wt::copy(mid, _pos, m_start_);
                wt::copy(_first, _last, mid);
            }
            else
            {
                ForwardIterator mid1 = _first;
                wt::advance(mid1, _count - elem_before);
                auto mid2 = wt::uninitialized_copy(m_start_, _pos, new_start);
                mid2 = wt::uninitialized_copy(_first, mid1, mid2);
                wt::copy(mid1, _last, mid2);
            }
        }
        catch(...) {
            _destroy_nodes(new_start.m_node_, m_start_.m_node_);
            throw;
        }
        m_start_ = new_start;
    }
    else
    {
        iterator new_finish = 
                    _reverse_elem_back(static_cast<size_type>(_count));
        iterator _pos = m_start_ + elem_before;
        const difference_type elem_after = m_finish_ - _pos;
        try {
            if(elem_after > _count)
            {
                iterator mid = m_finish_ - _count;
                wt::uninitialized_copy(mid, m_finish_, m_finish_);
                wt::copy_backward(_pos, mid, m_finish_);
                wt::copy(_first, _last, _pos);
            }
            else
            {
                ForwardIterator mid1 = _first;
                wt::advance(mid1, elem_after);
                iterator mid2 = new_finish - elem_after;
                wt::uninitialized_copy(_pos, m_finish_, mid2);
                wt::uninitialized_copy(mid1, _last, m_finish_);
                wt::copy(_first, mid1, _pos);
            }
        }
        catch(...) {
            _destroy_nodes(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
        m_finish_ = new_finish;
    }
}                                      

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator
deque<T, Allocator>::_fill_insert(const_iterator _pos, size_type _count, 
                                  const T& _value)
{
    iterator pos(_pos.m_cur_, _pos.m_node_);
    if(pos.m_cur_ == m_start_.m_cur_)
    {
        iterator new_start = _reverse_elem_front(_count);
        try {
            wt::uninitialized_fill(new_start, m_start_, _value);
        }
        catch(...) {
            _destroy_nodes(new_start.m_node_, m_start_.m_node_);
            throw;
        }
        m_start_ = new_start;
        return m_start_;
    }
    else if(pos.m_cur_ == m_finish_.m_cur_)
    {
        const difference_type elem_before = static_cast<difference_type>(size());
        iterator new_finish = _reverse_elem_back(_count);
        try {
            wt::uninitialized_fill(m_finish_, new_finish, _value);
        }
        catch(...) {
            _destroy_nodes(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
        m_finish_ = new_finish;
        return m_start_ + elem_before;
    }
    else
    {
        return _insert_aux(pos, _count, _value);
    }
}

template <typename T, typename Allocator>
template <typename ForwardIterator>
void deque<T, Allocator>::_insert(const_iterator _pos, ForwardIterator _first,
                              ForwardIterator _last, wt::forward_iterator_tag)
{
    iterator pos(_pos.m_cur_, _pos.m_node_);
    const auto count = static_cast<size_type>(wt::distance(_first, _last));
    if(pos.m_cur_ == m_start_.m_cur_)
    {
        iterator new_start = _reverse_elem_front(count);
        try {
            wt::uninitialized_copy(_first, _last, new_start);
        }
        catch(...) {
            _destroy_nodes(new_start.m_node_, m_start_.m_node_);
            throw;
        }
        m_start_ = new_start;
    }
    else if(pos.m_cur_ == m_finish_.m_cur_)
    {
        iterator new_finish = _reverse_elem_back(count);
        try {
            wt::uninitialized_copy(_first, _last, m_finish_);
        }
        catch(...) {
            _destroy_nodes(m_finish_.m_node_ + 1, new_finish.m_node_ + 1);
            throw;
        }
        m_finish_ = new_finish;
    }
    else
    {
        _insert_aux(pos, _first, _last, static_cast<difference_type>(count));
    }
}

template <typename T, typename Allocator>
template <typename... Args>
typename deque<T, Allocator>::iterator
deque<T, Allocator>::_emplace_aux(iterator _pos, Args&&... args)
{
    const difference_type elem_before = _pos - m_start_;
    if(elem_before < static_cast<difference_type>(size() / 2))
    {
        push_front(front());
        iterator fron1 = m_start_;
        ++fron1;
        iterator front2 = fron1;
        ++front2;
        _pos = m_start_ + elem_before;
        iterator new_pos = _pos;
        ++new_pos;
        wt::copy(front2, new_pos, fron1);
    }
    else
    {
        push_back(back());
        iterator back1 = m_finish_;
        --back1;
        iterator back2 = back1;
        --back2;
        _pos = m_start_ + elem_before;
        wt::copy_backward(_pos, back2, back1);
    }
    wt::destroy(_pos.m_cur_);
    ::new (static_cast<void*>(_pos.m_cur_)) T(wt::forward<Args>(args)...);
    return _pos;
}

///////////////
// Interface //
///////////////
template <typename T, typename Allocator>
void deque<T, Allocator>::clear()
{
    for(Map_pointer current = m_start_.m_node_ + 1;
        current < m_finish_.m_node_; ++current)
    {
        wt::destroy(*current, *current + deque_node_size());
        _deallocate_node(*current);
    }
    if(m_start_.m_node_ != m_finish_.m_node_)
    {
        wt::destroy(m_start_.m_cur_, m_start_.m_last_);
        wt::destroy(m_finish_.m_first_, m_finish_.m_cur_);
        _deallocate_node(m_finish_.m_first_);
    }
    else
    {
        wt::destroy(m_start_.m_cur_, m_finish_.m_cur_);
    }
    m_finish_ = m_start_;
}

template <typename T, typename Allocator>
void deque<T, Allocator>::push_front(const T& _value)
{
    if(m_start_.m_first_ != m_start_.m_cur_)
    {
        wt::construct(m_start_.m_cur_ - 1, _value);
        --m_start_.m_cur_;
    }
    else
    {
        _reverse_map_front();
        *(m_start_.m_node_ - 1) = _allocate_node();
        try {
            m_start_.set_node(m_start_.m_node_ - 1);
            m_start_.m_cur_ = m_start_.m_last_ - 1;
            wt::construct(m_start_.m_cur_, _value);
        }
        catch(...) {
            ++m_start_;
            _deallocate_node(*(m_start_.m_node_ - 1));
            throw;
        }
    }
}

template <typename T, typename Allocator>
void deque<T, Allocator>::push_back(const T& _value)
{
    if(m_finish_.m_cur_ != m_finish_.m_last_ - 1)
    {
        wt::construct(m_finish_.m_cur_, _value);
        ++m_finish_.m_cur_;
    }
    else
    {
        _reverse_map_back();
        *(m_finish_.m_node_ + 1) = _allocate_node();
        try {
            wt::construct(m_finish_.m_cur_, _value);
        }
        catch(...) {
            _deallocate_node(*(m_finish_.m_node_ + 1));
            throw;
        }
        m_finish_.set_node(m_finish_.m_node_ + 1);
        m_finish_.m_cur_ = m_finish_.m_first_;
    }
}

template <typename T, typename Allocator>
void deque<T, Allocator>::pop_front()
{
    wt::destroy(m_start_.m_cur_);
    if(m_start_.m_cur_ != m_start_.m_last_ - 1)
    {
        ++m_start_.m_cur_;
    }
    else
    {
        _deallocate_node(m_start_.m_first_);
        m_start_.set_node(m_start_.m_node_ + 1);
        m_start_.m_cur_ = m_start_.m_first_;
    }
}

template <typename T, typename Allocator>
void deque<T, Allocator>::pop_back()
{
    if(m_finish_.m_cur_ != m_finish_.m_first_)
    {
        --m_finish_.m_cur_;
        wt::destroy(m_finish_.m_cur_);
    }
    else
    {
        _deallocate_node(m_finish_.m_first_);
        m_finish_.set_node(m_finish_.m_node_ - 1);
        m_finish_.m_cur_ = m_finish_.m_last_ - 1;
        wt::destroy(m_finish_.m_cur_);
    }
}

template <typename T, typename Allocator>
typename deque<T, Allocator>::iterator
deque<T, Allocator>::erase(const_iterator _first, const_iterator _last)
{
    iterator first(_first.m_cur_, _first.m_node_);
    iterator last(_last.m_cur_, _last.m_node_);
    if(first == m_start_ && last == m_finish_)
    {
        clear();
        return m_finish_;
    }
    else
    {
        const difference_type n = _last - first;
        const difference_type elem_before = first - m_start_;
        if(elem_before < (static_cast<difference_type>(size() - n)) / 2)
        {
            wt::copy_backward(m_start_, first, last);
            iterator new_start = m_start_ + n;
            wt::destroy(m_start_, new_start);
            _destroy_nodes(m_start_.m_node_, new_start.m_node_);
            m_start_ = new_start;
        }   
        else
        {
            wt::copy(last, m_finish_, first);
            iterator new_finish = m_finish_ - n;
            wt::destroy(new_finish, m_finish_);
            _destroy_nodes(new_finish.m_node_ + 1, m_finish_.m_node_ + 1);
            m_finish_ = new_finish;
        }
        return m_start_ + elem_before;
    }
}

template <typename T, typename Allocator>
template <typename... Args>
typename deque<T, Allocator>::reference
deque<T, Allocator>::emplace_front(Args&&... args)
{
    if(m_start_.m_cur_ != m_start_.m_first_)
    {
        ::new (static_cast<void*>(m_start_.m_cur_ - 1)) 
                                            T(wt::forward<Args>(args)...);
        --m_start_.m_cur_;
    }
    else
    {
        _reverse_map_front();
        *(m_start_.m_node_ - 1) = _allocate_node();
        try {
            m_start_.set_node(m_start_.m_node_ - 1);
            m_start_.m_cur_ = m_start_.m_last_ - 1;
            ::new (static_cast<void*>(m_start_.m_cur_)) 
                                            T(wt::forward<Args>(args)...);
        }
        catch(...) {
            ++m_start_;
            _deallocate_node(*(m_start_.m_node_ -1));
            throw;
        }
    }
    return *m_start_;
}

template <typename T, typename Allocator>
template <typename... Args>
typename deque<T, Allocator>::reference
deque<T, Allocator>::emplace_back(Args&&... args)
{
    iterator old_finish;
    if(m_finish_.m_cur_ != m_finish_.m_last_ - 1)
    {
        ::new (static_cast<void*>(m_finish_.m_cur_)) 
                                            T(wt::forward<Args>(args)...);
        old_finish = m_finish_;
        ++m_finish_.m_cur_;
    }
    else
    {
        _reverse_map_back();
        *(m_finish_.m_node_ + 1) = _allocate_node();
        try {
            ::new (static_cast<void*>(m_finish_.m_cur_))
                                            T(wt::forward<Args>(args)...);
        }
        catch(...) {
            _deallocate_node(*(m_finish_.m_node_ + 1));
            throw;
        }
        old_finish = m_finish_;
        m_finish_.set_node(m_finish_.m_node_ + 1);
        m_finish_.m_cur_ = m_finish_.m_first_;
    }
    return *old_finish;
}

//////////////////////////
// Non-member functions //
//////////////////////////
template <typename T, typename Allocator>
inline bool operator==(const deque<T, Allocator>& lhs,
                       const deque<T, Allocator>& rhs)
{
    return lhs.size() == rhs.size() &&
            wt::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
    //  equivalent form
    // return wt::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

template <typename T, typename Allocator>
inline bool operator!=(const deque<T, Allocator>& lhs,
                       const deque<T, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Allocator>
inline bool operator<(const deque<T, Allocator>& lhs,
                      const deque<T, Allocator>& rhs)
{
    return wt::lexicographical_compare(lhs.cbegin(), lhs.cend(),
                                       rhs.cbegin(), rhs.cend());
}

template <typename T, typename Allocator>
inline bool operator<=(const deque<T, Allocator>& lhs,
                       const deque<T, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Allocator>
inline bool operator>(const deque<T, Allocator>& lhs,
                      const deque<T, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Allocator>
inline bool operator>=(const deque<T, Allocator>& lhs,
                       const deque<T, Allocator>& rhs)
{
    return !(lhs < rhs);
}






template <typename T, typename Allocator>
void swap(deque<T, Allocator>& lhs, deque<T,Allocator>& rhs)
{
    lhs.swap(rhs);
}


} // namespace wt



#endif