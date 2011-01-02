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
#include "Hash.h"
#include "Log.h"
#include "StringUtils.h"

#include <cstring>
#include <map>
#include <string>

#include "DebugNew.h"

#include <ctype.h>

std::map<StringHash, std::string> hashes;
std::map<ShortStringHash, std::string> shortHashes;

StringHash::StringHash(const char* str) :
    mData(calculate(str))
{
}

StringHash::StringHash(const std::string& str) :
    mData(calculate(str.c_str()))
{
}

unsigned StringHash::calculate(const char* str)
{
    unsigned hash = 0;
    
    if (!str)
        return hash;
    
    while (*str)
    {
        // Perform the actual hashing as case-insensitive
        char c = *str;
        updateHash(hash, tolower(c));
        ++str;
    }
    
    return hash;
}

ShortStringHash::ShortStringHash(const char* str) :
    mData(calculate(str))
{
}

ShortStringHash::ShortStringHash(const std::string& str) :
    mData(calculate(str.c_str()))
{
}

unsigned short ShortStringHash::calculate(const char* str)
{
    return StringHash::calculate(str);
}

void registerHash(const std::string& str, bool throwIfCollision)
{
    StringHash hash(str);
    
    // Check for collision
    std::map<StringHash, std::string>::const_iterator i = hashes.find(hash);
    if ((i != hashes.end()) && (toLower(i->second) != toLower(str)))
    {
        std::string errorMsg = "Hash collision - " + str + " vs " + i->second;
        if (throwIfCollision)
            SAFE_EXCEPTION(errorMsg)
        else
            LOGERROR(errorMsg);
    }
    
    hashes[hash] = str;
}

const std::string& hashToString(StringHash hash)
{
    return hashes[hash];
}

void registerShortHash(const std::string& str, bool throwIfCollision)
{
    ShortStringHash hash(str);
    
    // Check for collision
    std::map<ShortStringHash, std::string>::const_iterator i = shortHashes.find(hash);
    if ((i != shortHashes.end()) && (toLower(i->second) != toLower(str)))
    {
        std::string errorMsg = "Short hash collision - " + str + " vs " + i->second;
        if (throwIfCollision)
            SAFE_EXCEPTION(errorMsg)
        else
            LOGERROR(errorMsg);
    }
    
    shortHashes[hash] = str;
}

const std::string& shortHashToString(ShortStringHash hash)
{
    return shortHashes[hash];
}

