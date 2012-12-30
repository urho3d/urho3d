//
// Urho3D Engine
// Copyright (c) 2008-2012 Lasse Oorni
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
#include "ResourceCache.h"
#include "Scene.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

TextureUnit ParseTextureUnitName(const String& name);

static const String cmdNames[] =
{
    "clear",
    "scenepass",
    "quad",
    "forwardlights",
    "lightvolumes",
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
    if (!file && cache)
        file = cache->GetResource<XMLFile>("Data/RenderPaths/Forward.xml");
    if (!file)
        return false;
    
    XMLElement rootElem = file->GetRoot();
    if (!rootElem)
        return false;
    
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
            RenderTargetInfo target;
            target.name_ = name;
            target.format_ = format;
            target.size_ = IntVector2(width, height),
            target.sizeDivisor_ = sizeDivisor;
            target.filtered_ = filtered;
            renderPath_.renderTargets_[StringHash(name)] = target;
        }
        
        rtElem = rtElem.GetNext("rendertarget");
    }
    
    XMLElement cmdElem = rootElem.GetChild("command");
    while (cmdElem)
    {
        RenderCommandType type = (RenderCommandType)GetStringListIndex(cmdElem.GetAttributeLower("type"), cmdNames, CMD_UNKNOWN);
        if (type != CMD_UNKNOWN)
        {
            RenderPathCommand cmd;
            cmd.type_ = type;
            cmd.passName_ = cmdElem.GetAttribute("pass");
            cmd.vertexShaderName_ = cmdElem.GetAttribute("vs");
            cmd.pixelShaderName_ = cmdElem.GetAttribute("ps");
            
            if (type == CMD_CLEAR)
            {
                cmd.clearFlags_ = 0;
                if (cmdElem.HasAttribute("color"))
                {
                    cmd.clearFlags_ |= CLEAR_COLOR;
                    // Mark fog color with negative values
                    if (cmdElem.GetAttributeLower("color") == "fog")
                        cmd.clearColor_ = Color(-1.0f, -1.0f, -1.0f, -1.0f);
                    else
                        cmd.clearColor_ = cmdElem.GetColor("color");
                }
                if (cmdElem.HasAttribute("depth"))
                {
                    cmd.clearFlags_ |= CLEAR_DEPTH;
                    cmd.clearDepth_ = cmdElem.GetFloat("depth");
                }
                if (cmdElem.HasAttribute("stencil"))
                {
                    cmd.clearFlags_ |= CLEAR_STENCIL;
                    cmd.clearStencil_ = cmdElem.GetInt("stencil");
                }
            }
            
            // By default use 1 output, which is the viewport
            cmd.outputs_.Push("viewport");
            if (cmdElem.HasAttribute("output"))
                cmd.outputs_[0] = cmdElem.GetAttribute("output");
            // Check for defining multiple outputs
            XMLElement outputElem = cmdElem.GetChild("output");
            while (outputElem)
            {
                unsigned index = outputElem.GetInt("index");
                if (index < MAX_RENDERTARGETS)
                {
                    if (index >= cmd.outputs_.Size())
                        cmd.outputs_.Resize(index + 1);
                    cmd.outputs_[index] = outputElem.GetAttribute("name");
                }
                outputElem = outputElem.GetNext("output");
            }
            
            XMLElement parameterElem = cmdElem.GetChild("parameter");
            while (parameterElem)
            {
                String name = parameterElem.GetAttribute("name");
                Vector4 value = parameterElem.GetVector("value");
                cmd.shaderParameters_[StringHash(name)] = value;
                
                parameterElem = parameterElem.GetNext("parameter");
            }
            
            XMLElement textureElem = cmdElem.GetChild("texture");
            while (textureElem)
            {
                TextureUnit unit = TU_DIFFUSE;
                if (textureElem.HasAttribute("unit"))
                {
                    String unitName = textureElem.GetAttributeLower("unit");
                    if (unitName.Length() > 1)
                    {
                        unit = ParseTextureUnitName(unitName);
                        if (unit == MAX_MATERIAL_TEXTURE_UNITS)
                            LOGERROR("Unknown texture unit " + unitName);
                    }
                    else
                        unit = (TextureUnit)Clamp(ToInt(unitName), 0, MAX_MATERIAL_TEXTURE_UNITS - 1);
                }
                if (unit != MAX_TEXTURE_UNITS)
                {
                    String name = textureElem.GetAttribute("name");
                    cmd.textureNames_[unit] = name;
                }
                
                textureElem = textureElem.GetNext("texture");
            }
        }
        
        cmdElem = cmdElem.GetNext("command");
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
