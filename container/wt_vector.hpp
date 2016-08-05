#ifndef _STL_WT_VECTOR_HPP_
#define _STL_WT_VECTOR_HPP_

/**
 *  depend on :
 *             <cstddef>
 *             <limits>
 *             <stdexcept>
 *             "../allocator/wt_allocator_traits.hpp"
 *             "../allocator/wt_construct.hpp"
 *             "../iterator/wt_iterator_base.hpp"
 *             "../iterator/wt_iterator.hpp"
 *             "../algorithm/wt_uninitialized.hpp"
 *             "../algorithm/wt_algo_base.hpp"
 */

namespace wt{

template <typename T>
class _Vec_const_iterator : public iterator<wt::random_access_iterator_tag, T> {
public:
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef T*                              _Ptr;

    _Vec_const_iterator() noexcept : m_ptr_(nullptr) {}
    explicit _Vec_const_iterator(_Ptr _ptr) noexcept : m_ptr_(_ptr) {}
    _Vec_const_iterator(const _Vec_const_iterator<T>& other) noexcept
     : m_ptr_(other.m_ptr_) {}

    reference operator*() const noexcept
    {
        return *m_ptr_;
    }
    pointer operator->() const noexcept
    {
        return &(this->operator*());
    }
    reference operator[](difference_type _offset) const noexcept
    {
        return m_ptr_[_offset];
    }
    _Vec_const_iterator& operator++() noexcept
    {
        ++m_ptr_;
        return *this;
    }
    _Vec_const_iterator operator++(int) noexcept
    {
        return _Vec_const_iterator(m_ptr_++);
    }
    _Vec_const_iterator& operator--() noexcept
    {
        --m_ptr_;
        return *this;
    }
    _Vec_const_iterator operator--(int) noexcept
    {
        return _Vec_const_iterator(m_ptr_--);
    }
    _Vec_const_iterator& operator+=(difference_type _offset) noexcept
    {
        m_ptr_ += _offset;
        return *this;
    }
    _Vec_const_iterator& operator-=(difference_type _offset) noexcept
    {
        m_ptr_ -= _offset;
        return *this;
    }

    inline friend _Vec_const_iterator operator+(const _Vec_const_iterator& _iter, 
                                                difference_type _offset) noexcept
    {
        return _Vec_const_iterator(_iter.m_ptr_ + _offset);
    }
    inline friend _Vec_const_iterator operator+(difference_type _offset,
                                     const _Vec_const_iterator& _iter) noexcept
    {
        return operator+(_iter, _offset);
    }
    inline friend _Vec_const_iterator operator-(const _Vec_const_iterator& _iter,
                                            difference_type _offset) noexcept
    {
        return _Vec_const_iterator(_iter.m_ptr_ - _offset);
    }

    inline friend difference_type operator-(const _Vec_const_iterator& lhs, 
                                    const _Vec_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ - rhs.m_ptr_;
    }
    inline friend bool operator==(const _Vec_const_iterator& lhs,
                                  const _Vec_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ == rhs.m_ptr_;
    }
    inline friend bool operator!=(const _Vec_const_iterator& lhs,
                                  const _Vec_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ != rhs.m_ptr_;
    }
    inline friend bool operator<(const _Vec_const_iterator& lhs,
                                 const _Vec_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ < rhs.m_ptr_;
    }
    inline friend bool operator<=(const _Vec_const_iterator& lhs,
                                  const _Vec_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ <= rhs.m_ptr_;
    }
    inline friend bool operator>(const _Vec_const_iterator& lhs,
                                 const _Vec_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ > rhs.m_ptr_;
    }
    inline friend bool operator>=(const _Vec_const_iterator& lhs,
                                  const _Vec_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ >= rhs.m_ptr_;
    }

    _Ptr m_ptr_;
};

template <typename T>
class _Vec_iterator: public _Vec_const_iterator<T> {
public:
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef T*                              pointer;
    typedef T&                              reference;

    typedef _Vec_const_iterator<T>                _Base;
    using _Base::m_ptr_;

    _Vec_iterator() noexcept : _Base(nullptr) {}
    explicit _Vec_iterator(pointer _ptr) noexcept : _Base(_ptr) {}
    _Vec_iterator(const _Vec_iterator<T>& other) noexcept
     : _Base(other.m_ptr_) {}

