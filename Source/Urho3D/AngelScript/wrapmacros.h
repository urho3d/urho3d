//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// FIXME: This file needs to be cleaned up

#pragma once

// Only use this file if the portable (wrapped) code has been specifically requested
#ifdef AS_MAX_PORTABILITY

//the template wrapper code
#include "wrap16.h"

//can help solve potential ... problems if we need it at the start: http://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros

//Overview of the process:
//take the original function that registers a function for the angelscript engine:
//(RegisterGlobalFunction, RegisterObjectMethod, ...)
//Define it as a macro. Redefine the asFUNCTION family of macros to extract the arguments passed to them
//and pass an F, M, FPR, or MPR depending on which macro was chosen as another argument before the original
//contents of the asFUNCTION macro
//Use the ## operator to paste the F, M, FPR< or MPR along with the asECallConvTypes name to form the name of another macro
//This other macro will then bundle the arguments back into the original RegisterGlobalFunction... call, but will use the
//wrap macros from the wrap16.h and wrap.h files instead of the original asFUNCTION... call, and will specify the asCALL_GENERIC
//calling convention
//***NOTE***: not all of the possibly calling convention/method combinations have been finished, and those that Urho does not use are untested


#undef asFUNCTION
#define asFUNCTION(f) F, f
//define a new macro (taken from angelscript.h) to use in place of the original asFUNCTION macro
#define _asFUNCTION(f) asFunctionPtr(f)
//#define asMETHOD(cls, f) cls, M, f
#undef asMETHOD
#define asMETHOD(cls, f) M, (cls,f) //package class and function for UNWRAPping later
#undef UNWRAP
#define UNWRAP(x,y) x,y// try -fmacro-backtrace-limit=0 on compile
//define a new macro (taken from angelscript.h) to use in place of the original asMETHOD macro
#define _asMETHOD(c,m) asSMethodPtr<sizeof(void (c::*)())>::Convert((void (c::*)())(&c::m))
#define RegisterGlobalFunction(...) RegGlobalIndirect(__VA_ARGS__)
#define RegGlobalIndirect(decl, F, func, kind) RegisterGlobalFunction##F##kind (decl,func) // ... = decl or it = decl, cls for asCall_ThisCall
#define RegisterGlobalFunctionFasCALL_CDECL(decl,fun) RegisterGlobalFunction(decl, WRAP_FN(fun), asCALL_GENERIC); //assert(r >= 0);
#define RegisterGlobalFunctionFasCALL_STDCALL(decl,fun) RegisterGlobalFunction(decl, WRAP_FN(fun), asCALL_GENERIC); //assert(r >= 0);
#define RegisterGlobalFunctionMasCALL_THISCALL_ASGLOBAL(decl,fun) RegisterGlobalFunctionMasCALL_THISCALL_ASGLOBAL_2(decl,UNWRAP fun)
#define RegisterGlobalFunctionMasCALL_THISCALL_ASGLOBAL_2(decl, ...) RegisterGlobalFunction(decl, WRAP_MFN(__VA_ARGS__), asCALL_GENERIC); //assert(r >= 0);
#define RegisterGlobalFunctionFasCALL_GENERIC(decl,fun) RegisterGlobalFunction(decl, asFunctionPtr(fun), asCALL_GENERIC); //assert(r >= 0);

