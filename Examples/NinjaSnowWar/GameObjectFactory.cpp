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
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Ninja.h"
#include "SnowBall.h"
#include "SnowCrate.h"
#include "Potion.h"

#include "DebugNew.h"

Component* GameObjectFactory::createComponent(ShortStringHash type, const std::string& name)
{
    if (type == GameObject::getTypeStatic())
        return new GameObject();
    
    if (type == Ninja::getTypeStatic())
        return new Ninja();
    
    if (type == SnowBall::getTypeStatic())
        return new SnowBall();
    
    if (type == SnowCrate::getTypeStatic())
        return new SnowCrate();
    
    if (type == Potion::getTypeStatic())
        return new Potion();
    
    return 0;
}

void GameObjectFactory::getComponentTypes(std::vector<std::string>& dest)
{
    dest.push_back(GameObject::getTypeNameStatic());
    dest.push_back(Ninja::getTypeNameStatic());
    dest.push_back(SnowBall::getTypeNameStatic());
    dest.push_back(SnowCrate::getTypeNameStatic());
    dest.push_back(Potion::getTypeNameStatic());
}
