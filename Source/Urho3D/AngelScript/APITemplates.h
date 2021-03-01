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

#pragma once

#include "../AngelScript/Addons.h"
#include "../AngelScript/Script.h"
#include "../AngelScript/ScriptInstance.h"
#include "../Audio/SoundSource.h"
#include "../Core/Context.h"
#include "../Container/HashSet.h"
#include "../Container/Sort.h"
#include "../Graphics/Drawable.h"
#include "../Graphics/StaticModel.h"
#include "../Graphics/Texture.h"
#include "../IO/File.h"
#include "../IO/Log.h"
#include "../IO/VectorBuffer.h"
#include "../Resource/Resource.h"
#include "../Scene/Animatable.h"
#include "../Scene/Node.h"
#include "../UI/BorderImage.h"

#ifdef URHO3D_URHO2D
#include "../Urho2D/Drawable2D.h"
#endif

#include <AngelScript/angelscript.h>
#include <cstring>

#include "../AngelScript/RegistrationMacros.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4505)
#endif

namespace Urho3D
{

class Camera;

bool operator ==(const asSFuncPtr& a, const asSFuncPtr& b);

struct RegisterObjectMethodArgs
{
    String cppDeclaration_; // Used as identifier when removed from list
    String asDeclaration_;
    asSFuncPtr funcPointer_;
    asDWORD callConv_ = 0;

    RegisterObjectMethodArgs() = default;

    RegisterObjectMethodArgs(const String& cppDeclaration, const String& asDeclaration, const asSFuncPtr& funcPointer, asDWORD callConv)
        : cppDeclaration_(cppDeclaration)
        , asDeclaration_(asDeclaration)
        , funcPointer_(funcPointer)
        , callConv_(callConv)
    {
    }
};

struct RegisterGlobalFunctionArgs
{
    String cppDeclaration_;
    String asDeclaration_;
    asSFuncPtr funcPointer_;
    asDWORD callConv_ = 0;

    RegisterGlobalFunctionArgs() = default;

    RegisterGlobalFunctionArgs(const String& cppDeclaration, const String& asDeclaration, const asSFuncPtr& funcPointer, asDWORD callConv)
        : cppDeclaration_(cppDeclaration)
        , asDeclaration_(asDeclaration)
        , funcPointer_(funcPointer)
        , callConv_(callConv)
    {
    }
};

struct RegisterObjectPropertyArgs
{
    String cppDeclaration_;
    String asDeclaration_;
    int byteOffset_ = 0;

    RegisterObjectPropertyArgs() = default;

    RegisterObjectPropertyArgs(const String& cppDeclaration, const String& asDeclaration, int byteOffset)
        : cppDeclaration_(cppDeclaration)
        , asDeclaration_(asDeclaration)
        , byteOffset_(byteOffset)
    {
    }
};

struct RegisterGlobalPropertyArgs
{
    String cppDeclaration_;
    String asDeclaration_;
    void* pointer_ = nullptr;

    RegisterGlobalPropertyArgs() = default;
    
    RegisterGlobalPropertyArgs(const String& cppDeclaration, const String& asDeclaration, void* pointer)
        : cppDeclaration_(cppDeclaration)
        , asDeclaration_(asDeclaration)
        , pointer_(pointer)
    {
    }
};

struct RegisterObjectBehaviourArgs
{
    String cppDeclaration_;
    asEBehaviours behaviour_;
    String asDeclaration_;
    asSFuncPtr funcPointer_;
    asDWORD callConv_ = 0;

    RegisterObjectBehaviourArgs() = default;

