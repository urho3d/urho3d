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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/ProcessUtils.h"
#include "../Core/Profiler.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/Technique.h"
#include "../Graphics/ShaderVariation.h"
#include "../IO/Log.h"
#include "../Resource/ResourceCache.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

namespace Urho3D
{

extern const char* cullModeNames[];

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
    nullptr
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
    nullptr
};

static const char* lightingModeNames[] =
{
    "unlit",
    "pervertex",
    "perpixel",
    nullptr
};

Pass::Pass(const String& name) :
    blendMode_(BLEND_REPLACE),
    cullMode_(MAX_CULLMODES),
    depthTestMode_(CMP_LESSEQUAL),
    lightingMode_(LIGHTING_UNLIT),
    shadersLoadedFrameNumber_(0),
    alphaToCoverage_(false),
    depthWrite_(true),
    isDesktop_(false)
{
    name_ = name.ToLower();
    index_ = Technique::GetPassIndex(name_);

    // Guess default lighting mode from pass name
    if (index_ == Technique::basePassIndex || index_ == Technique::alphaPassIndex || index_ == Technique::materialPassIndex ||
        index_ == Technique::deferredPassIndex)
        lightingMode_ = LIGHTING_PERVERTEX;
    else if (index_ == Technique::lightPassIndex || index_ == Technique::litBasePassIndex || index_ == Technique::litAlphaPassIndex)
        lightingMode_ = LIGHTING_PERPIXEL;
}

Pass::~Pass() = default;

void Pass::SetBlendMode(BlendMode mode)
{
    blendMode_ = mode;
}

