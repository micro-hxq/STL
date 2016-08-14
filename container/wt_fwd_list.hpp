#ifndef _STL_WT_FWD_LIST_HPP_
#define _STL_WT_FWD_LIST_HPP_

namespace wt{

template <typename T>
struct Fwd_list_node {
    Fwd_list_node*  next_;
    T               data_;
};

template <typename T>
inline Fwd_list_node<T>*
fwd_list_insert_node(Fwd_list_node<T>* prev_node,
                     Fwd_list_node<T>* new_node)
{
    new_node->next_ = prev_node->next_;
    prev_node->next_ = new_node;
    return new_node;
}

template <typename T>
inline Fwd_list_node<T>*
fwd_list_previous(Fwd_list_node<T>* head, const Fwd_list_node<T>* node)
{
    while(head && head->next_ != node)
        head = head->next_;
    return head;
}

template <typename T>
inline const Fwd_list_node<T>*
fwd_list_previous(const Fwd_list_node<T>* head, 
                  const Fwd_list_node<T>* node)
{
    while(head && head->next_ != node)
        head = head->next_;
    return head;
}

template <typename T>
void fwd_list_splice_after(Fwd_list_node<T>* pos,
                           Fwd_list_node<T>* before_first,
                           Fwd_list_node<T>* before_last)
{
    if(pos != before_first && pos != before_last)
    {
        Fwd_list_node<T>* first = before_first->next_;
        Fwd_list_node<T>* last  = before_last->next_;
        before_first->next_ = last;
        before_last->next_  = pos->next_;
        pos->next_ = first;
    }
}

template <typename T>
inline void fwd_list_splice_after(Fwd_list_node<T>* pos,
                                  Fwd_list_node<T>* head)
{
    Fwd_list_node<T>* before_last = fwd_list_previous(head, nullptr);
    if(before_last != head)
    {
        before_last->next_ = pos->next_;
        pos->next_ = head->next_;
        head->next_ = nullptr;
    }
}

template <typename T>
Fwd_list_node<T>* fwd_list_reverse(Fwd_list_node<T>* node)
{
    Fwd_list_node<T>* start = node;
    node = node->next_;
    start->next_ = nullptr;
    while(node)
    {
        Fwd_list_node<T>* temp = node->next_;
        node->next_ = start;
        start = node;
        node = temp;
    }
    return start;
}

template <typename T>
inline size_t fwd_list_size(Fwd_list_node<T>* node)
{
    size_t count = 0;
    while(node)
    {
        ++count;
        node = node->next_;
    }
    return count;
}

template <typename T>
class Fwd_list_const_iterator
 : public wt::iterator<wt::forward_iterator_tag, T> {
public:
    typedef wt::forward_iterator_tag    iterator_category;
    typedef T                           value_type;
    typedef std::ptrdiff_t              difference_type;
    typedef const value_type*           pointer;
    typedef const value_type&           reference;
    typedef Fwd_list_node<T>            _Node;
    typedef Fwd_list_const_iterator<T>  _Self;

    Fwd_list_const_iterator() : node_(nullptr) {}
    explicit Fwd_list_const_iterator(_Node* _n) noexcept : node_(_n) {}
    Fwd_list_const_iterator(const Fwd_list_const_iterator& other) noexcept
     : node_(other.node_) {}

    reference operator*() const noexcept
    {
        return node_->data_;
    }

    pointer operator->() const noexcept
    {
        return &(operator*());
    }

    _Self& operator++() noexcept
    {
        node_ = node_->next_;
        return *this;
    }

    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        node_ = node_->next_;
        return temp;
    }

    bool operator==(const _Self& other) const noexcept
    {
        return this->node_ == other.node_;
    }

    bool operator!=(const _Self& other) const noexcept
    {
        return this->node_ != other.node_;
    }

    _Node*   node_;
};

template <typename T>
class Fwd_list_iterator : public Fwd_list_const_iterator<T> {
public:
    typedef wt::forward_iterator_tag    iterator_category;
    typedef T                           value_type;
    typedef std::ptrdiff_t              difference_type;
    typedef value_type*                 pointer;    
    typedef value_type&                 reference;
    typedef Fwd_list_node<T>            _Node;
    typedef Fwd_list_const_iterator<T>  _Base;
    typedef Fwd_list_iterator<T>        _Self;

    using _Base::node_;