    RegisterObjectBehaviourArgs(const String& cppDeclaration, asEBehaviours behaviour, const String& asDeclaration, const asSFuncPtr& funcPointer, asDWORD callConv)
        : cppDeclaration_(cppDeclaration)
        , behaviour_(behaviour)
        , asDeclaration_(asDeclaration)
        , funcPointer_(funcPointer)
        , callConv_(callConv)
    {
    }
};

struct MemberCollection
{
    Vector<RegisterObjectMethodArgs> methods_;
    Vector<RegisterGlobalFunctionArgs> staticMethods_;
    Vector<RegisterObjectPropertyArgs> fields_;
    Vector<RegisterObjectMethodArgs> wrappedFields_;
    Vector<RegisterGlobalPropertyArgs> staticFields_;
    Vector<RegisterObjectBehaviourArgs> behaviours_;
};

// Where T is RegisterObjectMethodArgs, RegisterObjectPropertyArgs, RegisterGlobalPropertyArgs
template<typename T> void Remove(Vector<T>& list, const String& cppDeclaration)
{
    // The vector can contain several elements with the same cppDeclaration (aliases)
    auto it = list.Begin();
    while (it != list.End())
    {
        if (it->cppDeclaration_ == cppDeclaration)
            it = list.Erase(it);
        else
            ++it;
    }
}

inline void RegisterMembers(asIScriptEngine* engine, const char* asClassName, const MemberCollection& members)
{
    for (const RegisterObjectMethodArgs& method : members.methods_)
        engine->RegisterObjectMethod(asClassName, method.asDeclaration_.CString(), method.funcPointer_, method.callConv_);

    for (const RegisterGlobalFunctionArgs& staticMethod : members.staticMethods_)
    {
        engine->SetDefaultNamespace(asClassName);
        engine->RegisterGlobalFunction(staticMethod.asDeclaration_.CString(), staticMethod.funcPointer_, staticMethod.callConv_);
        engine->SetDefaultNamespace("");
    }

    for (const RegisterObjectPropertyArgs& field : members.fields_)
        engine->RegisterObjectProperty(asClassName, field.asDeclaration_.CString(), field.byteOffset_);

    for (const RegisterObjectMethodArgs& wrappedField : members.wrappedFields_)
        engine->RegisterObjectMethod(asClassName, wrappedField.asDeclaration_.CString(), wrappedField.funcPointer_, wrappedField.callConv_);

    for (const RegisterGlobalPropertyArgs& staticField : members.staticFields_)
    {
        engine->SetDefaultNamespace(asClassName);
        engine->RegisterGlobalProperty(staticField.asDeclaration_.CString(), staticField.pointer_);
        engine->SetDefaultNamespace("");
    }

    for (const RegisterObjectBehaviourArgs& behaviour : members.behaviours_)
        engine->RegisterObjectBehaviour(asClassName, behaviour.behaviour_, behaviour.asDeclaration_.CString(), behaviour.funcPointer_, behaviour.callConv_);
}

/// Template function for Vector to array conversion.
template <class T> CScriptArray* VectorToArray(const Vector<T>& vector, const char* arrayName)
{
    Context* context = GetScriptContext();
    if (context)
    {
        asITypeInfo* type = context->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = vector[i];

        return arr;
    }
    else
        return nullptr;
}

/// Template function for PODVector to array conversion.
template <class T> CScriptArray* VectorToArray(const PODVector<T>& vector, const char* arrayName)
{
    Context* context = GetScriptContext();
    if (context)
    {
        asITypeInfo* type = context->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = vector[i];

        return arr;
    }
    else
        return nullptr;
}

/// Template function for data buffer to array conversion.
template <class T> CScriptArray* BufferToArray(const T* buffer, unsigned size, const char* arrayName)
{
    Context* context = GetScriptContext();
    if (context)
    {
        asITypeInfo* type = context->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, size);

        for (unsigned i = 0; i < arr->GetSize(); ++i)
            *(static_cast<T*>(arr->At(i))) = buffer[i];

        return arr;
    }
    else
        return nullptr;
}

/// Template function for Vector to handle array conversion.
template <class T> CScriptArray* VectorToHandleArray(const Vector<T*>& vector, const char* arrayName)
{
    Context* context = GetScriptContext();
    if (context)
    {
        asITypeInfo* type = context->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
        {
            // Increment reference count for storing in the array
            T* ptr = vector[i];
            if (ptr)
                ptr->AddRef();
            *(static_cast<T**>(arr->At(i))) = ptr;
        }

        return arr;
    }
    else
        return nullptr;
}

/// Template function for PODVector to handle array conversion.
template <class T> CScriptArray* VectorToHandleArray(const PODVector<T*>& vector, const char* arrayName)
{
    Context* context = GetScriptContext();
    if (context)
    {
        asITypeInfo* type = context->GetSubsystem<Script>()->GetObjectType(arrayName);
        CScriptArray* arr = CScriptArray::Create(type, vector.Size());

        for (unsigned i = 0; i < arr->GetSize(); ++i)
        {
            // Increment reference count for storing in the array
            T* ptr = vector[i];
            if (ptr)
                ptr->AddRef();
            *(static_cast<T**>(arr->At(i))) = ptr;
        }

        return arr;
    }
    else
        return nullptr;
}

