SLikeNet™ 0.1.2
===============
Copyright © 2016-2018 SLikeSoft™ UG (haftungsbeschränkt)

Part of the documentation in this readme file was taken from RakNet 4.082
readme files. These sections are marked with [partially copied from RakNet].
Please see licenses/RakNet license.txt for the underlying license and related
copyright.


The latest version and information are available at https://www.slikenet.com/



Table of Contents
   0.      Quickstart
   1.      What is SLikeNet?
   1.1     History of SLikeNet
   1.2     Version scheme and deprecation process
   1.2.1   Pre 1.0 releases
   1.2.2   Alpha releases
   1.2.3   Beta releases
   1.2.4   1.x.y releases
   1.2.5   2.x.y and following releases
   1.2.6   Client / Server compatibility
   1.2.7   API deprecation and dropping support for 3rd party versions
   1.3     Changes between RakNet (4.081/4.082) and SLikeNet
   2.      System/Dependency requirements
   2.1     Limitations on supported OSs, build environments, and 3rd party
           libraries
   2.2     Compiler support
   2.3     OS support
   2.4     3rd party libraries/dependencies
   2.4.1   Boost
   2.4.2   BZip2
   2.4.3   FMOD Ex
   2.4.4   Independent JPEG Group's free JPEG software
   2.4.5   Irrlicht Engine
   2.4.6   irrKlang
   2.4.7   Jansson
   2.4.8   libcatid
   2.4.9   Microsoft DirectX SDK / Microsoft Windows SDK
   2.4.10  MiniUPnP client
   2.4.11  MySQL
   2.4.12  NVIDIA Cg Toolkit
   2.4.13  NVIDIA Compress YCoCg-DXT
   2.4.14  Ogre3D
   2.4.15  OpenSSL
   2.4.16  PortAudio
   2.4.17  PostgreSQL
   2.4.18  Autodesk Scaleform GFx
   2.4.19  speex
   2.4.20  SQLite
   2.4.21  Steamworks SDK
   2.4.22  SWIG
   2.4.23  Xdelta
   2.4.24  XMLParser library
   3.      Getting Started
   3.1     Downloading SLikeNet
   3.1.1   Download from the webpage
   3.1.1.1 Verifying the file integrity
   3.1.1.2 Validating the download package
   3.1.2   Downloading via SVN
   3.1.3   Downloading via GIT
   3.2     Using SLikeNet on Windows
   3.2.1   Using prebuilt SLikeNet libraries with Microsoft Visual Studio
   3.2.2   Building SLikeNet yourself with Microsoft Visual Studio
   3.2.3   Provided default libraries
   3.3     Using SLikeNet with Linux and OSX
   3.3.1   Building SLikeNet
   3.4     RakNet compatibility mode
   3.4.1   Migrating from RakNet to SLikeNet
   3.4.2   Building RakNet compatibility mode yourself
   3.4.3   In-place replacement of RakNet
   3.5     Development notes on differences between RakNet and SLikeNet
   3.5.1   General notes
   3.5.2   Retail configuration
   3.5.3   OSX usage of @rpath for install_name
   3.5.4   PacketLogger FormatLine() changes
   3.5.5   CMake install destinations for non-Windows platforms
   3.6     Configuring SLikeNet
   3.6.1   Security relevant settings
   4.      Dependent Extensions
   4.1     AutopatcherMySQLRepository
   4.2     AutopatcherPostgreRepository
   4.3     BspCollision
   4.4     DXTCompressor
   4.5     IrrlichtDemo
   4.6     MySQLInterface
   4.7     Ogre3DInterpDemo
   4.8     Matrices
   4.9     PostgreSQLInterface
   4.10    Rackspace
   4.11    SQLite3Plugin / SQLite3ClientLogger / SQLite3ServerLogger
   4.12    Swig / DLL_Swig
   5.      Samples
   5.1     AutopatcherClient
   5.2     AutopatcherClientGFx3.0
   5.3     AutopatcherClientRestarter
   5.4     AutopatcherClient_SelfScaling
   5.5     AutopatcherServer
   5.6     AutoPatcherServer_MySQL
   5.7     AutopatcherServer_SelfScaling
   5.8     ChatExample
   5.9     CloudClient
   5.10    CloudServer
   5.11    CommandConsoleClient
   5.12    CommandConsoleServer
   5.13    ComprehensivePCGame
   5.14    CrashReporter
   5.15    DirectoryDeltaTransfer
   5.16    Encryption
   5.17    FCM2Host
   5.18    FCM2Host_Simultaneous
   5.19    FCM2VerifiedJoinSimultaneous
   5.20    FullyConnectedMesh
   5.21    iOS ChatClient
   5.22    LANServerDiscovery
   5.23    Lobby2Server_PGSQL
   5.24    MessageFilter
   5.25    NATCompleteClient
   5.26    NATCompleteServer
   5.27    PacketLogger
   5.28    PHPDirectoryServer2
   5.29    Ping
   5.30    RackspaceConsole
   5.31    RakVoice
   5.32    RakVoiceDSound
   5.33    RakVoiceFMOD / RakVoiceFMODAsDLL / RakVoiceFMODUsingDLL
   5.34    ReadyEvent
   5.35    ReplicaManager3
   5.36    RoomsPlugin
   5.37    Router2
   5.38    RPC3
   5.39    RPC4
   5.40    SendEmail
   5.41    SteamLobby
   5.42    TeamManager
   5.43    Timestamping
   5.44    TwoWayAuthentication
   5.45    UDP Forwarder
   5.46    WinPhone8
   6.      Help and Support
   6.1     Documenation
   6.2     Contact Information and Support
   7.      A word on licensing
   7.1     SLikeNet licensing (core and extended)
   7.2     Licensed Code
   7.2.1    (core) RakNet
   7.2.2    (core) DR_SHA1.cpp/.h (SHA-1 algorithm - version 2.1)
   7.2.3    (core) Rand.cpp (Mersenne Twister random number generator MT19937)
   7.2.4    (core) KBhit.h
   7.2.5    (core) FindBoost.cmake
   7.2.6    (DependentExtension/Autopatcher) ApplyPatch.cpp, CreatePatch.cpp
   7.2.7    (DependentExtension/DXTCompressor) OpenGLWindow.hpp
   7.2.8    (DependentExtension/IrrlichtDemo) FindIrrlicht.cmake,
            FindIrrKlang.cmake
   7.2.9    (DependentExtension/IrrlichtDemo) CDemo.cpp/.h, CMainMenu.cpp/.h,
            main.cpp
   7.2.10   (DependentExtension/speex related) FindSpeex.cmake,
            FindSpeexDSP.cmake
   7.2.11   (DependentExtension/Swig) arrays_csharp.i
   7.2.12   (Samples/nacl_sdk) httpd.py
   7.2.13   (Samples/Ogre3D related) FindOGRE.cmake, FindOIS.cmake,
            FindPkgMacros.cmake, PreprocessorUtils.cmake
   7.2.14   (Samples/Ogre3D related) BspCollision.cpp
   8.       Donations
   9.       Thanks / Acknowledgments
   10.      Trademark Notes / Affiliation Statement



0. Quickstart

If you want to get started quickly simply follow these directions:

Windows™: see chapter 3.2.1 and use the prebuilt libraries
Linux®/OSX: see chapter 3.3.1
Migrating from RakNet to SLikeNet: see chapter 3.4.1

For quick instructions to comply with license requirements see:
licenses/_quick_licensing_slikenet_core.txt and
licenses/_quick_licensing_slikenet_extended.txt


1. What is SLikeNet?

SLikeNet™ is an Open Source/Free Software cross-platform network engine written
in C++ and specifically designed for games (and applications which have
comparable requirements on a network engine like games) building upon the
discontinued RakNet network engine which had more than 13 years of active
development. SLikeNet currently supports Windows, Linux and Mac with limited
support for iPhone®, Android™, Windows Phone™ 8, and Windows Store 8.
SLikeNet is not a simple rebranding of RakNet, but rather incorporates already
in its initial version several bug- and security fixes as well as changes to
bring the engine back on track with recent compiler and language changes.

