//
// Created by WT on 2017/2/16.
//

#ifndef _STL_WT_AVL_TREE_HPP_
#define _STL_WT_AVL_TREE_HPP_

namespace wt {

template <typename T>
struct AVL_Node {
    T           key;
    int         height;
    AVL_Node    *parent;
    AVL_Node    *left;
    AVL_Node    *right;
};

template <typename T>
class avl_const_iterator : public iterator<wt::bidirectional_iterator_tag, T> {
public:
    typedef wt::bidirectional_iterator_tag      iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef const T&                            reference;
    typedef const T*                            pointer;
    typedef AVL_Node<T>                         node_type;
    typedef avl_const_iterator<T>               _Self;

    avl_const_iterator()
    : node_(nullptr) { }
    explicit avl_const_iterator(node_type *ptr)
    : node_(ptr) { }
    avl_const_iterator(const avl_const_iterator& other)
    : node_(other.node_) { }

    reference operator*() const noexcept
    {
        return node_->key;
    }
    pointer operator->() const noexcept
    {
        return &(this->operator*());
    }
    _Self& operator++() noexcept
    {
        if(node_->right)
        {
            node_ = node_->right;
            while(node_ && node_->left)
                node_ = node_->left;
        }
        else
        {
            auto y = node_->parent;
            while(y && node_ == y->right)
            {
                node_ = y;
                y = y->parent;
            }
            node_ = y;
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
        if(node_->left)
        {
            node_ = node_->left;
            while(node_ && node_->right)
                node_ = node_->right;
        }
        else
        {
            auto y = node_->parent;
            while(y && node_ == y->left)
            {
                node_ = y;
                y = y->parent;
            }
            node_ = y;
        }
        return *this;
    }
    _Self operator--(int) noexcept
    {
        _Self temp = *this;
        --*this;
        return temp;
    }

    bool operator==(const avl_const_iterator& other) const noexcept
    {
        return this->node_ == other.node_;
    }
    bool operator!=(const avl_const_iterator& other) const noexcept
    {
        return this->node_ != other.node_;
    }

    node_type *node_;
};

template <typename T>
class avl_iterator : public avl_const_iterator<T> {
public:
    typedef wt::bidirectional_iterator_tag  iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef T&                              reference;
    typedef T*                              pointer;
    typedef avl_const_iterator<T>           _Base;
    typedef avl_iterator<T>                 _Self;
    typedef typename _Base::node_type       node_type;

    using _Base::node_;

    avl_iterator()
    : _Base(nullptr) { }
    explicit avl_iterator(node_type *ptr)
    : _Base(ptr) { }
    avl_iterator(const avl_iterator& other)
    : _Base(other.node_) { }

    reference operator*() const noexcept
    {
        return node_->key;
    }
    pointer operator->() const noexcept
    {
        return &(this->operator*());
    }
    _Self& operator++() noexcept
    {
        if(node_->right)
        {
            node_ = node_->right;
            while(node_ && node_->left)
                node_ = node_->left;
        }
        else
        {
            auto y = node_->parent;
            while(y && node_ == y->right)
            {
                node_ = y;
                y = y->parent;
            }
            node_ = y;
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
        if(node_->left)
        {
            node_ = node_->left;
            while(node_ && node_->right)
                node_ = node_->right;
        }
        else
        {
            auto y = node_->parent;
            while(y && node_ == y->left)
            {
                node_ = y;
                y = y->parent;
            }
            node_ = y;
        }
        return *this;
    }
    _Self operator--(int) noexcept
    {
        _Self temp = *this;
        --*this;
        return temp;
    }

    bool operator==(const avl_iterator& other) const noexcept
    {
        return this->node_ == other.node_;
    }
    bool operator!=(const avl_iterator& other) const noexcept
    {
        return this->node_ != other.node_;
    }
};

template <typename T, typename Allocator = wt::allocator<T>>
class avl_tree {
public:
    typedef Allocator                   allocator_type;
    typedef T                           value_type;
    typedef AVL_Node<T>                 node_type;
    typedef avl_const_iterator<T>       const_iterator;
    typedef avl_iterator<T>             iterator;

    allocator_type get_allocator() const
    {
        return alloc_;
    }
    avl_tree()
    : alloc_(allocator_type()), root_(nullptr) { }
    avl_tree(const allocator_type& alloc)
    : alloc_(alloc), root_(nullptr) { }
    ~avl_tree()
    {
        clear();
    }

    avl_tree(const avl_tree&) = delete;
    avl_tree(avl_tree&&) = delete;
    avl_tree& operator=(const avl_tree&) = delete;
    avl_tree& operator=(avl_tree&&) = delete;

    bool empty() const noexcept
    {
        return root_ == nullptr;
    }

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

    int height() const
    {
        return height(root_);
    }

    int height(const_iterator pos) const
    {
        return height(pos.node_);
    }

    iterator search(const T& key)
    {
        return iterator(search(root_, key));
    }
    const_iterator search(const T& key) const
    {
        return const_iterator(search(root_, key));
    }

    const T& minimum() const
    {
        return minimum(root_)->key;
    }

    const T& maximum() const
    {
        return maximum(root_)->key;
    }

    iterator insert(const T& key)
    {
        auto x = create_node(key);
        insert(x);
        return iterator(x);
    }

