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

#ifndef NINJA_H
#define NINJA_H

#include "GameObject.h"

class Ninja : public GameObject
{
    DEFINE_TYPE(Ninja);
    
    friend class AIController;
    friend class Game;
    
public:
    Ninja();
    static void setup();
    
    virtual void save(Serializer& dest);
    virtual void load(Deserializer& source, ResourceCache* cache);
    virtual void saveXML(XMLElement& dest);
    virtual void loadXML(const XMLElement& source, ResourceCache* cache);
    virtual bool writeNetUpdate(Serializer& dest, Serializer& destRevision, Deserializer& baseRevision, const NetUpdateInfo& info);
    virtual void readNetUpdate(Deserializer& source, ResourceCache* cache, const NetUpdateInfo& info);
    
    Quaternion getAim() const;
    float getAimX() const { return mAimX; }
    float getAimY() const { return mAimY; }
    
protected:
    bool mOkToJump;
    bool mSmoke;
    float mDeathTime;
    float mInAirTime;
    float mOnGroundTime;
    float mDeathDir;
    float mThrowTime;
    float mDirChangeTime;
    float mAimX;
    float mAimY;
    Controls mControls;
    Controls mPrevControls;
    
    void onCreate(const Vector3& position, const Quaternion& orientation);
    bool onUpdate(float time);
    void onRemove();
    bool onHeal(int amount);
    bool onDeathUpdate(float time);
};

#endif // NINJA_H