/// Template function for shared pointer Vector to handle array conversion.
template <class T> CScriptArray* VectorToHandleArray(const Vector<SharedPtr<T> >& vector, const char* arrayName)
{
    Context* context = GetScriptContext();

    if (!context)
        return nullptr;

    asITypeInfo* type = context->GetSubsystem<Script>()->GetObjectType(arrayName);
    CScriptArray* arr = CScriptArray::Create(type, vector.Size());

    for (unsigned i = 0; i < arr->GetSize(); ++i)
    {
        // Increment reference count for storing in the array
        T* ptr = vector[i];
        if (ptr)
            ptr->AddRef();
        *(static_cast<T**>(arr->At(i))) = ptr;
    }

    return arr;
}

/// Template function for array to Vector conversion.
template <class T> Vector<T> ArrayToVector(CScriptArray* arr)
{
    Vector<T> dest(arr ? arr->GetSize() : 0);
    if (arr)
    {
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            dest[i] = *static_cast<T*>(arr->At(i));
    }
    return dest;
}

/// Template function for array to PODVector conversion.
template <class T> PODVector<T> ArrayToPODVector(CScriptArray* arr)
{
    PODVector<T> dest(arr ? arr->GetSize() : 0);
    if (arr)
    {
        for (unsigned i = 0; i < arr->GetSize(); ++i)
            dest[i] = *static_cast<T*>(arr->At(i));
    }
    return dest;
}

template <class T> Vector<SharedPtr<T> > HandleArrayToVector(CScriptArray* arr)
{
    Vector<T*> rawPtrs = ArrayToVector<T*>(arr);
    Vector<SharedPtr<T> > result(rawPtrs.Size());
    for (unsigned i = 0; i < rawPtrs.Size(); ++i)
        result[i] = SharedPtr<T>(rawPtrs[i]);
    return result;
}

/// Template function for dynamic cast between two script classes.
template <class A, class B> B* RefCast(A* a)
{
    if (!a)
        return nullptr;

    B* b = dynamic_cast<B*>(a);

    return b;
}

/// Template function for registering implicit casts between base and subclass.
// https://www.angelcode.com/angelscript/sdk/docs/manual/doc_adv_class_hierarchy.html
template <class BaseType, class DerivedType> void RegisterSubclass(asIScriptEngine* engine, const char* baseClassName, const char* derivedClassName)
{
    if (!strcmp(baseClassName, derivedClassName))
        return;

    String declReturnBase(String(baseClassName) + "@+ opImplCast()");
    engine->RegisterObjectMethod(derivedClassName, declReturnBase.CString(), AS_FUNCTION_OBJLAST((RefCast<DerivedType, BaseType>)), AS_CALL_CDECL_OBJLAST);

    String declReturnBaseConst("const " + String(baseClassName) + "@+ opImplCast() const");
    engine->RegisterObjectMethod(derivedClassName, declReturnBaseConst.CString(), AS_FUNCTION_OBJLAST((RefCast<DerivedType, BaseType>)), AS_CALL_CDECL_OBJLAST);

    // TODO fix all scripts to "cast(derivedClass)"

    //String declReturnDerived(String(derivedClassName) + "@+ opCast()");
    String declReturnDerived(String(derivedClassName) + "@+ opImplCast()");
    engine->RegisterObjectMethod(baseClassName, declReturnDerived.CString(), AS_FUNCTION_OBJLAST((RefCast<BaseType, DerivedType>)), AS_CALL_CDECL_OBJLAST);

    //String declReturnDerivedConst("const " + String(derivedClassName) + "@+ opCast() const");
    String declReturnDerivedConst("const " + String(derivedClassName) + "@+ opImplCast() const");
    engine->RegisterObjectMethod(baseClassName, declReturnDerivedConst.CString(), AS_FUNCTION_OBJLAST((RefCast<BaseType, DerivedType>)), AS_CALL_CDECL_OBJLAST);
}

// ================================================================================

// TODO Incorrect

// Template function for dynamic cast between two script value classes.
template <class SrcClass, class DstClass> DstClass* ValCast(SrcClass* src)
{
    if (!src)
        return nullptr;

    return dynamic_cast<DstClass*>(src);
}

template <class baseClass, class subclass> void RegisterSubclassValue(asIScriptEngine* engine, const char* baseClassName, const char* subclassName)
{
    assert(!strcmp(baseClassName, subclassName));

    String decl(String(baseClassName) + " opImplConvCast() const");
    engine->RegisterObjectMethod(subclassName, decl.CString(), asFUNCTION((ValCast<subclass, baseClass>)), asCALL_CDECL_OBJLAST);
}

