//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include <angelscript.h>

// Adapted from Angelscript's scriptarray & scriptstdstring add-ons, but with garbage collection disabled

struct SArrayBuffer;

/// %Script array type.
class CScriptArray
{
public:
    CScriptArray(asUINT length, asIObjectType *ot);
    CScriptArray(asUINT length, void *defVal, asIObjectType *ot);
    virtual ~CScriptArray();
    
    void AddRef() const;
    void Release() const;
    
    // Type information
    asIObjectType *GetArrayObjectType() const;
    int GetArrayTypeId() const;
    int GetElementTypeId() const;
    
    void Resize(asUINT numElements);
    asUINT GetSize() const;
    
    // Get a pointer to an element. Returns 0 if out of bounds
    void  *At(asUINT index);
    
    CScriptArray &operator=(const CScriptArray&);
    
    void InsertAt(asUINT index, void *value);
    void RemoveAt(asUINT index);
    void InsertLast(void *value);
    void RemoveLast();
    void SortAsc();
    void SortDesc();
    void SortAsc(asUINT index, asUINT count);
    void SortDesc(asUINT index, asUINT count);
    void Sort(asUINT index, asUINT count, bool asc);
    void Reverse();
    int Find(void *value);
    int Find(asUINT index, void *value);
    
protected:
    mutable int refCount;
    mutable bool gcFlag;
    asIObjectType *objType;
    SArrayBuffer *buffer;
    int elementSize;
    int cmpFuncId;
    int eqFuncId;
    int subTypeId;
    
    bool Less(const void *a, const void *b, bool asc, asIScriptContext *ctx);
    void *GetArrayItemPointer(int index);
    void *GetDataPointer(void *buffer);
    void Copy(void *dst, void *src);
    void Precache();
    bool CheckMaxSize(asUINT numElements);
    void Resize(int delta, asUINT at);
    void SetValue(asUINT index, void *value);
    void CreateBuffer(SArrayBuffer **buf, asUINT numElements);
    void DeleteBuffer(SArrayBuffer *buf);
    void CopyBuffer(SArrayBuffer *dst, SArrayBuffer *src);
    void Construct(SArrayBuffer *buf, asUINT start, asUINT end);
    void Destruct(SArrayBuffer *buf, asUINT start, asUINT end);
    bool Equals(const void *a, const void *b, asIScriptContext *ctx);
};

/// Register the array type to script.
void RegisterArray(asIScriptEngine* engine);
/// Register String to script.
void RegisterString(asIScriptEngine* engine);
