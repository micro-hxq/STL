#ifndef _STL_WT_HASH_TABLE_HPP_
#define _STL_WT_HASH_TABLE_HPP_

namespace wt {

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash = wt::hash<Key>,
          typename Equal = wt::equal_to<Key>, 
          typename Allocator = wt::allocator<Value>>
class hash_table;

template <typename Key, typename Value, typename KeyOfValue,
          typename Hash, typename Equal, typename Allocator>
class hash_table 
    : public wt::hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator>{
public:
    typedef wt::hashtable<Key, Value, KeyOfValue, Hash, Equal, Allocator> _Base;
    typedef typename _Base::key_type                    key_type;
    typedef typename _Base::value_type                  value_type;
    typedef typename _Base::size_type                   size_type;
    typedef typename _Base::difference_type             difference_type;
    typedef typename _Base::hasher                      hasher;
    typedef typename _Base::key_equal                   key_equal;
    typedef typename _Base::allocator_type              allocator_type;
    typedef typename _Base::reference                   reference;
    typedef typename _Base::const_reference             const_reference;
    typedef typename _Base::pointer                     pointer;
    typedef typename _Base::const_pointer               const_pointer;
    typedef typename _Base::iterator                    iterator;
    typedef typename _Base::const_iterator              const_iterator;
    typedef typename _Base::local_iterator              local_iterator;
    typedef typename _Base::const_local_iterator        const_local_iterator;

    hash_table(size_type _count, 
               const hasher& _hash,
               const key_equal& _equal,
               const KeyOfValue& _get_key ,
               const allocator_type& _alloc = allocator_type())
    : _Base(_count, _hash, _equal, _get_key, _alloc) { }

    hash_table(size_type _count,
               const hasher& _hash,
               const key_equal& _equal,
               const allocator_type& _alloc = allocator_type())
    : _Base(_count, _hash, _equal, _alloc) { }

    hash_table(const hash_table& other)
    : _Base(other) { }

    hash_table(hash_table&& other) noexcept
    {
        _Base::swap(other);
    }

    hash_table& operator=(const hash_table& other)
    {
        _Base::operator=(other);
        return *this;
    }

    hash_table& operator=(hash_table&& other) noexcept
    {
        _Base::operator=(wt::move(other));
        return *this;
    }

    ~hash_table() { }
};



} // namespace wt



#endif