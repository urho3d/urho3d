This is a simple application with a fairly static world and camera control,
world raycasting to the cursor position, and controls to toggle the rendering
options during runtime.


Controls:

W A S D     - Move
Left MB     - Shoot physics object
Right MB    - Camera rotation (hold down)
1           - Toggle deferred, light prepass & forward rendering
2           - Cycle texture quality
3           - Cycle material quality
4           - Toggle specular lighting
5           - Toggle shadows
6           - Cycle shadow map resolution
7           - Toggle shadow map depth resolution
8           - Toggle software occlusion
F           - Toggle edge filtering (deferred rendering only)
L           - Detach/attach camera spotlight
O           - Toggle occlusion buffer debug display
P           - Toggle scene animation
T           - Toggle profiler
Space       - Cycle debug geometry mode (none, renderer, physics)
Alt-Enter   - Toggle fullscreen/windowed

Commandline options:

-x<res>     - Horizontal resolution
-y<res>     - Vertical resolution
-m<level>   - Multisampling level
-w          - Start windowed
-v          - Enable vsync
-forward    - Start with forward rendering
-prepass    - Start with light prepass rendering
-sm2        - Force Shader Model 2.0 rendering

Note: when multisampling is specified with deferred rendering, it enables an
edge filtering postprocess instead of true hardware multisampling.