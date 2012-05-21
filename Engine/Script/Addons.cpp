//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Öörni
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
#include "Str.h"

#include <cstring>
#include <stdio.h>

// Adapted from Angelscript's scriptarray & scriptstdstring add-ons, but with garbage collection disabled

/// %Script array buffer.
struct SArrayBuffer
{
    asDWORD numElements;
    asBYTE  data[1];
};

static CScriptArray* ScriptArrayFactory2(asIObjectType *ot, asUINT length)
{
    CScriptArray *a = new CScriptArray(length, ot);
    
    // It's possible the constructor raised a script exception, in which case we 
    // need to free the memory and return null instead, else we get a memory leak.
    asIScriptContext *ctx = asGetActiveContext();
    if( ctx && ctx->GetState() == asEXECUTION_EXCEPTION )
    {
        delete a;
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
        delete a;
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
// subtype at compile time, instead of at runtime.
static bool ScriptArrayTemplateCallback(asIObjectType *ot)
{
    // Make sure the subtype can be instanciated with a default factory/constructor, 
    // otherwise we won't be able to instanciate the elements. Script classes always
    // have default factories, so we don't have to worry about those.
    int typeId = ot->GetSubTypeId();
    if( typeId == asTYPEID_VOID )
        return false;
    if( (typeId & asTYPEID_MASK_OBJECT) && !(typeId & asTYPEID_OBJHANDLE) && !(typeId & asTYPEID_SCRIPTOBJECT) )
    {
        asIObjectType *subtype = ot->GetEngine()->GetObjectTypeById(typeId);
        asDWORD flags = subtype->GetFlags();
        if( (flags & asOBJ_VALUE) && !(flags & asOBJ_POD) )
        {
            // Verify that there is a default constructor
            for( asUINT n = 0; n < subtype->GetBehaviourCount(); n++ )
            {
                asEBehaviours beh;
                int funcId = subtype->GetBehaviourByIndex(n, &beh);
                if( beh != asBEHAVE_CONSTRUCT ) continue;
                
                asIScriptFunction *func = ot->GetEngine()->GetFunctionById(funcId);
                if( func->GetParamCount() == 0 )
                {
                    // Found the default constructor
                    return true;
                }
            }
            
            // There is no default constructor
            return false;
        }
        else if( (flags & asOBJ_REF) )
        {
            // Verify that there is a default factory
            for( asUINT n = 0; n < subtype->GetFactoryCount(); n++ )
            {
                int funcId = subtype->GetFactoryIdByIndex(n);
                asIScriptFunction *func = ot->GetEngine()->GetFunctionById(funcId);
                if( func->GetParamCount() == 0 )
                {
                    // Found the default factory
                    return true;
                }
            }
            
            // No default factory
            return false;
        }
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
        if( buffer )
        {
            DeleteBuffer(buffer);
            buffer = 0;
        }
        
        // Copy all elements from the other array
        CreateBuffer(&buffer, other.buffer->numElements);
        CopyBuffer(buffer, other.buffer);
    }
    
    return *this;
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
    {
        elementSize = sizeof(asPWORD);
    }
    else
    {
        elementSize = objType->GetEngine()->GetSizeOfPrimitiveType(subTypeId);
    }
    
    // Make sure the array size isn't too large for us to handle
    if( !CheckMaxSize(length) )
    {
        // Don't continue with the initialization
        return;
    }
    
    CreateBuffer(&buffer, length);
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
    {
        elementSize = sizeof(asPWORD);
    }
    else
    {
        elementSize = objType->GetEngine()->GetSizeOfPrimitiveType(subTypeId);
    }
    
    // Make sure the array size isn't too large for us to handle
    if( !CheckMaxSize(length) )
    {
        // Don't continue with the initialization
        return;
    }
    
    CreateBuffer(&buffer, length);
    
    // Initialize the elements with the default value
    for( asUINT n = 0; n < GetSize(); n++ )
        SetValue(n, defVal);
}

// Internal
void CScriptArray::SetValue(asUINT index, void *value)
{
    if( (subTypeId & ~0x03FFFFFF) && !(subTypeId & asTYPEID_OBJHANDLE) )
        objType->GetEngine()->CopyScriptObject(At(index), value, subTypeId);
    else if( subTypeId & asTYPEID_OBJHANDLE )
    {
        *(void**)At(index) = *(void**)value;
        objType->GetEngine()->AddRefScriptObject(*(void**)value, objType->GetSubType());
    }
    else if( subTypeId == asTYPEID_BOOL ||
             subTypeId == asTYPEID_INT8 ||
             subTypeId == asTYPEID_UINT8 )
        *(char*)At(index) = *(char*)value;
    else if( subTypeId == asTYPEID_INT16 ||
             subTypeId == asTYPEID_UINT16 )
        *(short*)At(index) = *(short*)value;
    else if( subTypeId == asTYPEID_INT32 ||
             subTypeId == asTYPEID_UINT32 ||
             subTypeId == asTYPEID_FLOAT )
        *(int*)At(index) = *(int*)value;
    else if( subTypeId == asTYPEID_INT64 ||
             subTypeId == asTYPEID_UINT64 ||
             subTypeId == asTYPEID_DOUBLE )
        *(double*)At(index) = *(double*)value;
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
    
    // Allocate memory for the buffer
    SArrayBuffer *newBuffer;
    newBuffer = (SArrayBuffer*)new asBYTE[sizeof(SArrayBuffer)-1 + elementSize*(buffer->numElements + delta)];
    newBuffer->numElements = buffer->numElements + delta;
    
    memcpy(newBuffer->data, buffer->data, at*elementSize);
    if( delta > 0 && at < buffer->numElements )
        memcpy(newBuffer->data + (at+delta)*elementSize, buffer->data + at*elementSize, (buffer->numElements-at)*elementSize);
    else if( delta < 0 && at < buffer->numElements )
        memcpy(newBuffer->data + at*elementSize, buffer->data + (at-delta)*elementSize, (buffer->numElements-at+delta)*elementSize);
    
    if( subTypeId & asTYPEID_MASK_OBJECT )
    {
        if( delta > 0 )
            Construct(newBuffer, at, at+delta);
        else if( delta < 0 )
            Destruct(buffer, at, at-delta);
    }
    
    // Release the old buffer
    delete[] (asBYTE*)buffer;
    
    buffer = newBuffer;
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
void *CScriptArray::At(asUINT index)
{
    if( index >= buffer->numElements )
    {
        // If this is called from a script we raise a script exception
        asIScriptContext *ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException("Index out of bounds");
        return 0;
    }
    else
    {
        if( (subTypeId & asTYPEID_MASK_OBJECT) && !(subTypeId & asTYPEID_OBJHANDLE) )
            return (void*)((size_t*)buffer->data)[index];
        else
            return buffer->data + elementSize*index;
    }
}

// internal
void CScriptArray::CreateBuffer(SArrayBuffer **buf, asUINT numElements)
{
    if( subTypeId & asTYPEID_MASK_OBJECT )
    {
        *buf = (SArrayBuffer*)new asBYTE[sizeof(SArrayBuffer)-1+sizeof(void*)*numElements];
        (*buf)->numElements = numElements;
    }
    else
    {
        *buf = (SArrayBuffer*)new asBYTE[sizeof(SArrayBuffer)-1+elementSize*numElements];
        (*buf)->numElements = numElements;
    }
    
    Construct(*buf, 0, numElements);
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
        
        for( ; d < max; d++ )
            *d = (void*)engine->CreateScriptObject(subTypeId);
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
bool CScriptArray::Less(const void *a, const void *b, bool asc, asIScriptContext *ctx)
{
    if( !asc )
    {
        // Swap items
        const void *TEMP = a;
        a = b;
        b = TEMP;
    }
    
    if( subTypeId <= asTYPEID_DOUBLE )
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
            #undef COMPARE
        }
    }
    else
    {
        int r = 0;
        
        // Execute object opCmp
        // TODO: Add proper error handling
        r = ctx->Prepare(cmpFuncId); assert(r >= 0);
        r = ctx->SetObject((void*)a); assert(r >= 0);
        r = ctx->SetArgAddress(0, (void*)b); assert(r >= 0);
        r = ctx->Execute();
        
        if( r == asEXECUTION_FINISHED )
        {
            return (int)ctx->GetReturnDWord() < 0;
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

// internal
bool CScriptArray::Equals(const void *a, const void *b, asIScriptContext *ctx)
{
    if( subTypeId <= asTYPEID_DOUBLE )
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
            #undef COMPARE
        }
    }
    else
    {
        int r = 0;
        
        // Execute object opEquals if available
        if( eqFuncId >= 0 )
        {
            // TODO: Add proper error handling
            r = ctx->Prepare(eqFuncId); assert(r >= 0);
            r = ctx->SetObject((void*)a); assert(r >= 0);
            r = ctx->SetArgAddress(0, (void*)b); assert(r >= 0);
            r = ctx->Execute();
            
            if( r == asEXECUTION_FINISHED )
            {
                return ctx->GetReturnByte() != 0;
            }
        }
        
        // Execute object opCmp if available
        if( cmpFuncId >= 0 )
        {
            // TODO: Add proper error handling
            r = ctx->Prepare(cmpFuncId); assert(r >= 0);
            r = ctx->SetObject((void*)a); assert(r >= 0);
            r = ctx->SetArgAddress(0, (void*)b); assert(r >= 0);
            r = ctx->Execute();
            
            if( r == asEXECUTION_FINISHED )
            {
                return (int)ctx->GetReturnDWord() == 0;
            }
        }
    }
    
    return false;
}

int CScriptArray::Find(void *value)
{
    return Find(0, value);
}

int CScriptArray::Find(asUINT index, void *value)
{
    // Subtype isn't primitive and doesn't have opEquals / opCmp
    if( subTypeId > asTYPEID_DOUBLE && (cmpFuncId <= 0 && eqFuncId <= 0) )
    {
        asIScriptContext *ctx = asGetActiveContext();
        asIObjectType* subType = objType->GetEngine()->GetObjectTypeById(subTypeId);
        
        // Throw an exception
        if( ctx )
        {
            char tmp[512];
#if defined(_MSC_VER) && _MSC_VER >= 1500
            sprintf_s(tmp, 512, "Type '%s' does not have opEquals / opCmp", subType->GetName());
#else
            sprintf(tmp, "Type '%s' does not have opEquals / opCmp", subType->GetName());
#endif
            ctx->SetException(tmp);
        }
        
        return -1;
    }
    
    asIScriptContext *cmpContext = 0;
    
    if( subTypeId > asTYPEID_DOUBLE )
    {
        // TODO: Ideally this context would be retrieved from a pool, so we don't have to 
        //       create a new one everytime. We could keep a context with the array object 
        //       but that would consume a lot of resources as each context is quite heavy.
        cmpContext = objType->GetEngine()->CreateContext();
    }
    
    int ret = -1;
    asUINT size = GetSize();
    
    if( index < size )
    {
        for( asUINT i = index; i < size; i++ )
        {
            // value passed by reference
            if( Equals(At(i), (value), cmpContext) )
            {
                ret = (int)i;
                break;
            }
        }
    }
    
    if( cmpContext )
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
    if( subTypeId > asTYPEID_DOUBLE && cmpFuncId <= 0 )
    {
        asIScriptContext *ctx = asGetActiveContext();
        asIObjectType* subType = objType->GetEngine()->GetObjectTypeById(subTypeId);
        
        // Throw an exception
        if( ctx )
        {
            char tmp[512];
#if defined(_MSC_VER) && _MSC_VER >= 1500
            sprintf_s(tmp, 512, "Type '%s' does not have opCmp", subType->GetName());
#else
            sprintf(tmp, "Type '%s' does not have opCmp", subType->GetName());
#endif
            ctx->SetException(tmp);
        }
        
        return;
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
    
    if( subTypeId > asTYPEID_DOUBLE )
    {
        // TODO: Ideally this context would be retrieved from a pool, so we don't have to 
        //       create a new one everytime. We could keep a context with the array object 
        //       but that would consume a lot of resources as each context is quite heavy.
        cmpContext = objType->GetEngine()->CreateContext();
    }
    
    // Insertion sort
    for( int i = start + 1; i < end; i++ )
    {
        Copy(tmp, GetArrayItemPointer(i));
        
        int j = i - 1;
        
        while( j >= start && Less(GetDataPointer(tmp), At(j), asc, cmpContext) )
        {
            Copy(GetArrayItemPointer(j + 1), GetArrayItemPointer(j));
            j--;
        }
        
        Copy(GetArrayItemPointer(j + 1), tmp);
    }
    
    if( cmpContext )
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
                *d = *s;
                if( *d )
                    engine->AddRefScriptObject(*d, objType->GetSubType());
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
                
                for( ; d < max; d++, s++ )
                    engine->CopyScriptObject(*d, *s, subTypeId);
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
    // TODO: optimize: This information could be stored in the object type as user data,
    //                 then it wouldn't be necessary to look for this for each array initialization
    
    subTypeId = objType->GetSubTypeId();
    
    cmpFuncId = -1;
    eqFuncId = -1;
    
    // Object - search for opCmp / opEquals
    if( subTypeId > asTYPEID_DOUBLE )
    {
        asIObjectType *subType = objType->GetEngine()->GetObjectTypeById(subTypeId);
        
        if( subType )
        {
            for( asUINT i = 0; i < subType->GetMethodCount(); i++ )
            {
                asIScriptFunction *func = subType->GetMethodByIndex(i);
                
                if( func->GetParamCount() == 1 /* && func->IsReadOnly() */ )
                {
                    asDWORD flags = 0;
                    int returnTypeId = func->GetReturnTypeId();
                    int paramTypeId = func->GetParamTypeId(0, &flags);
                    
                    if( flags == asTM_INREF && paramTypeId == subTypeId )
                    {
                        if( returnTypeId == asTYPEID_INT32 && strcmp(func->GetName(), "opCmp") == 0 )
                        {
                            cmpFuncId = subType->GetMethodIdByIndex(i);
                        }
                        
                        if( returnTypeId == asTYPEID_BOOL && strcmp(func->GetName(), "opEquals") == 0 )
                        {
                            eqFuncId = subType->GetMethodIdByIndex(i);
                        }
                        
                        if( cmpFuncId >= 0 && eqFuncId >= 0 )
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void CScriptArray::AddRef() const
{
    // Clear the GC flag then increase the counter
    gcFlag = false;
    refCount++;
}

void CScriptArray::Release() const
{
    // Now do the actual releasing (clearing the flag set by GC)
    gcFlag = false;
    if( --refCount == 0 )
    {
        delete this;
    }
}

static void ScriptArrayClear(CScriptArray* ptr)
{
    ptr->Resize(0);
}

static bool ScriptArrayIsEmpty(CScriptArray* ptr)
{
    return ptr->GetSize() == 0;
}

void RegisterArray(asIScriptEngine* engine)
{
    engine->RegisterObjectType("Array<class T>", 0, asOBJ_REF | asOBJ_TEMPLATE);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_TEMPLATE_CALLBACK, "bool f(int&in)", asFUNCTION(ScriptArrayTemplateCallback), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in)", asFUNCTIONPR(ScriptArrayFactory, (asIObjectType*), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in, uint)", asFUNCTIONPR(ScriptArrayFactory2, (asIObjectType*, asUINT), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_FACTORY, "Array<T>@ f(int& in, uint, const T& in)", asFUNCTIONPR(ScriptArrayFactoryDefVal, (asIObjectType*, asUINT, void *), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_LIST_FACTORY, "Array<T>@ f(int& in, uint)", asFUNCTIONPR(ScriptArrayFactory2, (asIObjectType*, asUINT), CScriptArray*), asCALL_CDECL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_ADDREF, "void f()", asMETHOD(CScriptArray,AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Array<T>", asBEHAVE_RELEASE, "void f()", asMETHOD(CScriptArray,Release), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "T& opIndex(uint)", asMETHOD(CScriptArray, At), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "const T& opIndex(uint) const", asMETHOD(CScriptArray, At), asCALL_THISCALL);
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
    engine->RegisterObjectMethod("Array<T>", "int Find(const T&in) const", asMETHODPR(CScriptArray, Find, (void*), int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "int Find(uint, const T&in) const", asMETHODPR(CScriptArray, Find, (asUINT, void*), int), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "uint get_length() const", asMETHOD(CScriptArray, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "void set_length(uint)", asMETHODPR(CScriptArray, Resize, (asUINT), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Array<T>", "bool get_empty() const", asFUNCTION(ScriptArrayIsEmpty), asCALL_CDECL_OBJLAST);
    engine->RegisterDefaultArrayType("Array<T>");
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

// Workaround for asCALL_CDECL_OBJLAST trashing the first float parameter on Android
static void ConstructStringFloat(String* ptr, float value)
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

// Workaround for asCALL_CDECL_OBJLAST trashing the first float parameter on Android
static String& StringAssignFloat(String& str, float value)
{
    str = String(value);
    return str;
}

// Workaround for asCALL_CDECL_OBJLAST trashing the first float parameter on Android
static String& StringAddAssignFloat(String& str, float value)
{
    str += String(value);
    return str;
}

// Workaround for asCALL_CDECL_OBJLAST trashing the first float parameter on Android
static String StringAddFloat(const String& str, float value)
{
    return str + String(value);
}

// Workaround for asCALL_CDECL_OBJLAST trashing the first float parameter on Android
static String StringAddFloatReverse(const String& str, float value)
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
    engine->RegisterObjectMethod("String", "void Replace(uint8, uint8)", asMETHODPR(String, Replace, (char, char), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void Replace(const String&in, const String&in)", asMETHODPR(String, Replace, (const String&, const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String Replaced(uint8, uint8) const", asMETHODPR(String, Replaced, (char, char) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "String Replaced(const String&in, const String&in) const", asMETHODPR(String, Replaced, (const String&, const String&) const, String), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "void Resize(uint)", asFUNCTION(StringResize), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "int Find(const String&in, uint start = 0) const", asMETHODPR(String, Find, (const String&, unsigned) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "int Find(uint8, uint start = 0) const", asMETHODPR(String, Find, (char, unsigned) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "int FindLast(const String&in, uint start = 0xffffffff) const", asMETHODPR(String, FindLast, (const String&, unsigned) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "int FindLast(uint8, uint start = 0xffffffff) const", asMETHODPR(String, FindLast, (char, unsigned) const, unsigned), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool StartsWith(const String&in) const", asMETHOD(String, StartsWith), asCALL_THISCALL);
    engine->RegisterObjectMethod("String", "bool EndsWith(const String&in) const", asMETHOD(String, EndsWith), asCALL_THISCALL);
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
    
    // Register automatic conversion functions for convenience
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(ConstructStringInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructStringUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(float)", asFUNCTION(ConstructStringFloat), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectBehaviour("String", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(ConstructStringBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(int)", asFUNCTION(StringAssignInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(int)", asFUNCTION(StringAddAssignInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(int) const", asFUNCTION(StringAddInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(int) const", asFUNCTION(StringAddIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(uint)", asFUNCTION(StringAssignUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(uint)", asFUNCTION(StringAddAssignUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(uint) const", asFUNCTION(StringAddUInt), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(uint) const", asFUNCTION(StringAddUIntReverse), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAssign(float)", asFUNCTION(StringAssignFloat), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(float)", asFUNCTION(StringAddAssignFloat), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String opAdd(float) const", asFUNCTION(StringAddFloat), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String opAdd_r(float) const", asFUNCTION(StringAddFloatReverse), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectMethod("String", "String& opAssign(bool)", asFUNCTION(StringAssignBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String& opAddAssign(bool)", asFUNCTION(StringAddAssignBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd(bool) const", asFUNCTION(StringAddBool), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("String", "String opAdd_r(bool) const", asFUNCTION(StringAddBoolReverse), asCALL_CDECL_OBJLAST);
}
