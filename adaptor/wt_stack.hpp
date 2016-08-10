#ifndef _STL_WT_STACK_HPP_
#define _STL_WT_STACK_HPP_


namespace wt{

template <typename T, typename Container = wt::deque<T>>
class stack {
public:
    template <typename _T, typename _Con>
    friend bool operator==(const stack<_T, _Con>& lhs, const stack<_T, _Con>& rhs);
    template <typename _T, typename _Con>
    friend bool operator<(const stack<_T, _Con>& lhs, const stack<_T, _Con>& rhs);

    typedef Container                           container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

    explicit stack(const container_type& _c) : m_container_(_c) {}
    explicit stack(container_type&& _c = container_type())
     : m_container_(wt::move(_c)) {}

    stack(const stack& other) : m_container_(other.m_container_) {}
    stack(stack&& other) noexcept : m_container_(wt::move(other.m_container_)) {}

    template <typename Allocator>
    explicit stack(const Allocator& _alloc) : m_container_(_alloc) {}

    template <typename Allocator>
    stack(const container_type& _c, const Allocator& _alloc)
     : m_container_(_c, _alloc) {}
    template <typename Allocator>
    stack(container_type&& _c, const Allocator& _alloc)
     : m_container_(wt::move(_c), _alloc) {}

    template <typename Allocator>
    stack(const stack& other, const Allocator& _alloc)
     : m_container_(other.m_container_, _alloc) {}    
    template <typename Allocator>
    stack(stack&& other, const Allocator& _alloc)
     : m_container_(wt::move(other.m_container_), _alloc) {}

    ~stack() {}
    
    /**
     *  Element Access
     */
    reference top()
    {
        return m_container_.back();
    }
    const_reference top() const
    {
        return m_container_.back();
    }
    /**
     *  Capacity Operations
     */
    bool empty() const
    {
        return m_container_.empty();
    }
    size_type size() const
    {
        return m_container_.size();
    }
    /**
     *  Modify Operations
     */
    void push(const value_type& _value)
    {
        m_container_.push_back(_value);
    }
    void push(value_type&& _value)
    {
        m_container_.push_back(wt::move(_value));
    }
    
    template <typename... Args>
    reference emplace(Args&&... args)
    {
        return m_container_.emplace_back(wt::forward<Args>(args)...);
    }
    void pop()
    {
        m_container_.pop_back();
    }
    void swap(stack& other)
    {
        wt::swap(m_container_, other.m_container_);
    } 

protected:
    container_type m_container_;
};

template <typename T, typename Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.m_container_ == rhs.m_container_;
}

template <typename T, typename Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return lhs.m_container_ < rhs.m_container_;
}

template <typename T, typename Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Container>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Container>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
    return !(lhs < rhs);
}

template <typename T, typename Container>
void swap(stack<T, Container>& lhs, stack<T, Container>& rhs)
{
    lhs.swap(rhs);
}

} // namespace wt


#endif  