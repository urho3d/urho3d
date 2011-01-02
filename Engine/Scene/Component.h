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

#ifndef SCENE_COMPONENT_H
#define SCENE_COMPONENT_H

#include "HashedType.h"

typedef unsigned EntityID;

class Connection;
class Deserializer;
class Entity;
class ResourceCache;
class Serializer;
class XMLElement;
class VectorBuffer;

static const unsigned char NET_NONE = 0x00;
static const unsigned char NET_AUTHORITY = 0x01;
static const unsigned char NET_PROXY = 0x02;
static const unsigned char NET_OWNER = 0x04;
static const unsigned char NET_OWNERPREDICT = 0x08;
static const unsigned char NET_TRANSIENTPREDICT = 0x10;
static const unsigned char NET_SYNCTOALL = 0x00;
static const unsigned char NET_SYNCTOOWNER = 0x20;
static const unsigned char NET_SYNCTONONE = 0x40;

static const unsigned char NET_MODEFLAGS = 0x03;
static const unsigned char NET_PREDICTIONFLAGS = 0x18;
static const unsigned char NET_SYNCFLAGS = 0x60;

//! Information about a network update being written or read
struct NetUpdateInfo
{
    //! Remote connection
    Connection* mConnection;
    //! Local frame number
    unsigned short mFrameNumber;
    //! Last local frame number acked by the remote end
    unsigned short mFrameAck;
    //! Remote frame number
    unsigned short mRemoteFrameNumber;
    //! Estimated round trip time
    float mRoundTripTime;
};

struct ComponentRef;

//! Base class for components
class Component : public HashedType
{
    friend class Entity;
    
public:
    //! Construct with name
    Component(const std::string& name = std::string());
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Resolve component references after loading
    virtual void postLoad(ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Resolve component references after a network update
    virtual void postNetUpdate(ResourceCache* cache);
    //! Perform client-side visual smoothing
    virtual void interpolate(bool snapToEnd = false);
    //! Return component references
    virtual void getComponentRefs(std::vector<ComponentRef>& dest);
    
    //! Set name
    void setName(const std::string& name);
    //! Set network replication flags
    void setNetFlags(unsigned char flags);
    
    //! Return name
    const std::string& getName() const { return mName; }
    //! Return name hash
    StringHash getNameHash() const { return mNameHash; }
    //! Return combined 16-bit hash of type and name. Used for concise network identification
    ShortStringHash getCombinedHash() const { return getType() + ShortStringHash(mNameHash); }
    //! Return network replication flags
    unsigned char getNetFlags() const { return mNetFlags; }
    //! Return entity
    Entity* getEntity() const { return mEntity; }
    //! Return whether is in a server scene
    bool isAuthority() const { return (mNetFlags & NET_AUTHORITY) != 0; }
    //! Return whether is in a client scene
    bool isProxy() const { return (mNetFlags & NET_PROXY) != 0; }
    //! Return whether is client-side predicted by the owner
    bool isOwnerPredicted() const { return (mNetFlags & NET_OWNERPREDICT) != 0; }
    //! Return whether can be transiently client-side predicted
    bool isTransientPredicted() const { return (mNetFlags & NET_TRANSIENTPREDICT) != 0; }
    //! Return whether scene is performing client-side prediction by replaying controls
    bool isPlayback() const;
    //! Return whether component should be replicated to the connection
    bool checkSync(Connection* connection) const;
    //! Return whether should do client-side prediction on the component
    bool checkPrediction(Connection* connection = 0) const;
    
protected:
    //! Entity
    Entity* mEntity;
    
private:
    //! Name
    std::string mName;
    //! Name hash
    StringHash mNameHash;
    //! Network replication flags
    unsigned char mNetFlags;
};

//! Refers to other components during scene save/load or network updates
struct ComponentRef
{
    //! Construct as empty
    ComponentRef() :
        mEntityID(0),
        mDirty(false)
    {
    }
    
    //! Construct with component pointer. Optionally add information for XML serialization
    ComponentRef(Component* component, bool forXML = false);
    
    //! Test for equality with another component reference
    bool operator == (const ComponentRef& rhs) const
    {
        return (mEntityID == rhs.mEntityID) && (mHash == rhs.mHash);
    }
    
    //! Test for inequality with another componet reference
    bool operator != (const ComponentRef& rhs) const
    {
        return (mEntityID != rhs.mEntityID) || (mHash != rhs.mHash);
    }
    
    //! Write to a stream
    void write(Serializer& dest) const;
    //! Read from a stream
    void read(Deserializer& source);
    //! Write in packed format, where entity ID is only 16 bits
    void writePacked(Serializer& dest) const;
    //! Read in packet format, where entity ID is only 16 bits
    void readPacked(Deserializer& source);
    //! Write to an XML element
    void writeXML(XMLElement& dest) const;
    //! Read from an XML element
    void readXML(const XMLElement& source);
    
    //! Entity ID
    EntityID mEntityID;
    //! Combined hash of component type and name
    ShortStringHash mHash;
    //! Component type name for XML serialization
    std::string mTypeName;
    //! Component name for XML serialization
    std::string mName;
    //! Dirty flag. Set by deserialization
    bool mDirty;
};

#endif // SCENE_COMPONENT_H
