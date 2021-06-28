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
