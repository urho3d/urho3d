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

#pragma once

#include "Context.h"
#include "LuaScript.h"
#include "ProcessUtils.h"
#include "Variant.h"
#include "Timer.h"

namespace Urho3D
{
    const char* GetPlatformCString()
    {
        static String platform = GetPlatform();
        return platform.CString();
    }

    Time* GetTime()
    {
        return GetLuaScriptContext()->GetSubsystem<Time>();
    }

    const Variant& FindVariant(const VariantMap* vmap, const char* key)
    {
        VariantMap::ConstIterator i = vmap->Find(ShortStringHash(key));
        return i != vmap->End() ? i->second_ : Variant::EMPTY;
    }
    int VariantMapGetInt(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetInt();
    }
    bool VariantMapGetBool(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetBool();
    }
    float VariantMapGetFloat(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetFloat();
    }
    const Vector2& VariantMapGetVector2(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetVector2();
    }
    const Vector3& VariantMapGetVector3(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetVector3();
    }
    const Vector4& VariantMapGetVector4(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetVector4();
    }
    const Quaternion& VariantMapGetQuaternion(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetQuaternion();
    }
    const Color& VariantMapGetColor(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetColor();
    }
    const String& VariantMapGetString(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetString();
    }
    const void* VariantMapGetPtr(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetPtr();
    }
    const ResourceRef& VariantMapGetResourceRef(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetResourceRef();
    }
    const ResourceRefList& VariantMapGetResourceRefList(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetResourceRefList();
    }
    const IntRect& VariantMapGetIntRect(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetIntRect();
    }
    const IntVector2& VariantMapGetIntVector2(const VariantMap* vmap, const char* key)
    {
        return FindVariant(vmap, key).GetIntVector2();
    }

    void VariantMapSetInt(VariantMap* vmap, const char* key, int value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetBool(VariantMap* vmap, const char* key, bool value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetFloat(VariantMap* vmap, const char* key, float value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetVector2(VariantMap* vmap, const char* key, const Vector2& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetVector3(VariantMap* vmap, const char* key, const Vector3& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetVector4(VariantMap* vmap, const char* key, const Vector4& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetQuaternion(VariantMap* vmap, const char* key, const Quaternion& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetColor(VariantMap* vmap, const char* key, const Color& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetString(VariantMap* vmap, const char* key, const String& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetPtr(VariantMap* vmap, const char* key, const void* value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetResourceRef(VariantMap* vmap, const char* key, const ResourceRef& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetResourceRefList(VariantMap* vmap, const char* key, const ResourceRefList& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetIntRect(VariantMap* vmap, const char* key, const IntRect& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
    void VariantMapSetIntVector2(VariantMap* vmap, const char* key, const IntVector2& value)
    {
        (*vmap)[ShortStringHash(key)] = value;
    }
}