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

#include "../Graphics/Graphics.h"
#include "../Graphics/Material.h"
#include "../Graphics/RenderPath.h"
#include "../IO/Log.h"
#include "../Resource/XMLFile.h"

#include "../DebugNew.h"

#ifdef _MSC_VER
#pragma warning(disable:6293)
#endif

namespace Urho3D
{

static const char* commandTypeNames[] =
{
    "none",
    "clear",
    "scenepass",
    "quad",
    "forwardlights",
    "lightvolumes",
    "renderui",
    "sendevent",
    nullptr
};

static const char* sortModeNames[] =
{
    "fronttoback",
    "backtofront",
    nullptr
};

extern const char* blendModeNames[];

TextureUnit ParseTextureUnitName(String name);

void RenderTargetInfo::Load(const XMLElement& element)
{
    name_ = element.GetAttribute("name");
    tag_ = element.GetAttribute("tag");
    if (element.HasAttribute("enabled"))
        enabled_ = element.GetBool("enabled");
    if (element.HasAttribute("cubemap"))
        cubemap_ = element.GetBool("cubemap");

    String formatName = element.GetAttribute("format");
    format_ = Graphics::GetFormat(formatName);

    if (element.HasAttribute("filter"))
        filtered_ = element.GetBool("filter");

    if (element.HasAttribute("srgb"))
        sRGB_ = element.GetBool("srgb");

    if (element.HasAttribute("persistent"))
        persistent_ = element.GetBool("persistent");

    if (element.HasAttribute("size"))
        size_ = element.GetVector2("size");
    if (element.HasAttribute("sizedivisor"))
    {
        size_ = element.GetVector2("sizedivisor");
        sizeMode_ = SIZE_VIEWPORTDIVISOR;
    }
    else if (element.HasAttribute("rtsizedivisor"))
    {
        // Deprecated rtsizedivisor mode, acts the same as sizedivisor mode now
        URHO3D_LOGWARNING("Deprecated rtsizedivisor mode used in rendertarget definition");
        size_ = element.GetVector2("rtsizedivisor");
        sizeMode_ = SIZE_VIEWPORTDIVISOR;
    }
    else if (element.HasAttribute("sizemultiplier"))
    {
        size_ = element.GetVector2("sizemultiplier");
        sizeMode_ = SIZE_VIEWPORTMULTIPLIER;
    }

    if (element.HasAttribute("width"))
        size_.x_ = element.GetFloat("width");
    if (element.HasAttribute("height"))
        size_.y_ = element.GetFloat("height");

    if (element.HasAttribute("multisample"))
        multiSample_ = Clamp(element.GetInt("multisample"), 1, 16);
    if (element.HasAttribute("autoresolve"))
        autoResolve_ = element.GetBool("autoresolve");
}

void RenderPathCommand::Load(const XMLElement& element)
{
    type_ = (RenderCommandType)GetStringListIndex(element.GetAttributeLower("type").CString(), commandTypeNames, CMD_NONE);
    tag_ = element.GetAttribute("tag");
    if (element.HasAttribute("enabled"))
        enabled_ = element.GetBool("enabled");
    if (element.HasAttribute("metadata"))
        metadata_ = element.GetAttribute("metadata");

    switch (type_)
    {
    case CMD_CLEAR:
        if (element.HasAttribute("color"))
        {
            clearFlags_ |= CLEAR_COLOR;
            if (element.GetAttributeLower("color") == "fog")
                useFogColor_ = true;
            else
                clearColor_ = element.GetColor("color");
        }
        if (element.HasAttribute("depth"))
        {
            clearFlags_ |= CLEAR_DEPTH;
            clearDepth_ = element.GetFloat("depth");
        }
        if (element.HasAttribute("stencil"))
        {
            clearFlags_ |= CLEAR_STENCIL;
            clearStencil_ = (unsigned)element.GetInt("stencil");
        }
        break;

    case CMD_SCENEPASS:
        pass_ = element.GetAttribute("pass");
        sortMode_ =
            (RenderCommandSortMode)GetStringListIndex(element.GetAttributeLower("sort").CString(), sortModeNames, SORT_FRONTTOBACK);
        if (element.HasAttribute("marktostencil"))
            markToStencil_ = element.GetBool("marktostencil");
        if (element.HasAttribute("vertexlights"))
            vertexLights_ = element.GetBool("vertexlights");
        break;

    case CMD_FORWARDLIGHTS:
        pass_ = element.GetAttribute("pass");
        if (element.HasAttribute("uselitbase"))
            useLitBase_ = element.GetBool("uselitbase");
        break;

    case CMD_LIGHTVOLUMES:
    case CMD_QUAD:
        vertexShaderName_ = element.GetAttribute("vs");
        pixelShaderName_ = element.GetAttribute("ps");

        if (type_ == CMD_QUAD && element.HasAttribute("blend"))
        {
            String blend = element.GetAttributeLower("blend");
            blendMode_ = ((BlendMode)GetStringListIndex(blend.CString(), blendModeNames, BLEND_REPLACE));
        }
        break;

    case CMD_SENDEVENT:
        eventName_ = element.GetAttribute("name");
        break;

    default:
        break;
    }

    // By default use 1 output, which is the viewport
    outputs_.Resize(1);
    outputs_[0] = MakePair(String("viewport"), FACE_POSITIVE_X);
    if (element.HasAttribute("output"))
        outputs_[0].first_ = element.GetAttribute("output");
    if (element.HasAttribute("face"))
        outputs_[0].second_ = (CubeMapFace)element.GetInt("face");
    if (element.HasAttribute("depthstencil"))
        depthStencilName_ = element.GetAttribute("depthstencil");
    // Check for defining multiple outputs
    XMLElement outputElem = element.GetChild("output");
    while (outputElem)
    {
        unsigned index = (unsigned)outputElem.GetInt("index");
        if (index < MAX_RENDERTARGETS)
        {
            if (index >= outputs_.Size())
                outputs_.Resize(index + 1);
            outputs_[index].first_ = outputElem.GetAttribute("name");
            outputs_[index].second_ = outputElem.HasAttribute("face") ? (CubeMapFace)outputElem.GetInt("face") : FACE_POSITIVE_X;
        }
        outputElem = outputElem.GetNext("output");
    }

    // Shader compile flags & parameters
    vertexShaderDefines_ = element.GetAttribute("vsdefines");
    pixelShaderDefines_ = element.GetAttribute("psdefines");
    XMLElement parameterElem = element.GetChild("parameter");
    while (parameterElem)
    {
        String name = parameterElem.GetAttribute("name");
        shaderParameters_[name] = Material::ParseShaderParameterValue(parameterElem.GetAttribute("value"));
        parameterElem = parameterElem.GetNext("parameter");
    }

    // Texture bindings
    XMLElement textureElem = element.GetChild("texture");
    while (textureElem)
    {
        TextureUnit unit = TU_DIFFUSE;
        if (textureElem.HasAttribute("unit"))
            unit = ParseTextureUnitName(textureElem.GetAttribute("unit"));
        if (unit < MAX_TEXTURE_UNITS)
        {
            String name = textureElem.GetAttribute("name");
            textureNames_[unit] = name;
        }

        textureElem = textureElem.GetNext("texture");
    }
}

void RenderPathCommand::SetTextureName(TextureUnit unit, const String& name)
{
    if (unit < MAX_TEXTURE_UNITS)
        textureNames_[unit] = name;
}

void RenderPathCommand::SetShaderParameter(const String& name, const Variant& value)
{
    shaderParameters_[name] = value;
}

void RenderPathCommand::RemoveShaderParameter(const String& name)
{
    shaderParameters_.Erase(name);
}

void RenderPathCommand::SetNumOutputs(unsigned num)
{
    num = (unsigned)Clamp((int)num, 1, MAX_RENDERTARGETS);
    outputs_.Resize(num);
}

void RenderPathCommand::SetOutput(unsigned index, const String& name, CubeMapFace face)
{
    if (index < outputs_.Size())
        outputs_[index] = MakePair(name, face);
    else if (index == outputs_.Size() && index < MAX_RENDERTARGETS)
        outputs_.Push(MakePair(name, face));
}

void RenderPathCommand::SetOutputName(unsigned index, const String& name)
{
    if (index < outputs_.Size())
        outputs_[index].first_ = name;
    else if (index == outputs_.Size() && index < MAX_RENDERTARGETS)
        outputs_.Push(MakePair(name, FACE_POSITIVE_X));
}

void RenderPathCommand::SetOutputFace(unsigned index, CubeMapFace face)
{
    if (index < outputs_.Size())
        outputs_[index].second_ = face;
    else if (index == outputs_.Size() && index < MAX_RENDERTARGETS)
        outputs_.Push(MakePair(String::EMPTY, face));
}


void RenderPathCommand::SetDepthStencilName(const String& name)
{
    depthStencilName_ = name;
}

const String& RenderPathCommand::GetTextureName(TextureUnit unit) const
{
    return unit < MAX_TEXTURE_UNITS ? textureNames_[unit] : String::EMPTY;
}

const Variant& RenderPathCommand::GetShaderParameter(const String& name) const
{
    HashMap<StringHash, Variant>::ConstIterator i = shaderParameters_.Find(name);
    return i != shaderParameters_.End() ? i->second_ : Variant::EMPTY;
}

const String& RenderPathCommand::GetOutputName(unsigned index) const
{
    return index < outputs_.Size() ? outputs_[index].first_ : String::EMPTY;
}

CubeMapFace RenderPathCommand::GetOutputFace(unsigned index) const
{
    return index < outputs_.Size() ? outputs_[index].second_ : FACE_POSITIVE_X;
}

RenderPath::RenderPath() = default;

RenderPath::~RenderPath() = default;

SharedPtr<RenderPath> RenderPath::Clone()
{
    SharedPtr<RenderPath> newRenderPath(new RenderPath());
    newRenderPath->renderTargets_ = renderTargets_;
    newRenderPath->commands_ = commands_;
    return newRenderPath;
}

bool RenderPath::Load(XMLFile* file)
{
    renderTargets_.Clear();
    commands_.Clear();

    return Append(file);
}

bool RenderPath::Append(XMLFile* file)
{
    if (!file)
        return false;

    XMLElement rootElem = file->GetRoot();
    if (!rootElem)
        return false;

    XMLElement rtElem = rootElem.GetChild("rendertarget");
    while (rtElem)
    {
        RenderTargetInfo info;
        info.Load(rtElem);
        if (!info.name_.Trimmed().Empty())
            renderTargets_.Push(info);

        rtElem = rtElem.GetNext("rendertarget");
    }

    XMLElement cmdElem = rootElem.GetChild("command");
    while (cmdElem)
    {
        RenderPathCommand cmd;
        cmd.Load(cmdElem);
        if (cmd.type_ != CMD_NONE)
            commands_.Push(cmd);

        cmdElem = cmdElem.GetNext("command");
    }

    return true;
}

void RenderPath::SetEnabled(const String& tag, bool active)
{
    for (unsigned i = 0; i < renderTargets_.Size(); ++i)
    {
        if (!renderTargets_[i].tag_.Compare(tag, false))
            renderTargets_[i].enabled_ = active;
    }

    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        if (!commands_[i].tag_.Compare(tag, false))
            commands_[i].enabled_ = active;
    }
}

