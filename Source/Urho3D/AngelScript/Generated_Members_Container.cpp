// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// struct AllocatorBlock | File: ../Container/Allocator.h
void CollectMembers_AllocatorBlock(MemberCollection& members)
{
    // AllocatorNode* AllocatorBlock::free_
    // Not registered because pointer
    // AllocatorBlock* AllocatorBlock::next_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AllocatorBlock::nodeSize_", "uint nodeSize", offsetof(AllocatorBlock, nodeSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned AllocatorBlock::capacity_", "uint capacity", offsetof(AllocatorBlock, capacity_)));

}

// struct AllocatorNode | File: ../Container/Allocator.h
void CollectMembers_AllocatorNode(MemberCollection& members)
{
    // AllocatorNode* AllocatorNode::next_
    // Not registered because pointer

}

// class HashBase | File: ../Container/HashBase.h
void CollectMembers_HashBase(MemberCollection& members)
{
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const unsigned HashBase::MIN_BUCKETS", "const uint MIN_BUCKETS", (void*)&HashBase::MIN_BUCKETS));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const unsigned HashBase::MAX_LOAD_FACTOR", "const uint MAX_LOAD_FACTOR", (void*)&HashBase::MAX_LOAD_FACTOR));

}

// struct HashIteratorBase | File: ../Container/HashBase.h
void CollectMembers_HashIteratorBase(MemberCollection& members)
{
    // bool HashIteratorBase::operator !=(const HashIteratorBase& rhs) const
    // Only operator == is needed

    // HashNodeBase* HashIteratorBase::ptr_
    // Not registered because pointer

}

// struct HashNodeBase | File: ../Container/HashBase.h
void CollectMembers_HashNodeBase(MemberCollection& members)
{
    // HashNodeBase* HashNodeBase::down_
    // Not registered because pointer
    // HashNodeBase* HashNodeBase::prev_
    // Not registered because pointer
    // HashNodeBase* HashNodeBase::next_
    // Not registered because pointer

}

// struct LinkedListNode | File: ../Container/LinkedList.h
void CollectMembers_LinkedListNode(MemberCollection& members)
{
    // LinkedListNode* LinkedListNode::next_
    // Not registered because pointer

}

// class ListBase | File: ../Container/ListBase.h
void CollectMembers_ListBase(MemberCollection& members)
{
}

// struct ListIteratorBase | File: ../Container/ListBase.h
void CollectMembers_ListIteratorBase(MemberCollection& members)
{
    // bool ListIteratorBase::operator !=(const ListIteratorBase& rhs) const
    // Only operator == is needed

    // ListNodeBase* ListIteratorBase::ptr_
    // Not registered because pointer

}

// struct ListNodeBase | File: ../Container/ListBase.h
void CollectMembers_ListNodeBase(MemberCollection& members)
{
    // ListNodeBase* ListNodeBase::prev_
    // Not registered because pointer
    // ListNodeBase* ListNodeBase::next_
    // Not registered because pointer

}

