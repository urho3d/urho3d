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

#include "../Resource/ResourceCache.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Spark/SparkParticleEffect.h"
#include "../Spark/SPK_Urho3D_DEF.h"

#include "../DebugNew.h"

namespace Urho3D
{

SparkParticleEffect::SparkParticleEffect(Context* context) :
    Resource(context)
{
    loadedSystem_.reset();
}

SparkParticleEffect::~SparkParticleEffect()
{
}

void SparkParticleEffect::RegisterObject(Context* context)
{
    context->RegisterFactory<SparkParticleEffect>();
}

bool SparkParticleEffect::BeginLoad(Deserializer& source)
{
    String extension = GetExtension(source.GetName());
    extension.Erase(0,1); // erase dot in extension

    unsigned dataSize = source.GetSize();
    SharedArrayPtr<char> data(new char[dataSize]);
    source.Read(data.Get(), dataSize);

    loadedSystem_ = SPK::IO::IOManager::get().loadFromBuffer(extension.CString(), data, dataSize);

    if(loadedSystem_)
        return true;
    else
        URHO3D_LOGERROR(source.GetName() + " unable to load spark effect from file : " + source.GetName());

    return false;
}

bool SparkParticleEffect::EndLoad()
{
    return !!loadedSystem_;
}

bool SparkParticleEffect::Save(const String& filename) const
{
    if(loadedSystem_)
    {
        return SPK::IO::IOManager::get().save(filename.CString(), loadedSystem_);
    }

    return false;
}

const SPK::Ref<SPK::System> SparkParticleEffect::GetSystem() const
{
    return loadedSystem_;
}

void SparkParticleEffect::SetSystem(SPK::Ref<SPK::System> spkSystem)
{
    loadedSystem_ = spkSystem;
}

}
