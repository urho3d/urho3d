**This repository is now focused on Russian-speaking community only.
If you were looking for international versions of Urho3D, check out:**

* [Urho3D 1.9.0](https://github.com/urho3d/Urho3D/releases/tag/1.9.0): Last English version of Urho3D, unmaintained.

* [Rebel Fork](https://github.com/rbfx/rbfx): Reimagining of Urho3D with significant API changes, in active development.

* [U3D Community](https://github.com/u3d-community/U3D): Urho3D 1.8.0, in maintenance mode.

Sincerely yours, [Eugene Kozlov](https://github.com/eugeneko) (Rebel Fork developer)

---

Other forks:

* https://github.com/Urho-Net/Urho.Net
* https://gitlab.com/luckeyproductions/dry
* https://github.com/xamarin/urho
* https://github.com/AtomicGameEngine/AtomicGameEngine

---

# Urho3D

[![CI/CD](https://github.com/urho3d/Urho3D/workflows/CI/CD/badge.svg)](https://github.com/urho3d/Urho3D/actions?query=workflow%3ACI%2FCD)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/4954/badge.svg)](https://scan.coverity.com/projects/urho3d-urho3d)

**Urho3D** - это легковесный, кроссплатформенный 2D и 3D игровой движок, написанный на C++ и опубликованный под лицензией MIT.

## Лицензия

Urho3D распространяется под лицензией MIT.

Тексты лицензий:
* [Проект Urho3D](licenses/urho3d/LICENSE)
* [Третьесторонние библиотеки](licenses)

Папку [licenses](licenses) удобно распространять вместе с игрой.

## Важные ссылки:

* [Документация, сгенерированная Doxygen](https://urho3d-doxygen.github.io)
* [Форум](https://github.com/urho3d-community/discussions/discussions)
* [Wiki](https://github.com/urho3d-community/wiki/wiki)
* [Архив англоязычной Wiki](https://github.com/urho3d-community/wiki-archive/wiki)
* [Обучающие материалы](https://github.com/urho3d-learn)

## Авторы проекта

Основателем проекта является [Lasse Öörni](https://github.com/cadaver). Огромный вклад в развитие проекта также внесли
[Yao Wei Tjong](https://github.com/weitjong), [asterj](https://github.com/aster2013)
и многие другие разработчики, список которых можно посмотреть [тут](https://github.com/urho3d/Urho3D/graphs/contributors).

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

Latest documentation: <https://rurho3d.github.io>

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
