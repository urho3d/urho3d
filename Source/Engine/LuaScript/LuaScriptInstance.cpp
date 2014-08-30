//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "CoreEvents.h"
#include "Context.h"
#include "Log.h"
#include "LuaFile.h"
#include "LuaFunction.h"
#include "LuaScript.h"
#include "LuaScriptInstance.h"
#include "MemoryBuffer.h"
#ifdef URHO3D_PHYSICS
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#endif
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "ProcessUtils.h"
#include "VectorBuffer.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "tolua++.h"
#include "ToluaUtils.h"

#include "DebugNew.h"

namespace Urho3D
{

static const char* scriptObjectMethodNames[] = {
    "Start",
    "Stop",
    "Update",
    "PostUpdate",
    "FixedUpdate",
    "FixedPostUpdate",
    "Load",
    "Save",
    "ReadNetworkUpdate",
    "WriteNetworkUpdate",
    "ApplyAttributes",
    "TransformChanged"
};

LuaScriptInstance::LuaScriptInstance(Context* context) :
    Component(context),
    scriptObjectRef_(LUA_REFNIL)
{
    luaScript_ = GetSubsystem<LuaScript>();
    luaState_ = luaScript_->GetState();
    attributeInfos_ = *context_->GetAttributes(GetTypeStatic());
}

LuaScriptInstance::~LuaScriptInstance()
{
    ReleaseObject();
}

void LuaScriptInstance::RegisterObject(Context* context)
{
    context->RegisterFactory<LuaScriptInstance>(LOGIC_CATEGORY);

    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BOOL, "Is Enabled", IsEnabled, SetEnabled, bool, true, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_RESOURCEREF, "Script File", GetScriptFileAttr, SetScriptFileAttr, ResourceRef, ResourceRef(LuaFile::GetTypeStatic()), AM_DEFAULT);
    REF_ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_STRING, "Script Object Type", GetScriptObjectType, SetScriptObjectType, String, String::EMPTY, AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BUFFER, "Script Data", GetScriptDataAttr, SetScriptDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_FILE | AM_NOEDIT);
    ACCESSOR_ATTRIBUTE(LuaScriptInstance, VAR_BUFFER, "Script Network Data", GetScriptNetworkDataAttr, SetScriptNetworkDataAttr, PODVector<unsigned char>, Variant::emptyBuffer, AM_NET | AM_NOEDIT);
}

void LuaScriptInstance::OnSetAttribute(const AttributeInfo& attr, const Variant& src)
{
    if (attr.ptr_ != (void*)0xffffffff)
    {
        Serializable::OnSetAttribute(attr, src);
        return;
    }

    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    String name = attr.name_;
    unsigned length = name.Length();
    if (name.Back() == '_')
        length -= 1;

    int top = lua_gettop(luaState_);

    String functionName = String("Set") + name.Substring(0, 1).ToUpper() + name.Substring(1, length - 1);
    WeakPtr<LuaFunction> function = GetScriptObjectFunction(functionName);
    // If set function exist
    if (function)
    {
        if (function->BeginCall(this))
        {
            function->PushVariant(src);
            function->EndCall();
        }
    }
    else
    {
        lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);
        lua_pushstring(luaState_, name.CString());

        switch (attr.type_)
        {
        case VAR_BOOL:
            lua_pushboolean(luaState_, src.GetBool());
            break;
        case VAR_FLOAT:
            lua_pushnumber(luaState_, src.GetFloat());
            break;
        case VAR_STRING:
            tolua_pushurho3dstring(luaState_, src.GetString());
            break;
        case VAR_VECTOR2:
            {
                Vector2* value = new Vector2(src.GetVector2());
                tolua_pushusertype(luaState_, value, "Vector2");
                tolua_register_gc(luaState_, lua_gettop(luaState_));
            }
            break;
        case VAR_VECTOR3:
            {
                Vector3* value = new Vector3(src.GetVector3());
                tolua_pushusertype(luaState_, value, "Vector3");
                tolua_register_gc(luaState_, lua_gettop(luaState_));
            }
            break;
        case VAR_VECTOR4:
            {
                Vector4* value = new Vector4(src.GetVector4());
                tolua_pushusertype(luaState_, value, "Vector4");
                tolua_register_gc(luaState_, lua_gettop(luaState_));
            }            
            break;
        case VAR_QUATERNION:
            {
                Quaternion* value = new Quaternion(src.GetQuaternion());
                tolua_pushusertype(luaState_, value, "Quaternion");
                tolua_register_gc(luaState_, lua_gettop(luaState_));
            }
            
            break;
        case VAR_COLOR:
            {
                Color* value = new Color(src.GetColor());
                tolua_pushusertype(luaState_, value, "Color");
                tolua_register_gc(luaState_, lua_gettop(luaState_));
            }
            break;
        case VAR_INTRECT:
            {
                IntRect* value = new IntRect(src.GetIntRect());
                tolua_pushusertype(luaState_, value, "IntRect");
                tolua_register_gc(luaState_, lua_gettop(luaState_));
            }
            break;
        case VAR_INTVECTOR2:
            {
                IntVector2* value = new IntVector2(src.GetIntVector2());
                tolua_pushusertype(luaState_, value, "IntVector2");
                tolua_register_gc(luaState_, lua_gettop(luaState_));
            }
            break;
        default:
            LOGERROR("Unsupported data type");
            lua_settop(luaState_, top);
            return;
        }

        lua_settable(luaState_, -3);
    }

    lua_settop(luaState_, top);
}

