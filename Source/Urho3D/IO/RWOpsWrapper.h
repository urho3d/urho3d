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

#include "../IO/File.h"

#include <SDL/SDL_rwops.h>

namespace Urho3D
{

/// Template wrapper class for using Serializer / Deserializer or their subclasses through SDL's RWOps structure.
template <class T> class RWOpsWrapper
{
public:
    /// Construct with object reference.
    RWOpsWrapper(T& object)
    {
        ops_.type = dynamic_cast<File*>(&object) ? SDL_RWOPS_STDFILE : SDL_RWOPS_MEMORY;
        ops_.hidden.unknown.data1 = &object;
        ops_.size = &Size;
        ops_.seek = &Seek;
        ops_.close = &Close;
        ops_.read = &Read;
        ops_.write = &Write;
    }

    /// Return the RWOps structure.
    SDL_RWops* GetRWOps() { return &ops_; }

private:
    /// Return data size of the object.
    static Sint64 Size(SDL_RWops* context)
    {
        T* object = reinterpret_cast<T*>(context->hidden.unknown.data1);
        Deserializer* des = dynamic_cast<Deserializer*>(object);
        return des ? (Sint64)des->GetSize() : 0;
    }

    /// Seek within the object's data.
    static Sint64 Seek(SDL_RWops* context, Sint64 offset, int whence)
    {
        T* object = reinterpret_cast<T*>(context->hidden.unknown.data1);
        Deserializer* des = dynamic_cast<Deserializer*>(object);
        if (!des)
            return 0;

        switch (whence)
        {
        case RW_SEEK_SET:
            des->Seek((unsigned)offset);
            break;

        case RW_SEEK_CUR:
            des->Seek((unsigned)(des->GetPosition() + offset));
            break;

        case RW_SEEK_END:
            des->Seek((unsigned)(des->GetSize() + offset));
            break;

        default:
            assert(false);  // Should never reach here
            break;
        }

        return (Sint64)des->GetPosition();
    }

    /// Close the object. Only meaningful for files, no-op otherwise.
    static int Close(SDL_RWops* context)
    {
        T* object = reinterpret_cast<T*>(context->hidden.unknown.data1);
        File* file = dynamic_cast<File*>(object);
        if (file)
            file->Close();
        return 0;
    }

    /// Read from the object. Return number of "packets" read.
    static size_t Read(SDL_RWops* context, void* ptr, size_t size, size_t maxNum)
    {
        T* object = reinterpret_cast<T*>(context->hidden.unknown.data1);
        Deserializer* des = dynamic_cast<Deserializer*>(object);
        return des ? (size_t)(des->Read(ptr, (unsigned)(size * maxNum)) / size) : 0;
    }

    /// Write to the object. Return number of "packets" written.
    static size_t Write(SDL_RWops* context, const void* ptr, size_t size, size_t maxNum)
    {
        T* object = reinterpret_cast<T*>(context->hidden.unknown.data1);
        Serializer* ser = dynamic_cast<Serializer*>(object);
        return ser ? (size_t)(ser->Write(ptr, (unsigned)(size * maxNum)) / size) : 0;
    }

    /// SDL RWOps structure associated with the object.
    SDL_RWops ops_;
};

}
