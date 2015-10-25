//
// Copyright (c) 2008-2015 the Urho3D project.
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

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#else
#include <Urho3D/Urho3D.h>
#endif

#include "../Container/HashMap.h"
#include "../Container/Str.h"

#include <AngelScript/angelscript.h>

// Adapted from Angelscript's scriptarray, scriptdictionary & scriptstdstring add-ons, but with garbage collection disabled

namespace Urho3D
{

struct SArrayBuffer;
struct SArrayCache;

/// %Script array class.
class URHO3D_API CScriptArray
{
public:
    // Set the memory functions that should be used by all CScriptArrays
    static void SetMemoryFunctions(asALLOCFUNC_t allocFunc, asFREEFUNC_t freeFunc);

    // Factory functions
    static CScriptArray *Create(asIObjectType *ot);
    static CScriptArray *Create(asIObjectType *ot, asUINT length);
    static CScriptArray *Create(asIObjectType *ot, asUINT length, void *defaultValue);
    static CScriptArray *Create(asIObjectType *ot, void *listBuffer);

    // Memory management
    void AddRef() const;
    void Release() const;

    // Type information
    asIObjectType *GetArrayObjectType() const;
    int            GetArrayTypeId() const;
    int            GetElementTypeId() const;

    // Get the current size
    asUINT GetSize() const;

    // Returns true if the array is empty
    bool   IsEmpty() const;

    // Pre-allocates memory for elements
    void   Reserve(asUINT maxElements);

    // Resize the array
    void   Resize(asUINT numElements);

    // Get a pointer to an element. Returns 0 if out of bounds
    void       *At(asUINT index);
    const void *At(asUINT index) const;

    // Set value of an element. 
    // The value arg should be a pointer to the value that will be copied to the element.
    // Remember, if the array holds handles the value parameter should be the 
    // address of the handle. The refCount of the object will also be incremented
    void  SetValue(asUINT index, void *value);

    // Copy the contents of one array to another (only if the types are the same)
    CScriptArray &operator=(const CScriptArray&);

    // Compare two arrays
    bool operator==(const CScriptArray &) const;

    // Array manipulation
    void InsertAt(asUINT index, void *value);
    void RemoveAt(asUINT index);
    void InsertLast(void *value);
    void RemoveLast();
    void SortAsc();
    void SortDesc();
    void SortAsc(asUINT startAt, asUINT count);
    void SortDesc(asUINT startAt, asUINT count);
    void Sort(asUINT startAt, asUINT count, bool asc);
    void Reverse();
    int  Find(void *value) const;
    int  Find(asUINT startAt, void *value) const;
    int  FindByRef(void *ref) const;
    int  FindByRef(asUINT startAt, void *ref) const;

    // GC methods
    int  GetRefCount();
    void SetFlag();
    bool GetFlag();
    void EnumReferences(asIScriptEngine *engine);
    void ReleaseAllHandles(asIScriptEngine *engine);

protected:
    mutable int       refCount;
    mutable bool      gcFlag;
    asIObjectType    *objType;
    SArrayBuffer     *buffer;
    int               elementSize;
    int               subTypeId;

    // Constructors
    CScriptArray(asIObjectType *ot, void *initBuf); // Called from script when initialized with list
    CScriptArray(asUINT length, asIObjectType *ot);
    CScriptArray(asUINT length, void *defVal, asIObjectType *ot);
    CScriptArray(const CScriptArray &other);
    virtual ~CScriptArray();

    bool  Less(const void *a, const void *b, bool asc, asIScriptContext *ctx, SArrayCache *cache);
    void *GetArrayItemPointer(int index);
    void *GetDataPointer(void *buffer);
    void  Copy(void *dst, void *src);
    void  Precache();
    bool  CheckMaxSize(asUINT numElements);
    void  Resize(int delta, asUINT at);
    void  CreateBuffer(SArrayBuffer **buf, asUINT numElements);
    void  DeleteBuffer(SArrayBuffer *buf);
    void  CopyBuffer(SArrayBuffer *dst, SArrayBuffer *src);
    void  Construct(SArrayBuffer *buf, asUINT start, asUINT end);
    void  Destruct(SArrayBuffer *buf, asUINT start, asUINT end);
    bool  Equals(const void *a, const void *b, asIScriptContext *ctx, SArrayCache *cache) const;
};

class CScriptDictionary;

/// %Script dictionary value.
class URHO3D_API CScriptDictValue
{
public:
    // This class must not be declared as local variable in C++, because it needs 
    // to receive the script engine pointer in all operations. The engine pointer
    // is not kept as member in order to keep the size down
    CScriptDictValue();
    CScriptDictValue(asIScriptEngine *engine, void *value, int typeId);

