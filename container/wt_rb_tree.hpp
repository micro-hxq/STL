#ifndef _STL_WT_TREE_HPP_
#define _STL_WT_TREE_HPP_

namespace wt {

enum class RBColor {
    red     = true,
    black   = false
};

class Rb_tree_node_base {
public:
    typedef Rb_tree_node_base*           _PBase_type;
    typedef const Rb_tree_node_base*     _Const_PBase_type;

    Rb_tree_node_base() : m_color_(RBColor::black), m_parent_(nullptr),
                        m_left_(nullptr), m_right_(nullptr) { }

    static _PBase_type minimum(_PBase_type _node) noexcept
    {
        while(_node->m_left_ != nullptr)
            _node = _node->m_left_;
        return _node;
    }

    static _Const_PBase_type minimum(_Const_PBase_type _node) noexcept
    {
        while(_node->m_left_ != nullptr)
            _node = _node->m_left_;
        return _node;
    }

    static _PBase_type maximum(_PBase_type _node) noexcept
    {
        while(_node->m_right_ != nullptr)
            _node = _node->m_right_;
        return _node;
    }

    static _Const_PBase_type maximum(_Const_PBase_type _node) noexcept
    {
        while(_node->m_right_ != nullptr)
            _node = _node->m_right_;
        return _node;
    }

    RBColor         m_color_;
    _PBase_type     m_parent_;
    _PBase_type     m_left_;
    _PBase_type     m_right_;
};

template <typename T>
class Rb_tree_node : public Rb_tree_node_base {
public:
    typedef Rb_tree_node<T>*    _PNode_type;

    T* _ptr() noexcept
    {
        return &m_data_;
    }
    const T* _ptr() const noexcept
    {
        return &m_data_;
    }

    T& _val() noexcept
    {
        return m_data_;
    }
    const T& _val() const noexcept
    {
        return m_data_;
    }

    T   m_data_;
};

Rb_tree_node_base*
Rb_tree_increment(Rb_tree_node_base* _node)
{
    if(_node->m_right_)
    {
        _node = _node->m_right_;
        while(_node->m_left_)
            _node = _node->m_left_;
    }
    else
    {
        Rb_tree_node_base* p = _node->m_parent_;
        while(_node == p->m_right_)     //  until (1).find _node is left child of parent
        {                               //  or (2)._node is root without right child
            _node = p;
            p = p->m_parent_;
        }
        if(_node->m_right_ != p)         // case (2): equal when p is root and _node is m_header_
            _node = p;
    }
    return _node;
}

const Rb_tree_node_base*
Rb_tree_increment(const Rb_tree_node_base* _node)
{
    if(_node->m_right_)
    {
        _node = _node->m_right_;
        while(_node->m_left_)
            _node = _node->m_left_;
    }
    else
    {
        Rb_tree_node_base* p = _node->m_parent_;
        while(_node == p->m_right_)     //  until (1).find _node is left child of parent
        {                               //  or (2)._node is root without right child
            _node = p;
            p = p->m_parent_;
        }
        if(_node->m_right_ != p)         // case (2): equal when p is root and _node is m_header_
            _node = p;
    }
    return _node;
}

Rb_tree_node_base*
Rb_tree_decrement(Rb_tree_node_base* _node)
{
    if(_node->m_color_ == RBColor::red && _node->m_parent_->m_parent_ == _node)
        _node = _node->m_right_;
    else if(_node->m_left_)
    {
        _node = _node->m_left_;
        while(_node->m_right_)
            _node = _node->m_right_;
    }
    else
    {
        Rb_tree_node_base* p = _node->m_parent_;
        while(_node == p->m_left_)
        {
            _node = p;
            p = p->m_parent_;
        }
        if(_node->m_left_ != p)
            _node = p;
    }
    return _node;
}

const Rb_tree_node_base*
Rb_tree_decrement(const Rb_tree_node_base* _node)
{
    if(_node->m_color_ == RBColor::red && _node->m_parent_->m_parent_ == _node)
        _node = _node->m_right_;
    else if(_node->m_left_)
    {
        _node = _node->m_left_;
        while(_node->m_right_)
            _node = _node->m_right_;
    }
    else
    {
        Rb_tree_node_base* p = _node->m_parent_;
        while(_node == p->m_left_)
        {
            _node = p;
            p = p->m_parent_;
        }
        if(_node->m_left_ != p)
            _node = p;
    }
    return _node;
}

template <typename T>
class Rb_tree_const_iterator 
            : public wt::iterator<wt::bidirectional_iterator_tag, T> {
public:
    typedef wt::bidirectional_iterator_tag      iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef const value_type*                   pointer;
    typedef const value_type&                   reference;                      

    typedef Rb_tree_const_iterator<T>           _Self;
    typedef Rb_tree_node_base*                  _PBase_type;
    typedef const Rb_tree_node<T>*              _PNode_type;

    Rb_tree_const_iterator() : m_pnode_(nullptr) { }
    explicit Rb_tree_const_iterator(_PBase_type _ptr) : m_pnode_(_ptr) { }

    reference operator*() const noexcept
    {
        return static_cast<_PNode_type>(m_pnode_)->_val();
    }

    pointer operator->() const noexcept
    {
        return static_cast<_PNode_type>(m_pnode_)->_ptr();
    }

    _Self& operator++() noexcept
    {
        m_pnode_ = Rb_tree_increment(m_pnode_);
        return *this;
    }

    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        m_pnode_ = Rb_tree_increment(m_pnode_);
        return temp;
    }