// struct RefCount | File: ../Container/RefCounted.h
void CollectMembers_RefCount(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("int RefCount::refs_", "int refs", offsetof(RefCount, refs_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int RefCount::weakRefs_", "int weakRefs", offsetof(RefCount, weakRefs_)));

}

// class RefCounted | File: ../Container/RefCounted.h
void CollectMembers_RefCounted(MemberCollection& members)
{
    // void RefCounted::AddRef()
    // Not registered because have @manualbind mark
    // RefCount* RefCounted::RefCountPtr()
    // Error: type "RefCount*" can not automatically bind
    // void RefCounted::ReleaseRef()
    // Not registered because have @manualbind mark

    // RefCounted& RefCounted::operator =(const RefCounted& rhs) = delete
    // Not registered because deleted

}

// bool String::operator <(const String& rhs) const
static int String_bool_operatorles_constspStringamp(const String& lhs, const String& rhs)
{
    if (lhs < rhs)
        return -1;

    if (lhs > rhs)
        return 1;

    return 0;
}

// class String | File: ../Container/Str.h
void CollectMembers_String(MemberCollection& members)
{
    // String& String::Append(const char* str)
    // Error: type "const char*" can not automatically bind
    // String& String::Append(const char* str, unsigned length)
    // Error: type "const char*" can not automatically bind
    // String& String::AppendWithFormat(const char* formatString,...)
    // Error: type "const char*" can not automatically bind
    // String& String::AppendWithFormatArgs(const char* formatString, va_list args)
    // Error: type "const char*" can not automatically bind
    // ConstIterator String::Begin() const
    // Error: type "ConstIterator" can not automatically bind
    // Iterator String::Begin()
    // Error: type "Iterator" can not automatically bind
    // const char* String::CString() const
    // Error: type "const char*" can not automatically bind
    // int String::Compare(const char* str, bool caseSensitive = true) const
    // Error: type "const char*" can not automatically bind
    // ConstIterator String::End() const
    // Error: type "ConstIterator" can not automatically bind
    // Iterator String::End()
    // Error: type "Iterator" can not automatically bind
    // Iterator String::Erase(const Iterator& it)
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Erase(const Iterator& start, const Iterator& end)
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Insert(const Iterator& dest, char c)
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Insert(const Iterator& dest, const Iterator& start, const Iterator& end)
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Insert(const Iterator& dest, const String& str)
    // Error: type "const Iterator&" can not automatically bind
    // Iterator String::Replace(const Iterator& start, const Iterator& end, const String& replaceWith)
    // Error: type "const Iterator&" can not automatically bind
    // void String::Replace(unsigned pos, unsigned length, const char* replaceWith)
    // Error: type "const char*" can not automatically bind
    // void String::SetUTF8FromLatin1(const char* str)
    // Error: type "const char*" can not automatically bind
    // void String::SetUTF8FromWChar(const wchar_t* str)
    // Error: type "const wchar_t*" can not automatically bind
    // bool String::operator !=(const String& rhs) const
    // Only operator == is needed
    // bool String::operator !=(const char* rhs) const
    // Error: type "const char*" can not automatically bind
    // String String::operator +(const char* rhs) const
    // Error: type "const char*" can not automatically bind
    // String& String::operator +=(const char* rhs)
    // Error: type "const char*" can not automatically bind
    // String& String::operator +=(long rhs)
    // Not registered because have @nobind mark
    // String& String::operator +=(unsigned long rhs)
    // Not registered because have @nobind mark
    // bool String::operator <(const String& rhs) const
    // Registerd as opCmp separately
    // bool String::operator <(const char* rhs) const
    // Error: type "const char*" can not automatically bind
    // String& String::operator =(String&& rhs) noexcept
    // Error: type "String&&" can not automatically bind
    // String& String::operator =(const char* rhs)
    // Error: type "const char*" can not automatically bind
    // bool String::operator ==(const char* rhs) const
    // Error: type "const char*" can not automatically bind
    // bool String::operator>(const String& rhs) const
    // Registerd as opCmp separately
    // bool String::operator>(const char* rhs) const
    // Error: type "const char*" can not automatically bind

    members.methods_.Push(RegisterObjectMethodArgs("bool String::operator <(const String& rhs) const", "int opCmp(const String&in) const", AS_FUNCTION_OBJFIRST(String_bool_operatorles_constspStringamp), AS_CALL_CDECL_OBJFIRST));

    // template <class T> String& String::operator +=(const T& rhs)
    // Not registered because template
    // static Vector<String> String::Split(const char* str, char separator, bool keepEmptyStrings = false)
    // Error: type "const char*" can not automatically bind
    // static String String::Joined(const Vector<String>& subStrings, const String& glue)
    // Not registered because have @manualbind mark
    // static void String::EncodeUTF8(char*& dest, unsigned unicodeChar)
    // Error: type "char*&" can not automatically bind
    // static unsigned String::DecodeUTF8(const char*& src)
    // Error: type "const char*&" can not automatically bind
    // static unsigned String::CStringLength(const char* str)
    // Error: type "const char*" can not automatically bind
    // static int String::Compare(const char* lhs, const char* rhs, bool caseSensitive)
    // Error: type "const char*" can not automatically bind

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const unsigned String::NPOS", "const uint NPOS", (void*)&String::NPOS));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const unsigned String::MIN_CAPACITY", "const uint MIN_CAPACITY", (void*)&String::MIN_CAPACITY));
    members.staticFields_.Push(RegisterGlobalPropertyArgs("static const String String::EMPTY", "const String EMPTY", (void*)&String::EMPTY));

}

// class VectorBase | File: ../Container/VectorBase.h
void CollectMembers_VectorBase(MemberCollection& members)
{
}

// class WString | File: ../Container/Str.h
void CollectMembers_WString(MemberCollection& members)
{
    // const wchar_t& WString::At(unsigned index) const
    // Error: type "const wchar_t&" can not automatically bind
    // wchar_t& WString::At(unsigned index)
    // Error: type "wchar_t&" can not automatically bind
    // const wchar_t* WString::CString() const
    // Error: type "const wchar_t*" can not automatically bind
    // const wchar_t& WString::operator [](unsigned index) const
    // Error: type "const wchar_t&" can not automatically bind
    // wchar_t& WString::operator [](unsigned index)
    // Error: type "wchar_t&" can not automatically bind

}

} // namespace Urho3D
