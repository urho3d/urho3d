-----------------------------------------------------------------------------------
File change list
-----------------------------------------------------------------------------------
* tb_renderer_batcher.h - added TBRect clipRect member variable in Batch class
* tb_renderer_batcher.cpp - in AddQuadInternal(), batch triangle winding order is changed to clock-wise, and also
                            the batch.clipRect member variable is populated in that func

* test_tb_parser.cpp - changed TB_TEST_FILE("test_tb_parser.tb.txt") to hardcode path "demo01/ui_resources/test_tb_parser.tb.txt"

* tb_config.h - changed TB_FILE_WINDOWS for windows

-----------------------------------------------------------------------------------
Turbo Badger - Fast UI toolkit for hardware accelerated games & applications.
-----------------------------------------------------------------------------------

I created Turbo Badger because i wanted a small UI toolkit for use in games and
hardware accelerated applications across multiple platforms (that target both
desktop and mobile).

The goal is a toolkit that can be easily integrated into an existing codebase to
make UI with skinning.

It has no dependency on stl, RTTI or exceptions. Compiling without these features
makes footprint very small. Utility classes (such as string, lists, hash table,
etc.) are quite minimal for the basic needs of Turbo Badger itself.

See [integration.txt](integration.txt) for details about integrating image loading,
renderer, font system etc.


BETA notice
-----------------------------------------------------------------------------------

APIs are changed, features improved & added. Be aware that if you use this right
now, you'll probably have to adjust your code to API changes sometimes after
pulling master. Documentation about API changes take place in the git commit
changelog for now ;)


License
-----------------------------------------------------------------------------------

This software is provided 'as-is', without any express or implied warranty. In no
event will the authors be held liable for any damages arising from the use of this
software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to the
following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim
  that you wrote the original software. If you use this software in a product,
  an acknowledgment in the product documentation would be appreciated but is not
  required.

  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.


What features does it have
-----------------------------------------------------------------------------------

Core:

  * Widgets (many common standard widgets)
  * Text editing widget (With clipboard, undo/redo, styling functionality,
    embedded content (read only)...)
  * Extendable skin system with automatic runtime atlas creation,
    Expand (shadows & glow without nasty margin hacks),
    conditions (simple selectors), overrides, overlays, children, multiple
    pixel density support etc.
  * Automatic widget layout (No need to specify widget dimensions by pixels)
  * Text based UI resource format, supporting conditions etc.
  * Keyboard friendly (tab focus etc.)
  * Message handling, with delayed/timed messages.
  * All containers are scrollable/pannable (automatically from mouse/finger
    interaction, and following focus).
  * Very failproof event handling.
  * Widget connections (synchronize multiple widgets with "widget-values")
  * Language string handling
  * No dependency on stl, exceptions, RTTI
  * Very portable & easy to implement new backends (Image loading, fonts,
    renderer)
  * Support 32/64bit architectures and tested on Windows/Linux/Mac/iOS/Android
  * Uses constexpr by default for all ID comparisions on compilers that support
    it.
  * Unicode support (UTF8)
  * Multiple font systems can be used (Implementations of TBBF, freetype and stbf
    provided)
  * Animation system.
  * Unit tests.


The code design & developing Turbo Badger
-----------------------------------------------------------------------------------

If you try to familiarize yourself with the code, you might notice the heavily used
object `TBID` that may seem like a string. It's actually an uint32 that can be set
from a string (using the strings hash value). It's used for hash keys, as
substitute for enums and all kind of things needing custom IDs.

With compilers supporting C++ 11 `constexpr`, the string to integer conversion is
done compile time.

If you want to add new stuff, here are some hints that will make it easier to get a
pull requests accepted:

  * Do not make it dependant on exceptions, RTTI or stl (or boost or similar)

  * It should not leak or crash if running out of memory.

  * Follow the used code style (4 spaces wide tabs, indentation & whitespace style,
    documentation etc.)

  * Features that may be optional should be optional and not tied to the core.


Creating custom widgets
-----------------------------------------------------------------------------------

Widgets are cheap to create and layout and using many widgets to get what you want
is encouraged. A custom widget should typically not implement any layouting and
drawing of sub-elements if it can be solved by wrapping a TBLayout and other
existing widgets.

Any widget may contain other widgets and may control into which sub-widget other
widgets are inflated from resources (using `TBWidget::GetContentRoot`).

Custom widgets can be inflated from UI resources too. See the use of the
`TB_WIDGET_FACTORY` macro in `tb_widgets_reader.cpp` for examples on how to do
this.


Building the demo
-----------------------------------------------------------------------------------

The demo use GLFW as a submodule for some platform window & input handling.
After the first git clone, you need to run:

	git submodule init
	git submodule update

This will clone GLFW into the right directory.

There is project files for Visual Studio 2012 in Demo/VisualStudio.
For other platforms/compilers, you need to first run cmake to generate makefile or
projects for your favorite IDE.

There's a Sublime Text project for a small Android test app in DemoAndroid with a
custom build & deploy script (Windows .bat file. There's currently no Linux/Mac
scripts).


Author
-----------------------------------------------------------------------------------

Emil Segerås
Web: <http://fiffigt.com>  

Turbo Badger home: <https://github.com/fruxo/turbobadger>  


Screenshot
-----------------------------------------------------------------------------------

Some of the windows in the Demo application for desktop, using the default skin.

![Default skin](Demo/screenshot/screenshot_01.png)
