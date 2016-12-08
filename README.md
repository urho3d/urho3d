![Urho3D logo](https://raw.githubusercontent.com/urho3d/Urho3D/master/bin/Data/Textures/LogoLarge.png)

#Urho3D

[![Join the chat at https://gitter.im/urho3d/Urho3D](https://badges.gitter.im/urho3d/Urho3D.svg)](https://gitter.im/urho3d/Urho3D?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

**Urho3D** is a free lightweight, cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license. Greatly inspired by OGRE and Horde3D.

Main website: [https://urho3d.github.io/](https://urho3d.github.io/)

##License
Licensed under the MIT license, see [LICENSE](https://github.com/urho3d/Urho3D/blob/master/LICENSE) for details.

##Credits
Urho3D development, contributions and bugfixes by:
- Lasse Öörni (loorni@gmail.com, AgentC at GameDev.net)
- Wei Tjong Yao
- Aster Jian
- Vivienne Anthony
- Colin Barrett
- Erik Beran
- Gauthier Billot
- Loic Blot
- Danny Boisvert
- Sergey Bosko
- Carlo Carollo
- Pete Chown
- Christian Clavet
- Sebastian Delatorre (primitivewaste)
- Josh Engebretson
- Chris Friesen
- Alex Fuller
- Henrik Heino
- Mika Heinonen
- Victor Holt
- Johnathan Jenkins
- Jukka Jylänki
- Graham King
- Jason Kinzer
- Eugene Kozlov
- Gunnar Kriik
- Aliaksandr Kryvashein
- Artem Kulyk
- Rokas Kupstys
- Ali Kämäräinen
- Pete Leigh
- Frode 'Modanung' Lindeijer
- Thorbjørn Lindeijer
- Nathanial Lydick
- Xavier Maupeu
- Jonne Nauha
- Paul Noome
- David Palacios
- Alex Parlett
- Jordan Patterson
- Anton Petrov
- Vladimir Pobedinsky
- Franck Poulain
- Pranjal Raihan
- Nick Royer
- Miika Santala
- Anatoly Sennov
- Matan Shukry
- Bengt Soderstrom
- Hualin Song
- James Thomas
- Joshua Tippetts
- Yusuf Umar
- Daniel Wiberg
- Steven Zhang
- AGreatFish
- BlueMagnificent
- Enhex
- Fastran
- Firegorilla
- Gordon-F
- Lumak
- Magic.Lixin
- Mike3D
- MonkeyFirst
- Ner'zhul
- Newb I the Newbd
- OvermindDL1
- Scellow
- Skrylar
- TheComet93
- Y-way
- 1vanK
- andmar1x
- amadeus_osa
- atship
- att
- celeron55
- cosmy1
- damu
- dragonCASTjosh
- feltech
- fredakilla
- hdunderscore
- lvshiling
- marynate
- mightyCelu
- neat3d
- nemerle
- ninjastone
- proller
- raould
- rasteron
- reattiva
- rifai
- rikorin
- skaiware
- ssinai1
- svifylabs
- szamq
- thebluefish
- tommy3
- yushli

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
  https://www.geometrictools.com/Documentation/EulerAngles.pdf
- Red Black Trees by Julienne Walker
  http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx
- Comparison of several sorting algorithms by Juha Nieminen
  http://warp.povusers.org/SortComparison/

Urho3D uses the following third-party libraries:
- AngelScript 2.30.2 (http://www.angelcode.com/angelscript)
- Boost 1.61.0 (http://www.boost.org) - only used for AngelScript generic bindings
- Box2D 2.3.0 (http://box2d.org)
- Bullet 2.83.6 (http://www.bulletphysics.org)
- Civetweb 1.7 (https://github.com/civetweb/civetweb)
- FreeType 2.5.0 (https://www.freetype.org)
- GLEW 1.13.0 (http://glew.sourceforge.net)
- jo_jpeg 1.52 (http://www.jonolick.com/uploads/7/9/2/1/7921194/jo_jpeg.cpp)
- kNet (https://github.com/juj/kNet)
- libcpuid 0.2.2 (https://github.com/anrieff/libcpuid)
- Lua 5.1 (https://www.lua.org)
- LuaJIT 2.1.0+ (http://www.luajit.org)
- LZ4 r131 (https://github.com/Cyan4973/lz4)
- MojoShader (https://icculus.org/mojoshader)
- Mustache 1.0 (https://mustache.github.io, https://github.com/kainjow/Mustache)
- nanodbc 2.12.4 (https://lexicalunit.github.io/nanodbc)
- Open Asset Import Library (http://assimp.sourceforge.net)
- pugixml 1.7 (http://pugixml.org)
- rapidjson 0.11 (https://code.google.com/p/rapidjson)
- Recast/Detour (https://github.com/memononen/recastnavigation)
- SDL 2.0.5 (https://www.libsdl.org)
- SQLite 3.13.0 (https://www.sqlite.org)
- StanHull (https://codesuppository.blogspot.com/2006/03/john-ratcliffs-code-suppository-blog.html)
- stb_image 2.12 (https://nothings.org)
- stb_image_write 1.02 (https://nothings.org)
- stb_rect_pack 0.08 (https://nothings.org)
- stb_vorbis 1.09 (https://nothings.org)
- tolua++ 1.0.93 (defunct - http://www.codenix.com/~tolua)

DXT / ETC1 / PVRTC decompression code based on the Squish library and the Oolong
Engine.
Jack and mushroom models from the realXtend project. (https://www.realxtend.org)
Ninja model and terrain, water, smoke, flare and status bar textures from OGRE.
BlueHighway font from Larabie Fonts.
Anonymous Pro font by Mark Simonson.
NinjaSnowWar sounds by Veli-Pekka Tätilä.
PBR textures from Substance Share. (https://share.allegorithmic.com)
IBL textures from HDRLab's sIBL Archive.
Dieselpunk Moto model by allexandr007.
Mutant model from Mixamo.

##Documentation
Urho3D classes have been sparsely documented using Doxygen notation. To
generate documentation into the "Docs" subdirectory, open the Doxyfile in the
"Docs" subdirectory with doxywizard and click "Run doxygen" from the "Run" tab.
Get Doxygen from http://www.doxygen.org & Graphviz from http://www.graphviz.org.
See section "Documentation build" below on how to automate documentation
generation as part of the build process.

The documentation is also available online at
  https://urho3d.github.io/documentation/HEAD/index.html

Documentation on how to build Urho3D:
  https://urho3d.github.io/documentation/HEAD/_building.html
Documentation on how to use Urho3D as external library
  https://urho3d.github.io/documentation/HEAD/_using_library.html

Replace HEAD with a specific release version in the above links to obtain the
documentation pertinent to the specified release. Alternatively, use the
document-switcher in the documentation website to do so.

##History
The change history is available online at
  https://urho3d.github.io/documentation/HEAD/_history.html
