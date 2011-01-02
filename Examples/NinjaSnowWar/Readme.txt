NinjaSnowWar is a simple third person action game that demostrates the use of
Urho3D. The game was originally written in 2007 for a Computer Science minor
degree thesis, and back then it used OGRE, ODE & OgreODE libraries. Because
it's a port/reimplementation from those libraries, the code may not in parts
be fully "idiomatic" of Urho3D, and so care is advised when using it for
learning purposes. More/better examples hopefully to come!

The sound assets for this game come from another university course and game
project (The Interesting Adventures of Toy XYZ aka Lelupeli) and were done by
Veli-Pekka Tätilä.

Note: due to the simplicity of the scene, NinjaSnowWar uses forward rendering
by default for better performance.

Default mode is to start a singleplayer game; co-op multiplayer can be enabled
by commandline options (see below.)


Controls:

W A S D     - Move
Left MB     - Shoot
Space       - Jump
F           - Toggle edge filtering (deferred rendering only)
P           - Toggle pause (singleplayer only)
X           - Cycle packet loss test mode 0% - 33% - 66% (multiplayer only)
Z           - Cycle lag test mode 0 ms - 150 ms - 500 ms (multiplayer only)
F1          - Toggle profiler
F2          - Toggle physics debug geometry
F5          - Quicksave (singleplayer only)
F7          - Quickload (singleplayer only)
Alt-Enter   - Toggle fullscreen/windowed


Commandline options:

server      - Start a server
<address> [username] - connect to a server
-x<res>     - Horizontal resolution
-y<res>     - Vertical resolution
-m<level>   - Multisampling level
-w          - Start windowed
-v          - Enable vsync
-deferred   - Force deferred rendering
-prepass    - Force light prepass rendering
-sm2        - Force Shader Model 2.0 rendering
-nolimit    - Disable FPS limiter
-noshadows  - Disable shadows
-nosound    - Disable sound