    _Self& operator--() noexcept
    {
        m_pnode_ = Rb_tree_decrement(m_pnode_);
        return *this;
    }

    _Self operator--(int) noexcept
    {
        _Self temp = *this;
        m_pnode_ = Rb_tree_decrement(m_pnode_);
        return temp;
    }

    bool operator==(const _Self& other) const noexcept
    {
        return m_pnode_ == other.m_pnode_;
    }

    bool operator!=(const _Self& other) const noexcept
    {
        return m_pnode_ != other.m_pnode_;
    }

    _PBase_type m_pnode_;
};

template <typename T>
class Rb_tree_iterator : public Rb_tree_const_iterator<T> {
public:
    typedef wt::bidirectional_iterator_tag      iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef value_type*                         pointer;
    typedef value_type&                         reference;  

    typedef Rb_tree_iterator<T>                 _Self;
    typedef Rb_tree_const_iterator<T>           _Base;
    typedef typename _Base::_PBase_type         _PBase_type;
    typedef Rb_tree_node<T>*                    _PNode_type;

    using _Base::m_pnode_;

    Rb_tree_iterator() : _Base() { }
    explicit Rb_tree_iterator(_PBase_type _ptr) : _Base(_ptr) { }

    reference operator*() noexcept
    {
        return static_cast<_PNode_type>(m_pnode_)->_val();
    }

    pointer operator->() noexcept
    {
        return static_cast<_PNode_type>(m_pnode_)->_ptr();
    }

    _Self& operator++() noexcept
    {
        m_pnode_ = Rb_tree_increment(m_pnode_);
        return *this;
    }

    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        m_pnode_ = Rb_tree_increment(m_pnode_);
        return temp;
    }

    _Self& operator--() noexcept
    {
        m_pnode_ = Rb_tree_decrement(m_pnode_);
        return *this;
    }

    _Self operator--(int) noexcept
    {
        _Self temp = *this;
        m_pnode_ = Rb_tree_decrement(m_pnode_);
        return temp;
    }

    bool operator==(const _Self& other) const noexcept
    {
        return m_pnode_ == other.m_pnode_;
    }

    bool operator!=(const _Self& other) const noexcept
    {
        return m_pnode_ != other.m_pnode_;
    }
};

// Rb_tree_node_base*
// Rb_tree_rotate_left(Rb_tree_node_base* _node)
// {
//     Rb_tree_node_base* new_node = _node->m_right_;
//     _node->m_right_ = new_node->m_left_;
//     new_node->m_left_ = _node;
//     if(_node->m_right_)
//         _node->m_right_->m_parent_ = _node;
//     new_node->m_parent_ = _node->m_parent_;
//     _node->m_parent_ = new_node;
//     return new_node;
// }

// Rb_tree_node_base*
// Rb_tree_rotate_right(Rb_tree_node_base* _node)
// {
//     Rb_tree_node_base* new_node = _node->m_left_;
//     _node->m_left_ = new_node->m_right_;
//     new_node->m_right_ = _node;
//     if(_node->m_left_)
//         _node->m_left_->m_parent_ = _node;
//     new_node->m_parent_ = _node->m_parent_;
//     _node->m_parent_ = new_node;
//     return new_node;
// }

void
Rb_tree_rotate_left(Rb_tree_node_base* px, Rb_tree_node_base*& root)
{
    Rb_tree_node_base* py = px->m_right_;
    px->m_right_ = py->m_left_;
    if(py->m_left_ != nullptr)
        py->m_left_->m_parent_ = px;
    py->m_parent_ = px->m_parent_;

    if(px == root)
        root = py;
    else if(px->m_parent_->m_left_ == px)
        px->m_parent_->m_left_ = py;
    else
        px->m_parent_->m_right_ = py;

    py->m_left_ = px;
    px->m_parent_ = py;
}

void
Rb_tree_rotate_right(Rb_tree_node_base* px, Rb_tree_node_base*& root)
{
    Rb_tree_node_base* py = px->m_left_;
    px->m_left_ = py->m_right_;
    if(py->m_right_ != nullptr)
        py->m_right_->m_parent_ = px;
    py->m_parent_ = px->m_parent_;

    if(px == root)
        root = py;
    else if(px->m_parent_->m_left_ == px)
        px->m_parent_->m_left_ = py;
    else
        px->m_parent_->m_right_ = py;

    py->m_right_ = px;
    px->m_parent_ = py;
}

/**
 * This function is used to rebalance for inserted node
 * @param px   inserted node
 * @param root root node
 */
