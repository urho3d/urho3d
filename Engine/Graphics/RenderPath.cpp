//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "Graphics.h"
#include "RenderPath.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

static const String commandTypeNames[] =
{
    "none",
    "clear",
    "scenepass",
    "quad",
    "forwardlights",
    "lightvolumes",
    ""
};

static const String sortModeNames[] =
{
    "fronttoback"
    "backtofront",
    ""
};

TextureUnit ParseTextureUnitName(const String& name);

void RenderTargetInfo::LoadParameters(const XMLElement& element)
{
    name_ = element.GetAttribute("name");
    tag_ = element.GetAttribute("tag");
    if (element.HasAttribute("active"))
        active_ = element.GetBool("active");
    
    String formatName = element.GetAttribute("format");
    format_ = Graphics::GetFormat(formatName);
    
    if (element.HasAttribute("filter"))
        filtered_ = element.GetBool("filter");
   
    if (element.HasAttribute("size"))
        size_ = element.GetIntVector2("size");
    if (element.HasAttribute("sizedivisor"))
    {
        size_ = element.GetIntVector2("sizedivisor");
        sizeMode_ = SIZE_VIEWPORTDIVISOR;
    }
    if (element.HasAttribute("rtsizedivisor"))
    {
        size_ = element.GetIntVector2("rtsizedivisor");
        sizeMode_ = SIZE_RENDERTARGETDIVISOR;
    }
    
    if (element.HasAttribute("width"))
        size_.x_ = element.GetInt("width");
    if (element.HasAttribute("height"))
        size_.y_ = element.GetInt("height");
}

void RenderPathCommand::LoadParameters(const XMLElement& element)
{
    type_ = (RenderCommandType)GetStringListIndex(element.GetAttributeLower("type"), commandTypeNames, CMD_NONE);
    tag_ = element.GetAttribute("tag");
    if (element.HasAttribute("active"))
        active_ = element.GetBool("active");
    
    switch (type_)
    {
    case CMD_CLEAR:
        if (element.HasAttribute("color"))
        {
            clearFlags_ |= CLEAR_COLOR;
            // Mark fog color with negative values
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
            clearStencil_ = element.GetInt("stencil");
        }
        break;
        
    case CMD_SCENEPASS:
        pass_ = StringHash(element.GetAttribute("pass"));
        sortMode_ = (RenderCommandSortMode)GetStringListIndex(element.GetAttributeLower("sort"), sortModeNames, SORT_FRONTTOBACK);
        if (element.HasAttribute("marktostencil"))
            markToStencil_ = element.GetBool("marktostencil");
        if (element.HasAttribute("vertexlights"))
            vertexLights_ = element.GetBool("vertexlights");
        if (element.HasAttribute("usescissor"))
            useScissor_ = element.GetBool("usescissor");
        break;
        
    case CMD_LIGHTVOLUMES:
    case CMD_QUAD:
        vertexShaderName_ = element.GetAttribute("vs");
        pixelShaderName_ = element.GetAttribute("ps");
        if (type_ == CMD_QUAD)
        {
            XMLElement parameterElem = element.GetChild("parameter");
            while (parameterElem)
            {
                String name = parameterElem.GetAttribute("name");
                Vector4 value = parameterElem.GetVector("value");
                shaderParameters_[StringHash(name)] = value;
                
                parameterElem = parameterElem.GetNext("parameter");
            }
        }
        break;
    }
    
    // By default use 1 output, which is the viewport
    outputs_.Push("viewport");
    if (element.HasAttribute("output"))
        outputs_[0] = element.GetAttribute("output");
    // Check for defining multiple outputs
    XMLElement outputElem = element.GetChild("output");
    while (outputElem)
    {
        unsigned index = outputElem.GetInt("index");
        if (index < MAX_RENDERTARGETS)
        {
            if (index >= outputs_.Size())
                outputs_.Resize(index + 1);
            outputs_[index] = outputElem.GetAttribute("name");
        }
        outputElem = outputElem.GetNext("output");
    }
    
    XMLElement textureElem = element.GetChild("texture");
    while (textureElem)
    {
        TextureUnit unit = TU_DIFFUSE;
        if (textureElem.HasAttribute("unit"))
        {
            String unitName = textureElem.GetAttributeLower("unit");
            if (unitName.Length() > 1)
                unit = ParseTextureUnitName(unitName);
            else
                unit = (TextureUnit)Clamp(ToInt(unitName), 0, MAX_TEXTURE_UNITS - 1);
        }
        if (unit < MAX_TEXTURE_UNITS)
        {
            String name = textureElem.GetAttribute("name");
            textureNames_[unit] = name;
        }
        
        textureElem = textureElem.GetNext("texture");
    }
}

RenderPath::RenderPath()
{
}

RenderPath::~RenderPath()
{
}

SharedPtr<RenderPath> RenderPath::Clone()
{
    SharedPtr<RenderPath> newRenderPath(new RenderPath());
    newRenderPath->renderTargets_ = renderTargets_;
    newRenderPath->commands_ = commands_;
    return newRenderPath;
}

bool RenderPath::LoadParameters(XMLFile* file)
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
        info.LoadParameters(rtElem);
        if (!info.name_.Trimmed().Empty())
            renderTargets_.Push(info);
        
        rtElem = rtElem.GetNext("rendertarget");
    }
    
    XMLElement cmdElem = rootElem.GetChild("command");
    while (cmdElem)
    {
        RenderPathCommand cmd;
        cmd.LoadParameters(cmdElem);
        if (cmd.type_ != CMD_NONE)
            commands_.Push(cmd);
        
        cmdElem = cmdElem.GetNext("command");
    }
    
    return true;
}

void RenderPath::SetActive(const String& tag, bool active)
{
    for (unsigned i = 0; i < renderTargets_.Size(); ++i)
    {
        if (!renderTargets_[i].tag_.Compare(tag, false))
            renderTargets_[i].active_ = active;
    }
    
    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        if (!commands_[i].tag_.Compare(tag, false))
            commands_[i].active_ = active;
    }
}

void RenderPath::ToggleActive(const String& tag)
{
    for (unsigned i = 0; i < renderTargets_.Size(); ++i)
    {
        if (!renderTargets_[i].tag_.Compare(tag, false))
            renderTargets_[i].active_ = !renderTargets_[i].active_;
    }
    
    for (unsigned i = 0; i < commands_.Size(); ++i)
    {
        if (!commands_[i].tag_.Compare(tag, false))
            commands_[i].active_ = !commands_[i].active_;
    }
}

}
