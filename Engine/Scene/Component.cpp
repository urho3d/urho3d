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
#include "Node.h"
#include "ReplicationUtils.h"
#include "ResourceCache.h"
#include "Scene.h"

#include "DebugNew.h"

Component::Component(const std::string& name) :
    mEntity(0),
    mName(name),
    mNameHash(name),
    mNetFlags(NET_SYNCTOALL)
{
}

void Component::save(Serializer& dest)
{
    // Write type hash & name
    dest.writeShortStringHash(getType());
    dest.writeString(mName);
    
    // Write netflags
    dest.writeUByte(mNetFlags);
}

void Component::load(Deserializer& source, ResourceCache* cache)
{
    // Type and name are handled on the Entity level
    
    // Read netflags
    mNetFlags = source.readUByte();
}

void Component::saveXML(XMLElement& dest)
{
    // Write typename & name
    dest.setString("type", getTypeName());
    if (!mName.empty())
        dest.setString("name", mName);
    
    // Write netflags
    dest.setInt("netflags", mNetFlags);
}

void Component::loadXML(const XMLElement& source, ResourceCache* cache)
{
    // Type and name are handled on the Entity level
    
    // Read netflags
    mNetFlags = source.getInt("netflags");
}

void Component::postLoad(ResourceCache* cache)
{
}

bool Component::writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info)
{
    return false; // No data to write
}

void Component::readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info)
{
}

void Component::postNetUpdate(ResourceCache* cache)
{
}

void Component::interpolate(bool snapToEnd)
{
}

void Component::getComponentRefs(std::vector<ComponentRef>& dest)
{
}

void Component::setName(const std::string& name)
{
    mName = name;
    mNameHash = StringHash(name);
}

void Component::setNetFlags(unsigned char flags)
{
    // Respect the authority and proxy flags if they have been set already
    if (mNetFlags & NET_MODEFLAGS)
        mNetFlags = (mNetFlags & NET_MODEFLAGS) | (flags & ~NET_MODEFLAGS);
    else
        mNetFlags = flags;
}

bool Component::isPlayback() const
{
    if (!mEntity)
        return false;
    return mEntity->isPlayback();
}

bool Component::checkSync(Connection* connection) const
{
    if (!mEntity)
        return false;
    
    if ((mNetFlags & NET_SYNCTONONE) || (mEntity->getNetFlags() & NET_SYNCTONONE))
        return false;
    
    if ((mNetFlags & NET_SYNCTOOWNER) || (mEntity->getNetFlags() & NET_SYNCTOOWNER))
        return mEntity->getOwner() == connection;
    
    return true;
}

bool Component::checkPrediction(Connection* connection) const
{
    if ((!mEntity) || (!(mNetFlags & NET_PREDICTIONFLAGS)))
        return false;
    return mEntity->checkPrediction(connection);
}

ComponentRef::ComponentRef(Component* component, bool forXML) :
    mEntityID(0),
    mDirty(false)
{
    if (!component)
        return;
    
    if (component->getEntity())
    {
        mEntityID = component->getEntity()->getID();
        mHash = component->getCombinedHash();
    }
    else
    {
        // The component does not directly belong to an entity. However, if it is a scene node, check if any of the components
        // in the parent chain belongs to an entity
        Node* node = dynamic_cast<Node*>(component);
        while (node)
        {
            node = node->getParent();
            if ((node) && (node->getEntity()))
            {
                mEntityID = node->getEntity()->getID();
                mHash = component->getCombinedHash();
                break;
            }
        }
    }
    
    if (forXML)
    {
        mTypeName = component->getTypeName();
        mName = component->getName();
    }
}

void ComponentRef::write(Serializer& dest) const
{
    dest.writeUInt(mEntityID);
    if (mEntityID)
        dest.writeShortStringHash(mHash);
}

void ComponentRef::read(Deserializer& source)
{
    mEntityID = source.readUInt();
    if (mEntityID)
        mHash = source.readShortStringHash();
    else
        mHash = ShortStringHash();
    mDirty = true;
}

void ComponentRef::writePacked(Serializer& dest) const
{
    dest.writeUShort(mEntityID);
    if (mEntityID)
        dest.writeShortStringHash(mHash);
}

void ComponentRef::readPacked(Deserializer& source)
{
    mEntityID = source.readUShort();
    if (mEntityID)
        mHash = source.readShortStringHash();
    else
        mHash = ShortStringHash();
    mDirty = true;
}

void ComponentRef::writeXML(XMLElement& dest) const
{
    if ((mHash.mData) && (mTypeName.empty()))
        SAFE_EXCEPTION("Component reference was not initialized with typename and name information");
    
    dest.setInt("id", mEntityID);
    dest.setString("type", mTypeName);
    if (!mName.empty())
        dest.setString("name", mName);
}

void ComponentRef::readXML(const XMLElement& source)
{
    if (source)
    {
        mEntityID = source.getInt("id");
        mHash = ShortStringHash(source.getString("type")) + ShortStringHash(source.getString("name"));
    }
    else
    {
        mEntityID = 0;
        mHash = ShortStringHash();
    }
    
    mDirty = true;
}
