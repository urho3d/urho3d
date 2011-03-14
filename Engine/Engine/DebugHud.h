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

#ifndef ENGINE_DEBUGHUD_H
#define ENGINE_DEBUGHUD_H

#include "SharedPtr.h"

class Engine;
class Font;
class Text;
class XMLFile;

static const unsigned DEBUGHUD_SHOW_NONE = 0x0;
static const unsigned DEBUGHUD_SHOW_STATS = 0x1;
static const unsigned DEBUGHUD_SHOW_MODE = 0x2;
static const unsigned DEBUGHUD_SHOW_PROFILER = 0x4;

//! Displays rendering stats and profiling information
class DebugHud : public RefCounted
{
public:
    //! Construct with an Engine pointer
    DebugHud(Engine* engine);
    //! Destruct
    ~DebugHud();
    
    //! Update
    void update(float timeStep);
    //! Set UI elements' style from an XML file
    void setStyle(XMLFile* style);
    //! Set elements to show
    void setMode(unsigned mode);
    //! Set profiler accumulation interval
    void setProfilerInterval(float interval);
    //! Set whether to show 3D geometry primitive/batch count only. Default false
    void setUsePipelineStats(bool enable);
    //! Toggle elements
    void toggle(unsigned mode);
    //! Toggle all elements
    void toggleAll();
    
    //! Return the UI style file
    XMLFile* getStyle() const { return mStyle; }
    //! Return rendering stats text
    Text* getStatsText() const { return mStatsText; }
    //! Return rendering mode text
    Text* getModeText() const { return mModeText; }
    //! Return profiler text
    Text* getProfilerText() const { return mProfilerText; }
    //! Return currently shown elements
    unsigned getMode() const;
    //! Return profiler accumulation interval
    float getProfilerInterval() const { return mProfilerInterval; }
    //! Return whether showing 3D geometry primitive/batch count only
    bool getUsePipelineStats() const { return mUsePipelineStats; }
    
private:
    //! Engine
    Engine* mEngine;
    //! UI style file
    SharedPtr<XMLFile> mStyle;
    //! Rendering stats text
    SharedPtr<Text> mStatsText;
    //! Rendering mode text
    SharedPtr<Text> mModeText;
    //! Profiling information text
    SharedPtr<Text> mProfilerText;
    //! Profiler accumulation interval
    float mProfilerInterval;
    //! Profiler accumulation timer
    float mProfilerTimer;
    //! Show 3D geometry primitive/batch count flag
    bool mUsePipelineStats;
};

DebugHud* getDebugHud();

#endif // ENGINE_DEBUGHUD_H
