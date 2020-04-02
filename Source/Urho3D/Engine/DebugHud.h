//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "../Core/Object.h"
#include "../Core/Timer.h"

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
static const unsigned DEBUGHUD_SHOW_MEMORY = 0x8;
static const unsigned DEBUGHUD_SHOW_EVENTPROFILER = 0x10;
static const unsigned DEBUGHUD_SHOW_ALL = DEBUGHUD_SHOW_STATS | DEBUGHUD_SHOW_MODE | DEBUGHUD_SHOW_PROFILER | DEBUGHUD_SHOW_MEMORY;

/// Displays rendering stats and profiling information.
class URHO3D_API DebugHud : public Object
{
    URHO3D_OBJECT(DebugHud, Object);

public:
    /// Construct.
    explicit DebugHud(Context* context);
    /// Destruct.
    ~DebugHud() override;

    /// Update. Called by HandlePostUpdate().
    void Update();
    /// Set UI elements' style from an XML file.
    void SetDefaultStyle(XMLFile* style);
    /// Set elements to show.
    void SetMode(unsigned mode);
    /// Set maximum profiler block depth, default unlimited.
    void SetProfilerMaxDepth(unsigned depth);
    /// Set profiler accumulation interval in seconds.
    void SetProfilerInterval(float interval);
    /// Set whether to show 3D geometry primitive/batch count only. Default false.
    void SetUseRendererStats(bool enable);
    /// Toggle elements.
    void Toggle(unsigned mode);
    /// Toggle all elements.
    void ToggleAll();

    /// Return the UI style file.
    XMLFile* GetDefaultStyle() const;

    /// Return rendering stats text.
    Text* GetStatsText() const { return statsText_; }

    /// Return rendering mode text.
    Text* GetModeText() const { return modeText_; }

    /// Return profiler text.
    Text* GetProfilerText() const { return profilerText_; }

    /// Return memory text.
    Text* GetMemoryText() const { return memoryText_; }

    /// Return currently shown elements.
    unsigned GetMode() const { return mode_; }

    /// Return maximum profiler block depth.
    unsigned GetProfilerMaxDepth() const { return profilerMaxDepth_; }

    /// Return profiler accumulation interval in seconds.
    float GetProfilerInterval() const;

    /// Return whether showing 3D geometry primitive/batch count only.
    bool GetUseRendererStats() const { return useRendererStats_; }

    /// Set application-specific stats.
    void SetAppStats(const String& label, const Variant& stats);
    /// Set application-specific stats.
    void SetAppStats(const String& label, const String& stats);
    /// Reset application-specific stats. Return true if it was erased successfully.
    bool ResetAppStats(const String& label);
    /// Clear all application-specific stats.
    void ClearAppStats();

private:
    /// Handle logic post-update event. The HUD texts are updated here.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Rendering stats text.
    SharedPtr<Text> statsText_;
    /// Rendering mode text.
    SharedPtr<Text> modeText_;
    /// Profiling information text.
    SharedPtr<Text> profilerText_;
    /// Event profiling information text.
    SharedPtr<Text> eventProfilerText_;
    /// Memory stats text.
    SharedPtr<Text> memoryText_;
    /// Hashmap containing application specific stats.
    HashMap<String, String> appStats_;
    /// Profiler timer.
    Timer profilerTimer_;
    /// Profiler max block depth.
    unsigned profilerMaxDepth_;
    /// Profiler accumulation interval.
    unsigned profilerInterval_;
    /// Show 3D geometry primitive/batch count flag.
    bool useRendererStats_;
    /// Current shown-element mode.
    unsigned mode_;
};

}
