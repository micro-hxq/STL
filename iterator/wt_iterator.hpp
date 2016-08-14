#ifndef _STL_WT_ITERATOR_HPP_
#define _STL_WT_ITERATOR_HPP_

namespace wt{

template <typename Container>
class back_insert_iterator : public wt::iterator<wt::output_iterator_tag,
                                                void, void, void, void> {
public:
    typedef wt::output_iterator_tag     iterator_category;
    typedef void                        value_type;
    typedef void                        difference_type;
    typedef void                        pointer;
    typedef void                        reference;

    explicit back_insert_iterator(Container& container)
    {
        container_ = &container;
    }

    back_insert_iterator& operator=(const typename Container::value_type& value)
    {
        container_->push_back(value);
        return *this;
    }

    back_insert_iterator& operator*()
    {
        return *this;
    }

    back_insert_iterator& operator++()
    {
        return *this;
    }

    back_insert_iterator& operator++(int)
    {
        return *this;
    }
protected:
    Container* container_;
};

template <typename Container>
wt::back_insert_iterator<Container> back_inserter(Container& c)
{
    return wt::back_insert_iterator<Container>(c);
}

template <typename Container>
class front_insert_iterator : public wt::iterator<wt::output_iterator_tag,
                                                    void, void, void, void> {
public:
    typedef wt::output_iterator_tag     iterator_category;
    typedef void                        value_type;
    typedef void                        difference_type;
    typedef void                        pointer;
    typedef void                        reference;

    explicit front_insert_iterator(Container& c)
    {
        container_ = &c;
    }   

    front_insert_iterator& operator=(const typename Container::value_type& value)
    {
        container_->push_front(value);
        return *this;
    }

    front_insert_iterator& operator*()
    {
        return *this;
    }

    front_insert_iterator& operator++()
    {
        return *this;
    }

    front_insert_iterator& operator++(int)
    {
        return *this;
    }

private:
    Container* container_;                                                         
};

template <typename Container>
wt::front_insert_iterator<Container> front_inserter(Container& c)
{
    return wt::front_insert_iterator<Container>(c);
}

template <typename Container>
class insert_iterator : public wt::iterator<wt::output_iterator_tag,
                                            void, void, void, void> {
    typedef typename Container::iterator Iterator;
public:                
    typedef wt::output_iterator_tag     iterator_category;
    typedef void                        value_type;
    typedef void                        difference_type;
    typedef void                        pointer;
    typedef void                        reference;

    explicit insert_iterator(Container& container, Iterator iter)
    {
        container_ = container;
        iter_ = iter;
    }

    insert_iterator& operator=(const typename Container::value_type& value)
    {
        iter_ = container_->insert(iter_,value);
        ++iter_;
        return *this;
    }

    insert_iterator& operator*()
    {
        return *this;
    }

    insert_iterator& operator++()
    {
        return *this;
    }

    insert_iterator& operator++(int)
    {
        return *this;
    }
private:
    Container* container_;
    Iterator   iter_;
};

template <typename Container>
wt::insert_iterator<Container> inserter(Container& c,typename Container::iterator iter)
{
    return wt::insert_iterator<Container>(c,iter);
}

template <typename Iterator>
class reverse_iterator : public wt::iterator<
                            typename wt::iterator_traits<Iterator>::iterator_category,
                            typename wt::iterator_traits<Iterator>::value_type,
                            typename wt::iterator_traits<Iterator>::difference_type,
                            typename wt::iterator_traits<Iterator>::pointer,
                            typename wt::iterator_traits<Iterator>::reference> {
public:
    typedef typename wt::iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename wt::iterator_traits<Iterator>::value_type        value_type;
    typedef typename wt::iterator_traits<Iterator>::difference_type   difference_type;
    typedef typename wt::iterator_traits<Iterator>::pointer           pointer;
    typedef typename wt::iterator_traits<Iterator>::reference         reference;

    reverse_iterator() { }
    explicit reverse_iterator(Iterator iter) : current_(iter) { }
    reverse_iterator(const reverse_iterator& other) : current_(other.current_) { }

    template <typename _Iter>
    reverse_iterator(const reverse_iterator<_Iter>& other) : current_(other.base()) { }

    reverse_iterator& operator=(const reverse_iterator& other)
    {
        current_ = other.base();
    }
    Iterator base() const
    {
        return current_;
    }

    reference operator*() const
    {
        Iterator temp_iter = current_;
        return *(--temp_iter);
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    reverse_iterator& operator++()
    {
        --current_;
        return *this;
    }

    reverse_iterator operator++(int)
    {
        reverse_iterator temp_iter = *this;
        --current_;
        return temp_iter;
    }

    reverse_iterator& operator--()
    {
        ++current_;
        return *this;
    }

    reverse_iterator operator--(int)
    {
        reverse_iterator temp_iter = *this;
        ++current_;
        return temp_iter;
    }

    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(current_ - n);
    }

    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(current_ + n);
    }

