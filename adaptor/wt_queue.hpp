#ifndef _STL_WT_QUEUE_HPP_
#define _STL_WT_QUEUE_HPP_

namespace wt{

template <typename T, typename Container = wt::deque<T>>
class queue {
public:
    template <typename _T, typename _Con>
    friend bool operator==(const queue<_T, _Con>& lhs,
        const queue<_T, _Con>& rhs);
    template <typename _T, typename _Con>
    friend bool operator<(const queue<T, _Con>& lhs,
        const queue<_T, _Con>& rhs);

    typedef Container                           container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

    explicit queue(const container_type& _c) : m_container_(_c) {}
    explicit queue(container_type&& _c = container_type())
     : m_container_(wt::move(_c)) {}

    queue(const queue& other) : m_container_(other.m_container_) {}
    queue(queue&& other) : m_container_(wt::move(other.m_container_)) {}

    template <typename Allocator>
    explicit queue(const Allocator& _alloc) : m_container_(_alloc) {}

    template <typename Allocator>
    queue(const container_type& _a, const Allocator& _alloc) 
     : m_container_(_a, _alloc) {}
    template <typename Allocator>
    queue(container_type&& _a, const Allocator& _alloc)
     : m_container_(wt::move(_a), _alloc) {}

    template <typename Allocator>
    queue(const queue& other, const Allocator& _alloc)
     : m_container_(other.m_container_, _alloc) {}
    template <typename Allocator>
    queue(queue&& other, const Allocator& _alloc)
     : m_container_(wt::move(other.m_container_), _alloc) {}

    ~queue() {}

    queue& operator=(const queue& other)
    {
        m_container_ = other.m_container_;
        return *this;
    }
    queue& operator=(queue&& other)
    {
        m_container_ = wt::move(other.m_container_);
        return *this;
    }

    /**
     *  Element Access
     */
    reference front()
    {
        return m_container_.front();
    }
    const_reference front() const
    {
        return m_container_.front();
    }
    reference back()
    {
        return m_container_.back();
    }
    const_reference back() const
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
    // void push(value_type&& _value)
    // {
    //     m_container_.push_back(wt::move(_value));
    // }
    template <typename... Args>
    reference emplace(Args&&... args)
    {
        return m_container_.emplace_back(wt::forward<Args>(args)...);
    }
    void pop()
    {
        m_container_.pop_front();
    }
    void swap(queue& other)
    {
        wt::swap(m_container_, other.m_container_);
    }
protected:
    container_type m_container_;
};

template <typename T, typename Container>
bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return lhs.m_container_ == rhs.m_container_;
}

template <typename T, typename Container>
bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return lhs.m_container_ < rhs.m_container_;
}

template <typename T, typename Container>
bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Container>
bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return !(rhs < lhs);
}

template <typename T, typename Container>
bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return rhs < lhs;
}

template <typename T, typename Container>
bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
{
    return !(lhs < rhs);
}

template <typename T, typename Container>
void swap(queue<T, Container>& lhs, queue<T, Container>& rhs)
{
    lhs.swap(rhs);
}


} // namespace wt


#endif