#ifndef _WT_TYPE_TRAITS_HPP_
#define _WT_TYPE_TRAITS_HPP_

namespace wt{

template<typename T,T v>
struct integral_constant{
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant<T,v>;
    constexpr operator value_type() const noexcept
    {
        return value;
    }
    constexpr value_type operator()() const noexcept
    {
        return value;
    }
};

template<bool B>
using bool_constant = integral_constant<bool,B>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

template <typename T> struct is_integral : false_type{};
// template <typename T> struct is_void : false_type{};
// template <typename T> struct is_null_pointer : false_type{};
// template <typename T> struct is_floating_point : false_type{};
// template <typename T> struct is_array : false_type{};
// template <typename T> struct is_enum : false_type{};
// template <typename T> struct is_union : false_type{};
// template <typename T> struct is_class : false_type{};
// template <typename T> struct is_function : false_type{};
// template <typename T> struct is_pointer : false_type{};
// template <typename T> struct is_lvalue_reference : false_type{};
// template <typename T> struct is_rvalue_reference : false_type{};
// template <typename T> struct is_member_object_pointer : false_type{};
// template <typename T> struct is_member_function_pointer : false_type{};

// template <typename T> struct is_fundamental : false_type{};
// template <typename T> struct is_arithmetic : false_type{};
// template <typename T> struct is_scalar : false_type{};
// template <typename T> struct is_object : false_type{};
// template <typename T> struct is_compound : false_type{};
// template <typename T> struct is_reference : false_type{};
// template <typename T> struct is_member_pointer : false_type{};

// template <typename T> struct is_const : false_type{};
// template <typename T> struct is_volatile : false_type{};
// template <typename T> struct is_standard_layout : false_type{};
// template <typename T> struct is_pod : false_type{};
// template <typename T> struct is_literal_type : false_type{};
// template <typename T> struct is_empty : false_type{};
// template <typename T> struct is_polymorphic : false_type{};
// template <typename T> struct is_final : false_type{};
// template <typename T> struct is_abstract : false_type{};
// template <typename T> struct is_signed : false_type{};
// template <typename T> struct is_unsigned : false_type{};

template <typename T> struct is_trivially_default_constructible : false_type{};
template <typename T> struct is_trivially_copy_constructible : false_type{};
template <typename T> struct is_trivially_move_constructible : false_type{};
template <typename T> struct is_trivially_copy_assignable : false_type{};
template <typename T> struct is_trivially_move_assignable : false_type{};
template <typename T> struct is_trivially_destructible : false_type{};
template <typename T> struct is_pod : false_type{};

// partial specilization
template <> struct is_trivially_default_constructible<bool> : true_type{};
template <> struct is_trivially_default_constructible<char> : true_type{};
template <> struct is_trivially_default_constructible<signed char> : true_type{};
template <> struct is_trivially_default_constructible<unsigned char> : true_type{};
template <> struct is_trivially_default_constructible<wchar_t> : true_type{};
template <> struct is_trivially_default_constructible<short> : true_type{};
template <> struct is_trivially_default_constructible<unsigned short> : true_type{};
template <> struct is_trivially_default_constructible<int> : true_type{};
template <> struct is_trivially_default_constructible<unsigned int> : true_type{};
template <> struct is_trivially_default_constructible<long> : true_type{};
template <> struct is_trivially_default_constructible<unsigned long> : true_type{};
template <> struct is_trivially_default_constructible<long long> : true_type{};
template <> struct is_trivially_default_constructible<unsigned long long> : true_type{};
template <> struct is_trivially_default_constructible<float> : true_type{};
template <> struct is_trivially_default_constructible<double> : true_type{};
template <> struct is_trivially_default_constructible<long double> : true_type{};
template <> struct is_trivially_default_constructible<char*> : true_type{};
template <> struct is_trivially_default_constructible<signed char*> : true_type{};
template <> struct is_trivially_default_constructible<unsigned char*> : true_type{};
template <> struct is_trivially_default_constructible<const char*> : true_type{};
template <> struct is_trivially_default_constructible<const signed char*> : true_type{};
template <> struct is_trivially_default_constructible<const unsigned char*> : true_type{};
template <typename Tp> 
struct is_trivially_default_constructible<Tp*> : true_type{};

template <> struct is_trivially_copy_constructible<bool> : true_type{};
template <> struct is_trivially_copy_constructible<char> : true_type{};
template <> struct is_trivially_copy_constructible<signed char> : true_type{};
template <> struct is_trivially_copy_constructible<unsigned char> : true_type{};
template <> struct is_trivially_copy_constructible<wchar_t> : true_type{};
template <> struct is_trivially_copy_constructible<short> : true_type{};
template <> struct is_trivially_copy_constructible<unsigned short> : true_type{};
template <> struct is_trivially_copy_constructible<int> : true_type{};
template <> struct is_trivially_copy_constructible<unsigned int> : true_type{};
template <> struct is_trivially_copy_constructible<long> : true_type{};
template <> struct is_trivially_copy_constructible<unsigned long> : true_type{};
template <> struct is_trivially_copy_constructible<long long> : true_type{};
template <> struct is_trivially_copy_constructible<unsigned long long> : true_type{};
template <> struct is_trivially_copy_constructible<float> : true_type{};
template <> struct is_trivially_copy_constructible<double> : true_type{};
template <> struct is_trivially_copy_constructible<long double> : true_type{};
template <> struct is_trivially_copy_constructible<char*> : true_type{};
template <> struct is_trivially_copy_constructible<signed char*> : true_type{};
template <> struct is_trivially_copy_constructible<unsigned char*> : true_type{};
template <> struct is_trivially_copy_constructible<const char*> : true_type{};
template <> struct is_trivially_copy_constructible<const signed char*> : true_type{};
template <> struct is_trivially_copy_constructible<const unsigned char*> : true_type{};
template <typename Tp> 
struct is_trivially_copy_constructible<Tp*> : true_type{};

template <> struct is_trivially_move_constructible<bool> : true_type{};
template <> struct is_trivially_move_constructible<char> : true_type{};
template <> struct is_trivially_move_constructible<signed char> : true_type{};
template <> struct is_trivially_move_constructible<unsigned char> : true_type{};
template <> struct is_trivially_move_constructible<wchar_t> : true_type{};
template <> struct is_trivially_move_constructible<short> : true_type{};
template <> struct is_trivially_move_constructible<unsigned short> : true_type{};
template <> struct is_trivially_move_constructible<int> : true_type{};
template <> struct is_trivially_move_constructible<unsigned int> : true_type{};
template <> struct is_trivially_move_constructible<long> : true_type{};
template <> struct is_trivially_move_constructible<unsigned long> : true_type{};
template <> struct is_trivially_move_constructible<long long> : true_type{};
template <> struct is_trivially_move_constructible<unsigned long long> : true_type{};
template <> struct is_trivially_move_constructible<float> : true_type{};
template <> struct is_trivially_move_constructible<double> : true_type{};
template <> struct is_trivially_move_constructible<long double> : true_type{};
template <> struct is_trivially_move_constructible<char*> : true_type{};
template <> struct is_trivially_move_constructible<signed char*> : true_type{};
template <> struct is_trivially_move_constructible<unsigned char*> : true_type{};
template <> struct is_trivially_move_constructible<const char*> : true_type{};
template <> struct is_trivially_move_constructible<const signed char*> : true_type{};
template <> struct is_trivially_move_constructible<const unsigned char*> : true_type{};
template <typename Tp> 
struct is_trivially_move_constructible<Tp*> : true_type{};

template <> struct is_trivially_copy_assignable<bool> : true_type{};
template <> struct is_trivially_copy_assignable<char> : true_type{};
template <> struct is_trivially_copy_assignable<signed char> : true_type{};
template <> struct is_trivially_copy_assignable<unsigned char> : true_type{};
template <> struct is_trivially_copy_assignable<wchar_t> : true_type{};
template <> struct is_trivially_copy_assignable<short> : true_type{};
template <> struct is_trivially_copy_assignable<unsigned short> : true_type{};
template <> struct is_trivially_copy_assignable<int> : true_type{};
template <> struct is_trivially_copy_assignable<unsigned int> : true_type{};
template <> struct is_trivially_copy_assignable<long> : true_type{};
template <> struct is_trivially_copy_assignable<unsigned long> : true_type{};
template <> struct is_trivially_copy_assignable<long long> : true_type{};
template <> struct is_trivially_copy_assignable<unsigned long long> : true_type{};
template <> struct is_trivially_copy_assignable<float> : true_type{};
template <> struct is_trivially_copy_assignable<double> : true_type{};
template <> struct is_trivially_copy_assignable<long double> : true_type{};
template <> struct is_trivially_copy_assignable<char*> : true_type{};
template <> struct is_trivially_copy_assignable<signed char*> : true_type{};
template <> struct is_trivially_copy_assignable<unsigned char*> : true_type{};
template <> struct is_trivially_copy_assignable<const char*> : true_type{};
template <> struct is_trivially_copy_assignable<const signed char*> : true_type{};
template <> struct is_trivially_copy_assignable<const unsigned char*> : true_type{};
template <typename Tp> 
struct is_trivially_copy_assignable<Tp*> : true_type{};

template <> struct is_trivially_move_assignable<bool> : true_type{};
template <> struct is_trivially_move_assignable<char> : true_type{};
template <> struct is_trivially_move_assignable<signed char> : true_type{};
template <> struct is_trivially_move_assignable<unsigned char> : true_type{};
template <> struct is_trivially_move_assignable<wchar_t> : true_type{};
template <> struct is_trivially_move_assignable<short> : true_type{};
template <> struct is_trivially_move_assignable<unsigned short> : true_type{};
template <> struct is_trivially_move_assignable<int> : true_type{};
template <> struct is_trivially_move_assignable<unsigned int> : true_type{};
template <> struct is_trivially_move_assignable<long> : true_type{};
template <> struct is_trivially_move_assignable<unsigned long> : true_type{};
template <> struct is_trivially_move_assignable<long long> : true_type{};
template <> struct is_trivially_move_assignable<unsigned long long> : true_type{};
template <> struct is_trivially_move_assignable<float> : true_type{};
template <> struct is_trivially_move_assignable<double> : true_type{};
template <> struct is_trivially_move_assignable<long double> : true_type{};
template <> struct is_trivially_move_assignable<char*> : true_type{};
template <> struct is_trivially_move_assignable<signed char*> : true_type{};
template <> struct is_trivially_move_assignable<unsigned char*> : true_type{};
template <> struct is_trivially_move_assignable<const char*> : true_type{};
template <> struct is_trivially_move_assignable<const signed char*> : true_type{};
template <> struct is_trivially_move_assignable<const unsigned char*> : true_type{};
template <typename Tp> 
struct is_trivially_move_assignable<Tp*> : true_type{};

template <> struct is_trivially_destructible<bool> : true_type{};
template <> struct is_trivially_destructible<char> : true_type{};
template <> struct is_trivially_destructible<signed char> : true_type{};
template <> struct is_trivially_destructible<unsigned char> : true_type{};
template <> struct is_trivially_destructible<wchar_t> : true_type{};
template <> struct is_trivially_destructible<short> : true_type{};
template <> struct is_trivially_destructible<unsigned short> : true_type{};
template <> struct is_trivially_destructible<int> : true_type{};
template <> struct is_trivially_destructible<unsigned int> : true_type{};
template <> struct is_trivially_destructible<long> : true_type{};
template <> struct is_trivially_destructible<unsigned long> : true_type{};
template <> struct is_trivially_destructible<long long> : true_type{};
template <> struct is_trivially_destructible<unsigned long long> : true_type{};
template <> struct is_trivially_destructible<float> : true_type{};
template <> struct is_trivially_destructible<double> : true_type{};
template <> struct is_trivially_destructible<long double> : true_type{};
template <> struct is_trivially_destructible<char*> : true_type{};
template <> struct is_trivially_destructible<signed char*> : true_type{};
template <> struct is_trivially_destructible<unsigned char*> : true_type{};
template <> struct is_trivially_destructible<const char*> : true_type{};
template <> struct is_trivially_destructible<const signed char*> : true_type{};
template <> struct is_trivially_destructible<const unsigned char*> : true_type{};
template <typename Tp> 
struct is_trivially_destructible<Tp*> : true_type{};

template <> struct is_pod<bool> : true_type{};
template <> struct is_pod<char> : true_type{};
template <> struct is_pod<signed char> : true_type{};
template <> struct is_pod<unsigned char> : true_type{};
template <> struct is_pod<wchar_t> : true_type{};
template <> struct is_pod<short> : true_type{};
template <> struct is_pod<unsigned short> : true_type{};
template <> struct is_pod<int> : true_type{};
template <> struct is_pod<unsigned int> : true_type{};
template <> struct is_pod<long> : true_type{};
template <> struct is_pod<unsigned long> : true_type{};
template <> struct is_pod<long long> : true_type{};
template <> struct is_pod<unsigned long long> : true_type{};
template <> struct is_pod<float> : true_type{};
template <> struct is_pod<double> : true_type{};
template <> struct is_pod<long double> : true_type{};
template <> struct is_pod<char*> : true_type{};
template <> struct is_pod<signed char*> : true_type{};
template <> struct is_pod<unsigned char*> : true_type{};
template <> struct is_pod<const char*> : true_type{};
template <> struct is_pod<const signed char*> : true_type{};
template <> struct is_pod<const unsigned char*> : true_type{};
template <typename Tp> 
struct is_pod<Tp*> : true_type{};

template <> struct is_integral<bool> : true_type{};
template <> struct is_integral<char> : true_type{};
template <> struct is_integral<signed char> : true_type{};
template <> struct is_integral<unsigned char> : true_type{};
template <> struct is_integral<wchar_t> : true_type{};
template <> struct is_integral<short> : true_type{};
template <> struct is_integral<unsigned short> : true_type{};
template <> struct is_integral<int> : true_type{};
template <> struct is_integral<unsigned int> : true_type{};
template <> struct is_integral<long> : true_type{};
template <> struct is_integral<unsigned long> : true_type{};
template <> struct is_integral<long long> : true_type{};
template <> struct is_integral<unsigned long long> : true_type{};

//////////////////////
// remove_reference //
//////////////////////
template <typename T>
struct remove_reference {
    typedef T   type;
};

template <typename T>
struct remove_reference<T&> {
    typedef T   type;
};

template <typename T>
struct remove_reference<T&&> {
    typedef T   type;
};

// alias
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

} // namespace wt


#endif