// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#include "../Precompiled.h"

#include "../Core/CoreEvents.h"
#include "../Core/Profiler.h"
#include "../Core/EventProfiler.h"
#include "../Core/Context.h"
#include "../Engine/DebugHud.h"
#include "../Engine/Engine.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Renderer.h"
#include "../Resource/ResourceCache.h"
#include "../IO/Log.h"
#include "../UI/Font.h"
#include "../UI/Text.h"
#include "../UI/UI.h"

#include "../DebugNew.h"

namespace Urho3D
{

static const char* qualityTexts[] =
{
    "Low",
    "Med",
    "High",
    "High+"
};

static const char* shadowQualityTexts[] =
{
    "16bit Simple",
    "24bit Simple",
    "16bit PCF",
    "24bit PCF",
    "VSM",
    "Blurred VSM"
};

DebugHud::DebugHud(Context* context) :
    Object(context),
    profilerMaxDepth_(M_MAX_UNSIGNED),
    profilerInterval_(1000),
    useRendererStats_(false),
    mode_(DebugHudElements::None)
{
    auto* ui = GetSubsystem<UI>();
    UIElement* uiRoot = ui->GetRoot();

    statsText_ = new Text(context_);
    statsText_->SetAlignment(HA_LEFT, VA_TOP);
    statsText_->SetPriority(100);
    statsText_->SetVisible(false);
    uiRoot->AddChild(statsText_);

    modeText_ = new Text(context_);
    modeText_->SetAlignment(HA_LEFT, VA_BOTTOM);
    modeText_->SetPriority(100);
    modeText_->SetVisible(false);
    uiRoot->AddChild(modeText_);

    profilerText_ = new Text(context_);
    profilerText_->SetAlignment(HA_RIGHT, VA_TOP);
    profilerText_->SetPriority(100);
    profilerText_->SetVisible(false);
    uiRoot->AddChild(profilerText_);

    memoryText_ = new Text(context_);
    memoryText_->SetAlignment(HA_LEFT, VA_BOTTOM);
    memoryText_->SetPriority(100);
    memoryText_->SetVisible(false);
    uiRoot->AddChild(memoryText_);

    eventProfilerText_ = new Text(context_);
    eventProfilerText_->SetAlignment(HA_RIGHT, VA_TOP);
    eventProfilerText_->SetPriority(100);
    eventProfilerText_->SetVisible(false);
    uiRoot->AddChild(eventProfilerText_);

    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(DebugHud, HandlePostUpdate));
}

DebugHud::~DebugHud()
{
    statsText_->Remove();
    modeText_->Remove();
    profilerText_->Remove();
    memoryText_->Remove();
    eventProfilerText_->Remove();
}

void DebugHud::Update()
{
    auto* graphics = GetSubsystem<Graphics>();
    auto* renderer = GetSubsystem<Renderer>();
    if (!renderer || !graphics)
        return;

    // Ensure UI-elements are not detached
    if (!statsText_->GetParent())
    {
        auto* ui = GetSubsystem<UI>();
        UIElement* uiRoot = ui->GetRoot();
        uiRoot->AddChild(statsText_);
        uiRoot->AddChild(modeText_);
        uiRoot->AddChild(profilerText_);
    }

    if (statsText_->IsVisible())
    {
        unsigned primitives, batches;
        if (!useRendererStats_)
        {
            primitives = graphics->GetNumPrimitives();
            batches = graphics->GetNumBatches();
        }
        else
        {
            primitives = renderer->GetNumPrimitives();
            batches = renderer->GetNumBatches();
        }

        String stats;
        stats.AppendWithFormat("Triangles %u\nBatches %u\nViews %u\nLights %u\nShadowmaps %u\nOccluders %u",
            primitives,
            batches,
            renderer->GetNumViews(),
            renderer->GetNumLights(true),
            renderer->GetNumShadowMaps(true),
            renderer->GetNumOccluders(true));

        if (!appStats_.Empty())
        {
            stats.Append("\n");
            for (HashMap<String, String>::ConstIterator i = appStats_.Begin(); i != appStats_.End(); ++i)
                stats.AppendWithFormat("\n%s %s", i->first_.CString(), i->second_.CString());
        }

        statsText_->SetText(stats);
    }

    if (modeText_->IsVisible())
    {
        String mode;
        mode.AppendWithFormat("Tex:%s Mat:%s Spec:%s Shadows:%s Size:%i Quality:%s Occlusion:%s Instancing:%s API:%s",
            qualityTexts[renderer->GetTextureQuality()],
            qualityTexts[Min((i32)renderer->GetMaterialQuality(), 3)],
            renderer->GetSpecularLighting() ? "On" : "Off",
            renderer->GetDrawShadows() ? "On" : "Off",
            renderer->GetShadowMapSize(),
            shadowQualityTexts[renderer->GetShadowQuality()],
            renderer->GetMaxOccluderTriangles() > 0 ? "On" : "Off",
            renderer->GetDynamicInstancing() ? "On" : "Off",
            graphics->GetApiName().CString());
    #ifdef URHO3D_OPENGL
        mode.AppendWithFormat(" Renderer:%s Version:%s", graphics->GetRendererName().CString(),
            graphics->GetVersionString().CString());
    #endif


        modeText_->SetText(mode);
    }

    auto* profiler = GetSubsystem<Profiler>();
    auto* eventProfiler = GetSubsystem<EventProfiler>();
    if (profiler)
    {
        if (profilerTimer_.GetMSec(false) >= profilerInterval_)
        {
            profilerTimer_.Reset();

            if (profilerText_->IsVisible())
                profilerText_->SetText(profiler->PrintData(false, false, profilerMaxDepth_));

            profiler->BeginInterval();

            if (eventProfiler)
            {
                if (eventProfilerText_->IsVisible())
                    eventProfilerText_->SetText(eventProfiler->PrintData(false, false, profilerMaxDepth_));

                eventProfiler->BeginInterval();
            }
        }
    }

    if (memoryText_->IsVisible())
        memoryText_->SetText(GetSubsystem<ResourceCache>()->PrintMemoryUsage());
}