void LuaScriptInstance::OnGetAttribute(const AttributeInfo& attr, Variant& dest) const
{
    if (attr.ptr_ != (void*)0xffffffff)
    {
        Serializable::OnGetAttribute(attr, dest);
        return;
    }

    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    String name = attr.name_;
    unsigned length = name.Length();
    if (name.Back() == '_')
        length -= 1;

    int top = lua_gettop(luaState_);

    String functionName = String("Get") + name.Substring(0, 1).ToUpper() + name.Substring(1, length - 1);
    WeakPtr<LuaFunction> function = GetScriptObjectFunction(functionName);
    // If get function exist
    if (function)
    {
        if (function->BeginCall(this))
            function->EndCall(1);
    }
    else
    {
        lua_rawgeti(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);
        lua_pushstring(luaState_, name.CString());
        lua_gettable(luaState_, -2);
    }

    switch (attr.type_)
    {
    case VAR_BOOL:
        dest = lua_toboolean(luaState_, -1) != 0;
        break;
    case VAR_FLOAT:
        dest = (float)lua_tonumber(luaState_, -1);
        break;
    case VAR_STRING:
        dest = tolua_tourho3dstring(luaState_, -1, "");
        break;
    case VAR_VECTOR2:
        dest = *((Vector2*)tolua_tousertype(luaState_, -1, 0));
        break;
    case VAR_VECTOR3:
        dest = *((Vector3*)tolua_tousertype(luaState_, -1, 0));
        break;
    case VAR_VECTOR4:
        dest = *((Vector4*)tolua_tousertype(luaState_, -1, 0));
        break;
    case VAR_QUATERNION:
        dest = *((Quaternion*)tolua_tousertype(luaState_, -1, 0));
        break;
    case VAR_COLOR:
        dest = *((Color*)tolua_tousertype(luaState_, -1, 0));
        break;
    case VAR_INTRECT:
        dest = *((IntRect*)tolua_tousertype(luaState_, -1, 0));
        break;
    case VAR_INTVECTOR2:
        dest = *((IntVector2*)tolua_tousertype(luaState_, -1, 0));
        break;
    default:
        LOGERROR("Unsupported data type");
        return;
    }

    lua_settop(luaState_, top);
}

void LuaScriptInstance::ApplyAttributes()
{
    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_APPLYATTRIBUTES];
    if (function && function->BeginCall(this))
    {
        function->EndCall();
    }
}

void LuaScriptInstance::OnSetEnabled()
{
    if (IsEnabledEffective())
        SubscribeToScriptMethodEvents();
    else
        UnsubscribeFromScriptMethodEvents();
}

bool LuaScriptInstance::CreateObject(const String& scriptObjectType)
{
	SetScriptFile(0);
    SetScriptObjectType(scriptObjectType);
    return scriptObjectRef_ != LUA_REFNIL;
}

bool LuaScriptInstance::CreateObject(LuaFile* scriptFile, const String& scriptObjectType)
{
    SetScriptFile(scriptFile);
    SetScriptObjectType(scriptObjectType);
    return scriptObjectRef_ != LUA_REFNIL;
}