//object indirects
#define RegisterObjectMethod(...) RegObjectMethodIndirect(__VA_ARGS__)
//#define RegObjectIndirect(clsdcl,decl, F, func, kind) RegObjectIndirect_2(clsdcl,decl, F, UNWRAP func, kind)
#define RegObjectMethodIndirect(clsdcl,decl, F, clsfunc, kind) RegisterObjectMethod##F##kind (clsdcl,decl,clsfunc) // ... = decl or it = decl, cls for asCall_ThisCall
#define RegisterObjectMethodMasCALL_THISCALL(clsdcl,decl,clsfunc) RegisterObjectMethodMasCALL_THISCALL_2(clsdcl,decl,UNWRAP clsfunc)
#define RegisterObjectMethodMasCALL_THISCALL_2(clsdcl,decl,...) RegisterObjectMethodMasCALL_THISCALL_3(clsdcl,decl, WRAP_MFN(__VA_ARGS__));
#define RegisterObjectMethodMasCALL_THISCALL_3(clsdcl,decl,fn) RegisterObjectMethod(clsdcl,decl, fn, asCALL_GENERIC); //assert(r >= 0);
#define RegisterObjectMethodFasCALL_CDECL_OBJLAST(clsdcl,decl,fun) RegisterObjectMethod(clsdcl,decl, WRAP_OBJ_LAST(fun), asCALL_GENERIC); //assert(r >= 0);
#define RegisterObjectMethodFasCALL_CDECL_OBJFIRST(clsdcl,decl,fun) RegisterObjectMethod(clsdcl,decl, WRAP_OBJ_FIRST(fun), asCALL_GENERIC); //assert(r >= 0);
//#define RegisterObjectMethodMasCALL_CDECL_OBJECTFIRST(decl,cls,fun) RegisterObjectMethodMasCALL_THISCALL_ASGLOBAL_2(decl,UNWRAP fun)
//#define RegisterObjectMethodMasCALL_THISCALL_ASGLOBAL_2(decl, ...) RegisterObjectMethod(decl, WRAP_MFN(__VA_ARGS__), asCALL_GENERIC); //assert(r >= 0);
#define RegisterObjectMethodFasCALL_GENERIC(clsdcl,decl,fun) RegisterObjectMethod(clsdcl,decl, asFunctionPtr(fun), asCALL_GENERIC); //assert(r >= 0);

////note:unfortunately, the WrapCon methods are for creating the constructor wrapper, which typically seems to be done anyways, so we should just handle it like Register Object Method with 1 extra parameter
//#define RegisterObjectBehaviour(...) RegObjectBehaviorIndirect(__VA__ARGS__)
//#define RegObjectBehaviorIndirect(clsdcl,behavior,decl,fn,kind) RegisterObjectBehavior##behavior(clsdcl,behavior,decl,fn,kind)
//#define RegisterObjectBehaviorasBEHAVE_CONSTRUCT(clsdcl,behavior,decl,fn,kind) RegisterObjectConstructor##F##kind (clsdcl,behavior,decl,fn)
//#define RegisterObjectConstructorFasCALL_CDECL_OBJECTLAST(clsdcl,behavior,decl,fn) RegisterObjectBehavior(clsdcl,behavior,decl,WRAP_OBJ_LAST(fn),asCALL_GENERIC)
////RegisterObjectConstructorF##kind (clsdcl,decl,clsfunc)

//NOTE: Angelscript uses the British English spelling __iour!
#define RegisterObjectBehaviour(...) RegObjectBehaviorIndirect(__VA_ARGS__)
//#define RegObjectIndirect(clsdcl,behavior,decl, F, func, kind) RegObjectIndirect_2(clsdcl,behavior,decl, F, UNWRAP func, kind)
#define RegObjectBehaviorIndirect(clsdcl,behavior,decl, F, clsfunc, kind) RegisterObjectBehavior##F##kind (clsdcl,behavior,decl,clsfunc) // ... = decl or it = decl, cls for asCall_ThisCall
#define RegisterObjectBehaviorMasCALL_THISCALL(clsdcl,behavior,decl,clsfunc) RegisterObjectBehaviorMasCALL_THISCALL_2(clsdcl,behavior,decl,UNWRAP clsfunc)
#define RegisterObjectBehaviorMasCALL_THISCALL_2(clsdcl,behavior,decl,...) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_MFN(__VA_ARGS__), asCALL_GENERIC); //assert(r >= 0);
#define RegisterObjectBehaviorFasCALL_CDECL_OBJLAST(clsdcl,behavior,decl,...) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_OBJ_LAST(__VA_ARGS__), asCALL_GENERIC); //assert(r >= 0);
#define RegisterObjectBehaviorFasCALL_CDECL_OBJFIRST(clsdcl,behavior,decl,...) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_OBJ_FIRST(__VA_ARGS__), asCALL_GENERIC); //assert(r >= 0);
//#define RegisterObjectBehaviorMasCALL_CDECL_OBJECTFIRST(decl,cls,fun) RegisterObjectBehaviorMasCALL_THISCALL_ASGLOBAL_2(decl,UNWRAP fun)
//#define RegisterObjectBehaviorMasCALL_THISCALL_ASGLOBAL_2(decl, ...) RegisterObjectBehavior(decl, WRAP_MFN(__VA_ARGS__), asCALL_GENERIC); //assert(r >= 0);
#define RegisterObjectBehaviorFasCALL_CDECL(clsdcl,behavior,decl,...) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_FN(__VA_ARGS__),asCALL_GENERIC);
#define RegisterObjectBehaviorFasCALL_GENERIC(clsdcl,behavior,decl,fun) RegisterObjectBehaviour(clsdcl,behavior,decl, asFunctionPtr(fun), asCALL_GENERIC); //assert(r >= 0);

