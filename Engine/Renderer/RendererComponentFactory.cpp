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

#include "Precompiled.h"
#include "AnimatedModel.h"
#include "BillboardSet.h"
#include "CustomObject.h"
#include "InstancedModel.h"
#include "Light.h"
#include "Material.h"
#include "Octree.h"
#include "RendererComponentFactory.h"
#include "Skybox.h"
#include "Zone.h"

#include "DebugNew.h"

RendererComponentFactory::RendererComponentFactory(Octree* octree) :
    mOctree(octree)
{
}

Component* RendererComponentFactory::createComponent(ShortStringHash type, const std::string& name)
{
    if (type == Camera::getTypeStatic())
        return new Camera(name);
    
    if (type == Bone::getTypeStatic())
        return new Bone(0, name);
    
    if (type == Light::getTypeStatic())
        return new Light(mOctree, name);
    
    if (type == StaticModel::getTypeStatic())
        return new StaticModel(mOctree, name);
    
    if (type == AnimatedModel::getTypeStatic())
        return new AnimatedModel(mOctree, name);
    
    if (type == InstancedModel::getTypeStatic())
        return new InstancedModel(mOctree, name);
    
    if (type == BillboardSet::getTypeStatic())
        return new BillboardSet(mOctree, name);
    
    if (type == CustomObject::getTypeStatic())
        return new CustomObject(mOctree, name);
    
    if (type == Skybox::getTypeStatic())
        return new Skybox(mOctree, name);
    
    if (type == Zone::getTypeStatic())
        return new Zone(mOctree, name);
    
    return 0;
}

void RendererComponentFactory::getComponentTypes(std::vector<std::string>& dest)
{
    dest.push_back(Camera::getTypeNameStatic());
    dest.push_back(Bone::getTypeNameStatic());
    dest.push_back(Light::getTypeNameStatic());
    dest.push_back(StaticModel::getTypeNameStatic());
    dest.push_back(AnimatedModel::getTypeNameStatic());
    dest.push_back(InstancedModel::getTypeNameStatic());
    dest.push_back(BillboardSet::getTypeNameStatic());
    dest.push_back(CustomObject::getTypeNameStatic());
    dest.push_back(Skybox::getTypeNameStatic());
    dest.push_back(Zone::getTypeNameStatic());
}
