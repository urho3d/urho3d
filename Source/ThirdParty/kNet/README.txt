   Welcome to kNet!

kNet is a low-level networking protocol library designed for bit-efficient realtime streaming of custom application-specified messages on top of TCP or UDP. kNet is written in C++.


   Supported Platforms.

kNet has been tested to build on the following platforms:
 - Windows 7 & Visual Studio 2010 Professional
 - Windows 7 & Visual Studio 2008 Standard
 - Ubuntu 9.04 & GCC 4.4.1
 - Windows 7 & MinGW GCC 4.6.1 versioned 20111118 (beware though, MinGW is not actively supported)

 
   Documentation.
 
kNet uses doxygen to generate its documentation. See the web page http://clb.demon.fi/knet/ for an online hosted copy.
 
 
   Building kNet.

kNet uses cmake (2.6 or newer) as its build system. On Linux it can use pthreads or boost v1.38.0 or newer for threading support. On Windows a CMake flag USE_BOOST can be used to specify whether to depend on boost or not. By default USE_BOOST is on.

kNet can optionally use Qt to provide a debugging and statistics window for profiling and simulation of different network conditions.

Steps:
 1. Install cmake. 
 2a. Optional: Install and build Boost. Edit the root CMakeLists.txt to specify the source directory to boost path.
 2b. If you do not want to use Boost, edit the root CMakeLists.txt and comment out the USE_BOOST directive. If Boost is not used, kNet will utilize native threading APIs on each platform (WIN32 CreateThread or POSIX threads). There are no functional differences with using either.
 3. Optional: If you do not want to use TinyXML, edit the root CMakeLists.txt and make sure the USE_TINYXML directive is commented out. This will disable the functionality of SerializedMessageList/MessageListParser though. 
 4. Optional: kNet can use Qt to provider debug statistics and profiling windows. Install and build Qt (4.6.2 or newer recommended) and uncomment #set(USE_QT TRUE) in the root CMakeLists.txt.
 5a. Windows VS2008: Execute in project root folder the command 'cmake -G "Visual Studio 9"' (case sensitive!), or click on the cmake_vs2008.bat.
 5b. Windows VS2010: Execute in project root folder the command 'cmake -G "Visual Studio 10"' (case sensitive!), or click on the cmake_vs2010.bat.
 5c. Linux and Mac: Run 'cmake .' in kNet root folder.
 6. If CMake fails to find your Qt installation, or if you want to explicitly specify the source location, set the QMAKESPEC and QTDIR environment variables or alter the cmake_vs2008.bat/cmake_vs2010.bat files.
 7a. Windows: Open and build the kNet.sln.
 7b. Linux and Mac: Run 'make'.

The project output files are placed in the directory kNet/lib.


   Contributors.

The following people have contributed to the project:

   Toni Alatalo
   Jukka Jylänki
   Erno Kuusela
   Ali Kämäräinen
   Jonne Nauha
   Ville Saarinen
   Cvetan Stefanovski
   Kari Vatjus-Anttila
   Lasse Öörni

   
   Links.

The kNet repository is hosted at github: https://github.com/juj/kNet. Please report bugs using the github issue tracker.
There exists a Wireshark dissector plugin for kNet: http://chiru.cie.fi/chiru-sharedfolder/knet-tundra-v.0.0.8.tar.gz .
A SCTP -enabled branch of kNet is being developed at https://bitbucket.org/karivatj/knet-sctp/ .
