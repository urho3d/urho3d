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
#include "Context.h"
#include "Log.h"
#include "Technique.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "ShaderVariation.h"
#include "StringUtils.h"
#include "XMLFile.h"

static const String passNames[] =
{
    "base",
    "litbase",
    "light",
    "prealpha",
    "postalpha",
    "gbuffer",
    "material",
    "shadow",
    ""
};

static const String blendModeNames[] =
{
    "replace",
    "add",
    "multiply",
    "alpha",
    "addalpha",
    "premulalpha",
    "invdestalpha",
    ""
};

static const String CompareModeNames[] =
{
    "always",
    "equal",
    "notequal",
    "less",
    "lessequal",
    "greater",
    "greaterequal",
    ""
};

Pass::Pass(PassType type) :
    type_(type),
    alphaTest_(false),
    blendMode_(BLEND_REPLACE),
    depthTestMode_(CMP_LESSEQUAL),
    depthWrite_(true)
{
}

Pass::~Pass()
{
}

void Pass::SetAlphaTest(bool enable)
{
    alphaTest_ = enable;
}

void Pass::SetBlendMode(BlendMode mode)
{
    blendMode_ = mode;
}

void Pass::SetDepthTestMode(CompareMode mode)
{
    depthTestMode_ = mode;
}

void Pass::SetDepthWrite(bool enable)
{
    depthWrite_ = enable;
}

void Pass::SetVertexShader(const String& name)
{
    vertexShaderName_ = name;
    ReleaseShaders();
}

void Pass::SetPixelShader(const String& name)
{
    pixelShaderName_ = name;
    ReleaseShaders();
}

void Pass::ReleaseShaders()
{
    vertexShaders_.Clear();
    pixelShaders_.Clear();
}

OBJECTTYPESTATIC(Technique);

Technique::Technique(Context* context) :
    Resource(context),
    isSM3_(false),
    shadersLoadedFrameNumber_(0)
{
}

Technique::~Technique()
{
}

void Technique::RegisterObject(Context* context)
{
    context->RegisterFactory<Technique>();
}

bool Technique::Load(Deserializer& source)
{
    PROFILE(LoadTechnique);
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    XMLElement rootElem = xml->GetRoot();
    if (rootElem.HasAttribute("sm3"))
        isSM3_ = rootElem.GetBool("sm3");
    
    XMLElement passElem = rootElem.GetChild("pass");
    while (passElem)
    {
        PassType type = MAX_PASSES;
        if (passElem.HasAttribute("name"))
        {
            String name = passElem.GetAttributeLower("name");
            type = (PassType)GetStringListIndex(name, passNames, MAX_PASSES);
            if (type == MAX_PASSES)
                LOGERROR("Unknown pass " + name);
        }
        else
            LOGERROR("Missing pass name");
        
        if (type != MAX_PASSES)
        {
            Pass* newPass = CreatePass(type);
            
            if (passElem.HasAttribute("vs"))
                newPass->SetVertexShader(passElem.GetAttribute("vs"));
            
            if (passElem.HasAttribute("ps"))
                newPass->SetPixelShader(passElem.GetAttribute("ps"));
            
            if (passElem.HasAttribute("alphatest"))
                newPass->SetAlphaTest(passElem.GetBool("alphatest"));
            
            if (passElem.HasAttribute("blend"))
            {
                String blend = passElem.GetAttributeLower("blend");
                newPass->SetBlendMode((BlendMode)GetStringListIndex(blend, blendModeNames, BLEND_REPLACE));
            }
            
            if (passElem.HasAttribute("depthtest"))
            {
                String depthTest = passElem.GetAttributeLower("depthtest");
                if (depthTest == "false")
                    newPass->SetDepthTestMode(CMP_ALWAYS);
                else
                    newPass->SetDepthTestMode((CompareMode)GetStringListIndex(depthTest, CompareModeNames, CMP_LESS));
            }
            
            if (passElem.HasAttribute("depthwrite"))
                newPass->SetDepthWrite(passElem.GetBool("depthwrite"));
        }
        
        passElem = passElem.GetNext("pass");
    }
    
    // Calculate memory use
    unsigned memoryUse = sizeof(Technique);
    for (unsigned i = 0; i < MAX_PASSES; ++i)
    {
        if (passes_[i])
            memoryUse += sizeof(Pass);
    }
    
    SetMemoryUse(memoryUse);
    return true;
}

void Technique::SetIsSM3(bool enable)
{
    isSM3_ = enable;
}

void Technique::ReleaseShaders()
{
    for (unsigned i = 0; i < MAX_PASSES; ++i)
    {
        if (passes_[i])
            passes_[i]->ReleaseShaders();
    }
}

Pass* Technique::CreatePass(PassType pass)
{
    if (!passes_[pass])
        passes_[pass] = new Pass(pass);
    
    return passes_[pass];
}

void Technique::RemovePass(PassType pass)
{
    passes_[pass].Reset();
}

void Technique::MarkShadersLoaded(unsigned frameNumber)
{
    shadersLoadedFrameNumber_ = frameNumber;
}

const String& Technique::GetPassName(PassType pass)
{
    return passNames[pass];
}
