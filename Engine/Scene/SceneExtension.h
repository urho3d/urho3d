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

#ifndef SCENE_SCENEEXTENSION_H
#define SCENE_SCENEEXTENSION_H

#include "HashedType.h"

class Deserializer;
class Serializer;
class XMLElement;

//! Base class for extending Scene functionality
class SceneExtension : public HashedType
{
public:
    //! Write properties to a stream
    virtual void save(Serializer& dest) {}
    //! Read properties from a stream
    virtual void load(Deserializer& source) {}
    //! Write properties to an XML element
    virtual void saveXML(XMLElement& dest) {}
    //! Read properties from an XML element
    virtual void loadXML(const XMLElement& source) {}
    //! Run scene update
    virtual void update(float timeStep) {}
    //! Set client-side prediction controls playback mode
    virtual void setPlayback(bool enable) {}
    
protected:
    //! Write extension type to a stream
    void writeExtensionType(Serializer& dest);
    //! Read extension type from a stream. Throw an extension in case of mismatch
    void checkExtensionType(Deserializer& source);
};

#endif // SCENE_SCENEEXTENSION_H
