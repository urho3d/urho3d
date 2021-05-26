![Urho3D logo](https://raw.githubusercontent.com/urho3d/Urho3D/master/bin/Data/Textures/LogoLarge.png)

# Urho3D

[![CI/CD](https://github.com/urho3d/Urho3D/workflows/CI/CD/badge.svg)](https://github.com/urho3d/Urho3D/actions?query=workflow%3ACI%2FCD)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/4954/badge.svg)](https://scan.coverity.com/projects/urho3d-urho3d)

**Urho3D** is a free lightweight, cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license. Greatly inspired by OGRE and Horde3D.

Main website: [https://urho3d.io/](https://urho3d.io/)

## License
Licensed under the MIT license, see [LICENSE](https://github.com/urho3d/Urho3D/blob/master/LICENSE) for details.

## Contributing
Before making pull requests, please read the [Contribution checklist](https://urho3d.io/documentation/HEAD/_contribution_checklist.html) and [Coding conventions](https://urho3d.io/documentation/HEAD/_coding_conventions.html) pages from the documentation.

## Credits

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
- AngelScript 2.35.1 WIP (http://www.angelcode.com/angelscript)
- Boost 1.75.0 (http://www.boost.org) - only used for AngelScript generic bindings
- Box2D 2.3.2 WIP (http://box2d.org)
- Bullet 3.06+ (http://www.bulletphysics.org)
- Civetweb 1.7 (https://github.com/civetweb/civetweb)
- FreeType 2.8 (https://www.freetype.org)
- GLEW 1.13.0 (http://glew.sourceforge.net)
- SLikeNet (https://github.com/SLikeSoft/SLikeNet)
- libcpuid 0.4.0+ (https://github.com/anrieff/libcpuid)
- Lua 5.1 (https://www.lua.org)
- LuaJIT 2.1.0+ (http://www.luajit.org)
- LZ4 1.7.5 (https://github.com/lz4/lz4)
- MojoShader (https://icculus.org/mojoshader)
- Mustache 1.0 (https://mustache.github.io, https://github.com/kainjow/Mustache)
- nanodbc 2.12.4+ (https://lexicalunit.github.io/nanodbc)
- Open Asset Import Library 4.1.0 (http://assimp.sourceforge.net)
- pugixml 1.10+ (http://pugixml.org)
- rapidjson 1.1.0 (https://github.com/miloyip/rapidjson)
- Recast/Detour (https://github.com/recastnavigation/recastnavigation)
- SDL 2.0.10+ (https://www.libsdl.org)
- SQLite 3.20.1 (https://www.sqlite.org)
- StanHull (https://codesuppository.blogspot.com/2006/03/john-ratcliffs-code-suppository-blog.html)
- stb_image 2.18 (https://nothings.org)
- stb_image_write 1.08 (https://nothings.org)
- stb_rect_pack 0.11 (https://nothings.org)
- stb_vorbis 1.13b (https://nothings.org)
- tolua++ 1.0.93 (defunct - http://www.codenix.com/~tolua)
- WebP (https://chromium.googlesource.com/webm/libwebp)
- ETCPACK (https://github.com/Ericsson/ETCPACK)
- Tracy 0.7.6 (https://github.com/wolfpld/tracy)

DXT / PVRTC decompression code based on the Squish library and the Oolong
Engine.
Jack and mushroom models from the realXtend project. (https://www.realxtend.org)
Ninja model and terrain, water, smoke, flare and status bar textures from OGRE.
BlueHighway font from Larabie Fonts.
Anonymous Pro font by Mark Simonson.
NinjaSnowWar sounds by Veli-Pekka Tätilä.
PBR textures from Substance Share. (https://share.allegorithmic.com)
IBL textures from HDRLab's sIBL Archive.
Dieselpunk Moto model by allexandr007.
Mutant & Kachujin models from Mixamo.
License / copyright information included with the assets as necessary. All other assets (including shaders) by Urho3D authors and licensed similarly as the engine itself.

## Documentation
Urho3D classes have been sparsely documented using Doxygen notation. To
generate documentation into the "Docs" subdirectory, open the Doxyfile in the
"Docs" subdirectory with doxywizard and click "Run doxygen" from the "Run" tab.
Get Doxygen from http://www.doxygen.org & Graphviz from http://www.graphviz.org.
See section "Documentation build" below on how to automate documentation
generation as part of the build process.

The documentation is also available online at
  https://urho3d.io/documentation/HEAD/index.html

Documentation on how to build Urho3D:
  https://urho3d.io/documentation/HEAD/_building.html
Documentation on how to use Urho3D as external library
  https://urho3d.io/documentation/HEAD/_using_library.html

Replace HEAD with a specific release version in the above links to obtain the
documentation pertinent to the specified release. Alternatively, use the
document-switcher in the documentation website to do so.

## History
The change history is available online at
  https://urho3d.io/documentation/HEAD/_history.html
