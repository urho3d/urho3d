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
#else
#include <Urho3D/Urho3D.h>
#endif

namespace Urho3D
{
/**
*  \brief Information the version of Urho3D in use.
*
*  Represents the library's version as three levels: major revision
*  (increments with massive changes, additions, and enhancements),
*  minor revision (increments with backwards-compatible changes to the
*  major revision), and patchlevel (increments with fixes to the minor
*  revision).
*
*  \sa URHO3D_VERSION
*  \sa ::Urho3D::GetVersion
*/
typedef struct UrhoVersion
{
    ///major version
    unsigned char major;
    ///minor version
    unsigned char minor;
    ///patch version
    unsigned char patch;
}UrhoVersion;

/**
*  \brief Macro to determine Urho3D version program was compiled against.
*
*  This macro fills in a UrhoVersion structure with the version of the
*  library you compiled against. This is determined by what header the
*  compiler uses. Note that if you dynamically linked the library, you might
*  have a slightly newer or older version at runtime. That version can be
*  determined with ::Urho3D::GetVersion(), which, unlike URHO3D_VERSION(),
*  is not a macro.
*
*  \param x A pointer to a UrhoVersion struct to initialize.
*
*  \sa UrhoVersion
*  \sa ::Urho3D::GetVersion
*/
#define URHO3D_VERSION(x)                               \
{                                                                           \
    (x)->major = URHO3D_MAJOR_VERSION;         \
    (x)->minor = URHO3D_MINOR_VERSION;         \
    (x)->patch = URHO3D_PATCHLEVEL;                 \
}

///This macro turns the version numbers into a numeric value:
///    (1,2,3) -> (1203)
///This assumes that there will never be more than 100 patchlevels.
#define URHO3D_VERSIONNUM(X, Y, Z)          ((X)*1000 + (Y)*100 + (Z))

///This is the version number macro for the current URHO version.
#define URHO3D_COMPILEDVERSION             URHO3D_VERSIONNUM(URHO3D_MAJOR_VERSION, URHO3D_MINOR_VERSION, URHO3D_PATCHLEVEL)

///This macro will evaluate to true if compiled with URHO at least X.Y.Z.
#define URHO3D_VERSION_ATLEAST(X, Y, Z)    (URHO3D_COMPILEDVERSION >= URHO3D_VERSIONNUM(X, Y, Z))

/**
 *  \brief Get the version of Urho3D that is linked against your program.
 *
 *  If you are linking to Urho3D dynamically, then it is possible that the
 *  current version will be different than the version you compiled against.
 *  This function returns the current version, while URHO3D_VERSION() is a
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
