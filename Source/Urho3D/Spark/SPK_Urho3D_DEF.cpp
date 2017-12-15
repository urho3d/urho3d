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

#include "SPK_Urho3D_DEF.h"
#include "SPK_Urho3D_QuadRenderer.h"
#include "SparkParticle.h"
#include "SparkParticleEffect.h"
#include <Spark/Core/IO/SPK_IO_Manager.h>

namespace Urho3D {

void URHO3D_API RegisterSparkLibrary(Context* context)
{
    // Register Urho3D context for urho3d/spark objects
    SPK::URHO::Urho3DContext::get().registerUrhoContext(context);

    // Register Urho3DQuadRenderer to IO
    SPK::IO::IOManager::get().registerObject<SPK::URHO::Urho3DQuadRenderer>();

    // Register Urho3D objects
    SparkParticleEffect::RegisterObject(context);
    SparkParticle::RegisterObject(context);
}

}


namespace SPK {
namespace URHO {

    Urho3DContext::Urho3DContext()
    {       
    }

    Urho3DContext& Urho3DContext::get()
    {
        static Urho3DContext instance;
        return instance;
    }    

    void Urho3DContext::registerUrhoContext(Urho3D::Context* context)
    {
        SPK_ASSERT(context, "[registerUrhoContext] : Urho3D context is null.");
        urhoContext = context;       
    }

    Urho3D::Context* Urho3DContext::getUrhoContext()
    {
        SPK_ASSERT(urhoContext, "[getUrhoContext] : Urho3D Context is null, use registerUrhoContext");
        return urhoContext;
    }


    //////////////////////////
    // Conversion functions //
    //////////////////////////


    inline Urho3D::Vector3 spk2urho(const Vector3D& v)
    {
        return Urho3D::Vector3(v.x, v.y, v.z);
    }

    inline SPK::Vector3D urho2spk(const Urho3D::Vector3& v)
    {
        return Vector3D(v.x_, v.y_, v.z_);
    }

    inline Urho3D::Color spk2urho(unsigned char a, unsigned char  r, unsigned char  g, unsigned char  b)
    {
        return Urho3D::Color(r,g,b,a);
    }

    inline const Urho3D::Color spk2urho(SPK::Color c)
    {
        return Urho3D::Color(c.r, c.g, c.g, c.a);
    }

}}
