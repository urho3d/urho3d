Urho3D - cross-platform rendering and game engine
-------------------------------------------------

http://urho3d.googlecode.com

Licensed under the MIT license, see License.txt for details.


Credits
-------

Urho3D development, contributions and bugfixes by:
- Lasse Öörni (loorni@gmail.com)
- Wei Tjong Yao
- Colin Barrett
- Erik Beran
- Carlo Carollo
- Chris Friesen
- Alex Fuller
- Mika Heinonen
- Aster Jian
- Jason Kinzer
- Pete Leigh
- Paul Noome
- Vladimir Pobedinsky
- Miika Santala
- Firegorilla
- Magic.Lixin
- amadeus_osa
- primitivewaste
- skaiware

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
- AngelScript 2.27.0 (http://www.angelcode.com/angelscript/)
- Bullet 2.81 (http://www.bulletphysics.org/)
- FreeType 2.3.12 (http://www.freetype.org/)
- GLEW 1.9.0 (http://glew.sourceforge.net/)
- jo_jpeg 1.52 (http://www.jonolick.com/uploads/7/9/2/1/7921194/jo_jpeg.cpp)
- kNet (https://github.com/juj/kNet)
- libcpuid 0.2.0 (http://libcpuid.sourceforge.net/)
- Lua 5.1 (http://www.lua.org)
- MojoShader (http://icculus.org/mojoshader/)
- Open Asset Import Library (http://assimp.sourceforge.net/)
- pugixml 1.0 (http://pugixml.org/)
- Recast/Detour (http://code.google.com/p/recastnavigation/)
- SDL 2.0.0 (http://www.libsdl.org/)
- StanHull (http://codesuppository.blogspot.com/2006/03/
  john-ratcliffs-code-suppository-blog.html)
- stb_image 1.29 (http://nothings.org/)
- stb_vorbis 0.99996 (http://nothings.org/)
- tolua++ 1.0.93 (http://www.codenix.com/~tolua)

DXT / ETC1 / PVRTC decompression code based on the Squish library and the Oolong
Engine.

Jack and mushroom models from the realXtend project. (http://www.realxtend.org)

Ninja model and terrain / smoke / flare / status bar textures from OGRE.

Skybox cubemap from http://www.codemonsters.de.

BlueHighway font from Larabie Fonts.

Anonymous Pro font by Mark Simonson.

NinjaSnowWar sounds by Veli-Pekka Tätilä.


Documentation
-------------

Urho3D classes have been sparsely documented using Doxygen notation. To
generate documentation into the "Docs" subdirectory, open the Doxyfile in the
root directory with doxywizard and click "Run doxygen" from the "Run" tab.
Get Doxygen from http://www.doxygen.org

The documentation is also available online at http://cadaver.homeftp.net/urho3d


Building prerequisites
----------------------

Although all required third-party libraries are included as source code, there
are system-level dependencies that must be satisfied before Urho3D can be built
successfully:

- For Windows, the June 2010 DirectX SDK needs to be installed.

- For Linux, the following development packages need to be installed:
  libx11-dev, libxrandr-dev, libasound2-dev on Debian-based distros;
  libX11-devel, libXrandr-devel, alsa-lib-devel on RedHat-based distros.
  Also install the package libgl1-mesa-dev (Debian) or mesa-libGL-devel (RH)
  if your GPU driver does not include OpenGL headers & libs. Building as 32-bit on
  a 64-bit system requires installing also the 32-bit versions of the development
  libraries.

- For Raspberry Pi, the following development packages need to be installed:
  libraspberrypi0, libraspberrypi-dev, libasound2-dev on Raspbian;
  raspberrypi-vc-libs, raspberrypi-vc-libs-devel, alsa-lib-devel on Pidora.
  The first two packages which contain the Broadcom VideoCore IV libraries and
  development headers should normally come preinstalled.

- For Mac OS X, the Xcode developer tools package should include everything
  necessary.

- For Android, the Android SDK and Android NDK need to be installed. Optionally,
  also install Eclipse ADT plugin for building and deployment via Eclipse.

To run Urho3D, the minimum system requirements are:

- Windows: CPU with SSE instructions support, Windows XP or newer, DirectX 9.0c,
  GPU with Shader Model 2 support (Shader Model 3 recommended.)

- Linux & Mac OS X: CPU with SSE instructions support, GPU with OpenGL 2.0
  support, EXT_framebuffer_object and EXT_packed_depth_stencil extensions.

- Raspberry Pi: Model B revision 2.0 with at least 128 MB of 512 MB SDRAM
  allocated for GPU. OpenGL ES 2.0 capable GPU.

- Android: OS version 2.2 or newer, OpenGL ES 2.0 capable GPU.

- iOS: OpenGL ES 2.0 capable GPU.

SSE requirement can be eliminated by disabling the use of SSE instruction set,
see "Build options" below.


Desktop build process
---------------------

On desktop systems Urho3D uses CMake (http://www.cmake.org) to build. The
process has two steps:

1) Run CMake in the root directory with your preferred toolchain specified to
   generate the build files. You can use the provided batch files or shell
   scripts on the respective platform.
   
    Windows: cmake_vs2008.bat, cmake_vs2010.bat or cmake_vs2012.bat,
    Linux: cmake_gcc.sh or cmake_eclipse.sh,
    Mac OS X: cmake_gcc.sh or cmake_macosx.sh.

2) For Visual Studio, open Urho3D.sln and build the configuration(s) you like.
   
   For Eclipse, import the Eclipse's project generated by CMake into
   the workspace as a general project. Note that Eclipse requires CDT plugin to
   build C/C++ project.

   For GCC, execute make in the "Build" sub-directory (by default, cmake_gcc.sh
   specifies to make a Release build).

   For Xcode, open Urho3D.xcodeproj and build.

On Windows, using other compilers than Visual Studio is not officially
supported. MinGW may work (cmake -G "MinGW Makefiles"), but may lack required
DirectX headers. They can be copied to a MinGW installation from the following
package: http://www.libsdl.org/extras/win32/common/directx-devel.tar.gz

After the build is complete, the programs can be run from the Bin directory.
These include the Urho3D script host application, which can run application
scripts, the tools, and C++ sample applications if they have been enabled.

To run the Urho3D application from the Visual Studio debugger, set the Urho3D
project as the startup project and enter its relative path and filename into
Properties -> Debugging -> Command: ..\..\Bin\Urho3D.exe. Additionally, entering
-w into Debugging -> Command Arguments is highly recommended. This enables
startup in windowed mode: without it running into an exception or breakpoint
will be obnoxious as the mouse cursor will likely be hidden. To actually make
the Urho3D application do something useful, it must be supplied with the name of
the script file it should load and run. You can try for example the following 
arguments: Scripts/NinjaSnowWar.as -w

To run from Eclipse on Linux, locate and select the Urho3D executable in the
Project Explorer. From the menu, choose "Run Configurations" to create a new
launch configuration for "C/C++ Application". Switch to "Arguments" tab, specify
the argument required by Urho3D executable.

To run from Xcode on Mac OS X, edit the Product Scheme to set "Run" setting
to execute "Urho3D" in the "Info" tab. In the "Arguments" tab, specify the
arguments required by Urho3D executable. Ensure the check boxes are ticked on
the argument entries that you want to be active.


Android build process
---------------------

First, if you are building under Windows platform, copy Bin/Data and Bin/CoreData
directories to the Android/assets directory (you can use the provided batch file
CopyData.bat). This step is not necessary for non-Windows platform because the
build script uses symbolic links for platforms that support it.

Set the ANDROID_NDK environment variable to point to your Android NDK. On Windows,
ensure that make.exe from the Android NDK is included in the path and is executable
from the command line.

On Windows, execute cmake_android.bat then go to the Android directory and execute
the following commands. On OS X or Linux, execute cmake_gcc.sh (the ANDROID_NDK
environment variable distinguishes from a normal desktop build) then go to the
android-Build directory (which is a GCC out-of-source build) and execute the
following commands.

- android update project -p . -t 1 (only needed on the first time,
                                    replace '-t 1' with desired target-id)
- make -j8 (replace '-j8' with the number of logical CPU cores of the 
            host/build system)
- ant debug

After the commands finish successfully, the APK should have been generated to the
Android/bin directory, from where it can be installed on a device or an emulator.
The command "ant installd" can be used for this.

For a release build, use the "ant release" command instead of "ant debug" and
follow the Android SDK instructions on how to sign your APK properly.

By default the Android package for Urho3D is com.googlecode.urho3d. For a real
application you must replace this with your own package name. The Urho3D
activity subclasses the SDLActivity from org.libsdl.app package, whose name
(or the JNI code from SDL library) does not have to be changed.

Note that the native code is built by default for armeabi-v7a ABI. To make your
program compatible also with old Android devices, build also an armeabi version
by executing the CMake batch file again with the parameter -DANDROID_ABI=armeabi
added, then execute make again in the Android directory on Windows or android-Build
directory on Mac/Linux.

You can also build and deploy using Eclipse IDE with ADT plugin. To do that, after
setting the ANDROID_NDK environment variable then run cmake_eclipse.sh. Import
"Existing Android Code into Workspace" from the CMake generated Eclipse's project
found in the android-Build directory. Switch Eclipse IDE to use Java Perspective.
Update project properties to choose the desired Android API target and that's it.
Just choose "Run" to let ADT automatically build and deploy the application to
Android (virtual) device.


iOS build process
-----------------

Run cmake_ios.sh. This generates an Xcode project named Urho3D.xcodeproj.

Open the Xcode project and check the properties for the Urho3D project (topmost
in the Project Navigator.) In Architectures -> Base SDK, choose your iOS SDK
(CMake would automatically select latest iOS when generating the Xcode project).
In Code Signing, enter your developer identity as necessary.

The Urho3D target will actually build the application bundle and copy resources
from Bin/Data and Bin/CoreData directories. Edit its build scheme to choose
debug or release mode.

To run from Xcode on iPhone/iPad Simulator, edit the Product Scheme to set "Run"
destination setting to "iPhone Simulator" or "iPad Simulator", and executable
to "Urho3D.app".


Raspberry Pi build process
--------------------------

For native build on Raspberry Pi itself, use the similar process for Linux Desktop
build described above.

For cross-compiling build on another build/host machine, set the RASPI_TOOL
environment variable to point to your Raspberry Pi Cross-Compiling tool where all
the arm-linux-gnueabihf-* executables are located. You can setup the tool using
crosstool-NG (http://crosstool-ng.org/) or just download one from
https://github.com/raspberrypi/tools. The RASPI_TOOL environment variable tells
build script to generate additional build directory for cross-compiling.

Run cmake_gcc.sh then go to the raspi-Build directory and proceed to execute make.
After the build is complete, the ARM executables can be found in Bin-CC directory. 

You can also build, deploy, run/debug (as C/C++ Remote Application) using Eclipse
IDE, if you run cmake_eclipse.sh to generate the project file. Import the CMake
generated Eclipse project in the raspi-Build directory into Eclipse's workspace.
Build the project as usual. Use the SCP_TO_TARGET build option to automatically
deploy the ARM executables to target Raspberry Pi as part of every project build
or configure Eclipse to perform a "download to target path" in the Run/Debug
configuration for C/C++ Remote Application. Either way, you have to configure the
Run/Debug configuration how to reach your target Raspberry Pi.


Desktop 64bit build
-------------------

Currently CMake build configuration has been set to compile Urho3D as 32bit by
default. To enable 64bit build, run the provided cmake_xxxx.bat or cmake_xxxx.sh
by passing the option "-DENABLE_64BIT=1" explicitly. For Visual Studio on Windows
platform, this option also overrides CMake to use a 64bit solution generator.


Library build
-------------

CMake build configuration has been scripted to generate Urho3D executable as the
default build target. This default target builds the Urho3D script host application
(a tool to execute AngelScript and Lua script). To change it to generate an Urho3D
static or shared (dynamic) library build target instead, specify the build option
"-DURHO3D_BUILD_TYPE=STATIC" or "-DURHO3D_BUILD_TYPE=SHARED", respectively. When
this option is set, the other build options to generate sample and tool targets are
ignored. Due to the way the Urho3D project is being structured and the potential
conflict of different visibility (export) attribute settings, when building the
Urho3D library target then no other runtime targets can be built at the same time.    

Refer to "Using Urho3D as external library" on how to setup your own project to use
Urho3D as external library.


Compiling Direct3D shaders
--------------------------

When building with the Windows 8 SDK, copy d3dcompiler_46.dll from
C:/Program Files (x86)/Windows Kits/8.0/bin/x86 to Urho3D Bin directory so that
the ShaderCompiler program will run correctly.

To make the Urho3D examples start faster on Windows & Direct3D9 mode, run
CompileAllShaders.bat from the Bin directory first.

Note that you can also force an OpenGL mode build on Windows by using the CMake 
option in the table below; OpenGL does not need a separate shader compilation 
step or utility.


Build options     
-------------

A number of build options can be defined explicitly when invoking the above
cmake_xxxx batch files or shell scripts.

|----------------------|-------------------------------------------------------|
|Defines               |Build Options                                          |
|----------------------|-------------------------------------------------------|
|-DENABLE_64BIT=1      |to enable 64bit build                                  |
|-DENABLE_LUA=1        |to enable additional Lua scripting support             |
|-DENABLE_SAMPLES=1    |to build the C++ sample applications                   |
|-DENABLE_TOOLS=1      |to build the tools (only useful for Raspberry Pi build |
|                      | because this option is already enabled by default for |
|                      | other Desktop platforms)                              |
|-DENABLE_SSE=0        |to disable SSE instruction set                         |
|-DENABLE_MINIDUMPS=0  |to disable minidumps on crash (VS only)                |
|-DUSE_OPENGL=1        |to use OpenGL instead of Direct3D (only useful for VS  |
|                      | on Windows platform because this option is enabled by |
|                      | default for other platforms)                          | 
|-DUSE_MKLINK=1        |to use mklink command to create symbolic links (Windows|
|                      |  Vista and above only)                                |
|-DSCP_TO_TARGET=      |to automatically scp executables to target system (only|
|  usr@tgt:remote-loc  | applicable for cross compiling Raspberry Pi on a      |
|                      | build/host machine), SSH digital key must be setup    |
|                      | first for this to work                                |
|-DCMAKE_BUILD_TYPE=   |to tell CMake which build configuration to be          |
|  Release/Debug/      | generated, default is Release (only applicable for    |
|  RelWithDebInfo      | cmake_gcc.sh and cmake_eclipse.sh)                    |
|-DURHO3D_BUILD_TYPE=  |to tell CMake which Urho3D target to be built, default |
|  EXE/STATIC/SHARED   | is EXE (Urho3D script host)                           |          
|----------------------|-------------------------------------------------------|


History
-------

V1.23   - UI editing support in the editor.
        - Undo/redo in the editor.
        - Recast/Detour library integration for navigation mesh generation and
          pathfinding.
        - Open Asset Import Library update, enables FBX file support.
        - "Is Enabled" attribute in scene nodes and components for an uniform
          mechanism to temporarily disable unneeded audiovisual, physics or
          logic objects.
        - Script object public variables editing and serialization.
        - New components: Text3D and Sprite.
        - UI library functionality improvements.
        - sRGB texture and framebuffer support.
        - Switched to GLEW library for OpenGL extension handling.
        - Vegetation and lightmapping example shaders.
        - Engine configuration through a parameter map.
        - Lots of refactoring, code cleanup and bugfixes.

V1.22   - Configurable render path replaces hardcoded forward/prepass/deferred
          modes. Render path system also used for postprocessing now.
        - Threaded task priorities; long-running tasks (more than one frame) can
          coexist with the time-critical tasks.
        - Possibility to use also RGB normal maps.
        - CustomGeometry component, which allows geometry to be defined
          similarly to OpenGL immediate mode.
        - Elapsed time shader parameter for material animation.
        - Cubic environment mapping example shaders.
        - Separate physics collision start & end events.
        - Visual Studio 2012, Eclipse & Xcode build support.
        - Many bugfixes, including iOS 6 orientation & shadow mapping bugfixes,
          skinning on some Android devices.

V1.21   - Bugfixes and code cleanup.
        - External window support (experimental.)
        - UI elements refactored to use attributes for serialization.
        - Animation state editing and animation trigger events.
        - Scene update time scale can be modified.
        - Improved the delayed method call system.

V1.2    - Android and iOS support.
        - Decal rendering.
        - Terrain rendering.
        - Joystick input support.
        - Use SDL library for windowing and input on all platforms.
        - KTX and PVR image loading (for ETC1 & PVRTC compressed textures.)
        - Removed need for shader preprocessing; reorganized shaders to be more
          friendly to base custom shaders on.
        - Inbuilt geometry shapes in the editor.

V1.16   - Switched to Bullet physics library.
        - More physics constraint types.
        - Rendering and networking performance optimizations.
        - Use Squish library to implement software DXT decompression when not
          supported in hardware.

V1.15   - New deferred rendering pipeline.
        - Unicode support.
        - Live resource reloading in the editor (Windows only so far.)
        - More accurate frame timing.
        - Bugfixes to physics jittering and FBO performance issue on Linux.

V1.14   - Object (partial scene) load/save.
        - Post-processing.
        - Switched to pugixml library, scene load/save optimizations.
        - Bugfixes to rendertexture views and component attributes.

V1.13   - Task-based multithreading.
        - Vertex lighting option.
        - Forward and light pre-pass rendering pipelines.

V1.12   - Manipulator gizmo and multi-editing in the editor.
        - Switched to forward rendering exclusively, which is optimized to do
          more work in the vertex shader.
        - Zone system refactoring. Objects check the zone they belong to for
          per-zone light masking, ambient light and fog settings.
        - Scripting API fixes and improvements.

V1.11   - Bugfixes and performance optimizations.
        - Added GraphicsTest example from V1.0 (now called TestSceneOld.)
        - Added fallback mode, which is used if multiple render targets or
          hardware shadow maps are not available.

V1.1    - Object and scene model refactoring.
        - Automatic serialization of scene objects via attributes.
        - Added OpenGL and cross-platform support.
        - Switched to kNet library for networking.

V1.0    - Original release.