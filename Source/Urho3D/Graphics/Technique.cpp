//
// Copyright (c) 2008-2015 the Urho3D project.
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

#include "../Core/Context.h"
#include "../Graphics/Graphics.h"
#include "../IO/Log.h"
#include "../Graphics/Technique.h"
#include "../Core/ProcessUtils.h"
#include "../Core/Profiler.h"
#include "../Resource/ResourceCache.h"
#include "../Graphics/ShaderVariation.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

const char* blendModeNames[] =
{
    "replace",
    "add",
    "multiply",
    "alpha",
    "addalpha",
    "premulalpha",
    "invdestalpha",
    "subtract",
    "subtractalpha",
    0
};

static const char* compareModeNames[] =
{
    "always",
    "equal",
    "notequal",
    "less",
    "lessequal",
    "greater",
    "greaterequal",
    0
};

static const char* lightingModeNames[] =
{
    "unlit",
    "pervertex",
    "perpixel",
    0
};

static bool desktopSupportChecked = false;
static bool desktopSupportResult = false;

Pass::Pass(StringHash type) :
    type_(type),
    blendMode_(BLEND_REPLACE),
    depthTestMode_(CMP_LESSEQUAL),
    lightingMode_(LIGHTING_UNLIT),
    shadersLoadedFrameNumber_(0),
    depthWrite_(true),
    alphaMask_(false),
    isSM3_(false),
    isDesktop_(false)
{
    // Guess default lighting mode from pass name
    if (type == PASS_BASE || type == PASS_ALPHA || type == PASS_MATERIAL || type == PASS_DEFERRED)
        lightingMode_ = LIGHTING_PERVERTEX;
    else if (type == PASS_LIGHT || type == PASS_LITBASE || type == PASS_LITALPHA)
        lightingMode_ = LIGHTING_PERPIXEL;
}

Pass::~Pass()
{
}

void Pass::SetBlendMode(BlendMode mode)
{
    blendMode_ = mode;
}

void Pass::SetDepthTestMode(CompareMode mode)
{
    depthTestMode_ = mode;
}

void Pass::SetLightingMode(PassLightingMode mode)
{
    lightingMode_ = mode;
}

void Pass::SetDepthWrite(bool enable)
{
    depthWrite_ = enable;
}

void Pass::SetAlphaMask(bool enable)
{
    alphaMask_ = enable;
}

void Pass::SetIsSM3(bool enable)
{
    isSM3_ = enable;
}

