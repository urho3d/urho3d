// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../AngelScript/APITemplates.h"
#include "../Graphics/DebugRenderer.h"
#include "../IO/PackageFile.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/Scene.h"
#include "../Scene/SmoothedTransform.h"
#include "../Scene/SplinePath.h"
#include "../Scene/ValueAnimation.h"

namespace Urho3D
{

static void RegisterNode(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("Node@+ get_node()", AS_FUNCTION(GetScriptContextNode), AS_CALL_CDECL);
}

static CScriptArray* GetObjectCategories()
{
    Vector<String> categories = GetScriptContext()->GetObjectCategories().Keys();
    Sort(categories.Begin(), categories.End());
    return VectorToArray<String>(categories, "Array<String>");
}

static CScriptArray* GetObjectsByCategory(const String& category)
{
    const HashMap<String, Vector<StringHash> >& categories = GetScriptContext()->GetObjectCategories();
    Vector<String> components;

    HashMap<String, Vector<StringHash> >::ConstIterator i = categories.Find(category);
    if (i != categories.End())
    {
        const HashMap<StringHash, SharedPtr<ObjectFactory> >& factories = GetScriptContext()->GetObjectFactories();
        const Vector<StringHash>& factoryHashes = i->second_;
        components.Reserve(factoryHashes.Size());

        for (unsigned j = 0; j < factoryHashes.Size(); ++j)
        {
            HashMap<StringHash, SharedPtr<ObjectFactory> >::ConstIterator k = factories.Find(factoryHashes[j]);
            if (k != factories.End())
                components.Push(k->second_->GetTypeName());
        }
    }

    Sort(components.Begin(), components.End());
    return VectorToArray<String>(components, "Array<String>");
}

static CScriptArray* GetObjectAttributeInfos(const String& objectType)
{
    const Vector<AttributeInfo>* attributes = GetScriptContext()->GetAttributes(Urho3D::StringHash(objectType));
    static Vector<AttributeInfo> emptyAttributes;
    return VectorToArray<AttributeInfo>(attributes ? *attributes : emptyAttributes, "Array<AttributeInfo>");
}

static void RegisterScene(asIScriptEngine* engine)
{
    engine->RegisterGlobalFunction("Scene@+ get_scene()", AS_FUNCTION(GetScriptContextScene), AS_CALL_CDECL);

    engine->RegisterGlobalFunction("Array<String>@ GetObjectCategories()", AS_FUNCTION(GetObjectCategories), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("Array<String>@ GetObjectsByCategory(const String&in)", AS_FUNCTION(GetObjectsByCategory), AS_CALL_CDECL);
    engine->RegisterGlobalFunction("Array<AttributeInfo>@ GetObjectAttributeInfos(const String&in)", AS_FUNCTION(GetObjectAttributeInfos), AS_CALL_CDECL);
}

void RegisterSceneAPI(asIScriptEngine* engine)
{
    RegisterNode(engine);
    RegisterScene(engine);
}

}
