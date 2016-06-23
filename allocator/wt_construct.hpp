
#ifndef _STL_WT_CONSTRUCT_HPP_
#define _STL_WT_CONSTRUCT_HPP_

/**
 *  depend on:
 *            "type_traits.hpp"
 *            "utility/wt_utility.hpp"            
 *            "/iterator/wt_iterator_base.hpp"
 *            
 */

namespace wt{

template <typename T1,typename T2>
inline void construct(T1* _p,const T2& _value)
{
	new (_p) T1(_value);
}


template <typename T>
inline void construct(T* _p)
{
	new (_p) T();
}

template <typename T>
inline void destroy(T* _p)
{
	_p->~T();
}

template <typename ForwardIterator>
inline void destroy_aux(ForwardIterator _first,ForwardIterator _last,wt::true_type)
{

}

template <typename ForwardIterator>
void destroy_aux(ForwardIterator _first,ForwardIterator _last,wt::false_type)
{
	for(; _first != _last; ++_first)
	{
		destroy(&(*_first));
	}
}

template <typename ForwardIterator,typename T>
inline void destroy(ForwardIterator _first,ForwardIterator _last,T*)
{
	destroy_aux(_first,_last,is_trivially_destructible<T>());
}

template <typename ForwardIterator>
inline void destroy(ForwardIterator _first,ForwardIterator _last)
{
	destroy(_first,_last,_VALUE_TYPE(_first));
}

inline void destroy(char*, char*) {}
inline void destroy(int*, int&) {}
inline void destroy(long*, long&) {}
inline void destroy(float*,float*) {}
inline void destroy(double*, double*) {}


}

#endif