void Pass::SetIsDesktop(bool enable)
{
    isDesktop_ = enable;
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

void Pass::SetVertexShaderDefines(const String& defines)
{
    vertexShaderDefines_ = defines;
    ReleaseShaders();
}

void Pass::SetPixelShaderDefines(const String& defines)
{
    pixelShaderDefines_ = defines;
    ReleaseShaders();
}

void Pass::ReleaseShaders()
{
    vertexShaders_.Clear();
    pixelShaders_.Clear();
}

void Pass::MarkShadersLoaded(unsigned frameNumber)
{
    shadersLoadedFrameNumber_ = frameNumber;
}

Technique::Technique(Context* context) :
    Resource(context),
    isSM3_(false),
    isDesktop_(false),
    numPasses_(0)
{
    Graphics* graphics = GetSubsystem<Graphics>();
    sm3Support_ = graphics ? graphics->GetSM3Support() : true;
    
    if (!desktopSupportChecked)
    {
        String platformString = GetPlatform();
        desktopSupportResult = (platformString == "Windows" || platformString == "Mac OS X" || platformString == "Linux");
        desktopSupportChecked = true;
    }
    
    desktopSupport_ = desktopSupportResult;
}

Technique::~Technique()
{
}

void Technique::RegisterObject(Context* context)
{
    context->RegisterFactory<Technique>();
}

bool Technique::BeginLoad(Deserializer& source)
{
    passes_.Clear();

    numPasses_ = 0;
    SetMemoryUse(sizeof(Technique));
    
    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;
    
    XMLElement rootElem = xml->GetRoot();
    if (rootElem.HasAttribute("sm3"))
        isSM3_ = rootElem.GetBool("sm3");
    if (rootElem.HasAttribute("desktop"))
        isDesktop_ = rootElem.GetBool("desktop");
    
    String globalVS = rootElem.GetAttribute("vs");
    String globalPS = rootElem.GetAttribute("ps");
    String globalVSDefines = rootElem.GetAttribute("vsdefines");
    String globalPSDefines = rootElem.GetAttribute("psdefines");
    // End with space so that the pass-specific defines can be appended
    if (!globalVSDefines.Empty())
        globalVSDefines += ' ';
    if (!globalPSDefines.Empty())
        globalPSDefines += ' ';
    bool globalAlphaMask = false;
    if (rootElem.HasAttribute("alphamask"))
        globalAlphaMask = rootElem.GetBool("alphamask");
    
    XMLElement passElem = rootElem.GetChild("pass");
    while (passElem)
    {
        if (passElem.HasAttribute("name"))
        {
            StringHash nameHash(passElem.GetAttribute("name"));
            
            Pass* newPass = CreatePass(nameHash);
            
            if (passElem.HasAttribute("sm3"))
                newPass->SetIsSM3(passElem.GetBool("sm3"));
            if (passElem.HasAttribute("desktop"))
                newPass->SetIsDesktop(passElem.GetBool("desktop"));
            
            // Append global defines only when pass does not redefine the shader
            if (passElem.HasAttribute("vs"))
            {
                newPass->SetVertexShader(passElem.GetAttribute("vs"));
                newPass->SetVertexShaderDefines(passElem.GetAttribute("vsdefines"));
            }
            else
            {
                newPass->SetVertexShader(globalVS);
                newPass->SetVertexShaderDefines(globalVSDefines + passElem.GetAttribute("vsdefines"));
            }
            if (passElem.HasAttribute("ps"))
            {
                newPass->SetPixelShader(passElem.GetAttribute("ps"));
                newPass->SetPixelShaderDefines(passElem.GetAttribute("psdefines"));
            }
            else
            {
                newPass->SetPixelShader(globalPS);
                newPass->SetPixelShaderDefines(globalPSDefines + passElem.GetAttribute("psdefines"));
            }
            
            if (passElem.HasAttribute("lighting"))
            {
                String lighting = passElem.GetAttributeLower("lighting");
                newPass->SetLightingMode((PassLightingMode)GetStringListIndex(lighting.CString(), lightingModeNames,
                    LIGHTING_UNLIT));
            }
            
            if (passElem.HasAttribute("blend"))
            {
                String blend = passElem.GetAttributeLower("blend");
                newPass->SetBlendMode((BlendMode)GetStringListIndex(blend.CString(), blendModeNames, BLEND_REPLACE));
            }
            
            if (passElem.HasAttribute("depthtest"))
            {
                String depthTest = passElem.GetAttributeLower("depthtest");
                if (depthTest == "false")
                    newPass->SetDepthTestMode(CMP_ALWAYS);
                else
                    newPass->SetDepthTestMode((CompareMode)GetStringListIndex(depthTest.CString(), compareModeNames, CMP_LESS));
            }
            
            if (passElem.HasAttribute("depthwrite"))
                newPass->SetDepthWrite(passElem.GetBool("depthwrite"));
            
            if (passElem.HasAttribute("alphamask"))
                newPass->SetAlphaMask(passElem.GetBool("alphamask"));
            else
                newPass->SetAlphaMask(globalAlphaMask);
        }
        else
            LOGERROR("Missing pass name");
        
        passElem = passElem.GetNext("pass");
    }
    
    return true;
}

void Technique::SetIsSM3(bool enable)
{
    isSM3_ = enable;
}

void Technique::SetIsDesktop(bool enable)
{
    isDesktop_ = enable;
}

void Technique::ReleaseShaders()
{
    PODVector<SharedPtr<Pass>*> allPasses = passes_.Values();
    
    for (unsigned i = 0; i < allPasses.Size(); ++i)
        allPasses[i]->Get()->ReleaseShaders();
}

Pass* Technique::CreatePass(StringHash type)
{
    Pass* oldPass = GetPass(type);
    if (oldPass)
        return oldPass;
    
    SharedPtr<Pass> newPass(new Pass(type));
    passes_.Insert(type.Value(), newPass);
    
    // Calculate memory use now
    SetMemoryUse(sizeof(Technique) + ++numPasses_ * sizeof(Pass));

    return newPass;
}

void Technique::RemovePass(StringHash type)
{
    if (passes_.Erase(type.Value()))
        SetMemoryUse(sizeof(Technique) + --numPasses_ * sizeof(Pass));
}

Vector<StringHash> Technique::GetPassTypes() const
{
    // Convert PODVector<unsigned> to Vector<StringHash>
    PODVector<unsigned> vectorIn = passes_.Keys();
    Vector<StringHash> vectorOut;
    vectorOut.Reserve(vectorIn.Size());
    for (unsigned i = 0; i < vectorIn.Size(); ++i)
        vectorOut.Push(StringHash(vectorIn[i]));

    return vectorOut;
}

PODVector<Pass*> Technique::GetPasses() const
{
    // Convert PODVector<SharedPtr<Pass>*> to PODVector<Pass*>
    PODVector<SharedPtr<Pass>*> vectorIn = passes_.Values();
    PODVector<Pass*> vectorOut;
    vectorOut.Reserve(vectorIn.Size());
    for (unsigned i = 0; i < vectorIn.Size(); ++i)
        vectorOut.Push(vectorIn[i]->Get());

    return vectorOut;
}

}
