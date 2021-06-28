// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Generated_Includes.h"

// Some headers could re-define M_PI, ensure that it's undefined
#undef M_PI

namespace Urho3D
{

void ASRegisterGeneratedGlobalVariables(asIScriptEngine* engine)
{
    // static const float ANIMATION_LOD_BASESCALE | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const float ANIMATION_LOD_BASESCALE", (void*)&ANIMATION_LOD_BASESCALE);

    // static const int BITS_PER_COMPONENT | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const int BITS_PER_COMPONENT", (void*)&BITS_PER_COMPONENT);

    // static const int COLOR_LUT_SIZE | File: ../Resource/Image.h
    engine->RegisterGlobalProperty("const int COLOR_LUT_SIZE", (void*)&COLOR_LUT_SIZE);

    // static const int CONVERSION_BUFFER_LENGTH | File: ../Container/Str.h
    engine->RegisterGlobalProperty("const int CONVERSION_BUFFER_LENGTH", (void*)&CONVERSION_BUFFER_LENGTH);

    // static const unsigned DEBUGHUD_SHOW_ALL | File: ../Engine/DebugHud.h
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_ALL", (void*)&DEBUGHUD_SHOW_ALL);

    // static const unsigned DEBUGHUD_SHOW_EVENTPROFILER | File: ../Engine/DebugHud.h
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_EVENTPROFILER", (void*)&DEBUGHUD_SHOW_EVENTPROFILER);

    // static const unsigned DEBUGHUD_SHOW_MEMORY | File: ../Engine/DebugHud.h
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_MEMORY", (void*)&DEBUGHUD_SHOW_MEMORY);

    // static const unsigned DEBUGHUD_SHOW_MODE | File: ../Engine/DebugHud.h
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_MODE", (void*)&DEBUGHUD_SHOW_MODE);

    // static const unsigned DEBUGHUD_SHOW_NONE | File: ../Engine/DebugHud.h
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_NONE", (void*)&DEBUGHUD_SHOW_NONE);

    // static const unsigned DEBUGHUD_SHOW_PROFILER | File: ../Engine/DebugHud.h
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_PROFILER", (void*)&DEBUGHUD_SHOW_PROFILER);

    // static const unsigned DEBUGHUD_SHOW_STATS | File: ../Engine/DebugHud.h
    engine->RegisterGlobalProperty("const uint DEBUGHUD_SHOW_STATS", (void*)&DEBUGHUD_SHOW_STATS);

    // static const float DEFAULT_CAMERA_FOV | File: ../Graphics/Camera.h
    engine->RegisterGlobalProperty("const float DEFAULT_CAMERA_FOV", (void*)&DEFAULT_CAMERA_FOV);

    // static const float DEFAULT_FARCLIP | File: ../Graphics/Camera.h
    engine->RegisterGlobalProperty("const float DEFAULT_FARCLIP", (void*)&DEFAULT_FARCLIP);

    // static const float DEFAULT_FONT_SIZE | File: ../UI/Text.h
    engine->RegisterGlobalProperty("const float DEFAULT_FONT_SIZE", (void*)&DEFAULT_FONT_SIZE);

    // static const unsigned DEFAULT_LIGHTMASK | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DEFAULT_LIGHTMASK", (void*)&DEFAULT_LIGHTMASK);

    // static const float DEFAULT_NEARCLIP | File: ../Graphics/Camera.h
    engine->RegisterGlobalProperty("const float DEFAULT_NEARCLIP", (void*)&DEFAULT_NEARCLIP);

    // static const unsigned DEFAULT_NUM_PARTICLES | File: ../Graphics/ParticleEffect.h
    engine->RegisterGlobalProperty("const uint DEFAULT_NUM_PARTICLES", (void*)&DEFAULT_NUM_PARTICLES);

    // static const float DEFAULT_ORTHOSIZE | File: ../Graphics/Camera.h
    engine->RegisterGlobalProperty("const float DEFAULT_ORTHOSIZE", (void*)&DEFAULT_ORTHOSIZE);

    // static const unsigned char DEFAULT_RENDER_ORDER | File: ../Graphics/Material.h
    engine->RegisterGlobalProperty("const uint8 DEFAULT_RENDER_ORDER", (void*)&DEFAULT_RENDER_ORDER);

    // static const unsigned DEFAULT_SHADOWMASK | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DEFAULT_SHADOWMASK", (void*)&DEFAULT_SHADOWMASK);

    // static const unsigned DEFAULT_VIEWMASK | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DEFAULT_VIEWMASK", (void*)&DEFAULT_VIEWMASK);

    // static const unsigned DEFAULT_ZONEMASK | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DEFAULT_ZONEMASK", (void*)&DEFAULT_ZONEMASK);

    // const Vector3 DOT_SCALE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const Vector3 DOT_SCALE", (void*)&DOT_SCALE);

    // static const unsigned DRAWABLE_ANY | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DRAWABLE_ANY", (void*)&DRAWABLE_ANY);

    // static const unsigned DRAWABLE_GEOMETRY | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DRAWABLE_GEOMETRY", (void*)&DRAWABLE_GEOMETRY);

    // static const unsigned DRAWABLE_GEOMETRY2D | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DRAWABLE_GEOMETRY2D", (void*)&DRAWABLE_GEOMETRY2D);

    // static const unsigned DRAWABLE_LIGHT | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DRAWABLE_LIGHT", (void*)&DRAWABLE_LIGHT);

    // static const unsigned DRAWABLE_UNDEFINED | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DRAWABLE_UNDEFINED", (void*)&DRAWABLE_UNDEFINED);

    // static const unsigned DRAWABLE_ZONE | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const uint DRAWABLE_ZONE", (void*)&DRAWABLE_ZONE);

    // const unsigned ELEMENT_TYPESIZES[] | File: ../Graphics/GraphicsDefs.h
    // Not registered because array

    // static const String EP_AUTOLOAD_PATHS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_AUTOLOAD_PATHS", (void*)&EP_AUTOLOAD_PATHS);

    // static const String EP_BORDERLESS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_BORDERLESS", (void*)&EP_BORDERLESS);

    // static const String EP_DUMP_SHADERS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_DUMP_SHADERS", (void*)&EP_DUMP_SHADERS);

    // static const String EP_EVENT_PROFILER | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_EVENT_PROFILER", (void*)&EP_EVENT_PROFILER);

    // static const String EP_EXTERNAL_WINDOW | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_EXTERNAL_WINDOW", (void*)&EP_EXTERNAL_WINDOW);

    // static const String EP_FLUSH_GPU | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_FLUSH_GPU", (void*)&EP_FLUSH_GPU);

    // static const String EP_FORCE_GL2 | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_FORCE_GL2", (void*)&EP_FORCE_GL2);

    // static const String EP_FRAME_LIMITER | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_FRAME_LIMITER", (void*)&EP_FRAME_LIMITER);

    // static const String EP_FULL_SCREEN | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_FULL_SCREEN", (void*)&EP_FULL_SCREEN);

    // static const String EP_HEADLESS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_HEADLESS", (void*)&EP_HEADLESS);

    // static const String EP_HIGH_DPI | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_HIGH_DPI", (void*)&EP_HIGH_DPI);

    // static const String EP_LOG_LEVEL | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_LOG_LEVEL", (void*)&EP_LOG_LEVEL);

    // static const String EP_LOG_NAME | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_LOG_NAME", (void*)&EP_LOG_NAME);

    // static const String EP_LOG_QUIET | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_LOG_QUIET", (void*)&EP_LOG_QUIET);

    // static const String EP_LOW_QUALITY_SHADOWS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_LOW_QUALITY_SHADOWS", (void*)&EP_LOW_QUALITY_SHADOWS);

    // static const String EP_MATERIAL_QUALITY | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_MATERIAL_QUALITY", (void*)&EP_MATERIAL_QUALITY);

    // static const String EP_MONITOR | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_MONITOR", (void*)&EP_MONITOR);

    // static const String EP_MULTI_SAMPLE | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_MULTI_SAMPLE", (void*)&EP_MULTI_SAMPLE);

    // static const String EP_ORIENTATIONS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_ORIENTATIONS", (void*)&EP_ORIENTATIONS);

    // static const String EP_PACKAGE_CACHE_DIR | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_PACKAGE_CACHE_DIR", (void*)&EP_PACKAGE_CACHE_DIR);

    // static const String EP_REFRESH_RATE | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_REFRESH_RATE", (void*)&EP_REFRESH_RATE);

    // static const String EP_RENDER_PATH | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_RENDER_PATH", (void*)&EP_RENDER_PATH);

    // static const String EP_RESOURCE_PACKAGES | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_RESOURCE_PACKAGES", (void*)&EP_RESOURCE_PACKAGES);

    // static const String EP_RESOURCE_PATHS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_RESOURCE_PATHS", (void*)&EP_RESOURCE_PATHS);

    // static const String EP_RESOURCE_PREFIX_PATHS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_RESOURCE_PREFIX_PATHS", (void*)&EP_RESOURCE_PREFIX_PATHS);

    // static const String EP_SHADER_CACHE_DIR | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_SHADER_CACHE_DIR", (void*)&EP_SHADER_CACHE_DIR);

    // static const String EP_SHADOWS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_SHADOWS", (void*)&EP_SHADOWS);

    // static const String EP_SOUND | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_SOUND", (void*)&EP_SOUND);

    // static const String EP_SOUND_BUFFER | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_SOUND_BUFFER", (void*)&EP_SOUND_BUFFER);

    // static const String EP_SOUND_INTERPOLATION | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_SOUND_INTERPOLATION", (void*)&EP_SOUND_INTERPOLATION);

    // static const String EP_SOUND_MIX_RATE | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_SOUND_MIX_RATE", (void*)&EP_SOUND_MIX_RATE);

    // static const String EP_SOUND_STEREO | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_SOUND_STEREO", (void*)&EP_SOUND_STEREO);

    // static const String EP_TEXTURE_ANISOTROPY | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_TEXTURE_ANISOTROPY", (void*)&EP_TEXTURE_ANISOTROPY);

    // static const String EP_TEXTURE_FILTER_MODE | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_TEXTURE_FILTER_MODE", (void*)&EP_TEXTURE_FILTER_MODE);

    // static const String EP_TEXTURE_QUALITY | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_TEXTURE_QUALITY", (void*)&EP_TEXTURE_QUALITY);

    // static const String EP_TIME_OUT | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_TIME_OUT", (void*)&EP_TIME_OUT);

    // static const String EP_TOUCH_EMULATION | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_TOUCH_EMULATION", (void*)&EP_TOUCH_EMULATION);

    // static const String EP_TRIPLE_BUFFER | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_TRIPLE_BUFFER", (void*)&EP_TRIPLE_BUFFER);

    // static const String EP_VSYNC | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_VSYNC", (void*)&EP_VSYNC);

    // static const String EP_WINDOW_HEIGHT | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WINDOW_HEIGHT", (void*)&EP_WINDOW_HEIGHT);

    // static const String EP_WINDOW_ICON | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WINDOW_ICON", (void*)&EP_WINDOW_ICON);

    // static const String EP_WINDOW_POSITION_X | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WINDOW_POSITION_X", (void*)&EP_WINDOW_POSITION_X);

    // static const String EP_WINDOW_POSITION_Y | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WINDOW_POSITION_Y", (void*)&EP_WINDOW_POSITION_Y);

    // static const String EP_WINDOW_RESIZABLE | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WINDOW_RESIZABLE", (void*)&EP_WINDOW_RESIZABLE);

    // static const String EP_WINDOW_TITLE | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WINDOW_TITLE", (void*)&EP_WINDOW_TITLE);

    // static const String EP_WINDOW_WIDTH | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WINDOW_WIDTH", (void*)&EP_WINDOW_WIDTH);

    // static const String EP_WORKER_THREADS | File: ../Engine/EngineDefs.h
    engine->RegisterGlobalProperty("const String EP_WORKER_THREADS", (void*)&EP_WORKER_THREADS);

    // static const unsigned FIRST_LOCAL_ID | File: ../Scene/Scene.h
    engine->RegisterGlobalProperty("const uint FIRST_LOCAL_ID", (void*)&FIRST_LOCAL_ID);

    // static const unsigned FIRST_REPLICATED_ID | File: ../Scene/Scene.h
    engine->RegisterGlobalProperty("const uint FIRST_REPLICATED_ID", (void*)&FIRST_REPLICATED_ID);

    // static const int FONT_DPI | File: ../UI/Font.h
    engine->RegisterGlobalProperty("const int FONT_DPI", (void*)&FONT_DPI);

    // static const int FONT_TEXTURE_MIN_SIZE | File: ../UI/Font.h
    engine->RegisterGlobalProperty("const int FONT_TEXTURE_MIN_SIZE", (void*)&FONT_TEXTURE_MIN_SIZE);

    // static const int INSTANCING_BUFFER_DEFAULT_SIZE | File: ../Graphics/Renderer.h
    engine->RegisterGlobalProperty("const int INSTANCING_BUFFER_DEFAULT_SIZE", (void*)&INSTANCING_BUFFER_DEFAULT_SIZE);

    // static const unsigned LAST_LOCAL_ID | File: ../Scene/Scene.h
    engine->RegisterGlobalProperty("const uint LAST_LOCAL_ID", (void*)&LAST_LOCAL_ID);

    // static const unsigned LAST_REPLICATED_ID | File: ../Scene/Scene.h
    engine->RegisterGlobalProperty("const uint LAST_REPLICATED_ID", (void*)&LAST_REPLICATED_ID);

    // const VertexElement LEGACY_VERTEXELEMENTS[] | File: ../Graphics/GraphicsDefs.h
    // Not registered because array

    // static const int LOG_DEBUG | File: ../IO/Log.h
    engine->RegisterGlobalProperty("const int LOG_DEBUG", (void*)&LOG_DEBUG);

    // static const int LOG_ERROR | File: ../IO/Log.h
    engine->RegisterGlobalProperty("const int LOG_ERROR", (void*)&LOG_ERROR);

    // static const int LOG_INFO | File: ../IO/Log.h
    engine->RegisterGlobalProperty("const int LOG_INFO", (void*)&LOG_INFO);

    // static const int LOG_NONE | File: ../IO/Log.h
    engine->RegisterGlobalProperty("const int LOG_NONE", (void*)&LOG_NONE);

    // static const int LOG_RAW | File: ../IO/Log.h
    engine->RegisterGlobalProperty("const int LOG_RAW", (void*)&LOG_RAW);

    // static const int LOG_TRACE | File: ../IO/Log.h
    engine->RegisterGlobalProperty("const int LOG_TRACE", (void*)&LOG_TRACE);

    // static const int LOG_WARNING | File: ../IO/Log.h
    engine->RegisterGlobalProperty("const int LOG_WARNING", (void*)&LOG_WARNING);

    // static const int MATRIX_CONVERSION_BUFFER_LENGTH | File: ../Container/Str.h
    engine->RegisterGlobalProperty("const int MATRIX_CONVERSION_BUFFER_LENGTH", (void*)&MATRIX_CONVERSION_BUFFER_LENGTH);

    // static const unsigned MAX_CASCADE_SPLITS | File: ../Graphics/Light.h
    engine->RegisterGlobalProperty("const uint MAX_CASCADE_SPLITS", (void*)&MAX_CASCADE_SPLITS);

    // static const int MAX_CONSTANT_REGISTERS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const int MAX_CONSTANT_REGISTERS", (void*)&MAX_CONSTANT_REGISTERS);

    // static const int MAX_LIGHT_SPLITS | File: ../Graphics/Light.h
    engine->RegisterGlobalProperty("const int MAX_LIGHT_SPLITS", (void*)&MAX_LIGHT_SPLITS);

    // static const unsigned MAX_NETWORK_ATTRIBUTES | File: ../Scene/ReplicationState.h
    engine->RegisterGlobalProperty("const uint MAX_NETWORK_ATTRIBUTES", (void*)&MAX_NETWORK_ATTRIBUTES);

    // static const int MAX_RENDERTARGETS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const int MAX_RENDERTARGETS", (void*)&MAX_RENDERTARGETS);

    // static const int MAX_TEXTURE_QUALITY_LEVELS | File: ../Graphics/Texture.h
    engine->RegisterGlobalProperty("const int MAX_TEXTURE_QUALITY_LEVELS", (void*)&MAX_TEXTURE_QUALITY_LEVELS);

    // static const int MAX_VERTEX_LIGHTS | File: ../Graphics/Drawable.h
    engine->RegisterGlobalProperty("const int MAX_VERTEX_LIGHTS", (void*)&MAX_VERTEX_LIGHTS);

    // static const int MAX_VERTEX_STREAMS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const int MAX_VERTEX_STREAMS", (void*)&MAX_VERTEX_STREAMS);

    // static const unsigned MAX_VIEWPORT_TEXTURES | File: ../Graphics/View.h
    engine->RegisterGlobalProperty("const uint MAX_VIEWPORT_TEXTURES", (void*)&MAX_VIEWPORT_TEXTURES);

    // const IntVector2 MOUSE_POSITION_OFFSCREEN | File: ../Input/Input.h
    engine->RegisterGlobalProperty("const IntVector2 MOUSE_POSITION_OFFSCREEN", (void*)&MOUSE_POSITION_OFFSCREEN);

    // static const float M_DEGTORAD | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_DEGTORAD", (void*)&M_DEGTORAD);

    // static const float M_DEGTORAD_2 | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_DEGTORAD_2", (void*)&M_DEGTORAD_2);

    // static const float M_EPSILON | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_EPSILON", (void*)&M_EPSILON);

    // static const float M_HALF_PI | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_HALF_PI", (void*)&M_HALF_PI);

    // static const float M_INFINITY | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_INFINITY", (void*)&M_INFINITY);

    // static const float M_LARGE_EPSILON | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_LARGE_EPSILON", (void*)&M_LARGE_EPSILON);

    // static const float M_LARGE_VALUE | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_LARGE_VALUE", (void*)&M_LARGE_VALUE);

    // static const float M_MAX_FOV | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_MAX_FOV", (void*)&M_MAX_FOV);

    // static const int M_MAX_INT | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const int M_MAX_INT", (void*)&M_MAX_INT);

    // static const unsigned M_MAX_UNSIGNED | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const uint M_MAX_UNSIGNED", (void*)&M_MAX_UNSIGNED);

    // static const int M_MIN_INT | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const int M_MIN_INT", (void*)&M_MIN_INT);

    // static const float M_MIN_NEARCLIP | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_MIN_NEARCLIP", (void*)&M_MIN_NEARCLIP);

    // static const unsigned M_MIN_UNSIGNED | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const uint M_MIN_UNSIGNED", (void*)&M_MIN_UNSIGNED);

    // static const float M_PI | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_PI", (void*)&M_PI);

    // static const float M_RADTODEG | File: ../Math/MathDefs.h
    engine->RegisterGlobalProperty("const float M_RADTODEG", (void*)&M_RADTODEG);

    // static const unsigned NUM_FRUSTUM_PLANES | File: ../Math/Frustum.h
    engine->RegisterGlobalProperty("const uint NUM_FRUSTUM_PLANES", (void*)&NUM_FRUSTUM_PLANES);

    // static const unsigned NUM_FRUSTUM_VERTICES | File: ../Math/Frustum.h
    engine->RegisterGlobalProperty("const uint NUM_FRUSTUM_VERTICES", (void*)&NUM_FRUSTUM_VERTICES);

    // static const int NUM_OCTANTS | File: ../Graphics/Octree.h
    engine->RegisterGlobalProperty("const int NUM_OCTANTS", (void*)&NUM_OCTANTS);

    // static const int OCCLUSION_DEFAULT_MAX_TRIANGLES | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterGlobalProperty("const int OCCLUSION_DEFAULT_MAX_TRIANGLES", (void*)&OCCLUSION_DEFAULT_MAX_TRIANGLES);

    // static const int OCCLUSION_FIXED_BIAS | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterGlobalProperty("const int OCCLUSION_FIXED_BIAS", (void*)&OCCLUSION_FIXED_BIAS);

    // static const int OCCLUSION_MIN_SIZE | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterGlobalProperty("const int OCCLUSION_MIN_SIZE", (void*)&OCCLUSION_MIN_SIZE);

    // static const float OCCLUSION_RELATIVE_BIAS | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterGlobalProperty("const float OCCLUSION_RELATIVE_BIAS", (void*)&OCCLUSION_RELATIVE_BIAS);

    // static const float OCCLUSION_X_SCALE | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterGlobalProperty("const float OCCLUSION_X_SCALE", (void*)&OCCLUSION_X_SCALE);

    // static const float OCCLUSION_Z_SCALE | File: ../Graphics/OcclusionBuffer.h
    engine->RegisterGlobalProperty("const float OCCLUSION_Z_SCALE", (void*)&OCCLUSION_Z_SCALE);

    // static const unsigned PRIORITY_LAST | File: ../Resource/ResourceCache.h
    engine->RegisterGlobalProperty("const uint PRIORITY_LAST", (void*)&PRIORITY_LAST);

    // const StringHash PSP_AMBIENTCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_AMBIENTCOLOR", (void*)&PSP_AMBIENTCOLOR);

    // const StringHash PSP_CAMERAPOS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_CAMERAPOS", (void*)&PSP_CAMERAPOS);

    // const StringHash PSP_DELTATIME | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_DELTATIME", (void*)&PSP_DELTATIME);

    // const StringHash PSP_DEPTHRECONSTRUCT | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_DEPTHRECONSTRUCT", (void*)&PSP_DEPTHRECONSTRUCT);

    // const StringHash PSP_ELAPSEDTIME | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_ELAPSEDTIME", (void*)&PSP_ELAPSEDTIME);

    // const StringHash PSP_FARCLIP | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_FARCLIP", (void*)&PSP_FARCLIP);

    // const StringHash PSP_FOGCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_FOGCOLOR", (void*)&PSP_FOGCOLOR);

    // const StringHash PSP_FOGPARAMS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_FOGPARAMS", (void*)&PSP_FOGPARAMS);

    // const StringHash PSP_GBUFFERINVSIZE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_GBUFFERINVSIZE", (void*)&PSP_GBUFFERINVSIZE);

    // const StringHash PSP_LIGHTCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_LIGHTCOLOR", (void*)&PSP_LIGHTCOLOR);

    // const StringHash PSP_LIGHTDIR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_LIGHTDIR", (void*)&PSP_LIGHTDIR);

    // const StringHash PSP_LIGHTLENGTH | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_LIGHTLENGTH", (void*)&PSP_LIGHTLENGTH);

    // const StringHash PSP_LIGHTMATRICES | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_LIGHTMATRICES", (void*)&PSP_LIGHTMATRICES);

    // const StringHash PSP_LIGHTPOS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_LIGHTPOS", (void*)&PSP_LIGHTPOS);

    // const StringHash PSP_LIGHTRAD | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_LIGHTRAD", (void*)&PSP_LIGHTRAD);

    // const StringHash PSP_MATDIFFCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_MATDIFFCOLOR", (void*)&PSP_MATDIFFCOLOR);

    // const StringHash PSP_MATEMISSIVECOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_MATEMISSIVECOLOR", (void*)&PSP_MATEMISSIVECOLOR);

    // const StringHash PSP_MATENVMAPCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_MATENVMAPCOLOR", (void*)&PSP_MATENVMAPCOLOR);

    // const StringHash PSP_MATSPECCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_MATSPECCOLOR", (void*)&PSP_MATSPECCOLOR);

    // const StringHash PSP_METALLIC | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_METALLIC", (void*)&PSP_METALLIC);

    // const StringHash PSP_NEARCLIP | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_NEARCLIP", (void*)&PSP_NEARCLIP);

    // const StringHash PSP_NORMALOFFSETSCALE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_NORMALOFFSETSCALE", (void*)&PSP_NORMALOFFSETSCALE);

    // const StringHash PSP_ROUGHNESS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_ROUGHNESS", (void*)&PSP_ROUGHNESS);

    // const StringHash PSP_SHADOWCUBEADJUST | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_SHADOWCUBEADJUST", (void*)&PSP_SHADOWCUBEADJUST);

    // const StringHash PSP_SHADOWDEPTHFADE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_SHADOWDEPTHFADE", (void*)&PSP_SHADOWDEPTHFADE);

    // const StringHash PSP_SHADOWINTENSITY | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_SHADOWINTENSITY", (void*)&PSP_SHADOWINTENSITY);

    // const StringHash PSP_SHADOWMAPINVSIZE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_SHADOWMAPINVSIZE", (void*)&PSP_SHADOWMAPINVSIZE);

    // const StringHash PSP_SHADOWSPLITS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_SHADOWSPLITS", (void*)&PSP_SHADOWSPLITS);

    // const StringHash PSP_VSMSHADOWPARAMS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_VSMSHADOWPARAMS", (void*)&PSP_VSMSHADOWPARAMS);

    // const StringHash PSP_ZONEMAX | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_ZONEMAX", (void*)&PSP_ZONEMAX);

    // const StringHash PSP_ZONEMIN | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash PSP_ZONEMIN", (void*)&PSP_ZONEMIN);

    // static const int QUICKSORT_THRESHOLD | File: ../Container/Sort.h
    engine->RegisterGlobalProperty("const int QUICKSORT_THRESHOLD", (void*)&QUICKSORT_THRESHOLD);

    // static const unsigned ROOT_INDEX | File: ../Graphics/Octree.h
    engine->RegisterGlobalProperty("const uint ROOT_INDEX", (void*)&ROOT_INDEX);

    // static const unsigned SCAN_DIRS | File: ../IO/FileSystem.h
    engine->RegisterGlobalProperty("const uint SCAN_DIRS", (void*)&SCAN_DIRS);

    // static const unsigned SCAN_FILES | File: ../IO/FileSystem.h
    engine->RegisterGlobalProperty("const uint SCAN_FILES", (void*)&SCAN_FILES);

    // static const unsigned SCAN_HIDDEN | File: ../IO/FileSystem.h
    engine->RegisterGlobalProperty("const uint SCAN_HIDDEN", (void*)&SCAN_HIDDEN);

    // static const int SHADOW_MIN_PIXELS | File: ../Graphics/Renderer.h
    engine->RegisterGlobalProperty("const int SHADOW_MIN_PIXELS", (void*)&SHADOW_MIN_PIXELS);

    // static const float SHADOW_MIN_QUANTIZE | File: ../Graphics/Light.h
    engine->RegisterGlobalProperty("const float SHADOW_MIN_QUANTIZE", (void*)&SHADOW_MIN_QUANTIZE);

    // static const float SHADOW_MIN_VIEW | File: ../Graphics/Light.h
    engine->RegisterGlobalProperty("const float SHADOW_MIN_VIEW", (void*)&SHADOW_MIN_VIEW);

    // static const String SOUND_AMBIENT | File: ../Audio/AudioDefs.h
    engine->RegisterGlobalProperty("const String SOUND_AMBIENT", (void*)&SOUND_AMBIENT);

    // static const String SOUND_EFFECT | File: ../Audio/AudioDefs.h
    engine->RegisterGlobalProperty("const String SOUND_EFFECT", (void*)&SOUND_EFFECT);

    // static const String SOUND_MASTER | File: ../Audio/AudioDefs.h
    engine->RegisterGlobalProperty("const String SOUND_MASTER", (void*)&SOUND_MASTER);

    // static const String SOUND_MUSIC | File: ../Audio/AudioDefs.h
    engine->RegisterGlobalProperty("const String SOUND_MUSIC", (void*)&SOUND_MUSIC);

    // static const String SOUND_VOICE | File: ../Audio/AudioDefs.h
    engine->RegisterGlobalProperty("const String SOUND_VOICE", (void*)&SOUND_VOICE);

    // static const int STREAM_BUFFER_LENGTH | File: ../Audio/SoundSource.h
    engine->RegisterGlobalProperty("const int STREAM_BUFFER_LENGTH", (void*)&STREAM_BUFFER_LENGTH);

    // static const unsigned UI_VERTEX_SIZE | File: ../UI/UIBatch.h
    engine->RegisterGlobalProperty("const uint UI_VERTEX_SIZE", (void*)&UI_VERTEX_SIZE);

    // static const unsigned VARIANT_VALUE_SIZE | File: ../Core/Variant.h
    engine->RegisterGlobalProperty("const uint VARIANT_VALUE_SIZE", (void*)&VARIANT_VALUE_SIZE);

    // const StringHash VSP_AMBIENTENDCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_AMBIENTENDCOLOR", (void*)&VSP_AMBIENTENDCOLOR);

    // const StringHash VSP_AMBIENTSTARTCOLOR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_AMBIENTSTARTCOLOR", (void*)&VSP_AMBIENTSTARTCOLOR);

    // const StringHash VSP_BILLBOARDROT | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_BILLBOARDROT", (void*)&VSP_BILLBOARDROT);

    // const StringHash VSP_CAMERAPOS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_CAMERAPOS", (void*)&VSP_CAMERAPOS);

    // const StringHash VSP_CLIPPLANE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_CLIPPLANE", (void*)&VSP_CLIPPLANE);

    // const StringHash VSP_DELTATIME | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_DELTATIME", (void*)&VSP_DELTATIME);

    // const StringHash VSP_DEPTHMODE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_DEPTHMODE", (void*)&VSP_DEPTHMODE);

    // const StringHash VSP_ELAPSEDTIME | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_ELAPSEDTIME", (void*)&VSP_ELAPSEDTIME);

    // const StringHash VSP_FARCLIP | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_FARCLIP", (void*)&VSP_FARCLIP);

    // const StringHash VSP_FRUSTUMSIZE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_FRUSTUMSIZE", (void*)&VSP_FRUSTUMSIZE);

    // const StringHash VSP_GBUFFEROFFSETS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_GBUFFEROFFSETS", (void*)&VSP_GBUFFEROFFSETS);

    // const StringHash VSP_LIGHTDIR | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_LIGHTDIR", (void*)&VSP_LIGHTDIR);

    // const StringHash VSP_LIGHTMATRICES | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_LIGHTMATRICES", (void*)&VSP_LIGHTMATRICES);

    // const StringHash VSP_LIGHTPOS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_LIGHTPOS", (void*)&VSP_LIGHTPOS);

    // const StringHash VSP_MODEL | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_MODEL", (void*)&VSP_MODEL);

    // const StringHash VSP_NEARCLIP | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_NEARCLIP", (void*)&VSP_NEARCLIP);

    // const StringHash VSP_NORMALOFFSETSCALE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_NORMALOFFSETSCALE", (void*)&VSP_NORMALOFFSETSCALE);

    // const StringHash VSP_SKINMATRICES | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_SKINMATRICES", (void*)&VSP_SKINMATRICES);

    // const StringHash VSP_UOFFSET | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_UOFFSET", (void*)&VSP_UOFFSET);

    // const StringHash VSP_VERTEXLIGHTS | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_VERTEXLIGHTS", (void*)&VSP_VERTEXLIGHTS);

    // const StringHash VSP_VIEW | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_VIEW", (void*)&VSP_VIEW);

    // const StringHash VSP_VIEWINV | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_VIEWINV", (void*)&VSP_VIEWINV);

    // const StringHash VSP_VIEWPROJ | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_VIEWPROJ", (void*)&VSP_VIEWPROJ);

    // const StringHash VSP_VOFFSET | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_VOFFSET", (void*)&VSP_VOFFSET);

    // const StringHash VSP_ZONE | File: ../Graphics/GraphicsDefs.h
    engine->RegisterGlobalProperty("const StringHash VSP_ZONE", (void*)&VSP_ZONE);

#ifdef URHO3D_NETWORK
    // static const unsigned CONTROLS_CONTENT_ID | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const uint CONTROLS_CONTENT_ID", (void*)&CONTROLS_CONTENT_ID);

    // static const int MSG_COMPONENTDELTAUPDATE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_COMPONENTDELTAUPDATE", (void*)&MSG_COMPONENTDELTAUPDATE);

    // static const int MSG_COMPONENTLATESTDATA | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_COMPONENTLATESTDATA", (void*)&MSG_COMPONENTLATESTDATA);

    // static const int MSG_CONTROLS | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_CONTROLS", (void*)&MSG_CONTROLS);

    // static const int MSG_CREATECOMPONENT | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_CREATECOMPONENT", (void*)&MSG_CREATECOMPONENT);

    // static const int MSG_CREATENODE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_CREATENODE", (void*)&MSG_CREATENODE);

    // static const int MSG_IDENTITY | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_IDENTITY", (void*)&MSG_IDENTITY);

    // static const int MSG_LOADSCENE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_LOADSCENE", (void*)&MSG_LOADSCENE);

    // static const int MSG_NODEDELTAUPDATE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_NODEDELTAUPDATE", (void*)&MSG_NODEDELTAUPDATE);

    // static const int MSG_NODELATESTDATA | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_NODELATESTDATA", (void*)&MSG_NODELATESTDATA);

    // static const int MSG_PACKAGEDATA | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_PACKAGEDATA", (void*)&MSG_PACKAGEDATA);

    // static const int MSG_PACKAGEINFO | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_PACKAGEINFO", (void*)&MSG_PACKAGEINFO);

    // static const int MSG_PACKED_MESSAGE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_PACKED_MESSAGE", (void*)&MSG_PACKED_MESSAGE);

    // static const int MSG_REMOTEEVENT | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_REMOTEEVENT", (void*)&MSG_REMOTEEVENT);

    // static const int MSG_REMOTENODEEVENT | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_REMOTENODEEVENT", (void*)&MSG_REMOTENODEEVENT);

    // static const int MSG_REMOVECOMPONENT | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_REMOVECOMPONENT", (void*)&MSG_REMOVECOMPONENT);

    // static const int MSG_REMOVENODE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_REMOVENODE", (void*)&MSG_REMOVENODE);

    // static const int MSG_REQUESTPACKAGE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_REQUESTPACKAGE", (void*)&MSG_REQUESTPACKAGE);

    // static const int MSG_SCENECHECKSUMERROR | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_SCENECHECKSUMERROR", (void*)&MSG_SCENECHECKSUMERROR);

    // static const int MSG_SCENELOADED | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_SCENELOADED", (void*)&MSG_SCENELOADED);

    // static const int MSG_USER | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const int MSG_USER", (void*)&MSG_USER);

    // static const unsigned PACKAGE_FRAGMENT_SIZE | File: ../Network/Protocol.h
    engine->RegisterGlobalProperty("const uint PACKAGE_FRAGMENT_SIZE", (void*)&PACKAGE_FRAGMENT_SIZE);
#endif

#ifdef URHO3D_PHYSICS
    // static const int DEFAULT_FPS | File: ../Physics/PhysicsWorld.h
    engine->RegisterGlobalProperty("const int DEFAULT_FPS", (void*)&DEFAULT_FPS);

    // static const float DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY | File: ../Physics/PhysicsWorld.h
    engine->RegisterGlobalProperty("const float DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY", (void*)&DEFAULT_MAX_NETWORK_ANGULAR_VELOCITY);
#endif

#ifdef URHO3D_URHO2D
    // static const unsigned FLIP_ALL | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterGlobalProperty("const uint FLIP_ALL", (void*)&FLIP_ALL);

    // static const unsigned FLIP_DIAGONAL | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterGlobalProperty("const uint FLIP_DIAGONAL", (void*)&FLIP_DIAGONAL);

    // static const unsigned FLIP_HORIZONTAL | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterGlobalProperty("const uint FLIP_HORIZONTAL", (void*)&FLIP_HORIZONTAL);

    // static const unsigned FLIP_RESERVED | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterGlobalProperty("const uint FLIP_RESERVED", (void*)&FLIP_RESERVED);

    // static const unsigned FLIP_VERTICAL | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterGlobalProperty("const uint FLIP_VERTICAL", (void*)&FLIP_VERTICAL);

    // const float PIXEL_SIZE | File: ../Urho2D/Drawable2D.h
    engine->RegisterGlobalProperty("const float PIXEL_SIZE", (void*)&PIXEL_SIZE);
#endif
}

}