1.1 History of SLikeNet
Like many teenagers in the 90th and in the early years of the 21st century the
developers have been quite into the area of computer games. One of them
actually took his hobby over to the professional life and started a career in
the games industry. Of special interest for him was the area of
multiplayer/network engines which he also took as the topic for his diploma
thesis.
Unfortunately, even after a decade in the industry and despite his passion for
that area, he didn't get the chance to directly work on a multiplayer
integration and could only invest his own spare time in this area.
2014 finally came the opportunity to change that when RakNet
(http://www.jenkinssoftware.com/), which was developed for over 13 years by
Kevin Jenkins / Jenkins Software LLC, got acquired by Oculus VR, LLC. and was
put under an open source license.
Initially the developers thought about mainly becoming an active member of the
community. However, it turned out that since GitHub® wasn't opened up, no
organized community established itself and the idea of the development of
RakNet being taken over by the community didn't come true.
While there were quite a few talented developers who provided patches on
GitHub and helped with providing support, there didn't seem to be any endeavor
to get an organizational structure around the continuous development of RakNet.
Hence, to the developers of SLikeNet the question arose how they could actually
help out here and what would be the best way to ensure that RakNet will
continue to thrive for several years to come. The conclusion was to found a
company (SLikeSoft™) and continue the work RakNet left behind under a fresh
name. That should provide a strong fundament and basis for the community to
rely on that their ideas, bugfixes, and features won't get lost but rather will
be integrated/handled in an organized manner.

1.2 Version scheme and deprecation process
SLikeNet is using the Semantic Versioning (version 2.0.0) authored by Tom
Preston-Werner. See http://semver.org/ for details.

1.2.1 Pre 1.0 releases
The initial versions on the way towards the 1.0.0 release will use the version
number 0.x.y to reflect the current (early) development stage of SLikeNet.
However, since SLikeNet is heavily based on the very well tested RakNet
library, we consider already these early versions way more stable than what you
would normally expect from a library with such a version number.
Furthermore, since our aim for SLikeNet 1.0.0 is to keep ABI/API/Protocol
compatibility with RakNet 4.081/4.082, we consider the API/ABI/Protocol of the
0.x.y releases already stable and do plan to change them only in order to fix
(undesired/unintended) API/ABI/Protocol incompatibility with RakNet which might
have slipped in during development.
Hence, in contrast to what the Semantic Versioning 2.0.0 permits, we are
considering the 0.1.0 API being stable, already.

1.2.2 Alpha releases
Starting with 1.0.0, for each new release we will go through a >= 2-weeks alpha
release period. During this period we will only implement bugfixes which are
considered safe or are fixes for regressions. Anything else will be postponed
and scheduled for a following version. If significant changes need to be made
for the released alpha version, we will release another alpha version and
restart the 2-weeks test period.
The version numbering for alpha releases will be x.y.z-alpha.d where d begins
with 1 and is incremented by 1 for each successive alpha release of the same
version.

1.2.3 Beta releases
After the alpha version passed without major rework and the risk assessment
concurred, we will release a beta version of the new version which starts the
beta test phase of at least 2 weeks. During that period we will only fix
regressions introduced in the new versions. Anything else will be postponed and
scheduled for a following version. If there is a regression fix during the beta
phase, we will release a new beta version and restart the 2 week test period.
The version numbering will be x.y.z-beta.d where d begins with 1 and is incremented
by 1 for each successive beta release of the same version.

1.2.4 1.x.y releases
The 1.x.y releases will ensure API, ABI, and protocol compatibility with RakNet
4.081/4.082. This way we allow everybody currently using RakNet in their
product to perform a simple in-place test of SLikeNet with as little work as
possible. In principle it will allow you to test SLikeNet by simply replacing
the RakNet DLLs without even having to recompile your game/application. If you
linked RakNet statically, all you need to do is to link against the SLikeNet
library. No other changes should be required. You can even run a client built
with RakNet 4.082 and connect it to a SLikeNet 1.x.y server (or vice versa).

1.2.5 2.x.y and following releases
2.0.0 will be the first release which breaks backwards compatibility with
RakNet. This allows us to integrate performance improvements and new features
which would otherwise be impossible to realize with keeping backwards
compatibility with RakNet. The server as well as the connecting clients will
require both at least running SLikeNet 2.0.0 in order to work together.

1.2.6 Client / Server compatibility
Any x.y.z version will always be compatible with any other x.y.z version as
long as x is the same (or differs by only 1 digit and is at least 2). For
instance: Running a server on 3.0.0 allows clients running 2.x.y up to 4.x.y to
connect to that server. From the other point of view: A client running version
4.0.0 can connect to any server running 3.x.y up to 5.x.y.

1.2.7 API deprecation and dropping support for 3rd party versions
From time to time we need to deprecate APIs/functions/classes/etc. In some
cases this is done in order to keep the network engine maintainable, in other
cases we might have to deprecate APIs for security reasons. For versions
>= 2.0.0 we will make sure that any API which is deprecated is still available
for the next major release (i.e. if we deprecate a version in 2.x.y, it will
still be available for all 3.x.y releases but will be dropped in 4.0.0). The
same goes for the deprecation of old 3rd party libraries.
There are however a couple of cases where we might deviate from this procedure.
Examples could be that security fixes require us to deprecate an API or 3rd
party library already earlier or we might deprecate 3rd party library versions
which are incompatible with new compilers. To comply with the Semantic
Versioning 2.0.0 we will announce the deprecation of the API/3rd-party library
version at least in a sub version of the current major release branch and then
remove it in the following major release.
For instance, if we learn that there's a security flaw in SLikeNet 2.0.5 which
requires a change to the API we mark the problematic function deprecated and
release 2.1.0. In the following 3.0.0 release the function will then be
removed.

1.3 Changes between RakNet (4.081/4.082) and SLikeNet
RakNet 4.081 was the final release of RakNet with 4.082 having been in
development. SLikeNet is based on the sourcecode of RakNet 4.082 and aims for
API, ABI, and protocol compatibility with RakNet 4.081/4.082.
That way it's possible to use (and evaluate) SLikeNet as an in-place
replacement for RakNet.

The major differences/improvements of SLikeNet over RakNet are:
- added support for the latest compilers and dropped support for older
  compilers
- added support for newer versions of 3rd-party libraries
- security enhancements (f.e. by fixing buffer overflows, using security
  enhanced CRT functions, replacing obsolete less secure CRT functions with
  up-to-date ones, etc.)
- replaced Multi-Byte Character support with Unicode support
- warning free compiling/linking (i.e. warnings RakNet triggered when building
  the source were resolved)
- easier way to get started with SLikeNet by providing precompiled libraries
  and easily loadable/upgradable solution/project files for recent Visual
  Studio versions
- extended documentation
- countless bugfixes and improvements (see changelog.txt for details)

There are also a couple of restrictions SLikeNet has when comparing its feature
set with RakNet. Some of them are going to be dealt with in later versions,
some of them however are not planned to be resolved. If any of the missing
features/support is causing you trouble to try out SLikeNet, drop us a note
(see chapter 6) and we'll see whether we find a solution for you.
There are mainly the following reasons behind this decision:
a) license restrictions prevent us to provide the same support RakNet used to
provide (marked with "licensing" in the following list)
b) we intentionally dropped support, so to reduce the maintenance work and be
able to make use of new language and 3rd-party-library features (marked with
"deprecated" in the following list)
c) especially for the first versions we had to prioritize the work and had to
postpone work on certain parts but are planning to do so in later versions
(marked with "later in the following list)

The following list presents the known restrictions:
- dropped support for old/outdated libraries (deprecated)
- dropped support for old compilers (deprecated)
- removed the following source code files/directories:
	- DependentExtensions/DXTCompressor/External/include/*.h (deprecated)
	- DependentExtensions/DXTCompressor/External/include/GL/glext.h
          (deprecated)
	- DependentExtensions/IrrlichtDemo/irrKlang-1.1.3/*.* (licensing)
	- DependentExtensions/IrrlichtDemo/irrKlang.dll (licensing)
	- Samples/Marmalade (licensing)
	- Samples/AutopatcherClientGFx3.0/GFxPlayerTinyD3D9.cpp (licensing)
	- Samples/Lobby2ClientGFx3.0/GFxPlayerTinyD3D9.cpp (licensing)
	- Samples/RoomsBrowserGFx3/GFxPlayerTinyD3D9.cpp (licensing)
- dropped support for the following platforms (licensing):
	- Xbox 360®
	- PlayStation® Vita
	- Playstation 3
- limited support for iOS, Android, Windows Phone 8, Windows Store 8 (later)
- limited support for Samples and Tests (later)
- limited support for RakVoiceFMOD (later)
- limited support for SWIG and the C# interface (later)
- missing support for server related features like Lobby3, MasterServer,
  MasterServer2, etc. (later)



2. System/Dependency requirements

2.1 Limitations on supported OSs, build environments, and 3rd party libraries
SLikeNet supports a brought variety of different compilers, OSs, build tools,
and 3rd part libraries.
We are aiming to provide a stable environment for our users to have SLikeNet
build with the supported compilers/build tools/3rd party libraries and run on
all the supported OSs.
Obviously it's unfeasible to test each release with all possible combinations
of compilers(-versions), on all OSs, and with all versions of the 3rd party
dependencies.
Therefore, we decided to restrict the full support as follows:

Compiler/Build tools:
We only provide full support for the latest patch release of a compiler. That
means that for the Visual Studio 2013 compiler we only support VS 2013 Update 5
(but not Update 1 to Update 4 and also not the unpatched Visual Studio 2013
compiler).

OSs:
We test SLikeNet on the fully patched earliest and on the latest version of the
supported OS. Full support is only provided for the operation systems listed
below. For instance we support Microsoft™ Windows XP but only if Service Pack 3
is installed (and all available OS patches are applied). Windows XP without any
service pack or only SP1/SP1a/SP2 installed is unsupported.

3rd party libraries:
3rd party libraries are tested with the earliest supported version and the
latest supported one. Furthermore, we are only supporting the latest patch
release of a 3rd-party library. As an example this means that we support Boost
1.46.1 but not Boost 1.46.0.

By restricting the support we certainly don't mean that SLikeNet won't work
with a compiler version, 3rd party library version or OS version which is not
listed here. It simply means that we haven't tested that combination and you
might run into issues or warnings might show up during the build. SLikeNet
however might still work just fine.
If your preferred (build) environment is not listed here and you'd like to get
full support for it, please contact us (see chapter 6) so we can see whether we
can add full support for your combination.
If a compiler/OS/3rd party is listed as supported, we are considering any issue
SLikeNet runs into with that environment a problem we have to deal with. If
however you are running into problems with an unsupported combination (for
instance the code not being compilable with an ancient version of Visual Studio
like VC6) we might in the end ask you to upgrade to one of the supported
compilers/OSs/3rd-party libraries.

A special note on Xcode® / OSX support:
Our test capabilities are limited on OSX atm. Therefore, we cannot test
SLikeNet at the moment on any other compiler than the one listed below. Since
RakNet originally supported the OSXSDK 10.5+ we are listing that version as
limited support. If you are testing SLikeNet with an older version of Xcode and
are running into any issues, we'd appreciate a short note (preferably with the
compiler error output).

Xbox 360/Playstation Vita/Playstation 3:
RakNet originally supported these platforms. Presumably due to license
restrictions the support couldn't be made open source however. If you require
support for these platforms, please contact us (see chapter 6).

2.2 Compiler support
   Microsoft Visual Studio™: 2010 SP1, 2012 Update 1, 2013 Update 5, 2015
                             Update 3, 2017 15.4.1
   GNU Compiler Collection: 4.6.4, 4.7.4, 4.8.5, 4.9.3, 5.4.0
   Xcode: 7.3.1 (limited support for 3.0+ with OSXSDK 10.5+)
   CMake®: 2.6.4 2.8.12.2, 3.0.2, 3.1.3, 3.2.3, 3.3.2, 3.4.3, 3.5.2, 3.6.3,
           3.7.2

2.3 OS support
   Microsoft Windows: Windows XP (SP3), Windows XP x64 (SP2), Windows Vista®
                      (SP2), Windows 7 (SP1), Windows 8.1,
                      Windows 10 (1607 / 1703)
   Linux: Ubuntu 14.04/16.04
   OSX: 10.12 (Sierra) (limited support for 10.5 (Leopard) and later)

2.4 3rd party libraries/dependencies
While the SLikeNet core engine does not rely on any 3rd party library, several
samples, dependent extensions and also certain optional SLikeNet features make
heavy use of 3rd party libraries/code. This chapter provides an overview of
which 3rd party libraries are used for which configurations/samples and which
versions are supported.
3rd party libraries which are bundled with SLikeNet are marked as such. For
these we also list the 3rd party library's license and reference the location
of the license file.

2.4.1 Boost
   Description: Boost provides free peer-reviewed portable C++ source
                libraries.
   URL: https://www.boost.org/
   Supported versions: 1.34.1, 1.35.0, 1.36.0, 1.37.0, 1.38.0, 1.39.0, 1.40.0,
                       1.41.0, 1.42.0, 1.43.0, 1.44.0, 1.45.0, 1.46.1, 1.47.0,
                       1.48.0
   Used in:
      - Ogre3dInterpDemo (see 4.7)
      - RPC3 (see 5.38)

2.4.2 BZip2
   Description: bzip2 is a freely available, patent free, high-quality data
                compressor.
   URL: http://www.bzip.org/
   Supported versions: 1.0.6 (bundled)
   Used in:
      - AutopatcherClient_SelfScaling (see 5.4)
      - AutopatcherClientGFx3.0 (see 5.2)
      - AutopatcherMySQLRepository (see 4.1)
      - AutopatcherPostgreRepository (see 4.2)
      - AutopatcherServer (see 5.5)
      - AutopatcherServer_MySQL (see 5.6)
      - AutopatcherServer_SelfScaling (see 5.7)
   License: BSD style License
   License file(s): licenses/bzip2 license.txt

2.4.3 FMOD® Ex
   Description: FMOD is a sound effects engine for video games and applications
                developed by Firelight Technologies Pty Ltd.
   URL: https://www.fmod.com/
   Supported versions: 4.38.07+
   Used in:
      - RakVoiceFMOD (see 5.33)

2.4.4 Independent JPEG Group's free JPEG software
   Description: A package containing C software to implement JPEG image
                encoding, decoding, and transcoding.
   URL: http://www.ijg.org/
   Supported versions: version 7 (6b for Microsoft DirectX® - 8d for Irrlicht
                       Engine) (version 7 is bundled)
   Used in:
      - Irrlicht Engine (see 2.4.5)
      - Microsoft DirectX (see 2.4.9)
      - SQLite3ServerLogger (see 4.11)
   License: Independent JPEG Group License
   License file(s): licenses/jpglib license v6b.txt, licenses/jpglib
                    license v7.txt, licenses/jpglib license v8d.txt

   Note:
   A different license (GPL) applies to ansi2knr.c. This source code file is
   however not used by the SQLite3ServerLogger integration and hence doesn't
   have any license implications there. For the usage in Microsoft DirectX and
   the Irrlicht Engine we can't make an explicit statement, though.

2.4.5 Irrlicht Engine
   Description: The Irrlicht Engine is an open source high performance realtime
                3D engine written in C++.
   URL: http://irrlicht.sourceforge.net/
   Supported versions: 1.8.4 (some binary files bundled)
   Dependencies:
      - Independent JPEG Group's free JPEG software (see 2.4.4)
   Used in:
      - IrrlichtDemo (see 4.5)
   License: libpng™/zlib license
   License file(s): licenses/Irrlicht Engine License.txt, libpng license.txt,
                    zlib license.txt

2.4.6 irrKlang
   Description: irrKlang is a cross platform sound library for C++, C# and all
                .NET languages.
   URL: http://www.ambiera.com/irrklang/
   Supported versions: 1.1.3
   Used in:
      - IrrlichtDemo (see 4.5)

2.4.7 Jansson
   Description: Jansson is a C library for encoding, decoding and manipulating
                JSON data.
   URL: http://www.digip.org/jansson/
   Supported versions: 2.4 (bundled)
   Used in:
      - AutopatcherServer_SelfScaling (see 5.7)
      - ComprehensivePCGame (see 5.13)
      - Rackspace (see 4.10)
   License: MIT License
   License file(s): licenses/Jansson License.txt

2.4.8 libcatid
   Description: CatId Common Code Library - a collection of different code
                snippets.
   URL: https://github.com/catid/libcat
   Supported versions: 1.0 (bundled)
   Used in: 
      - Core (if LIBCAT_SECURITY is set to 1)
   License: Modified BSD License
   License file(s): licenses/libcatid license.txt

2.4.9 Microsoft DirectX SDK / Microsoft Windows SDK
   Description: DirectX is a set of low-level APIs for creating games and other
                high-performance multimedia applications.
   Note: As of Windows SDK 8.0 DirectX was integrated into the Windows SDK and
         is no longer shipped as a separate SDK.
   URL: https://msdn.microsoft.com/library/windows/apps/hh452744
   Supported versions: DirectX SDK June 2010 (Matrices contains modified DX
                      sample source code and uses some DX resource files) /
                      WinPhone8: Windows SDK 8.0, 8.0A, 8.1, 8.1A, 10 (builds:
                      10.0.10240.0, 10.0.10586.212, 10.0.14393.795,
                      10.0.15063.0, 10.0.16299.0)
   Dependencies:
      - Independent JPEG Group's free JPEG software (see 2.4.4)
   Used in:
      - AutopatcherClientGFx3.0 (see 5.2)
      - Matrices (see 4.8)
      - Ogre3D (see 2.4.14)
      - RakVoiceDSound (see 5.32)
      - WinPhone8 (see 5.46)
   License: Microsoft Software License Terms - Microsoft DirectX Software
            Development Kit (SDK)
   License file(s): licenses/DirectX SDK EULA.txt

2.4.10 MiniUPnP client
   Description: A UPnP Internet Gateway Device (IGD) control point.
   URL: http://miniupnp.free.fr/
   Supported versions: 1.7 pre-release (1.5 for IrrlichtDemo) (bundled)
   Used in:
      - ComprehensivePCGame (see 5.13)
      - IrrlichtDemo (see 4.5)
      - NATCompleteClient (see 5.25)
   License: Modified BSD License
   License file(s): licenses/MiniUPnP License.txt
   Notes:
   bsdqueue.h has separate license terms (also licensed under the Modified BSD
   License, however).

2.4.11 MySQL®
   Description: MySQL is the world's most popular open source database.
   URL: https://www.mysql.com/
   Supported versions: 5.1.30
   Used in: 
      - AutopatcherMySQLRepository (see 4.1)
      - AutoPatcherServer_MySQL (see 5.6)
      - MySQLInterface (see 4.6)

2.4.12 NVIDIA® Cg Toolkit
   Description: The Cg Toolkit is a legacy NVIDIA toolkit allowing to use
                programmable shading with Cg.
   URL: https://developer.nvidia.com/cg-toolkit
   Supported versions: 2.2 (bundled)
   Used in:
      - DXTCompressor (see 4.4)
   License: NVIDIA license
   License file(s): licenses/NVIDIA Cg Toolkit.txt

2.4.13 NVIDIA Compress YCoCg-DXT
   Description: This example demonstrates how a pixel shader can be used to
                compress a dynamically rendered color map into a texture, using
                both the DXT1 and YCoCg-DXT5 texture formats.
   URL: http://developer.download.nvidia.com/SDK/10/opengl/samples.html#compress_YCoCgDXT
   Supported versions: version downloaded 04/17/2017 (partially bundled with
                       modifications)
   Used in:
      - DXTCompressor (see 4.4)
   License: NVIDIA license, GLEW: Modified BSD License and MIT License
   License file(s): licenses/NVIDIA Compress YCoCg-DXT.txt,
                    licenses/glut license.txt
   Notes:
   NVIDIA Compress YCoCg-DXT contains a version of GLUT which appears to have
   been a continuation by Mark J. Kilgard of the discontinued OpenGL Utility
   Toolkit. The contained glut.h header file suggests it is freely
   distributable and doesn't specify a separate license. Furthermore, it
   bundles GLEW (The OpenGL Wrangler Extension Library) 1.5.0.

2.4.14 Ogre3D
   Description: OGRE (Object-Oriented Graphics Rendering Engine) is a
                scene-oriented, flexible 3D engine written in C++ designed to
                make it easier and more intuitive for developers to produce
                games and demos utilizing 3D hardware.
   URL: http://www.ogre3d.org/
   Supported versions: 1.7.4
   Dependencies:
      - Microsoft DirectX SDK (see 2.4.9)
   Used in:
      - BspCollision (see 4.3)
      - Ogre3DInterpDemo (see 4.7)

2.4.15 OpenSSL®
   Description: OpenSSL is an open source project that provides a robust,
                commercial-grade, and full-featured toolkit for the Transport
                Layer Security (TLS) and Secure Socket Layer (SSL) protocols.
                It is also a general-purpose cryptography library.
   URL: https://www.openssl.org/
   Supported versions: 1.0.0d (bundled)
   Used in:
      - Core (if OPEN_SSL_CLIENT_SUPPORT is set  to 1)
   License: BSD-style license
   License file(s): licenses/OpenSSL License.txt

2.4.16 PortAudio
   Description: PortAudio is a free, cross-platform, open-source, audio I/O
                library.
   URL: http://www.portaudio.com/
   Supported versions: v18.1 (bundled)
   Used in:
      - RakVoice (see 5.31)
   License: MIT-style License
   License file(s): PortAudio License.txt

2.4.17 PostgreSQL®
   Description: PostgreSQL is a powerful, open source object-relational
                database system.
   URL: https://www.postgresql.org/
   Supported versions: 9.1.24
   Used in:
      - AutopatcherPostgreRepository (see 4.2)
      - AutopatcherServer (see 5.5)
      - AutopatcherServer_SelfScaling (see 5.7)
      - PostgreSQLInterface (see 4.9)
      - Lobby2Server_PGSQL (see 5.23)

2.4.18 Autodesk® Scaleform® GFx
   Description: Autodesk Scaleform middleware provides a design-driven workflow
                for creating powerful and immersive user interface (UI)
                environments for PCs, game consoles, mobile devies, and
                consumer electronics.
   URL: https://www.autodesk.com/products/scaleform/overview
   Supported versions: 3.x
   Used in:
      - AutopatcherClientGFx3.0 (see 5.2)

2.4.19 speex
   Description: Speex is an OpenSource/Free Software patent-free audio
                compression format designed for speech.
   URL: https://www.speex.org/
   Supported versions: 1.1.12 (bundled)
   Used in:
      - RakVoice (see 5.31)
      - RakVoiceDSound (see 5.32)
      - RakVoiceFMOD (see 5.33)
      - RakVoiceFMODAsDLL (see 5.33)
      - RakVoiceFMODUsingDLL (see 5.33)
   License: Modified BSD License
   License file(s): licenses/speex license.txt

2.4.20 SQLite®
   Description: SQLite is a self-contained, high-reliability, embedded,
                full-featured, public-domain, SQL database engine. SQLite is
                the most used database engine in the world.
   URL: https://www.sqlite.org/
   Supported versions: 3.6.13 (bundled)
   Used in:
      - BspCollision (see 4.3)
      - Matrices (see 4.8)
      - SQLite3Plugin (see 4.11)
      - SQLite3ClientLogger (see 4.11)
      - SQLite3ServerLogger (see 4.11)
   License: Public Domain
   License file(s): n/A

2.4.21 Steamworks® SDK
   Description: Steamworks is a free suite of tools available to any developer
                to use in their game or software on Steam®.
   URL: https://partner.steamgames.com/
   Supported versions: 1.15-1.23a
   Used in:
      - SteamLobby (see 5.41)

2.4.22 SWIG
   Description: SWIG is a software development tool that connects programs
                written in C and C++ with a variety of high-level programming
                languages.
   URL: http://www.swig.org/
   Supported versions: 2.0.1
   Used in:
      - Swig (see 4.12)

2.4.23 Xdelta
   Description: Xdelta is a C library and command-line tool for delta
                compression using VCDIFF/RFC 3284 steams.
   URL: http://xdelta.org/
   Supported versions: 3.0.6
   Used in:
      - AutopatcherServer_SelfScaling (see 5.7)

2.4.24 XMLParser library
   Description: This is a basic XML parser written in ANSI C++ for portability.
   URL: http://www.applied-mathematics.net/tools/xmlParser.html
   Supported versions: 2.44 (bundled)
   Used in:
      - RoomsBrowserGFx3 (not yet documented)
   License: Modified BSD License
   License file(s): licenses/xmlParser license.txt



3. Getting Started

We provide different ways to build and integrate SLikeNet yourself. For
Windows, we also provide prebuilt libraries to make it as painless as possible
for you to get started.
Furthermore, if you are currently using RakNet 4.081/4.082, we provide a
compatibility mode which allows you to build SLikeNet without any code changes
on your side as an in-place replacement (see chapter 3.4).
If you are using RakNet via DLLs/shared objects you can even replace the DLLs
directly with the correct counterparts of SLikeNet to give it a try.

Note that we also ship the RakNet help as part of SLikeNet. The help files are
located in Help/RakNet and provide references, documentation, and tutorials
which are still useful even if you are using SLikeNet. Unless you define the
macro RAKNET_COMPATIBILITY for your build, you should rename the namespace
RakNet -> SLikeNet and use the includes: <slikenet/foo.h> (instead of simply
including <foo.h>). See chapter 3.5 for further details.
Otherwise, most of the samples/tutorials provided in the help documentation
should still run with SLikeNet the same way.

In the following chapters [SLikeNet] corresponds to the path you extracted the
SLikeNet package to.

3.1 Downloading SLikeNet
We provide the following ways to download SLikeNet:

3.1.1 Download from the webpage
The main download source is via our webpage. Just go to
https://www.slikenet.com/ and download the version there.
We provide different kind of packages. The packages not marked as "source" are
containing prebuilt libraries to simplify getting started and reducing the
maintenance overhead, since they do not require setting up a build environment
for SLikeNet.
Since the packages are however quite large, we also provide the source packages
which contain the complete package (including source code and documentation)
except for the large prebuild libraries.
ZIP and RAR archives are containing the source code and text files with Windows
line endings while the TAR.GZ archive contains the files with Linux line
endings.

3.1.1.1 Verifying the file integrity
The used RAR, TAR.GZ, and ZIP archives have built-in checksums to verify the
data integrity of the package. You can use the different archive tools to
ensure the package was downloaded correctly and isn't broken.
In addition to this, you can calculate the MD5, SHA-1, SHA-256, or SHA-512 hash
of the archive and compare it against the hash value noted at the download
page.

3.1.1.2 Validating the download package
In order to validate the downloaded package was really published by SLikeNet
and wasn't altered with by someone else, ASCII armored signatures are provided
for each download package (using an OpenPGP key). The corresponding key can be
downloaded from the homepage: https://www.slikesoft.com/?page_id=111,
the webpage's foaf.rdf-file or from a public key server.
Fingerprint: 90BDC5B9C28EBCAD5805930806DED38809EECFCA

3.1.2 Downloading via SVN
The latest development version can always be acquired directly via our
Subversion® repository at https://www.slikesoft.com/svn/slikenet/.
Released versions are tagged (i.e.
https://www.slikesoft.com/svn/slikenet/tags/) while the main development trunk
is located under https://www.slikenet.com/svn/slikenet/trunk/ .
We suggest you use a Subversion client to get your copy from that repository. A
list of available Subversion clients is located here:
https://subversion.apache.org/packages.html .

3.1.3 Downloading via GIT®
In addition to the main SVN repository, we also provide SLikeNet as a fork of
RakNet on GitHub (https://github.com/SLikeSoft/SLikeNet). If you are mainly
using GIT, this might be the way you wanna got to acquire a copy of SLikeNet.

Note that on GitHub we don't provide the prebuild libraries in the repository
due to the implications of large files inside a GIT repository. If you require
the prebuild biniares you can download these from our webpage (see 3.1.1) or
from the release page on GitHub as separate download packages.

3.2 Using SLikeNet on Windows

3.2.1 Using prebuilt SLikeNet libraries with Microsoft Visual Studio
Following is a step-by-step instruction on how to set up a C++ project using
the Visual Studio IDE.

1. Right click your project in the Solution explorer -> Properties
2. C/C++ -> General -> Additional Include Directories: add
   [SLikeNet]\Source\include
3. Linker -> General -> Additional Library Directories: add
   [SLikeNet]\Lib\prebuild\[VS_2010] (where VS_2010 should be replaced with the
   version of the IDE being used)
4. Linker -> Input -> Additional Dependencies: add the correct library (see
   chapter 3.2.3)

That's all you need to get started using SLikeNet. No additional steps are
required. You won't even have to compile SLikeNet yourself.

3.2.2 Building SLikeNet yourself with Microsoft Visual Studio
If you need a special configuration which we don't provide or if you simply
want to build SLikeNet yourself:

1. Open SLikeNet.sln with Visual Studio
2. VS2010: skip this step
   VS2012: Select "Update" in the pop-up dialog: "Update VC++ Compiler and
           Libraries"
   VS2013/VS2015: Select "OK" in the pop-up dialog: "Upgrade VC++ Compiler and
                  Libraries"
   VS2017: Select "OK" in the pop-up dialog: "Retarget Projects"
3. Adjust NativeFeatureIncludesOverrides.h and define any optional macros to
   enable (or disable) certain features
4. Select the correct configuration (Debug, Release or Retail; with or without
   Unicode support) and the correct machine type (Win32 or x64)
5. Build the appropriate project:
   - DLL: to build SLikeNet as a dynamic link library
   - LibStatic: to build SLikeNet as a static library

See chapter 3.4 if you want to build SLikeNet for an in-place replacement of
RakNet.

3.2.3 Provided default libraries
We ship several libraries which can be used without having to compile SLikeNet
yourself. The prebuilt libraries are located under
[SLikeNet]/Lib/prebuild/[VS_2010].
VS_2010 corresponds to the Visual Studio version the contained libraries have
been built with/for.
The naming scheme follows the following pattern:
SLikeNet libraries: SLikeNet(_DLL)_[Debug|Release|Retail]( - Unicode)_[core|ext]_[Win32|x64]
RakNet compatibility libraries RakNet(_DLL)_[Debug|Release|Retail]_[core|ext]_[Win32|x64]

_DLL indicates the library is built as a dynamic link library. The absence of
_DLL indicates that it's a static library.
Debug|Release|Retail correspond to the configuration (see chapter 3.5.2 for
details).
"- Unicode" indicates the library is built with the Unicode character set. We
do not provide this configuration by default with the RakNet compatibility
mode, since RakNet did not provide such configuration.
Following the "- Unicode" marker is either the _core or _ext (for extended)
marker. A core configuration is built with the bare minimum settings for
SLikeNet which means: no ipv6, no OpenSSL, and no LIBCAT support. The extended
configuration is built with these three features enabled.
The last marker indicates whether it's a 32-bit (Win32) or a 64-bit (x64)
library.

3.3 Using SLikeNet with Linux and OSX

3.3.1 Building SLikeNet
To build SLikeNet on Linux or OSX, you need a supported version of CMake and a
supported compiler version. See chapter 2.2 for a list of what is supported.

1. Create a directory which you will use as the root-directory for SLikeNet (we
   refer to that directory as [SLikeNetRootDirectory])
2. Extract the SLikeNet package to [SLikeNetRootDirectory]/source
3. Adjust [SLikeNetRootDirectory]/source/Source/NativeFeatureIncludesOverrides.h
   and define any optional macros to enable (or disable) certain features
4. Create a new directory: [SLikeNetRootDirectory]/cmake
5. Change the directory to [SLikeNetRootDirectory]/cmake
6. Run cmake ../source
7. Run make

This will build SLikeNet as a static as well as the shared object library.
Please note that at the moment the generated libraries using CMake are still
named RakNet. This will be changed in SLikeNet 0.2.0.

3.4 RakNet compatibility mode

3.4.1 Migrating from RakNet to SLikeNet
SLikeNet provides a simple way to migrate from RakNet to SLikeNet. All you need
to do is to make sure that your project defines RAKNET_COMPATIBILITY in
defineoverrides.h, redirect your include and library folders to the SLikeNet
ones (see chapter 3.2.1 for how this is done with Visual Studio), adjust the
.lib file name, and rebuild your game/application without further
modifications.

Note that you can also continue pointing your include directory to
[SLikeNet]/Source (instead of [SLikeNet]/Source/include as it is described in
chapter 3.2.1). That way you can more easily switch between RakNet and SLikeNet
if you need to.

3.4.2 Building RakNet compatibility mode yourself
If you want to build SLikeNet in RakNet compatibility mode yourself on Windows,
follow the steps described in chapter 3.2.2 and build the corresponding project
listed under RakNet_Backwards_Compatibility in the SLikeNet solution.

Note that at the moment SLikeNet only provides building the RakNet
compatibility mode on Windows.

3.4.3 In-place replacement of RakNet
A very handy way to give SLikeNet a try is to simply replace the DLL of your
application with the corresponding one provided by SLikeNet. You can find the
DLLs under [SLikeNet]/Lib/prebuild/[VS_2010]. Replace your existing DLL with
the SLikeNet version and start your application. If everything goes well, your
game/application will start and run without any issues and no further changes
required.

Since the protocol was kept compatible with RakNet, you can even run the server
using RakNet and the client(s) running SLikeNet (or vice versa).

3.5 Development notes on differences between RakNet and SLikeNet

3.5.1 General notes
There are a couple of differences between RakNet and SLikeNet when it comes to
using the libraries which are noteworthy:
1. (except for RakNet compatibility mode) You should include SLikeNet headers
   via <slikenet/foobar.h> where RakNet required you to include only
   <foobar.h>.
2. (except for RakNet compatibility mode) You need to use the SLikeNet
   namespace where previously you used the RakNet namespace.
3. RAKNET_VERSION, RAKNET_VERSION_NUMBER, RAKNET_VERSION_NUMBER_INT, and
   RAKNET_DATE were kept due to backwards compatibility with RakNet but were
   updated to 4.082 and 7/26/2017 respectively and will stay at these values for
   all SLikeNet 0.x.x/1.x.x releases.
   In order to distinguish between different SLikeNet versions, you should use
   the newly introduced SLIKENET_VERSION, SLIKNET_VERSION_NUMBER,
   SLIKENET_VERSION_NUMBER_INT, and SLIKNET_DATE macros.

3.5.2 Retail configuration
RakNet only shipped with a debug and a release configuration while SLikeNet
ships 3 different configurations: debug, release, and retail.
The debug configuration provides full debugging support without any kind of
optimization. The focus of this configuration lies in debugging capabilities
(and not on performance). This is in principle the same what RakNet provided.
The release configuration provides partial debugging mode with optimizations
but configured so it's usable for larger games. In particular the whole program
optimization (WPO) and link time code generation (LTCG) is disabled (since this
can significantly increase build times on larger projects).
The retail configuration is the configuration intended to be used when building
the versions which will be shipped to users/customers. It's configured to
provide the best performance and no debugging overhead whatsoever. WPO and LTCG
are enabled in this configuration too.

To use the retail configuration you also need to define the _RETAIL macro
(usually you'd do that via the project properties).

Note that the RakNet 4.081/4.082 configurations were a bit inconsistent. By
default the release configuration for RakNet DLL was built with WPO/LTCG
enabled while for RakNet Static it was disabled. So if you want to use the
corresponding SLikeNet libraries for what RakNet used as the release
configurations, you'd use the retail configuration for the dynamic library and
the release configuration in case of a static library.

3.5.3 OSX usage of @rpath for install_name
SLikeNet uses @rpath for the directory portion of the "install_name" field of
shared libraries, if CMake >= 2.8.18 is used.
See the CMake documentation regarding MACOSX_RPATH for further details.
Since this property was introduced in CMake 2.8.18 building SLikeNet with CMake
2.6.4 will not use this property and instead set the "install_name" field to an
absolute path like RakNet did.

3.5.4 PacketLogger FormatLine() changes
For security reasons SLikeNet introduces two overloads of the virtual
PacketLogger::FormatLine() method which take an additional size parameter for
the output buffer. Internally only these new overloads are called. If you
overwrote the implementation of the FormatLine() method and relied on this
being used/called from the library, you will have to adjust your overrides to
overwrite the new variants instead.

3.5.5 CMake install destinations for non-Windows platforms
RakNet used to install its libs/headers into the source directory rather than
lib/include destinations commonly used on Linux/OSX platforms. Since this
prevented straight forward usage of the library on these platforms, it was
changed in SLikeNet 0.2.0. As of this version, running 'make install' will
install the lib/header files in the usual locations which are configurable via
the CMAKE_INSTALL_PREFIX variable.

3.6 Configuring SLikeNet

SLikeNet uses macros to control certain settings. The overview of the available
settings can be found in the accompanying Doxygen generated documentation
(refer to the documentation regarding defines.h and NativeFeatureIncludes.h).
These "settings" can be redefined in the corresponding override-headers
(definesoverrides.h / NativeFeatureIncludeOverrides.h).

3.6.1 Security relevant settings

When using SLikeNet to transfer files between peers (f.e. via the AutoPatcher
or directly via FileListTransfer), SLikeNet allocates a single memory chunk to
retrieve the incoming file. For rather large files (up to 4 GiB), this can
trigger crashes (due to running out of memory) especially on 32-bit targets or
on Windows the receiving peer becoming unresponsive (due to falling back to
using page files).

To mitigate these cases, it's *strongly* suggested to redefine
SLNET_MAX_RETRIEVABLE_FILESIZE to a reasonable value for your application. In
principle a lower setting is always preferred. So if you know that you never
transmit files > 20 MiB over the wire, you'd define the macro to 20971520.



4. Dependent Extensions [partially copied from RakNet]

SLikeNet contains several dependent extensions which extend the core
functionality of SLikeNet. Following lists and describes the available
extensions:

4.1 AutopatcherMySQLRepository
   Description: Autopatcher Server implemented using MySQL providing patch
                information and asynchronous database queries to
                AutopatcherClient.
   Dependencies:
      - BZip2 (see 2.4.2)
      - MySQL (see 2.4.11)
      - MySQLInterface (see 4.6)
   Notes:
   A database with the specified name must be created manually (i.e. run:
   "CREATE DATABASE myDatabaseName"). When asked to "Enter DB scheme:" enter
   "myDatabaseName". The max packet size should be increased to 1000M.

4.2 AutopatcherPostgreRepository
   Description: Autopatcher Server implemented using PostgreSQL providing patch
                information and asynchronous database queries to
                AutopatcherClient.
   Dependencies:
      - BZip2 (see 2.4.2)
      - PostgreSQL (see 2.4.17)
      - PostgreSQLInterface (see 4.9)

4.3 BspCollision
   Description: Sample project demonstrating the usage of the
                SQLite3ClientLogger.
   Dependencies:
      - Ogre3D (see 2.4.14)
      - SQLite (see 2.4.20)

4.4 DXTCompressor
   Description: Image data compressor.
   Dependencies:
      - NVIDIA Cg Toolkit (see 2.4.12)
      - NVIDIA Compress YCoCg-DXT (see 2.4.13)
   Notes:
   The following source code files, which carry a specific license, are taken
   directly from the NVIDIA Compress YCoCg-DXT library:
   - FrameBufferRenderBuffer.hpp: Simplified BSD License - Copyright (c) 2005,
     Aaron Lefohn (lefohn@cs.ucdavis.edu), Adam Moerschell
     (atmoerschell@ucdavis.edu)
   - ShaderSource.h: MIT License - Copyright (c) NVIDIA Corporation.

4.5 IrrlichtDemo
   Description: Demonstrates Irrlicht modified with SLikeNet for peer to peer
                multiplayer.
   Dependencies:
      - Irrlicht Engine (see 2.4.5)
      - irrKlang (see 2.4.6)
      - MiniUPnP client (see 2.4.10)
   Notes:
   Due to license restrictions we are currently not able to bundle irrKlang
   with our sourcecode. To compile the IrrlichtDemo you will have to download
   irrKlang separately, put the header files and library file in the
   IrrlichtDemo/irrKlang-1.1.3 directory and the irrKlang.dll in the
   IrrlichtDemo directory.

   See slikenetstuff.cpp for most of the netowrking code.
   Once the user presses "Start Demo" InstantiateRakNetClasses() is called. It
   allocates all SLikeNet classes including the dependent plugins. It also
   tries to connect to the NATCompleteServer.
   Upon an established connection to the NATPunchthroughServer (see
   ID_CONNECTION_REQUEST_ACCEPTED), UPNP will run to open the router, if
   possible. It tries to open the external port connected to the
   NATPunchthroughServer and maps that to the internal port used by SLikeNet.
   If this succeds, NATPunchthrough should automatically succeed for this
   system. Next, the cloduServer will be queried for active connections. If any
   connection is returned, NATPunchthroughClient::OpenNATGroup() is called to
   open the router for those systems and these systems are connected to. If
   there are no existing games or a failure occurs, a new game is started.
   Incoming packets are checked in UpdateRakNet(). If the NAT punchrough
   failed, we use the proxy server instead. CDemo derives from
   UDPProxyClientResultHandler, which will get the results of the proxy
   connection attempt via its callback interfaces.
   When another user connects with us (i.e. ID_NEW_INCOMING_CONNECTION or
   ID_CONNECTION_REQUEST_ACCEPTED), we create a new connection object and call
   ReplicaManager3::PushConnection(). This tells the automatic object
   replication system that this connection is ready to participate in the game.
   On pushing a new connection to ReplicaManager3, all existing Replica3
   objects are sent to that server. In the case it's our own player (i.e.
   PlayerReplica) which was created via InstantiateRakNetClasses.
   PlayerReplica derives from BaseIrrlichtReplica which derives from Replica3.
   BaseIrrlichtReplica implements all the interfaces necessary for peer to peer
   multiplayer; particularly returning QueryConstruction_PeerToPeer,
   QueryRemoteConstruction_PeerToPeer, and QuerySerialization_PeerToPeer. It
   also has a member variable position which is used by all derived classes.
   This variable is automatically synchronized in SerializeConstruction() and
   Serialize().
   PlayerReplica additionally serializes playerName, isMoving, isDead, and
   rotationAroundYAxis. playerName never changes, so is sent only in
   SerializeConstruction(). isMoving and isDead are serialized per-tick, and
   are used to control what animation is played on remote systems.
   rotationAroundYAxis is the camera rotation, which rotates the player on the
   remote system.
   Both, position and rotationAroundYAxis, are interpolated on the remote
   system using positionDeltaPerMS and rotationDeltaPerMS. When we deserialize
   either of these values, the amount is added per-tick based on the amount of
   time elapsed until the real position is reached. This happens in Update(),
   which is called from the CDemo.
   When the player presses the shoot button, CDemo::shoot() is called. If the
   player is not dead, CDemo::shootFromOrigin() is called which behaves the
   same as in the original demo. It creates a moving ball to hit the nearest
   terrain object. In the same function, a new instance of BallReplica is
   created and referenced. ReplicaManager3 will automatically transmit this new
   object to connected systems (including systems which connect later).
   BallReplica is initialized with the same parameters as the animated particle
   created in shootFromOrigin(). Its position is a different variable, but the
   math works the same so the replicated object is always in the same spot as
   the particle you see.
   BallReplica::PostDeserializeConstruction() is called on remote systems when
   a new ball is created. It calls shootFromOrigin() to create the particle
   visible effect. It also causes the remote player with the same
   creatingSystemGUID to play the attack animation. creatingSystemGUID is a
   value automatically set by ReplicaManager3 and identifies which system
   originally instantiated this object.
   Note that the position variable in BallReplica works differently than with
   PlayerReplica. In PlayerReplica, it is updated from the remote system
   because it can change at random. In BallReplica, it represents only the
   origin of when the ball was created and doesn't otherwise change. This can
   be done because the path the ball takes is deterministic. This saves
   bandwidth and programming.
   In BallReplica::Update(), if this is our own ball, we check if the ball has
   existed long enough that it should hit a wall. If so, we destroy it and send
   out this destruction packet to the other systems.
   In BallReplica::Update(), if this is a ball created by a remote system, we
   check if the ball has hit our own player. The function
   GetSyndeyBoundingBox() is needed because our own player has no model (i.e.
   it's only a camera). Were the game to use other models, we would need to
   calculate the bounding box for whatever player model we would be using.
   If we die, PlayerReplica::deathTimeout is set and is sent to the remote
   systems in PlayerReplica::Serialize() as a single boolean read into the
   isDead member variable.
   That's it.
   There's a known issue in the implementation:
   Because the ball effet in Irrlicht and the BallReplica class for the actual
   gameplay are disjoint, were a player to disconnect and his ball deleted, the
   visible effect would still be there. This issue could be fixed by adding a
   reference to the particle effect and removing the particle when the ball is
   destroyed.

4.6 MySQLInterface
   Description: Interface class for MySQL integration.
   Dependencies:
      - MySQL (2.4.11)

4.7 Ogre3DInterpDemo
   Description: Demonstrates how to lag a client in the past using the
                interpolation history class in order to get smooth visuals
                despite the choppy input.
   Dependencies:
      - Boost (see 2.4.1)
      - Ogre3D (see 2.4.14)
   Notes:
   Start two instances on the same computer, press 's' on one and 'c' on the
   other. Hold down space to see the actual networking.

4.8 Matrices
   Description: DirectX Matrices sample used to copy the backbuffer to the main
                memory in order to send it to the SQLiteClientLoggerPlugin.
   Dependencies:
      - Microsoft DirectX SDK (see 2.4.9)
      - SQLite (see 2.4.20)

4.9 PostgreSQLInterface
   Description: Interface class for PostgreSQL integration.
   Dependencies:
      - PostgreSQL (see 2.4.17)

4.10 Rackspace
   Description: Communication class for the Rackspace Cloud Servers using API
                v2.0
   Dependencies:
      - Jansson (see 2.4.7)

4.11 SQLite3Plugin / SQLite3ClientLogger / SQLite3ServerLogger
   Description: Passes calls to sqlite3_exec over the network.
                SQLite3ClientLogger and SQLite3ServerLogger extend this to
                using an SQLite database for logging.
   Dependencies:
      - Independent JPEG Group's free JPEG software (SQLite3SeverLogger only -
        see 2.4.4)
      - DXTCompressor (SQLite3SeverLogger only - see 4.4)
      - SQLite (see 2.4.20)

4.12 Swig / DLL_Swig
   Description: Generates a C# interface for the SLikeNet DLL.
   Dependencies:
      - SWIG (see 2.4.22)



5. Samples [partially copied from RakNet]

SLikeNet contains different samples which can also be used as the basis (or
direct integration) of certain functionality. The following chapters provide an
overview of all the samples:

5.1 AutopatcherClient
   Description: Console application to provide patching capabilities to an
                end-user's application.

5.2 AutopatcherClientGFx3.0
   Description: Skinnable GUI client using Autodesk Scaleform GFX to provide
                patching capabilities to an end-user's application.
   Dependencies:
      - BZip2 (see 2.4.2)
      - Microsoft DirectX SDK (see 2.4.9)
      - Autodesk Scaleform GFx (see 2.4.18)

5.3 AutopatcherClientRestarter
   Description: Client application to restart the autopatcher process if it got
                stuck and needs a manual restart. This application should be
                shipped alongside a client application which uses the
                Autopatcher.

5.4 AutopatcherClient_SelfScaling
   Description: Provides patching capabilities to an end-user's application for
                the AutopatcherServer_SelfScaling project.
   Dependencies:
      - BZip2 (see 2.4.2)

5.5 AutopatcherServer
   Description: This is a sample implementation of the autopatcher server
                implemented using PostgreSQL.
   Dependencies:
      - BZip2 (see 2.4.2)
      - PostgreSQL (see 2.4.17)
      - PostgreSQLInterface (see 4.9)

5.6 AutoPatcherServer_MySQL
   Description: This is a sample implementation of the autopatcher server
                implemented using MySQL.
   Dependencies:
      - BZip2 (see 2.4.2)
      - MySQL (see 2.4.11)
      - MySQLInterface (see 4.6)
   Notes:
   A database with the specified name must be created manually (i.e. run:
   "CREATE DATABASE myDatabaseName"). When asked to "Enter DB scheme:" enter
   "myDatabaseName". The max packet size should be increased to 1000M.

5.7 AutopatcherServer_SelfScaling
   Description: Extended version of AutopatcherServer. It will self-scale to
                load, using the Rackspace Cloud to add additional servers when
                all servers are full. Load balancing is accomplished with the
                help of ClouseServer / ClouseClient. DynDNS is used to point to
                the host of the system.
   Dependencies:
      - BZip2 (see 2.4.2)
      - Jansson (see 2.4.7)
      - PostgreSQL (see 2.4.17)
      - PostgreSQLInterface (see 4.9)
      - (OPTIONAL) Xdelta (see 2.4.23)
   Notes:
   SLikeNet must be compiled with OPEN_SSL_CLIENT_SUPPORT set to 1.
   xdelta is optionally used to generate patches.

5.8 ChatExample
   Description: Sample of a simple text-based client/server chat.

5.9 CloudClient
   Description: Associated with the CloudServer project, this sample provides a
                directory server implementation.
   Notes:
   The application connects to whichever instance of the CloudServer project
   was passed on the command line. After connection UploadInstanceToCloud(),
   GetClientSubscription(), and GetServers() are called.
   UploadInstanceToCloud() uploads the own instance to the cloud.
   GetClientSubscription() returns a list of all clients.
   GetServers() returns the list of running servers with the connection counts.
   ID_CLOUD_GET_RESPONSE is returned if GetServers()/GetClientSubscription()
   has results. In case of GetServers() it will also reconnect to the server
   with the least connections (i.e. client-based load balancing).
   ID_CLOUD_SUBSCRIPTION_NOTIFICATION is returned when the subscription to the
   client list changes.

5.10 CloudServer
   Description: Provides ways for queries on remote systems but does not
                provide a way to discover these.
   Notes:
   Using the command line passed domain name:
      - the server acts as host, if connecting to own IP
      - the server acts as host and points the domain name to our own IP, if
        connecting to another system fails
      - the server treats any already existing system on the domain name as host
   For the host connection the TwoWayAuthentication plugin is used to validate
   that the system is actually a host by checking a pre-designated password.
   Using a local CloudClient instance, querying the cloud server. The retrieved
   list is then the list of other servers (including internal and external
   IPs). The internal IP is used first to establish a connection, in case it's
   a co-located server. If that fails, the external IP is used.
   After that connection process the local CloudClient instance uploads our own
   internal and external IP to the CloudServer.
   Two lists are used to restrict (via CloudServerQueryFilter) reads to
   internal IPs (stored in CloudServerList,1).
   FullyConnectedMesh2::AddParticipant() is used to determine the host of the
   server. When the host changes to the local server, the DynDNS class is used
   to update the DNS to point to the new host.
   Load balancing is client-based (see CloudClient).
   Following plugins can be opted in on the server:
      - AutopatcherServer (provided that all server use the same database)
      - DeltaDirectoryTransfer
      - FileListTransfer
      - Lobby2 (database operations only; no login or presence)
      - NATTypeDetection
   Following plugins can be opted in but require that interacting clients are
   on the same server (hence connect the client to all relevant servers, if
   required):
      - NATPunchthroughServer
      - TeamManager (entire team must be on the same server)
      - RoomsPlugin (all users that interact with each other must be on the
                     same server)
   Following plugins are active implicitly:
      - UDPProxyCoordinator (supporting multiple UDPProxyServers but only a
                             single coordinator)

5.11 CommandConsoleClient
   Description: Used for console-based remote text administration of servers,
                this console project connects to a server running
                RakNetTransport with the ConsoleServer.

5.12 CommandConsoleServer
   Description: Tests the ConsoleServer class which provide means to administer
                servers remotely through text commands. telnet and SLikeNet's
                protocol are supported.

5.13 ComprehensivePCGame
   Description: This sample demonstrates complete network functionality found
                in typical PC peer to peer games via the integration of UPNP,
                HTTPConnection2, NATPunchthrough, TeamManager, ReplicaManager3,
                FullyConnectedMesh2, RPC4, and ReadyEvent.
   Dependencies:
      - Jansson (see 2.4.7)
      - MiniUPnP client (see 2.4.10)
      - (OPTIONAL) NATCompleteServer (see 5.26)
   Notes:
   Following describes the network flow of the sample:
   - Initially the CONNECTING_TO_SERVER phase is entered to connect to a NAT
     punchthrough server and connects to the master server. The NAT
     punchthrough server must be running at a minimum
     FeatureList::NAT_PUNCHTHROUGH_SERVER. If NAT_PUNCHTHROUGH_SEVER is set to
     1, the server must be running FeatureList::NAT_TYPE_DETECTION_SERVER.
   - If NAT_TYPE_DETECTION_SERVER is set to 1, the DETERMINE_NAT_TYPE phase is
     entered and the result of this is stored in myNatType. Otherwise, the
     SEARCH_FOR_GAMES phase is entered.
   - SearchForGames() sends a GET request to the master server. In the
     background, HTTPConnection2 uses TCPInterface to connect to the server and
     to send the command. If it succeeds, TCPInterface returns a valid
     SystemAddress structure from HasCompleteConnectionAttempt() and later
     HTTPConnection2::GetResponse() returns true.
   - Upon HTTPConnection2::GerResponse() returning true, if parsed JSON body
     for a GET operation has a body, this indicates that other systems have
     uploaded rooms. The user is presented the options to join, create or
     search for rooms.
   - In CreateRoom() PostRoomToMaster() is called. PostRoomToMaster() iterates
     through the list of users (from the Context of CreateRoom()) and
     serializes the natType of each of the users. It also serializes the
     game->gameName variable. Other data such as the names of users, score,
     locked value, etc. can be serialized too. Two Team classes are
     instantiates as the game supports two teams. TM_World::ReferenceTeam() is
     called right away because you can join teams at any time. However,
     ReplicaManager3::Reference() is not called yet, because we do not want to
     replicate game objects (including teams) until the host is known from
     ID_FCM2_NEW_HOST. Lastly, FullyConnectedMesh2::ResetHostCalculation() is
     called. This resets the internal timer that tracks basically how long the
     multiplayer game has been playing. This is necessary because the order of
     how the host migrates follows how long each session has been running.
   - If the user presses 'j' to join a room, NatPunchthroughClient::OpenNAT()
     is called. Upon ID_NAT_PUNCHTHROUGH_SUCCEEDED, RakPeerInterface::Connect()
     is called. Upon ID_NAT_PUNCHTHROUGH_SUCCEEDED, RakPeerInterface::Connect()
     is called to connect to that system. This system is whichever system last
     uploaded the session, which is the responsibility of the session host.
     Note that even if it wasn't the session host, the program would still
     operate correctly provided that the system connected to has the correct
     list of participants in the FullyConnectedMesh2 plugin. Also note that the
     process of joining a session is asynchronous and does not modify data on
     the server or affect the game in operation. The game phase is updated to
     NAT_PUNCH_TO_GAME_HOST.
   - If the connection attempt in the previous step fails, or the connection is
     lost while in the NAT_PUNCH_TO_GAME_HOST phase, the rooms are searched
     again.
   - If the connection attempt succeeds,
     FullyConnectedMesh2::ResetHostCalculation() is called. ID_USER_PACKET_ENUM
     is then transmitted without data to indicate that this is a request
     message to join a game.
   - Upon ID_USER_PACKET_ENUM, either FullyConnectedMesh2::StartVerifiedJoin()
     is called or ID_USER_PACKET_ENUM+1 is returned if the session is not
     joinable. StartVerifiedJoin() ultimately returns
     ID_FCM2_VERIFIED_JOIN_START, ID_FCM2_VERIFIED_JOIN_ACCEPT, or
     ID_FCM2_VERIFIED_JOIN_REJECTED to the requester.
   - ID_FCM2_VERIFIED_JOIN_START means the requester has to perform additional
     connection steps before the game session can be joined.
     NatPunchthroughClient::OpenNAT() is performed on each system returned from
     FullyConnectedMesh2::GetVerifiedJoinRequiredProcessingList(). It may not
     be necessary to call OpenNAT() on each of these systems (for example if
     UPNP succeeded) but there's no harm in doing so and it simplifies the code
     flow. If ID_NAT_PUNCHTHROUGH_SUCCEEDED is returned, the system is
     connected. FullyConnectedMesh2 reads connection attempt successes,
     failures, and NAT punchthrough failures automatically. When all systems in
     the GetVerifiedJoinRequiredProcessingList() have been processed, the
     system that sent StartVerifiedJoin() is notified automatically. The
     process will continue with ID_FCM2_VERIFIED_JOIN_START or stop with
     ID_FCM2_VERIFIED_JOIN_ACCEPTED or ID_FCM2_VERIFIED_JOIN_REJECTED.
   - Assuming ID_FCM2_VERIFIED_JOIN_ACCEPTED completed,
     FullyConnectedMesh2::AddParticipant() is called internally on all systems
     automatically. This leads to ID_FCM2_NEW_HOST being returned to the
     program. If this is the first time ID_FCM2_NEW_HOST has been calculated
     (which is when two systems first connect), all FullyConnectedMesh2
     participants added in the previous step are registered with
     ReplicaManager2, TeamManager, and ReadyEvent in RegisterGameParticipant().
     If the host is already known, the new partiicipant(s) are read using
     GetVerifiedJoinAcceptedAdditionalData() in the
     ID_FCM2_VERIFIED_JOIN_ACCEPTED block and added with
     RegisterGameParticipant().
   - Registering remote systems and game objects with ReplicaManager3 leads to
     ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE on each system. Each system creates
     its own user, so that ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE arrives once
     from each remote system for that user. Additionally, the host sends the
     two Team objects. When all downloads are complete from all systems,
     ReplicaManager3::GetAllConnectionDownloadCompleted() returns true and the
     game can proceed.
   - The Game class is implemented as a static object. This means it is created
     locally on each system rahter than via a network command. It is also not
     destroyed when a remote system disconnects. Refer to the retuns calls from
     QueryConstruction(), QueryActionOnPopConnection(), and other operations
     for further details. Note that no statement exists in
     SampleConnectionRM3::AllocReplica() to create a game instance, as it's not
     necessary.
   - The Team class is created remotely by the host via QueryConstruction().
     The host also serializes the object. The Team object is not destroyed when
     the original system that created it disconnects. The host can change.
     Therefore, whoever is currently the host according to FullyConnectedMesh2
     automatically takes over replication duties.
   - The User class is created and serialized by whichever system created it.
     When that system disconnects, the User object is deleted automatically due
     to the return value from QueryActionOnPopConnection().
   - Teams and team members are managed by the TeamManager plugin. The data
     used by TeamManager is TM_Team in the Team class and TM_TeamMember in the
     User class. The only thing of note is that TM_Team and TM_TeamMember is
     referenced when created by the network in DeserializeConstruction(), but
     deserialized in PostDeserializeConstruction(). This is because
     deserialization of the TM_TeamMember requires that any TM_Team objects
     that team references has already been created.
   - PostRoomToMaster() is called by the host whenever users leave (in the
     User-dtor) or are created (in User::PostDeserializeConstruction()). This
     is to update the current user count returned from the master server.
     PostRoomToMaster() is also called by the new host whenever a new system
     becomes host, so connecting systems know which system to connect to.
   - When a system exits a room by pressing 'e', all connections are closed
     except the connection to the NAT punchthrough server. The state data
     maintained by each plugin is cleared. The room entry on the cloud is
     deleted (only does something, if we are host).

5.14 CrashReporter
   Description: Demonstrates the crash reporter system. When the application
                crashes, this generates and optionally emails or saves a
                mini-dump.

5.15 DirectoryDeltaTransfer
   Description: Demonstration of the DirectoryDeltaTansfer plugin (a patching
                system without dependencies on a database).

5.16 Encryption
   Description: Sample project to demonstrate the secure connectivity feature
                of SLikeNet.

5.17 FCM2Host
   Description: Demonstrates the FullyConnectedMesh2 plugin host migration.

5.18 FCM2Host_Simultaneous
   Description: Another demonstration of the FullyConnectedMesh2 plugin host
                migration.

5.19 FCM2VerifiedJoinSimultaneous
   Description: Demonstration of two systems calling StartVerifiedJoin()
                simultaneously

5.20 FullyConnectedMesh
   Description: Sample of the FullyConnectedMesh2 plugin.

5.21 iOS ChatClient
   Description: iOS sample chat client (equivalent to ChatExampleClient)
                connecting to a chat server (see ChatExampleServer)

5.22 LANServerDiscovery
   Description: Demonstrates how to find other servers on a LAN.

5.23 Lobby2Server_PGSQL
   Description: Database backend for the Lobby2 system supporting users, clans,
                friends, and other persistent information.
   Dependencies:
      - PostgreSQL (2.4.17)

5.24 MessageFilter
   Description: Sample project showing the use of the message filter plugin
                which can be used to filter out network messages on a
                filter-set basis.
                For instance one could have a spectator filter to prevent
                spectators sending gameplay messages.

5.25 NATCompleteClient
   Description: Client to demonstrates all NAT components in a sample project.
   Dependencies:
      - MiniUPnP client (see 2.4.10)

5.26 NATCompleteServer
   Description: Server to demonstrates all NAT components in a sample project.

5.27 PacketLogger
   Description: Shows how to use the PacketLogger plugin(s).

5.28 PHPDirectoryServer2
   Description: Sample to setup a php-based administration page to interact
                with SLikeNet.
   Notes:
   SLikeNet uses a php page to hold listings of running games. For example, one
   might run a server with the name "MyServer" and the game mode "Deathmatch"
   and wants to let people know that this server is running. Other people would
   connect to the webpage to download the list of running servers.
   Following functions are available:
   - Admin:
     When the php page is running and no password file exists, prompt the user
     to enter two password: upload and download. The user must set both
     passwords before any other functionality is available. Once the passwords
     have been set, the password file is created. The file must not be readable
     by the general public and passwords must be checked for syntax such that
     they can be used in subsequent operations and passed in the URL. There are
     otherwise no restrictions on what password can be used. Once the two
     passwords are set, the only way to change them is to delete the file that
     stores the passwords. After doing so, the page will once again prompt to
     set the two passwords.
     If in any operation the password is required but missing (or incorrect),
     the operation will be ignored.
   - Upload:
     The user executes Directoryserver.php?query=upload&uploadPassword=yyy .
     The body of the message contains the data to be stored. Every odd indexed
     field is the column name. Every even indexed field is the value. Fields
     are separated by ASCII value 1.
     Column names will always contain at a minimum __GAME_PORT and __GAME_NAME.
     A column name __System_Address with corresponding value is automatically
     added to the input based on the IP address of the system doing the upload.
     If the body of the message also contains __System_Address as a column
     name, use that instead of the automatically generated column.
     A column name __SEC_AFTER_EPOCH_SINCE_LAST_UPDATE with a corresponding
     value is automatically added to the input, based on the current time of
     the update.
     If the __System_Address, __GAME_PORT, and __GAME_NAME fields all match an
     existing entry, the entry will be overwritten.
     Input example: __GAME_PORT?1235?__GAME_NAME?My game?MapType?Deathmatch?Number of players?5
     Stored example:
       __GAME_PORT=1235
       __GAME_NAME=My game
       MapType=Deathmatch
       NumberOfPlayer=5
       __System_Address="1.2.4.5"
       __SEC_AFTER_EPOCH_SINCE_LAST_UPDATE=1234567
   - Download:
     The user executes DirectoryServer.php?query=download&downloadPassword=xxx .
     This returns all rows stored that are less than 60 seconds old. The output
     format is the same as the input, except that ASCII value 2 is used to
     separate rows.
     Output example with two rows returned: __GAME_PORT?12345?__GAME_NAME?My game?__SystemAddress?1.2.4.5?__SEC_AFTER_EPOCH_SINCE_LAST_UPDATE?1234567?MapType?Deathmatch?Number of player?5?__GAME_PORT?1236?__GAME_NAME?My game 2?__System_Address?1.2.4.5?__SEC_AFTER_EPOCH_SINCE_LAST_UPDATE?1888888?MapType?Deathmatch?Number of players?3
     Not all entries necessarily have the same number of types of columns.
   - Upload and download:
     The user executes DirectoryServer.php?query=upDown&downloadPassword=xxx&uploadPassword=yyy .
     Query results are prepared the same way as if the user would have executed
     DirectoryServer.php?query=download. Table data is added the same way as if
     the user would have executed DirectoryServer.php?query=upload. The data
     uploaded in this request is skipped for this download request.
   - Expire rows:
     If a row is more than 60 seconds old, the record is removed.
   - Vieweing:
     Viewing the webpage with no commands should display the uploaded entires.
     No password is required for vieweing the webpage.
     Two test applications are provided as part of this sample. The first test
     application repeatedly queries and updates the data over time. The second
     test application is a game that uploads and downloads at the same time the
     game is started.

5.29 Ping
   Description: Simple project demonstrating pinging.

5.30 RackspaceConsole
   Description: Allows to control Rackspace API servers through a console.
   Notes:
   To use RackspaceConsole OPEN_SSL_CLIENT_SUPPORT must be set to 1.

5.31 RakVoice
   Description: Sample project to show how to use the RakVoice class.
   Dependencies:
      - PortAudio (see 2.4.16)
      - speex (see 2.4.19)
   Notes:
   Using speex, the input data is encoded, transmitted using SLikeNet, and then
   decoded again.

5.32 RakVoiceDSound
   Description: Sample project showing how to use Rakvoice together with
                DirectSound.
   Dependencies:
      - Microsoft DirectX SDK (see 2.4.9)
      - speex (see 2.4.19)

5.33 RakVoiceFMOD / RakVoiceFMODAsDLL / RakVoiceFMODUsingDLL
   Description: Sample project showing how to use RakVoice together with FMOD.
   Dependencies:
      - FMOD Ex (see 2.4.3)
      - speex (see 2.4.19)
   Notes:
   Using speex, the input data is encoded, transmitted using SLikeNet, and then
   decoded again.
   FMODVoiceAdapter can be reused for simple integration of FMOD in other
   applications.

5.34 ReadyEvent
   Description: Demonstrates how to use the ReadyEvent plugin (for example to
                have a group of peers all execute a command at the same time).

5.35 ReplicaManager3
   Description: Demonstrates how the ReplicaManager3 class is used to
                distribute and autoserializes objects.

5.36 RoomsPlugin
   Description: Sample to demonstrate using the independent Lobby2 room system.

5.37 Router2
   Description: Shows how to use the Router2 plugin to setup and forward
                connections through an intermediate (already connected to)
                system.

5.38 RPC3
   Description: Demonstrates how to use the RPC3 plugin to issue remote
                procedure calls where the call format is very similar to a
                local function call.
   Dependencies:
      - Boost (see 2.4.1)

5.39 RPC4
   Description: Demonstrates how to use the RPC4 plugin which is a simpler
                 version of the RPC3 plugin without the boost dependency.

5.40 SendEmail
   Description: A sample project to use TCP to connect to a mail host using the
                EmailSender class.

5.41 SteamLobby
   Description: Demonstrates the integration of the Steam lobby and NAT
                traversal sockets.
   Dependencies:
      - Steamworks SDK (see 2.4.21)
   Notes:
   To use SteamLobby, MAXIMUM_MTU_SIZE must be set to 1200.

5.42 TeamManager
   Description: Demonstrates the TeamManager in a typical in-game lobby setting
                with users being able to switch between 3 teams. The sample
                uses the TeamBalancer, ReplicaManager3, and FullyConnectedMesh2
                plugins.
   Notes:
   Before using TeamBalancer and ReplicaManager3, we wait until we know who the
   host is of the session. We do not know this until one other system connects,
   at which point we get ID_FCM2_NEW_HOST. This is the purpose behind the two
   calls to SetAutoManageConnections(). When we do know the host, we call
   RegisterFullyConnectedMesh2Participants() to register all prior connections
   with ReplicaManager3 and TeamBalancer. Once we get
   ID_NEW_INCOMING_CONNECTION and ID_CONNECTION_REQUEST_ACCEPTED while we
   already know the host, we also register those connections with
   PushConnection() and AddParticipant().
   ReplicaManager3 handles object replication to new participants.
   SerializeConstructionExisting() is called on all teams. The User object is
   replicated using SerializeConstruction() to send the initial state data. The
   Team and User classes contain corresponding instances of TM_Team and
   TM_TeamMember, so SerializeConstruction() is called on those instances. We
   reference the Team objects before the User objects with ReplicaManager3
   first in order to ensure that the Team objects are serialized first.
   TeamBalancer requires this, since TM_TeamMember::DeserializeConstruction()
   needs to be able to look up teams in order for these to have been previously
   registered with TeamBalancer and deseralized.
   The setup has one team "REFEREE_TEAM" joinable only through a direct
   request. The other teams are subject to autobalancing.
   Examples of intended operation:
   - If there are two players on team one and no players on team two, when
     autobalancing is turned on the second player will be forced from team one
     to team two.
   - If there are two players on team one and one player on team two, when
     autobalancing is turned on the second player will be forced off team one
     and set to no team.
   - If there are two players on team one and the team limit for team one is
     reduced to 1, the second player to join team one is kicked off.
   - If there is one player on team one, one player on team two, and
     autobalancing is turned on, normally neither player can switch teams
     without the other player leaving first. However, if both players use
     RequestTeamSwitch() to switch to each other's teams, they swap teams.
   - If team one is full or unjoinable due to unbalanced teams, anyone who
     requests to join team one has that team added to their requested list. If
     someone leaves team one, the team size is increased, or team balancing is
     turned off, requesting players join the vacated slots in order of request.

5.43 Timestamping
   Description: Illustrates how to use timestamps.
   Notes:
   Connect to the server and press 'c' or 's' respectively. The time that shows
   up on the remote system should be roughly half your ping.

5.44 TwoWayAuthentication
   Description: Shows how to use the TwoWayAuthentication plugin

5.45 UDP Forwarder
   Description: Demonstrates the UDP Forwarder class usage and how it forwards
                diagrams from one system to another.

5.46 WinPhone8
   Description: Sample for Win Phone 8 integration.
   Dependencies:
      - Microsoft DirectX SDK (see 2.4.9)
   License: Microsoft Permissive License (Ms-PL)
   License file(s): licenses/Microsoft Permissive License.rtf



6. Help and Support

6.1 Documenation
This readme.txt file contains the most up-to-date information and supersedes
any older documentation, in case of contradicting statements.
The changelog.txt covers the changes of the different releases.
Help/Doxygen contains the complete reference manual generated with Doxygen in
Microsoft Compiled HTML Help format (SLikeNetManual.chm) and in html format
(Help/Doxygen/html/index.html).
Help/RakNet contains the documentation which was shipped with RakNet
4.081/4.082 and is provided for cases where updated documentation isn't
available yet.

6.2 Contact Information and Support
We provide different ways to contact us for support requests:
- bulletin board: http://www.slikesoft.com/forum/
- by email: support@slikesoft.com
- contact form: https://www.slikesoft.com/?page_id=187&lang=en
- IRC: #slikenet on irc.freenode.net

For security relevant issues, please use either the contact form or send us a
mail.



7. A word on licensing

SLikeNet is completely open source (including any licensed code or bundled
3rd-party library). This means that you can use SLikeNet free of any charge in
your product (even if it's a commercial product you are making money with).

SLikeNet itself is distributed under the MIT license. You can find the license
in the license.txt provided alongside this readme.txt file.
SLikeNet is however heavily based on RakNet (which is licensed under the
Simplified BSD License). See chapter 7.2.1 for further details.
In addition to that, SLikeNet also contains code licensed under different
licenses/conditions and bundles 3rd-party libraries which also carry their own
licenses.

For an overview of the licenses of bundled 3rd party libraries, please refer to
chapter 2.4. Chapter 7.1 gets into the details on SLikeNet's own license and
chapter 7.2 covers the RakNet license as well as other licensed code (which is
not particularly a 3rd party library).
For help to comply with the license requirements, we provide some quick
licensing instructions, which is explained in chapter 7.1 as well.

7.1 SLikeNet licensing (core and extended)
The SLikeNet core only relies on RakNet licensed code and code/libraries under
public domain or provided under a free license. It does not rely on any
3rd-party library.
This means that to comply to the license requirements the only relevant
licenses are the SLikeNet license (see license.txt in the same directory as
this readme.txt file) and the licenses listed under chapter 7.2 marked with the
(core)-prefix.
This also applies to the prebuilt libraries marked with "_core".

If you are using the prebuilt libraries marked with "_ext" in addition to the
licenses mentioned above, you have to comply to the the OpenSSL license (see
chapter 2.4.15) and the libcatid license (see chapter 2.4.8).

Depending on the core feature you enable, the sample you are using, or the
dependent extension you utilize, additional 3rd-party libraries might be
required. Please see chapter 2.4 for a list of the 3rd-party libraries and
their associated licenses.

If you are distributing the SLikeNet source, we also explicitly permit you to
rename (and move) the license.txt file to a different location within the
package without having to update all the references to the location of the
license.txt file, as long as you make it clear in any accompanying
documentation where to locate the license terms and clarify that the source
code references outdated locations.

In cases where SLikeNet contains modifications to 3rd-party code/libraries, we
provide the modifications under the 3rd-party code's/libraries' own license in
addition to providing these under the MIT license so to allow our modifications
to also being utilized under the same license as the author of the 3rd-party
code/library provided his/her own code for. This is mainly done so to not
enforce additional license requirements, if someone wants to incorporate our
modifications in their own usage of the 3rd party code/library. Where this
applies, the copyright/license header in the particular source code file states
so.

To simplify handling licensing requirements for the majority of the users, we
provide simplified instructions for the two default combinations (core and
extended) SLikeNet is shipped with. These instructions are located under
licenses/_quick_licensing_slikenet_core.txt and
licenses/_quick_licensing_slikenet_extended.txt.

Also we'd like to state that you are not allowed (without prior written
permission from SLikeSoft) to suggest that you, your company, and/or your
product is affiliated with SLikeSoft.

In addition to the licensing requirements, we'd appreciate if you are
considering the following legally NON binding requests:
- send us a short mail (info@slikesoft.com) to let us know that you are using
  our library in your product
- mention in your product / on your webpage that you are using SLikeNet
  (provide a link to https://www.slikenet.com/ on your webpage)
- allow us to put your product/company name on our webpage as a reference that
  you are using SLikeNet

As mentioned: None of these optional requests are binding. If you don't feel
like following any of these requests, we are still glad you decided to use our
network library, nevertheless.

7.2 Licensed Code
This chapter provides an overview of 3rd-party code directly incorporated into
the SLikeNet core.
Unless otherwise noted, license texts are directly located in the corresponding
source code file.

7.2.1 (core) RakNet
The basis of SLikeNet is RakNet (which SLikeNet is derived from). As a result
of this, the RakNet license applies to a big portion of the SLikeNet source
code.
Also the majority of the documentation generated using Doxygen is directly
taken from RakNet and hence the RakNet license applies to this documentation as
well, as it does to the documentation shipped under Help/RakNet. Last but not
least, part of the documentation in sections in this readme file were copied
from the RakNet documentation and slightly modified. These sections are marked
with: "[partially copied from RakNet]" and the RakNet license applies to this
copied/modified documentation as well.
RakNet is licensed under the Simplified BSD License and also comes with the
grant of patent rights.
License file(s): licenses/RakNet License.txt, licenses/RakNet Patents.txt

7.2.2 (core) DR_SHA1.cpp/.h (SHA-1 algorithm - version 2.1)
This is a 100% free public domain implementation of the SHA-1 algorithm by
Dominik Reichl (dominik.reichl@t-online.de) / http://www.dominik-reichl.de/ .

7.2.3 (core) Rand.cpp (Mersenne Twister random number generator MT19937)
This is the 'Mersenne Twister' random number generator MT19937 which generated
pseudorandom integers uniformly distributed in 0..(2^32 -1) starting from any
odd seed in 0..(2^32 -1). It is a recode by Shawn Cokus
(Cokus@math.washington.edu) from March 8th, 1998 of a version by Takuji
Nishimura (who had suggestions from Topher Cooper and Marc Rieffel in
July-August 1997).
The licensing is free: http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/elicense.html
"Until 2001/4/6, MT had been distributed under GNU Public License, but after
2001/4/6, we decided to let MT be used for any purpose, including commercial
use. 2002-versions of mt19937ar.c mt19937ar-cok.c are considered to be usable
freely."
The authors asked to be sent an e-mail to (with an appropriate reference to
your work) to Makoto Matsumoto and Takuji Nishimaru (matumoto@math.keio.ac.jp)
as well as CC Shawn Cokus (Cokus@math.washington.edu).
Note: We failed to contact the authors via these mail addresses. Both addresses
appear to be dead. We keep these mail addresses here for reference,
nevertheless.

7.2.4 (core) KBhit.h
_kbhit() and _getch() implementation for Linux/UNIX by Chris Giese
(geezer@execpc.com) / http://my.execpc.com/~geezer .
His source is public domain.

7.2.5 (core) FindBoost.cmake
Modified version of the FindBoost module shipped with CMake 2.8.10.2
https://cmake.org/ .
The sourcecode is licensed under the Modified BSD License.

7.2.6 (DependentExtension/Autopatcher) ApplyPatch.cpp, CreatePatch.cpp
These source code files which are part of the Autopatcher dependent extension
contain code which is copyright 2003-2005 by Colin Percival and licensed under
the Simplified BSD license.

7.2.7 (DependentExtension/DXTCompressor) OpenGLWindow.hpp
This source code file which is part of the DXTCompressor dependent extension is
based on code written by Jeff Molofee 2000. Acknoledgements go to Frederic
Echols for cleaning up and optimizing the code. It carries no particular
license note but asks to let Jeff Molofee know if the code was found useful
via http://nehe.gamedev.net .

7.2.8 (DependentExtension/IrrlichtDemo) FindIrrlicht.cmake, FindIrrKlang.cmake
CMake modules to locate the corresponding libraries. These files are copyright
(c) 2006 by Andreas Schneider (mail@cynapses.org) and licensed under the New
BSD license.
License file(s): licenses/FindIrrlicht CMake License.txt

7.2.9 (DependentExtension/IrrlichtDemo) CDemo.cpp/.h, CMainMenu.cpp/.h, main.cpp
These are sample files taken from the Irrlicht Engine. The files are copyright
2005-2009 by Nikolaus Gebhardt (actual copyright years vary for each file)
(irrlicht@users.sourceforge.net) / http://irrlicht.sourceforge.net .
The underlying license is based on the zlib/libpng license.
Since the Irrlicht Engine is based in part on the work of the Independent JPEG
Group, zlib, and libpng, you have to also comply to these licenses as well.
It's also asked for (but not legally required) to acknowledge that you use the
Irrlicht Engine, libpng, and zlib in your product.
License file(s): licenses/Irrlicht Engine License.txt,
                 licenses/jpglib license v8d.txt, license/libpng license.txt,
                 licenses/zlib license.txt

7.2.10 (DependentExtension/speex related) FindSpeex.cmake, FindSpeexDSP.cmake
CMake modules to locate the corresponding libraries. These files are copyright
(c) 2006 by Andreas Schneider (mail@cynapses.org) and licensed under the New
BSD license.
License file(s): licenses/FindIrrlicht CMake License.txt

7.2.11 (DependentExtension/Swig) arrays_csharp.i
SWIG library file containing a two approaches to marshalling arrays. Being a
file located inside the Lib directory of the SWIG library, no particular
license applies. The software is free to be used on any terms one wishes. Since
the original file contains a license reference, we put the license note into
the licenses-directory, nevertheless.
License file(s): licenses/SWIG library files license.txt

7.2.12 (Samples/nacl_sdk) httpd.py
This file was taken from the Native Client SDK and is Copyright (c) 2012 The
Chromium Authors. It is provided under the Modified BSD License.
License file(s): licenses/nacl license.txt

7.2.13 (Samples/Ogre3D related) FindOGRE.cmake, FindOIS.cmake, FindPkgMacros.cmake, PreprocessorUtils.cmake
CMake modules to locate the corresponding libraries. The source files are part
of OGRE (Object-oriented Graphics Rendering Engine) http://www.ogre3d.org/ .
They are provided as public domain.

7.2.14 (Samples/Ogre3D related) BspCollision.cpp
This is a sample file to demonstrate integration into Ogre3D. The source file
is part of OGRE (Object-oriented Graphics Rendering Engine)
http://www.ogre3d.org/ and Copyright (c) 2000-2006 Torus Knot Software Ltd. It
is provided completely free without an explicit license requirement.



8. Thanks / Acknowledgments

First of all we'd like to thank Kevin Jenkins for his year long work on RakNet.
Without his work SLikeNet wouldn't have seen the light of day at all.
Second, we'd like to thank Oculus VR, LLC. which put the RakNet source code
under the Simplified BSD License. Without having done that, it would have been
impossible for us to continue the effort which went into the RakNet library.

Further, we'd like to thank the following contributors who handed in pull
requests to the RakNet project on GitHub which are incorporated in SLikeNet:
- Alex Howland: https://github.com/alliekins (pull request: RAKNET_48)
- AlιAѕѕaѕѕιN: https://github.com/0x416c69 (pull requests: SLNET_30)
- GBearUK: https://github.com/GBearUK (pull request: RAKNET_67)
- Hunter Mayer: https://github.com/orionnoir (pull request: RAKNET_31)
- Ian Clarkson: https://github.com/aardvarkk (pull request: RAKNET_84)
- Jalmari Ikävalko: https://github.com/tzaeru (pull request: RAKNET_56)
- jaynus: https://github.com/jaynus (pull request: RAKNET_64)
- lenky0401: https://github.com/lenky0401 (pull request: RAKNET_60)
- Peter Hille: https://github.com/png85 (pull request: RAKNET_7)
- Rhys Kidd:  https://github.com/Echelon9 (pull requests: RAKNET_10 and RAKNET_14)
- TheComet: https://github.com/TheComet (pull request: RAKNET_29)
- Tim Ullrich: https://github.com/tullrich (pull request: RAKNET_63)
- Tobias Kahlert: https://github.com/SrTobi (pull requests: RAKNET_51, RAKNET_54, and RAKNET_57)
- Viktor Korsun: https://github.com/bitekas (pull request: RAKNET_80)

We'd also like to thank those contributors who have requested to remain
anonymous and/or those who we could not contact at all (due to lack of contact
information).
If you spot your contribution in our library and haven't been mentioned in the
acknowledgment section, simply send us a mail and we'll update the section as
soon as possible.

Last but not least, we also acknowledge all the work of the developers and
companies related to incorporated/depending 3rd-party libraries (see chapter
2.4) and code snippets (see chapter 7.2).

To comply with the license requirements, we further list these acknowledgment
statements:
This product includes software developed by the OpenSSL Project for use in the
OpenSSL Toolkit. (http://www.openssl.org/)
This product includes cryptographic software written by Eric Young
(eay@cryptsoft.com)
This product includes software written by Tim Hudson (tjh@cryptsoft.com)
this software is based in part on the work of the Independent JPEG Group
This software contains source code provided by NVIDIA Corporation.



8. Donations

We provide SLikeNet completely free of charge and fully rely on donations.

If you are happy with the library and want to support its further development,
we would appreciate a donation so we can at least to some degree cover the
running costs.

To make a donation, head over to the donation page on our webpage at
https://www.slikesoft.com/?page_id=1437&lang=en which provides additional
details on benefits for donors and transparency on how we spend the money on
the project.



9. Trademark Notes / Affiliation Statement

Neither SLikeNet nor SLikeSoft is affiliated in any means to any company or
other 3rd-party product mentioned in either the source code or the accompanying
documentation. Mentioning of product and company names are solely done for the
purpose of referencing the actual 3rd-part product or its associated company.

While we tried hard to take best care for properly handling trademarks and
follow each trademark holder's guideline with appropriate usage of their
property, we can't rule out that some trademark slipped by and didn't get
referenced below. Hence, please understand that this list has no obligation of
being complete. If a name is not listed in this section or you spot a mistake
of how use the trademark we'd appreciate to be dropped a note so we can correct
the mistake/oversight.

In general we mark trademarks with ™ and registered trademarks with ® upon
first use of the trademark. Any following usages of the same trademark implies
the corresponding trademark symbol.

Subversion is a registered trademark of the Apache Software Foundation
iPhone and Xcode are registered trademarks of Apple Inc.
Autodesk and Scaleform are registered trademarks of Autodesk, Inc.
FMOD is a registered trademark of Firelight Technologies Pty Ltd.
GITHUB is a registered trademark of GitHub, Inc.
libpng is a trademark of Glenn Randers-Pehrson
Android is a trademark of Google Inc.
SQLite is a registered trademark of Hipp, Wyrick & Company, Inc
Linux® is the registered trademark of Linus Torvalds in the U.S. and other
countries.
CMake is a registered trademark of Kitware, Inc.
DirectX, Windows Vista,  Windows Phone, and Xbox 360 are registered trademarks
of Microsoft Corporation.
Microsoft, Visual Studio, and Windows are trademarks of Microsoft Corporation.
MySQL is a registered trademark of MySQL AB
NVIDIA is a registered trademark of NVIDIA Corporation
OpenSSL is a registered trademark of the OpenSSL Software Foundation, Inc.
SLikeSoft and SLikeNet are trademarks of SLikeSoft UG (haftungsbeschränkt)
GIT is a registered trademark of Software Freedom Conservancy, Inc.
Playstation is a registered trademark of Sony Interactive Entertainment Inc.
PostgreSQL is a registered trademark of the PostgreSQL Community Association of
Canada
Steam and Steamworks are registered trademarks of Valve Corporation.