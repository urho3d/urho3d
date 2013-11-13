//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Precompiled.h"
#include "Addons.h"

#include <cString>
#include <new>
#include <stdio.h>

// Adapted from Angelscript's scriptarray & scriptstdstring add-ons, but with garbage collection disabled
namespace Urho3D
{

using namespace std;

/// %Script array buffer.
struct SArrayBuffer
{
    asDWORD maxElements;
    asDWORD numElements;
    asBYTE  data[1];
};

/// %Script array cache.
struct SArrayCache
{
    asIScriptFunction *cmpFunc;
    asIScriptFunction *eqFunc;
    int cmpFuncReturnCode; // To allow better error message in case of multiple matches
    int eqFuncReturnCode;
};

// We just define a number here that we assume nobody else is using for 
// object type user data. The add-ons have reserved the numbers 1000 
// through 1999 for this purpose, so we should be fine.
const asPWORD ARRAY_CACHE = 1000;

static void CleanupObjectTypeArrayCache(asIObjectType *type)
{
    SArrayCache *cache = reinterpret_cast<SArrayCache*>(type->GetUserData(ARRAY_CACHE));
    if( cache )
        delete cache;
}

static CScriptArray* ScriptArrayFactory2(asIObjectType *ot, asUINT length)
{
    CScriptArray *a = new CScriptArray(length, ot);

    // It's possible the constructor raised a script exception, in which case we 
    // need to free the memory and return null instead, else we get a memory leak.
    asIScriptContext *ctx = asGetActiveContext();
    if( ctx && ctx->GetState() == asEXECUTION_EXCEPTION )
    {
        a->Release();
        return 0;
    }

    return a;
}

static CScriptArray* ScriptArrayListFactory(asIObjectType *ot, void *initList)
{
    CScriptArray *a = new CScriptArray(ot, initList);

    // It's possible the constructor raised a script exception, in which case we 
    // need to free the memory and return null instead, else we get a memory leak.
    asIScriptContext *ctx = asGetActiveContext();
    if( ctx && ctx->GetState() == asEXECUTION_EXCEPTION )
    {
        a->Release();
        return 0;
    }

    return a;
}

static CScriptArray* ScriptArrayFactoryDefVal(asIObjectType *ot, asUINT length, void *defVal)
{
    CScriptArray *a = new CScriptArray(length, defVal, ot);

    // It's possible the constructor raised a script exception, in which case we 
    // need to free the memory and return null instead, else we get a memory leak.
    asIScriptContext *ctx = asGetActiveContext();
    if( ctx && ctx->GetState() == asEXECUTION_EXCEPTION )
    {
        a->Release();
        return 0;
    }

    return a;
}

static CScriptArray* ScriptArrayFactory(asIObjectType *ot)
{
    return ScriptArrayFactory2(ot, 0);
}

// This optional callback is called when the template type is first used by the compiler.
// It allows the application to validate if the template can be instanciated for the requested 
// subtype at compile time, instead of at runtime. The output argument dontGarbageCollect
// allow the callback to tell the engine if the template instance type shouldn't be garbage collected, 
// i.e. no asOBJ_GC flag. 
static bool ScriptArrayTemplateCallback(asIObjectType *ot, bool &dontGarbageCollect)
{
    // Urho3D: nothing is garbage collected
    dontGarbageCollect = true;

    // Make sure the subtype can be instanciated with a default factory/constructor, 
    // otherwise we won't be able to instanciate the elements. 
    int typeId = ot->GetSubTypeId();
    if( typeId == asTYPEID_VOID )
        return false;
    if( (typeId & asTYPEID_MASK_OBJECT) && !(typeId & asTYPEID_OBJHANDLE) )
    {
        asIObjectType *subtype = ot->GetEngine()->GetObjectTypeById(typeId);
        asDWORD flags = subtype->GetFlags();
        if( (flags & asOBJ_VALUE) && !(flags & asOBJ_POD) )
        {
            // Verify that there is a default constructor
            bool found = false;
            for( asUINT n = 0; n < subtype->GetBehaviourCount(); n++ )
            {
                asEBehaviours beh;
                asIScriptFunction *func = subtype->GetBehaviourByIndex(n, &beh);
                if( beh != asBEHAVE_CONSTRUCT ) continue;

                if( func->GetParamCount() == 0 )
                {
                    // Found the default constructor
                    found = true;
                    break;
                }
            }

            if( !found )
            {
                // There is no default constructor
                return false;
            }
        }
        else if( (flags & asOBJ_REF) )
        {
            bool found = false;

            // If value assignment for ref type has been disabled then the array 
            // can be created if the type has a default factory function
            if( !ot->GetEngine()->GetEngineProperty(asEP_DISALLOW_VALUE_ASSIGN_FOR_REF_TYPE) )
            {
                // Verify that there is a default factory
                for( asUINT n = 0; n < subtype->GetFactoryCount(); n++ )
                {
                    asIScriptFunction *func = subtype->GetFactoryByIndex(n);
                    if( func->GetParamCount() == 0 )
                    {
                        // Found the default factory
                        found = true;
                        break;
                    }
                }
            }

            if( !found )
            {
                // No default factory
                return false;
            }
        }

        // If the object type is not garbage collected then the array also doesn't need to be
        if( !(flags & asOBJ_GC) )
            dontGarbageCollect = true;
    }
    else if( !(typeId & asTYPEID_OBJHANDLE) )
    {
        // Arrays with primitives cannot form circular references, 
        // thus there is no need to garbage collect them
        dontGarbageCollect = true;
    }

    // The type is ok
    return true;
}

CScriptArray &CScriptArray::operator=(const CScriptArray &other)
{
    // Only perform the copy if the array types are the same
    if( &other != this && 
        other.GetArrayObjectType() == GetArrayObjectType() )
    {
        // Make sure the arrays are of the same size
        Resize(other.buffer->numElements);

        // Copy the value of each element
        CopyBuffer(buffer, other.buffer);
    }

    return *this;
}

CScriptArray::CScriptArray(asIObjectType *ot, void *buf)
{
    refCount = 1;
    gcFlag = false;
    objType = ot;
    objType->AddRef();
    buffer = 0;

    Precache();

    asIScriptEngine *engine = ot->GetEngine();

    // Determine element size
    if( subTypeId & asTYPEID_MASK_OBJECT )
        elementSize = sizeof(asPWORD);
    else
        elementSize = engine->GetSizeOfPrimitiveType(subTypeId);

    // Determine the initial size from the buffer
    asUINT length = *(asUINT*)buf;

    // Make sure the array size isn't too large for us to handle
    if( !CheckMaxSize(length) )
    {
        // Don't continue with the initialization
        return;
    }

    // Copy the values of the array elements from the buffer
    if( (ot->GetSubTypeId() & asTYPEID_MASK_OBJECT) == 0 )
    {
        CreateBuffer(&buffer, length);

        // Copy the values of the primitive type into the internal buffer
        memcpy(At(0), (((asUINT*)buf)+1), length * elementSize);
    }
    else if( ot->GetSubTypeId() & asTYPEID_OBJHANDLE )
    {
        CreateBuffer(&buffer, length);

        // Copy the handles into the internal buffer
        memcpy(At(0), (((asUINT*)buf)+1), length * elementSize);

        // With object handles it is safe to clear the memory in the received buffer
        // instead of increasing the ref count. It will save time both by avoiding the
        // call the increase ref, and also relieve the engine from having to release
        // its references too
        memset((((asUINT*)buf)+1), 0, length * elementSize);
    }
    else if( ot->GetSubType()->GetFlags() & asOBJ_REF )
    {
        // Only allocate the buffer, but not the objects
        subTypeId |= asTYPEID_OBJHANDLE;
        CreateBuffer(&buffer, length);
        subTypeId &= ~asTYPEID_OBJHANDLE;

        // Copy the handles into the internal buffer
        memcpy(buffer->data, (((asUINT*)buf)+1), length * elementSize);

        // For ref types we can do the same as for handles, as they are 
        // implicitly stored as handles.
        memset((((asUINT*)buf)+1), 0, length * elementSize);
    }
    else
    {
        // TODO: Optimize by calling the copy constructor of the object instead of 
        //       constructing with the default constructor and then assigning the value
        // TODO: With C++11 ideally we should be calling the move constructor, instead
        //       of the copy constructor as the engine will just discard the objects in the
        //       buffer afterwards.
        CreateBuffer(&buffer, length);

        // For value types we need to call the opAssign for each individual object
        for( asUINT n = 0; n < length; n++ )
        {
            void *obj = At(n);
            asBYTE *srcObj = (asBYTE*)buf;
            srcObj += 4 + n*ot->GetSubType()->GetSize();
            engine->AssignScriptObject(obj, srcObj, ot->GetSubType());
        }
    }

    // Urho3D: garbage collection disabled
    /*
    // Notify the GC of the successful creation
    if( objType->GetFlags() & asOBJ_GC )
        objType->GetEngine()->NotifyGarbageCollectorOfNewObject(this, objType);
    */
}

CScriptArray::CScriptArray(asUINT length, asIObjectType *ot)
{
    refCount = 1;
    gcFlag = false;
    objType = ot;
    objType->AddRef();
    buffer = 0;

    Precache();

    // Determine element size
    if( subTypeId & asTYPEID_MASK_OBJECT )
        elementSize = sizeof(asPWORD);
    else
        elementSize = objType->GetEngine()->GetSizeOfPrimitiveType(subTypeId);

    // Make sure the array size isn't too large for us to handle
    if( !CheckMaxSize(length) )
    {
        // Don't continue with the initialization
        return;
    }

    CreateBuffer(&buffer, length);

    // Urho3D: garbage collection disabled
    /*
    // Notify the GC of the successful creation
    if( objType->GetFlags() & asOBJ_GC )
        objType->GetEngine()->NotifyGarbageCollectorOfNewObject(this, objType);
    */
}

CScriptArray::CScriptArray(const CScriptArray &other)
{
    refCount = 1;
    gcFlag = false;
    objType = other.objType;
    objType->AddRef();
    buffer = 0;

    Precache();

    elementSize = other.elementSize;

    // Urho3D: garbage collection disabled
    /*
    if( objType->GetFlags() & asOBJ_GC )
        objType->GetEngine()->NotifyGarbageCollectorOfNewObject(this, objType);
    */
    
    CreateBuffer(&buffer, 0);

    // Copy the content
    *this = other;
}

CScriptArray::CScriptArray(asUINT length, void *defVal, asIObjectType *ot)
{
    refCount = 1;
    gcFlag = false;
    objType = ot;
    objType->AddRef();
    buffer = 0;

    Precache();

    // Determine element size
    if( subTypeId & asTYPEID_MASK_OBJECT )
        elementSize = sizeof(asPWORD);
    else
        elementSize = objType->GetEngine()->GetSizeOfPrimitiveType(subTypeId);

    // Make sure the array size isn't too large for us to handle
    if( !CheckMaxSize(length) )
    {
        // Don't continue with the initialization
        return;
    }

    CreateBuffer(&buffer, length);

    // Urho3D: garbage collection disabled
    /*
    // Notify the GC of the successful creation
    if( objType->GetFlags() & asOBJ_GC )
        objType->GetEngine()->NotifyGarbageCollectorOfNewObject(this, objType);
    */
    
    // Initialize the elements with the default value
    for( asUINT n = 0; n < GetSize(); n++ )
        SetValue(n, defVal);
}

void CScriptArray::SetValue(asUINT index, void *value)
{
    // At() will take care of the out-of-bounds checking, though  
    // if called from the application then nothing will be done
    void *ptr = At(index);
    if( ptr == 0 ) return;

    if( (subTypeId & ~asTYPEID_MASK_SEQNBR) && !(subTypeId & asTYPEID_OBJHANDLE) )
        objType->GetEngine()->AssignScriptObject(ptr, value, objType->GetSubType());
    else if( subTypeId & asTYPEID_OBJHANDLE )
    {
        void *tmp = *(void**)ptr;
        *(void**)ptr = *(void**)value;
        objType->GetEngine()->AddRefScriptObject(*(void**)value, objType->GetSubType());
        if( tmp )
            objType->GetEngine()->ReleaseScriptObject(tmp, objType->GetSubType());
    }
    else if( subTypeId == asTYPEID_BOOL ||
             subTypeId == asTYPEID_INT8 ||
             subTypeId == asTYPEID_UINT8 )
        *(char*)ptr = *(char*)value;
    else if( subTypeId == asTYPEID_INT16 ||
             subTypeId == asTYPEID_UINT16 )
        *(short*)ptr = *(short*)value;
    else if( subTypeId == asTYPEID_INT32 ||
             subTypeId == asTYPEID_UINT32 ||
             subTypeId == asTYPEID_FLOAT ||
             subTypeId > asTYPEID_DOUBLE ) // enums have a type id larger than doubles
        *(int*)ptr = *(int*)value;
    else if( subTypeId == asTYPEID_INT64 ||
             subTypeId == asTYPEID_UINT64 ||
             subTypeId == asTYPEID_DOUBLE )
        *(double*)ptr = *(double*)value;
}

CScriptArray::~CScriptArray()
{
    if( buffer )
    {
        DeleteBuffer(buffer);
        buffer = 0;
    }
    if( objType ) objType->Release();
}

asUINT CScriptArray::GetSize() const
{
    return buffer->numElements;
}

bool CScriptArray::IsEmpty() const
{
    return buffer->numElements == 0;
}

void CScriptArray::Reserve(asUINT maxElements)
{
    if( maxElements <= buffer->maxElements )
        return;

    // Allocate memory for the buffer
    SArrayBuffer *newBuffer;
    #if defined(__S3E__) // Marmalade doesn't understand (nothrow)
    newBuffer = (SArrayBuffer*)new asBYTE[sizeof(SArrayBuffer)-1 + elementSize*maxElements];
    #else
    newBuffer = (SArrayBuffer*)new (nothrow) asBYTE[sizeof(SArrayBuffer)-1 + elementSize*maxElements];
    #endif
    if( newBuffer )
    {
        newBuffer->numElements = buffer->numElements;
        newBuffer->maxElements = maxElements;
    }
    else
    {
        // Out of memory
        asIScriptContext *ctx = asGetActiveContext();
        if( ctx )    
            ctx->SetException("Out of memory");
        return;
    }

    memcpy(newBuffer->data, buffer->data, buffer->numElements*elementSize);

    // Release the old buffer
    delete[] (asBYTE*)buffer;

    buffer = newBuffer;
}

void CScriptArray::Resize(asUINT numElements)
{
    if( numElements & 0x80000000 )
    {
        CheckMaxSize(numElements);
        return;
    }

    Resize((int)numElements - (int)buffer->numElements, (asUINT)-1);
}

// Internal
void CScriptArray::Resize(int delta, asUINT at)
{
    if( delta < 0 )
    {
        if( -delta > (int)buffer->numElements )
            delta = -(int)buffer->numElements;
        if( at > buffer->numElements + delta )
            at = buffer->numElements + delta;
    }
    else if( delta > 0 )
    {
        // Make sure the array size isn't too large for us to handle
        if( delta > 0 && !CheckMaxSize(buffer->numElements + delta) )
            return;

        if( at > buffer->numElements )
            at = buffer->numElements;
    }

    if( delta == 0 ) return;

    if( buffer->maxElements < buffer->numElements + delta )
    {
        // Allocate memory for the buffer
        SArrayBuffer *newBuffer;
        #if defined(__S3E__) // Marmalade doesn't understand (nothrow)
        newBuffer = (SArrayBuffer*)new asBYTE[sizeof(SArrayBuffer)-1 + elementSize*(buffer->numElements + delta)];
        #else
        newBuffer = (SArrayBuffer*)new (nothrow) asBYTE[sizeof(SArrayBuffer)-1 + elementSize*(buffer->numElements + delta)];
        #endif
        if( newBuffer )
        {
            newBuffer->numElements = buffer->numElements + delta;
            newBuffer->maxElements = newBuffer->numElements;
        }
        else
        {
            // Out of memory
            asIScriptContext *ctx = asGetActiveContext();
            if( ctx )    
                ctx->SetException("Out of memory");
            return;
        }

        memcpy(newBuffer->data, buffer->data, at*elementSize);
        if( at < buffer->numElements )
            memcpy(newBuffer->data + (at+delta)*elementSize, buffer->data + at*elementSize, (buffer->numElements-at)*elementSize);

        if( subTypeId & asTYPEID_MASK_OBJECT )
            Construct(newBuffer, at, at+delta);

        // Release the old buffer
        delete[] (asBYTE*)buffer;

        buffer = newBuffer;
    }
    else if( delta < 0 )
    {
        Destruct(buffer, at, at-delta);
        memmove(buffer->data + at*elementSize, buffer->data + (at-delta)*elementSize, (buffer->numElements - (at-delta))*elementSize);
        buffer->numElements += delta;
    }
    else
    {
        memmove(buffer->data + (at+delta)*elementSize, buffer->data + at*elementSize, (buffer->numElements - at)*elementSize);
        Construct(buffer, at, at+delta);
        buffer->numElements += delta;
    }
}

// internal
bool CScriptArray::CheckMaxSize(asUINT numElements)
{
    // This code makes sure the size of the buffer that is allocated 
    // for the array doesn't overflow and becomes smaller than requested

    asUINT maxSize = 0xFFFFFFFFul - sizeof(SArrayBuffer) + 1;
    if( subTypeId & asTYPEID_MASK_OBJECT )
        maxSize /= sizeof(void*);
    else if( elementSize > 0 )
        maxSize /= elementSize;

    if( numElements > maxSize )
    {
        asIScriptContext *ctx = asGetActiveContext();
        if( ctx )
        {
            // Set a script exception
            ctx->SetException("Too large array size");
        }

        return false;
    }

    // OK
    return true;
}

asIObjectType *CScriptArray::GetArrayObjectType() const
{
    return objType;
}

int CScriptArray::GetArrayTypeId() const
{
    return objType->GetTypeId();
}

int CScriptArray::GetElementTypeId() const
{
    return subTypeId;
}

void CScriptArray::InsertAt(asUINT index, void *value)
{
    if( index > buffer->numElements )
    {
        // If this is called from a script we raise a script exception
        asIScriptContext *ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException("Index out of bounds");
        return;
    }

    // Make room for the new element
    Resize(1, index);

    // Set the value of the new element
    SetValue(index, value);
}

void CScriptArray::InsertLast(void *value)
{
    InsertAt(buffer->numElements, value);
}

void CScriptArray::RemoveAt(asUINT index)
{
    if( index >= buffer->numElements )
    {
        // If this is called from a script we raise a script exception
        asIScriptContext *ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException("Index out of bounds");
        return;
    }

    // Remove the element
    Resize(-1, index);
}

void CScriptArray::RemoveLast()
{
    RemoveAt(buffer->numElements-1);
}

// Return a pointer to the array element. Returns 0 if the index is out of bounds
const void *CScriptArray::At(asUINT index) const
{
    if( buffer == 0 || index >= buffer->numElements )
    {
        // If this is called from a script we raise a script exception
        asIScriptContext *ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException("Index out of bounds");
        return 0;
    }

    if( (subTypeId & asTYPEID_MASK_OBJECT) && !(subTypeId & asTYPEID_OBJHANDLE) )
        return (void*)((size_t*)buffer->data)[index];
    else
        return buffer->data + elementSize*index;
}
void *CScriptArray::At(asUINT index)
{
    return const_cast<void*>(const_cast<const CScriptArray *>(this)->At(index));
}


// internal
void CScriptArray::CreateBuffer(SArrayBuffer **buf, asUINT numElements)
{
    if( subTypeId & asTYPEID_MASK_OBJECT )
    {
    #if defined(__S3E__) // Marmalade doesn't understand (nothrow)
        *buf = (SArrayBuffer*)new asBYTE[sizeof(SArrayBuffer)-1+sizeof(void*)*numElements];
    #else
        *buf = (SArrayBuffer*)new (nothrow) asBYTE[sizeof(SArrayBuffer)-1+sizeof(void*)*numElements];
    #endif
    }
    else
    {
        #if defined(__S3E__)
        *buf = (SArrayBuffer*)new asBYTE[sizeof(SArrayBuffer)-1+elementSize*numElements];
        #else
        *buf = (SArrayBuffer*)new (nothrow) asBYTE[sizeof(SArrayBuffer)-1+elementSize*numElements];
        #endif
    }

    if( *buf )
    {
        (*buf)->numElements = numElements;
        (*buf)->maxElements = numElements;
        Construct(*buf, 0, numElements);
    }
    else
    {
        // Oops, out of memory
        asIScriptContext *ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException("Out of memory");
    }
}

// internal
void CScriptArray::DeleteBuffer(SArrayBuffer *buf)
{
    Destruct(buf, 0, buf->numElements);

    // Free the buffer
    delete[] (asBYTE*)buf;
}

// internal
void CScriptArray::Construct(SArrayBuffer *buf, asUINT start, asUINT end)
{
    if( subTypeId & asTYPEID_OBJHANDLE )
    {
        // Set all object handles to null
        void *d = (void*)(buf->data + start * sizeof(void*));
        memset(d, 0, (end-start)*sizeof(void*));
    }
    else if( subTypeId & asTYPEID_MASK_OBJECT )
    {
        void **max = (void**)(buf->data + end * sizeof(void*));
        void **d = (void**)(buf->data + start * sizeof(void*));

        asIScriptEngine *engine = objType->GetEngine();
        asIObjectType *subType = objType->GetSubType();

        for( ; d < max; d++ )
            *d = (void*)engine->CreateScriptObject(subType);
    }
}

// internal
void CScriptArray::Destruct(SArrayBuffer *buf, asUINT start, asUINT end)
{
    if( subTypeId & asTYPEID_MASK_OBJECT )
    {
        asIScriptEngine *engine = objType->GetEngine();

        void **max = (void**)(buf->data + end * sizeof(void*));
        void **d   = (void**)(buf->data + start * sizeof(void*));

        for( ; d < max; d++ )
        {
            if( *d )
                engine->ReleaseScriptObject(*d, objType->GetSubType());
        }
    }
}

// internal
bool CScriptArray::Less(const void *a, const void *b, bool asc, asIScriptContext *ctx, SArrayCache *cache)
{
    if( !asc )
    {
        // Swap items
        const void *TEMP = a;
        a = b;
        b = TEMP;
    }

    if( !(subTypeId & ~asTYPEID_MASK_SEQNBR) )
    {
        // Simple compare of values
        switch( subTypeId )
        {
            #define COMPARE(T) *((T*)a) < *((T*)b)
            case asTYPEID_BOOL: return COMPARE(bool);
            case asTYPEID_INT8: return COMPARE(signed char);
            case asTYPEID_UINT8: return COMPARE(unsigned char);
            case asTYPEID_INT16: return COMPARE(signed short);
            case asTYPEID_UINT16: return COMPARE(unsigned short);
            case asTYPEID_INT32: return COMPARE(signed int);
            case asTYPEID_UINT32: return COMPARE(unsigned int);
            case asTYPEID_FLOAT: return COMPARE(float);
            case asTYPEID_DOUBLE: return COMPARE(double);
            default: return COMPARE(signed int); // All enums fall in this case
            #undef COMPARE
        }
    }
    else
    {
        int r = 0;

        if( subTypeId & asTYPEID_OBJHANDLE )
        {
            // Allow sort to work even if the array contains null handles
            if( *(void**)a == 0 ) return true;
            if( *(void**)b == 0 ) return false;
        }

        // Execute object opCmp
        if( cache && cache->cmpFunc )
        {
            // TODO: Add proper error handling
            r = ctx->Prepare(cache->cmpFunc); assert(r >= 0);

            if( subTypeId & asTYPEID_OBJHANDLE )
            {
                r = ctx->SetObject(*((void**)a)); assert(r >= 0);
                r = ctx->SetArgObject(0, *((void**)b)); assert(r >= 0);
            }
            else
            {
                r = ctx->SetObject((void*)a); assert(r >= 0);
                r = ctx->SetArgObject(0, (void*)b); assert(r >= 0);
            }

            r = ctx->Execute();

            if( r == asEXECUTION_FINISHED )
            {
                return (int)ctx->GetReturnDWord() < 0;
            }
        }
    }

    return false;
}

void CScriptArray::Reverse()
{
    asUINT size = GetSize();

    if( size >= 2 )
    {
        asBYTE TEMP[16];

        for( asUINT i = 0; i < size / 2; i++ )
        {
            Copy(TEMP, GetArrayItemPointer(i));
            Copy(GetArrayItemPointer(i), GetArrayItemPointer(size - i - 1));
            Copy(GetArrayItemPointer(size - i - 1), TEMP);
        }
    }
}

bool CScriptArray::operator==(const CScriptArray &other) const
{
    if( objType != other.objType )
        return false;

    if( GetSize() != other.GetSize() )
        return false;

    asIScriptContext *cmpContext = 0;
    bool isNested = false;

    if( subTypeId & ~asTYPEID_MASK_SEQNBR )
    {
        // Try to reuse the active context
        cmpContext = asGetActiveContext();
        if( cmpContext )
        {
            if( cmpContext->PushState() >= 0 )
                isNested = true;
            else
                cmpContext = 0;
        }
        if( cmpContext == 0 )
        {
            // TODO: Ideally this context would be retrieved from a pool, so we don't have to 
            //       create a new one everytime. We could keep a context with the array object 
            //       but that would consume a lot of resources as each context is quite heavy.
            cmpContext = objType->GetEngine()->CreateContext();
        }
    }
    
    // Check if all elements are equal
    bool isEqual = true;
    SArrayCache *cache = reinterpret_cast<SArrayCache*>(objType->GetUserData(ARRAY_CACHE));
    for( asUINT n = 0; n < GetSize(); n++ )
        if( !Equals(At(n), other.At(n), cmpContext, cache) )
        {
            isEqual = false;
            break;
        }

    if( cmpContext )
        if( isNested )
        {
            asEContextState state = cmpContext->GetState();
            cmpContext->PopState();
            if( state == asEXECUTION_ABORTED )
                cmpContext->Abort();
        }
        else
            cmpContext->Release();

    return isEqual;
}

// internal
bool CScriptArray::Equals(const void *a, const void *b, asIScriptContext *ctx, SArrayCache *cache) const
{
    if( !(subTypeId & ~asTYPEID_MASK_SEQNBR) )
    {
        // Simple compare of values
        switch( subTypeId )
        {
            #define COMPARE(T) *((T*)a) == *((T*)b)
            case asTYPEID_BOOL: return COMPARE(bool);
            case asTYPEID_INT8: return COMPARE(signed char);
            case asTYPEID_UINT8: return COMPARE(unsigned char);
            case asTYPEID_INT16: return COMPARE(signed short);
            case asTYPEID_UINT16: return COMPARE(unsigned short);
            case asTYPEID_INT32: return COMPARE(signed int);
            case asTYPEID_UINT32: return COMPARE(unsigned int);
            case asTYPEID_FLOAT: return COMPARE(float);
            case asTYPEID_DOUBLE: return COMPARE(double);
            default: return COMPARE(signed int); // All enums fall here
            #undef COMPARE
        }
    }
    else
    {
        int r = 0;

        if( subTypeId & asTYPEID_OBJHANDLE )
        {
            // Allow the find to work even if the array contains null handles
            if( *(void**)a == *(void**)b ) return true;
        }

        // Execute object opEquals if available
        if( cache && cache->eqFunc )
        {
            // TODO: Add proper error handling
            r = ctx->Prepare(cache->eqFunc); assert(r >= 0);

            if( subTypeId & asTYPEID_OBJHANDLE )
            {
                r = ctx->SetObject(*((void**)a)); assert(r >= 0);
                r = ctx->SetArgObject(0, *((void**)b)); assert(r >= 0);
            }
            else
            {
                r = ctx->SetObject((void*)a); assert(r >= 0);
                r = ctx->SetArgObject(0, (void*)b); assert(r >= 0);
            }

            r = ctx->Execute();

            if( r == asEXECUTION_FINISHED )
                return ctx->GetReturnByte() != 0;

            return false;
        }

        // Execute object opCmp if available
        if( cache && cache->cmpFunc )
        {
            // TODO: Add proper error handling
            r = ctx->Prepare(cache->cmpFunc); assert(r >= 0);

            if( subTypeId & asTYPEID_OBJHANDLE )
            {
                r = ctx->SetObject(*((void**)a)); assert(r >= 0);
                r = ctx->SetArgObject(0, *((void**)b)); assert(r >= 0);
            }
            else
            {
                r = ctx->SetObject((void*)a); assert(r >= 0);
                r = ctx->SetArgObject(0, (void*)b); assert(r >= 0);
            }

            r = ctx->Execute();

            if( r == asEXECUTION_FINISHED )
                return (int)ctx->GetReturnDWord() == 0;

            return false;
        }
    }

    return false;
}

int CScriptArray::Find(void *value) const
{
    return Find(0, value);
}

int CScriptArray::Find(asUINT index, void *value) const
{
    // Check if the subtype really supports find()
    // TODO: Can't this be done at compile time too by the template callback
    SArrayCache *cache = 0;
    if( subTypeId & ~asTYPEID_MASK_SEQNBR )
    {
        cache = reinterpret_cast<SArrayCache*>(objType->GetUserData(ARRAY_CACHE));
        if( !cache || (cache->cmpFunc == 0 && cache->eqFunc == 0) )
        {
            asIScriptContext *ctx = asGetActiveContext();
            asIObjectType* subType = objType->GetEngine()->GetObjectTypeById(subTypeId);

            // Throw an exception
            if( ctx )
            {
                char tmp[512];

                if( cache && cache->eqFuncReturnCode == asMULTIPLE_FUNCTIONS )
#if defined(_MSC_VER) && _MSC_VER >= 1500 && !defined(__S3E__)
                    sprintf_s(tmp, 512, "Type '%s' has multiple matching opEquals or opCmp methods", subType->GetName());
#else
                    sprintf(tmp, "Type '%s' has multiple matching opEquals or opCmp methods", subType->GetName());
#endif
                else
#if defined(_MSC_VER) && _MSC_VER >= 1500 && !defined(__S3E__)
                    sprintf_s(tmp, 512, "Type '%s' does not have a matching opEquals or opCmp method", subType->GetName());
#else
                    sprintf(tmp, "Type '%s' does not have a matching opEquals or opCmp method", subType->GetName());
#endif
                ctx->SetException(tmp);
            }

            return -1;
        }
    }

    asIScriptContext *cmpContext = 0;
    bool isNested = false;

    if( subTypeId & ~asTYPEID_MASK_SEQNBR )
    {
        // Try to reuse the active context
        cmpContext = asGetActiveContext();
        if( cmpContext )
        {
            if( cmpContext->PushState() >= 0 )
                isNested = true;
            else
                cmpContext = 0;
        }
        if( cmpContext == 0 )
        {
            // TODO: Ideally this context would be retrieved from a pool, so we don't have to 
            //       create a new one everytime. We could keep a context with the array object 
            //       but that would consume a lot of resources as each context is quite heavy.
            cmpContext = objType->GetEngine()->CreateContext();
        }
    }

    // Find the matching element
    int ret = -1;
    asUINT size = GetSize();

    if( index < size )
    {
        for( asUINT i = index; i < size; i++ )
        {
            // value passed by reference
            if( Equals(At(i), (value), cmpContext, cache) )
            {
                ret = (int)i;
                break;
            }
        }
    }

    if( cmpContext )
        if( isNested )
        {
            asEContextState state = cmpContext->GetState();
            cmpContext->PopState();
            if( state == asEXECUTION_ABORTED )
                cmpContext->Abort();
        }
        else
            cmpContext->Release();

    return ret;
}



// internal
// Copy object handle or primitive value
void CScriptArray::Copy(void *dst, void *src)
{
    memcpy(dst, src, elementSize);
}


// internal
// Return pointer to array item (object handle or primitive value)
void *CScriptArray::GetArrayItemPointer(int index)
{
    return buffer->data + index * elementSize;
}

// internal
// Return pointer to data in buffer (object or primitive)
void *CScriptArray::GetDataPointer(void *buffer)
{
    if ((subTypeId & asTYPEID_MASK_OBJECT) && !(subTypeId & asTYPEID_OBJHANDLE) )
    {
        // Real address of object
        return reinterpret_cast<void*>(*(size_t*)buffer);
    }
    else
    {
        // Primitive is just a raw data
        return buffer;
    }
}


// Sort ascending
void CScriptArray::SortAsc()
{
    Sort(0, GetSize(), true);
}

// Sort ascending
void CScriptArray::SortAsc(asUINT index, asUINT count)
{
    Sort(index, count, true);
}

// Sort descending
void CScriptArray::SortDesc()
{
    Sort(0, GetSize(), false);
}

// Sort descending
void CScriptArray::SortDesc(asUINT index, asUINT count)
{
    Sort(index, count, false);
}


// internal
void CScriptArray::Sort(asUINT index, asUINT count, bool asc)
{
    // Subtype isn't primitive and doesn't have opCmp
    SArrayCache *cache = reinterpret_cast<SArrayCache*>(objType->GetUserData(ARRAY_CACHE));
    if( subTypeId & ~asTYPEID_MASK_SEQNBR )
    {
        if( !cache || cache->cmpFunc == 0 )
        {
            asIScriptContext *ctx = asGetActiveContext();
            asIObjectType* subType = objType->GetEngine()->GetObjectTypeById(subTypeId);

            // Throw an exception
            if( ctx )
            {
                char tmp[512];

                if( cache && cache->cmpFuncReturnCode == asMULTIPLE_FUNCTIONS )
#if defined(_MSC_VER) && _MSC_VER >= 1500 && !defined(__S3E__)
                    sprintf_s(tmp, 512, "Type '%s' has multiple matching opCmp methods", subType->GetName());
#else
                    sprintf(tmp, "Type '%s' has multiple matching opCmp methods", subType->GetName());
#endif
                else
#if defined(_MSC_VER) && _MSC_VER >= 1500 && !defined(__S3E__)
                    sprintf_s(tmp, 512, "Type '%s' does not have a matching opCmp method", subType->GetName());
#else
                    sprintf(tmp, "Type '%s' does not have a matching opCmp method", subType->GetName());
#endif

                ctx->SetException(tmp);
            }

            return;
        }
    }

    // No need to sort
    if( count < 2 )
    {
        return;
    }

    int start = index;
    int end = index + count;

    // Check if we could access invalid item while sorting
    if( start >= (int)buffer->numElements || end > (int)buffer->numElements )
    {
        asIScriptContext *ctx = asGetActiveContext();

        // Throw an exception
        if( ctx )
        {
            ctx->SetException("Index out of bounds");
        }

        return;
    }

    asBYTE tmp[16];
    asIScriptContext *cmpContext = 0;
    bool isNested = false;

    if( subTypeId & ~asTYPEID_MASK_SEQNBR )
    {
        // Try to reuse the active context
        cmpContext = asGetActiveContext();
        if( cmpContext )
        {
            if( cmpContext->PushState() >= 0 )
                isNested = true;
            else
                cmpContext = 0;
        }
        if( cmpContext == 0 )
        {
            // TODO: Ideally this context would be retrieved from a pool, so we don't have to 
            //       create a new one everytime. We could keep a context with the array object 
            //       but that would consume a lot of resources as each context is quite heavy.
            cmpContext = objType->GetEngine()->CreateContext();
        }
    }

    // Insertion sort
    for( int i = start + 1; i < end; i++ )
    {
        Copy(tmp, GetArrayItemPointer(i));

        int j = i - 1;

        while( j >= start && Less(GetDataPointer(tmp), At(j), asc, cmpContext, cache) )
        {
            Copy(GetArrayItemPointer(j + 1), GetArrayItemPointer(j));
            j--;
        }

        Copy(GetArrayItemPointer(j + 1), tmp);
    }

    if( cmpContext )
        if( isNested )
        {
            asEContextState state = cmpContext->GetState();
            cmpContext->PopState();
            if( state == asEXECUTION_ABORTED )
                cmpContext->Abort();
        }
        else
            cmpContext->Release();
}

// internal
void CScriptArray::CopyBuffer(SArrayBuffer *dst, SArrayBuffer *src)
{
    asIScriptEngine *engine = objType->GetEngine();
    if( subTypeId & asTYPEID_OBJHANDLE )
    {
        // Copy the references and increase the reference counters
        if( dst->numElements > 0 && src->numElements > 0 )
        {
            int count = dst->numElements > src->numElements ? src->numElements : dst->numElements;

            void **max = (void**)(dst->data + count * sizeof(void*));
            void **d   = (void**)dst->data;
            void **s   = (void**)src->data;
            
            for( ; d < max; d++, s++ )
            {
                void *tmp = *d;
                *d = *s;
                if( *d )
                    engine->AddRefScriptObject(*d, objType->GetSubType());
                // Release the old ref after incrementing the new to avoid problem incase it is the same ref
                if( tmp )
                    engine->ReleaseScriptObject(tmp, objType->GetSubType());
            }
        }
    }
    else
    {
        if( dst->numElements > 0 && src->numElements > 0 )
        {
            int count = dst->numElements > src->numElements ? src->numElements : dst->numElements;
            if( subTypeId & asTYPEID_MASK_OBJECT )
            {
                // Call the assignment operator on all of the objects
                void **max = (void**)(dst->data + count * sizeof(void*));
                void **d   = (void**)dst->data;
                void **s   = (void**)src->data;

                asIObjectType *subType = objType->GetSubType();
                for( ; d < max; d++, s++ )
                    engine->AssignScriptObject(*d, *s, subType);
            }
            else
            {
                // Primitives are copied byte for byte
                memcpy(dst->data, src->data, count*elementSize);
            }
        }
    }
}

// internal
// Precache some info
void CScriptArray::Precache()
{
    subTypeId = objType->GetSubTypeId();

    // Check if it is an array of objects. Only for these do we need to cache anything
    // Type ids for primitives and enums only has the sequence number part
    if( !(subTypeId & ~asTYPEID_MASK_SEQNBR) )
        return;
        
    // The opCmp and opEquals methods are cached because the searching for the
    // methods is quite time consuming if a lot of array objects are created.

    // First check if a cache already exists for this array type
    SArrayCache *cache = reinterpret_cast<SArrayCache*>(objType->GetUserData(ARRAY_CACHE));
    if( cache )    return;

    // We need to make sure the cache is created only once, even  
    // if multiple threads reach the same point at the same time
    asAcquireExclusiveLock();

    // Now that we got the lock, we need to check again to make sure the 
    // cache wasn't created while we were waiting for the lock
    cache = reinterpret_cast<SArrayCache*>(objType->GetUserData(ARRAY_CACHE));
    if( cache )
    {
        asReleaseExclusiveLock();
        return;
    }

    // Create the cache
    cache = new SArrayCache();
    memset(cache, 0, sizeof(SArrayCache));

    // If the sub type is a handle to const, then the methods must be const too
    bool mustBeConst = (subTypeId & asTYPEID_HANDLETOCONST) ? true : false;

    asIObjectType *subType = objType->GetEngine()->GetObjectTypeById(subTypeId);
    if( subType )
    {
        for( asUINT i = 0; i < subType->GetMethodCount(); i++ )
        {
            asIScriptFunction *func = subType->GetMethodByIndex(i);

            if( func->GetParamCount() == 1 && (!mustBeConst || func->IsReadOnly()) )
            {
                asDWORD flags = 0;
                int returnTypeId = func->GetReturnTypeId(&flags);

                // The method must not return a reference
                if( flags != asTM_NONE )
                    continue;

                // opCmp returns an int and opEquals returns a bool
                bool isCmp = false, isEq = false;
                if( returnTypeId == asTYPEID_INT32 && strcmp(func->GetName(), "opCmp") == 0 )
                    isCmp = true;
                if( returnTypeId == asTYPEID_BOOL && strcmp(func->GetName(), "opEquals") == 0 )
                    isEq = true;

                if( !isCmp && !isEq )
                    continue;

                // The parameter must either be a reference to the subtype or a handle to the subtype            
                int paramTypeId = func->GetParamTypeId(0, &flags);

                if( (paramTypeId & ~(asTYPEID_OBJHANDLE|asTYPEID_HANDLETOCONST)) != (subTypeId &  ~(asTYPEID_OBJHANDLE|asTYPEID_HANDLETOCONST)) )
                    continue;

                if( (flags & asTM_INREF) )
                {
                    if( (paramTypeId & asTYPEID_OBJHANDLE) || mustBeConst && !(flags & asTM_CONST) )
                        continue;
                }
                else if( paramTypeId & asTYPEID_OBJHANDLE )
                {
                    if( mustBeConst && !(paramTypeId & asTYPEID_HANDLETOCONST) )
                        continue;
                }
                else
                    continue;

                if( isCmp )
                {
                    if( cache->cmpFunc || cache->cmpFuncReturnCode )
                    {
                        cache->cmpFunc = 0;
                        cache->cmpFuncReturnCode = asMULTIPLE_FUNCTIONS;
                    }
                    else
                        cache->cmpFunc = func;
                }
                else if( isEq )
                {
                    if( cache->eqFunc || cache->eqFuncReturnCode )
                    {
                        cache->eqFunc = 0;
                        cache->eqFuncReturnCode = asMULTIPLE_FUNCTIONS;
                    }
                    else
                        cache->eqFunc = func;
                }
            }
        }
    }

    if( cache->eqFunc == 0 && cache->eqFuncReturnCode == 0 )
        cache->eqFuncReturnCode = asNO_FUNCTION;
    if( cache->cmpFunc == 0 && cache->cmpFuncReturnCode == 0 )
        cache->cmpFuncReturnCode = asNO_FUNCTION;

    // Set the user data only at the end so others that retrieve it will know it is complete
    objType->SetUserData(cache, ARRAY_CACHE);

    asReleaseExclusiveLock();
}

// GC behaviour
void CScriptArray::EnumReferences(asIScriptEngine *engine)
{
    // If the array is holding handles, then we need to notify the GC of them
    if( subTypeId & asTYPEID_MASK_OBJECT )
    {
        void **d = (void**)buffer->data;
        for( asUINT n = 0; n < buffer->numElements; n++ )
        {
            if( d[n] )
                engine->GCEnumCallback(d[n]);
        }
    }
}

// GC behaviour
void CScriptArray::ReleaseAllHandles(asIScriptEngine *engine)
{
    // Resizing to zero will release everything
    Resize(0);
}

void CScriptArray::AddRef() const
{
    // Clear the GC flag then increase the counter
    gcFlag = false;
    asAtomicInc(refCount);
}

void CScriptArray::Release() const
{
    // Clearing the GC flag then descrease the counter
    gcFlag = false;
    if( asAtomicDec(refCount) == 0 )
    {
        // When reaching 0 no more references to this instance 
        // exists and the object should be destroyed
        delete this;
    }
}

// GC behaviour
int CScriptArray::GetRefCount()
{
    return refCount;
}

// GC behaviour
void CScriptArray::SetFlag()
{
    gcFlag = true;
}

// GC behaviour
bool CScriptArray::GetFlag()
{
    return gcFlag;
}

static void ScriptArrayClear(CScriptArray* ptr)
{
    ptr->Resize(0);
}

void RegisterArray(asIScriptEngine* engine)
{
    // Register the object type user data clean up
    engine->SetObjectTypeUserDataCleanupCallback(CleanupObjectTypeArrayCache, ARRAY_CACHE);
    engine->RegisterObjectType("Array<class T>", 0, asOBJ_REF | asOBJ_TEMPLATE);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in, bool&out)", asFUNCTION(ScriptArrayTemplateCallback), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in)", asFUNCTIONPR(ScriptArrayFactory, (asIObjectType*), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in, uint)", asFUNCTIONPR(ScriptArrayFactory2, (asIObjectType*, asUINT), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in, uint, const T& in)", asFUNCTIONPR(ScriptArrayFactoryDefVal, (asIObjectType*, asUINT, void *), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_LIST_FACTORY, "Array<T>@ f(int&in type, int&in list) {repeat T}", asFUNCTIONPR(ScriptArrayListFactory, (asIObjectType*, void*), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_ADDREF, "void f()", asMETHOD(CScriptArray,AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_RELEASE, "void f()", asMETHOD(CScriptArray,Release), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "T& opIndex(uint)", asMETHODPR(CScriptArray, At, (unsigned), void*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "const T& opIndex(uint) const", asMETHODPR(CScriptArray, At, (unsigned), void*), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "Array<T>& opAssign(const Array<T>& in)", asMETHOD(CScriptArray, operator=), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Insert(uint, const T& in)", asMETHOD(CScriptArray, InsertAt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Erase(uint)", asMETHOD(CScriptArray, RemoveAt), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Push(const T& in)", asMETHOD(CScriptArray, InsertLast), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Pop()", asMETHOD(CScriptArray, RemoveLast), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Resize(uint)", asMETHODPR(CScriptArray, Resize, (asUINT), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Clear()", asFUNCTION(ScriptArrayClear), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("Array<T>", "void Sort()", asMETHODPR(CScriptArray, SortAsc, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Sort(uint, uint)", asMETHODPR(CScriptArray, SortAsc, (asUINT, asUINT), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void SortReverse()", asMETHODPR(CScriptArray, SortDesc, (), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void SortReverse(uint, uint)", asMETHODPR(CScriptArray, SortDesc, (asUINT, asUINT), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void Reverse()", asMETHOD(CScriptArray, Reverse), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "int Find(const T&in) const", asMETHODPR(CScriptArray, Find, (void*) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "int Find(uint, const T&in) const", asMETHODPR(CScriptArray, Find, (asUINT, void*) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "bool opEquals(const Array<T>&in) const", asMETHOD(CScriptArray, operator==), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "uint get_length() const", asMETHOD(CScriptArray, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void set_length(uint)", asMETHODPR(CScriptArray, Resize, (asUINT), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "bool get_empty() const", asMETHOD(CScriptArray, IsEmpty), asCALL_THISCALL);
    engine->RegisterDefaultArrayType("Array<T>");
}

CScriptDictionary::CScriptDictionary(asIScriptEngine *engine)
{
    // We start with one reference
    refCount = 1;
    gcFlag = false;

    // Keep a reference to the engine for as long as we live
    // We don't increment the reference counter, because the 
    // engine will hold a pointer to the object. 
    this->engine = engine;

    // Urho3D: garbage collection disabled
    /*
    // Notify the garbage collector of this object
    // TODO: The type id should be cached
    engine->NotifyGarbageCollectorOfNewObject(this, engine->GetObjectTypeByName("dictionary"));
    */
}

CScriptDictionary::CScriptDictionary(asBYTE *buffer)
{
    // We start with one reference
    refCount = 1;
    gcFlag = false;

    // This constructor will always be called from a script
    // so we can get the engine from the active context
    asIScriptContext *ctx = asGetActiveContext();
    engine = ctx->GetEngine();

    // Urho3D: garbage collection disable
    /*
    // Notify the garbage collector of this object
    // TODO: The type id should be cached
    engine->NotifyGarbageCollectorOfNewObject(this, engine->GetObjectTypeByName("dictionary"));
    */

    // Initialize the dictionary from the buffer
    asUINT length = *(asUINT*)buffer;
    buffer += 4;

    while( length-- )
    {
        // Align the buffer pointer on a 4 byte boundary in 
        // case previous value was smaller than 4 bytes
        if( asPWORD(buffer) & 0x3 )
            buffer += 4 - (asPWORD(buffer) & 0x3);

        // Get the name value pair from the buffer and insert it in the dictionary
        String name = *(String*)buffer;
        buffer += sizeof(String);

        // Get the type id of the value
        int typeId = *(int*)buffer;
        buffer += sizeof(int);

        // Depending on the type id, the value will inline in the buffer or a pointer
        void *ref = (void*)buffer;

        if( typeId >= asTYPEID_INT8 && typeId <= asTYPEID_DOUBLE )
        {
            // Convert primitive values to either int64 or double, so we can use the overloaded Set methods
            asINT64 i64;
            double d;
            switch( typeId )
            {
            case asTYPEID_INT8: i64 = *(char*)ref; break;
            case asTYPEID_INT16: i64 = *(short*)ref; break;
            case asTYPEID_INT32: i64 = *(int*)ref; break;
            case asTYPEID_INT64: i64 = *(asINT64*)ref; break;
            case asTYPEID_UINT8: i64 = *(unsigned char*)ref; break;
            case asTYPEID_UINT16: i64 = *(unsigned short*)ref; break;
            case asTYPEID_UINT32: i64 = *(unsigned int*)ref; break;
            case asTYPEID_UINT64: i64 = *(asINT64*)ref; break;
            case asTYPEID_FLOAT: d = *(float*)ref; break;
            case asTYPEID_DOUBLE: d = *(double*)ref; break;
            }
            
            if( typeId >= asTYPEID_FLOAT )
                Set(name, d);
            else
                Set(name, i64);
        }
        else
        {
            if( (typeId & asTYPEID_MASK_OBJECT) && 
                !(typeId & asTYPEID_OBJHANDLE) && 
                (engine->GetObjectTypeById(typeId)->GetFlags() & asOBJ_REF) )
            {
                // Dereference the pointer to get the reference to the actual object
                ref = *(void**)ref;
            }

            Set(name, ref, typeId);
        }

        // Advance the buffer pointer with the size of the value
        if( typeId & asTYPEID_MASK_OBJECT )
        {
            asIObjectType *ot = engine->GetObjectTypeById(typeId);
            if( ot->GetFlags() & asOBJ_VALUE )
                buffer += ot->GetSize();
            else
                buffer += sizeof(void*);
        }
        else if( typeId == 0 )
        {
            // null pointer
            buffer += sizeof(void*);
        }
        else
        {
            buffer += engine->GetSizeOfPrimitiveType(typeId);
        }
    }
}

CScriptDictionary::~CScriptDictionary()
{
    // Delete all keys and values
    DeleteAll();
}

void CScriptDictionary::AddRef() const
{
    // We need to clear the GC flag
    gcFlag = false;
    asAtomicInc(refCount);
}

void CScriptDictionary::Release() const
{
    // We need to clear the GC flag
    gcFlag = false;
    if( asAtomicDec(refCount) == 0 )
        delete this;
}

int CScriptDictionary::GetRefCount()
{
    return refCount;
}

void CScriptDictionary::SetGCFlag()
{
    gcFlag = true;
}

bool CScriptDictionary::GetGCFlag()
{
    return gcFlag;
}

void CScriptDictionary::EnumReferences(asIScriptEngine *engine)
{
    // Call the gc enum callback for each of the objects
    HashMap<String, valueStruct>::Iterator it;
    for( it = dict.Begin(); it != dict.End(); it++ )
    {
        if( it->second_.typeId & asTYPEID_MASK_OBJECT )
            engine->GCEnumCallback(it->second_.valueObj);
    }
}

void CScriptDictionary::ReleaseAllReferences(asIScriptEngine * /*engine*/)
{
    // We're being told to release all references in 
    // order to break circular references for dead objects
    DeleteAll();
}

CScriptDictionary &CScriptDictionary::operator =(const CScriptDictionary &other)
{
    // Clear everything we had before
    DeleteAll();

    // Do a shallow copy of the dictionary
    HashMap<String, valueStruct>::ConstIterator it;
    for( it = other.dict.Begin(); it != other.dict.End(); it++ )
    {
        if( it->second_.typeId & asTYPEID_OBJHANDLE )
            Set(it->first_, (void*)&it->second_.valueObj, it->second_.typeId);
        else if( it->second_.typeId & asTYPEID_MASK_OBJECT )
            Set(it->first_, (void*)it->second_.valueObj, it->second_.typeId);
        else
            Set(it->first_, (void*)&it->second_.valueInt, it->second_.typeId);
    }

    return *this;
}

void CScriptDictionary::Set(const String &key, void *value, int typeId)
{
    valueStruct valStruct = {{0},0};
    valStruct.typeId = typeId;
    if( typeId & asTYPEID_OBJHANDLE )
    {
        // We're receiving a reference to the handle, so we need to dereference it
        valStruct.valueObj = *(void**)value;
        engine->AddRefScriptObject(valStruct.valueObj, engine->GetObjectTypeById(typeId));
    }
    else if( typeId & asTYPEID_MASK_OBJECT )
    {
        // Create a copy of the object
        valStruct.valueObj = engine->CreateScriptObjectCopy(value, engine->GetObjectTypeById(typeId));
    }
    else
    {
        // Copy the primitive value
        // We receive a pointer to the value.
        int size = engine->GetSizeOfPrimitiveType(typeId);
        memcpy(&valStruct.valueInt, value, size);
    }

    HashMap<String, valueStruct>::Iterator it;
    it = dict.Find(key);
    if( it != dict.End() )
    {
        FreeValue(it->second_);

        // Insert the new value
        it->second_ = valStruct;
    }
    else
    {
        dict.Insert(MakePair(key, valStruct));
    }
}

// This overloaded method is implemented so that all integer and
// unsigned integers types will be stored in the dictionary as int64
// through implicit conversions. This simplifies the management of the
// numeric types when the script retrieves the stored value using a 
// different type.
void CScriptDictionary::Set(const String &key, asINT64 &value)
{
    Set(key, &value, asTYPEID_INT64);
}

// This overloaded method is implemented so that all floating point types 
// will be stored in the dictionary as double through implicit conversions. 
// This simplifies the management of the numeric types when the script 
// retrieves the stored value using a different type.
void CScriptDictionary::Set(const String &key, double &value)
{
    Set(key, &value, asTYPEID_DOUBLE);
}

// Returns true if the value was successfully retrieved
bool CScriptDictionary::Get(const String &key, void *value, int typeId) const
{
    HashMap<String, valueStruct>::ConstIterator it;
    it = dict.Find(key);
    if( it != dict.End() )
    {
        // Return the value
        if( typeId & asTYPEID_OBJHANDLE )
        {
            // A handle can be retrieved if the stored type is a handle of same or compatible type
            // or if the stored type is an object that implements the interface that the handle refer to.
            if( (it->second_.typeId & asTYPEID_MASK_OBJECT) && 
                engine->IsHandleCompatibleWithObject(it->second_.valueObj, it->second_.typeId, typeId) )
            {
                engine->AddRefScriptObject(it->second_.valueObj, engine->GetObjectTypeById(it->second_.typeId));
                *(void**)value = it->second_.valueObj;

                return true;
            }
        }
        else if( typeId & asTYPEID_MASK_OBJECT )
        {
            // Verify that the copy can be made
            bool isCompatible = false;
            if( it->second_.typeId == typeId )
                isCompatible = true;

            // Copy the object into the given reference
            if( isCompatible )
            {
                engine->AssignScriptObject(value, it->second_.valueObj, engine->GetObjectTypeById(typeId));

                return true;
            }
        }
        else
        {
            if( it->second_.typeId == typeId )
            {
                int size = engine->GetSizeOfPrimitiveType(typeId);
                memcpy(value, &it->second_.valueInt, size);
                return true;
            }

            // We know all numbers are stored as either int64 or double, since we register overloaded functions for those
            if( it->second_.typeId == asTYPEID_INT64 && typeId == asTYPEID_DOUBLE )
            {
                *(double*)value = double(it->second_.valueInt);
                return true;
            }
            else if( it->second_.typeId == asTYPEID_DOUBLE && typeId == asTYPEID_INT64 )
            {
                *(asINT64*)value = asINT64(it->second_.valueFlt);
                return true;
            }
        }
    }

    // AngelScript has already initialized the value with a default value,
    // so we don't have to do anything if we don't find the element, or if 
    // the element is incompatible with the requested type.

    return false;
}

bool CScriptDictionary::Get(const String &key, asINT64 &value) const
{
    return Get(key, &value, asTYPEID_INT64);
}

bool CScriptDictionary::Get(const String &key, double &value) const
{
    return Get(key, &value, asTYPEID_DOUBLE);
}

bool CScriptDictionary::Exists(const String &key) const
{
    HashMap<String, valueStruct>::ConstIterator it;
    it = dict.Find(key);
    if( it != dict.End() )
        return true;

    return false;
}

bool CScriptDictionary::IsEmpty() const
{
    if( dict.Size() == 0 )
        return true;

    return false;
}

asUINT CScriptDictionary::GetSize() const
{
    return asUINT(dict.Size());
}

void CScriptDictionary::Delete(const String &key)
{
    HashMap<String, valueStruct>::Iterator it;
    it = dict.Find(key);
    if( it != dict.End() )
    {
        FreeValue(it->second_);
        dict.Erase(it);
    }
}

void CScriptDictionary::DeleteAll()
{
    HashMap<String, valueStruct>::Iterator it;
    for( it = dict.Begin(); it != dict.End(); it++ )
        FreeValue(it->second_);

    dict.Clear();
}

void CScriptDictionary::FreeValue(valueStruct &value)
{
    // If it is a handle or a ref counted object, call release
    if( value.typeId & asTYPEID_MASK_OBJECT )
    {
        // Let the engine release the object
        engine->ReleaseScriptObject(value.valueObj, engine->GetObjectTypeById(value.typeId));
        value.valueObj = 0;
        value.typeId = 0;
    }

    // For primitives, there's nothing to do
}

CScriptArray* CScriptDictionary::GetKeys() const
{
    // TODO: optimize: The String array type should only be determined once. 
    //                 It should be recomputed when registering the dictionary class.
    //                 Only problem is if multiple engines are used, as they may not
    //                 share the same type id. Alternatively it can be stored in the 
    //                 user data for the dictionary type.
    int StringArrayType = engine->GetTypeIdByDecl("Array<String>");
    asIObjectType *ot = engine->GetObjectTypeById(StringArrayType);

    // Create the array object
    CScriptArray *arr = new CScriptArray(asUINT(dict.Size()), ot);
    long current = -1;
    HashMap<String, valueStruct>::ConstIterator it;
    for( it = dict.Begin(); it != dict.End(); it++ )
    {
        current++;
        *(String*)arr->At(current) = it->first_;
    }

    return arr;
}

void ScriptDictionaryFactory_Generic(asIScriptGeneric *gen)
{
    *(CScriptDictionary**)gen->GetAddressOfReturnLocation() = new CScriptDictionary(gen->GetEngine());
}

void ScriptDictionaryListFactory_Generic(asIScriptGeneric *gen)
{
    asBYTE *buffer = (asBYTE*)gen->GetArgAddress(0);
    *(CScriptDictionary**)gen->GetAddressOfReturnLocation() = new CScriptDictionary(buffer);
}

void RegisterDictionary(asIScriptEngine *engine)
{
    engine->RegisterObjectType("Dictionary", sizeof(CScriptDictionary), asOBJ_REF);
    // Use the generic interface to construct the object since we need the engine pointer, we could also have retrieved the engine pointer from the active context
    engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_FACTORY, "Dictionary@ f()", asFUNCTION(ScriptDictionaryFactory_Generic), asCALL_GENERIC);
    engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_LIST_FACTORY, "Dictionary @f(int &in) {repeat {String, ?}}", asFUNCTION(ScriptDictionaryListFactory_Generic), asCALL_GENERIC);
    engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_ADDREF, "void f()", asMETHOD(CScriptDictionary,AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Dictionary", asBEHAVE_RELEASE, "void f()", asMETHOD(CScriptDictionary,Release), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "Dictionary &opAssign(const Dictionary &in)", asMETHODPR(CScriptDictionary, operator=, (const CScriptDictionary &), CScriptDictionary&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "void Set(const String &in, ?&in)", asMETHODPR(CScriptDictionary,Set,(const String&,void*,int),void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "bool Get(const String &in, ?&out) const", asMETHODPR(CScriptDictionary,Get,(const String&,void*,int) const,bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "void Set(const String &in, int64&in)", asMETHODPR(CScriptDictionary,Set,(const String&,asINT64&),void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "bool Get(const String &in, int64&out) const", asMETHODPR(CScriptDictionary,Get,(const String&,asINT64&) const,bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "void Set(const String &in, double&in)", asMETHODPR(CScriptDictionary,Set,(const String&,double&),void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "bool Get(const String &in, double&out) const", asMETHODPR(CScriptDictionary,Get,(const String&,double&) const,bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "bool Exists(const String &in) const", asMETHOD(CScriptDictionary,Exists), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "bool get_empty() const", asMETHOD(CScriptDictionary, IsEmpty), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "uint get_length() const", asMETHOD(CScriptDictionary, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "void Erase(const String &in)", asMETHOD(CScriptDictionary,Delete), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "void Clear()", asMETHOD(CScriptDictionary,DeleteAll), asCALL_THISCALL);
    engine->RegisterObjectMethod("Dictionary", "Array<String> @get_keys() const", asMETHOD(CScriptDictionary,GetKeys), asCALL_THISCALL);
}


static String StringFactory(asUINT length, const char* s)
{
    return String(s, length);
}

static void ConstructString(String* ptr)
{
    new(ptr) String();
}

static void ConstructStringCopy(const String& str, String* ptr)
{
    new(ptr) String(str);
}

static void DestructString(String* ptr)
{
    ptr->~String();
}

static char* StringCharAt(unsigned int i, String& str)
{
    if (i >= str.Length())
    {
        asIScriptContext* context = asGetActiveContext();
        if (context)
            context->SetException("Index out of bounds");
        return 0;
    }
    return &str[i];
}

static int StringCmp(const String& lhs, const String& rhs)
{
    int cmp = 0;
    if (lhs < rhs)
        cmp = -1;
    else if (lhs > rhs)
        cmp = 1;
    return cmp;
}

void StringResize(unsigned newSize, String& str)
{
    unsigned oldSize = str.Length();
    str.Resize(newSize);
    for (unsigned i = oldSize; i < newSize; ++i)
        str[i] = ' ';
}

static void ConstructStringInt(int value, String* ptr)
{
    new(ptr) String(value);
}

static void ConstructStringUInt(unsigned value, String* ptr)
{
    new(ptr) String(value);
}

static void ConstructStringFloat(float value, String* ptr)
{
    new(ptr) String(value);
}

static void ConstructStringBool(bool value, String* ptr)
{
    new(ptr) String(value);
}

static String& StringAssignInt(int value, String& str)
{
    str = String(value);
    return str;
}

static String& StringAddAssignInt(int value, String& str)
{
    str += String(value);
    return str;
}

static String StringAddInt(int value, const String& str)
{
    return str + String(value);
}

static String StringAddIntReverse(int value, const String& str)
{
    return String(value) + str;
}

static String& StringAssignUInt(unsigned value, String& str)
{
    str = String(value);
    return str;
}

static String& StringAddAssignUInt(unsigned value, String& str)
{
    str += String(value);
    return str;
}

static String StringAddUInt(unsigned value, const String& str)
{
    return str + String(value);
}

static String StringAddUIntReverse(unsigned value, const String& str)
{
    return String(value) + str;
}

static String& StringAssignFloat(float value, String& str)
{
    str = String(value);
    return str;
}

static String& StringAddAssignFloat(float value, String& str)
{
    str += String(value);
    return str;
}

static String StringAddFloat(float value, const String& str)
{
    return str + String(value);
}

static String StringAddFloatReverse(float value, const String& str)
{
    return String(value) + str;
}

static String& StringAssignBool(bool value, String& str)
{
    str = String(value);
    return str;
}

static String& StringAddAssignBool(bool value, String& str)
{
    str += String(value);
    return str;
}

static String StringAddBool(bool value, const String& str)
{
    return str + String(value);
}

static String StringAddBoolReverse(bool value, const String& str)
{
    return String(value) + str;
}

static void StringSetUTF8FromLatin1(const String& src, String& str)
{
    str.SetUTF8FromLatin1(src.CString());
}

void RegisterString(asIScriptEngine *engine)
{
    engine->RegisterObjectType("String", sizeof(String), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
    engine->RegisterStringFactory("String", asFUNCTION(StringFactory), asCALL_CDECL);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(const String&in)", asFUNCTION(ConstructStringCopy), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructString), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(const String&in)", asMETHODPR(String, operator =, (const String&), String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String& opAddAssign(const String&in)", asMETHODPR(String, operator +=, (const String&), String&), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool opEquals(const String&in) const", asMETHODPR(String, operator ==, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "int opCmp(const String&in) const", asFUNCTION(StringCmp), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String opAdd(const String&in) const", asMETHODPR(String, operator +, (const String&) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint8 &opIndex(uint)", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "const uint8 &opIndex(uint) const", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "void Replace(uint8, uint8, bool caseSensitive = true)", asMETHODPR(String, Replace, (char, char, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void Replace(const String&in, const String&in, bool caseSensitive = true)", asMETHODPR(String, Replace, (const String&, const String&, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String Replaced(uint8, uint8, bool caseSensitive = true) const", asMETHODPR(String, Replaced, (char, char, bool) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String Replaced(const String&in, const String&in, bool caseSensitive = true) const", asMETHODPR(String, Replaced, (const String&, const String&, bool) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void Resize(uint)", asFUNCTION(StringResize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "uint Find(const String&in, uint start = 0, bool caseSensitive = true) const", asMETHODPR(String, Find, (const String&, unsigned, bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint Find(uint8, uint start = 0, bool caseSensitive = true) const", asMETHODPR(String, Find, (char, unsigned, bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint FindLast(const String&in, uint start = 0xffffffff, bool caseSensitive = true) const", asMETHODPR(String, FindLast, (const String&, unsigned, bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint FindLast(uint8, uint start = 0xffffffff, bool caseSensitive = true) const", asMETHODPR(String, FindLast, (char, unsigned, bool) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool StartsWith(const String&in, bool caseSensitive = true) const", asMETHOD(String, StartsWith), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool EndsWith(const String&in, bool caseSensitive = true) const", asMETHOD(String, EndsWith), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String Substring(uint) const", asMETHODPR(String, Substring, (unsigned) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String Substring(uint, uint) const", asMETHODPR(String, Substring, (unsigned, unsigned) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String ToUpper() const", asMETHOD(String, ToUpper), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String ToLower() const", asMETHOD(String, ToLower), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String Trimmed() const", asMETHOD(String, Trimmed), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void SetUTF8FromLatin1(const String& in)", asFUNCTION(StringSetUTF8FromLatin1), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "uint get_utf8Length() const", asMETHOD(String, LengthUTF8), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint ByteOffsetUTF8(uint) const", asMETHOD(String, ByteOffsetUTF8), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint NextUTF8Char(uint&) const", asMETHOD(String, NextUTF8Char), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint AtUTF8(uint) const", asMETHOD(String, AtUTF8), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void ReplaceUTF8(uint, uint)", asMETHOD(String, ReplaceUTF8), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void AppendUTF8(uint)", asMETHOD(String, AppendUTF8), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String SubstringUTF8(uint) const", asMETHODPR(String, SubstringUTF8, (unsigned) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String SubstringUTF8(uint, uint) const", asMETHODPR(String, SubstringUTF8, (unsigned, unsigned) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "uint get_length() const", asMETHOD(String, Length), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool get_empty() const", asMETHOD(String, Empty), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "int Compare(const String&in, bool caseSensitive = true) const", asMETHODPR(String, Compare, (const String&, bool) const, int), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool Contains(const String&in) const", asMETHODPR(String, Contains, (const String&) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool Contains(uint8) const", asMETHODPR(String, Contains, (char) const, bool), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void Clear()", asMETHOD(String, Clear), asCALL_THISCALL);
    
    // Register automatic conversion functions for convenience
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(ConstructStringInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructStringUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructStringFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(ConstructStringBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(int)", asFUNCTION(StringAssignInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(int)", asFUNCTION(StringAddAssignInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(int) const", asFUNCTION(StringAddInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(int) const", asFUNCTION(StringAddIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(uint)", asFUNCTION(StringAssignUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint)", asFUNCTION(StringAddAssignUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(uint) const", asFUNCTION(StringAddUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(uint) const", asFUNCTION(StringAddUIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(float)", asFUNCTION(StringAssignFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(float)", asFUNCTION(StringAddAssignFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(float) const", asFUNCTION(StringAddFloat), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(float) const", asFUNCTION(StringAddFloatReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(bool)", asFUNCTION(StringAssignBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(bool)", asFUNCTION(StringAddAssignBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(bool) const", asFUNCTION(StringAddBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(bool) const", asFUNCTION(StringAddBoolReverse), asCALL_CDECL_OBJLAST);
}

}