void 
Rb_tree_insert_rebalance(Rb_tree_node_base* px, Rb_tree_node_base*& root)
{
    px->m_color_ = RBColor::red;
    while(px != root && px->m_parent_->m_color_ == RBColor::red)
    {
        if(px->m_parent_ == px->m_parent_->m_parent_->m_left_)
        {
            Rb_tree_node_base* py = px->m_parent_->m_parent_->m_right_;
            if(py && py->m_color_ == RBColor::red)                  //  case 1
            {
                py->m_color_ = RBColor::black;
                px->m_parent_->m_color_ = RBColor::black;
                px->m_parent_->m_parent_->m_color_ = RBColor::red;
                px = px->m_parent_->m_parent_;
            }
            else
            {
                if(px == px->m_parent_->m_right_)                   //  case 2
                {
                    px = px->m_parent_;
                    Rb_tree_rotate_left(px, root);
                }
                px->m_parent_->m_color_ = RBColor::black;           //  case 3
                px->m_parent_->m_parent_->m_color_ = RBColor::red;
                Rb_tree_rotate_right(px->m_parent_->m_parent_, root);
            }
        }
        else
        {
            Rb_tree_node_base* py = px->m_parent_->m_parent_->m_left_;
            if(py && py->m_color_ == RBColor::red)
            {
                py->m_color_ = RBColor::black;
                px->m_parent_->m_color_ = RBColor::black;
                px->m_parent_->m_parent_->m_color_ = RBColor::red;
                px = px->m_parent_->m_parent_;
            }
            else
            {
                if(px == px->m_parent_->m_left_)
                {
                    px = px->m_parent_;
                    Rb_tree_rotate_right(px, root);
                }
                px->m_parent_->m_color_ = RBColor::black;
                px->m_parent_->m_parent_->m_color_ = RBColor::red;
                Rb_tree_rotate_left(px->m_parent_->m_parent_, root);
            }
        }
    }
    root->m_color_ = RBColor::black;
}

/**
 * [Rb_tree_erase_rebalance description]
 * @param  pz    [description]
 * @param  root  [description]
 * @param  lmost [description]
 * @param  rmost [description]
 * @return       Pointer point to erased node
 */
Rb_tree_node_base* 
Rb_tree_erase_rebalance(Rb_tree_node_base* pz, Rb_tree_node_base*& root,
                        Rb_tree_node_base*& lmost, Rb_tree_node_base*& rmost)
{
    Rb_tree_node_base* py = pz;
    Rb_tree_node_base* px = nullptr;
    Rb_tree_node_base* px_parent = nullptr;

    //  erase process
    if(py->m_left_ == nullptr)          // px may be nullptr or not
        px = py->m_right_;
    else
    {
        if(py->m_right_ == nullptr)     //  px must not nullptr
            px = py->m_left_;
        else
        {
            py = py->m_right_;
            while(py->m_left_)
                py = py->m_left_;
            px = py->m_right_;          //  px may be nullptr or not
        }
    }

    if(py == pz)
    {
        px_parent = py->m_parent_;
        if(px)
            px->m_parent_ = px_parent;
        if(pz == root)
            root = px;
        else if(pz == pz->m_parent_->m_left_)
            pz->m_parent_->m_left_ = px;
        else
            pz->m_parent_->m_right_ = px;

        if(pz == lmost)
        {
            if(pz->m_right_)
                lmost = Rb_tree_node_base::minimum(px);
            else 
                lmost = pz->m_parent_;
        }
        if(pz == rmost)
        {
            if(pz->m_left_)
                rmost = Rb_tree_node_base::maximum(px);
            else
                rmost = pz->m_parent_;
        }
    }
    else
    {
        pz->m_left_->m_parent_ = py;
        py->m_left_ = pz->m_left_;
        if(py == pz->m_right_)
            px_parent = py;
        else
        {
            px_parent = py->m_parent_;
            if(px)
                px->m_parent_ = px_parent;
            py->m_parent_->m_left_ = px;
            py->m_right_ = pz->m_right_;
            pz->m_right_->m_parent_ = py;
        }
        if(root == pz)
            root = py;
        else if(pz == pz->m_parent_->m_left_)
            pz->m_parent_->m_left_ = py;
        else
            pz->m_parent_->m_right_ = py;
        py->m_parent_ = pz->m_parent_;
        wt::swap(py->m_color_, pz->m_color_);
        py = pz;
    }

    //  rebalance process
    if(py->m_color_ == RBColor::black)
    {
        // rebalance for four cases
        while(px != root && (px == nullptr || px->m_color_ == RBColor::black))
        {
            if(px == px_parent->m_left_)
            {
                Rb_tree_node_base* pw = px_parent->m_right_;
                if(pw->m_color_ == RBColor::red)                    // case 1
                {
                    px_parent->m_color_ = RBColor::red;
                    pw->m_color_ = RBColor::black;
                    Rb_tree_rotate_left(px_parent, root);
                    pw = px_parent->m_right_;
                }
                if((pw->m_left_ == nullptr ||                       //  case 2
                    pw->m_left_->m_color_ == RBColor::black) &&
                    (pw->m_right_ == nullptr ||
                    pw->m_right_->m_color_ == RBColor::black))
                {
                    pw->m_color_ = RBColor::red;
                    px = px_parent;
                    px_parent = px_parent->m_parent_;
                }
                else 
                {
                    if(pw->m_right_ == nullptr ||                   //  case 3
                        pw->m_right_->m_color_ == RBColor::black)
                    {
                        //  pw->m_left_ must exist
                        pw->m_left_->m_color_ = RBColor::black;
                        pw->m_color_ = RBColor::red;
                        Rb_tree_rotate_right(pw, root);
                        pw = px_parent->m_right_;
                    }
                    // pw->m_right_ must exist
                    pw->m_color_ = px_parent->m_color_;             //  case 4
                    pw->m_right_->m_color_ = RBColor::black;
                    px_parent->m_color_ = RBColor::black;
                    Rb_tree_rotate_left(px_parent, root);
                    break;
                }
            }
            else
            {
                Rb_tree_node_base* pw = px_parent->m_left_;
                if(pw->m_color_ == RBColor::red)
                {
                    px_parent->m_color_ = RBColor::red;
                    pw->m_color_ = RBColor::black;
                    Rb_tree_rotate_right(px_parent, root);
                    pw = px_parent->m_left_;
                }
                if((pw->m_left_ == nullptr || 
                    pw->m_left_->m_color_ == RBColor::black) && 
                    (pw->m_right_ == nullptr ||
                    pw->m_right_->m_color_ == RBColor::black))
                {
                    pw->m_color_ = RBColor::red;
                    px = px_parent;
                    px_parent = px_parent->m_parent_;
                }
                else
                {
                    if(pw->m_left_ == nullptr || 
                        pw->m_left_->m_color_ == RBColor::black)
                    {
                        pw->m_right_->m_color_ = RBColor::black;
                        pw->m_color_ = RBColor::red;
                        Rb_tree_rotate_left(pw, root);
                        pw = px_parent->m_left_;
                    }
                    pw->m_color_ = px_parent->m_color_;
                    pw->m_left_->m_color_ = RBColor::black;
                    px_parent->m_color_ = RBColor::black;
                    Rb_tree_rotate_right(px_parent, root);
                    break;
                }
            }
        }
        if(px)
            px->m_color_ = RBColor::black;
    }
    return py;
}