bool RenderPath::IsEnabled(const String& tag) const
{
    for (unsigned i = 0; i < renderTargets_.Size(); ++i)
    {
        if (!renderTargets_[i].tag_.Compare(tag, false) && renderTargets_[i].enabled_)
            return true;
    }

    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        if (!commands_[i].tag_.Compare(tag, false) && commands_[i].enabled_)
            return true;
    }

    return false;
}

bool RenderPath::IsAdded(const String& tag) const
{
    for (unsigned i = 0; i < renderTargets_.Size(); ++i)
    {
        if (!renderTargets_[i].tag_.Compare(tag, false))
            return true;
    }

    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        if (!commands_[i].tag_.Compare(tag, false))
            return true;
    }

    return false;
}

void RenderPath::ToggleEnabled(const String& tag)
{
    for (unsigned i = 0; i < renderTargets_.Size(); ++i)
    {
        if (!renderTargets_[i].tag_.Compare(tag, false))
            renderTargets_[i].enabled_ = !renderTargets_[i].enabled_;
    }

    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        if (!commands_[i].tag_.Compare(tag, false))
            commands_[i].enabled_ = !commands_[i].enabled_;
    }
}

void RenderPath::SetRenderTarget(unsigned index, const RenderTargetInfo& info)
{
    if (index < renderTargets_.Size())
        renderTargets_[index] = info;
    else if (index == renderTargets_.Size())
        AddRenderTarget(info);
}