    reference operator*() const noexcept
    {
        return *m_ptr_;
    }
    pointer operator->() const noexcept
    {
        return &(this->operator*());
    }
    reference operator[](difference_type _offset) const noexcept
    {
        return m_ptr_[_offset];
    }
    _Vec_iterator& operator++() noexcept
    {
        ++m_ptr_;
        return *this;
    }
    _Vec_iterator operator++(int) noexcept
    {
        return _Vec_iterator(m_ptr_++);
    }
    _Vec_iterator& operator--() noexcept
    {
        --m_ptr_;
        return *this;
    }
    _Vec_iterator operator--(int) noexcept
    {
        return _Vec_iterator(m_ptr_--);
    }
    _Vec_iterator& operator+=(difference_type _offset) noexcept
    {
        m_ptr_ += _offset;
        return *this;
    }
    _Vec_iterator& operator-=(difference_type _offset) noexcept
    {
        m_ptr_ -= _offset;
        return *this;
    }

    inline friend _Vec_iterator operator+(const _Vec_iterator& _iter, 
                                            difference_type _offset) noexcept
    {
        return _Vec_iterator(_iter.m_ptr_ + _offset);
    }
    inline friend _Vec_iterator operator+(difference_type _offset,
                                     const _Vec_iterator& _iter) noexcept
    {
        return operator+(_iter, _offset);
    }
    inline friend _Vec_iterator operator-(const _Vec_iterator& _iter,
                                            difference_type _offset) noexcept
    {
        return _Vec_iterator(_iter.m_ptr_ - _offset);
    }

    inline friend difference_type operator-(const _Vec_iterator& lhs, 
                                    const _Vec_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ - rhs.m_ptr_;
    }
    inline friend bool operator==(const _Vec_iterator& lhs,
                                  const _Vec_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ == rhs.m_ptr_;
    }
    inline friend bool operator!=(const _Vec_iterator& lhs,
                                  const _Vec_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ != rhs.m_ptr_;
    }
    inline friend bool operator<(const _Vec_iterator& lhs,
                                 const _Vec_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ < rhs.m_ptr_;
    }
    inline friend bool operator<=(const _Vec_iterator& lhs,
                                  const _Vec_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ <= rhs.m_ptr_;
    }
    inline friend bool operator>(const _Vec_iterator& lhs,
                                 const _Vec_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ > rhs.m_ptr_;
    }
    inline friend bool operator>=(const _Vec_iterator& lhs,
                                 const _Vec_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ >= rhs.m_ptr_;
    }
};



template <typename T, typename Allocator, bool _IsStatic>
class _Vector_alloc_base {
public:
    typedef typename allocator_traits<Allocator>::allocator_type
            allocator_type;

    _Vector_alloc_base(const allocator_type& _a)
    :m_data_allocator_(_a), m_start_(nullptr), m_finish_(nullptr), 
     m_end_of_storage_(nullptr) {}

     allocator_type get_allocator() const
     {
        return m_data_allocator_;
     }
protected:
    T* _allocate(size_t _n)
    {
        return m_data_allocator_.allocate(_n);
    }

    void _deallocate(T* _p, size_t _n)
    {
        if(_p)
            m_data_allocator_.deallocate(_p, _n);
    }
protected:
    allocator_type  m_data_allocator_;
    T*              m_start_;
    T*              m_finish_;
    T*              m_end_of_storage_;
};

/**
 *  specialization for no state allocator
 */
template <typename T, typename Allocator>
 class _Vector_alloc_base<T, Allocator, true> {
public:
    typedef typename allocator_traits<Allocator>::allocator_type
            allocator_type;

    _Vector_alloc_base(const allocator_type& _a)
    : m_start_(nullptr), m_finish_(nullptr), m_end_of_storage_(nullptr) {}

    allocator_type get_allocator() const
    {
        return allocator_type();
    }
protected:
    typedef typename _Alloc_traits<T, Allocator>::_Alloc_type _Alloc_type;
    T* _allocate(size_t _n)
    {
        return _Alloc_type::allocate(_n);
    }

