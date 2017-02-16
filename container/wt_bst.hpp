//
// Created by WT on 2017/2/6.
//

#ifndef _STL_WT_BST_HPP_
#define _STL_WT_BST_HPP_

namespace wt {

template <typename U>
struct BST_Node {
    BST_Node    *parent;
    BST_Node    *left, *right;
    U           value;
};

template <typename T>
class bst_const_iterator : public iterator<wt::bidirectional_iterator_tag, T>{
public:
    typedef bidirectional_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef const T *                       pointer;
    typedef const T &                       reference;
    typedef BST_Node <T>                    node_type;
    typedef bst_const_iterator<T>           _Self;
    bst_const_iterator() noexcept
    : nptr(nullptr) { }
    explicit bst_const_iterator(node_type *ptr)
    : nptr(ptr) { }
    bst_const_iterator(const _Self& other)
    : nptr(other.nptr) { }

    reference operator*() const
    {
        return nptr->value;
    }
    pointer operator->() const
    {
        return &(this->operator*());
    }
    _Self& operator++() noexcept
    {
        if(nptr->right)
        {
            nptr = nptr->right;
            while(nptr && nptr->left)
                nptr = nptr->left;
        }
        else
        {
            auto p = nptr->parent;
            while(p && p->right == nptr)
            {
                nptr = p;
                p = p->parent;
            }
            nptr = p;
        }
        return *this;
    }
    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        ++*this;
        return temp;
    }
    _Self& operator--() noexcept
    {
        if(nptr->left)
        {
            nptr = nptr->left;
            while(nptr && nptr->right)
                nptr = nptr->right;
        }
        else
        {
            auto p = nptr->parent;
            while(p && p->left == nptr)
            {
                nptr = p;
                p = p->parent;
            }
            nptr = p;
        }
        return *this;
    }
    _Self operator--(int) noexcept
    {
        _Self temp = *this;
        --*this;
        return temp;
    }

    bool operator==(const bst_const_iterator& other) const noexcept
    {
        return this->nptr == other.nptr;
    }

    bool operator!=(const bst_const_iterator& other) const noexcept
    {
        return this->nptr != other.nptr;
    }

    node_type *nptr;
};

template <typename T>
class bst_iterator : public bst_const_iterator<T> {
public:
    typedef bidirectional_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef T *                             pointer;
    typedef T &                             reference;
    typedef bst_iterator<T>                 _Self;
    typedef bst_const_iterator<T>           _Base;
    typedef typename _Base::node_type       node_type;

    using _Base::nptr;

    bst_iterator()
    : _Base() { }
    explicit bst_iterator(node_type *ptr)
    : _Base(ptr) { }
    bst_iterator(const _Self& other)
    : _Base(other.nptr) { }

    reference operator*() const noexcept
    {
        return nptr->value;
    }
    pointer operator->() const noexcept
    {
        return &(this->operator*());
    }
    _Self& operator++() noexcept
    {
        if(nptr->right)
        {
            nptr = nptr->right;
            while(nptr && nptr->left)
                nptr = nptr->left;
        }
        else
        {
            auto p = nptr->parent;
            while(p && p->right == nptr)
            {
                nptr = p;
                p = p->parent;
            }
            nptr = p;
        }
        return *this;
    }
    _Self operator++(int) noexcept
    {
        _Self temp = *this;
        ++*this;
        return temp;
    }
    _Self& operator--() noexcept
    {
        if(nptr->left)
        {
            nptr = nptr->left;
            while(nptr && nptr->right)
                nptr = nptr->right;
        }
        else
        {
            auto p = nptr->parent;
            while(p && p->left == nptr)
            {
                nptr = p;
                p = p->parent;
            }
            nptr = p;
        }
        return *this;
    }
    _Self operator--(int) noexcept
    {
        _Self temp = *this;
        --*this;
        return temp;
    }

    bool operator==(const bst_iterator& other) const noexcept
    {
        return this->nptr == other.nptr;
    }
    bool operator!=(const bst_iterator& other) const noexcept
    {
        return this->nptr != other.nptr;
    }
};
template <typename T, typename Allocator = wt::allocator<T>>
class binary_search_tree {

public:
    typedef Allocator               allocator_type;
    typedef BST_Node<T>             node_type;
    typedef T                       value_type;
    typedef size_t                  size_type;
    typedef bst_const_iterator<T>   const_iterator;
    typedef bst_iterator<T>         iterator;
    typedef wt::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef wt::reverse_iterator<iterator>          reverse_iterator;