// ================================================================================

// https://en.cppreference.com/w/cpp/types/enable_if

// We need detect implicitly-declared assign operator on complie time because Doxygen not povide this information
template<typename classType, typename std::enable_if<std::is_copy_assignable<classType>::value, int>::type = 0>
void RegisterImplicitlyDeclaredAssignOperatorIfPossible(asIScriptEngine* engine, const String& className)
{
    String decl = className + "& opAssign(const " + className + "&in)";
    engine->RegisterObjectMethod(className.CString(), decl.CString(), AS_METHODPR(classType, operator=, (const classType&), classType&), AS_CALL_THISCALL);
}

// This empty function need to prevent build errors when classType have no assing operator
template<typename classType, typename std::enable_if<!std::is_copy_assignable<classType>::value, int>::type = 0>
void RegisterImplicitlyDeclaredAssignOperatorIfPossible(asIScriptEngine* engine, const String& className)
{
}

// ================================================================================

static const AttributeInfo noAttributeInfoOLD{};

// To keep Xcode LLVM/Clang happy - it erroneously warns on unused functions defined below which are actually being referenced in the code
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif

static const AttributeInfo& SerializableGetAttributeInfoOLD(unsigned index, Serializable* ptr)
{
    const Vector<AttributeInfo>* attributes = ptr->GetAttributes();
    if (!attributes || index >= attributes->Size())
    {
        GetActiveASContext()->SetException("Index out of bounds");
        return noAttributeInfoOLD;
    }
    else
        return attributes->At(index);
}

// ================================================================================

// bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h
static bool ResourceLoadOLD(File* file, Resource* ptr)
{
    return file && ptr->Load(*file);
}

// bool Resource::Load(Deserializer &source) | File: ../Resource/Resource.h
static bool ResourceLoadVectorBufferOLD(VectorBuffer& buffer, Resource* ptr)
{
    return ptr->Load(buffer);
}

// bool Resource::LoadFile(const String &fileName) | File: ../Resource/Resource.h
static bool ResourceLoadByNameOLD(const String& fileName, Resource* ptr)
{
    return ptr->LoadFile(fileName);
}

// virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h
static bool ResourceSaveOLD(File* file, Resource* ptr)
{
    return file && ptr->Save(*file);
}

// virtual bool Resource::Save(Serializer &dest) const | File: ../Resource/Resource.h
static bool ResourceSaveVectorBufferOLD(VectorBuffer& buffer, Resource* ptr)
{
    return ptr->Save(buffer);
}

// virtual bool Resource::SaveFile(const String &fileName) const | File: ../Resource/Resource.h
static bool ResourceSaveByNameOLD(const String& fileName, Resource* ptr)
{
    return ptr->SaveFile(fileName);
}

// ================================================================================

template <class T> T* ConstructObject()
{
    auto* object = new T(GetScriptContext());
    object->AddRef();
    return object;
}

template <class T> T* ConstructNamedObject(const String& name)
{
    auto* object = new T(GetScriptContext());
    object->AddRef();
    object->SetName(name);
    return object;
}

/// Template function for registering a default constructor for a class derived from Object.
template <class T> void RegisterObjectConstructor(asIScriptEngine* engine, const char* className)
{
    String declFactory(String(className) + "@ f()");
    engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactory.CString(), AS_FUNCTION(ConstructObject<T>), AS_CALL_CDECL);
}

/// Template function for registering a named constructor for a class derived from Object.
template <class T> void RegisterNamedObjectConstructor(asIScriptEngine* engine, const char* className)
{
    String declFactoryWithName(String(className) + "@ f(const String&in)");
    engine->RegisterObjectBehaviour(className, asBEHAVE_FACTORY, declFactoryWithName.CString(), AS_FUNCTION(ConstructNamedObject<T>), AS_CALL_CDECL);
}

static bool SerializableLoad(File* file, Serializable* ptr)
{
    return file && ptr->Load(*file);
}

static bool SerializableLoadVectorBuffer(VectorBuffer& buffer, Serializable* ptr)
{
    return ptr->Load(buffer);
}

static bool SerializableSave(File* file, Serializable* ptr)
{
    return file && ptr->Save(*file);
}

static bool SerializableSaveVectorBuffer(VectorBuffer& buffer, Serializable* ptr)
{
    return ptr->Save(buffer);
}

#if __clang__
#pragma clang diagnostic pop
#endif

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