    void _deallocate(T* _p, size_t _n)
    {
        _Alloc_type::deallocate(_p, _n);
    }
protected:
    T*  m_start_;
    T*  m_finish_;
    T*  m_end_of_storage_;
 };

template <typename T, typename Allocator>
class Vector_base : public _Vector_alloc_base<T, Allocator, 
                    _Alloc_traits<T, Allocator>::isStatic> {
public:
    typedef _Vector_alloc_base<T, Allocator, 
            _Alloc_traits<T, Allocator>::isStatic> _Base;
    typedef typename _Base::allocator_type         allocator_type;

    using _Base::m_start_;
    using _Base::m_finish_;
    using _Base::m_end_of_storage_;
    using _Base::_allocate;
    using _Base::_deallocate;

    Vector_base(const allocator_type& _a) : _Base(_a) {}
    Vector_base(size_t _n, const allocator_type& _a) : _Base(_a)
    {
        m_start_ = _allocate(_n);
        m_finish_ = m_start_;
        m_end_of_storage_ = m_start_ + _n;
    }

    ~Vector_base()
    {
        _deallocate(m_start_, m_end_of_storage_ - m_start_);
    }
};

template <typename T, typename Allocator = allocator<T>>
class vector : protected Vector_base<T, Allocator> {
    typedef Vector_base<T, Allocator> _Base;
public:
    typedef T                                   value_type;
    typedef value_type*                         pointer;
    typedef const value_type*                   const_pointer;
    typedef _Vec_iterator<value_type>           iterator;
    typedef _Vec_const_iterator<value_type>     const_iterator;
    typedef value_type&                         reference;
    typedef const value_type&                   const_reference;
    typedef size_t                              size_type;
    typedef std::ptrdiff_t                      difference_type;

    typedef typename _Base::allocator_type      allocator_type;
    typedef wt::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef wt::reverse_iterator<iterator>          reverse_iterator;

    allocator_type get_allocator() const
    {
        return _Base::get_allocator();
    } 

protected:
    using _Base::m_start_;
    using _Base::m_finish_;
    using _Base::m_end_of_storage_;
    using _Base::_allocate;
    using _Base::_deallocate;

public:
    vector() : _Base(allocator_type()) {}
    explicit vector(const Allocator& _alloc) : _Base(_alloc) {}
    vector(size_type _count, const T& _value, 
           const Allocator& _alloc = allocator_type()) : _Base(_count, _alloc)
    {
        m_finish_ = wt::uninitialized_fill_n(m_start_, _count, _value);
    }
    explicit vector(size_type _count, const Allocator& _alloc = allocator_type()) 
             : _Base(_count, _alloc)
    {
        m_finish_ = wt::uninitialized_fill_n(m_start_, _count, T());
    }

    template <typename InputIterator>
    vector(InputIterator _first, InputIterator _last, 
           const Allocator& _alloc = allocator_type()) : _Base(_alloc)
    {
        _initialize_aux(_first, _last, is_integral<InputIterator>());
    }

    vector(const vector<T, Allocator>& other) 
    : _Base(other.size(), other.get_allocator())
    {
        m_finish_ = wt::uninitialized_copy(other.m_start_, other.m_finish_, m_start_);
    }

    vector(const vector<T, Allocator>& other, const Allocator& _alloc)
    : _Base(other.size(), _alloc)
    {
        m_finish_ = wt::uninitialized_copy(other.m_start_, other.m_finish_, m_start_);
    }

    vector(vector<T, Allocator>&& other) : _Base(other.get_allocator())
    {
        swap(other);
    }

    vector(std::initializer_list<T> _il,
           const Allocator& _alloc = allocator_type())
     : _Base(_il.size(), _alloc)
    {
        m_finish_ = wt::uninitialized_copy(_il.begin(), _il.end(), m_start_);
    }

    ~vector() { wt::destroy(m_start_, m_finish_); }
    vector<T, Allocator>& operator=(const vector<T, Allocator>& other);
    vector<T, Allocator>& operator=(vector<T, Allocator>&& other) noexcept
    {
        swap(other);
    }
    vector<T, Allocator>& operator=(std::initializer_list<T> _il)
    {
        assign(_il.begin(), _il.end());
        return *this;
    }
    void assign(size_type _count, const T& _value)
    {
        _fill_assign(_count, _value);
    }