    reverse_iterator& operator+=(difference_type n) 
    {
        current_ -= n;
        return *this;
    }

    reverse_iterator& operator-=(difference_type n)
    {
        current_ += n;
        return *this;
    }

    // construct reverse_iterator to deference conversely
    reference operator[](difference_type n) const
    {
        return *(*this + n);
    }
private:
    Iterator current_;                                
};

template <typename Iterator>
wt::reverse_iterator<Iterator> make_reverse_iterator(Iterator iter)
{
    return wt::reverse_iterator<Iterator>(iter);
}

template <typename Iterator1, typename Iterator2>
inline bool operator==(const wt::reverse_iterator<Iterator1>& lhs,
                       const wt::reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename Iterator1, typename Iterator2>
inline bool operator!=(const wt::reverse_iterator<Iterator1>& lhs,
                       const wt::reverse_iterator<Iterator2>& rhs)
{
    return !(lhs == rhs);
}

template <typename Iterator1, typename Iterator2>
inline bool operator<(const wt::reverse_iterator<Iterator1>& lhs,
                      const wt::reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename Iterator1, typename Iterator2>
inline bool operator>(const wt::reverse_iterator<Iterator1>& lhs,
                      const wt::reverse_iterator<Iterator2>& rhs)
{
    return rhs < lhs;
}

template <typename Iterator1, typename Iterator2>
inline bool operator<=(const wt::reverse_iterator<Iterator1>& lhs,
                       const wt::reverse_iterator<Iterator2>& rhs)
{
    return !(rhs < lhs);
}

template <typename Iterator1, typename Iterator2>
inline bool operator>=(const wt::reverse_iterator<Iterator1>& lhs,
                       const wt::reverse_iterator<Iterator2>& rhs)
{
    return !(lhs < rhs);
}

template <typename Iterator>
inline typename wt::reverse_iterator<Iterator>::difference_type 
operator-(const wt::reverse_iterator<Iterator>& lhs,
          const wt::reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

template <typename Iterator>
inline wt::reverse_iterator<Iterator> 
operator+(typename wt::reverse_iterator<Iterator>::difference_type n,
          wt::reverse_iterator<Iterator> iter)
{
    return iter + n;
}

template <typename Container>
constexpr auto begin(Container& c) -> decltype(c.begin())
{
    return c.begin();
}

template <typename Container>
constexpr auto begin(const Container& c) -> decltype(c.begin())
{
    return c.begin();
}

template <typename Container>
constexpr auto cbegin(const Container& c) -> decltype(c.cbegin())
{
    return c.cbegin();
}

template <typename Container>
constexpr auto end(Container& c) -> decltype(c.end())
{
    return c.end();
}

template <typename Container>
constexpr auto end(const Container& c) -> decltype(c.end())
{
    return c.end();
}

template <typename Container>
constexpr auto cend(const Container& c) -> decltype(c.cend())
{
    return c.cend();
}

template <typename T, std::size_t N>
constexpr T* begin(T (&array)[N])
{
    return array;
}

template <typename T, std::size_t N>
constexpr T* end(T (&array)[N])
{
    return array + N;
}

template <typename T>
constexpr const T* begin(std::initializer_list<T> il)
{
    return il.begin();
}

template <typename T>
constexpr const T* end(std::initializer_list<T> il)
{
    return il.end();
}

template <typename Container>
constexpr auto rbegin(Container& c) -> decltype(c.rbegin())
{
    return c.rbegin();
}

template <typename Container>
constexpr auto rbegin(const Container& c) -> decltype(c.rbegin())
{
    return c.rbegin();
}

template <typename Container>
constexpr auto crbegin(const Container& c) -> decltype(c.crbegin())
{
    return c.crbegin();
}

template <typename Container>
constexpr auto rend(Container& c) -> decltype(c.rend())
{
    return c.rend();
}

template <typename Container>
constexpr auto rend(const Container& c) -> decltype(c.rend())
{
    return c.rend();
}

template <typename Container>
constexpr auto crend(const Container& c) -> decltype(c.crend())
{
    return c.crend();
}

template <typename T, std::size_t N>
constexpr wt::reverse_iterator<T*> rbegin(T (&array)[N])
{
    return wt::reverse_iterator<T*>(array + N);
}

template <typename T, std::size_t N>
constexpr wt::reverse_iterator<T*> rend(T (&array)[N])
{
    return wt::reverse_iterator<T*>(array);
}

template <typename T>
wt::reverse_iterator<const T*> rbegin(std::initializer_list<T> il)
{
    return wt::reverse_iterator<const T*>(il.end());
}

template <typename T>
wt::reverse_iterator<const T*> rend(std::initializer_list<T> il)
{
    return wt::reverse_iterator<const T*>(il.begin());
}



  // TODO stream_iterator


} // namespace std


#endif