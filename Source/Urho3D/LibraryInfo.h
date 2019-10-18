//
// Copyright (c) 2008-2019 the Urho3D project.
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

#ifdef URHO3D_IS_BUILDING
#include "Urho3D.h"
#include "librevision.h"
#else
#include <Urho3D/Urho3D.h>
#include <Urho3D/librevision.h>
#endif

namespace Urho3D
{
/**
 *  \brief Get the version of Urho3D that is linked against your program.
 *
 *  If you are linking to Urho3D dynamically, then it is possible that the
 *  current version will be different than the version you compiled against.
 *  This function returns the current version, while SDL_VERSION() is a
 *  macro that tells you what version you compiled with.
 *
 *  \code
 *  UrhoVersion compiled;
 *  UrhoVersion linked;
 *
 *  URHO3D_VERSION(&compiled);
 *  ::Urho3D::GetVersion(&linked);
 *  printf("We compiled against Urho3D version %d.%d.%d ...\n",
 *         compiled.major, compiled.minor, compiled.patch);
 *  printf("But we linked against Urho3D version %d.%d.%d.\n",
 *         linked.major, linked.minor, linked.patch);
 *  \endcode
 *
 *  This function may be called safely at any time
 *
 *  \sa URHO3D_VERSION
 */
/// Get the version of Urho3D that is linked against your program.
URHO3D_API void GetVersion(UrhoVersion* ver);

/// Return git description of the HEAD when building the library.
URHO3D_API unsigned GetRevisionNumber();

/// Return git description of the HEAD when building the library.
URHO3D_API const char* GetRevision();

/// Return baked-in compiler defines used when building the library.
URHO3D_API const char* GetCompilerDefines();

}
