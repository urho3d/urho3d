Urho3D - Direct3D9 / OpenGL rendering and game engine
-----------------------------------------------------

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
- Red Black Trees by Julienne Walker 
  http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx
- Comparison of several sorting algorithms by Juha Nieminen 
  http://warp.povusers.org/SortComparison/
- NVIDIA FXAA II for Consoles by Timothy Lottes
  http://timothylottes.blogspot.com/2011/04/nvidia-fxaa-ii-for-console.html

Urho3D uses the following third-party libraries:
- AngelScript 2.21.0 WIP (http://www.angelcode.com/angelscript/)
- ENet 1.3.1 (http://enet.bespin.org/)
- FreeType 2.3.12 (http://www.freetype.org/)
- GLee 5.4 (http://elf-stone.com/)
- GLFW 3.0 WIP (http://www.glfw.org/)
- Open Asset Import Library 2.0.863 (http://assimp.sourceforge.net/)
- Open Dynamics Engine, svn rev 1806 (http://www.ode.org/)
- PortAudio V19 (http://www.portaudio.com/)
- StanHull (http://codesuppository.blogspot.com/2006/03/
  john-ratcliffs-code-suppository-blog.html)
- stb_image 1.29 (http://nothings.org/)
- stb_vorbis 0.99996 (http://nothings.org/)
- TinyXML 2.6.1 (http://www.grinninglizard.com/tinyxml/)

Jack and mushroom models from the realXtend project. (http://www.realxtend.org)

Ninja model and smoke/flare/status bar textures from OGRE.

BlueHighway font from Larabie Fonts.

Anonymous Pro font by Mark Simonson.

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
generate the build files. You can use the batch files or shell scripts provided.
Use cmake_vs2008.bat, cmake_vs2010.bat or cmake_mingw.bat on Windows, and
cmake_gcc.sh on Linux and Mac OS X.

2) For Visual Studio, open Urho3D.sln and build the configuration(s) you like.
For gcc, execute make (by default, cmake_mingw.bat or cmake_gcc.sh specify to 
make a Release build.)

The build process will also compile models and shaders from the Source_Asset
directory into Bin/Data/Models & Bin/Data/Shaders. On Windows & Direct3D9,
shader compilation requires the D3DX library from the DirectX runtime or SDK to
be available.

After the build is complete, the programs can be run from the Bin directory.

To run Urho3D from the Visual Studio debugger, set it as a startup project and
enter its relative path and filename into Properties -> Debugging -> Command:
..\Bin\Urho3D.exe or ..\Bin\Urho3D_d.exe. Additionally, entering -w into
Debugging -> Command Arguments is highly recommended. This enables startup in
windowed mode: without it running into an exception or breakpoint will be
obnoxious as the mouse cursor will most probably be hidden.

To actually make Urho3D.exe do something useful, it must be supplied with the
name of the script file it should load and run. You can try for example the
following arguments: Scripts/TestScene.as -w

Note: some Direct3D9 SM2.0 shaders in Urho3D reach exactly the arithmetic 
instruction count limit. Some versions of the HLSL compiler may fail to compile
them. At least the February 2010 SDK is known to work.
