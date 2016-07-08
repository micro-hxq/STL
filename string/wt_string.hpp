#ifndef _STL_WT_STRING_HPP_
#define _STL_WT_STRING_HPP_

/**
 *  depend on:
 *            <stdexcept>            
 *            <limits>
 *            "allocator/wt_allocator.hpp"
 *            "allocator/wt_allocator_traits.hpp"
 *            "iterator/wt_iterator_base.hpp"
 *            "iterator/wt_iterator.hpp"
 *            ...
 */

#define MIN_BLOCK_SIZE 8

namespace wt{

// Iterator for basic_string
template <typename T>
class _String_const_iterator : public iterator<random_access_iterator_tag, T> {
public:
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef T*                              _Ptr;

    _String_const_iterator() noexcept : m_ptr_(nullptr) {}
    explicit _String_const_iterator(_Ptr _ptr) noexcept : m_ptr_(_ptr) {}
    _String_const_iterator(const _String_const_iterator<T>& other) noexcept
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
    _String_const_iterator& operator++() noexcept
    {
        ++m_ptr_;
        return *this;
    }
    _String_const_iterator operator++(int) noexcept
    {
        return _String_const_iterator(m_ptr_++);
    }
    _String_const_iterator& operator--() noexcept
    {
        --m_ptr_;
        return *this;
    }
    _String_const_iterator operator--(int) noexcept
    {
        return _String_const_iterator(m_ptr_--);
    }
    _String_const_iterator& operator+=(difference_type _offset) noexcept
    {
        m_ptr_ += _offset;
        return *this;
    }
    _String_const_iterator& operator-=(difference_type _offset) noexcept
    {
        m_ptr_ -= _offset;
        return *this;
    }

    inline friend 
    _String_const_iterator operator+(const _String_const_iterator& _iter, 
                                     difference_type _offset) noexcept
    {
        return _String_const_iterator(_iter.m_ptr_ + _offset);
    }
    inline friend 
    _String_const_iterator operator+(difference_type _offset,
                                 const _String_const_iterator& _iter) noexcept
    {
        return operator+(_iter, _offset);
    }
    inline friend 
    _String_const_iterator operator-(const _String_const_iterator& _iter,
                                     difference_type _offset) noexcept
    {
        return _String_const_iterator(_iter.m_ptr_ - _offset);
    }
    inline friend 
    _String_const_iterator operator-(difference_type _offset,
                                const _String_const_iterator& _iter) noexcept
    {
        return operator-(_iter, _offset);
    }

    inline friend difference_type operator-(const _String_const_iterator& lhs, 
                                    const _String_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ - rhs.m_ptr_;
    }
    inline friend bool operator==(const _String_const_iterator& lhs,
                                  const _String_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ == rhs.m_ptr_;
    }
    inline friend bool operator!=(const _String_const_iterator& lhs,
                                  const _String_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ != rhs.m_ptr_;
    }
    inline friend bool operator<(const _String_const_iterator& lhs,
                                 const _String_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ < rhs.m_ptr_;
    }
    inline friend bool operator<=(const _String_const_iterator& lhs,
                                  const _String_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ <= rhs.m_ptr_;
    }
    inline friend bool operator>(const _String_const_iterator& lhs,
                                 const _String_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ > rhs.m_ptr_;
    }
    inline friend bool operator>=(const _String_const_iterator& lhs,
                                  const _String_const_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ >= rhs.m_ptr_;
    }

    _Ptr m_ptr_;
};

template <typename T>
class _String_iterator : public _String_const_iterator<T> {
public:
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef T*                              pointer;
    typedef T&                              reference;

    typedef _String_const_iterator<T>       _Base;
    using _Base::m_ptr_;

    _String_iterator() noexcept : _Base(nullptr) {}
    explicit _String_iterator(pointer _ptr) noexcept : _Base(_ptr) {}
    _String_iterator(const _String_iterator<T>& other) noexcept
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
    _String_iterator& operator++() noexcept
    {
        ++m_ptr_;
        return *this;
    }
    _String_iterator operator++(int) noexcept
    {
        return _String_iterator(m_ptr_++);
    }
    _String_iterator& operator--() noexcept
    {
        --m_ptr_;
        return *this;
    }
    _String_iterator operator--(int) noexcept
    {
        return  (m_ptr_--);
    }
    _String_iterator& operator+=(difference_type _offset) noexcept
    {
        m_ptr_ += _offset;
        return *this;
    }
    _String_iterator& operator-=(difference_type _offset) noexcept
    {
        m_ptr_ -= _offset;
        return *this;
    }

    inline friend 
    _String_iterator operator+(const _String_iterator& _iter, 
                                     difference_type _offset) noexcept
    {
        return _String_iterator(_iter.m_ptr_ + _offset);
    }
    inline friend 
    _String_iterator operator+(difference_type _offset,
                                 const _String_iterator& _iter) noexcept
    {
        return operator+(_iter, _offset);
    }
    inline friend 
    _String_iterator operator-(const _String_iterator& _iter,
                                     difference_type _offset) noexcept
    {
        return _String_iterator(_iter.m_ptr_ - _offset);
    }
    inline friend 
    _String_iterator operator-(difference_type _offset,
                                const _String_iterator& _iter) noexcept
    {
        return operator-(_iter, _offset);
    }

    inline friend difference_type operator-(const _String_iterator& lhs, 
                                    const _String_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ - rhs.m_ptr_;
    }
    inline friend bool operator==(const _String_iterator& lhs,
                                  const _String_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ == rhs.m_ptr_;
    }
    inline friend bool operator!=(const _String_iterator& lhs,
                                  const _String_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ != rhs.m_ptr_;
    }
    inline friend bool operator<(const _String_iterator& lhs,
                                 const _String_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ < rhs.m_ptr_;
    }
    inline friend bool operator<=(const _String_iterator& lhs,
                                  const _String_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ <= rhs.m_ptr_;
    }
    inline friend bool operator>(const _String_iterator& lhs,
                                 const _String_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ > rhs.m_ptr_;
    }
    inline friend bool operator>=(const _String_iterator& lhs,
                                  const _String_iterator& rhs) noexcept
    {
        return lhs.m_ptr_ >= rhs.m_ptr_;
    }
};

template <typename T, typename Allocator, bool _IsStatic>
class _String_alloc_base {
public:
    typedef typename allocator_traits<Allocator>::allocator_type allocator_type;
    allocator_type get_allocator() const 
    {
        return m_allocator_;
    }