void RenderPath::AddRenderTarget(const RenderTargetInfo& info)
{
    renderTargets_.Push(info);
}

void RenderPath::RemoveRenderTarget(unsigned index)
{
    renderTargets_.Erase(index);
}

void RenderPath::RemoveRenderTarget(const String& name)
{
    for (unsigned i = 0; i < renderTargets_.Size(); ++i)
    {
        if (!renderTargets_[i].name_.Compare(name, false))
        {
            renderTargets_.Erase(i);
            return;
        }
    }
}

void RenderPath::RemoveRenderTargets(const String& tag)
{
    for (unsigned i = renderTargets_.Size() - 1; i < renderTargets_.Size(); --i)
    {
        if (!renderTargets_[i].tag_.Compare(tag, false))
            renderTargets_.Erase(i);
    }
}

void RenderPath::SetCommand(unsigned index, const RenderPathCommand& command)
{
    if (index < commands_.Size())
        commands_[index] = command;
    else if (index == commands_.Size())
        AddCommand(command);
}

void RenderPath::AddCommand(const RenderPathCommand& command)
{
    commands_.Push(command);
}

void RenderPath::InsertCommand(unsigned index, const RenderPathCommand& command)
{
    commands_.Insert(index, command);
}

void RenderPath::RemoveCommand(unsigned index)
{
    commands_.Erase(index);
}

void RenderPath::RemoveCommands(const String& tag)
{
    for (unsigned i = commands_.Size() - 1; i < commands_.Size(); --i)
    {
        if (!commands_[i].tag_.Compare(tag, false))
            commands_.Erase(i);
    }
}

void RenderPath::SetShaderParameter(const String& name, const Variant& value)
{
    StringHash nameHash(name);

    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        HashMap<StringHash, Variant>::Iterator j = commands_[i].shaderParameters_.Find(nameHash);
        if (j != commands_[i].shaderParameters_.End())
            j->second_ = value;
    }
}

const Variant& RenderPath::GetShaderParameter(const String& name) const
{
    StringHash nameHash(name);

    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        HashMap<StringHash, Variant>::ConstIterator j = commands_[i].shaderParameters_.Find(nameHash);
        if (j != commands_[i].shaderParameters_.End())
            return j->second_;
    }

    return Variant::EMPTY;
}

}
