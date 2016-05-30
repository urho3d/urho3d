/*
 * wrap.hpp
 *
 *  Created on: Apr 6, 2016
 *      Author: nathan
 */

#pragma once
#include <type_traits>
//#include "AngelScript/angelscript.h"
#include "angelscript.h"
#include <boost/preprocessor.hpp>



//Return void enable if: http://stackoverflow.com/questions/12002447/template-method-enable-if-specialization
//# do with // http://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick


#define EV(...) __VA_ARGS__

//inline asSFuncPtr asFunctionPtr<asGENFUNC_t>(asGENFUNC_t func)
//{
//	// Mark this as a generic function
//	asSFuncPtr p(1);
//	p.ptr.f.func = reinterpret_cast<asFUNCTION_t>(func);
//	return p;
//}
typedef void (*asGENFUNC_t)(asIScriptGeneric *);


//#define DO_2(_,a,b) GET(a,0), GET(b,1)//Proxy<a>::cast(gen->arguments[0])
//#define DO_4(_,a,b,c,d) GET(a,0), GET(b,1),GET(c,2), GET(d,3)//(a*)(gen->arguments[0]),(b*)(gen->arguments[1]),(a*)(gen->arguments[2]),(b*)(gen->arguments[3])
//#define DO_6(_,a,b,c,d,e,f) GET(a,0), GET(b,1),GET(c,2), GET(d,3),GET(e,4), GET(f,5)//(a*)(gen->arguments[0]),(b*)(gen->arguments[1]),(a*)(gen->arguments[2]),(b*)(gen->arguments[3]),(a*)(gen->arguments[4]),(b*)(gen->arguments[5])
//
////#define DO_1(_,a) static_cast<Proxy <a> *>(gen->arguments[0])->value
//#define DO_1(_,a) Proxy<a>::cast(gen->arguments[0])
//#define DO_3(_,a,b,c) GET(a,0), GET(b,1),GET(c,2)
//#define DO_5(_,a,b,c,d,e) GET(a,0), GET(b,1),GET(c,2), GET(d,3),GET(e,4)
//
//#define DO_0(_)
//
//#define GET7TH(_,arg1, arg2, arg3, arg4, arg5, arg6, arg7,...) arg7
//#define DO_CHOOSER(...) GET7TH(__VA_ARGS__,DO_6,DO_5,DO_4,DO_3,DO_2,DO_1,DO_0)
//
//#define DO(...) DO_CHOOSER(_,##__VA_ARGS__)(_,##__VA_ARGS__)
//
//#define CHOOSE(...)


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
//	, Proxy<elem>::cast(gen->arguments[idx])

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

//typedef asIScriptGeneric Gen;
#include <Container/RefCounted.h> //<- needed for the AddRef stuff
namespace wrap
{

template<class T>
void AddRef(const void*)
{
	return;
}
template<class T>
void AddRef(Urho3D::RefCounted** obj)
{
	if (*obj)
	{
		(*obj)->AddRef();
	}
}

//void Add(::std::false_type, ...)
//{
//	return;
//}
//void Add(::std::true_type, void* obj)
//{
//	if (*obj)
//	{
//		((Urho3D::RefCounted*)obj)->AddRef();
//	}
//}
//
//template<class T, typename ...P>
//void Deploy(T, ...P)
//{
//	Add(::std::is_base_of<Urho3D::RefCounted,)
//}



template<class T> void call(T t)
{
	gw::Proxy<T> ret(t);
	AddRef<T>(&(ret.value));
}
template<typename ...T>
void nill(T... args)
{
	(void)0;
}
/*
template<class ...T>
void calls(T... args)
{
	// from: http://stackoverflow.com/questions/17339789/how-to-call-a-function-on-all-variadic-template-args

	    using expand_type = int[];


	//#define SO_EXPAND_SIDE_EFFECTS(PATTERN) ::so::expand_type{ 0, ((PATTERN), 0)... }

	expand_type{ 0, ((call<T>(args)), 0)... };
}*/

template<class R, class C, typename ...P>
void call_helper(::std::false_type, asIScriptGeneric*g, C*obj, R (C::*fn)(P...), P... args)
{
//	cout << "do non-void";
//	g->return_value = new R ((obj->*fn)(args...));
//	(AddRef(args)...);
	//calls<P...>(args...); // <- working one
//	Add(::std::is_base_of<)
	new (g->GetAddressOfReturnLocation()) gw::Proxy<R> ((obj->*fn)(args...));
	gw::Proxy<R>* ret = static_cast<gw::Proxy<R>*>(g->GetAddressOfReturnLocation());
	//AddRef<R>(&(ret->value));
}

template<class R, class C, typename ...P>
void call_helper(::std::true_type,asIScriptGeneric*g, C*obj, R (C::*fn)(P...), P... args)
{
//	cout << "do void";
	//calls(args...);
	(obj->*fn)(args...);
//	g->return_value = nullptr;

}
template<class R, class C, typename ...P>
void call_helper(::std::false_type, asIScriptGeneric*g, C*obj, R (C::*fn)(P...)const, P... args)
{
//	cout << "do non-void const";
//	g->return_value = new R ((obj->*fn)(args...));
	//calls(args...);
	new (g->GetAddressOfReturnLocation()) gw::Proxy<R> ((obj->*fn)(args...));
	gw::Proxy<R>* ret = static_cast<gw::Proxy<R>*>(g->GetAddressOfReturnLocation());
	//AddRef<R>(&(ret->value));
}

template<class R, class C, typename ...P>
void call_helper(::std::true_type,asIScriptGeneric*g, C*obj, R (C::*fn)(P...)const, P... args)
{
//	cout << "do void const";
	//calls(args...);
	(obj->*fn)(args...);
//	g->return_value = nullptr;

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
}


