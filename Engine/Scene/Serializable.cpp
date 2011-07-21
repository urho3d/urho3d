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
#include "Context.h"
#include "Deserializer.h"
#include "Log.h"
#include "Serializable.h"
#include "Serializer.h"
#include "XMLElement.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(Serializable);

Serializable::Serializable(Context* context) :
    Object(context),
    inSerialization_(false)
{
}

Serializable::~Serializable()
{
}

void Serializable::OnSetAttribute(const AttributeInfo& attr, const Variant& value)
{
    // Check for accessor function mode
    if (attr.accessor_)
    {
        attr.accessor_->Set(this, value);
        return;
    }
    
    // Calculate the destination address
    void* dest = reinterpret_cast<unsigned char*>(this) + attr.offset_;
    
    switch (attr.type_)
    {
    case VAR_INT:
        // If enum type, use the low 8 bits only (assume full value to be initialized)
        if (attr.enumNames_)
            *(reinterpret_cast<unsigned char*>(dest)) = value.GetInt();
        else
            *(reinterpret_cast<int*>(dest)) = value.GetInt();
        break;
        
    case VAR_BOOL:
        *(reinterpret_cast<bool*>(dest)) = value.GetBool();
        break;
        
    case VAR_FLOAT:
        *(reinterpret_cast<float*>(dest)) = value.GetFloat();
        break;
        
    case VAR_VECTOR2:
        *(reinterpret_cast<Vector2*>(dest)) = value.GetVector2();
        break;
        
    case VAR_VECTOR3:
        *(reinterpret_cast<Vector3*>(dest)) = value.GetVector3();
        break;
        
    case VAR_VECTOR4:
        *(reinterpret_cast<Vector4*>(dest)) = value.GetVector4();
        break;
        
    case VAR_QUATERNION:
        *(reinterpret_cast<Quaternion*>(dest)) = value.GetQuaternion();
        break;
        
    case VAR_COLOR:
        *(reinterpret_cast<Color*>(dest)) = value.GetColor();
        break;
        
    case VAR_STRING:
        *(reinterpret_cast<String*>(dest)) = value.GetString();
        break;
        
    case VAR_BUFFER:
        *(reinterpret_cast<PODVector<unsigned char>*>(dest)) = value.GetBuffer();
        break;
        
    case VAR_RESOURCEREF:
        *(reinterpret_cast<ResourceRef*>(dest)) = value.GetResourceRef();
        break;
        
    case VAR_RESOURCEREFLIST:
        *(reinterpret_cast<ResourceRefList*>(dest)) = value.GetResourceRefList();
        break;
        
    case VAR_VARIANTVECTOR:
        *(reinterpret_cast<VariantVector*>(dest)) = value.GetVariantVector();
        break;
        
    case VAR_VARIANTMAP:
        *(reinterpret_cast<VariantMap*>(dest)) = value.GetVariantMap();
        break;
    }
}

Variant Serializable::OnGetAttribute(const AttributeInfo& attr)
{
    // Check for accessor function mode
    if (attr.accessor_)
        return attr.accessor_->Get(this);
    
    // Calculate the source address
    void* src = reinterpret_cast<unsigned char*>(this) + attr.offset_;
    
    switch (attr.type_)
    {
    case VAR_INT:
        // If enum type, use the low 8 bits only
        if (attr.enumNames_)
            return Variant(*(reinterpret_cast<const unsigned char*>(src)));
        else
            return Variant(*(reinterpret_cast<const int*>(src)));
        
    case VAR_BOOL:
        return Variant(*(reinterpret_cast<const bool*>(src)));
        
    case VAR_FLOAT:
        return Variant(*(reinterpret_cast<const float*>(src)));
        
    case VAR_VECTOR2:
        return Variant(*(reinterpret_cast<const Vector2*>(src)));
        
    case VAR_VECTOR3:
        return Variant(*(reinterpret_cast<const Vector3*>(src)));
        
    case VAR_VECTOR4:
        return Variant(*(reinterpret_cast<const Vector4*>(src)));
        
    case VAR_QUATERNION:
        return Variant(*(reinterpret_cast<const Quaternion*>(src)));
        
    case VAR_COLOR:
        return Variant(*(reinterpret_cast<const Color*>(src)));
        
    case VAR_STRING:
        return Variant(*(reinterpret_cast<const String*>(src)));
        
    case VAR_BUFFER:
        return Variant(*(reinterpret_cast<const PODVector<unsigned char>*>(src)));
        
    case VAR_RESOURCEREF:
        return Variant(*(reinterpret_cast<const ResourceRef*>(src)));
        
    case VAR_RESOURCEREFLIST:
        return Variant(*(reinterpret_cast<const ResourceRefList*>(src)));
        
    case VAR_VARIANTVECTOR:
        return Variant(*(reinterpret_cast<const VariantVector*>(src)));
        
    case VAR_VARIANTMAP:
        return Variant(*(reinterpret_cast<const VariantMap*>(src)));
    }
    
    return Variant();
}

bool Serializable::Load(Deserializer& source)
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
        return true;
    
    inSerialization_ = true;
    
    // Read attributes as Variants with predefined types from the attribute info
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_FILE))
            continue;
        
        if (source.IsEof())
        {
            LOGERROR("Could not load " + GetTypeName() + ", stream not open or at end");
            inSerialization_  = false;
            return false;
        }
        SetAttribute(i, source.ReadVariant(attr.type_));
    }
    
    inSerialization_ = false;
    return true;
}