    template <typename InputIterator>
    void assign(InputIterator _first, InputIterator _last)
    {
        _assign_dispatch(_first, _last, is_integral<InputIterator>());
    }
    /**
     *  iterator operation
     */
    // begin
    iterator begin() noexcept
    {
        return iterator(m_start_);
    }
    const_iterator begin() const noexcept
    {
        return const_iterator(m_start_);
    }
    const_iterator cbegin() const noexcept
    {
        return const_iterator(m_start_);
    }
    // end
    iterator end() noexcept
    {
        return iterator(m_finish_);
    }
    const_iterator end() const noexcept
    {
        return const_iterator(m_finish_);
    }
    const_iterator cend() const noexcept
    {
        return const_iterator(m_finish_);
    }
    // rbegin
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(cend());
    }
    // rend
    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const noexcept
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(cbegin());
    }

    /**
     *  capacity operation
     */
    bool empty() const noexcept
    {
        return begin() == end();
    }
    size_type size() const noexcept
    {
        return static_cast<size_type>(end() - begin());
    }
    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
    size_type capacity() const noexcept
    {
        return static_cast<size_type>(m_end_of_storage_ - m_start_);
    }
    void reserve(size_type _new_cap);
    void shrink_to_fit()
    {
        if(m_end_of_storage_ != m_finish_)
        {
            pointer new_start = _allocate(size());
            pointer new_finish;
            try {
                new_finish = wt::uninitialized_copy(m_start_, m_finish_, new_start);
            }
            catch(...) {
                _deallocate(new_start, size());
                throw;
            }
            clear();
            m_start_ = new_start;
            m_finish_ = new_finish;
            m_end_of_storage_ = m_finish_;
        }
    }

    /**
     *  element access
     */
    reference operator[](size_type _pos)
    {
        return *(begin() + _pos);
    }
    const_reference operator[](size_type _pos) const
    {
        return *(begin() + _pos);
    }
    reference at(size_type _pos)
    {
        _range_check(_pos);
        return *(begin() + _pos);
    }
    const_reference at(size_type _pos) const
    {
        _range_check(_pos);
        return *(begin() + _pos);
    }
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
        iterator temp = end();
        return *(--temp);
    }
    const_reference back() const
    {
        const_iterator temp = cend();
        return *(--temp);
    }
    pointer data() noexcept
    {
        return m_start_;
    }
    const_pointer data() const noexcept
    {
        return m_start_;
    }

    /**
     *  modify operation
     */
    void clear() noexcept
    {
        erase(begin(), end());
    }
    iterator insert(const_iterator _pos, const T& _value)
    {
        size_type pos_diff = _pos.m_ptr_ - m_start_;
        if(m_finish_ != m_end_of_storage_ && _pos.m_ptr_ == m_finish_)
        {
            wt::construct(_pos.m_ptr_, _value);
            ++m_finish_;
        }
        else
        {
            _insert_aux(_pos, _value);
        }
        return begin() + pos_diff;
    }
    iterator insert(const_iterator _pos, size_type _count, const T& _value)
    {
        size_type pos_diff = _pos.m_ptr_ - m_start_;
        _fill_insert(_pos, _count, _value);
        return begin() + pos_diff;
    }
    template <typename InputIterator>
    iterator insert(const_iterator _pos, InputIterator _first, InputIterator _last)
    {
        const size_type pos_diff = _pos.m_ptr_ - m_start_;
        _insert_dispatch(_pos, _first, _last, is_integral<InputIterator>());
        return begin() + pos_diff;
    }
    iterator insert(const_iterator _pos, std::initializer_list<T> _il)
    {
        return insert(_pos, _il.begin(), _il.end());
    }
    
    template <typename... Args>
    iterator emplace(const_iterator _pos, Args&&... args)
    {
        const size_type pos_diff = _pos.m_ptr_ - m_start_;
        if(m_finish_ != m_end_of_storage_ && _pos.m_ptr_ == m_finish_)
        {
            ::new (static_cast<void*>(m_finish_)) T(wt::forward<Args>(args)...);
            ++m_finish_;
        }
        else
        {
            _emplace_aux(_pos, wt::forward<Args>(args)...);
        }
        return begin() + pos_diff;
    }
    template <typename... Args>
    reference emplace_back(Args&&... args)
    {
        if(m_finish_ != m_end_of_storage_)
        {
            ::new (static_cast<void*>(m_finish_)) T(wt::forward<Args>(args)...);
            ++m_finish_;
        }
        else
        {
            _emplace_aux(end(), wt::forward<Args>(args)...);
        }
        return *(m_finish_ - 1);
    }

    iterator erase(const_iterator _pos)
    {
        if(_pos.m_ptr_ + 1 != m_finish_)
            wt::copy(_pos.m_ptr_ + 1, m_finish_, _pos.m_ptr_);
        --m_finish_;
        wt::destroy(m_finish_);
        return iterator(_pos.m_ptr_);
    }
    iterator erase(const_iterator _first, const_iterator _last)
    {
        pointer temp = wt::copy(_last.m_ptr_, m_finish_, _first.m_ptr_);
        wt::destroy(temp, m_finish_);
        m_finish_ = temp;
        // m_finish_ = m_finish_ - (_last - _first);
        return iterator(_first.m_ptr_);
    }

    void push_back(const T& _value)
    {
        if(m_finish_ != m_end_of_storage_)
        {
            wt::construct(m_finish_, _value);
            ++m_finish_;
        }
        else
        {
            _insert_aux(end(), _value);
        }
    }
    void pop_back()
    {
        --m_finish_;
        wt::destroy(m_finish_);
    }

    void resize(size_type _count, const T& _value)
    {
        if(_count < size())
            erase(begin() + _count, end());
        else
            insert(end(), _count - size(), _value);
    }
    void resize(size_type _count)
    {
        resize(_count, T());
    }
    void swap(vector<T, Allocator>& other)
    {
        wt::swap(m_start_, other.m_start_);
        wt::swap(m_finish_, other.m_finish_);
        wt::swap(m_end_of_storage_, other.m_end_of_storage_);
    }