int Rb_black_count(const Rb_tree_node_base* node, const Rb_tree_node_base* root)
{
    if(node == nullptr)
        return 0;
    int n = node->m_color_ == RBColor::black ? 1 : 0;
    if(node == root)
        return n;
    else
        return n + Rb_black_count(node->m_parent_, root);
}

template <typename T, typename Allocator, bool IsStatic>
class Rb_tree_alloc_base {
public:
    typedef typename wt::allocator_traits<Allocator>::allocator_type 
            allocator_type;
    allocator_type get_allocator() const 
    {
        return m_allocator_;
    }

    Rb_tree_alloc_base(const allocator_type& _a)
    : m_allocator_(_a), m_header_(nullptr) { }
protected:
    Rb_tree_node<T>* _alloc_node()
    {
        return m_allocator_.allocate(1);
    }
    void _dealloc_node(Rb_tree_node<T>* _p)
    {
        m_allocator_.deallocate(_p, 1);
    }
    typename wt::_Alloc_traits<Rb_tree_node<T>, Allocator>::allocator_type
                        m_allocator_;
    Rb_tree_node<T>*    m_header_;
};

template <typename T, typename Allocator>
class Rb_tree_alloc_base<T, Allocator, true> {
public:
    typedef typename wt::allocator_traits<Allocator>::allocator_type 
            allocator_type;
    allocator_type get_allocator() const 
    {
        return allocator_type();
    }

    Rb_tree_alloc_base(const allocator_type& _a)
    : m_header_(nullptr) { }

protected:
    typedef typename wt::_Alloc_traits<Rb_tree_node<T>, Allocator>::_Alloc_type
            _Alloc_type;
    Rb_tree_node<T>* _alloc_node()
    {
        return _Alloc_type::allocate(1);
    }
    void _dealloc_node(Rb_tree_node<T>* _p)
    {
        _Alloc_type::deallocate(_p, 1);
    }

    Rb_tree_node<T>*    m_header_;
};