void LuaScriptInstance::SetScriptFile(LuaFile* scriptFile)
{
	if (scriptFile == scriptFile_)
		return;

	scriptFile_ = scriptFile;

	if (!scriptFile_)
		return;

    if (!scriptFile_->LoadAndExecute(luaState_))
        LOGERROR("Execute Lua file failed: " + scriptFile_->GetName());
}

void LuaScriptInstance::SetScriptObjectType(const String& scriptObjectType)
{
    if (scriptObjectType == scriptObjectType_)
        return;

    ReleaseObject();

    WeakPtr<LuaFunction> function = luaScript_->GetFunction("CreateScriptObjectInstance");
    if (!function || !function->BeginCall())
        return;

    function->PushLuaTable(scriptObjectType);
    function->PushUserType((void*)this, "LuaScriptInstance");

    // Return script object and attribute names
    if (!function->EndCall(2))
        return;

    GetScriptAttributes();
    scriptObjectType_ = scriptObjectType;
    scriptObjectRef_ = luaL_ref(luaState_, LUA_REGISTRYINDEX);

    // Find script object method refs
    FindScriptObjectMethodRefs();
}

void LuaScriptInstance::SetScriptDataAttr(PODVector<unsigned char> data)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_LOAD];
    if (function && function->BeginCall(this))
    {
        MemoryBuffer buf(data);
        function->PushUserType((Deserializer&)buf, "Deserializer");
        function->EndCall();
    }
}

void LuaScriptInstance::SetScriptNetworkDataAttr(PODVector<unsigned char> data)
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_READNETWORKUPDATE];
    if (function && function->BeginCall(this))
    {
        MemoryBuffer buf(data);
        function->PushUserType((Deserializer&)buf, "Deserializer");
        function->EndCall();
    }
}