    Fwd_list_iterator() : _Base() {}
    explicit Fwd_list_iterator(_Node* _n) : _Base(_n) {}
    Fwd_list_iterator(const _Self& other) : _Base(other.node_) {}

    reference operator*() const noexcept
    {
        return node_->data_;
    }

    pointer operator->() const noexcept
    {
        return &(operator*());
    }

    _Self& operator++() noexcept
    {
        node_ = node_->next_;
        return *this;
    }

    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        node_ = node_->next_;
        return temp;
    }

    bool operator==(const _Self& other) const noexcept
    {
        return this->node_ == other.node_;
    }

    bool operator!=(const _Self& other) const noexcept
    {
        return this->node_ != other.node_;
    }
};

template <typename T, typename Allocator, bool _IsStatic>
class Fwd_list_alloc_base {
public:
    typedef typename wt::allocator_traits<Allocator>::allocator_type
            allocator_type;

    allocator_type get_allocator() const 
    {
        return m_allocator_;
    }

    Fwd_list_alloc_base(const allocator_type& _alloc)
     : m_allocator_(_alloc), m_head_(nullptr) {}

protected:
    Fwd_list_node<T>* _get_node()
    {
        return m_allocator_.allocate(1);
    }

    void _put_node(Fwd_list_node<T>* _p)
    {
        m_allocator_.deallocate(_p, 1);
    }
protected:
    typename wt::_Alloc_traits<Fwd_list_node<T>, Allocator>::allocator_type
                        m_allocator_;
    Fwd_list_node<T>    m_head_;
};

template <typename T, typename Allocator>
class Fwd_list_alloc_base<T, Allocator, true> {
public:
    typedef typename wt::allocator_traits<Allocator>::allocator_type
            allocator_type;

    allocator_type get_allocator() const
    {
        return allocator_type();
    }

    Fwd_list_alloc_base(const allocator_type& _alloc) {}

protected:
    typedef typename _Alloc_traits<Fwd_list_node<T>, Allocator>::_Alloc_type
            _Alloc_type;
    Fwd_list_node<T>* _get_node()
    {
        return _Alloc_type::allocate(1);
    }

    void _put_node(Fwd_list_node<T>* _p)
    {
        _Alloc_type::deallocate(_p, 1);
    }
protected:
    Fwd_list_node<T>    m_head_;
};

template <typename T, typename Allocator>
class Fwd_list_base : public Fwd_list_alloc_base<T, Allocator, 
                    wt::_Alloc_traits<T, Allocator>::isStatic> {
public:
    typedef Fwd_list_alloc_base<T, Allocator, 
        wt::_Alloc_traits<T, Allocator>::isStatic>  _Base;
    typedef Fwd_list_node<T>                        _Node;
    typedef typename _Base::allocator_type          allocator_type;

    using _Base::m_head_;
    using _Base::_get_node;
    using _Base::_put_node;

    Fwd_list_base(const allocator_type& _alloc) : _Base(_alloc)
    {
        m_head_.next_ = nullptr;
    }

    ~Fwd_list_base()
    {
        _erase_after(&m_head_, nullptr);
    }

protected:
    _Node* _erase_after(_Node* _pos)
    {
        _Node* temp = _pos->next_;
        _pos->next_ = temp->next_;
        wt::destroy(&(temp->data_));
        _put_node(temp);
        return _pos->next_;
    }

    _Node* _erase_after(_Node* _before_first, _Node* _last);
};

template <typename T, typename Allocator>
typename Fwd_list_base<T, Allocator>::_Node*
Fwd_list_base<T, Allocator>::_erase_after(_Node* _before_first, _Node* _last)
{
    _Node* current = _before_first->next_;
    while(current != _last)
    {
        _Node* temp = current;
        current = current->next_;
        wt::destroy(&(temp->data_));
        _put_node(temp);
    }
    _before_first->next_ = _last;
    return _last;
}

template <typename T, typename Allocator = wt::allocator<T>>
class forward_list : public Fwd_list_base<T, Allocator> {
private:
    typedef Fwd_list_base<T, Allocator>         _Base;
    typedef Fwd_list_node<T>                    _Node;

    using _Base::m_head_;
    using _Base::_get_node;
    using _Base::_put_node;
    using _Base::_erase_after;
public:
    typedef typename _Base::allocator_type  allocator_type;
    typedef T                               value_type;
    typedef std::size_t                     size_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef value_type&                     reference;
    typedef const value_type&               const_reference;
    typedef value_type*                     pointer;
    typedef const value_type*               const_pointer;
    typedef Fwd_list_iterator<T>            iterator;
    typedef Fwd_list_const_iterator<T>      const_iterator;

