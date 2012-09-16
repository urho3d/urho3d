//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "Timer.h"

namespace Urho3D
{

class Engine;
class Font;
class Text;
class XMLFile;

static const unsigned DEBUGHUD_SHOW_NONE = 0x0;
static const unsigned DEBUGHUD_SHOW_STATS = 0x1;
static const unsigned DEBUGHUD_SHOW_MODE = 0x2;
static const unsigned DEBUGHUD_SHOW_PROFILER = 0x4;
static const unsigned DEBUGHUD_SHOW_ALL = 0x7;

/// Displays rendering stats and profiling information.
class DebugHud : public Object
{
    OBJECT(DebugHud);
    
public:
    /// Construct.
    DebugHud(Context* context);
    /// Destruct.
    ~DebugHud();
    
    /// Update. Called by HandleUpdate().
    void Update();
    /// Set UI elements' style from an XML file.
    void SetStyle(XMLFile* style);
    /// Set elements to show.
    void SetMode(unsigned mode);
    /// Set maximum profiler block depth, default unlimited.
    void SetProfilerMaxDepth(unsigned depth);
    /// Set profiler accumulation interval.
    void SetProfilerInterval(float interval);
    /// Set whether to show 3D geometry primitive/batch count only. Default false.
    void SetUseRendererStats(bool enable);
    /// Toggle elements.
    void Toggle(unsigned mode);
    /// Toggle all elements.
    void ToggleAll();
    
    /// Return the UI style file.
    XMLFile* GetStyle() const { return style_; }
    /// Return rendering stats text.
    Text* GetStatsText() const { return statsText_; }
    /// Return rendering mode text.
    Text* GetModeText() const { return modeText_; }
    /// Return profiler text.
    Text* GetProfilerText() const { return profilerText_; }
    /// Return currently shown elements.
    unsigned GetMode() const;
    /// Return maximum profiler block depth.
    unsigned GetProfilerMaxDepth() const { return profilerMaxDepth_; }
    /// Return profiler accumulation interval.
    float GetProfilerInterval() const { return profilerInterval_; }
    /// Return whether showing 3D geometry primitive/batch count only.
    bool GetUseRendererStats() const { return useRendererStats_; }
    
private:
    /// Handle logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    
    /// UI style file.
    SharedPtr<XMLFile> style_;
    /// Rendering stats text.
    SharedPtr<Text> statsText_;
    /// Rendering mode text.
    SharedPtr<Text> modeText_;
    /// Profiling information text.
    SharedPtr<Text> profilerText_;
    /// Profiler timer.
    Timer profilerTimer_;
    /// Profiler max block depth.
    unsigned profilerMaxDepth_;
    /// Profiler accumulation interval.
    float profilerInterval_;
    /// Show 3D geometry primitive/batch count flag.
    bool useRendererStats_;
};

}
