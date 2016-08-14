#ifndef _STL_WT_PRI_QUEUE_HPP_
#define _STL_WT_PRI_QUEUE_HPP_

namespace wt {

template <typename T, typename Container = wt::vector<T>,
        typename Compare = wt::default_order_t<typename Container::value_type>>
class priority_queue {
public: 
    typedef Container                           container_type;
    typedef Compare                             value_compare;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

    priority_queue(const Compare& _comp, const Container& _c)
     : m_comparator_(_comp), m_container_(_c)
    {
        wt::make_heap(m_container_.begin(), m_container_.end(), m_comparator_);
    }

    explicit priority_queue(const Compare& _comp = Compare(),
                            Container&& _c = Container())
     : m_comparator_(_comp), m_container_(wt::move(_c))
    {
        wt::make_heap(m_container_.begin(), m_container_.end(), m_comparator_);
    }

    priority_queue(const priority_queue& other)
     : m_comparator_(other.m_comparator_), m_container_(other.m_container_)
    { }

    priority_queue(priority_queue&& other)
     : m_comparator_(wt::move(other.m_comparator_)),
       m_container_(wt::move(other.m_container_))
    { }

    template <typename Allocator>
    explicit priority_queue(const Allocator& _alloc)
     : m_comparator_(Compare()), m_container_(_alloc)
    { }

    template <typename Allocator>
    priority_queue(const Compare& _comp, const Allocator& _alloc)
     : m_comparator_(_comp), m_container_(_alloc)
    { }

    template <typename Allocator>
    priority_queue(const Compare& _comp, const Container& _c,
                   const Allocator& _alloc)
     : m_comparator_(_comp), m_container_(_c, _alloc)
    {
        wt::make_heap(m_container_.begin(), m_container_.end(), _comp);
    }

    template <typename Allocator>
    priority_queue(const Compare& _comp, Container&& _c, const Allocator& _alloc)
     : m_comparator_(_comp), m_container_(wt::move(_c), _alloc)
    {
        wt::make_heap(m_container_.begin(), m_container_.end(), _comp);
    }

    template <typename Allocator>
    priority_queue(const priority_queue& other, const Allocator& _alloc)
     : m_comparator_(other.m_comparator_),
       m_container_(other.m_container_, _alloc)
    { }

    template <typename Allocator>
    priority_queue(priority_queue&& other, const Allocator& _alloc)
     : m_comparator_(wt::move(other.m_comparator_)),
       m_container_(wt::move(other.m_container_), _alloc)
    { }

    template <typename InputIterator>
    priority_queue(InputIterator _first, InputIterator _last,
                   const Compare& _comp, const Container& _c)
     : m_comparator_(_comp), m_container_(_c)
    {
        m_container_.insert(m_container_.end(), _first, _last);
        wt::make_heap(m_container_.begin(), m_container_.end(), _comp);
    }

    template <typename InputIterator>
    priority_queue(InputIterator _first, InputIterator _last,
                   const Compare& _comp = Compare(),
                   Container&& _c = Container())
     : m_comparator_(_comp), m_container_(wt::move(_c))
    {
        m_container_.insert(m_container_.end(), _first, _last);
        wt::make_heap(m_container_.begin(), m_container_.end(), _comp);
    }

    ~priority_queue() { }

    /**
     *  Elements Access
     */
    const_reference top() const
    {
        return m_container_.front();
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
    void push(const T& _value)
    {
        m_container_.push_back(_value);
        wt::push_heap(m_container_.begin(), m_container_.end(), m_comparator_);
    }

    void push(T&& _value)
    {
        m_container_.push_back(wt::move(_value));
        wt::push_heap(m_container_.begin(), m_container_.end(), m_comparator_);
    }

    template <typename... Args>
    void emplace(Args&&... args)
    {
        m_container_.emplace_back(wt::forward<Args>(args)...);
        wt::push_heap(m_container_.begin(), m_container_.end(), m_comparator_);
    }

    void pop()
    {
        wt::pop_heap(m_container_.begin(), m_container_.end(), m_comparator_);
        m_container_.pop_back();
    }

    void swap(priority_queue& other)
    {
        wt::swap(m_comparator_, other.m_comparator_);
        wt::swap(m_container_, other.m_container_);
    }

protected:
    value_compare   m_comparator_;
    container_type  m_container_;
};

template <typename T, typename Container, typename Compare>
void swap(priority_queue<T, Container, Compare>& lhs,
          priority_queue<T, Container, Compare>& rhs)
{
    return lhs.swap(rhs);
}

} // namespace wt


#endif