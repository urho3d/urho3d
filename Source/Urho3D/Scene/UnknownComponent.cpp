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

#include "../Core/Context.h"
#include "../IO/Deserializer.h"
#include "../IO/Log.h"
#include "../IO/Serializer.h"
#include "../Scene/UnknownComponent.h"
#include "../Resource/XMLElement.h"

#include "../DebugNew.h"

namespace Urho3D
{

static HashMap<StringHash, String> unknownTypeToName;
static String letters("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

static String GenerateNameFromType(StringHash typeHash)
{
    if (unknownTypeToName.Contains(typeHash))
        return unknownTypeToName[typeHash];
    
    String test;
    
    // Begin brute-force search
    unsigned numLetters = letters.Length();
    unsigned combinations = numLetters;
    bool found = false;
    
    for (unsigned i = 1; i < 6; ++i)
    {
        test.Resize(i);
        
        for (unsigned j = 0; j < combinations; ++j)
        {
            unsigned current = j;
            
            for (unsigned k = 0; k < i; ++k)
            {
                test[k] = letters[current % numLetters];
                current /= numLetters;
            }
            
            if (StringHash(test) == typeHash)
            {
                found = true;
                break;
            }
        }
        
        if (found)
            break;
        
        combinations *= numLetters;
    }
    
    unknownTypeToName[typeHash] = test;
    return test;
}

UnknownComponent::UnknownComponent(Context* context) :
    Component(context),
    useXML_(false)
{
}

void UnknownComponent::RegisterObject(Context* context)
{
    context->RegisterFactory<UnknownComponent>();
}

bool UnknownComponent::Load(Deserializer& source, bool setInstanceDefault)
{
    useXML_ = false;
    xmlAttributes_.Clear();
    xmlAttributeInfos_.Clear();
    
    // Assume we are reading from a component data buffer, and the type has already been read
    unsigned dataSize = source.GetSize() - source.GetPosition();
    binaryAttributes_.Resize(dataSize);
    return dataSize ? source.Read(&binaryAttributes_[0], dataSize) == dataSize : true;
}

bool UnknownComponent::LoadXML(const XMLElement& source, bool setInstanceDefault)
{
    useXML_ = true;
    xmlAttributes_.Clear();
    xmlAttributeInfos_.Clear();
    binaryAttributes_.Clear();
    
    XMLElement attrElem = source.GetChild("attribute");
    while (attrElem)
    {
        AttributeInfo attr;
        attr.mode_ = AM_FILE;
        attr.name_ = attrElem.GetAttribute("name");
        attr.type_ = VAR_STRING;
        
        if (!attr.name_.Empty())
        {
            String attrValue = attrElem.GetAttribute("value");
            attr.defaultValue_ = String::EMPTY;
            xmlAttributeInfos_.Push(attr);
            xmlAttributes_.Push(attrValue);
        }
        
        attrElem = attrElem.GetNext("attribute");
    }
    
    // Fix up pointers to the attributes after all have been read
    for (unsigned i = 0; i < xmlAttributeInfos_.Size(); ++i)
        xmlAttributeInfos_[i].ptr_ = &xmlAttributes_[i];
    
    return true;
}

bool UnknownComponent::Save(Serializer& dest) const
{
    if (useXML_)
        LOGWARNING("UnknownComponent loaded in XML mode, attributes will be empty for binary save");
    
    // Write type and ID
    if (!dest.WriteStringHash(GetType()))
        return false;
    if (!dest.WriteUInt(id_))
        return false;
    
    if (!binaryAttributes_.Size())
        return true;
    else
        return dest.Write(&binaryAttributes_[0], binaryAttributes_.Size()) == binaryAttributes_.Size();
}

bool UnknownComponent::SaveXML(XMLElement& dest) const
{
    if (dest.IsNull())
    {
        LOGERROR("Could not save " + GetTypeName() + ", null destination element");
        return false;
    }
    
    if (!useXML_)
        LOGWARNING("UnknownComponent loaded in binary mode, attributes will be empty for XML save");
    
    // Write type and ID
    if (!dest.SetString("type", GetTypeName()))
        return false;
    if (!dest.SetInt("id", id_))
        return false;
    
    for (unsigned i = 0; i < xmlAttributeInfos_.Size(); ++i)
    {
        XMLElement attrElem = dest.CreateChild("attribute");
        attrElem.SetAttribute("name", xmlAttributeInfos_[i].name_);
        attrElem.SetAttribute("value", xmlAttributes_[i]);
    }
    
    return true;
}

void UnknownComponent::SetTypeName(const String& typeName)
{
    typeName_ = typeName;
    typeHash_ = typeName;
}

void UnknownComponent::SetType(StringHash typeHash)
{
    typeName_ = GenerateNameFromType(typeHash);
    typeHash_ = typeHash;
}

}
