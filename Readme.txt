Urho3D - a Win32/Direct3D9 rendering and game engine
----------------------------------------------------

http://urho3d.googlecode.com

Licensed under the MIT license, see License.txt for details.


Credits
-------

Urho3D engine & example code by Lasse Öörni (loorni@gmail.com)

Urho3D is greatly inspired by OGRE (http://www.ogre3d.org) and Horde3D
(http://www.horde3d.org). Additional inspiration & research used:
- Rectangle packing by Jukka Jylänki (clb)
  http://clb.demon.fi/projects/rectangle-bin-packing
- Tangent generation from Terathon
  http://www.terathon.com/code/tangent.html
- Fast, Minimum Storage Ray/Triangle Intersection by Möller & Trumbore
  http://www.graphics.cornell.edu/pubs/1997/MT97.pdf
- Linear-Speed Vertex Cache Optimisation by Tom Forsyth
  http://home.comcast.net/~tom_forsyth/papers/fast_vert_cache_opt.html
- Software rasterization of triangles based on Chris Hecker's
  Perspective Texture Mapping series in the Game Developer magazine
  http://chrishecker.com/Miscellaneous_Technical_Articles
- Networked Physics by Glenn Fiedler
  http://gafferongames.com/game-physics/networked-physics/
- Euler Angle Formulas by David Eberly
  http://www.geometrictools.com/Documentation/EulerAngles.pdf

Urho3D uses the following third-party libraries:
- AngelScript (2.20.2)
- ENet (1.3.0)
- FreeType (2.3.12)
- Open Asset Import Library (2.0.863)
- Open Dynamics Engine (svn rev 1770)
- StanHull
- stb_image (1.29)
- stb_vorbis (0.99996)
- TinyXML (2.6.1)

Ninja model, BlueHighway font and smoke/flare/status bar textures are from OGRE.

Jack and mushroom models are from the realXtend project. (http://www.realxtend.org)

NinjaSnowWar sounds by Veli-Pekka Tätilä.


Documentation
-------------

Urho3D classes have been sparsely documented using Doxygen notation. To
generate documentation into the "Docs" subdirectory, open the Doxyfile in the
root directory with doxywizard and click "Run doxygen" from the "Run" tab. 
Get Doxygen from http://www.doxygen.org


Building
--------

Urho3D uses cmake (http://www.cmake.org) to build. The process has two steps:

1) Run cmake in the root directory with your preferred toolchain specified to
generate the build files. Visual Studio 2008/2010 and MinGW have been tested.
You can use the batch files provided (cmake_vs2008.bat, cmake_vs2010.bat and
cmake_gcc.bat.)

2) For Visual Studio, open Urho3D.sln and build the configuration(s) you like.
For MinGW, execute make (by default, cmake_gcc.bat specifies to make a Release
build.)

The build process will also compile models and shaders from the Source_Asset
directory into Bin/Data/Models & Bin/Data/Shaders. Shader compilation requires
fxc.exe (from the DirectX SDK) to be available through the system PATH. Note
that the debug executables of tools will not have the _d postfix, to allow the
asset build scripts to work in both debug & release builds.

After the build is complete, the programs can be run from the Bin directory.

To run Urho3D.exe from the Visual Studio debugger, set it as a startup project
and enter its relative path and filename into Debugging -> Command: 
..\Bin\Urho3D.exe or ..\Bin\Urho3D_d.exe. Additionally, entering -w into 
Debugging -> Command Arguments is highly recommended. This enables startup in 
windowed mode: without it running into an exception or breakpoint will be 
obnoxious as the mouse cursor will most probably be hidden.

Note: some SM2.0 shaders in Urho3D reach exactly the arithmetic instruction
count limit. The fxc.exe in newer DirectX SDK's may fail to compile them. At
least the February 2010 SDK is known to work.
