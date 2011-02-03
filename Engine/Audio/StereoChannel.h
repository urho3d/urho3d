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

#ifndef AUDIO_STEREOCHANNEL_H
#define AUDIO_STEREOCHANNEL_H

#include "Channel.h"
#include "Component.h"

//! A stereo channel component
class StereoChannel: public Channel, public Component
{
    DEFINE_TYPE(StereoChannel);
    
public:
    //! Construct with Audio subsystem pointer
    StereoChannel(Audio* audio, const std::string& name = std::string());
    
    //! Write component state to a stream
    virtual void save(Serializer& dest);
    //! Read component state from a stream
    virtual void load(Deserializer& source, ResourceCache* cache);
    //! Write component state to an XML element
    virtual void saveXML(XMLElement& dest);
    //! Read component state from an XML element
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    //! Write a network update
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    //! Read a network update
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    //! Return resource references
    virtual void getResourceRefs(std::vector<Resource*>& dest);
    //! Update channel
    virtual void update(float timeStep);
    
    //! Set whether the channel is automatically removed from the Entity when the sound playback stops
    void setAutoRemove(bool enable);
    
    //! Return autoremove flag
    bool getAutoRemove() const { return mAutoRemove; }
    
protected:
    //! Autoremove timer
    float mAutoRemoveTimer;
    //! Autoremove flag
    bool mAutoRemove;
};

#endif // AUDIO_STEREOCHANNEL_H
