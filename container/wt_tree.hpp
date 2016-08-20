#ifndef _STL_WT_TREE_HPP_
#define _STL_WT_TREE_HPP_

namespace wt {

enum class RBColor {
    red     = false,
    black   = true
};

struct Rb_tree_node_base {
    typedef Rb_tree_node_base*           _Base_ptr;
    typedef const Rb_tree_node_base*     _Const_Base_ptr;

    RBColor         m_color_;
    _Base_ptr       m_parent_;
    _Base_ptr       m_left_;
    _Base_ptr       m_right_;

    static _Base_ptr minimum(_Base_ptr _node) noexcept
    {
        while(_node->m_left_ != nullptr)
            _node = _node->m_left_;
        return _node;
    }

    static _Const_Base_ptr minimum(_Const_Base_ptr _node) noexcept
    {
        while(_node->m_left_ != nullptr)
            _node = _node->m_left_;
        return _node;
    }

    static _Base_ptr maximum(_Base_ptr _node) noexcept
    {
        while(_node->m_right_ != nullptr)
            _node = _node->m_right_;
        return _node;
    }

    static _Const_Base_ptr maximum(_Const_Base_ptr _node) noexcept
    {
        while(_node->m_right_ != nullptr)
            _node = _node->m_right_;
        return _node;
    }
};

template <typename T>
class Rb_tree_node : public Rb_tree_node_base {
public:
    typedef Rb_tree_node<T>*    _Node_ptr;

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

inline Rb_tree_node_base*
Rb_tree_increment(Rb_tree_node_base* _node)
{
    return nullptr;
}

inline const Rb_tree_node_base*
Rb_tree_increment(const Rb_tree_node_base* _node)
{
    return nullptr;
}

inline Rb_tree_node_base*
Rb_tree_decrement(Rb_tree_node_base* _node)
{
    return nullptr;
}

inline const Rb_tree_node_base*
Rb_tree_decrement(const Rb_tree_node_base* _node)
{
    return nullptr;
}















} // namespace wt


#endif