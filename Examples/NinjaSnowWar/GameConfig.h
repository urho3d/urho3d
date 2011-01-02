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

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include "Vector3.h"
#include "Color.h"
#include "Quaternion.h"

#include <string>

class TiXmlElement;
class ResourceCache;

class GameConfig
{
public:
    static void load(const std::string& fileName, ResourceCache* cache);
    static const std::string& get(const std::string& name);
    static bool getBool(const std::string& name);
    static float getReal(const std::string& name);
    static int getInt(const std::string& name);
    static Vector3 getVector3(const std::string& name);
    static Color getColor(const std::string& name);
    static Quaternion getQuaternion(const std::string& name);
    static void setSection(const std::string& name = "");
    
private:
    static std::map<std::string, std::string> mSettings;
    static void readSection(const TiXmlElement* parentElement, const std::string& name);
};

#endif // GAMECONFIG_H
