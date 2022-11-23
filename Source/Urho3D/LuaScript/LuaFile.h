// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
    /// @nobind
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