    allocator_type get_allocator() const
    {
        return _Base::get_allocator();
    }

    forward_list() : forward_list(allocator_type()) {}
    explicit forward_list(const allocator_type& _alloc) : _Base(_alloc) {}
    forward_list(size_type _count, const T& _value,
                 const allocator_type& _alloc = allocator_type())
     : _Base(_alloc)
    {
        _fill_insert_after(&m_head_, _count, _value);
    }
    explicit forward_list(size_type _count, 
                          const allocator_type& _alloc = allocator_type())
     : _Base(_alloc)
    {
        _fill_insert_after(&m_head_, _count, value_type());
    }
    template <typename InputIterator>
    forward_list(InputIterator _first, InputIterator _last,
                 const allocator_type& _alloc = allocator_type())
     : _Base(_alloc)
    {
        _range_insert_after(&m_head_, _first, _last);
    }
    forward_list(const forward_list& other)
     : _Base(other.get_allocator())
    {
        _range_insert_after(&m_head_, other.begin(), other.end());
    }
    forward_list(const forward_list& other, const allocator_type& _alloc)
     : _Base(_alloc)
    {
        _range_insert_after(&m_head_, other.begin(), other.end());
    }
    forward_list(forward_list&& other) : _Base(other.get_allocator())
    {
        this->swap(other);
    }
    forward_list(forward_list&& other, const allocator_type& _alloc)
     : _Base(_alloc)
    {
        this->swap(other);
    }
    forward_list(std::initializer_list<T> _il,
                 const allocator_type& _alloc = allocator_type())
     : _Base(_alloc) 
    {
        _range_insert_after(&m_head_, _il.begin(), _il.end());
    }

    forward_list& operator=(const forward_list& other);
    forward_list& operator=(forward_list&& other)
    {
        if(this != &other)
            this->swap(other);
        return *this;
    }
    forward_list& operator=(std::initializer_list<T> _il);

    void assign(size_type _count, const T& _value)
    {
        _fill_assign(_count, _value);
    }
    template <typename InputIterator>
    void assign(InputIterator _first, InputIterator _last)
    {
        _assign_dispatch(_first, _last, wt::is_integral<InputIterator>());
    }
    void assign(std::initializer_list<T> _il)
    {
        assign(_il.begin(), _il.end());
    }

    /**
     *  Element Access
     */
    reference front()
    {
        return *begin();
    }
    const_reference front() const
    {
        return *begin();
    }

    /**
     *  Iterator
     */
    iterator before_begin() noexcept
    {
        return iterator(&m_head_);
    }
    const_iterator before_begin() const noexcept
    {
        return const_iterator(const_cast<_Node*>(&m_head_));
    }
    const_iterator cbefore_begin() const noexcept
    {
        return const_iterator(const_cast<_Node*>(&m_head_));
    }
    
    iterator begin() noexcept
    {
        return iterator(m_head_.next_);
    }
    const_iterator begin() const noexcept
    {
        return const_iterator(m_head_.next_);
    }
    const_iterator cbegin() const noexcept
    {
        return const_iterator(m_head_.next_);
    }

    iterator end() noexcept
    {
        return iterator(nullptr);
    }
    const_iterator end() const noexcept
    {
        return const_iterator(nullptr);
    }
    const_iterator cend() const noexcept
    {
        return const_iterator(nullptr);
    }

    /**
     *  Capacity Operations
     */
    bool empty() const noexcept
    {
        return m_head_.next_ == nullptr;
    }
    size_type size() const 
    {
        return fwd_list_size(m_head_.next_);
    }
    size_type max_size() const noexcept
    {
        return static_cast<size_type>(-1);
    }

    /**
     *  Modify Operations
     */
    void clear()
    {
        if(!empty())
            _erase_after(&m_head_, nullptr);
    }

    iterator insert_after(const_iterator _pos, const T& _value)
    {
        return iterator(fwd_list_insert_node(_pos.node_,
                                             _create_node(_value)));
    }
    iterator insert_after(const_iterator _pos, size_type _count,
                          const T& _value)
    {
        return iterator(_fill_insert_after(_pos.node_, _count, _value));
    }
    template <typename InputIterator>
    iterator insert_after(const_iterator _pos, InputIterator _first,
                          InputIterator _last)
    {
        return iterator(_range_insert_after(_pos.node_, _first, _last));
    }
    iterator insert_after(const_iterator _pos, std::initializer_list<T> _il)
    {
        return iterator(_range_insert_after(_pos.node_, _il.begin(),
                                            _il.end()));
    }

