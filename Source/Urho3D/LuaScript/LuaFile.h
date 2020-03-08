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

#include "../Container/ArrayPtr.h"
#include "../Resource/Resource.h"

struct lua_State;

namespace Urho3D
{

/// Lua file.
class URHO3D_API LuaFile : public Resource
{
    URHO3D_OBJECT(LuaFile, Resource);

public:
    /// Construct.
    explicit LuaFile(Context* context);
    /// Destruct.
    ~LuaFile() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    bool BeginLoad(Deserializer& source) override;
    /// Save resource. Return true if successful.
    bool Save(Serializer& dest) const override;

    /// Load buffer as chunk. Return true if the resource is successfully loaded as a Lua function on top of the stack.
    bool LoadChunk(lua_State* luaState);
    /// Load buffer as chunk and execute. Return true if successful.
    bool LoadAndExecute(lua_State* luaState);

private:
    /// File size.
    unsigned size_;
    /// File data.
    SharedArrayPtr<char> data_;
    /// Has loaded.
    bool hasLoaded_;
    /// Has executed.
    bool hasExecuted_;
};

}
