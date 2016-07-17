#ifndef _STL_WT_LIST_HPP_
#define _STL_WT_LIST_HPP_

/**
 *  depend on :
 *             "type_traits.hpp"
 *             "iterator/wt_iterator_base.hpp"
 *             "iterator/wt_iterator.hpp"
 *             "allocator/wt_allocator.hpp"
 *             "allocator/wt_allocator_traits.hpp"
 *             "algorithm/wt_algo_base.hpp"
 *             
 */

namespace wt{

template <typename T>
struct List_node {
    List_node* next_;
    List_node* prev_;
    T          data_;
};

template <typename T>
class _List_const_iterator : public iterator<wt::bidirectional_iterator_tag, T> {
public:
    typedef bidirectional_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef List_node<T>                    _Node;

    _List_const_iterator() noexcept : node_(nullptr) {}
    explicit _List_const_iterator(_Node* _node) noexcept : node_(_node) {}
    _List_const_iterator(const _List_const_iterator& other) noexcept
     : node_(other.node_) {}

    reference operator*() const noexcept
    {
        return node_->data_;
    }
    pointer operator->() const noexcept
    {
        return &(this->operator*());
    }
    _List_const_iterator& operator++() noexcept
    {
        node_ = node_->next_;
        return *this;
    }
    _List_const_iterator& operator++(int) noexcept
    {
        _List_const_iterator temp = *this;
        node_ = node_->next_;
        return temp;
    }
    _List_const_iterator& operator--() noexcept
    {
        node_ = node_->prev_;
        return *this;
    }
    _List_const_iterator& operator--(int) noexcept
    {
        _List_const_iterator temp = *this;
        node_ = node_->prev_;
        return temp;
    }

    bool operator==(const _List_const_iterator& other) const noexcept
    {
        return node_ == other.node_;
    }
    bool operator!=(const _List_const_iterator& other) const noexcept
    {
        return node_ != other.node_;
    }

    _Node* node_;
};

template <typename T>
class _List_iterator : public _List_const_iterator<T> {
public:
    typedef bidirectional_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef T*                              pointer;
    typedef T&                              reference;

    typedef List_node<T>                    _Node;
    typedef _List_const_iterator<T>         _Base;
    using _Base::node_;

    _List_iterator() noexcept : _Base(nullptr) {}
    explicit _List_iterator(_Node* _node) noexcept : _Base(_node) {}
    _List_iterator(const _List_iterator& other) noexcept
     : _Base(other.node_) {}

    reference operator*() const noexcept
    {
        return node_->data_;
    }
    pointer operator->() const noexcept
    {
        return &(this->operator*());
    }
    _List_iterator& operator++() noexcept
    {
        node_ = node_->next_;
        return *this;
    }
    _List_iterator& operator++(int) noexcept
    {
        _List_iterator temp = *this;
        node_ = node_->next_;
        return temp;
    }
    _List_iterator& operator--() noexcept
    {
        node_ = node_->prev_;
        return *this;
    }
    _List_iterator& operator--(int) noexcept
    {
        _List_iterator temp = *this;
        node_ = node_->prev_;
        return temp;
    }

    bool operator==(const _List_iterator& other) const noexcept
    {
        return node_ == other.node_;
    }
    bool operator!=(const _List_iterator& other) const noexcept
    {
        return node_ != other.node_;
    }
};

template <typename T, typename Allocator, bool _IsStatic>
class List_alloc_base {
public:
    typedef typename allocator_traits<Allocator>::allocator_type allocator_type;
    allocator_type get_allocator() const 
    {
        return m_allocator_;
    }

    List_alloc_base(const allocator_type& _a)
     : m_allocator_(_a), m_node_(nullptr) {}

protected:
    List_node<T>* _get_node()
    {
        return m_allocator_.allocate(1);
    }
    void _put_node(List_node<T>* _p)
    {
        m_allocator_.deallocate(_p, 1);
    }
protected:
    typename _Alloc_traits<List_node<T>, Allocator>::allocator_type 
                    m_allocator_;
    List_node<T>*   m_node_;
};

template <typename T, typename Allocator>
class List_alloc_base<T, Allocator, true> {
public:
    typedef typename allocator_traits<Allocator>::allocator_type allocator_type;
    allocator_type get_allocator() const
    {
        return allocator_type();
    }