    void erase(const_iterator pos)
    {
        auto x = search(root_, pos.node_);
        if(x != nullptr)
        {
            x = erase(root_, x);
            destroy_node(x);
        }
    }

    void clear()
    {
        if(root_ != nullptr)
        {
            erase(root_);
            root_ = nullptr;
        }
    }
private:
    node_type* create_node(const T& val)
    {
        node_type *p = alloc_.allocate(1);
        try {
            wt::construct(&p->key, val);
        } catch(...) {
            alloc_.deallocate(p, 1);
        }
        p->height = 1;
        p->parent = nullptr;
        p->left = nullptr;
        p->right = nullptr;
        return p;
    }
    void destroy_node(node_type *p)
    {
        wt::destroy(&p->key);
        alloc_.deallocate(p, 1);
    }

    int height(node_type *node) const
    {
        return node == nullptr ? 0 : node->height;
    }

    int max_height(node_type *t1, node_type *t2) const
    {
        int h1 = height(t1);
        int h2 = height(t2);
        return h1 < h2 ? h2 : h1;
    }

    node_type* search(node_type *tree, const T& key) const
    {
        while(tree && tree->key != key)
        {
            if(key < tree->key)
                tree = tree->left;
            else
                tree = tree->right;
        }
        return tree;
    }

    node_type* search(node_type *tree, node_type *x) const
    {
        while(tree && tree != x)
        {
            if(x->key < tree->key)
                tree = tree->left;
            else
                tree = tree->right;
        }
        return tree;
    }

    node_type* minimum(node_type *tree) const
    {
        while(tree && tree->left)
            tree = tree->left;
        return tree;
    }

    node_type* maximum(node_type *tree) const
    {
        while(tree && tree->right)
            tree = tree->right;
        return tree;
    }

    node_type* rotate_right(node_type *x)
    {
        auto y = x->left;
        x->left = y->right;
        if(y->right)
            y->right->parent = x;
        y->parent = x->parent;
        if(x->parent == nullptr)
            root_ = y;
        else if(x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->right = x;
        x->parent = y;
        //  update height
        x->height = max_height(x->left, x->right) + 1;
        y->height = max_height(y->left, y->right) + 1;
        return y;
    }

    node_type* rotate_left(node_type *x)
    {
        auto y = x->right;
        x->right = y->left;
        if(y->left)
            y->left->parent = x;
        y->parent = x->parent;
        if(x->parent == nullptr)
            root_ = y;
        else if(x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
        //  update height
        x->height = max_height(x->left, x->right) + 1;
        y->height = max_height(y->left, y->right) + 1;
        return y;
    }

    void LL(node_type *x)
    {
        rotate_right(x);
    }
    void RR(node_type *x)
    {
        rotate_left(x);
    }
    void LR(node_type *x)
    {
        rotate_left(x->left);
        rotate_right(x);
    }
    void RL(node_type *x)
    {
        rotate_right(x->right);
        rotate_left(x);
    }

    void insert(node_type *x)
    {
        node_type *y = nullptr;
        node_type *cur = root_;
        while(cur)
        {
            y = cur;
            if(x->key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        x->parent = y;
        if(y == nullptr)
            root_ = x;
        else if(x->key < y->key)
            y->left = x;
        else
            y->right = x;
        // update height
        while(y)
        {
            int diff = height(y->left) - height(y->right);
            if(diff == 2)
            {
                if(x->key < y->left->key)
                    LL(y);
                else
                    LR(y);
            }
            else if(diff == -2)
            {
                if(x->key < y->right->key)
                    RL(y);
                else
                    RR(y);
            }
            y->height = max_height(y->left, y->right) + 1;
            y = y->parent;
        }
    }

    void transform(node_type *x, node_type *y)
    {
        if(y != nullptr)
            y->parent = x->parent;
        if(x->parent == nullptr)
            root_ = y;
        else if(x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
        // rebalance avl-tree
        y = x->parent;
        while(y)
        {
            int diff = height(y->left) - height(y->right);
            if(diff == 2)
            {
                if(height(y->left->left) > height(y->left->right))
                    LL(y);
                else
                    LR(y);
            }
            else if(diff == -2)
            {
                if(height(y->right->left) > height(y->right->right))
                    RL(y);
                else
                    RR(y);
            }
            y->height = max_height(y->left, y->right) + 1;
            y = y->parent;
        }
    }

    node_type* erase(node_type *tree, node_type *x)
    {
        node_type *cur = tree;
        while(cur != x)
        {
            if(x->key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if(cur->left == nullptr)
            transform(cur, cur->right);
        else if(cur->right == nullptr)
            transform(cur, cur->left);
        else
        {
            if(height(cur->left) > height(cur->right))
            {
                x = maximum(cur->left);
                cur->key = x->key;
                erase(cur->left, x);
            }
            else
            {
                x = minimum(cur->right);
                cur->key = x->key;
                erase(cur->right, x);
            }
        }
        return x;
    }

    void erase(node_type *x)
    {
        if(x == nullptr)
            return;
        erase(x->left);
        erase(x->right);
        destroy_node(x);
    }
private:
    typename Allocator::template rebind<node_type>::other
                alloc_;
    node_type   *root_;
};

} // namespace wt

#endif //_STL_WT_AVL_TREE_HPP_