    template <typename... Args>
    iterator emplace_after(const_iterator _pos, Args&&... args);

    iterator erase_after(const_iterator _pos)
    {
        return iterator(_erase_after(_pos.node_));
    }
    /**
     * erase elements in range(_first, _last)
     * @param  _first position before the first removed element
     * @param  _last  position after the last removed element
     * @return        iterator points to element after the last removed element
     */
    iterator erase_after(const_iterator _first, const_iterator _last)
    {
        return iterator(_erase_after(_first.node_, _last.node_));
    }

    void push_front(const T& _value)
    {
        fwd_list_insert_node(&m_head_, _create_node(_value));
    }

    void push_front(T&& _value)
    {
        emplace_front(wt::move(_value));
    }

    void pop_front()
    {
        _erase_after(&m_head_);
    }

    template <typename... Args>
    reference emplace_front(Args&&... args);

    void resize(size_type _count)
    {
        resize(_count, value_type());
    }
    void resize(size_type _count, const T& _value);

    void swap(forward_list& other)
    {
        wt::swap(m_head_.next_, other.m_head_.next_);
    }

    /**
     *  Operations
     */
    void splice_after(const_iterator _pos, forward_list& other)
    {
        fwd_list_splice_after(_pos.node_, &other.m_head_);
    }
    void splice_after(const_iterator _pos, forward_list& other,
                      const_iterator _iter)
    {
        fwd_list_splice_after(_pos.node_, _iter.node_);
    }
    void splice_after(const_iterator _pos, forward_list& other,
                      const_iterator _first, const_iterator _last)
    {
        _Node* before_last = fwd_list_previous(_first.node_, _last.node_);
        if(_first.node_ != before_last)
            fwd_list_splice_after(_pos.node_, _first.node_, before_last);
    }

    void reverse()
    {
        if(m_head_.next_)
            m_head_.next_ = fwd_list_reverse(m_head_.next_);
    }

    void unique();
    template <typename UnaryPredicate>
    void unique(UnaryPredicate _pred);

    void remove(const T& _value)
    {
        _Node* current = &m_head_;
        while(current->next_)
        {
            if(current->next_->data_ == _value)
                _erase_after(current);
            else
                current = current->next_;
        }
    }
    template <typename UnaryPredicate>
    void remove_if(UnaryPredicate _pred)
    {
        _Node* current = &m_head_;
        while(current->next_)
        {
            if(_pred(current->next_->data_))
                _erase_after(current);
            else
                current = current->next_;
        }
    }

    void merge(forward_list& other);
    template <typename Compare>
    void merge(forward_list& other, Compare _comp);

    void sort();
    template <typename Compare>
    void sort(Compare _comp);

private:
    _Node* _create_node(const value_type& _value)
    {
        _Node* new_node = _get_node();
        try {
            wt::construct(&new_node->data_, _value);
            new_node->next_ = nullptr;
        }
        catch(...) {
            _put_node(new_node);
            throw;
        }
        return new_node;
    }
    _Node* _create_node()
    {
        _Node* new_node = _get_node();
        try {
            wt::construct(&new_node->data_);
            new_node->next_ = nullptr;
        }
        catch(...) {
            _put_node(new_node);
            throw;
        }
        return new_node;
    }
    //  assign aux
    void _fill_assign(size_type _count, const T& _value);
    template <typename Integer>
    void _assign_dispatch(Integer _count, Integer _value, wt::true_type)
    {
        _fill_assign(static_cast<size_type>(_count), static_cast<T>(_value));
    }
    template <typename InputIterator>
    void _assign_dispatch(InputIterator _first, InputIterator _last, 
                          wt::false_type);


