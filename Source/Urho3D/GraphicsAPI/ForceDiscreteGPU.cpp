// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

// Prefer the high-performance GPU on switchable GPU systems

#ifdef _WIN32

extern "C"
{
    // https://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
    __declspec(dllexport) unsigned long NvOptimusEnablement = 1;

    // https://community.amd.com/t5/archives-discussions/can-an-opengl-app-default-to-the-discrete-gpu-on-an-enduro/td-p/279440
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#endif // def _WIN32