void LuaScriptInstance::ScriptSubscribeToEvent(const String& eventName, const String& functionName)
{
    String realFunctionName = functionName.Replaced(":", ".");

    WeakPtr<LuaFunction> function = luaScript_->GetFunction(realFunctionName);
    if (function)
    {
        StringHash eventType(eventName);
        SubscribeToEvent(eventType, HANDLER(LuaScriptInstance, HandleEvent));
        eventTypeToFunctionMap_[eventType] = function;
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvent(const String& eventName)
{
    StringHash eventType(eventName);

    HashMap<StringHash, WeakPtr<LuaFunction> >::Iterator i = eventTypeToFunctionMap_.Find(eventType);
    if (i != eventTypeToFunctionMap_.End())
    {
        UnsubscribeFromEvent(eventType);
        eventTypeToFunctionMap_.Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromAllEvents()
{
    if (eventTypeToFunctionMap_.Empty())
        return;

    UnsubscribeFromAllEvents();
    eventTypeToFunctionMap_.Clear();
}

void LuaScriptInstance::ScriptSubscribeToEvent(void* sender, const String& eventName, const String& functionName)
{
    String realFunctionName = functionName.Replaced(":", ".");

    WeakPtr<LuaFunction> function = luaScript_->GetFunction(realFunctionName);
    if (function)
    {
        Object* object = (Object*)sender;
        StringHash eventType(eventName);
        SubscribeToEvent(object, eventType, HANDLER(LuaScriptInstance, HandleObjectEvent));
        objectToEventTypeToFunctionMap_[object][eventType] = function;
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvent(void* sender, const String& eventName)
{
    StringHash eventType(eventName);
    Object* object = (Object*)sender ;

    HashMap<StringHash, WeakPtr<LuaFunction> >::Iterator i = objectToEventTypeToFunctionMap_[object].Find(eventType);
    if (i != objectToEventTypeToFunctionMap_[object].End())
    {
        UnsubscribeFromEvent(object, eventType);
        objectToEventTypeToFunctionMap_[object].Erase(i);
    }
}

void LuaScriptInstance::ScriptUnsubscribeFromEvents(void* sender)
{
    Object* object = (Object*)sender;

    HashMap<Object*, HashMap<StringHash, WeakPtr<LuaFunction> > >::Iterator it = objectToEventTypeToFunctionMap_.Find(object);
    if (it == objectToEventTypeToFunctionMap_.End())
        return;

    UnsubscribeFromEvents(object);
    objectToEventTypeToFunctionMap_.Erase(it);
}

LuaFile* LuaScriptInstance::GetScriptFile() const
{
	return scriptFile_;
}

PODVector<unsigned char> LuaScriptInstance::GetScriptDataAttr() const
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return PODVector<unsigned char>();

    VectorBuffer buf;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_SAVE];
    if (function && function->BeginCall(this))
    {
        function->PushUserType((Serializer&)buf, "Serializer");
        function->EndCall();
    }

    return buf.GetBuffer();
}

PODVector<unsigned char> LuaScriptInstance::GetScriptNetworkDataAttr() const
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return PODVector<unsigned char>();

    VectorBuffer buf;

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_WRITENETWORKUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushUserType((Serializer&)buf, "Serializer");
        function->EndCall();
    }

    return buf.GetBuffer();
}

void LuaScriptInstance::OnMarkedDirty(Node* node)
{
    // Script functions are not safe from worker threads
    Scene* scene = GetScene();
    if (scene && scene->IsThreadedUpdate())
    {
        scene->DelayedMarkedDirty(this);
        return;
    }

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_TRANSFORMCHANGED];
    if (function && function->BeginCall(this))
    {
        function->EndCall();
    }
}

void LuaScriptInstance::GetScriptAttributes()
{
    // Get all attribute names
    Vector<String> names;
    if (lua_istable(luaState_, -1))
    {
        int length = lua_objlen(luaState_, -1);
        for (int i = 1; i <= length; ++i)
        {
            lua_pushinteger(luaState_, i);
            lua_gettable(luaState_, -2);

            if (!lua_isstring(luaState_, -1))
            {
                lua_pop(luaState_, 1);
                continue;
            }

            String name = lua_tostring(luaState_, -1);
            names.Push(name);

            lua_pop(luaState_, 1);
        }
    }
    lua_pop(luaState_, 1);

    attributeInfos_ = *context_->GetAttributes(GetTypeStatic());

    for (unsigned i = 0; i < names.Size(); ++i)
    {
        lua_pushstring(luaState_, names[i].CString());
        lua_gettable(luaState_, -2);

        // Get attribute type
        int type = lua_type(luaState_, -1);

        AttributeInfo info;
        info.mode_ = AM_FILE;
        info.name_ = names[i];
        info.ptr_ = (void*)0xffffffff;

        switch (type)
        {
        case LUA_TBOOLEAN:
            info.type_ = VAR_BOOL;
            break;
        case LUA_TNUMBER:
            info.type_ = VAR_FLOAT;
            break;
        case LUA_TSTRING:
            info.type_ = VAR_STRING;
            break;
        case LUA_TUSERDATA:
            {
                String typeName = tolua_typename(luaState_, -1);
                lua_pop(luaState_, 1);

                if (typeName == "Vector2")
                    info.type_ = VAR_VECTOR2;
                else if (typeName == "Vector3")
                    info.type_ = VAR_VECTOR3;
                else if (typeName == "Vector4")
                    info.type_ = VAR_VECTOR4;
                else if (typeName == "Quaternion")
                    info.type_ = VAR_QUATERNION;
                else if (typeName == "Color")
                    info.type_ = VAR_COLOR;
                else if (typeName == "Intrect")
                    info.type_ = VAR_INTRECT;
                else if (typeName == "Intvector2")
                    info.type_ = VAR_INTVECTOR2;
            }
            break;
        default:
            break;
        }
        lua_pop(luaState_, 1);

        if (info.type_ != VAR_NONE)
            attributeInfos_.Push(info);
    }
}

void LuaScriptInstance::FindScriptObjectMethodRefs()
{
    for (unsigned i = 0; i < MAX_LUA_SCRIPT_OBJECT_METHODS; ++i)
        scriptObjectMethods_[i] = GetScriptObjectFunction(scriptObjectMethodNames[i]);

    if (IsEnabledEffective())
        SubscribeToScriptMethodEvents();
}

void LuaScriptInstance::SubscribeToScriptMethodEvents()
{
    Scene* scene = GetScene();

    if (scene && scriptObjectMethods_[LSOM_UPDATE])
        SubscribeToEvent(scene, E_SCENEUPDATE, HANDLER(LuaScriptInstance, HandleUpdate));

    if (scene && scriptObjectMethods_[LSOM_POSTUPDATE])
        SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(LuaScriptInstance, HandlePostUpdate));

#ifdef URHO3D_PHYSICS
    PhysicsWorld* physicsWorld = scene ? scene->GetComponent<PhysicsWorld>() : 0;

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDUPDATE])
        SubscribeToEvent(physicsWorld, E_PHYSICSPRESTEP, HANDLER(LuaScriptInstance, HandleFixedUpdate));

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDPOSTUPDATE])
        SubscribeToEvent(physicsWorld, E_PHYSICSPOSTSTEP, HANDLER(LuaScriptInstance, HandlePostFixedUpdate));