    //  insert aux
    _Node* _fill_insert_after(_Node* _pos, size_type _count, const T& _value)
    {
        for(; _count > 0; --_count)
            _pos = fwd_list_insert_node(_pos, _create_node(_value));
        return  _pos;
    }
    template <typename InputIterator>
    _Node* _range_insert_after(_Node* _pos, InputIterator _first,
                               InputIterator _last)
    {
        return _range_insert_after_dispatch(_pos, _first, _last,
                                     wt::is_integral<InputIterator>());
    }
    template <typename Integer>
    _Node* _range_insert_after_dispatch(_Node* _pos, Integer _count,
                                        Integer _value, wt::true_type)
    {
        return _fill_insert_after(_pos, static_cast<size_type>(_count),
                                  static_cast<T>(_value));
    }
    template <typename InputIterator>
    _Node* _range_insert_after_dispatch(_Node* _pos, InputIterator _first,
                                        InputIterator _last, wt::false_type)
    {
        for(; _first != _last; ++_first)
            _pos = fwd_list_insert_node(_pos, _create_node(*_first));
        return _pos;
    }
};

/**
 *  Auxiliary functions
 */
template <typename T, typename Allocator>
void forward_list<T, Allocator>::_fill_assign(size_type _count, const T& _value)
{
    _Node* prev = &m_head_;
    _Node* first = m_head_.next_;
    while(first && _count)
    {
        first->data_ = _value;
        prev = first;
        first = first->next_;
        --_count;
    }
    if(_count == 0)
        _erase_after(prev, nullptr);
    else
        _fill_insert_after(prev, _count, _value);
}

template <typename T, typename Allocator>
template <typename InputIterator>
void forward_list<T, Allocator>::_assign_dispatch(InputIterator _first,
                                                  InputIterator _last,
                                                  wt::false_type)
{
    _Node* prev = &m_head_;
    _Node* first1 = m_head_.next_;
    while(first1 && _first != _last)
    {
        first1->data_ = *_first;
        prev = first1;
        first1 = first1->next_;
        ++_first;
    }
    if(_first == _last)
        _erase_after(prev, nullptr);
    else
        _range_insert_after(prev, _first, _last);
}



/**
 *  Interface
 */
template <typename T, typename Allocator>
forward_list<T, Allocator>&
forward_list<T, Allocator>::operator=(const forward_list& other)
{
    if(this != &other)
    {
        _Node* prev = &m_head_;
        _Node* first1 = m_head_.next_;
        const _Node* first2 = other.m_head_.next_;
        while(first1 && first2)
        {
            first1->data_ = first2->data_;
            prev = first1;
            first1 = first1->next_;
            first2= first2->next_;
        }
        if(first2 == nullptr)
            _erase_after(prev, nullptr);
        else
            _range_insert_after(prev,
                                const_iterator(const_cast<_Node*>(first2)),
                                const_iterator(nullptr));
    }
    return *this;
}

template <typename T, typename Allocator>
forward_list<T, Allocator>&
forward_list<T, Allocator>::operator=(std::initializer_list<T> _il)
{
    _Node* prev   = &m_head_;
    _Node* first1 = m_head_.next_;
    auto first2   = _il.begin();
    auto last2    = _il.end();
    while(first1 && first2 != last2)
    {
        first1->data_ = *first2;
        prev = first1;
        first1 = first1->next_;
        ++first2;
    }
    if(first2 == last2)
        _erase_after(prev, nullptr);
    else
        _range_insert_after(prev, first2, last2);

    return *this;
}

template <typename T, typename Allocator>
template <typename... Args>
typename forward_list<T, Allocator>::iterator
forward_list<T, Allocator>::emplace_after(const_iterator _pos, Args&&... args)
{
    _Node* current = _pos.node_;
    _Node* new_node = _get_node();
    try {
        ::new (static_cast<void*>(&new_node->data_))
            T(wt::forward<Args>(args)...);
        new_node->next_ = current->next_;
        current->next_ = new_node;
    }
    catch(...) {
        _put_node(new_node);
        throw;
    }
    return iterator(new_node);
}

