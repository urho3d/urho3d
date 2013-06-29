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

#include "Animation.h"
#include "Context.h"
#include "Font.h"
#include "Image.h"
#include "LuaScript.h"
#include "Material.h"
#include "Model.h"
#include "ResourceCache.h"
#include "Sound.h"
#include "Technique.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "XMLFile.h"

namespace Urho3D
{

    ResourceCache* GetCache()
    {
        return GetLuaScriptContext()->GetSubsystem<ResourceCache>();
    }

    Animation* ResourceCacheGetAnimation(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Animation>(fileName);
    }
    
    Font* ResourceCacheGetFont(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Font>(fileName);
    }

    Image* ResourceCacheGetImage(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Image>(fileName);
    }
    
    Material* ResourceCacheGetMaterial(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Material>(fileName);
    }

    Model* ResourceCacheGetModel(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Model>(fileName);
    }

    Sound* ResourceCacheGetSound(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Sound>(fileName);
    }

    Technique* ResourceCacheGetTechnique(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Technique>(fileName);
    }

    Texture2D* ResourceCacheGetTexture2D(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<Texture2D>(fileName);
    }

    TextureCube* ResourceCacheGetTextureCube(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<TextureCube>(fileName);
    }

    XMLFile * ResourceCacheGetXMLFile(ResourceCache* cache, const char* fileName)
    {
        return cache->GetResource<XMLFile>(fileName);
    }
}