    List_alloc_base(const allocator_type& _a)
     : m_node_(nullptr) {}

protected:
    typedef typename _Alloc_traits<List_node<T>, Allocator>::_Alloc_type
                        _Alloc_type;
    List_node<T>* _get_node()
    {
        return _Alloc_type::allocate(1);
    }
    void _put_node(List_node<T>* _p)
    {
        _Alloc_type::deallocate(_p, 1);
    }
protected:
    List_node<T>*   m_node_;
};

template <typename T, typename Allocator>
class List_base : public List_alloc_base<T, Allocator,
                     _Alloc_traits<T, Allocator>::isStatic> {
public:
    typedef List_alloc_base<T, Allocator, _Alloc_traits<T, Allocator>::isStatic>
            _Base;
    typedef typename _Base::allocator_type  allocator_type;

    using _Base::_get_node;
    using _Base::_put_node;
    using _Base::m_node_;

    List_base(const allocator_type& _a) : _Base(_a) 
    {
        m_node_ = _get_node();
        m_node_->prev_ = m_node_;
        m_node_->next_ = m_node_;
    }
    ~List_base()
    {
        clear();
        _put_node(m_node_);
    }
    void clear();

};

template <typename T, typename Allocator>
void List_base<T, Allocator>::clear()
{
    List_node<T>* current = m_node_->next_;
    while(current != m_node_)
    {
        List_node<T>* temp = current;
        current = current->next_;
        destroy(&temp->data_);
        _put_node(temp);
    }
    m_node_->prev_ = m_node_;
    m_node_->next_ = m_node_;
}

template <typename T, typename Allocator = wt::allocator<T>>
class list : protected List_base<T, Allocator> {
protected:
    typedef List_base<T, Allocator>     _Base;
    using _Base::_get_node;
    using _Base::_put_node;
    using _Base::m_node_;

public:
    typedef typename allocator_traits<Allocator>::allocator_type    allocator_type;
    typedef typename allocator_traits<Allocator>::size_type         size_type;
    typedef typename allocator_traits<Allocator>::difference_type   difference_type;
    typedef T                                                       value_type;
    typedef const value_type&                                       const_reference;
    typedef value_type&                                             reference;
    typedef const value_type*                                       const_pointer;
    typedef value_type*                                             pointer;
    typedef _List_const_iterator<value_type>                        const_iterator;
    typedef _List_iterator<value_type>                              iterator;
    typedef reverse_iterator<const_iterator>                        const_reverse_iterator;
    typedef reverse_iterator<iterator>                              reverse_iterator;

    allocator_type get_allocator() const 
    {
        return _Base::get_allocator();
    }

    list() : list(allocator_type()) {}
    explicit list(const allocator_type& _a) : _Base(_a) {}
    list(size_type _count, const T& _value,
         const allocator_type& _a = allocator_type())
     : _Base(_a)
    {
        insert(begin(), _count, _value);
    }
    explicit list(size_type _count, const allocator_type& _a = allocator_type())
     : list(_count, T(), _a) {}
    template <typename InputIterator>
    list(InputIterator _first, InputIterator _last,
         const allocator_type& _a = allocator_type())
     : _Base(_a)
    {
        insert(begin(), _first, _last);
    }
    list(const list& other) : _Base(other.get_allocator())
    {
        insert(begin(), other.begin(), other.end());
    }
    list(const list& other, const allocator_type& _a) : _Base(_a)
    {
        insert(begin(), other.begin(), other.end());
    }
    list(list&& other) noexcept : _Base(other.get_allocator())
    {
        this->swap(other);
    }
    list(list&& other, const allocator_type& _a) noexcept : _Base(_a)
    {
        this->swap(other);
    }
    ~list() {}
    list& operator=(const list& other);

    list& operator=(list&& other) noexcept
    {
        this->swap(other);
        return *this;
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
        return *cbegin();
    }
    reference back()
    {
        return *(--end());
    }
    const_reference back() const
    {
        return *(--cend());
    }

