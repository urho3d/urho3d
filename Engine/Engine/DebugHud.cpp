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

#include "Precompiled.h"
#include "CoreEvents.h"
#include "DebugHud.h"
#include "Engine.h"
#include "Font.h"
#include "Graphics.h"
#include "Log.h"
#include "Profiler.h"
#include "Renderer.h"
#include "StringUtils.h"
#include "Text.h"
#include "UI.h"

#include "DebugNew.h"

OBJECTTYPESTATIC(DebugHud);

DebugHud::DebugHud(Context* context) :
    Object(context),
    profilerInterval_(1.0f),
    profilerTimer_(0.0f),
    useRendererStats_(false)
{
    UI* ui = GetSubsystem<UI>();
    UIElement* uiRoot = ui->GetRootElement();
    
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
    
    SubscribeToEvent(E_UPDATE, HANDLER(DebugHud, HandleUpdate));
}

DebugHud::~DebugHud()
{
    UI* ui = GetSubsystem<UI>();
    if (ui)
    {
        UIElement* uiRoot = ui->GetRootElement();
        uiRoot->RemoveChild(statsText_);
        uiRoot->RemoveChild(modeText_);
        uiRoot->RemoveChild(profilerText_);
    }
}

void DebugHud::Update(float timeStep)
{
    Graphics* graphics = GetSubsystem<Graphics>();
    Renderer* renderer = GetSubsystem<Renderer>();
    if ((!renderer) || (!graphics))
        return;
    
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
    
    if (statsText_->IsVisible())
    {
        std::string stats = 
            "Triangles " + ToString(graphics->GetNumPrimitives()) +
            "\nBatches " + ToString(graphics->GetNumBatches()) +
            "\nViews " + ToString(renderer->GetNumViews()) + 
            "\nLights " + ToString(renderer->GetNumLights(true)) +
            "\nShadowmaps " + ToString(renderer->GetNumShadowMaps(true)) +
            "\nOccluders " + ToString(renderer->GetNumOccluders(true) + renderer->GetNumShadowOccluders(true));
        
        statsText_->SetText(stats);
    }
    
    if (modeText_->IsVisible())
    {
        std::string mode;
        
        RenderMode renderMode = graphics->GetRenderMode();
        if (renderMode == RENDER_FORWARD)
            mode = "Forward";
        else if (renderMode == RENDER_PREPASS)
            mode = "Prepass";
        else
            mode = "Deferred";
        
        int textureQuality = renderer->GetTextureQuality();
        mode += " Tex:";
        if (textureQuality == 0)
            mode += "Low";
        if (textureQuality == 1)
            mode += "Med";
        if (textureQuality == 2)
            mode += "High";
        
        int materialQuality = renderer->GetMaterialQuality();
        mode +=" Mat:";
        if (materialQuality == 0)
            mode += "Low";
        if (materialQuality == 1)
            mode += "Med";
        if (materialQuality == 2)
            mode += "High";
        
        bool specular = renderer->GetSpecularLighting();
        mode += " Spec:";
        if (specular)
            mode += "On";
        else
            mode += "Off";
        
        bool shadows = renderer->GetDrawShadows();
        mode += " Shadows:";
        if (shadows)
            mode += "On";
        else
            mode += "Off";
        
        int shadowMapSize = renderer->GetShadowMapSize();
        mode += " Size:" + ToString(shadowMapSize);
        
        bool shadowMapHiresDepth = renderer->GetShadowMapHiresDepth();
        mode += " Depth:";
        if (shadowMapHiresDepth)
            mode += "24";
        else
            mode += "16";
        
        bool occlusion = renderer->GetMaxOccluderTriangles() > 0;
        mode += " Occlusion:";
        if (occlusion)
            mode += "On";
        else
            mode += "Off";
        
        bool instancing = renderer->GetDynamicInstancing();
        mode += " Instancing:";
        if (instancing)
            mode += "On";
        else
            mode += "Off";
        
        bool sm3 = graphics->GetSM3Support();
        mode += " Mode:";
        if (sm3)
            mode += "SM3";
        else
            mode += "SM2";
        
        modeText_->SetText(mode);
    }
    
    Profiler* profiler = GetSubsystem<Profiler>();
    if (profiler)
    {
        profilerTimer_ += timeStep;
        if (profilerTimer_ >= profilerInterval_)
        {
            if (profilerText_->IsVisible())
            {
                std::string profilerOutput = profiler->GetData(false, true, false);
                profilerText_->SetText(profilerOutput);
            }
            
            profilerTimer_ -= profilerInterval_;
            profiler->ClearAccumulated();
        }
    }
}

void DebugHud::SetStyle(XMLFile* style)
{
    if (!style)
        return;
    
    style_ = style;
    statsText_->SetStyle(style, "DebugHudText");
    modeText_->SetStyle(style, "DebugHudText");
    profilerText_->SetStyle(style, "DebugHudText");
}

void DebugHud::SetMode(unsigned mode)
{
    statsText_->SetVisible((mode & DEBUGHUD_SHOW_STATS) != 0);
    modeText_->SetVisible((mode & DEBUGHUD_SHOW_MODE) != 0);
    profilerText_->SetVisible((mode & DEBUGHUD_SHOW_PROFILER) != 0);
    
    // If profiler text is made visible, force update
    if (profilerText_->IsVisible())
        profilerTimer_ = profilerInterval_;
}

void DebugHud::SetProfilerInterval(float interval)
{
    profilerInterval_ = Max(interval, 0.0f);
}

void DebugHud::SetUseRendererStats(bool enable)
{
    useRendererStats_ = enable;
}

void DebugHud::Toggle(unsigned mode)
{
    SetMode(GetMode() ^ mode);
}

void DebugHud::ToggleAll()
{
    Toggle(DEBUGHUD_SHOW_STATS | DEBUGHUD_SHOW_MODE | DEBUGHUD_SHOW_PROFILER);
}

unsigned DebugHud::GetMode() const
{
    unsigned mode = DEBUGHUD_SHOW_NONE;
    
    if (statsText_->IsVisible())
        mode |= DEBUGHUD_SHOW_STATS;
    if (modeText_->IsVisible())
        mode |= DEBUGHUD_SHOW_MODE;
    if (profilerText_->IsVisible())
        mode |= DEBUGHUD_SHOW_PROFILER;
    
    return mode;
}

void DebugHud::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    
    Update(eventData[P_TIMESTEP].GetFloat());
}
