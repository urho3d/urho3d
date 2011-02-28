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
#include "Exception.h"
#include "GameConfig.h"
#include "ResourceCache.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <tinyxml.h>

#include "DebugNew.h"

std::map<std::string, std::string> GameConfig::mSettings;
std::string mSection = "";

void GameConfig::load(const std::string& fileName, ResourceCache* cache)
{
    XMLFile* file = cache->getResource<XMLFile>(fileName);
    if (!file)
        return;
    
    const TiXmlElement* root = file->getRootElement().getElement();
    const TiXmlElement* element = 0;
    
    for (element = root->FirstChildElement(); element != 0; element = element->NextSiblingElement())
    {
        if ((!element->NoChildren()) && (!element->FirstChild()->NoChildren()))
            readSection(element, element->Value());
    }
}

void GameConfig::readSection(const TiXmlElement* parentElement, const std::string& name)
{
    const TiXmlElement* element = 0;
    
    for (element = parentElement->FirstChildElement(); element != 0; element = element->NextSiblingElement())
    {
        if (!element->NoChildren())
        {
            if (!element->FirstChild()->NoChildren())
                readSection(element, name + "/" + element->Value());
            else
            mSettings[name + "/" + element->Value()] = element->FirstChild()->Value();
        }
    }
}

void GameConfig::setSection(const std::string& name)
{
    if (name.length())
        mSection = name + "/";
    else
        mSection = name;
}

const std::string& GameConfig::get(const std::string& name)
{
    static const std::string empty;
    std::map<std::string, std::string>::const_iterator i = mSettings.find(mSection + name);
    if (i != mSettings.end())
        return i->second;
    else
        return empty;
}

bool GameConfig::getBool(const std::string& name)
{
    return toBool(get(name));
}

float GameConfig::getReal(const std::string& name)
{
    return toFloat(get(name));
}

int GameConfig::getInt(const std::string& name)
{
    return toInt(get(name));
}

Vector3 GameConfig::getVector3(const std::string& name)
{
    return toVector3(get(name));
}

Color GameConfig::getColor(const std::string& name)
{
    return toColor(get(name));
}

Quaternion GameConfig::getQuaternion(const std::string& name)
{
    return toQuaternion(get(name));
}
