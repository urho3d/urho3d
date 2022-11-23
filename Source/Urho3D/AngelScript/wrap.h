// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

// WRAP_MFN_PR for GCC
// GCC has problems with templates, VS with macros, so implementations is different

/*
struct A
{
    bool f(int i) { return true; }
};

struct B : public A
{
    // f() is inherited
};

template <bool (B::*fp)(int)>
struct WrapF
{
};

WrapF<&B::f> a;
// Doesn't work for any compiler
// Error: non-type template argument of type 'bool (Urho3D::A::*)(int)' cannot be converted to a value of type 'bool (Urho3D::B::*)(int)'

WrapF<static_cast<bool (B::*)(int)>(&B::f)> b;
// Works for VS but not works for GCC
// Error: non-type template argument is not a pointer to member constant

==================================

MACROS1(a, b, MACROS2)
GCC replaces the parameter MACROS2 first and after that MACROS1
VS replaces MACROS1 first

VS has parameters:
https://docs.microsoft.com/en-us/cpp/preprocessor/preprocessor-experimental-overview
https://docs.microsoft.com/en-us/cpp/build/reference/experimental-preprocessor
but it cause banch of errors in Windows 10 SDK <= 10.0.17763.0
and third party libs
*/

#ifndef _MSC_VER

#include <type_traits>

#include <AngelScript/angelscript.h>

//only Boost.Preprocessor is needed, so it may be reasonable to include it in the Urho repository directly
#include <boost/preprocessor.hpp>


//Return void enable if: http://stackoverflow.com/questions/12002447/template-method-enable-if-specialization
//# do with // http://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick

#define EV(...) __VA_ARGS__

#define UNWRAP(...) __VA_ARGS__
#define EXTRACT_CONST(...) (__VA_ARGS__),
// from http://stackoverflow.com/questions/18851889/boost-preprocessor-skip-if-variadic-is-empty

// based on the: http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments
#define __ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define __HAS_COMMA(...) __ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define __TRIGGER_PARENTHESIS_(...) ,
#define __PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define __IS_EMPTY_CASE_0001 ,
#define __IS_EMPTY(_0, _1, _2, _3) __HAS_COMMA(__PASTE5(__IS_EMPTY_CASE_, _0, _1, _2, _3))

#define TUPLE_IS_EMPTY(...) \
    __IS_EMPTY( \
        /* test if there is just one argument, eventually an empty one */ \
        __HAS_COMMA(__VA_ARGS__), \
        /* test if _TRIGGER_PARENTHESIS_ together with the argument adds a comma */ \
        __HAS_COMMA(__TRIGGER_PARENTHESIS_ __VA_ARGS__),                 \
        /* test if the argument together with a parenthesis adds a comma */ \
        __HAS_COMMA(__VA_ARGS__ (/*empty*/)), \
        /* test if placing it between _TRIGGER_PARENTHESIS_ and the parenthesis adds a comma */ \
        __HAS_COMMA(__TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/)) \
    )

#define __GEN_EMPTY_ARGS(...)

#define __GEN_NONEMPTY_ARGS_CB(unused, data, idx, elem) \
    , static_cast<gw::Proxy <elem> *>(gen->GetAddressOfArg(idx))->value

#define __GEN_NONEMPTY_ARGS(seq) \
    BOOST_PP_SEQ_FOR_EACH_I( \
         __GEN_NONEMPTY_ARGS_CB \
        ,~ \
        ,seq \
    )

#define CreateGenericFromMethod_2(...) EV(CreateGenericFromMethod_3(__VA_ARGS__))
#define CreateGenericFromMethod_3(class_t,method,parameters,const,return_t) \
asFunctionPtr<asGENFUNC_t>([] (asIScriptGeneric* gen) {\
        BOOST_PP_CAT(wrap::call,const) <return_t,class_t BOOST_PP_COMMA_IF(BOOST_PP_IF(TUPLE_IS_EMPTY parameters ,0,1)) EV parameters>\
                (gen,/*&(Proxy<class_t>::cast(gen->GetObject()))*/((class_t*)gen->GetObject()), static_cast<return_t (class_t::*) parameters const>(&class_t::method)\
                    BOOST_PP_IF( \
                         TUPLE_IS_EMPTY parameters \
                        ,__GEN_EMPTY_ARGS \
                        ,__GEN_NONEMPTY_ARGS \
                    )(BOOST_PP_TUPLE_TO_SEQ( parameters )) \
                );\
})

#define WRAP_MFN_PR(class_t,method,parameters,return_t) EV(EV(EV(CreateGenericFromMethod_2(class_t,method,EXTRACT_CONST parameters,return_t))))


namespace wrap
{

template<class R, class C, typename ...P>
void call_helper(::std::false_type, asIScriptGeneric*g, C*obj, R (C::*fn)(P...), P... args)
{
    new (g->GetAddressOfReturnLocation()) gw::Proxy<R> ((obj->*fn)(args...));
}

template<class R, class C, typename ...P>
void call_helper(::std::true_type,asIScriptGeneric*g, C*obj, R (C::*fn)(P...), P... args)
{
    (obj->*fn)(args...);
}
template<class R, class C, typename ...P>
void call_helper(::std::false_type, asIScriptGeneric*g, C*obj, R (C::*fn)(P...)const, P... args)
{
    new (g->GetAddressOfReturnLocation()) gw::Proxy<R> ((obj->*fn)(args...));
}

template<class R, class C, typename ...P>
void call_helper(::std::true_type,asIScriptGeneric*g, C*obj, R (C::*fn)(P...)const, P... args)
{
    (obj->*fn)(args...);
}
template<class R, class C, typename ...P>
void call(asIScriptGeneric*g, C*obj, R (C::*fn)(P...), P... args)
{
    call_helper<R,C,P...>(::std::is_void<R>(),
            g,
            obj,
            fn,
            args...);
}
template<class R, class C, typename ...P>
void callconst(asIScriptGeneric*g, C*obj, R (C::*fn)(P...)const, P... args)
{
    call_helper<R,C,P...>(std::is_void<R>(),
            g,
            obj,
            fn,
            args...);
}

} // namespace wrap

#endif // ndef _MSC_VER
