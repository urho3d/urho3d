This is a shell for running script-based Urho3D examples. Usage:
Urho3D <scriptfile | scenefile> [options]

Either a script file or a scene file can be specified. The script file should
implement the function void start(), which should in turn subscribe to all 
necessary events, such as the application update. If a scene is loaded, it 
should contain script objects to implement the application logic.


Commandline options:

-x<res>     - Horizontal resolution
-y<res>     - Vertical resolution
-m<level>   - Multisampling level
-w          - Start windowed
-v          - Enable vsync
-r<mixrate> - Sound mixrate in Hz, default 44100
-forward    - Start with forward rendering
-prepass    - Start with light prepass rendering
-mono       - Force mono sound output
-8bit       - Force 8-bit sound output
-noip       - Force non-interpolated sound mixing
-nosound    - Disable sound
-nolimit    - Disable FPS limiter
-noshadows  - Disable shadows
-headless   - Disable the rendering window
-sm2        - Force Shader Model 2.0 rendering
