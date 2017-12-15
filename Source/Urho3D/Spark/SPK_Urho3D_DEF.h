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

#ifndef H_SPK_URHO3D_DEF
#define H_SPK_URHO3D_DEF

#include "../Core/Context.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"


// for windows platform only
#if defined(WIN32) || defined(_WIN32)
#ifdef SPK_URHO_EXPORT
#define SPK_URHO_PREFIX __declspec(dllexport)
#elif defined(SPK_IMPORT) || defined(SPK_URHO_IMPORT)
#define SPK_URHO_PREFIX __declspec(dllimport)
#else
#define SPK_URHO_PREFIX
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4275) // disables the warning about exporting DLL classes children of non DLL classes
#endif

#else
#define SPK_URHO_PREFIX
#endif

namespace SPK {

class Vector3D;
class Color;

namespace URHO {


    /**
    * @brief Helper class to register Urho3D context
    * */
    class SPK_URHO_PREFIX Urho3DContext
    {
    public :

        static Urho3DContext& get();

        void registerUrhoContext(Urho3D::Context* context);
        Urho3D::Context* getUrhoContext();

    private :

        Urho3D::Context* urhoContext;

        Urho3DContext();
        Urho3DContext(const Urho3DContext&) {}
        Urho3DContext& operator=(const Urho3DContext&);
    };



    //////////////////////////
    // Conversion functions //
    //////////////////////////

    /**
    * @brief Converts a SPARK Vector3D to an Urho3D Vector3
    * @param v : the Vector3D to convert
    * @return the Urho3D Vector3
    */
    inline Urho3D::Vector3 spk2urho(const Vector3D& v);

    /**
    * @brief Converts an Urho3D Vector3 to a SPARK Vector3D
    * @param v : the Vector3 to convert
    * @return the SPARK Vector3D
    */
    inline SPK::Vector3D urho2spk(const Urho3D::Vector3& v);

    /**
    * @brief Gets an Urho3D Color from rgba values
    * @param a : the alpha value
    * @param r : the red value
    * @param g : the green value
    * @param b : the blue value
    * @return the Urho3D SColor
    */
    inline Urho3D::Color spk2urho(unsigned char a, unsigned char  r, unsigned char  g, unsigned char  b);


    /**
    * @brief Gets an Urho3D Color from SPK::Color values
    * @param a : the SPK::Color value
    * @return the Urho3D SColor
    */
    inline const Urho3D::Color spk2urho(SPK::Color c);


}}

#endif
