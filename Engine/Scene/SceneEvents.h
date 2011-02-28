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

#ifndef SCENE_SCENEEVENTS_H
#define SCENE_SCENEEVENTS_H

#include "Event.h"

//! Update all non-networked scenes. Sent by Engine
DEFINE_EVENT(EVENT_UPDATESCENES, UpdateScenes)
{
    EVENT_PARAM(P_TIMESTEP, TimeStep);          // float
}

//! Variable timestep scene update
DEFINE_EVENT(EVENT_SCENEUPDATE, SceneUpdate)
{
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
    EVENT_PARAM(P_TIMESTEP, TimeStep);          // float
}

//! Variable timestep scene post-update
DEFINE_EVENT(EVENT_SCENEPOSTUPDATE, ScenePostUpdate)
{
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
    EVENT_PARAM(P_TIMESTEP, TimeStep);          // float
}

//! Asynchronous scene loading progress
DEFINE_EVENT(EVENT_ASYNCLOADPROGRESS, AsyncLoadProgress)
{
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
    EVENT_PARAM(P_PROGRESS, Progress);          // float
    EVENT_PARAM(P_LOADEDENTITIES, LoadedEntities); // int
    EVENT_PARAM(P_TOTALENTITIES, TotalEntities); // int
};

//! Asynchronous scene loading finished
DEFINE_EVENT(EVENT_ASYNCLOADFINISHED, AsyncLoadFinished)
{
    EVENT_PARAM(P_SCENE, Scene);                // Scene pointer
};

#endif // SCENE_SCENEEVENTS_H