    /**
     *  Iterator Operations
     */
    iterator begin() noexcept
    {   
        return iterator(m_node_->next_);
    }
    const_iterator begin() const noexcept
    {   
        return const_iterator(m_node_->next_);
    }
    const_iterator cbegin() const noexcept
    {   
        return const_iterator(m_node_->next_);
    }
    iterator end() noexcept
    {   
        return iterator(m_node_);
    }
    const_iterator end() const noexcept
    {   
        return const_iterator(m_node_);
    }
    const_iterator cend() const noexcept
    {   
        return const_iterator(m_node_);
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
        return m_node_ == m_node_->next_;
    }
    size_type size() const noexcept
    {
        return static_cast<size_type>(wt::distance(begin(), end()));
    }
    size_type max_size() const noexcept
    {
        return static_cast<size_type>(-1);
    }

    /**
     *  Modify Operations
     */
    void assign(size_type _count, const T& _value)
    {
        _fill_assign(_count, _value);
    }
    template <typename InputIterator>
    void assign(InputIterator _first, InputIterator _last)
    {
        _assign_dispatch(_first, _last, wt::is_integral<InputIterator>());
    }

    iterator insert(const_iterator _pos, const T& _value)
    {
        List_node<T>* temp = _creat_node(_value);
        temp->next_ = _pos.node_;
        temp->prev_ = _pos.node_->prev_;
        _pos.node_->prev_->next_ = temp;
        _pos.node_->prev_ = temp;
        return iterator(temp);
    }
    iterator insert(const_iterator _pos, size_type _count, const T& _value)
    {
        List_node<T>* previous = _pos.node_->prev_;
        _fill_insert(_pos, _count, _value);
        return iterator(previous->next_);
    }
    template <typename InputIterator>
    iterator insert(const_iterator _pos, InputIterator _first, 
                    InputIterator _last)
    {
        List_node<T>* previous = _pos.node_->prev_;
        _insert_dispatch(_pos, _first, _last, wt::is_integral<InputIterator>());
        return iterator(previous->next_);
    }

    iterator erase(const_iterator _pos)
    {
        _pos.node_->prev_->next_ = _pos.node_->next_;
        _pos.node_->next_->prev_ = _pos.node_->prev_;
        iterator iter(_pos.node_->next_);
        wt::destroy(&_pos.node_->data_);
        _put_node(_pos.node_);
        return iter;
    }
    iterator erase(const_iterator _first, const_iterator _last)
    {
        for(; _first != _last; ++_first)
            erase(_first);
        return iterator(_last.node_);
    }
    void clear() noexcept
    {
        _Base::clear();
    }

    void push_front(const T& _value)
    {
        insert(begin(), _value);
    }
    void push_back(const T& _value)
    {
        insert(end(), _value);
    }
    void pop_front()
    {
        erase(begin());
    }
    void pop_back()
    {
        iterator temp = end();
        erase(--temp);
    }
    template <typename... Args>
    iterator emplace(const_iterator _pos, Args&&... args);

    template <typename... Args>
    reference emplace_back(Args&&... args)
    {
        iterator temp = emplace(end(), wt::forward<Args>(args)...);
        return temp.node_->data_;
    }
    template <typename... Args>
    reference emplace_front(Args&&... args)
    {
        iterator temp = emplace(begin(), wt::forward<Args>(args)...);
        return temp.node_->data_;
    }
    void resize(size_type _count)
    {
        resize(_count, T());
    }
    void resize(size_type _count, const T& _value);

    void swap(list& other) noexcept
    {
        wt::swap(m_node_, other.m_node_);
    }

    void merge(list& other);
    template <typename Compare>
    void merge(list& other, Compare _comp);

    void splice(const_iterator _pos, list& other)
    {
        if(!other.empty())
            _transfer(_pos, other.cbegin(), other.cend());
    }
    void splice(const_iterator _pos, list& other, const_iterator _pos2)
    {
        const_iterator temp = _pos2;
        ++temp;
        if(_pos != _pos2 && _pos != temp)
            _transfer(_pos, _pos2, temp);
    }
    void splice(const_iterator _pos, list& other,
                const_iterator _first, const_iterator _last)
    {
        if(_pos != _last && _first != _last)
            _transfer(_pos, _first, _last);
    }

    void remove(const T& _value);
    template <typename UnaryPredicate>
    void remove_if(UnaryPredicate _pred);

