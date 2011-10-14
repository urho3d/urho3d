//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "Object.h"

/// Variable timestep scene update.
EVENT(E_SCENEUPDATE, SceneUpdate)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Scene subsystem update.
EVENT(E_SCENESUBSYSTEMUPDATE, SceneSubsystemUpdate)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Variable timestep scene post-update.
EVENT(E_SCENEPOSTUPDATE, ScenePostUpdate)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_TIMESTEP, TimeStep);            // float
}

/// Asynchronous scene loading progress.
EVENT(E_ASYNCLOADPROGRESS, AsyncLoadProgress)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
    PARAM(P_PROGRESS, Progress);            // float
    PARAM(P_LOADEDNODES, LoadedNodes);      // int
    PARAM(P_TOTALNODES, TotalNodes);        // int
};

/// Asynchronous scene loading finished.
EVENT(E_ASYNCLOADFINISHED, AsyncLoadFinished)
{
    PARAM(P_SCENE, Scene);                  // Scene pointer
};