protected:
    /**
     *  auxiliary member functions
     */
    void _range_check(size_type _pos) const
    {
        if(!(_pos < this->size()))
            throw std::out_of_range("vector");
    }
    template <typename Integer>
    void _initialize_aux(Integer _count, Integer _value, true_type)
    {
        m_start_ = _allocate(_count);
        m_end_of_storage_ = m_start_ + _count;
        m_finish_ = wt::uninitialized_fill_n(m_start_, _count, _value);
    }
    template <typename InputIterator>
    void _initialize_aux(InputIterator _first, InputIterator _last, false_type)
    {
        _range_initialize(_first, _last, _ITERATOR_CATEGORY(_first));
    }

    template <typename InputIterator>
    void _range_initialize(InputIterator _first, InputIterator _last,
                           input_iterator_tag)
    {
        for(; _first != _last; ++_first)
        {
            push_back(*_first);
        }
    }

    template <typename ForwardIterator>
    void _range_initialize(ForwardIterator _first, ForwardIterator _last,
                           forward_iterator_tag)
    {
        size_type n_elems = wt::distance(_first, _last);
        m_start_ = _allocate(n_elems);
        m_end_of_storage_ = m_start_ + n_elems;
        m_finish_ =  wt::uninitialized_copy(_first, _last, m_start_);
    }

    template <typename ForwardIterator>
    iterator _allocate_and_copy(size_type _n, ForwardIterator _first,
                                       ForwardIterator _last)
    {
        pointer _result = _allocate(_n);
        try {
            wt::uninitialized_copy(_first, _last, _result);
        }
        catch(...) {
            _deallocate(_result, _n);
            throw;
        }
        return iterator(_result);
    }

    void _fill_assign(size_type _n, const T& _value);

    template <typename Integer>
    void _assign_dispatch(Integer _count, Integer _value, true_type)
    {
        _fill_assign(static_cast<size_type>(_count), static_cast<T>(_value));
    }
    template <typename InputIterator>
    void _assign_dispatch(InputIterator _first, InputIterator _last, false_type)
    {
        _assign_dispatch_aux(_first, _last, _ITERATOR_CATEGORY(_first));
    }
    template <typename InputIterator>
    void _assign_dispatch_aux(InputIterator _first, InputIterator _last,
                              input_iterator_tag);
    template <typename ForwardIterator>
    void _assign_dispatch_aux(ForwardIterator _first, ForwardIterator _last,
                              forward_iterator_tag);

    void _insert_aux(const_iterator _pos, const T& _value);
    void _fill_insert(const_iterator _pos, size_type _count, const T& _value);

    template <typename Integer>
    void _insert_dispatch(const_iterator _pos, Integer _count, Integer _value,
                          true_type)
    {
        _fill_insert(_pos, static_cast<size_type>(_count),
                     static_cast<T>(_value));
    }
    template <typename InputIterator>
    void _insert_dispatch(const_iterator _pos, InputIterator _first,
                          InputIterator _last, false_type)
    {
        _range_insert(_pos, _first, _last, _ITERATOR_CATEGORY(_first));
    }
    template <typename InputIterator>
    void _range_insert(const_iterator _pos, InputIterator _first,
                       InputIterator _last, input_iterator_tag);
    template <typename ForwardIterator>
    void _range_insert(const_iterator _pos,ForwardIterator _first,
                       ForwardIterator _last, forward_iterator_tag);
    template <typename... Args>
    void _emplace_aux(const_iterator _pos, Args&&... args);
};