//Parameter-Return versions:

#undef asFUNCTIONPR
#define asFUNCTIONPR(f,p,r) FPR, (f,p,r)
#define UNWRAP3(x,y,z) x,y,z
#define UNWRAP4(x,y,z,w) x,y,z,w
#undef asMETHODPR
#define asMETHODPR(cls,f,p,r) MPR, (cls,f,p,r)
//define a new macro (taken from angelscript.h) to use in place of the original asFUNCTIONPR macro
#if (defined(_MSC_VER) && _MSC_VER <= 1200) || (defined(__BORLANDC__) && __BORLANDC__ < 0x590)
// MSVC 6 has a bug that prevents it from properly compiling using the correct asFUNCTIONPR with operator >
// so we need to use ordinary C style cast instead of static_cast. The drawback is that the compiler can't
// check that the cast is really valid.
// BCC v5.8 (C++Builder 2006) and earlier have a similar bug which forces us to fall back to a C-style cast.
#define _asFUNCTIONPR(f,p,r) asFunctionPtr((void (*)())((r (*)p)(f)))
#elif (defined(_MSC_VER) && _MSC_VER >= 1900)
// Urho3D: VS2015 does not compile the C-style cast of the function pointer
#define _asFUNCTIONPR(f,p,r) asFunctionPtr(reinterpret_cast<void (*)()>(static_cast<r (*)p>(f)))
#else
#define _asFUNCTIONPR(f,p,r) asFunctionPtr((void (*)())(static_cast<r (*)p>(f)))
#endif
//define a new macro (taken from angelscript.h) to use in place of the original asMETHODPR macro
#define _asMETHODPR(c,m,p,r) asSMethodPtr<sizeof(void (c::*)())>::Convert(AS_METHOD_AMBIGUITY_CAST(r (c::*)p)(&c::m))


#define RegisterGlobalFunctionFPRasCALL_CDECL(decl,fun) RegisterGlobalFunctionFPRasCALL_CDECL_2(decl, UNWRAP3 fun);
#define RegisterGlobalFunctionFPRasCALL_CDECL_2(decl,...) RegisterGlobalFunction(decl, WRAP_FN_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterGlobalFunctionFPRasCALL_STDCALL(decl,fun) RegisterGlobalFunctionFPRasCALL_STDCALL_2(decl, UNWRAP3 fun);
#define RegisterGlobalFunctionFPRasCALL_STDCALL_2(decl,...) RegisterGlobalFunction(decl, WRAP_FN_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterGlobalFunctionMPRasCALL_THISCALL_ASGLOBAL(decl,fun) RegisterGlobalFunctionMasCALL_THISCALL_ASGLOBAL_2(decl,UNWRAP4 fun)
#define RegisterGlobalFunctionMPRasCALL_THISCALL_ASGLOBAL_2(decl, ...) RegisterGlobalFunction(decl, WRAP_MFN_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterGlobalFunctionFPRasCALL_GENERIC(decl,fun) RegisterGlobalFunctionFPRasCALL_GENERIC_2(decl, UNWRAP3 fun);
#define RegisterGlobalFunctionFPRasCALL_GENERIC_2(decl,...) RegisterGlobalFunction(decl, _asFUNCTIONPR(__VA_ARGS__), asCALL_GENERIC);

