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
#include "Camera.h"
#include "Graphics.h"
#include "Log.h"
#include "PostProcess.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

TextureUnit ParseTextureUnitName(const String& name);

static const String commandTypeNames[] =
{
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

OBJECTTYPESTATIC(Viewport);

Viewport::Viewport(Context* context) :
    Object(context),
    rect_(IntRect::ZERO)
{
    SetRenderPath(0);
}

Viewport::Viewport(Context* context, Scene* scene, Camera* camera, XMLFile* renderPath) :
    Object(context),
    scene_(scene),
    camera_(camera),
    rect_(IntRect::ZERO)
{
    SetRenderPath(renderPath);
}

Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, XMLFile* renderPath) :
    Object(context),
    scene_(scene),
    camera_(camera),
    rect_(rect)
{
    SetRenderPath(renderPath);
}

Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const Vector<SharedPtr<PostProcess> >& postProcesses, XMLFile* renderPath) :
    Object(context),
    scene_(scene),
    camera_(camera),
    rect_(IntRect::ZERO),
    postProcesses_(postProcesses)
{
    SetRenderPath(renderPath);
}

Viewport::Viewport(Context* context, Scene* scene, Camera* camera, const IntRect& rect, const Vector<SharedPtr<PostProcess> >& postProcesses, XMLFile* renderPath) :
    Object(context),
    scene_(scene),
    camera_(camera),
    rect_(rect),
    postProcesses_(postProcesses)
{
    SetRenderPath(renderPath);
}

Viewport::~Viewport()
{
}

void Viewport::SetScene(Scene* scene)
{
    scene_ = scene;
}

void Viewport::SetCamera(Camera* camera)
{
    camera_ = camera;
}

void Viewport::SetRect(const IntRect& rect)
{
    rect_ = rect;
}