    void reverse();

    void unique();
    template <typename BinaryPredicate>
    void unique(BinaryPredicate _pred);

    void sort();
    template <typename Compare>
    void sort(Compare _comp);
protected:
    List_node<T>* _creat_node(const T& _value)
    {
        List_node<T>* temp = _get_node();
        try {
            wt::construct(&temp->data_, _value);
        }
        catch(...) {
            wt::destroy(&temp->data_);
            _put_node(temp);
            throw;
        }
        return temp;
    }
    List_node<T>* _creat_node()
    {
        List_node<T>* temp = _get_node();
        try {
            wt::construct(&temp->data_);
        }
        catch(...) {
            wt::destroy(&temp->data_);
            _put_node(temp);
            throw;
        }
        return temp;
    }

    void _fill_assign(size_type _count, const T& _value)
    {
        iterator start = begin();
        iterator finish = end();
        for(; start != finish && _count > 0; ++start, --_count)
            *start = _value;
        if(_count > 0)
            insert(finish, _count, _value);
        else
            erase(start, finish);
    }
    template <typename Integer>
    void _assign_dispatch(Integer _count, Integer _value, wt::true_type)
    {
        _fill_assign(static_cast<size_type>(_count), static_cast<T>(_value));
    }
    template <typename InputIterator>
    void _assign_dispatch(InputIterator _first, InputIterator _last,
                          wt::false_type)
    {
        iterator start = begin();
        iterator finish = end();
        for(; start != finish && _first != _last; ++start, ++_first)
            *start = *_first;
        if(_first == _last)
            erase(start, finish);
        else
            insert(finish, _first, _last);
    }

    void _fill_insert(const_iterator _pos, size_type _count, const T& _value)
    {
        for(; _count > 0; --_count)
            insert(_pos, _value);
    }

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
        for(; _first != _last; ++_first)
            insert(_pos, *_first);
    }

    void _transfer(const_iterator _pos, const_iterator _first,
                   const_iterator _last)
    {
        if(_pos != _last)
        {
            _last.node_->prev_->next_  = _pos.node_;
            _first.node_->prev_->next_ = _last.node_;
            _pos.node_->prev_ ->next_  = _first.node_;

            List_node<T>* temp  = _pos.node_->prev_;
            _pos.node_->prev_   = _last.node_->prev_;
            _last.node_->prev_  = _first.node_->prev_;
            _first.node_->prev_ = temp;
        }
    }
};

template <typename T, typename Allocator>
list<T, Allocator>& 
list<T, Allocator>::operator=(const list& other)
{
    if(this != &other)
    {
        iterator _first1 = begin();
        iterator _last1  = end();
        const_iterator _first2 = other.cbegin();
        const_iterator _last2  = other.cend();
        while(_first1 != _last1 && _first2 != _last2)
        {
            *_first1++ = *_first2++;
        }
        if(_first2 == _last2)
            erase(_first1, _last1);
        else
            insert(_last1, _first2, _last2);
    }
    return *this;
}

template <typename T, typename Allocator>
void list<T, Allocator>::merge(list& other)
{
    iterator first1 = begin();
    iterator last1  = end();
    iterator first2 = other.begin();
    iterator last2  = other.end();
    while(first1 != last1 && first2 != last2)
    {
        if(*first2 < *first1)
        {
            iterator next = first2;
            ++next;
            _transfer(first1, first2, next);
            first2 = next;
        }
        else
        {
            ++first1;
        }
    }
    if(first2 != last2)
        _transfer(last1, first2, last2);
}

template <typename T, typename Allocator>
template <typename Compare>
void list<T, Allocator>::merge(list& other, Compare _comp)
{
    iterator first1 = begin();
    iterator last1  = end();
    iterator first2 = other.begin();
    iterator last2  = other.end();
    while(first1 != last1 && first2 != last2)
    {
        if(_comp(*first2, *first1))
        {
            iterator next = first2;
            ++next;
            _transfer(first1, first2, next);
            first2 = next;
        }
        else
        {
            ++first1;
        }
    }
    if(first2 != last2)
        _transfer(last1, first2, last2);
}


