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

#ifndef ENGINE_REGISTERLIBRARIES_H
#define ENGINE_REGISTERLIBRARIES_H

class asIScriptEngine;

//! Register the Math library to script
void registerMathLibrary(asIScriptEngine* engine);
//! Register the Common library to script
void registerCommonLibrary(asIScriptEngine* engine);
//! Register the Resource library to script
void registerResourceLibrary(asIScriptEngine* engine);
//! Register the Scene library to script
void registerSceneLibrary(asIScriptEngine* engine);
//! Register the Audio library to script
void registerAudioLibrary(asIScriptEngine* engine);
//! Register the Renderer library to script
void registerRendererLibrary(asIScriptEngine* engine);
//! Register the Input library to script
void registerInputLibrary(asIScriptEngine* engine);
//! Register the UI library to script
void registerUILibrary(asIScriptEngine* engine);
//! Register the Physics library to script
void registerPhysicsLibrary(asIScriptEngine* engine);
//! Register the Script library to script
void registerScriptLibrary(asIScriptEngine* engine);
//! Register the Engine library to script
void registerEngineLibrary(asIScriptEngine* engine);

#endif // ENGINE_REGISTERLIBRARIES_H