    // Destructor must not be called without first calling FreeValue, otherwise a memory leak will occur
    ~CScriptDictValue();

    // Replace the stored value
    void Set(asIScriptEngine *engine, void *value, int typeId);
    void Set(asIScriptEngine *engine, const asINT64 &value);
    void Set(asIScriptEngine *engine, const double &value);

    // Gets the stored value. Returns false if the value isn't compatible with the informed typeId
    bool Get(asIScriptEngine *engine, void *value, int typeId) const;
    bool Get(asIScriptEngine *engine, asINT64 &value) const;
    bool Get(asIScriptEngine *engine, double &value) const;

    // Returns the type id of the stored value
    int  GetTypeId() const;

    // Free the stored value
    void FreeValue(asIScriptEngine *engine);

protected:
    friend class CScriptDictionary;

    union
    {
        asINT64 m_valueInt;
        double  m_valueFlt;
        void   *m_valueObj;
    };
    int m_typeId;
};

/// %Script dictionary class.
class URHO3D_API CScriptDictionary
{
public:
    // Factory functions
    static CScriptDictionary *Create(asIScriptEngine *engine);

    // Called from the script to instantiate a dictionary from an initialization list
    static CScriptDictionary *Create(asBYTE *buffer);

    // Reference counting
    void AddRef() const;
    void Release() const;

    // Reassign the dictionary
    CScriptDictionary &operator =(const CScriptDictionary &other);

    // Sets a key/value pair
    void Set(const String &key, void *value, int typeId);
    void Set(const String &key, const asINT64 &value);
    void Set(const String &key, const double &value);

    // Gets the stored value. Returns false if the value isn't compatible with the informed typeId
    bool Get(const String &key, void *value, int typeId) const;
    bool Get(const String &key, asINT64 &value) const;
    bool Get(const String &key, double &value) const;

    // Index accessors. If the dictionary is not const it inserts the value if it doesn't already exist
    // If the dictionary is const then a script exception is set if it doesn't exist and a null pointer is returned
    CScriptDictValue *operator[](const String &key);
    const CScriptDictValue *operator[](const String &key) const;

    // Returns the type id of the stored value, or negative if it doesn't exist
    int GetTypeId(const String &key) const;

    // Returns true if the key is set
    bool Exists(const String &key) const;

    // Returns true if there are no key/value pairs in the dictionary
    bool IsEmpty() const;

    // Returns the number of key/value pairs in the dictionary
    asUINT GetSize() const;

    // Deletes the key
    void Delete(const String &key);

    // Deletes all keys
    void DeleteAll();

    // Get an array of all keys
    CScriptArray *GetKeys() const;

public:
    /// STL style iterator for %Script dictionary class.
    class CIterator
    {
    public:
        void operator++();    // Pre-increment
        void operator++(int); // Post-increment

        // This is needed to support C++11 range-for
        CIterator &operator*();

        bool operator==(const CIterator &other) const;
        bool operator!=(const CIterator &other) const;

        // Accessors
        const String &GetKey() const;
        int                GetTypeId() const;
        bool               GetValue(asINT64 &value) const;
        bool               GetValue(double &value) const;
        bool               GetValue(void *value, int typeId) const;

    protected:
        friend class CScriptDictionary;

        CIterator();
        CIterator(const CScriptDictionary &dict,
                  HashMap<String, CScriptDictValue>::ConstIterator it);

        CIterator &operator=(const CIterator &) {return *this;} // Not used

        HashMap<String, CScriptDictValue>::ConstIterator m_it;
        const CScriptDictionary &m_dict;
    };

    CIterator begin() const;
    CIterator end() const;

    // Garbage collections behaviours
    int GetRefCount();
    void SetGCFlag();
    bool GetGCFlag();
    void EnumReferences(asIScriptEngine *engine);
    void ReleaseAllReferences(asIScriptEngine *engine);

protected:
    // Since the dictionary uses the asAllocMem and asFreeMem functions to allocate memory
    // the constructors are made protected so that the application cannot allocate it 
    // manually in a different way
    CScriptDictionary(asIScriptEngine *engine);
    CScriptDictionary(asBYTE *buffer);

    // We don't want anyone to call the destructor directly, it should be called through the Release method
    virtual ~CScriptDictionary();
    
    // Our properties
    asIScriptEngine *engine;
    mutable int refCount;
    mutable bool gcFlag;

    // TODO: memory: The allocator should use the asAllocMem and asFreeMem
    HashMap<String, CScriptDictValue> dict;
};

/// Register the array type to script.
void RegisterArray(asIScriptEngine* engine);
/// Register the dictionary type to script.
void RegisterDictionary(asIScriptEngine* engine);
/// Register String to script.
void RegisterString(asIScriptEngine* engine);

}
