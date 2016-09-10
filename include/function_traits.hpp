#ifndef FUNCTION_TRAITS_HPP_INCLUDED
#define FUNCTION_TRAITS_HPP_INCLUDED

#include <functional>
#include <tuple>

/*
 * This is mostly taken from
 * https://github.com/kennytm/utils/blob/master/traits.hpp
 *
 * But with the lambda function decomposition fixed and an additional tuple_type type added
 * */

namespace fn_traits {
    template <typename Functor>
    struct function_traits
        : public function_traits<decltype( &Functor::operator())> {
    };

    template <typename R, typename... Args>
    struct function_traits<R( Args... )> {
        typedef R result_type;

        typedef result_type return_type;

        typedef result_type function_type( Args... );

        enum {
            arity = sizeof...( Args )
        };

        typedef std::tuple<Args...> tuple_type;

        template <size_t i>
        struct arg {
            typedef typename std::tuple_element<i, tuple_type>::type type;
        };
    };

    template <typename R, typename... Args>
    struct function_traits<R( * )( Args... )>
        : public function_traits<R( Args... )> {
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<R( C::* )( Args... )>
        : public function_traits<R( Args... )> {
        typedef C &owner_type;
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<R( C::* )( Args... ) const>
        : public function_traits<R( Args... )> {
        typedef const C &owner_type;
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<R( C::* )( Args... ) volatile>
        : public function_traits<R( Args... )> {
        typedef volatile C &owner_type;
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<R( C::* )( Args... ) const volatile>
        : public function_traits<R( Args... )> {
        typedef const volatile C &owner_type;
    };

#if defined(_GLIBCXX_FUNCTIONAL)
#define MEM_FN_SYMBOL std::_Mem_fn
#elif defined(_LIBCPP_FUNCTIONAL)
#define MEM_FN_SYMBOL std::__mem_fn
#endif

#ifdef MEM_FN_SYMBOL
    template <typename R, typename... Args>
    struct function_traits<MEM_FN_SYMBOL<R( * )( Args... )>>
        : public function_traits<R( Args... )> {
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<MEM_FN_SYMBOL<R( C::* )( Args... )>>
        : public function_traits<R( Args... )> {
        typedef C &owner_type;
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<MEM_FN_SYMBOL<R( C::* )( Args... ) const>>
        : public function_traits<R( Args... )> {
        typedef const C &owner_type;
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<MEM_FN_SYMBOL<R( C::* )( Args... ) volatile>>
        : public function_traits<R( Args... )> {
        typedef volatile C &owner_type;
    };

    template <typename C, typename R, typename... Args>
    struct function_traits<MEM_FN_SYMBOL<R( C::* )( Args... ) const volatile>>
        : public function_traits<R( Args... )> {
        typedef const volatile C &owner_type;
    };

#undef MEM_FN_SYMBOL
#endif

    template <typename Functor>
    struct function_traits<std::function<Functor>>
        : public function_traits<Functor> {
    };

    template <typename T>
    struct function_traits<T &> : public function_traits<T> {
    };

    template <typename T>
    struct function_traits<const T &> : public function_traits<T> {
    };

    template <typename T>
    struct function_traits<volatile T &> : public function_traits<T> {
    };

    template <typename T>
    struct function_traits<const volatile T &> : public function_traits<T> {
    };

    template <typename T>
    struct function_traits<T &&> : public function_traits<T> {
    };

    template <typename T>
    struct function_traits<const T &&> : public function_traits<T> {
    };

    template <typename T>
    struct function_traits<volatile T &&> : public function_traits<T> {
    };

    template <typename T>
    struct function_traits<const volatile T &&> : public function_traits<T> {
    };

/*
 * This seems to be slightly better than the standard library version as of now.
 * */

    template <typename Functor>
    using fn_result_of = typename function_traits<Functor>::result_type;
}

#endif // FUNCTION_TRAITS_HPP_INCLUDED