#endif

    if (node_ && scriptObjectMethods_[LSOM_TRANSFORMCHANGED])
        node_->AddListener(this);
}

void LuaScriptInstance::UnsubscribeFromScriptMethodEvents()
{
    Scene* scene = GetScene();
    if (scene && scriptObjectMethods_[LSOM_UPDATE])
        UnsubscribeFromEvent(scene, E_SCENEUPDATE);

    if (scene && scriptObjectMethods_[LSOM_POSTUPDATE])
        UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);

#ifdef URHO3D_PHYSICS
    PhysicsWorld* physicsWorld = scene ? scene->GetComponent<PhysicsWorld>() : 0;

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDUPDATE])
        UnsubscribeFromEvent(physicsWorld, E_PHYSICSPRESTEP);

    if (physicsWorld && scriptObjectMethods_[LSOM_FIXEDPOSTUPDATE])
        UnsubscribeFromEvent(physicsWorld, E_PHYSICSPOSTSTEP);
#endif

    if (node_ && scriptObjectMethods_[LSOM_TRANSFORMCHANGED])
        node_->RemoveListener(this);
}

void LuaScriptInstance::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_UPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}

void LuaScriptInstance::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PostUpdate;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_POSTUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}

#ifdef URHO3D_PHYSICS
void LuaScriptInstance::HandleFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_FIXEDUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}

void LuaScriptInstance::HandlePostFixedUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPostStep;
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    WeakPtr<LuaFunction> function = scriptObjectMethods_[LSOM_FIXEDPOSTUPDATE];
    if (function && function->BeginCall(this))
    {
        function->PushFloat(timeStep);
        function->EndCall();
    }
}
#endif

void LuaScriptInstance::HandleEvent(StringHash eventType, VariantMap& eventData)
{
    WeakPtr<LuaFunction> function = eventTypeToFunctionMap_[eventType];
    if (function && function->BeginCall(this))
    {
        function->PushUserType(eventType, "StringHash");
        function->PushUserType(eventData, "VariantMap");
        function->EndCall();
    }
}

void LuaScriptInstance::HandleObjectEvent(StringHash eventType, VariantMap& eventData)
{
    Object* object = GetEventSender();
    WeakPtr<LuaFunction> function = objectToEventTypeToFunctionMap_[object][eventType];
    if (function && function->BeginCall(this))
    {
        function->PushUserType(eventType, "StringHash");
        function->PushUserType(eventData, "VariantMap");
        function->EndCall();
    }
}

void LuaScriptInstance::ReleaseObject()
{
    if (scriptObjectRef_ == LUA_REFNIL)
        return;

    attributeInfos_ = *context_->GetAttributes(GetTypeStatic());

    if (IsEnabledEffective())
        UnsubscribeFromScriptMethodEvents();

    // Unref script object
    luaL_unref(luaState_, LUA_REGISTRYINDEX, scriptObjectRef_);
    scriptObjectRef_ = LUA_REFNIL;

    WeakPtr<LuaFunction> function = luaScript_->GetFunction("DestroyScriptObjectInstance");
    if (function && function->BeginCall())
    {
        function->PushUserType((void*)this, "LuaScriptInstance");
        function->EndCall();
    }
}

WeakPtr<LuaFunction> LuaScriptInstance::GetScriptObjectFunction(const String& functionName) const
{
    return luaScript_->GetFunction(scriptObjectType_ + "." + functionName, true);
}

void LuaScriptInstance::SetScriptFileAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetScriptFile(cache->GetResource<LuaFile>(value.name_));
}

ResourceRef LuaScriptInstance::GetScriptFileAttr() const
{
    return GetResourceRef(scriptFile_, LuaFile::GetTypeStatic());
}

}
