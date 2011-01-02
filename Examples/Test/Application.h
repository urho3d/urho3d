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

#ifndef TEST_APPLICATION_H
#define TEST_APPLICATION_H

#include "EventListener.h"
#include "SharedPtr.h"

#include <string>
#include <vector>

class AnimatedModel;
class BillboardSet;
class BorderImage;
class Camera;
class Channel;
class DebugHud;
class Engine;
class Entity;
class Geometry;
class Light;
class Material;
class Model;
class Node;
class Octree;
class ResourceCache;
class RigidBody;
class Scene;
class Song;
class Sound;
class Text;
class Texture2D;
class TiXmlElement;
class VolumeNode;
class XMLFile;
class Zone;

class Application : public EventListener
{
public:
    Application(const std::vector<std::string>& arguments);
    ~Application();
    
    void run();

private:
    void init();
    void createScene();
    void handleUpdate(StringHash eventType, VariantMap& eventData);
    void handlePostRenderUpdate(StringHash eventType, VariantMap& eventData);
    void handleMouseMove(StringHash eventType, VariantMap& eventData);
    void handleMouseButtonDown(StringHash eventType, VariantMap& eventData);
    void handleMouseButtonUp(StringHash eventType, VariantMap& eventData);
    
    std::vector<std::string> mArguments;
    
    SharedPtr<Engine> mEngine;
    SharedPtr<ResourceCache> mCache;
    SharedPtr<Scene> mScene;
    
    std::vector<Entity*> mAnimatingObjects;
    std::vector<Entity*> mLights;
    std::vector<Entity*> mBillboards;
    Entity* mCameraEntity;
    
    SharedPtr<Texture2D> mOcclusionDebugTexture;
    SharedPtr<BorderImage> mOcclusionDebugImage;
};

#endif // TEST_APPLICATION_H
