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
#include "DebugHud.h"
#include "Engine.h"
#include "Font.h"
#include "Log.h"
#include "Pipeline.h"
#include "Profiler.h"
#include "Renderer.h"
#include "StringUtils.h"
#include "Text.h"

#include "DebugNew.h"

DebugHud::DebugHud(Engine* engine) :
    mEngine(engine),
    mProfilerInterval(1.0f),
    mProfilerTimer(0.0f),
    mUsePipelineStats(false)
{
    if (!mEngine)
        EXCEPTION("Null Engine for Debug HUD");
    
    LOGINFO("Debug HUD created");
    
    UIElement* uiRoot = mEngine->getUIRoot();
    if (uiRoot)
    {
        mStatsText = new Text();
        mStatsText->setAlignment(HA_LEFT, VA_TOP);
        mStatsText->setPriority(100);
        mStatsText->setVisible(false);
        uiRoot->addChild(mStatsText);
        
        mModeText = new Text();
        mModeText->setAlignment(HA_LEFT, VA_BOTTOM);
        mModeText->setPriority(100);
        mModeText->setVisible(false);
        uiRoot->addChild(mModeText);
        
        mProfilerText = new Text();
        mProfilerText->setAlignment(HA_RIGHT, VA_TOP);
        mProfilerText->setPriority(100);
        mProfilerText->setVisible(false);
        uiRoot->addChild(mProfilerText);
    }
}

DebugHud::~DebugHud()
{
    UIElement* uiRoot = mEngine->getUIRoot();
    if (uiRoot)
    {
        uiRoot->removeChild(mStatsText);
        uiRoot->removeChild(mModeText);
        uiRoot->removeChild(mProfilerText);
    }
    
    LOGINFO("Debug HUD shut down");
}

void DebugHud::update(float timeStep)
{
    Pipeline* pipeline = mEngine->getPipeline();
    Renderer* renderer = mEngine->getRenderer();
    if ((!pipeline) || (!renderer))
        return;
    
    unsigned primitives, batches;
    if (!mUsePipelineStats)
    {
        primitives = renderer->getNumPrimitives();
        batches = renderer->getNumBatches();
    }
    else
    {
        primitives = pipeline->getNumPrimitives();
        batches = pipeline->getNumBatches();
    }
    
    if (mStatsText->isVisible())
    {
        std::string stats = 
            "Triangles " + toString(renderer->getNumPrimitives()) +
            "\nBatches " + toString(renderer->getNumBatches()) +
            "\nViews " + toString(pipeline->getNumViews()) + 
            "\nLights " + toString(pipeline->getNumLights(true)) +
            "\nShadowmaps " + toString(pipeline->getNumShadowMaps(true)) +
            "\nOccluders " + toString(pipeline->getNumOccluders(true) + pipeline->getNumShadowOccluders(true));
        
        mStatsText->setText(stats);
    }
    
    if (mModeText->isVisible())
    {
        std::string mode;
        
        RenderMode renderMode = renderer->getRenderMode();
        switch (renderMode)
        {
        case RENDER_DEFERRED:
            mode += "Deferred";
            break;
            
        case RENDER_PREPASS:
            mode += "Prepass";
            break;
            
        case RENDER_FORWARD:
            mode += "Forward";
            break;
        }
        
        int textureQuality = pipeline->getTextureQuality();
        mode += " Tex:";
        if (textureQuality == 0)
            mode += "Low";
        if (textureQuality == 1)
            mode += "Med";
        if (textureQuality == 2)
            mode += "High";
        
        int materialQuality = pipeline->getMaterialQuality();
        mode +=" Mat:";
        if (materialQuality == 0)
            mode += "Low";
        if (materialQuality == 1)
            mode += "Med";
        if (materialQuality == 2)
            mode += "High";
        
        bool specular = pipeline->getSpecularLighting();
        mode += " Spec:";
        if (specular)
            mode += "On";
        else
            mode += "Off";
        
        bool shadows = pipeline->getDrawShadows();
        mode += " Shadows:";
        if (shadows)
            mode += "On";
        else
            mode += "Off";
        
        int shadowMapSize = pipeline->getShadowMapSize();
        mode += " Size:" + toString(shadowMapSize);
        
        bool shadowMapHiresDepth = pipeline->getShadowMapHiresDepth();
        mode += " Depth:";
        if (shadowMapHiresDepth)
            mode += "24";
        else
            mode += "16";
        
        bool occlusion = pipeline->getMaxOccluderTriangles() > 0;
        mode += " Occlusion:";
        if (occlusion)
            mode += "On";
        else
            mode += "Off";
        
        bool sm3 = renderer->getSM3Support();
        mode += " Mode:";
        if (sm3)
            mode += "SM3";
        else
            mode += "SM2";
        
        mModeText->setText(mode);
    }
    
    Profiler* profiler = mEngine->getProfiler();
    
    mProfilerTimer += timeStep;
    if (mProfilerTimer >= mProfilerInterval)
    {
        if (mProfilerText->isVisible())
        {
            std::string profilerOutput = profiler->getData(false, true, false);
            mProfilerText->setText(profilerOutput);
        }
        
        mProfilerTimer -= mProfilerInterval;
        profiler->clearAccumulated();
    }
}

void DebugHud::setStyle(XMLFile* style)
{
    if ((!style) || (!mEngine) || (!mStatsText) || (!mModeText) || (!mProfilerText))
        return;
    
    mStyle = style;
    ResourceCache* cache = mEngine->getResourceCache();
    mStatsText->setStyle(style, "DebugHudText", cache);
    mModeText->setStyle(style, "DebugHudText", cache);
    mProfilerText->setStyle(style, "DebugHudText", cache);
}

void DebugHud::setMode(unsigned mode)
{
    if ((!mStatsText) || (!mModeText) || (!mProfilerText))
        return;
    
    mStatsText->setVisible((mode & DEBUGHUD_SHOW_STATS) != 0);
    mModeText->setVisible((mode & DEBUGHUD_SHOW_MODE) != 0);
    mProfilerText->setVisible((mode & DEBUGHUD_SHOW_PROFILER) != 0);
    
    // If profiler text is made visible, force update
    if (mProfilerText->isVisible())
        mProfilerTimer = mProfilerInterval;
}

void DebugHud::setProfilerInterval(float interval)
{
    mProfilerInterval = max(interval, 0.0f);
}

void DebugHud::setUsePipelineStats(bool enable)
{
    mUsePipelineStats = enable;
}

void DebugHud::toggle(unsigned mode)
{
    setMode(getMode() ^ mode);
}

void DebugHud::toggleAll()
{
    toggle(DEBUGHUD_SHOW_STATS | DEBUGHUD_SHOW_MODE | DEBUGHUD_SHOW_PROFILER);
}

unsigned DebugHud::getMode() const
{
    unsigned mode = DEBUGHUD_SHOW_NONE;
    
    if ((!mStatsText) || (!mModeText) || (!mProfilerText))
        return mode;
    
    if (mStatsText->isVisible())
        mode |= DEBUGHUD_SHOW_STATS;
    if (mModeText->isVisible())
        mode |= DEBUGHUD_SHOW_MODE;
    if (mProfilerText->isVisible())
        mode |= DEBUGHUD_SHOW_PROFILER;
    
    return mode;
}