template <typename T, typename Allocator>
class Rb_tree_base : public wt::Rb_tree_alloc_base<T, Allocator,
                    wt::_Alloc_traits<T, Allocator>::isStatic> {
protected:
    typedef wt::Rb_tree_alloc_base<T, Allocator, 
            wt::_Alloc_traits<T, Allocator>::isStatic>  _Base;
    using _Base::_alloc_node;
    using _Base::_dealloc_node;
    using _Base::m_header_;
public:
    typedef typename _Base::allocator_type   allocator_type;
    Rb_tree_base(const allocator_type& _a) : _Base(_a)
    {
        m_header_ = _alloc_node();
    }
    ~Rb_tree_base() 
    {
        _dealloc_node(m_header_);
    }
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator>
class Rb_tree : protected Rb_tree_base<Value, Allocator> {
protected:
    typedef Rb_tree_base<Value, Allocator>  _Base;
    typedef Rb_tree_node_base*              _PBase_type;
    typedef const Rb_tree_node_base*        _Const_PBase_type;
    typedef Rb_tree_node<Value>             _Node_type;
    typedef _Node_type*                     _PNode_type;
    typedef const _Node_type*               _Const_PNode_type;

    using _Base::_alloc_node;
    using _Base::_dealloc_node;
    using _Base::m_header_;
public:
    typedef typename _Base::allocator_type              allocator_type;
    typedef Key                                         key_type;
    typedef Value                                       value_type;
    typedef Compare                                     key_comare;
    typedef value_type*                                 pointer;
    typedef const value_type*                           const_pointer;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef std::size_t                                 size_type;
    typedef std::ptrdiff_t                              difference_type;
    typedef Rb_tree_const_iterator<value_type>          const_iterator;
    typedef Rb_tree_iterator<value_type>                iterator;
    typedef wt::reverse_iterator<const_iterator>        const_reverse_iterator;
    typedef wt::reverse_iterator<iterator>              reverse_iterator;

    allocator_type get_allocator() const
    {
        return _Base::get_allocator();
    }

    /**
     *  Constructor
     */
    Rb_tree()
    : _Base(allocator_type()), m_node_count_(0), m_key_comparator_()
    {
        _empty_initialize();
    }
    Rb_tree(const Compare& _comp)
    : _Base(allocator_type()), m_node_count_(0), m_key_comparator_(_comp)
    {
        _empty_initialize();
    }
    Rb_tree(const Compare& _comp, const allocator_type& _alloc)
    : _Base(_alloc), m_node_count_(0), m_key_comparator_(_comp)
    {
        _empty_initialize();
    }

    Rb_tree(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& other)
    : Rb_tree(other, other.get_allocator()) { }
    Rb_tree(const Rb_tree& other, const allocator_type& _alloc)
    : _Base(_alloc), m_node_count_(0),
      m_key_comparator_(other.m_key_comparator_)
    {
        if(other._root() == nullptr)
            _empty_initialize();
        else
        {
            _color(m_header_) = _red();
            _root() = _Rb_copy(other._begin(), m_header_);
            _leftmost() = _minimum(_root());
            _rightmost() = _maximum(_root());
        }
        m_node_count_ = other.m_node_count_;
    }
    ~Rb_tree()
    {
        clear();
    }
    Rb_tree& operator=(const Rb_tree& other);

    /**
     *  Iterator Operations
     */
    iterator begin() noexcept
    {
        return iterator(m_header_->m_left_);
    }
    const_iterator begin() const noexcept
    {
        return const_iterator(m_header_->m_left_);
    }
    const_iterator cbegin() const noexcept
    {
        return const_iterator(m_header_->m_left_);
    }

    iterator end() noexcept
    {
        return iterator(m_header_);
    }
    const_iterator end() const noexcept
    {
        return const_iterator(m_header_);
    }
    const_iterator cend() const noexcept
    {
        return const_iterator(m_header_);
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
        return const_reverse_iterator(end());
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
        return const_reverse_iterator(begin());
    }

    /**
     *  Access Operations
     */
    key_comare key_comp() const
    {
        return m_key_comparator_;
    }
    bool empty() const noexcept
    {
        return m_node_count_ == 0;
    }
    size_type size() const noexcept
    {
        return m_node_count_;
    }
    size_type max_size() const noexcept
    {
        return static_cast<size_type>(-1);
    }

    /**
     *  Set Operations
     */
    iterator find(const key_type& _key);
    const_iterator find(const key_type& _key) const;

    size_type count(const key_type& _key) const;

    iterator lower_bound(const key_type& _key);
    const_iterator lower_bound(const key_type& _key) const;

    iterator upper_bound(const key_type& _key);
    const_iterator upper_bound(const key_type& _key) const;

    wt::pair<iterator, iterator>
    equal_range(const key_type& _k)
    {
        return wt::make_pair(lower_bound(_k), upper_bound(_k));
    }

    wt::pair<const_iterator, const_iterator> 
    equal_range(const key_type& _k) const
    {
        return wt::make_pair(lower_bound(_k), upper_bound(_k));
    }
    /**
     *  Modify Operations
     */
    wt::pair<iterator, bool> insert_unique(const Value& _value);
    iterator insert_equal(const Value& _value);

    iterator insert_unique(const_iterator _hint, const Value& _value);
    /**
     * The order of equivalent node differ from STL
     * @param  _hint  [description]
     * @param  _value [description]
     * @return        [description]
     */
    iterator insert_equal(const_iterator _hint, const Value& _value);

    template <typename InputIter>
    void insert_unique(InputIter _first, InputIter _last);
    template <typename InputIter>
    void insert_equal(InputIter _first, InputIter _last);

    void insert_unique(std::initializer_list<Value> _ilist)
    {
        insert_unique(_ilist.begin(), _ilist.end());
    }
    void insert_equal(std::initializer_list<Value> _ilist)
    {
        insert_equal(_ilist.begin(), _ilist.end());
    }

    iterator erase(const_iterator _pos);
    iterator erase(const_iterator _first, const_iterator _last);
    size_type erase(const key_type& _key);

    void clear()
    {
        if(m_node_count_ != 0)
        {
            _Rb_erase(_begin());
            _root() = nullptr;
            _leftmost() = m_header_;
            _rightmost() = m_header_;
            m_node_count_ = 0;
        }
    }

    void swap(Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& other) noexcept

    {
        wt::swap(m_header_, other.m_header_);
        wt::swap(m_key_comparator_, other.m_key_comparator_);
        wt::swap(m_node_count_, other.m_node_count_);
    }

    bool rb_verify() const;
protected:
    _PNode_type _create_node(const value_type& _val)
    {
        _PNode_type pnode = _alloc_node();
        try {
            wt::construct(&pnode->m_data_, _val);
        } catch(...) {
            _dealloc_node(pnode);
            throw;
        }
        return pnode;
    }

    _PNode_type _clone_node(_Const_PNode_type _p)
    {
        _PNode_type pnode = _create_node(_p->m_data_);
        pnode->m_color_ = _p->m_color_;
        pnode->m_left_  = nullptr;
        pnode->m_right_ = nullptr;
        return pnode;
    }

    void _destroy_node(_PNode_type _p)
    {
        wt::destroy(&_p->m_data_);
        _dealloc_node(_p);
    }

    _PBase_type& _root() 
    {
        return m_header_->m_parent_;
    }
    _Const_PBase_type _root() const
    {
        return m_header_->m_parent_;
    }
    _PBase_type& _leftmost()
    {
        return m_header_->m_left_;
    }
    _Const_PBase_type _leftmost() const
    {
        return m_header_->m_left_;
    }
    _PBase_type& _rightmost()
    {
        return m_header_->m_right_;
    }
    _Const_PBase_type _rightmost() const
    {
        return m_header_->m_right_;
    }
    //  root
    _PNode_type _begin()
    {
        return static_cast<_PNode_type>(m_header_->m_parent_);
    }
    _Const_PNode_type _begin() const
    {
        return static_cast<_Const_PNode_type>(m_header_->m_parent_);
    }
    _PNode_type _end()
    {
        return m_header_;
    }
    _Const_PNode_type _end() const
    {
        return m_header_;
    }

    static RBColor _red()
    {
        return RBColor::red;
    }
    static RBColor _black()
    {
        return RBColor::black;
    }

    static const_reference _value(_Const_PBase_type _pb)
    {
        return static_cast<_Const_PNode_type>(_pb)->_val();
    }
    static const_reference _value(_Const_PNode_type _pn)
    {
        return _pn->_val();
    }

    static const Key& _key(_Const_PBase_type _pb)
    {
        return KeyOfValue()(_value(_pb));
    }
    static const Key& _key(_Const_PNode_type _pn)
    {
        return KeyOfValue()(_value(_pn));
    }

    static _PNode_type _left(_PBase_type _pb)
    {
        return static_cast<_PNode_type>(_pb->m_left_);
    }
    static _Const_PNode_type _left(_Const_PBase_type _pb)
    {
        return static_cast<_Const_PNode_type>(_pb->m_left_);
    }

    static _PNode_type _right(_PBase_type _pb)
    {
        return static_cast<_PNode_type>(_pb->m_right_);
    }
    static _Const_PNode_type _right(_Const_PBase_type _pb)
    {
        return static_cast<_Const_PNode_type>(_pb->m_right_);
    }

    static RBColor& _color(_PNode_type _pn)
    {
        return _pn->m_color_;
    }

    static _PNode_type _parent(_PBase_type _pb)
    {
        return static_cast<_PNode_type>(_pb->m_parent_);
    }
    static _Const_PNode_type _parent(_Const_PBase_type _pb)
    {
        return static_cast<_Const_PNode_type>(_pb->m_parent_);
    }

    static _PBase_type _minimum(_PBase_type _pb)
    {
        return Rb_tree_node_base::minimum(_pb);
    }
    static _Const_PBase_type _minimum(_Const_PBase_type _pb)
    {
        return Rb_tree_node_base::minimum(_pb);
    }

    static _PBase_type _maximum(_PBase_type _pb)
    {
        return Rb_tree_node_base::maximum(_pb);
    }
    static _Const_PBase_type _maximum(_Const_PBase_type _pb)
    {
        return Rb_tree_node_base::maximum(_pb);
    }

    void _empty_initialize()
    {
        _color(m_header_) = _red();
        _root() = nullptr;
        _leftmost()  = m_header_;
        _rightmost() = m_header_;
    }

    /**
     * insert and rebalance
     * @param  _x     hint， insert left if non-null
     * @param  _y     parent of inserted node
     * @param  _value data
     * @return        iterator to inserted node
     */
    iterator _Rb_insert(_PBase_type _x, _PBase_type _y, const Value& _value);
    /**
     * copy sub-tree _x to parent node _p
     * @param  _x sub-tree
     * @param  _p parent of new sub-tree
     * @return    root of new sub-tree
     */
    _PNode_type _Rb_copy(_Const_PNode_type _x, _PNode_type _p);
    /**
     * erase without rebalancing
     * @param _x root of erased sub-tree
     */
    void _Rb_erase(_PNode_type _x); 

protected:
    size_type       m_node_count_;
    Compare         m_key_comparator_;
};

template <typename Key, typename Value, typename KeyOfValue, 
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::_Rb_insert(_PBase_type _px, _PBase_type _py, const Value& _value)
{
    auto px = static_cast<_PNode_type>(_px);
    auto py = static_cast<_PNode_type>(_py);
    _PNode_type pz = nullptr;
    pz = _create_node(_value);
    if(py == m_header_ || px != nullptr ||
        m_key_comparator_(KeyOfValue()(_value), _key(py)))
    {
        py->m_left_ = pz;   //  m_left == _leftmost() when py == m_header_
        if(py == m_header_)
        {
            _root() = pz;
            _rightmost() = pz;
        }
        else if(py == _leftmost())
            _leftmost() = pz;
    }
    else
    {
        py->m_right_ = pz;
        if(py == _rightmost())
            _rightmost() = pz;
    }
    pz->m_parent_ = py;
    pz->m_left_ = nullptr;
    pz->m_right_ = nullptr;
    Rb_tree_insert_rebalance(pz, _root());
    ++m_node_count_;
    return iterator(pz);
}

template <typename Key, typename Value, typename KeyOfValue, 
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_PNode_type
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::_Rb_copy(_Const_PNode_type _x, _PNode_type _p)
{
    _PNode_type top = _clone_node(_x);
    top->m_parent_ = _p;
    try {
        if(_right(_x))
            top->m_right_ = _Rb_copy(_right(_x), top);
        _p = top;
        _x = _left(_x);
        while(_x)
        {
            _PNode_type py = _clone_node(_x);
            _p->m_left_ = py;
            py->m_parent_ = _p;
            if(_right(_x))
                py->m_right_ = _Rb_copy(_right(_x), py);
            _p = py;
            _x = _left(_x);
        }
    } catch(...) {
        _Rb_erase(top);
        throw;
    }
    return top;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
void
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::_Rb_erase(_PNode_type _px)
{
    while(_px)
    {
        _Rb_erase(_right(_px));
        _PNode_type py = _left(_px);
        _destroy_node(_px);
        _px = py;
    }
}

/**
 *  Public Interface
 */
template <typename Key, typename Value, typename KeyOfValue, 
        typename Compare, typename Allocator>
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>&
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::operator=(const Rb_tree& other)
{
    if(this != &other)
    {
        clear();
        m_key_comparator_ = other.m_key_comparator_;
        if(other._root())
        {
            _root() = _Rb_copy(other._begin(), m_header_);
            _leftmost() = _minimum(_root());
            _rightmost() = _maximum(_root());
            m_node_count_ = other.m_node_count_;
        }
    }
    return *this;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::find(const key_type& _k)
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    while(px)
    {
        if(!m_key_comparator_(_key(px), _k))
        {
            py = px;
            px = _left(px);
        }
        else
            px = _right(px);
    }
    iterator result(py);
    return (result == end() || m_key_comparator_(_k, _key(py))) ?
            end() : result;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::find(const key_type& _k) const
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    while(px)
    {
        if(!m_key_comparator_(_key(px), _k))
        {
            py = px;
            px = _left(px);
        }
        else
            px = _right(px);
    }
    const_iterator result(py);
    return (result == cend() || m_key_comparator_(_k, _key(py))) ?
            cend() : result;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::count(const key_type& _k) const
{
    wt::pair<const_iterator, const_iterator> p = equal_range(_k);
    auto n = static_cast<size_type>(wt::distance(p.first, p.second));
    return n;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::lower_bound(const key_type& _k)
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    while(px)
    {
        if(!m_key_comparator_(_key(px), _k))
        {
            py = px;
            px = _left(px);
        }
        else
            px = _right(px);
    }
    return iterator(py);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::lower_bound(const key_type& _k) const
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    while(px)
    {
        if(!m_key_comparator_(_key(px), _k))
        {
            py = px;
            px = _left(px);
        }
        else
            px = _right(px);
    }
    return const_iterator(py);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::upper_bound(const key_type& _k)
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    while(px)
    {
        if(m_key_comparator_(_k, _key(px)))
        {
            py = px;
            px = _left(px);
        }
        else
            px = _right(px);
    }
    return iterator(py);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::upper_bound(const key_type& _k) const
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    while(px)
    {
        if(m_key_comparator_(_k, _key(px)))
        {
            py = px;
            px = _left(px);
        }
        else
            px = _right(px);
    }
    return const_iterator(py);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
wt::pair<typename Rb_tree<Key, Value, KeyOfValue, Compare, 
        Allocator>::iterator, bool>
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::insert_unique(const Value& _value)
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    bool insert_left = true;
    while(px)
    {
        py = px;
        insert_left = m_key_comparator_(KeyOfValue()(_value), _key(px));
        px = insert_left ? _left(px) : _right(px);
    }
    iterator piter(py);
    if(insert_left)
    {
        if(piter == begin())
            return wt::make_pair(_Rb_insert(px, py, _value), true);
        else
            --piter;
    }
    if(m_key_comparator_(_key(piter.m_pnode_), KeyOfValue()(_value)))
        return wt::make_pair(_Rb_insert(px, py, _value), true);
    return wt::make_pair(piter, false);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::insert_equal(const Value& _value)
{
    _PNode_type py = m_header_;
    _PNode_type px = _begin();
    while(px)
    {
        py = px;
        px = m_key_comparator_(KeyOfValue()(_value), _key(px)) ?
                _left(px) : _right(px);
    }
    return _Rb_insert(px, py, _value);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::insert_unique(const_iterator _hint, const Value& _value)
{
    if(_hint.m_pnode_ == m_header_->m_left_)    //  begin
    {
        if(size() > 0 && 
            m_key_comparator_(KeyOfValue()(_value), _key(_leftmost())))
            return _Rb_insert(_hint.m_pnode_, _leftmost(), _value);
        else
            return insert_unique(_value).first;
    }
    else if(_hint.m_pnode_ == m_header_)        //  end
    {
        if(m_key_comparator_(_key(_rightmost()), KeyOfValue()(_value)))
            return _Rb_insert(nullptr, _rightmost(), _value);
        else
            return insert_unique(_value).first;
    }
    else
    {
        const_iterator prior = _hint;
        --prior;
        if(m_key_comparator_(_key(prior.m_pnode_)), KeyOfValue()(_value) &&
            m_key_comparator_(KeyOfValue()(_value), _key(_hint.m_pnode_)))
        {
            if(_right(prior.m_pnode_))
                return _Rb_insert(_hint.m_pnode_, _hint.m_pnode_, _value);
            else
                return _Rb_insert(nullptr, prior.m_pnode_, _value);
        }
        else
            return insert_unique(_value).first;
    }
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::insert_equal(const_iterator _hint, const Value& _value)
{
    if(_hint.m_pnode_ == m_header_->m_left_)
    {
        if(size() > 0 && 
            !m_key_comparator_(_key(_leftmost()), KeyOfValue()(_value)))
            return _Rb_insert(_hint.m_pnode_, _leftmost(), _value);
        else
            return insert_equal(_value);
    }
    else if(_hint.m_pnode_ == m_header_)
    {
        if(!m_key_comparator_(KeyOfValue()(_value), _key(_rightmost())))
            return _Rb_insert(nullptr, _rightmost(), _value);
        else
            return insert_equal(_value);
    }
    else
    {
        const_iterator prior = _hint;
        --prior;
        if(!m_key_comparator_(KeyOfValue()(_value), _key(prior.m_pnode_)) &&
            !m_key_comparator_(_key(_hint.m_pnode_), KeyOfValue()(_value)))
        {
            if(_right(prior.m_pnode_))
                return _Rb_insert(_hint.m_pnode_, _hint.m_pnode_, _value);
            else
                return _Rb_insert(nullptr, prior.m_pnode_, _value);
        }
        else
            return insert_equal(_value);
    }
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
template <typename InputIter>
void
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::insert_unique(InputIter _first, InputIter _last)
{
    for(;_first != _last; ++_first)
        insert_unique(*_first);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
template <typename InputIter>
void
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::insert_equal(InputIter _first, InputIter _last)
{
    for(; _first != _last; ++_first)
        insert_equal(*_first);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::erase(const_iterator _pos)
{
    iterator result(_pos.m_pnode_);
    ++result;
    _PNode_type pnode = 
        static_cast<_PNode_type>(Rb_tree_erase_rebalance(_pos.m_pnode_,
          m_header_->m_parent_, m_header_->m_left_, m_header_->m_right_));
    _destroy_node(pnode);
    --m_node_count_;
    return result;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::erase(const_iterator _first, const_iterator _last)
{
    if(_first == cbegin() && _last == cend())
    {
        clear();
        return end();
    }
    // Note: _first is invalid after invoking earse(_first)
    // Wrong code !!!
    // for(;_first != _last; ++_first)
    //     erase(_first);
    for(; _first != _last; )
        erase(_first++);
    return iterator(_last.m_pnode_);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::erase(const key_type& _k)
{
    wt::pair<iterator, iterator> p = equal_range(_k);
    auto count = static_cast<size_type>(wt::distance(p.first, p.second));
    erase(p.first, p.second);
    return count;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
inline bool
operator==(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
    return lhs.size() == rhs.size() &&
            wt::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
inline bool
operator<(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
          const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
    return wt::lexicographical_compare(lhs.begin(), lhs.end(),
                                       rhs.begin(), rhs.end());
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
inline bool
operator!=(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
inline bool
operator<=(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
inline bool
operator>(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
          const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
inline bool
operator>=(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
void swap(Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs,
          Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs) noexcept
{
    lhs.swap(rhs);
}

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
bool
Rb_tree<Key, Value, KeyOfValue, Compare, Allocator>
::rb_verify() const
{
    if(size() == 0 || begin() == end())
        return m_node_count_ == 0 && begin() == end() && 
            _leftmost() == m_header_ && _rightmost() == m_header_ && 
            _root() == nullptr;

    int hight = Rb_black_count(_leftmost(), _root());
    for(auto iter = begin(); iter != end(); ++iter)
    {
        _PNode_type px = static_cast<_PNode_type>(iter.m_pnode_);
        _PNode_type pL = _left(px);
        _PNode_type pR = _right(px);

        if(_color(px) == _red())
            if((pL && _color(pL) == _red()) || (pR && _color(pR) == _red()))
                return false;

        if(pL && m_key_comparator_(_key(px), _key(pL)))
            return false;
        if(pR && m_key_comparator_(_key(pR), _key(px)))
            return false;
        if(!pL && !pR && Rb_black_count(px, _root()) != hight)
            return false;
    }

    if(_leftmost() != Rb_tree_node_base::minimum(_root()))
        return false;
    if(_rightmost() != Rb_tree_node_base::maximum(_root()))
        return false;
    return true;
}


template <typename Key, typename Value, typename KeyOfValue,
          typename Compare = wt::default_order_t<Key>,
          typename Allocator = wt::allocator<Value>>
class rb_tree;


template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
class rb_tree : public Rb_tree<Key, Value, KeyOfValue, Compare, Allocator> {
public:
    typedef Rb_tree<Key, Value, KeyOfValue, Compare, Allocator> _Base;
    typedef typename _Base::allocator_type           allocator_type;
    typedef typename _Base::key_type                 key_type;
    typedef typename _Base::value_type               value_type;
    typedef typename _Base::key_comare               key_comare;
    typedef typename _Base::pointer                  pointer;
    typedef typename _Base::const_pointer            const_pointer;
    typedef typename _Base::reference                reference;
    typedef typename _Base::const_reference          const_reference;
    typedef typename _Base::size_type                size_type;
    typedef typename _Base::difference_type          difference_type;
    typedef typename _Base::const_iterator           const_iterator;
    typedef typename _Base::iterator                 iterator;
    typedef typename _Base::const_reverse_iterator   const_reverse_iterator;
    typedef typename _Base::reverse_iterator         reverse_iterator;

    rb_tree(const Compare& _comp = Compare(), 
            const allocator_type& _alloc = allocator_type())
    : _Base(_comp, _alloc) { }
    ~rb_tree() { }
};

} // namespace wt


#endif