    allocator_type get_allocator() const
    {
        return alloc_;
    }
    binary_search_tree()
    : alloc_(allocator_type()), root_(nullptr) { }
    binary_search_tree(const allocator_type& alloc)
    : alloc_(alloc), root_(nullptr) { }

    binary_search_tree(const binary_search_tree& ) = delete;
    binary_search_tree(binary_search_tree&& ) = delete;

    ~binary_search_tree()
    {
        clear();
    }

    binary_search_tree &operator=(const binary_search_tree&) = delete;
    binary_search_tree &operator=(binary_search_tree&&) = delete;

    const_iterator cbegin() const noexcept
    {
        return const_iterator(minimum(root_));
    }
    const_iterator begin() const noexcept
    {
        return const_iterator(minimum(root_));
    }
    iterator begin() noexcept
    {
        return iterator(minimum(root_));
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(nullptr);
    }
    const_iterator end() const noexcept
    {
        return const_iterator(nullptr);
    }
    iterator end() noexcept
    {
        return iterator(nullptr);
    }

    bool empty() const noexcept
    {
        return root_ == nullptr;
    }

    node_type* search(const T& val) const
    {
        auto cur = root_;
        while(cur && cur->value != val)
        {
            if(val < cur->value)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return cur;
    }

    const T& min() const
    {
        auto cur = root_;
        while(cur && cur->left)
            cur = cur->left;
        return cur->value;
    }

    const T& max() const
    {
        auto cur = root_;
        while(cur && cur->right)
            cur = cur->right;
        return cur->value;
    }

    node_type* prev(const node_type *pos) const
    {
        if(pos->left)
        {
            pos = pos->left;
            while(pos && pos->right)
                pos = pos->right;
            return pos;
        }
        auto p = pos->parent;
        while(p && pos == p->left)
        {
            pos = p;
            p = p->parent;
        }
        return p;
    }

    node_type* next(const node_type *pos) const
    {
        if(pos->right)
        {
            pos = pos->right;
            while(pos && pos->left)
                pos = pos->left;
            return pos;
        }
        auto p = pos->parent;
        while(p && pos == p->right)
        {
            pos = p;
            p = p->parent;
        }
        return p;
    }

    node_type* insert(value_type val)
    {
        auto inode = create_node(val);
        node_type *x = root_;
        node_type *y = nullptr;
        while(x)
        {
            y = x;
            if(inode->value < x->value)     // (1).
                x = x->left;
            else
                x = x->right;
        }
        inode->parent = y;
        if(y == nullptr)
            root_ = inode;
        else if(inode->value < y->value)    // (2). the order of comparison must be same as (1)
            y->left = inode;
        else
            y->right = inode;
        return inode;
    }

    void erase(node_type* pos)
    {
        if(pos->left == nullptr)
            transform(pos, pos->right);
        else if(pos->right == nullptr)
            transform(pos, pos->left);
        else
        {
            auto y = pos->right;
            while(y && y->left)
                y = y->left;
            if(y != pos->right)
            {
                transform(y, y->right);
                y->right = pos->right;
                y->right->parent = y;
            }
            transform(pos, y);
            y->left = pos->left;
            y->left->parent = y;
        }
        destroy_node(pos);
    }

    void clear()
    {
        while(root_)
            erase(root_);
    }
private:
    node_type* create_node(const T& val)
    {
        node_type* temp = alloc_.allocate(1);
        try {
            wt::construct(&temp->value, val);
        } catch(...) {
            alloc_.deallocate(temp, 1);
        }
        temp->parent = nullptr;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }

    void destroy_node(node_type *p)
    {
        wt::destroy(&p->value);
        alloc_.deallocate(p, 1);
    }

    void transform(node_type *u, node_type *v)
    {
        if(u->parent == nullptr)
            root_ = v;
        else if(u->parent->left == u)
            u->parent->left = v;
        else
            u->parent->right = v;
        if(v)
            v->parent = u->parent;
    }

    node_type* minimum(node_type *x) const
    {
        while(x && x->left)
            x = x->left;
        return x;
    }

    node_type* maximum(node_type *x) const
    {
        while(x && x->right)
            x = x->right;
        return x;
    }
private:
    typename Allocator::template rebind<node_type>::other
                    alloc_;
    node_type       *root_;
};


} // namespace wt

#endif