    _String_alloc_base(const allocator_type& _a) : m_allocator_(_a),
    m_start_(nullptr), m_finish_(nullptr), m_end_of_storage_(nullptr) {}

protected:
    T* _allocate(size_t _n)
    {
        return m_allocator_.allocate(_n);
    }
    void _deallocate(T* _p, size_t _n)
    {
        if(_p)
            m_allocator_.deallocate(_p, _n);
    }
 protected:
    allocator_type  m_allocator_;
    T*              m_start_;
    T*              m_finish_;
    T*              m_end_of_storage_;
};

template <typename T, typename Allocator>
class _String_alloc_base<T, Allocator, true> {
public:
    typedef typename allocator_traits<Allocator>::allocator_type allocator_type;
    allocator_type get_allocator() const 
    {
        return allocator_type();
    }
    _String_alloc_base(const allocator_type&)
     : m_start_(nullptr), m_finish_(nullptr), m_end_of_storage_(nullptr) {}
 protected:
    typedef typename _Alloc_traits<T, Allocator>::_Alloc_type   _Alloc_type;
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
class _String_base : public _String_alloc_base<T, Allocator,
                        _Alloc_traits<T, Allocator>::isStatic> {
protected:
    typedef _String_alloc_base<T, Allocator, 
            _Alloc_traits<T, Allocator>::isStatic> _Base;
    using _Base::m_start_;
    using _Base::m_finish_;
    using _Base::m_end_of_storage_;
    using _Base::_allocate;
    using _Base::_deallocate;
public:
    typedef typename _Base::allocator_type      allocator_type;

    void _allocate_block(size_t _n)
    {
        if(_n <= max_size())
        {
            m_start_ = _allocate(_n);
            m_finish_ = m_start_;
            m_end_of_storage_ = m_start_ + _n;
        }
        else
        {
            _throw_length_error();
        }
    }

    void _deallocate_block()
    {
        _deallocate(m_start_, m_end_of_storage_ - m_start_);
    }

    // additional null terminal char
    size_t max_size() const 
    {
        return std::numeric_limits<size_t>::max() / sizeof(T) -1;
    }
    _String_base(const allocator_type& _a) : _Base(_a) {}

    _String_base(const allocator_type& _a, size_t _n) : _Base(_a)
    { _allocate_block(_n); }

    ~_String_base()
    { _deallocate_block(); }

    void _throw_length_error() const;
    void _throw_out_of_range() const;
};

template <typename T, typename Allocator>
void _String_base<T, Allocator>::_throw_length_error() const
{
    throw std::length_error("basic_string");
}

template <typename T, typename Allocator>
void _String_base<T, Allocator>::_throw_out_of_range() const
{
    throw std::out_of_range("basic_string");
}

// Class template basic_string
template <typename CharT, typename Traits, typename Allocator>
class basic_string : private _String_base<CharT, Allocator> {
public:
    typedef Traits                                                traits_type;
    typedef CharT                                                 value_type;
    typedef Allocator                                             allocator_type;
    typedef typename allocator_traits<Allocator>::size_type       size_type;
    typedef typename allocator_traits<Allocator>::difference_type difference_type;
    typedef const value_type&                                     const_reference;
    typedef value_type&                                           reference;
    typedef typename allocator_traits<Allocator>::const_pointer   const_pointer;
    typedef typename allocator_traits<Allocator>::pointer         pointer;
    typedef _String_const_iterator<value_type>                    const_iterator;
    typedef _String_iterator<value_type>                          iterator;
    typedef reverse_iterator<const_iterator>                      const_reverse_iterator;
    typedef reverse_iterator<iterator>                            reverse_iterator;

 protected:
    typedef _String_base<CharT, Allocator> _Base;
    using _Base::_allocate;
    using _Base::_deallocate;
    using _Base::_allocate_block;
    using _Base::_deallocate_block;
    using _Base::_throw_length_error;
    using _Base::_throw_out_of_range;

    using _Base::m_start_;
    using _Base::m_finish_;
    using _Base::m_end_of_storage_;

public:
    static const size_type npos;
    allocator_type get_allocator() const
    {
        return _Base::get_allocator();
    }

    basic_string() : basic_string(allocator_type()) {}
    explicit basic_string(const allocator_type& _a) : _Base(_a, MIN_BLOCK_SIZE)
    {
        _terminate_string();
    }
    basic_string(size_type _count, CharT _c, 
                 const allocator_type& _a = allocator_type())
     : _Base(_a, _count + 1)
    {
        m_finish_ = uninitialized_fill_n(m_start_, _count, _c);
        _terminate_string();
    }
    basic_string(const basic_string& _s, size_type _pos, 
                 const allocator_type& _a = allocator_type())
     : _Base(_a)
    {
        if(_s.size() < _pos)
            _throw_out_of_range();
        else
            _range_initialize(_s.begin() + _pos, _s.end());
    }

    basic_string(const basic_string& _s, size_type _pos, size_type _count,
                 const allocator_type& _a = allocator_type())
     : _Base(_a)
    {
        if(_s.size() < _pos)
            _throw_out_of_range();
        else
            _range_initialize(_s.begin() + _pos,
                          _s.begin() + _pos + min(_count, _s.size() - _pos));
    }

    basic_string(const CharT* _s, size_type _count,
                 const allocator_type& _a = allocator_type())
      : _Base(_a)
    {
        _range_initialize(_s, _s + _count);
    }

    basic_string(const CharT* _s, const allocator_type& _a = allocator_type())
      : _Base(_a)
    {
        _range_initialize(_s, _s + Traits::length(_s));
    }

    template <typename InputIterator>
    basic_string (InputIterator _first, InputIterator _last,
                  const allocator_type& _a = allocator_type())
    : _Base(_a)
    {
        _initialize_dispatch(_first, _last, is_integral<InputIterator>());
    }

    basic_string(const basic_string& other)
     : basic_string(other, other.get_allocator()) {}

    basic_string(const basic_string& other, const allocator_type& _a)
     : _Base(_a)
    {
        _range_initialize(other.begin(), other.end());
    }

    basic_string(basic_string&& other) noexcept : basic_string(other.get_allocator())
    {
        this->swap(other);
    }
    basic_string(basic_string&& other, const allocator_type& _a) noexcept
     : _Base(_a)
    {
        this->swap(other);
    }

    basic_string& operator=(const basic_string& _str)
    {
        if(this != &_str)
        {
            assign(_str.begin(), _str.end());
        }
        return *this;
    }

    basic_string& operator=(basic_string&& _str) noexcept
    {
        if(this != &_str)
        {
            this->swap(_str);
        }
        return *this;
    }

    basic_string& operator=(const CharT* _s)
    {
        return assign(_s, _s + Traits::length(_s));
    }
    basic_string& operator=(CharT _ch)
    {
        return assign(static_cast<size_type>(1), _ch);
    }

    ~basic_string() { destroy(m_start_, m_finish_); }

    basic_string& assign(size_type _count, CharT ch);
    basic_string& assign(const basic_string& _str)
    {
        return assign(_str.begin(), _str.end());
    }
    basic_string& assign(const basic_string& _str, size_type _pos,
                         size_type _count = npos)
    {
        if(_pos > _str.size())
            _throw_out_of_range();
        return assign(_str.begin() + _pos,
                      _str.begin() + _pos + min(_count, _str.size() - _pos));
    }
    basic_string& assign(basic_string&& _str)
    {
        if(this != &_str)
            this->swap(_str);
        return *this;
    }
    basic_string& assign(const CharT* _s, size_type _count)
    {
        return assign(_s, _s + _count);
    }
    basic_string& assign(const CharT* _s)
    {
        return assign(_s, _s + Traits::length(_s));
    }
    template <typename InputIterator>
    basic_string& assign(InputIterator _first, InputIterator _last)
    {
        return _assign_dispatch(_first, _last, is_integral<InputIterator>());
    }