template <typename T, typename Allocator>
template <typename... Args>
typename list<T, Allocator>::iterator
list<T, Allocator>::emplace(const_iterator _pos, Args&&... args)
{
    List_node<T>* temp = _get_node();
    ::new (static_cast<void*>(&temp->data_)) T(wt::forward<Args>(args)...);
    temp->next_ = _pos.node_;
    temp->prev_ = _pos.node_->prev_;
    _pos.node_->prev_  = temp;
    temp->prev_->next_ = temp;
    return iterator(temp);
}

template <typename T, typename Allocator>
void list<T, Allocator>::resize(size_type _count, const T& _value)
{
    iterator start = begin();
    iterator finish = end();
    for(; start != finish && _count > 0; ++start, --_count)
        ;
    if(_count > 0)
        insert(end(), _count, _value);
    else
        erase(start, finish);
}

template <typename T, typename Allocator>
void list<T, Allocator>::remove(const T& _value)
{
    iterator current = begin();
    iterator finish  = end();
    while(current != finish)
    {
        if(*current == _value)
            current = erase(current);
        else
            ++current;   
    }
}

template <typename T, typename Allocator>
template <typename UnaryPredicate>
void list<T, Allocator>::remove_if(UnaryPredicate _pred)
{
    iterator current = begin();
    iterator finish = end();
    while(current != finish)
    {
        if(_pred(*current))
            current = erase(current);
        else
            ++current;
    }
}

template <typename T, typename Allocator>
void list<T, Allocator>::reverse()
{
    List_node<T>* current = m_node_;
    do
    {
        wt::swap(current->prev_, current->next_);
        current = current->prev_;
    } while(current != m_node_);
}


template <typename T, typename Allocator>
void list<T, Allocator>::unique()
{
    iterator current = begin();
    iterator finish  = end();
    if(current == finish) return;
    iterator next = current;
    while(++next != finish)
    {
        if(*current == *next)
        {
            erase(next);
            next = current;
        }
        else
        {   
            current = next;
        }
    }
}

template <typename T, typename Allocator>
template <typename BinaryPredicate>
void list<T, Allocator>::unique(BinaryPredicate _pred)
{
    iterator current = begin();
    iterator finish  = end();
    if(current == finish) return;
    iterator next = current;
    while(++next != finish)
    {
        if(_pred(*current, *next))
        {
            erase(next);
            next = current;
        }
        else
        {
            current = next;
        }
    }
}

template <typename T, typename Allocator>
void list<T, Allocator>::sort()
{
    if(m_node_->next_ != m_node_ && m_node_->next_->next_ != m_node_)
    {
        list<T, Allocator> carry;
        list<T, Allocator> aux[64];
        int filled = 0;
        while(!empty())
        {
            carry.splice(carry.begin(), *this, begin());
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
}

template <typename T, typename Allocator>
template <typename Compare>
void list<T, Allocator>::sort(Compare _comp)
{
    if(m_node_->next_ != m_node_ && m_node_->next_->next_ != m_node_)
    {
        list<T, Allocator> carry;
        list<T, Allocator> aux[64];
        int filled = 0;
        while(!empty())
        {
            carry.splice(carry.begin(), *this, begin());
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
}

template <typename T, typename Allocator>
bool operator==(const list<T, Allocator>& lhs, const list<T,Allocator>& rhs)
{
    if(lhs.size() != rhs.size())
        return false;
    auto first1 = lhs.cbegin();
    auto last1  = lhs.cend();
    auto first2 = rhs.cbegin();
    auto last2  = rhs.cend();
    while(first1 != last1 && first2 != last2 && *first1 == *first2)
    {
        ++first1;
        ++first2;
    }
    return  first1 == last1 && first2 == last2;
}

template <typename T, typename Allocator>
inline bool operator<(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs)
{
    return wt::lexicographical_compare(lhs.cbegin(), lhs.cend(),
                                       rhs.cbegin(), rhs.cend());
}

template <typename T, typename Allocator>
inline bool operator!=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Allocator>
inline bool operator>(const list<T, Allocator>& lhs, const list<T,Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Allocator>
inline bool operator<=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Allocator>
inline bool operator>=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <typename T, typename Allocator>
void swap(list<T, Allocator>& lhs, list<T, Allocator>& rhs)
{
    lhs.swap(rhs);
}

} // namespace wt
#endif