bool Serializable::Save(Serializer& dest)
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
        return true;
    
    inSerialization_ = true;
    
    // Then write attributes as Variants without type
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_FILE))
            continue;
        
        if (!dest.WriteVariantData(GetAttribute(i)))
        {
            LOGERROR("Could not save " + GetTypeName() + ", writing to stream failed");
            inSerialization_ = false;
            return false;
        }
    }
    
    inSerialization_ = false;
    return true;
}

bool Serializable::LoadXML(const XMLElement& source)
{
    if (source.IsNull())
    {
        LOGERROR("Could not load " + GetTypeName() + ", null source element");
        return false;
    }
    
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
        return true;
    
    inSerialization_ = true;
    
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_FILE))
            continue;
        
        // We could assume fixed order. However, do name-based lookup instead for more robustness
        XMLElement attrElem = source.GetChild("attribute");
        bool found = false;
        while (attrElem)
        {
            if (attrElem.GetString("name") == attr.name_)
            {
                // If enums specified, do enum lookup and int assignment. Otherwise assign the variant directly
                if (attr.enumNames_)
                {
                    String value = attrElem.GetString("value");
                    const String* enumPtr = attr.enumNames_;
                    int enumValue = 0;
                    bool enumFound = false;
                    while (enumPtr->Length())
                    {
                        if (*enumPtr == value)
                        {
                            enumFound = true;
                            break;
                        }
                        ++enumPtr;
                        ++enumValue;
                    }
                    if (enumFound)
                        SetAttribute(i, Variant(enumValue));
                    else
                        LOGWARNING("Unknown enum value " + value + " in attribute " + String(attr.name_));
                }
                else
                    SetAttribute(i, attrElem.GetVariant());
                
                found = true;
                break;
            }
            
            attrElem = attrElem.GetNext("attribute");
        }
        
        if (!found)
            LOGWARNING("Attribute " + String(attr.name_) + " not found in XML data");
    }
    
    inSerialization_ = false;
    return true;
}

bool Serializable::SaveXML(XMLElement& dest)
{
    if (dest.IsNull())
    {
        LOGERROR("Could not save " + GetTypeName() + ", null destination element");
        return false;
    }
    
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
        return true;
    
    inSerialization_ = true;
    
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (!(attr.mode_ & AM_FILE))
            continue;
        
        XMLElement attrElem = dest.CreateChild("attribute");
        attrElem.SetString("name", String(attr.name_));
        // If enums specified, set as an enum string. Otherwise set directly as a Variant
        if (attr.enumNames_)
        {
            int enumValue = GetAttribute(i).GetInt();
            attrElem.SetString("type", "Enum");
            attrElem.SetString("value", String(attr.enumNames_[enumValue]));
        }
        else
            attrElem.SetVariant(GetAttribute(i));
    }
    
    inSerialization_ = false;
    return true;
}

bool Serializable::SetAttribute(unsigned index, const Variant& value)
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
    {
        LOGERROR(GetTypeName() + " has no attributes");
        return false;
    }
    if (index >= attributes->Size())
    {
        LOGERROR("Attribute index out of bounds");
        return false;
    }
    
    const AttributeInfo& attr = attributes->At(index);
    
    // Check that the new value's type matches the attribute type
    if (value.GetType() == attr.type_)
    {
        OnSetAttribute(attr, value);
        return true;
    }
    else
    {
        LOGERROR("Could not set attribute " + String(attr.name_) + ": expected type " + Variant::GetTypeName(attr.type_) +
            " but got " + value.GetTypeName());
        return false;
    }
}

bool Serializable::SetAttribute(const String& name, const Variant& value)
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
    {
        LOGERROR(GetTypeName() + " has no attributes");
        return false;
    }
    
    for (Vector<AttributeInfo>::ConstIterator i = attributes->Begin(); i != attributes->End(); ++i)
    {
        if (i->name_ == name)
        {
            // Check that the new value's type matches the attribute type
            if (value.GetType() == i->type_)
            {
                OnSetAttribute(*i, value);
                return true;
            }
            else
            {
                LOGERROR("Could not set attribute " + String(i->name_) + ": expected type " + Variant::GetTypeName(i->type_)
                    + " but got " + value.GetTypeName());
                return false;
            }
        }
    }
    
    LOGERROR("Could not find attribute " + String(name) + " in " + GetTypeName());
    return false;
}

Variant Serializable::GetAttribute(unsigned index)
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes || index >= attributes->Size())
        return Variant();
    
    return OnGetAttribute(attributes->At(index));
}

Variant Serializable::GetAttribute(const String& name)
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
    {
        LOGERROR(GetTypeName() + " has no attributes");
        return Variant();
    }
    
    for (Vector<AttributeInfo>::ConstIterator i = attributes->Begin(); i != attributes->End(); ++i)
    {
        if (i->name_ == name)
            return OnGetAttribute(*i);
    }
    
    LOGERROR("Could not find attribute " + String(name) + " in " + GetTypeName());
    return Variant();
}

unsigned Serializable::GetNumAttributes() const
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    return attributes ? attributes->Size() : 0;
}

unsigned Serializable::GetNumNetworkAttributes() const
{
    const Vector<AttributeInfo>* attributes = context_->GetAttributes(GetType());
    if (!attributes)
        return 0;
    
    unsigned num = 0;
    for (unsigned i = 0; i < attributes->Size(); ++i)
    {
        const AttributeInfo& attr = attributes->At(i);
        if (attr.mode_ & AM_NET)
            ++num;
    }
    
    return num;
}

const Vector<AttributeInfo>* Serializable::GetAttributes() const
{
    return context_->GetAttributes(GetType());
}