    /**
     *  Iteartor operations
     */
    iterator begin() noexcept
    {   return iterator(m_start_);  }
    const_iterator begin() const noexcept
    {   return const_iterator(m_start_);  }
    const_iterator cbegin() const noexcept
    {   return const_iterator(m_start_);    }

    iterator end() noexcept
    {   return iterator(m_finish_); }
    const_iterator end() const noexcept
    {   return const_iterator(m_finish_);   }
    const_iterator cend() const noexcept
    {   return const_iterator(m_finish_);   }

    reverse_iterator rbegin() noexcept
    {   return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept
    {   return const_reverse_iterator(end());   }
    const_reverse_iterator crbegin() const noexcept
    {   return const_reverse_iterator(cend());  }

    reverse_iterator rend() noexcept
    {   return reverse_iterator(begin());   }
    const_reverse_iterator rend() const noexcept
    {   return const_reverse_iterator(begin());     }
    const_reverse_iterator crend() const noexcept
    {   return const_reverse_iterator(cbegin());    }

    /**
     *  Element access 
     */
    reference at(size_type _pos)
    {
        if(_pos >= size())
            _throw_out_of_range();
        return *(m_start_ + _pos);
    }
    const_reference at(size_type _pos) const
    {
        if(_pos >= size())
            _throw_out_of_range();
        return *(m_start_ + _pos);
    }

    reference operator[](size_type _pos)
    {
        return *(m_start_ + _pos);
    }
    const_reference operator[](size_type _pos) const
    {
        return *(m_start_ + _pos);
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
        return *(m_finish_ -1);
    }
    const_reference back() const
    {
        return *(m_finish_ -1);
    }

    const_pointer data() const noexcept
    {
        return m_start_;
    }
    pointer data() noexcept
    {
        return m_start_;
    }

    const_pointer c_str() const
    {
        return m_start_;
    }

    /**
     *  Capacity operations
     */
    bool empty() const noexcept
    {
        return m_finish_ == m_start_;
    }
    size_type size() const noexcept
    {
        return m_finish_ - m_start_;
    }
    size_type length() const noexcept
    {
        return size();
    }
    size_type max_size() const noexcept
    {
        return _Base::max_size();
    }
    void reserve(size_type _new_cap = 0);
    size_type capacity() const noexcept
    {
        return (m_end_of_storage_ - m_start_) - 1;
    }
    void shrink_to_fit()
    {
        if(m_finish_ + 1 != m_end_of_storage_)
        {
            _deallocate(m_finish_ + 1, m_end_of_storage_ - m_finish_ -1);
            m_end_of_storage_ = m_finish_ + 1;
        }
    }

    /**
     *  Modified Operations
     */
    void clear()
    {
        if(!empty())
        {
            destroy(m_start_ + 1, m_finish_+1);
            Traits::assign(*m_start_, _null());
            m_finish_ = m_start_;
        }
    }

    basic_string& insert(size_type _pos, size_type _count, CharT _ch)
    {
        if(_pos >size())
            _throw_out_of_range();
        if(_count > max_size() || size() + _count > max_size())
            _throw_length_error();
        insert(begin() + _pos, _count, _ch);
        return *this;
    }
    basic_string& insert(size_type _pos, const CharT* _s)
    {
        if(_pos > size())
            _throw_out_of_range();
        const size_type count = Traits::length(_s);
        if(size() + count > max_size() || count > max_size())
            _throw_length_error();
        insert(begin() + _pos, _s, _s + count);
        return *this;
    }
    basic_string& insert(size_type _pos, const CharT* _s, size_type _count)
    {
        if(_pos > size())
            _throw_out_of_range();
        if(_count + size() > max_size() || _count > max_size())
            _throw_length_error();
        insert(begin() + _pos, _s, _s + _count);
        return *this;
    }
    basic_string& insert(size_type _pos, const basic_string& _str)
    {
        if(_pos > size())
            _throw_out_of_range();
        const size_type count = _str.size();
        if(size() + count > max_size() || count > max_size())
            _throw_length_error();
        insert(begin() + _pos, _str.begin(), _str.end());
        return *this;
    }
    basic_string& insert(size_type _pos, const basic_string& _str, 
                         size_type _pos2, size_type _count = npos)
    {
        if(_pos > size() || _pos2 > _str.size())
            _throw_out_of_range();
        const size_type count = min(_str.size() - _pos, _count);
        if(size() + count > max_size())
            _throw_length_error();
        insert(begin() + _pos, _str.begin() + _pos, _str.begin() + _pos + count);
        return *this;
    }
    iterator insert(const_iterator _pos, CharT _ch)
    {
        if(_pos.m_ptr_ == m_finish_)
            push_back(_ch);
        else
            _insert_aux(_pos, _ch);
        return iterator(_pos.m_ptr_);
    }
    iterator insert(const_iterator _pos, size_type _count, CharT _ch);
    template <typename InputIterator>
    iterator insert(const_iterator _pos, InputIterator _first, InputIterator _last)
    {
        _insert_dispatch(_pos, _first, _last, is_integral<InputIterator>());
        return iterator(_pos.m_ptr_);
    }

    basic_string& erase(size_type _pos = 0, size_type _count = npos)
    {
        if(_pos > size())
            _throw_out_of_range();
        erase(begin() + _pos, begin() + _pos + min(_count, size() - _pos));
        return *this;
    }
    iterator erase(const_iterator _pos)
    {
        Traits::move(_pos, _pos + 1, m_finish_ - _pos.m_ptr_);
        destroy(m_finish_);
        --m_finish_;
        return iterator(_pos.m_ptr_);
    }
    iterator erase(const_iterator _first, const_iterator _last)
    {
        if(_first != _last)
        {
            Traits::move(_first.m_ptr_, _last.m_ptr_, m_finish_ - _last.m_ptr_ + 1);
            pointer new_finish = m_finish_ - (_last - _first);
            destroy(new_finish + 1, m_finish_ + 1);
            m_finish_ = new_finish;
        }
        return iterator(_first.m_ptr_);
    }

    void push_back(CharT ch)
    {
        if(m_finish_ + 1 == m_end_of_storage_)
        {
            reserve(size() + max(size(), static_cast<size_type>(1)));
        }
        _construct_null(m_finish_ + 1);
        Traits::assign(*m_finish_, ch);
        ++m_finish_;
    }

    void pop_back()
    {
        Traits::assign(*(m_finish_ -1), _null());
        destroy(m_finish_);
        --m_finish_;
    }

    basic_string& append(size_type _count, CharT ch);
    basic_string& append(const basic_string& _str)
    {
        return append(_str.begin(), _str.end());
    }
    basic_string& append(const basic_string& _str, size_type _pos,
                         size_type _count = npos)
    {
        if(_pos > _str.size())
            _throw_out_of_range();
        return append(_str.begin() + _pos, 
                      _str.begin() + _pos + min(_count, _str.size() - _pos));
    }
    basic_string& append(const CharT* _s, size_type _count)
    {
        return append(_s, _s + _count);
    }
    basic_string& append(const CharT* _s)
    {
        return append(_s, _s + Traits::length(_s));
    }
    template <typename InputIterator>
    basic_string& append(InputIterator _first, InputIterator _last)
    {
        return _append_dispatch(_first, _last, is_integral<InputIterator>());
    }

    basic_string& operator+=(const basic_string& _str)
    {
        append(_str.begin(), _str.end());
        return *this;
    }
    basic_string& operator+=(CharT _ch)
    {
        push_back(_ch);
        return *this;
    }
    basic_string& operator+=(const CharT* _s)
    {
        append(_s);
        return *this;
    }

    int compare(const basic_string& _str) const
    {
        return _compare_str(m_start_, m_finish_, _str.m_start_, _str.m_finish_);
    }
    int compare(size_type _pos1, size_type _count1, const basic_string& _str) const
    {
        if(_pos1 >= size())
            _throw_out_of_range();
        const auto len = wt::min(_count1, size() - _pos1);
        return _compare_str(m_start_ + _pos1, m_start_ + _pos1 + len,
                            _str.m_start_, _str.m_finish_);
    }
    int compare(size_type _pos1, size_type _count1, const basic_string& _str,
                size_type _pos2, size_type _count2 = npos) const
    {
        if(_pos1 >= size() || _pos2 >= _str.size())
            _throw_out_of_range();
        return _compare_str(m_start_ + _pos1,
                m_start_ + _pos1 + wt::min(_count1, size() - _pos1),
                _str.m_start_ + _pos2,
                _str.m_start_ + _pos2 + wt::min(_count2, _str.size() - _pos2));
    }
    int compare(const CharT* _s) const
    {
        return _compare_str(m_start_, m_finish_, _s, _s + Traits::length(_s));
    }
    int compare(size_type _pos, size_type _count, const CharT* _s) const
    {
        if(_pos >= size())
            _throw_out_of_range();
        return _compare_str(m_start_ + _pos,
                            m_start_ + _pos + wt::min(_count, size() - _pos));
    }
    int compare(size_type _pos1, size_type _count1, 
                const CharT* _s, size_type _count2) const
    {
        if(_pos1 >= size())
            _throw_out_of_range();
        return _compare_str(m_start_ + _pos1,
                            m_start_ + _pos1 + wt::min(_count1, size() - _pos1),
                            _s,
                            _s + wt::min(_count2, Traits::length(_s)));
    }

    basic_string& replace(size_type _pos, size_type _count,
                          const basic_string& _str)
    {
        if(_pos > size())
            _throw_length_error();
        const auto len2 = _str.size();
        if(size() - _count > max_size() - len2)
            _throw_out_of_range();
        return replace(begin() + _pos,
                       begin() + _pos + wt::min(_count, size() - _pos),
                       _str.begin(), _str.end());
    }
    basic_string& replace(const_iterator _first1, const_iterator _last1,
                          const basic_string& _str)
    {
        return replace(_first1, _last1, _str.begin(), _str.end());
    }
    basic_string& replace(size_type _pos1, size_type _count1,
                          const basic_string& _str,
                          size_type _pos2, size_type _count2 = npos)
    {
        if(_pos1 > size() || _pos2 > _str.size())
            _throw_out_of_range();
        if(size() - _count1 > max_size() - _count2)
            _throw_length_error();
        return replace(begin() + _pos1,
                       begin() + _pos1 + wt::min(_count1,size() - _pos1),
               _str.begin() + _pos2,
               _str.begin() + _pos2 + wt::min(_count2, _str.size() - _pos2));
    }
    template <typename InputIterator>
    basic_string& replace(const_iterator _first1, const_iterator _last1,
                          InputIterator _first2, InputIterator _last2)
    {
        return _replace_dispatch(_first1, _last1, _first2, _last2,
                                 is_integral<InputIterator>());
    }
    basic_string& replace(size_type _pos, size_type _count1, 
                          const CharT* _cstr, size_type _count2)
    {
        if(_pos > size())
            _throw_out_of_range();
        return replace(begin() + _pos,
                       begin() + _pos + wt::min(_count1, size() - _pos),
                       _cstr, _cstr + wt::min(_count2, Traits::length(_cstr)));
    }
    basic_string& replace(const_iterator _first, const_iterator _last,
                          const CharT* _cstr, size_type _count)
    {
        return replace(_first, _last, 
                       _cstr, _cstr + wt::min(_count, Traits::length(_cstr)));
    }
    basic_string& replace(size_type _pos, size_type _count, const CharT* _cstr)
    {
        if(_pos > size())
            _throw_out_of_range();
        return replace(begin() + _pos, begin() + wt::min(_count, size() - _pos),
                       _cstr, _cstr + Traits::length(_cstr));
    }
    basic_string& replace(const_iterator _first, const_iterator _last,
                          const CharT* _cstr)
    {
        return replace(_first, _last, _cstr, _cstr + Traits::length(_cstr));
    }
    basic_string& replace(size_type _pos, size_type _count1,
                          size_type _count2, CharT _ch)
    {
        if(_pos > size())
            _throw_out_of_range();
        if(size() - _count1 > max_size() - _count2)
            _throw_length_error();
        return replace(begin() + _pos,
                       begin() + _pos + wt::min(_count1, size() - _pos),
                       _count2, _ch);
    }
    basic_string& replace(const_iterator _first, const_iterator _last,
                          size_type _count2, CharT _ch);

    basic_string& substr(size_type _pos = 0, size_type _count = npos) const
    {
        if(_pos > size())
            _throw_out_of_range();
        return basic_string(begin() + _pos,
                            begin() + _pos + wt::min(_count, size() - _pos));
    }

    /**
     * copy a substring [_pos, _pos + _count) to _dest,
     * the result string is not null-teriminated.
     * Note : this member function differs from STL's.
     * @param  _dest  [description]
     * @param  _pos   [description]
     * @param  _count [description]
     * @return        [description]
     */
    size_type copy(CharT* _dest, size_type _pos = 0,
                   size_type _count = npos) const
    {
        if(_pos > size())
            _throw_out_of_range();
        const auto len = wt::min(_count, size() - _pos);
        Traits::copy(_dest, m_start_ + _pos, len);
        return len;
    }

    void resize(size_type _count)
    {
        resize(_count, _null());
    }
    void resize(size_type _count, CharT _ch)
    {
        if(_count > max_size())
            _throw_length_error();
        if(_count <= size())
            erase(begin() + _count, end());
        else
            append(_count - size(), _ch);
    }

    void swap(basic_string& other) noexcept
    {
        wt::swap(m_start_, other.m_start_);
        wt::swap(m_finish_, other.m_finish_);
        wt::swap(m_end_of_storage_, other.m_end_of_storage_);
    }

    /**
     *  Search Operations
     */

    size_type find(const basic_string& _str, size_type _pos = 0) const
    {
        return find(_str.m_start_, _pos, _str.size());
    }
    size_type find(const CharT* _cstr, size_type _pos = 0) const
    {
        return find(_cstr, _pos, Traits::length(_cstr));
    }
    size_type find(const CharT* _cstr, size_type _pos, size_type _count) const;
    size_type find(CharT _ch, size_type _pos = 0) const;

    size_type rfind(const basic_string& _str, size_type _pos = npos) const
    {
        return rfind(_str.m_start_, _pos, _str.size());
    }
    size_type rfind(const CharT* _cstr, size_type _pos = npos) const
    {
        return rfind(_cstr, _pos, Traits::length(_cstr));
    }
    size_type rfind(const CharT* _cstr, size_type _pos, size_type _count) const;
    size_type rfind(CharT ch, size_type pos = npos) const;

    size_type find_first_of(const basic_string& _str, size_type _pos = 0) const
    {
        return find_first_of(_str.m_start_, _pos, _str.size());
    }
    size_type find_first_of(const CharT* _cstr, size_type _pos,
                            size_type _count) const;
    size_type find_first_of(const CharT* _cstr, size_type _pos = 0) const
    {
        return find_first_of(_cstr, _pos, Traits::length(_cstr));
    }
    size_type find_first_of(CharT _ch, size_type _pos = 0) const
    {
        return find(_ch, _pos);
    }

    size_type find_first_not_of(const basic_string& _str,
                                size_type _pos = 0) const
    {
        return find_first_not_of(_str.m_start_, _pos, _str.size());
    }
    size_type find_first_not_of(const CharT* _cstr, size_type _pos,
                                size_type _count) const;
    size_type find_first_not_of(const CharT* _cstr, size_type _pos = 0) const
    {
        return find_first_not_of(_cstr, _pos, Traits::length(_cstr));
    }
    size_type find_first_not_of(CharT _ch, size_type _pos = 0) const;

    size_type find_last_of(const basic_string& _str, size_type _pos = npos) const
    {
        return find_last_of(_str.m_start_, _pos, _str.size());
    }
    size_type find_last_of(const CharT* _cstr, size_type _pos,
                           size_type _count) const;
    size_type find_last_of(const CharT* _cstr, size_type _pos = npos) const
    {
        return find_last_of(_cstr, _pos, Traits::length(_cstr));
    }
    size_type find_last_of(CharT _ch, size_type _pos = npos) const
    {
        return rfind(_ch, _pos);
    }

    size_type find_last_not_of(const basic_string& _str,
                               size_type _pos = npos) const
    {
        return find_last_not_of(_str.m_start_, _pos, _str.size());
    }
    size_type find_last_not_of(const CharT* _cstr, size_type _pos,
                               size_type _count) const;
    size_type find_last_not_of(const CharT* _cstr, size_type _pos = npos) const
    {
        return find_last_not_of(_cstr, _pos, Traits::length(_cstr));
    }
    size_type find_last_not_of(CharT _ch, size_type _pos = npos) const;
private:
    void _construct_null(CharT* _p)
    {
        construct(_p);
    }
    static CharT _null()
    {
        return CharT();
    } 
    void _terminate_string() 
    {
        try {
            _construct_null(m_finish_);
        }
        catch(...) {
            destroy(m_start_, m_finish_);
            throw;
        }
    }

    template <typename InputIterator>
    void _copy_str(InputIterator _first, InputIterator _last, const_iterator _result)
    {
        for(; _first != _last; ++_first, ++_result)
        {
            Traits::assign(*(_result.m_ptr_), *_first);
        }
    }
    void _copy_str(const CharT* _first, const CharT* _last, CharT* _result)
    {
        Traits::copy(_result, _first, _last - _first);
    }

    static int _compare_str(const CharT* _first1, const CharT* _last1,
                            const CharT* _first2, const CharT* _last2)
    {
        const auto n1 = _last1 - _first1;
        const auto n2 = _last2 - _first2;
        const auto result = Traits::compare(_first1, _first2, wt::min(n1, n2));
        return result != 0 ? result : (n1 > n2 ? 1 : (n1 < n2 ? -1 : 0));
    }

    template <typename InputIterator>
    void _range_initialize(InputIterator _first, InputIterator _last,
                           input_iterator_tag)
    {
        _allocate_block(MIN_BLOCK_SIZE);
        _construct_null(m_finish_); // ???
        try {
            append(_first, _last); // TODO
        }
        catch(...) {
            destroy(m_start_, m_finish_ + 1);
            throw;
        }
    }
    template <typename ForwardIterator>
    void _range_initialize(ForwardIterator _first, ForwardIterator _last,
                           forward_iterator_tag)
    {
        difference_type n = distance(_first, _last);
        _allocate_block(n + 1);
        m_finish_ = uninitialized_copy(_first, _last, m_start_);
        _terminate_string();
    }

    template <typename InputIterator>
    void _range_initialize(InputIterator _first, InputIterator _last)
    {
        _range_initialize(_first, _last, _ITERATOR_CATEGORY(_first));
    }

    template <typename InputIterator>
    void _initialize_dispatch(InputIterator _first, InputIterator _last,
                              false_type)
    {
        _range_initialize(_first, _last);
    }

    template <typename Integer>
    void _initialize_dispatch(Integer _count, Integer _x, true_type)
    {
        _allocate_block(_count + 1);
        m_finish_ = uninitialized_fill_n(m_start_, _count, _x);
        _terminate_string();
    }

    template <typename Integer>
    basic_string& _assign_dispatch(Integer _count, Integer _ch, true_type)
    {
        return assign(static_cast<size_type>(_count),
                      static_cast<CharT>(_ch));
    }
    template <typename InputIterator>
    basic_string& _assign_dispatch(InputIterator _first, InputIterator _last,
                                   false_type);

    template <typename Integer>
    basic_string& _append_dispatch(Integer _count, Integer _ch, true_type)
    {
        return append(static_cast<size_type>(_count), static_cast<CharT>(_ch));
    }

    template <typename InputIterator>
    basic_string& _append_dispatch(InputIterator _first, InputIterator _last,
                                   false_type)
    {
        return _append_aux(_first, _last, _ITERATOR_CATEGORY(_first));
    }
    template <typename InputIterator>
    basic_string& _append_aux(InputIterator _first, InputIterator _last, 
                              input_iterator_tag)
    {
        while(_first != _last)
        {
            push_back(*_first);
            ++_first;
        }
        return *this;
    }

    template <typename ForwardIterator>
    basic_string& _append_aux(ForwardIterator _first, ForwardIterator _last,
                              forward_iterator_tag);

    iterator _insert_aux(const_iterator _pos, CharT _ch);
    template <typename Integer>
    void _insert_dispatch(const_iterator _pos, Integer _count, Integer _ch,
                          true_type)
    {
        insert(_pos, static_cast<size_type>(_count), static_cast<CharT>(_ch));
    }
    template <typename InputIterator>
    void _insert_dispatch(const_iterator _pos, InputIterator _first,
                          InputIterator _last, false_type)
    {
        _insert_aux(_pos, _first, _last, _ITERATOR_CATEGORY(_first));
    }
    template <typename InputIterator>
    void _insert_aux(const_iterator _pos, InputIterator _first,
                     InputIterator _last, input_iterator_tag)
    {
        for(; _first != _last; ++_first)
        {
            _pos = insert(_pos, *_first);
            ++_pos;
        }
    }
    template <typename ForwardIterator>
    void _insert_aux(const_iterator _pos, ForwardIterator _first,
                     ForwardIterator _last, forward_iterator_tag);

    template <typename Integer>
    basic_string& _replace_dispatch(const_iterator _first,
                                    const_iterator _last,
                                    Integer _count, Integer _ch, true_type)
    {
        return replace(_first, _last, static_cast<size_type>(_count),
                       static_cast<size_type>(_ch));
    }
    template <typename InputIterator>
    basic_string& _replace_dispatch(const_iterator _first1,
                                    const_iterator _last1,
                                    InputIterator _first2,
                                    InputIterator _last2,
                                    false_type)
    {
        return _replace_aux(_first1, _last1, _first2, _last2,
                            _ITERATOR_CATEGORY(_first2));
    }
    template <typename InputIterator>
    basic_string& _replace_aux(const_iterator _first1, const_iterator _last1,
                               InputIterator _first2, InputIterator _last2,
                               input_iterator_tag);
    template <typename ForwardIterator>
    basic_string& _replace_aux(const_iterator _first1, const_iterator _last1,
                               ForwardIterator _first2, ForwardIterator _last2,
                               forward_iterator_tag);



};

//  definition of npos
template <typename CharT, typename Traits, typename Allocator>
const typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::npos 
 = static_cast<basic_string<CharT, Traits, Allocator>::size_type>(-1);

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>&
basic_string<CharT, Traits, Allocator>::assign(size_type _count, CharT _ch)
{
    if(_count > size())
    {
        Traits::assign(m_start_, size(), _ch);
        append(_count - size(), _ch);
    }
    else
    {
        Traits::assign(m_start_, _count, _ch);
        erase(begin() + _count, end());
    }
    return *this;
}

template <typename CharT, typename Traits, typename Allocator>
template <typename InputIterator>
basic_string<CharT, Traits, Allocator>&
basic_string<CharT, Traits, Allocator>::_assign_dispatch(InputIterator _first,
                                                         InputIterator _last,
                                                         false_type)
{
    iterator cur(m_start_);
    while(_first != _last && cur.m_ptr_ != m_finish_)
    {
        Traits::assign(*cur, *_first);
        ++cur;
        ++_first;
    }
    if(_first == _last)
        erase(cur, end());
    else
        append(_first, _last);
    return *this;
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::iterator
basic_string<CharT, Traits, Allocator>::insert(const_iterator _pos,
                                               size_type _count,
                                               CharT _ch)
{
    if(_count > 0)
    {
        if(static_cast<size_type>(m_end_of_storage_ - m_finish_) > _count + 1)
        {
            const size_type elem_after = m_finish_ - _pos.m_ptr_;
            if(elem_after >= _count)
            {
                uninitialized_copy(m_finish_ - _count + 1, m_finish_ + 1, m_finish_ + 1);
                m_finish_ += _count;
                Traits::move(_pos.m_ptr_ + _count, _pos.m_ptr_, elem_after - _count + 1);
                Traits::assign(_pos.m_ptr_, _count, _ch);
            }
            else
            {
                try {
                    uninitialized_fill_n(m_finish_ + 1, _count - elem_after - 1, _ch);
                    uninitialized_copy(_pos.m_ptr_, m_finish_ + 1, _pos.m_ptr_  + _count);
                }
                catch(...) {
                    destroy(m_finish_ + 1, m_finish_ + _count);
                    throw;
                }
                Traits::assign(_pos.m_ptr_, elem_after + 1, _ch);
                m_finish_ += _count;
            }
        }
        else
        {
            const size_type len = size() + max(size(), _count) + 1;
            pointer new_start = _allocate(len);
            pointer new_finish = new_start;
            try {
                new_finish = uninitialized_copy(m_start_, _pos.m_ptr_, new_finish);
                new_finish = uninitialized_fill_n(new_finish, _count, _ch);
                new_finish = uninitialized_copy(_pos.m_ptr_, m_finish_, new_finish);
                _construct_null(new_finish);
            }
            catch(...) {
                destroy(new_start, new_finish + 1);
                _deallocate(new_start, len);
                throw;
            }
            _deallocate_block();
            m_start_ = new_start;
            m_finish_ = new_finish;
            m_end_of_storage_ = m_start_ + len;
        }
    }
    return iterator(_pos.m_ptr_);
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::iterator
basic_string<CharT, Traits, Allocator>::_insert_aux(const_iterator _pos, CharT _ch)
{
    return iterator(_pos.m_ptr_);
}

template <typename CharT, typename Traits, typename Allocator>
template <typename ForwardIterator>
void basic_string<CharT, Traits, Allocator>::_insert_aux(const_iterator _pos,
                                                         ForwardIterator _first,
                                                         ForwardIterator _last,
                                                         forward_iterator_tag)
{
    if(_first != _last)
    {
        const size_type count = distance(_first, _last);
        if(static_cast<size_type>(m_end_of_storage_ - m_finish_) > count + 1)
        {
            const size_type elem_after = m_finish_ - _pos.m_ptr_;
            if(elem_after >= count)
            {
                uninitialized_copy(m_finish_ - count + 1, m_finish_ + 1,
                                   m_finish_ + 1);
                Traits::move(_pos.m_ptr_ + count, _pos.m_ptr_, elem_after - count + 1);
                _copy_str(_first, _last, _pos);
                m_finish_ += count;
            }
            else
            {
                ForwardIterator mid = _first;
                advance(mid, elem_after + 1);
                uninitialized_copy(_pos.m_ptr_, m_finish_ + 1, _pos.m_ptr_ + count);
                try {
                    uninitialized_copy(mid, _last, m_finish_ + 1);
                }
                catch(...) {
                    destroy(m_finish_ + 1, m_finish_ + count + 1);
                    throw;
                }
                _copy_str(_first, mid, _pos.m_ptr_);
                m_finish_ += count;
            }
        }
        else
        {
            const size_type len = size() + max(size(), count) + 1;
            pointer new_start = _allocate(len);
            pointer new_finish = new_start;
            try {
                new_finish = uninitialized_copy(m_start_, _pos.m_ptr_, new_finish);
                new_finish = uninitialized_copy(_first, _last, new_finish);
                new_finish = uninitialized_copy(_pos.m_ptr_, m_finish_, new_finish);
                _construct_null(new_finish);
            }
            catch(...) {
                destroy(new_start, new_finish + 1);
                _deallocate(new_start, len);
                throw;
            }
            destroy(m_start_, m_finish_ + 1);
            _deallocate_block();
            m_start_ = new_start;
            m_finish_ = new_finish;
            m_end_of_storage_ = new_start + len;
        }
    }
}

template <typename CharT, typename Traits, typename Allocator>
void basic_string<CharT, Traits, Allocator>::reserve(size_type _new_cap)
{
    if(max_size() < _new_cap)
        _throw_length_error();
    if(capacity() < _new_cap)
    {
        ++_new_cap;
        pointer new_start = _allocate(_new_cap);
        pointer new_finish = new_start;
        try {
            new_finish = uninitialized_copy(m_start_, m_finish_, new_start);
            _construct_null(new_finish);
        }
        catch(...) {
            destroy(new_start, new_finish + 1);
            _deallocate(new_start, _new_cap);
            throw;
        }
        destroy(m_start_, m_finish_ + 1);
        _deallocate_block();
        m_start_ = new_start;
        m_finish_ = new_finish;
        m_end_of_storage_ = m_start_ + _new_cap;
    }
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>&
basic_string<CharT, Traits, Allocator>::append(size_type _count, CharT _ch)
{
    if(size() + _count > max_size() || _count > max_size())
        _throw_length_error();
    if(capacity() - size() < _count)
        reserve(size() + max(size(), _count));
    if(_count > 0)
    {
        try {
            uninitialized_fill_n(m_finish_ + 1, _ch, _count - 1);
            _construct_null(m_finish_ + _count);
        }
        catch(...) {
            destroy(m_finish_ + 1, m_finish_ + _count + 1);
            throw;
        }
        Traits::assign(*m_finish_, _ch);
        m_finish_ += _count;
    }
    return *this;
}

template <typename CharT, typename Traits, typename Allocator>
template <typename ForwardIterator>
basic_string<CharT, Traits, Allocator>&
basic_string<CharT, Traits, Allocator>::_append_aux(ForwardIterator _first,
                                                    ForwardIterator _last,
                                                    forward_iterator_tag)
{
    if(_first != _last)
    {
        size_type count = static_cast<size_type>(distance(_first, _last));
        const size_type old_size = size();
        if(count + old_size > max_size() || count > max_size())
            _throw_length_error();
        if(count + old_size > capacity())
        {
            const size_type len = old_size + max(old_size, count);
            pointer new_start = _allocate(len);
            pointer new_finish = new_start;
            try {
                new_finish = uninitialized_copy(m_start_, m_finish_, new_finish);
                new_finish = uninitialized_copy(_first, _last, new_finish);
                _construct_null(new_finish);
            }
            catch(...) {
                destroy(new_start, new_finish + 1);
                _deallocate(new_start, len);
                throw;
            }
            destroy(m_start_, m_finish_ + 1);
            _deallocate_block();
            m_start_ = new_start;
            m_finish_ = new_finish;
            m_end_of_storage_ = m_start_ + len;
        }
        else
        {
            uninitialized_copy(_first + 1, _last, m_finish_ + 1);
            try {
                _construct_null(m_finish_ + count);
            }
            catch(...) {
                destroy(m_finish_ + 1, m_finish_ + count + 1);
                throw;
            }
            Traits::assign(*m_finish_, *_first);
            m_finish_ += count;
        }
    }
    return *this;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>&
basic_string<CharT, Traits, Allocator>::replace(const_iterator _first,
                                                const_iterator _last,
                                                size_type _count,
                                                CharT _ch)
{
    const auto len = static_cast<size_type>(_last - _first);
    if(size() - len > max_size() - _count)
        _throw_length_error();
    if(len >= _count)
    {
        Traits::assign(_first, _count, _ch);
        erase(_first + _count, _last);
    }
    else
    {
        Traits::assign(_first, len, _ch);
        insert(_last, _count - len, _ch);
    }
    return *this;
}            

template <typename CharT, typename Traits, typename Allocator>
template <typename InputIterator>
basic_string<CharT, Traits, Allocator>&
basic_string<CharT, Traits, Allocator>::_replace_aux(const_iterator _first1,
                                                     const_iterator _last1,
                                                     InputIterator _first2,
                                                     InputIterator _last2,
                                                     input_iterator_tag)
{
    for(;_first1 != _last1 && _first2 != _last2; ++_first1, ++_first2)
        Traits::assign(*_first1, *_first2);
    if(_first2 == _last2)
        erase(_first1, _last1);
    else
        insert(_first1, _first2, _last2);
    return *this;
}

template <typename CharT, typename Traits, typename Allocator>
template <typename ForwardIterator>
basic_string<CharT, Traits, Allocator>&
basic_string<CharT, Traits, Allocator>::_replace_aux(const_iterator _first1,
                                                     const_iterator _last1,
                                                     ForwardIterator _first2,
                                                     ForwardIterator _last2,
                                                     forward_iterator_tag)
{
    const auto len1 = static_cast<size_type>(distance(_first1, _last1));
    const auto len2 = static_cast<size_type>(distance(_first2, _last2));
    if(size() - len1 > max_size() - len2)
        _throw_length_error();
    if(len1 >= len2)
    {
        Traits::assign(_first1, _first2, len2);
        erase(_first1 + len2, _last1);
    }
    else
    {
        Traits::assign(_first1, _first2, len1);
        insert(_last1, _first2 + len1, _last2);
    }
    return *this;
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find(const CharT* _cstr,
                                             size_type _pos,
                                             size_type _count) const
{
    if(_pos + _count > size())
        return npos;
    const_iterator result = wt::search(cbegin() + _pos, cend(),
                                       _cstr, _cstr + _count,
                                       wt::equal_to<CharT>());
    return result == cend() ? npos : (result - cbegin());
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find(CharT _ch, size_type _pos) const
{
    if(_pos >= size())
        return npos;
    const_iterator result = wt::find_if(cbegin() + _pos, cend(),
                        [=](CharT _elem) { return Traits::eq(_elem, _ch); });
    return result == cend() ? npos : (result - cbegin());
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::rfind(const CharT* _cstr,
                                              size_type _pos,
                                              size_type _count) const
{
    const size_type len = size();
    if(len < _count)
        return npos;
    if(_count == 0)
        return wt::min(_pos, len);
    const_iterator new_last = cbegin() + wt::min(len - _count, _pos) + _count;
    const_iterator result = wt::find_end(cbegin(), new_last,
                                         _cstr, _cstr + _count,
                                         wt::equal_to<CharT>());
    return result == new_last ? npos : (result - cbegin());
}

// TODO: replace find with find_if
template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::rfind(CharT _ch,
                                              size_type _pos) const
{
    const size_type len = size();
    if(len < 1)
        return npos;
    const_iterator new_last = cbegin() + wt::min(len - 1, _pos) + 1;
    auto rresult = wt::find_if(wt::make_reverse_iterator(new_last), crend(),
                        [=](CharT _elem) { return Traits::eq(_elem, _ch); });
    return rresult == crend() ? npos : (rresult.base() - 1 - cbegin());
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find_first_of(const CharT* _cstr,
                                                      size_type _pos,
                                                      size_type _count) const
{
    if(_pos >= size())
        return npos;
    const_iterator result = wt::find_first_of(cbegin() + _pos, cend(),
                                              _cstr, _cstr + _count,
                                              wt::equal_to<CharT>());
    return result == cend() ? npos : (result - cbegin());
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find_first_not_of(const CharT* _cstr,
                                                      size_type _pos,
                                                      size_type _count) const
{
    if(_pos >= size())
        return npos;
    auto new_end = _cstr + _count;
    for(auto result = m_start_ + _pos; result != m_finish_; ++result)
    {
        for(auto iter = _cstr; ; ++ iter)
        {
            if(iter == new_end)
                return result - m_start_;
            if(Traits::eq(*iter, *result))
                break;
        }
    }
    return npos;
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find_first_not_of(CharT _ch,
                                                          size_type _pos) const
{
    if(_pos >= size())
        return npos;
    const_iterator result = wt::find_if_not(cbegin() + _pos, cend(),
                          [=](CharT _elem) { return Traits::eq(_elem, _ch); });
    return result == cend() ? npos : (result - cbegin());
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find_last_of(const CharT* _cstr,
                                                     size_type _pos,
                                                     size_type _count) const
{
    const size_type len = size();
    if(len < 1)
        return npos;
    const_iterator new_last = cbegin() + wt::min(_pos, len - 1) + 1;
    auto rresult = wt::find_first_of(wt::make_reverse_iterator(new_last),
                                     crend(),
                                     _cstr, _cstr + _count,
                                     wt::equal_to<CharT>());
    return rresult == crend() ? npos : (rresult.base() - 1 - cbegin());
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find_last_not_of(const CharT* _cstr,
                                                        size_type _pos,
                                                        size_type _count) const
{
    const size_type len = size();
    if(len < 1)
        return npos;
    const_iterator new_last = cbegin() + wt::min(_pos, len -1) + 1;
    auto rresult = wt::find_first_of(wt::make_reverse_iterator(new_last),
                                     crend(),
                                     _cstr, _cstr + _count,
                                     wt::not_equal_to<CharT>());
    return rresult == crend() ? npos : (rresult.base() - 1 - cbegin());
}

template <typename CharT, typename Traits, typename Allocator>
typename basic_string<CharT, Traits, Allocator>::size_type
basic_string<CharT, Traits, Allocator>::find_last_not_of(CharT _ch,
                                                         size_type _pos) const
{
    const size_type len = size();
    if(len < 1)
        return npos;
    const_iterator new_last = cbegin() + wt::min(_pos + len -1) + 1;
    auto rresult = wt::find_if_not(wt::make_reverse_iterator(new_last), crend(),
                        [=](CharT _elem) { return !Traits::eq(_elem, _ch); });
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(const basic_string<CharT, Traits, Allocator>& lhs, 
          const basic_string<CharT, Traits, Allocator>& rhs)
{
    return lhs.append(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(const CharT* lhs, const basic_string<CharT, Traits, Allocator>& rhs)
{
    return basic_string<CharT, Traits, Allocator>(lhs).append(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(CharT lhs, const basic_string<CharT, Traits, Allocator>& rhs)
{
    return basic_string<CharT, Traits, Allocator>(1, lhs).append(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(const basic_string<CharT, Traits, Allocator>& lhs, const CharT* rhs)
{
    return lhs + basic_string<CharT, Traits, Allocator>(rhs);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(const basic_string<CharT, Traits, Allocator>& lhs, CharT rhs)
{
    return lhs + basic_string<CharT, Traits, Allocator>(1, rhs);
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(basic_string<CharT, Traits, Allocator>&& lhs, 
          const basic_string<CharT, Traits, Allocator>& rhs)
{
    return wt::move(lhs.append(rhs));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(const basic_string<CharT, Traits, Allocator>& lhs,
          basic_string<CharT, Traits, Allocator>&& rhs)
{
    return wt::move(rhs.insert(0, lhs));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(basic_string<CharT, Traits, Allocator>&& lhs,
          basic_string<CharT, Traits, Allocator>&& rhs)
{
    return wt::move(lhs.append(rhs));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(const CharT* lhs, basic_string<CharT, Traits,Allocator>&& rhs)
{
    return wt::move(rhs.insert(0, lhs));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(CharT lhs, basic_string<CharT, Traits, Allocator>&& rhs)
{
    return wt::move(rhs.insert(0, 1, rhs));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(basic_string<CharT, Traits, Allocator>&& lhs, const CharT* rhs)
{
    return wt::move(lhs.append(rhs));
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator>
operator+(basic_string<CharT, Traits, Allocator>&& lhs, CharT rhs)
{
    return wt::move(lhs.append(1, rhs));
}

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const basic_string<CharT, Traits, Allocator>& lhs,
                const basic_string<CharT, Traits, Allocator>& rhs) noexcept
{
    return lhs.size() == rhs.size() && 
            Traits::compare(lhs.data(), rhs.data(), lhs.size()) == 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator!=(const basic_string<CharT, Traits, Allocator>& lhs,
                const basic_string<CharT, Traits, Allocator>& rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<(const basic_string<CharT, Traits, Allocator>& lhs,
               const basic_string<CharT, Traits, Allocator>& rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<=(const basic_string<CharT, Traits, Allocator>& lhs,
                const basic_string<CharT, Traits, Allocator>& rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>(const basic_string<CharT, Traits, Allocator>& lhs,
               const basic_string<CharT, Traits, Allocator>& rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>=(const basic_string<CharT, Traits, Allocator>& lhs,
                const basic_string<CharT, Traits, Allocator>& rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const CharT* lhs,
                const basic_string<CharT, Traits, Allocator>& rhs)
{
    return Traits::length(lhs) == rhs.size() &&
            Traits::compare(lhs, rhs.data(), rhs.size()) == 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const basic_string<CharT, Traits, Allocator>& lhs,
                const CharT* rhs)
{
    return Traits::length(rhs) == lhs.size() &&
            Traits::compare(lhs.data(), rhs, lhs.size()) == 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator!=(const CharT* lhs,
                const basic_string<CharT, Traits, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator!=(const basic_string<CharT, Traits, Allocator>& lhs,
                const CharT* rhs)
{
    return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<(const CharT* lhs,
               const basic_string<CharT, Traits, Allocator>& rhs)
{
    return rhs.compare(lhs) > 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<(const basic_string<CharT, Traits, Allocator>& lhs,
               const CharT* rhs)
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<=(const CharT* lhs,
                const basic_string<CharT, Traits, Allocator>& rhs)
{
    return rhs.compare(lhs) >= 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator<=(const basic_string<CharT, Traits, Allocator>& lhs,
                const CharT* rhs)
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>(const CharT* lhs,
               const basic_string<CharT, Traits, Allocator>& rhs)
{
    return rhs.compare(lhs) < 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>(const basic_string<CharT, Traits, Allocator>& lhs,
               const CharT* rhs)
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>=(const CharT* lhs,
                const basic_string<CharT, Traits, Allocator>& rhs)
{
    return rhs.compare(lhs) <= 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator>=(const basic_string<CharT, Traits, Allocator>& lhs,
                const CharT* rhs)
{
    return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, typename Allocator>
void swap(basic_string<CharT, Traits, Allocator>& lhs,
          basic_string<CharT, Traits, Allocator>& rhs)
{
    lhs.swap(rhs);
}



} // namespace wt
#endif