#define RegisterObjectMethodMPRasCALL_THISCALL(clsdcl,decl,clsfunc) RegisterObjectMethodMPRasCALL_THISCALL_2(clsdcl,decl,UNWRAP4 clsfunc)
#define RegisterObjectMethodMPRasCALL_THISCALL_2(clsdcl,decl,...) RegisterObjectMethod(clsdcl,decl, WRAP_MFN_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterObjectMethodFPRasCALL_CDECL_OBJLAST(clsdcl,decl,fun) RegisterObjectMethodFPRasCALL_CDECL_OBJLAST_2(clsdcl,decl, UNWRAP3 fun);
#define RegisterObjectMethodFPRasCALL_CDECL_OBJLAST_2(clsdcl,decl,...) RegisterObjectMethod(clsdcl,decl, WRAP_OBJ_LAST_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterObjectMethodFPRasCALL_CDECL_OBJFIRST(clsdcl,decl,fun) RegisterObjectMethodFPRasCALL_CDECL_OBJFIRST_2(clsdcl,decl, UNWRAP3 fun);
#define RegisterObjectMethodFPRasCALL_CDECL_OBJFIRST_2(clsdcl,decl,...) RegisterObjectMethod(clsdcl,decl, WRAP_OBJ_FIRST_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterObjectMethodFPRasCALL_GENERIC(clsdcl,decl,fun) RegisterObjectMethodFPRasCALL_GENERIC_2(clsdcl,decl, UNWRAP3 fun);
#define RegisterObjectMethodFPRasCALL_GENERIC_2(clsdcl,decl,...) RegisterObjectMethod(clsdcl,decl, _asFUNCTIONPR(__VA_ARGS__), asCALL_GENERIC);

#define RegisterObjectBehaviorMPRasCALL_THISCALL(clsdcl,behavior,decl,clsfunc) RegisterObjectBehaviorMPRasCALL_THISCALL_2(clsdcl,behavior,decl,UNWRAP4 clsfunc)
#define RegisterObjectBehaviorMPRasCALL_THISCALL_2(clsdcl,behavior,decl,...) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_MFN_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterObjectBehaviorFPRasCALL_CDECL_OBJLAST(clsdcl,behavior,decl,clsfunc) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_OBJ_LAST_PR clsfunc, asCALL_GENERIC);
#define RegisterObjectBehaviorFPRasCALL_CDECL_OBJFIRST(clsdcl,behavior,decl,...) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_OBJ_FIRST_PR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterObjectBehaviorFPRasCALL_GENERIC(clsdcl,behavior,decl,...) RegisterObjectBehaviour(clsdcl,behavior,decl, _asFUNCTIONPR(__VA_ARGS__), asCALL_GENERIC);
#define RegisterObjectBehaviorFPRasCALL_CDECL(clsdcl,behavior,decl,clsfunc) RegisterObjectBehaviour(clsdcl,behavior,decl, WRAP_FN_PR clsfunc, asCALL_GENERIC);


/*#define SetExceptionCallback(...) SetExceptionCallback_2(__VA_ARGS__)
#define SetExceptionCallback_2(M,params,obj,kind) SetExceptionCallback(WRAP_MFN params, obj, asCALL_GENERIC);

#define SetMessageCallback(...) SetMessageCallback_2(__VA_ARGS__)
#define SetMessageCallback_2(M,params,obj,kind) SetMessageCallback(WRAP_MFN params, obj, asCALL_GENERIC);
*/

#endif