template <typename T, typename Allocator>
template <typename... Args>
typename forward_list<T, Allocator>::reference
forward_list<T, Allocator>::emplace_front(Args&&... args)
{
    _Node* new_node = _get_node();
    try {
        ::new (static_cast<void*>(&new_node->data_)) 
            T(wt::forward<Args>(args)...);
        fwd_list_insert_node(&m_head_, new_node);
    }
    catch(...) {
        _put_node(new_node);
        throw;
    }
    return new_node->data_;
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::resize(size_type _count, const T& _value)
{
    _Node* prev = &m_head_;
    while(prev->next_ && _count)
    {
        prev = prev->next_;
        --_count;
    }
    if(_count == 0)
        _erase_after(prev, nullptr);
    else
        _fill_insert_after(prev, _count, _value);
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::unique()
{
    _Node* current = m_head_.next_;
    if(current)
    {
        while(current->next_)
        {
            if(current->data_ == current->next_->data_)
                _erase_after(current);
            else
                current = current->next_;
        }
    }
}

template <typename T, typename Allocator>
template <typename BinaryPredicate>
void forward_list<T, Allocator>::unique(BinaryPredicate _pred)
{
    _Node* current = m_head_.next_;
    if(current)
    {
        while(current->next_)
        {
            if(_pred(current->data_, current->next_->data_))
                _erase_after(current);
            else
                current = current->next_;
        }
    }
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::merge(forward_list& other)
{
    _Node* cur = &m_head_;
    while(cur->next_ && other.m_head_.next_)
    {
        if(other.m_head_.next_->data_ < cur->next_->data_)
            fwd_list_splice_after(cur, &other.m_head_, other.m_head_.next_);
        cur = cur->next_;
    }
    if(cur->next_ == nullptr)
    {
        cur->next_ = other.m_head_.next_;
        other.m_head_.next_ = nullptr;
    }

}

template <typename T, typename Allocator>
template <typename Compare>
void forward_list<T, Allocator>::merge(forward_list& other, Compare _comp)
{
    _Node* cur = &m_head_;
    while(cur->next_ && other.m_head_.next_)
    {
        if(_comp(other.m_head_.next_->data_, cur->next_->data_))
            fwd_list_splice_after(cur, &other.m_head_, other.m_head_.next_);
        cur = cur->next_;
    }
    if(cur->next_ == nullptr)
    {
        cur->next_ = other.m_head_.next_;
        other.m_head_.next_ = nullptr;
    }
}

template <typename T, typename Allocator>
void forward_list<T, Allocator>::sort()
{
    forward_list<T, Allocator> carry;
    forward_list<T, Allocator> aux[64];
    int filled = 0;
    while(!empty())
    {
        fwd_list_splice_after(&carry.m_head_, &m_head_, m_head_.next_);
        int cur = 0;
        while(cur < filled && !aux[cur].empty())
        {
            aux[cur].merge(carry);
            carry.swap(aux[cur++]);
        }
        aux[cur].swap(carry);
        if(cur == filled)
            ++filled;
    }
    for(int i = 1; i < filled; ++i)
        aux[i].merge(aux[i - 1]);

    this->swap(aux[filled - 1]);
}

template <typename T, typename Allocator>
template <typename Compare>
void forward_list<T, Allocator>::sort(Compare _comp)
{
    forward_list<T, Allocator> carry;
    forward_list<T, Allocator> aux[64];
    int filled = 0;
    while(!empty())
    {
        fwd_list_splice_after(&carry.m_head_, &m_head_, m_head_.next_);
        int cur = 0;
        while(cur < filled && !aux[cur].empty())
        {
            aux[cur].merge(carry, _comp);
            carry.swap(aux[cur++]);
        }
        aux[cur].swap(carry);
        if(cur == filled)
            ++filled;
    }
    for(int i = 1; i < filled; ++i)
        aux[i].merge(aux[i - 1], _comp);

    this->swap(aux[filled - 1]);
}

/**
 *  Non-member functions
 */
template <typename T, typename Allocator>
inline bool operator==(const wt::forward_list<T, Allocator>& lhs,
                       const wt::forward_list<T, Allocator>& rhs)
{
    return wt::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Allocator>
inline bool operator<(const wt::forward_list<T, Allocator>& lhs,
                      const wt::forward_list<T, Allocator>& rhs)
{
    return wt::lexicographical_compare(lhs.begin(), lhs.end(),
                                       rhs.begin(), rhs.end());
}

template <typename T, typename Allocator>
inline bool operator!=(const wt::forward_list<T, Allocator>& lhs,
                       const wt::forward_list<T, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Allocator>
inline bool operator<=(const wt::forward_list<T, Allocator>& lhs,
                       const wt::forward_list<T, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Allocator>
inline bool operator>(const wt::forward_list<T, Allocator>& lhs,
                      const wt::forward_list<T, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Allocator>
inline bool operator>=(const wt::forward_list<T, Allocator>& lhs,
                       const wt::forward_list<T, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <typename T, typename Allocator>
inline void swap(wt::forward_list<T, Allocator>& lhs,
                 wt::forward_list<T, Allocator>& rhs)
{
    lhs.swap(rhs);
}


} // namespace wt

#endif