void Pass::SetCullMode(CullMode mode)
{
    cullMode_ = mode;
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

void Pass::SetAlphaToCoverage(bool enable)
{
    alphaToCoverage_ = enable;
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

void Pass::SetVertexShaderDefineExcludes(const String& excludes)
{
    vertexShaderDefineExcludes_ = excludes;
    ReleaseShaders();
}

void Pass::SetPixelShaderDefineExcludes(const String& excludes)
{
    pixelShaderDefineExcludes_ = excludes;
    ReleaseShaders();
}

void Pass::ReleaseShaders()
{
    vertexShaders_.Clear();
    pixelShaders_.Clear();
    extraVertexShaders_.Clear();
    extraPixelShaders_.Clear();
}

void Pass::MarkShadersLoaded(unsigned frameNumber)
{
    shadersLoadedFrameNumber_ = frameNumber;
}

String Pass::GetEffectiveVertexShaderDefines() const
{
    // Prefer to return just the original defines if possible
    if (vertexShaderDefineExcludes_.Empty())
        return vertexShaderDefines_;

    Vector<String> vsDefines = vertexShaderDefines_.Split(' ');
    Vector<String> vsExcludes = vertexShaderDefineExcludes_.Split(' ');
    for (unsigned i = 0; i < vsExcludes.Size(); ++i)
        vsDefines.Remove(vsExcludes[i]);

    return String::Joined(vsDefines, " ");
}

String Pass::GetEffectivePixelShaderDefines() const
{
    // Prefer to return just the original defines if possible
    if (pixelShaderDefineExcludes_.Empty())
        return pixelShaderDefines_;

    Vector<String> psDefines = pixelShaderDefines_.Split(' ');
    Vector<String> psExcludes = pixelShaderDefineExcludes_.Split(' ');
    for (unsigned i = 0; i < psExcludes.Size(); ++i)
        psDefines.Remove(psExcludes[i]);

    return String::Joined(psDefines, " ");
}

Vector<SharedPtr<ShaderVariation> >& Pass::GetVertexShaders(const StringHash& extraDefinesHash)
{
    // If empty hash, return the base shaders
    if (!extraDefinesHash.Value())
        return vertexShaders_;
    else
        return extraVertexShaders_[extraDefinesHash];
}

Vector<SharedPtr<ShaderVariation> >& Pass::GetPixelShaders(const StringHash& extraDefinesHash)
{
    if (!extraDefinesHash.Value())
        return pixelShaders_;
    else
        return extraPixelShaders_[extraDefinesHash];
}

unsigned Technique::basePassIndex = 0;
unsigned Technique::alphaPassIndex = 0;
unsigned Technique::materialPassIndex = 0;
unsigned Technique::deferredPassIndex = 0;
unsigned Technique::lightPassIndex = 0;
unsigned Technique::litBasePassIndex = 0;
unsigned Technique::litAlphaPassIndex = 0;
unsigned Technique::shadowPassIndex = 0;

HashMap<String, unsigned> Technique::passIndices;

Technique::Technique(Context* context) :
    Resource(context),
    isDesktop_(false)
{
#ifdef DESKTOP_GRAPHICS
    desktopSupport_ = true;
#else
    desktopSupport_ = false;
#endif
}

Technique::~Technique() = default;

void Technique::RegisterObject(Context* context)
{
    context->RegisterFactory<Technique>();
}

bool Technique::BeginLoad(Deserializer& source)
{
    passes_.Clear();
    cloneTechniques_.Clear();

    SetMemoryUse(sizeof(Technique));

    SharedPtr<XMLFile> xml(new XMLFile(context_));
    if (!xml->Load(source))
        return false;

    XMLElement rootElem = xml->GetRoot();
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

    XMLElement passElem = rootElem.GetChild("pass");
    while (passElem)
    {
        if (passElem.HasAttribute("name"))
        {
            Pass* newPass = CreatePass(passElem.GetAttribute("name"));

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

            newPass->SetVertexShaderDefineExcludes(passElem.GetAttribute("vsexcludes"));
            newPass->SetPixelShaderDefineExcludes(passElem.GetAttribute("psexcludes"));

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

            if (passElem.HasAttribute("cull"))
            {
                String cull = passElem.GetAttributeLower("cull");
                newPass->SetCullMode((CullMode)GetStringListIndex(cull.CString(), cullModeNames, MAX_CULLMODES));
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

            if (passElem.HasAttribute("alphatocoverage"))
                newPass->SetAlphaToCoverage(passElem.GetBool("alphatocoverage"));
        }
        else
            URHO3D_LOGERROR("Missing pass name");

        passElem = passElem.GetNext("pass");
    }

    return true;
}

void Technique::SetIsDesktop(bool enable)
{
    isDesktop_ = enable;
}

void Technique::ReleaseShaders()
{
    for (Vector<SharedPtr<Pass> >::ConstIterator i = passes_.Begin(); i != passes_.End(); ++i)
    {
        Pass* pass = i->Get();
        if (pass)
            pass->ReleaseShaders();
    }
}

SharedPtr<Technique> Technique::Clone(const String& cloneName) const
{
    SharedPtr<Technique> ret(new Technique(context_));
    ret->SetIsDesktop(isDesktop_);
    ret->SetName(cloneName);

    // Deep copy passes
    for (Vector<SharedPtr<Pass> >::ConstIterator i = passes_.Begin(); i != passes_.End(); ++i)
    {
        Pass* srcPass = i->Get();
        if (!srcPass)
            continue;

        Pass* newPass = ret->CreatePass(srcPass->GetName());
        newPass->SetCullMode(srcPass->GetCullMode());
        newPass->SetBlendMode(srcPass->GetBlendMode());
        newPass->SetDepthTestMode(srcPass->GetDepthTestMode());
        newPass->SetLightingMode(srcPass->GetLightingMode());
        newPass->SetDepthWrite(srcPass->GetDepthWrite());
        newPass->SetAlphaToCoverage(srcPass->GetAlphaToCoverage());
        newPass->SetIsDesktop(srcPass->IsDesktop());
        newPass->SetVertexShader(srcPass->GetVertexShader());
        newPass->SetPixelShader(srcPass->GetPixelShader());
        newPass->SetVertexShaderDefines(srcPass->GetVertexShaderDefines());
        newPass->SetPixelShaderDefines(srcPass->GetPixelShaderDefines());
        newPass->SetVertexShaderDefineExcludes(srcPass->GetVertexShaderDefineExcludes());
        newPass->SetPixelShaderDefineExcludes(srcPass->GetPixelShaderDefineExcludes());
    }

    return ret;
}

Pass* Technique::CreatePass(const String& name)
{
    Pass* oldPass = GetPass(name);
    if (oldPass)
        return oldPass;

    SharedPtr<Pass> newPass(new Pass(name));
    unsigned passIndex = newPass->GetIndex();
    if (passIndex >= passes_.Size())
        passes_.Resize(passIndex + 1);
    passes_[passIndex] = newPass;

    // Calculate memory use now
    SetMemoryUse((unsigned)(sizeof(Technique) + GetNumPasses() * sizeof(Pass)));

    return newPass;
}

void Technique::RemovePass(const String& name)
{
    HashMap<String, unsigned>::ConstIterator i = passIndices.Find(name.ToLower());
    if (i == passIndices.End())
        return;
    else if (i->second_ < passes_.Size() && passes_[i->second_].Get())
    {
        passes_[i->second_].Reset();
        SetMemoryUse((unsigned)(sizeof(Technique) + GetNumPasses() * sizeof(Pass)));
    }
}

bool Technique::HasPass(const String& name) const
{
    HashMap<String, unsigned>::ConstIterator i = passIndices.Find(name.ToLower());
    return i != passIndices.End() ? HasPass(i->second_) : false;
}

Pass* Technique::GetPass(const String& name) const
{
    HashMap<String, unsigned>::ConstIterator i = passIndices.Find(name.ToLower());
    return i != passIndices.End() ? GetPass(i->second_) : nullptr;
}

Pass* Technique::GetSupportedPass(const String& name) const
{
    HashMap<String, unsigned>::ConstIterator i = passIndices.Find(name.ToLower());
    return i != passIndices.End() ? GetSupportedPass(i->second_) : nullptr;
}

unsigned Technique::GetNumPasses() const
{
    unsigned ret = 0;

    for (Vector<SharedPtr<Pass> >::ConstIterator i = passes_.Begin(); i != passes_.End(); ++i)
    {
        if (i->Get())
            ++ret;
    }

    return ret;
}

Vector<String> Technique::GetPassNames() const
{
    Vector<String> ret;

    for (Vector<SharedPtr<Pass> >::ConstIterator i = passes_.Begin(); i != passes_.End(); ++i)
    {
        Pass* pass = i->Get();
        if (pass)
            ret.Push(pass->GetName());
    }

    return ret;
}

PODVector<Pass*> Technique::GetPasses() const
{
    PODVector<Pass*> ret;

    for (Vector<SharedPtr<Pass> >::ConstIterator i = passes_.Begin(); i != passes_.End(); ++i)
    {
        Pass* pass = i->Get();
        if (pass)
            ret.Push(pass);
    }

    return ret;
}

SharedPtr<Technique> Technique::CloneWithDefines(const String& vsDefines, const String& psDefines)
{
    // Return self if no actual defines
    if (vsDefines.Empty() && psDefines.Empty())
        return SharedPtr<Technique>(this);

    Pair<StringHash, StringHash> key = MakePair(StringHash(vsDefines), StringHash(psDefines));

    // Return existing if possible
    HashMap<Pair<StringHash, StringHash>, SharedPtr<Technique> >::Iterator i = cloneTechniques_.Find(key);
    if (i != cloneTechniques_.End())
        return i->second_;

    // Set same name as the original for the clones to ensure proper serialization of the material. This should not be a problem
    // since the clones are never stored to the resource cache
    i = cloneTechniques_.Insert(MakePair(key, Clone(GetName())));

    for (Vector<SharedPtr<Pass> >::ConstIterator j = i->second_->passes_.Begin(); j != i->second_->passes_.End(); ++j)
    {
        Pass* pass = (*j);
        if (!pass)
            continue;

        if (!vsDefines.Empty())
            pass->SetVertexShaderDefines(pass->GetVertexShaderDefines() + " " + vsDefines);
        if (!psDefines.Empty())
            pass->SetPixelShaderDefines(pass->GetPixelShaderDefines() + " " + psDefines);
    }

    return i->second_;
}

unsigned Technique::GetPassIndex(const String& passName)
{
    // Initialize built-in pass indices on first call
    if (passIndices.Empty())
    {
        basePassIndex = passIndices["base"] = 0;
        alphaPassIndex = passIndices["alpha"] = 1;
        materialPassIndex = passIndices["material"] = 2;
        deferredPassIndex = passIndices["deferred"] = 3;
        lightPassIndex = passIndices["light"] = 4;
        litBasePassIndex = passIndices["litbase"] = 5;
        litAlphaPassIndex = passIndices["litalpha"] = 6;
        shadowPassIndex = passIndices["shadow"] = 7;
    }

    String nameLower = passName.ToLower();
    HashMap<String, unsigned>::Iterator i = passIndices.Find(nameLower);
    if (i != passIndices.End())
        return i->second_;
    else
    {
        unsigned newPassIndex = passIndices.Size();
        passIndices[nameLower] = newPassIndex;
        return newPassIndex;
    }
}

}