bool Viewport::SetRenderPath(XMLFile* file)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    Renderer* renderer = GetSubsystem<Renderer>();
    if (!file && cache && renderer)
        file = cache->GetResource<XMLFile>(renderer->GetDefaultRenderPathName());
    if (!file)
        return false;
    
    XMLElement rootElem = file->GetRoot();
    if (!rootElem)
        return false;
    
    renderPath_.renderTargets_.Clear();
    renderPath_.commands_.Clear();
    
    XMLElement rtElem = rootElem.GetChild("rendertarget");
    while (rtElem)
    {
        String name = rtElem.GetAttribute("name");
        
        String formatName = rtElem.GetAttribute("format");
        unsigned format = Graphics::GetFormat(formatName);
        
        bool sizeDivisor = false;
        bool filtered = false;
        unsigned width = 0;
        unsigned height = 0;
        
        if (rtElem.HasAttribute("filter"))
            filtered = rtElem.GetBool("filter");
        if (rtElem.HasAttribute("size"))
        {
            IntVector2 size = rtElem.GetIntVector2("size");
            width = size.x_;
            height = size.y_;
        }
        if (rtElem.HasAttribute("width"))
            width = rtElem.GetInt("width");
        if (rtElem.HasAttribute("height"))
            height = rtElem.GetInt("height");
        if (rtElem.HasAttribute("sizedivisor"))
        {
            IntVector2 size = rtElem.GetIntVector2("sizedivisor");
            width = size.x_;
            height = size.y_;
            sizeDivisor = true;
        }
        
        if (!name.Trimmed().Empty())
        {
            RenderTargetInfo rtInfo;
            rtInfo.name_ = name;
            rtInfo.format_ = format;
            rtInfo.size_ = IntVector2(width, height),
            rtInfo.sizeDivisor_ = sizeDivisor;
            rtInfo.filtered_ = filtered;
            renderPath_.renderTargets_.Push(rtInfo);
        }
        
        rtElem = rtElem.GetNext("rendertarget");
    }
    
    XMLElement commandElem = rootElem.GetChild("command");
    while (commandElem)
    {
        RenderCommandType type = (RenderCommandType)GetStringListIndex(commandElem.GetAttributeLower("type"), commandTypeNames,
            CMD_UNKNOWN);
        if (type != CMD_UNKNOWN)
        {
            RenderPathCommand command;
            command.type_ = type;
            
            switch (type)
            {
            case CMD_CLEAR:
                if (commandElem.HasAttribute("color"))
                {
                    command.clearFlags_ |= CLEAR_COLOR;
                    // Mark fog color with negative values
                    if (commandElem.GetAttributeLower("color") == "fog")
                        command.clearColor_ = Color(-1.0f, -1.0f, -1.0f, -1.0f);
                    else
                        command.clearColor_ = commandElem.GetColor("color");
                }
                if (commandElem.HasAttribute("depth"))
                {
                    command.clearFlags_ |= CLEAR_DEPTH;
                    command.clearDepth_ = commandElem.GetFloat("depth");
                }
                if (commandElem.HasAttribute("stencil"))
                {
                    command.clearFlags_ |= CLEAR_STENCIL;
                    command.clearStencil_ = commandElem.GetInt("stencil");
                }
                break;
            
            case CMD_SCENEPASS:
                command.pass_ = StringHash(commandElem.GetAttribute("pass"));
                command.sortMode_ = (RenderCommandSortMode)GetStringListIndex(commandElem.GetAttributeLower("sort"), sortModeNames, SORT_FRONTTOBACK);
                if (commandElem.HasAttribute("marktostencil"))
                    command.markToStencil_ = commandElem.GetBool("marktostencil");
                if (commandElem.HasAttribute("vertexlights"))
                    command.vertexLights_ = commandElem.GetBool("vertexlights");
                if (commandElem.HasAttribute("usescissor"))
                    command.useScissor_ = commandElem.GetBool("usescissor");
                break;
                
            case CMD_LIGHTVOLUMES:
            case CMD_QUAD:
                command.vertexShaderName_ = commandElem.GetAttribute("vs");
                command.pixelShaderName_ = commandElem.GetAttribute("ps");
                if (type == CMD_QUAD)
                {
                    XMLElement parameterElem = commandElem.GetChild("parameter");
                    while (parameterElem)
                    {
                        String name = parameterElem.GetAttribute("name");
                        Vector4 value = parameterElem.GetVector("value");
                        command.shaderParameters_[StringHash(name)] = value;
                        
                        parameterElem = parameterElem.GetNext("parameter");
                    }
                }
                break;
            }
            
            // By default use 1 output, which is the viewport
            command.outputs_.Push("viewport");
            if (commandElem.HasAttribute("output"))
                command.outputs_[0] = commandElem.GetAttribute("output");
            // Check for defining multiple outputs
            XMLElement outputElem = commandElem.GetChild("output");
            while (outputElem)
            {
                unsigned index = outputElem.GetInt("index");
                if (index < MAX_RENDERTARGETS)
                {
                    if (index >= command.outputs_.Size())
                        command.outputs_.Resize(index + 1);
                    command.outputs_[index] = outputElem.GetAttribute("name");
                }
                outputElem = outputElem.GetNext("output");
            }
            
            XMLElement textureElem = commandElem.GetChild("texture");
            while (textureElem)
            {
                TextureUnit unit = TU_DIFFUSE;
                if (textureElem.HasAttribute("unit"))
                {
                    String unitName = textureElem.GetAttributeLower("unit");
                    if (unitName.Length() > 1)
                    {
                        unit = ParseTextureUnitName(unitName);
                        if (unit >= MAX_TEXTURE_UNITS)
                            LOGERROR("Unknown texture unit " + unitName);
                    }
                    else
                        unit = (TextureUnit)Clamp(ToInt(unitName), 0, MAX_TEXTURE_UNITS - 1);
                }
                if (unit < MAX_TEXTURE_UNITS)
                {
                    String name = textureElem.GetAttribute("name");
                    command.textureNames_[unit] = name;
                }
                
                textureElem = textureElem.GetNext("texture");
            }
            
            renderPath_.commands_.Push(command);
        }
        
        commandElem = commandElem.GetNext("command");
    }
    
    return true;
}

void Viewport::AddPostProcess(PostProcess* effect)
{
    if (!effect)
        return;
    
    SharedPtr<PostProcess> effectPtr(effect);
    if (!postProcesses_.Contains(effectPtr))
        postProcesses_.Push(effectPtr);
}

void Viewport::InsertPostProcess(unsigned index, PostProcess* effect)
{
    if (!effect)
        return;
    
    SharedPtr<PostProcess> effectPtr(effect);
    if (postProcesses_.Contains(effectPtr))
        return;
    
    if (index >= postProcesses_.Size())
        postProcesses_.Push(effectPtr);
    else
        postProcesses_.Insert(index, effectPtr);
}

void Viewport::RemovePostProcess(PostProcess* effect)
{
    for (Vector<SharedPtr<PostProcess> >::Iterator i = postProcesses_.Begin(); i != postProcesses_.End(); ++i)
    {
        if (i->Get() == effect)
        {
            postProcesses_.Erase(i);
            return;
        }
    }
}

void Viewport::RemovePostProcess(unsigned index)
{
    postProcesses_.Erase(index);
}

void Viewport::RemoveAllPostProcesses()
{
    postProcesses_.Clear();
}

Scene* Viewport::GetScene() const
{
    return scene_;
}

Camera* Viewport::GetCamera() const
{
    return camera_;
}

PostProcess* Viewport::GetPostProcess(unsigned index) const
{
    return index < postProcesses_.Size() ? postProcesses_[index] : (PostProcess*)0;
}

}