template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type _new_cap)
{
    if(max_size() < _new_cap)
        throw std::length_error("vector length error");
    if(capacity() < _new_cap)
    {
        const size_type old_size = size();
        iterator temp = _allocate_and_copy(_new_cap, begin(), end());
        wt::destroy(m_start_, m_finish_);
        _deallocate(m_start_, m_end_of_storage_ - m_start_);
        m_start_ = temp.m_ptr_;
        m_finish_ = m_start_ + old_size;
        m_end_of_storage_ = m_start_ + _new_cap;
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>& 
vector<T, Allocator>::operator=(const vector<T, Allocator>& other)
{
    if(!(this == &other))
    {
        const size_type other_size = other.size();
        if(other_size > capacity())
        {
            iterator temp = _allocate_and_copy(other_size, other.begin(), other.end());
            wt::destroy(m_start_, m_finish_);
            _deallocate(m_start_, m_end_of_storage_ - m_start_);
            m_start_ = temp.m_ptr_;
            m_end_of_storage_ = m_start_ + other_size;
        }
        else if(other_size < size())
        {
            iterator new_finish = copy(other.begin(), other.end(), begin());
            wt::destroy(new_finish.m_ptr_, m_finish_);
        }
        else
        {
            wt::copy(other.begin(), other.begin() + size(), begin());
            wt::uninitialized_copy(other.begin() + size(), other.end(), end());
        }
        m_finish_ = m_start_ + other.size();
    }
    return *this;
}

//  protected auxiliary member functions' implementation
template <typename T, typename Allocator>
void vector<T, Allocator>::_fill_assign(size_type _count, const T& _value)
{
    if(_count > capacity())
    {
        vector<T, Allocator> temp(_count, _value);
        this->swap(temp);
    }
    else if(_count > size())
    {
        fill(begin(), end(), _value);
        m_finish_ = wt::uninitialized_fill_n(m_finish_, _count - size(), _value);
    }
    else
    {
        erase(fill_n(begin(), _count, _value), end());
    }
}

template <typename T, typename Allocator>
template <typename InputIterator>
void vector<T, Allocator>::_assign_dispatch_aux(InputIterator _first,
                                                InputIterator _last,
                                                input_iterator_tag)
{
    iterator cur_pos = begin();
    for(; _first != _last && cur_pos != end(); ++_first, ++cur_pos)
    {
        *cur_pos = *_first;
    }
    if(_first == _last)
        erase(cur_pos, end());
    if(cur_pos == end())
        insert(end(), _first, _last);
}

template <typename T, typename Allocator>
template <typename ForwardIterator>
void vector<T, Allocator>::_assign_dispatch_aux(ForwardIterator _first,
                                                ForwardIterator _last,
                                                forward_iterator_tag)
{
    auto _count = static_cast<size_type>(wt::distance(_first, _last));
    if(_count > capacity())
    {
        pointer temp = _allocate(_count);
        wt::uninitialized_copy(_first, _last, temp);
        wt::destroy(m_start_, m_finish_);
        _deallocate(m_start_, m_end_of_storage_ - m_start_);
        m_start_ = temp;
        m_end_of_storage_ = m_finish_ = m_start_ + _count;
    }
    else if(_count < size())
    {
        erase(copy(_first, _last, begin()), end());
    }
    else
    {
        wt::copy(_first, _first + size(), begin());
        m_finish_ = wt::uninitialized_copy(_first + size(), _last, m_finish_);
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::_insert_aux(const_iterator _pos, const T& _value)
{
    if(m_finish_ != m_end_of_storage_)
    {
        wt::construct(m_finish_, *(m_finish_ - 1));
        ++m_finish_;
        wt::copy_backward(_pos.m_ptr_, m_finish_ - 2, m_finish_ - 1);
        *(_pos.m_ptr_) = _value;
    }
    else
    {
        const size_type old_size = size();
        const size_type length = old_size == 0 ? 1 : 2 * old_size;
        pointer new_start = _allocate(length);
        pointer new_finish = new_start;
        try {
            new_finish = wt::uninitialized_copy(m_start_, _pos.m_ptr_, new_start);
            wt::construct(new_finish, _value);
            ++new_finish;
            new_finish = wt::uninitialized_copy(_pos.m_ptr_, m_finish_, new_finish);
        }
        catch(...) {
            wt::destroy(new_start, new_finish);
            _deallocate(new_start, length);
            throw;
        }
        wt::destroy(m_start_, m_finish_);
        _deallocate(m_start_, m_end_of_storage_ - m_start_);
        m_start_ = new_start;
        m_finish_ = new_finish;
        m_end_of_storage_ = m_start_ + length;
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::_fill_insert(const_iterator _pos, size_type _count,
                                        const T& _value)
{
    if(_count != 0)
    {
        if(size_type(m_end_of_storage_ - m_finish_) >= _count)
        {
            const size_type elems_after_pos = m_finish_ - _pos.m_ptr_;
            pointer old_finish = m_finish_;
            if(elems_after_pos > _count)
            {
                wt::uninitialized_copy(old_finish - _count, old_finish, m_finish_);
                m_finish_ += _count;
                wt::copy_backward(_pos.m_ptr_, old_finish - _count, old_finish);
                wt::fill(_pos.m_ptr_, _pos.m_ptr_ + _count, _value);
            }
            else
            {
                wt::uninitialized_fill_n(old_finish, _count - elems_after_pos, _value);
                m_finish_ += _count - elems_after_pos;
                wt::uninitialized_copy(_pos.m_ptr_, old_finish, m_finish_);
                m_finish_ += elems_after_pos;
                wt::fill(_pos.m_ptr_, old_finish, _value);
            }
        }
        else
        {
            const size_type old_size = size();
            const size_type length = old_size + wt::max(old_size, _count);
            pointer new_start = _allocate(length);
            pointer new_finish = new_start;
            try {
                new_finish = wt::uninitialized_copy(m_start_, _pos.m_ptr_, new_start);
                new_finish = wt::uninitialized_fill_n(new_finish, _count, _value);
                new_finish = wt::uninitialized_copy(_pos.m_ptr_, m_finish_, new_finish);
            }
            catch(...) {
                wt::destroy(new_start, new_finish);
                _deallocate(new_start, length);
                throw;
            }
            wt::destroy(m_start_, m_finish_);
            _deallocate(m_start_, m_end_of_storage_ - m_start_);
            m_start_ = new_start;
            m_finish_ = new_finish;
            m_end_of_storage_ = m_start_ + length;
        }
    }
}

template <typename T, typename Allocator>
template <typename InputIterator>
void vector<T, Allocator>::_range_insert(const_iterator _pos, InputIterator _first,
                                         InputIterator _last, input_iterator_tag)
{
    for(; _first != _last; ++_first)
    {
        _pos = insert(_pos, *_first);
        ++_pos;
    }
}

template <typename T, typename Allocator>
template <typename ForwardIterator>
void vector<T, Allocator>::_range_insert(const_iterator _pos, ForwardIterator _first,
                                         ForwardIterator _last, forward_iterator_tag)
{
    if(_first != _last)
    {
        size_type _count = wt::distance(_first, _last);
        if(size_type(m_end_of_storage_ - m_finish_) >= _count)
        {
            const size_type elems_after_pos = m_finish_ - _pos.m_ptr_;
            pointer old_finish = m_finish_;
            if(elems_after_pos > _count)
            {
                wt::uninitialized_copy(old_finish - _count, old_finish, m_finish_);
                m_finish_ += _count;
                wt::copy_backward(_pos.m_ptr_, old_finish - _count, old_finish);
                wt::copy(_first, _last, _pos.m_ptr_);
            }
            else
            {
                ForwardIterator mid_insert = _first;
                wt::advance(mid_insert, elems_after_pos);
                wt::uninitialized_copy(mid_insert, _last, old_finish);
                m_finish_ += _count - elems_after_pos;
                wt::uninitialized_copy(_pos.m_ptr_, old_finish, m_finish_);
                m_finish_ += elems_after_pos;
                wt::copy(_first, mid_insert, _pos.m_ptr_);
            }
        }
        else
        {
            const size_type old_size = size();
            const size_type length = old_size + max(old_size, _count);
            pointer new_start = _allocate(length);
            pointer new_finish = new_start;
            try {
                new_finish = wt::uninitialized_copy(m_start_, _pos.m_ptr_, new_start);
                new_finish = wt::uninitialized_copy(_first, _last, new_finish);
                new_finish = wt::uninitialized_copy(_pos.m_ptr_, m_finish_, new_finish);
            }
            catch(...) {
                wt::destroy(new_start, new_finish);
                _deallocate(new_start, length);
            }
            wt::destroy(m_start_, m_finish_);
            _deallocate(m_start_, m_end_of_storage_ - m_start_);
            m_start_ = new_start;
            m_finish_ = new_finish;
            m_end_of_storage_ = m_start_ + length;
        }
    }   
}

template <typename T, typename Allocator>
template <typename... Args>
void vector<T, Allocator>::_emplace_aux(const_iterator _pos, Args&&... args)
{
    if(m_finish_ != m_end_of_storage_)
    {
        wt::construct(m_finish_, *(m_finish_ - 1));
        ++m_finish_;
        wt::copy_backward(_pos.m_ptr_, m_finish_ - 2, m_finish_ - 1);
        wt::destroy(_pos.m_ptr_);
        ::new (static_cast<void*>(_pos.m_ptr_)) T(wt::forward<Args>(args)...);
    }
    else
    {
        const size_type old_size = size();
        const size_type length = old_size == 0 ? 1 : 2 * old_size;
        pointer new_start = _allocate(length);
        pointer new_finish = new_start;
        try {
            new_finish = wt::uninitialized_copy(m_start_, _pos.m_ptr_, new_start);
            ::new (static_cast<void*>(new_finish)) T(wt::forward<Args>(args)...);
            ++new_finish;
            new_finish = wt::uninitialized_copy(_pos.m_ptr_, m_finish_, new_finish);
        }
        catch(...) {
            wt::destroy(new_start, new_finish);
            _deallocate(new_start, length);
            throw;
        }
        wt::destroy(m_start_, m_finish_);
        _deallocate(m_start_, m_end_of_storage_ - m_start_);
        m_start_ = new_start;
        m_finish_ = new_finish;
        m_end_of_storage_ = m_start_ + length;
    }
}

template <typename T, typename Allocator>
inline bool operator==(const vector<T, Allocator>& lhs,
                       const vector<T, Allocator>& rhs)
{
    return lhs.size() == rhs.size() &&
            wt::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Allocator>
inline bool operator<(const vector<T, Allocator>& lhs,
                      const vector<T, Allocator>& rhs)
{
    return wt::lexicographical_compare(lhs.begin(), lhs.end(),
                                       rhs.begin(), rhs.end());
}

template <typename T, typename Allocator>
inline void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs)
{
    lhs.swap(rhs);
}

template <typename T, typename Allocator>
inline bool operator!=(const vector<T, Allocator>& lhs,
                       const vector<T, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Allocator>
inline bool operator<=(const vector<T, Allocator>& lhs,
                       const vector<T, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Allocator>
inline bool operator>(const vector<T, Allocator>& lhs,
                      const vector<T, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Allocator>
inline bool operator>=(const vector<T, Allocator>& lhs,
                       const vector<T, Allocator>& rhs)
{
    return !(lhs < rhs);
}


}  // namespace wt
#endif