void DebugHud::SetDefaultStyle(XMLFile* style)
{
    if (!style)
        return;

    statsText_->SetDefaultStyle(style);
    statsText_->SetStyle("DebugHudText");
    modeText_->SetDefaultStyle(style);
    modeText_->SetStyle("DebugHudText");
    profilerText_->SetDefaultStyle(style);
    profilerText_->SetStyle("DebugHudText");
    memoryText_->SetDefaultStyle(style);
    memoryText_->SetStyle("DebugHudText");
    eventProfilerText_->SetDefaultStyle(style);
    eventProfilerText_->SetStyle("DebugHudText");
}

void DebugHud::SetMode(DebugHudElements mode)
{
    statsText_->SetVisible(!!(mode & DebugHudElements::Stats));
    modeText_->SetVisible(!!(mode & DebugHudElements::Mode));
    profilerText_->SetVisible(!!(mode & DebugHudElements::Profiler));
    memoryText_->SetVisible(!!(mode & DebugHudElements::Memory));
    eventProfilerText_->SetVisible(!!(mode & DebugHudElements::EventProfiler));

    memoryText_->SetPosition(0, modeText_->IsVisible() ? modeText_->GetHeight() * -2 : 0);

#ifdef URHO3D_PROFILING
    // Event profiler is created on engine initialization if "EventProfiler" parameter is set
    auto* eventProfiler = GetSubsystem<EventProfiler>();
    if (eventProfiler)
        EventProfiler::SetActive(!!(mode & DebugHudElements::EventProfiler));
#endif

    mode_ = mode;
}

void DebugHud::SetProfilerMaxDepth(unsigned depth)
{
    profilerMaxDepth_ = depth;
}

void DebugHud::SetProfilerInterval(float interval)
{
    profilerInterval_ = Max((unsigned)(interval * 1000.0f), 0U);
}

void DebugHud::SetUseRendererStats(bool enable)
{
    useRendererStats_ = enable;
}

void DebugHud::Toggle(DebugHudElements mode)
{
    SetMode(GetMode() ^ mode);
}

void DebugHud::ToggleAll()
{
    Toggle(DebugHudElements::All);
}

XMLFile* DebugHud::GetDefaultStyle() const
{
    return statsText_->GetDefaultStyle(false);
}

float DebugHud::GetProfilerInterval() const
{
    return (float)profilerInterval_ / 1000.0f;
}

void DebugHud::SetAppStats(const String& label, const Variant& stats)
{
    SetAppStats(label, stats.ToString());
}

void DebugHud::SetAppStats(const String& label, const String& stats)
{
    bool newLabel = !appStats_.Contains(label);
    appStats_[label] = stats;
    if (newLabel)
        appStats_.Sort();
}

bool DebugHud::ResetAppStats(const String& label)
{
    return appStats_.Erase(label);
}

void DebugHud::ClearAppStats()
{
    appStats_.Clear();
}

void DebugHud::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PostUpdate;

    Update();
}

}
