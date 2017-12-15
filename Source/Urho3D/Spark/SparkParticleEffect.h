//
// Copyright (c) 2008-2017 the Urho3D project.
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

#pragma once

#ifndef H_SPARKPARTICLEEFFECT
#define H_SPARKPARTICLEEFFECT

#include "../Graphics/GraphicsDefs.h"
#include "../Resource/Resource.h"

#include <Spark/SPARK_Core.h>

namespace Urho3D
{

class XMLFile;
class XMLElement;

/// %Spark Particle effect definition.
class URHO3D_API SparkParticleEffect : public Resource
{
    URHO3D_OBJECT(SparkParticleEffect, Resource);

public:
    /// Construct.
    SparkParticleEffect(Context* context);
    /// Destruct.
    virtual ~SparkParticleEffect() override;
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source) override;
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad() override;
    /// Save resource. Return true if successful.
    bool Save(const String &filename) const;

    /// Get Spark particle system loaded
    const SPK::Ref<SPK::System> GetSystem() const;

    /// Manually set spark particle system
    void SetSystem(SPK::Ref<SPK::System> spkSystem);

private:
    /// loaded spark particle system
    SPK::Ref<SPK::System> loadedSystem_;

};

}

#endif // H_SPARKPARTICLEEFFECT
