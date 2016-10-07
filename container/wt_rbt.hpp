#ifndef _STL_WT_RBT_HPP_
#define _STL_WT_RBT_HPP_

namespace wt {


template <typename Key, typename Value, typename KeyOfValue,
          typename Compare = wt::default_order_t<Key>,
          typename Allocator = wt::allocator<Value>>
class rb_tree;

template <typename Key, typename Value, typename KeyOfValue,
        typename Compare, typename Allocator>
class rb_tree : public Rb_tree<Key, Value, KeyOfValue, Compare, Allocator> {
public:
    typedef Rb_tree<Key, Value, KeyOfValue, Compare, Allocator> _Impl_type;
    typedef typename _Impl_type::allocator_type           allocator_type;
    typedef typename _Impl_type::key_type                 key_type;
    typedef typename _Impl_type::value_type               value_type;
    typedef typename _Impl_type::key_comare               key_comare;
    typedef typename _Impl_type::pointer                  pointer;
    typedef typename _Impl_type::const_pointer            const_pointer;
    typedef typename _Impl_type::reference                reference;
    typedef typename _Impl_type::const_reference          const_reference;
    typedef typename _Impl_type::size_type                size_type;
    typedef typename _Impl_type::difference_type          difference_type;
    typedef typename _Impl_type::const_iterator           const_iterator;
    typedef typename _Impl_type::iterator                 iterator;
    typedef typename _Impl_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename _Impl_type::reverse_iterator         reverse_iterator;

    rb_tree(const Compare& _comp = Compare(), 
            const allocator_type& _alloc = allocator_type())
    : _Impl_type(_comp, _alloc) { }
    ~rb_tree() { }
};

} // namespace wt

#endif