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
#include "Graphics.h"
#include "Log.h"
#include "PostProcess.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "XMLFile.h"

#include "DebugNew.h"

namespace Urho3D
{

TextureUnit ParseTextureUnitName(const String& name);

PostProcessPass::PostProcessPass()
{
}

PostProcessPass::~PostProcessPass()
{
}

void PostProcessPass::SetVertexShader(const String& name)
{
    vertexShaderName_ = name;
}

void PostProcessPass::SetPixelShader(const String& name)
{
    pixelShaderName_ = name;
}

void PostProcessPass::SetTexture(TextureUnit unit, const String& name)
{
    if (unit < MAX_TEXTURE_UNITS)
        textureNames_[unit] = name;
}

void PostProcessPass::SetShaderParameter(const String& name, const Vector4& value)
{
    shaderParameters_[StringHash(name)] = value;
}

void PostProcessPass::RemoveShaderParameter(const String& name)
{
    shaderParameters_.Erase(StringHash(name));
}

void PostProcessPass::SetOutput(const String& name)
{
    outputName_ = name;
}

SharedPtr<PostProcessPass> PostProcessPass::Clone()
{
    SharedPtr<PostProcessPass> clone(new PostProcessPass());
    clone->vertexShaderName_ = vertexShaderName_;
    clone->pixelShaderName_ = pixelShaderName_;
    clone->shaderParameters_ = shaderParameters_;
    for (unsigned i = 0; i < MAX_TEXTURE_UNITS; ++i)
        clone->textureNames_[i] = textureNames_[i];
    clone->outputName_ = outputName_;
    
    return clone;
}

const String& PostProcessPass::GetTexture(TextureUnit unit) const
{
    return unit < MAX_TEXTURE_UNITS ? textureNames_[unit] : String::EMPTY;
}

const Vector4& PostProcessPass::GetShaderParameter(const String& name) const
{
    HashMap<StringHash, Vector4>::ConstIterator i = shaderParameters_.Find(StringHash(name));
    return i != shaderParameters_.End() ? i->second_ : Vector4::ZERO;
}

OBJECTTYPESTATIC(PostProcess);

PostProcess::PostProcess(Context* context) :
    Object(context),
    active_(true)
{
}

PostProcess::~PostProcess()
{
}

bool PostProcess::LoadParameters(XMLFile* file)
{
    if (!file)
        return false;
    
    XMLElement rootElem = file->GetRoot();
    if (!rootElem)
        return false;
    
    parameterSource_ = file;
    renderTargets_.Clear();
    shaderParameters_.Clear();
    passes_.Clear();
    
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
        
        CreateRenderTarget(name, width, height, format, sizeDivisor, filtered);
        rtElem = rtElem.GetNext("rendertarget");
    }
    
    XMLElement parameterElem = rootElem.GetChild("parameter");
    while (parameterElem)
    {
        String name = parameterElem.GetAttribute("name");
        Vector4 value = parameterElem.GetVector("value");
        SetShaderParameter(name, value);
        
        parameterElem = parameterElem.GetNext("parameter");
    }
    
    XMLElement passElem = rootElem.GetChild("pass");
    while (passElem)
    {
        SharedPtr<PostProcessPass> pass(new PostProcessPass());
        pass->SetVertexShader(passElem.GetAttribute("vs"));
        pass->SetPixelShader(passElem.GetAttribute("ps"));
        pass->SetOutput(passElem.GetAttribute("output"));
        
        XMLElement textureElem = passElem.GetChild("texture");
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
                pass->SetTexture(unit, name);
            }
            
            textureElem = textureElem.GetNext("texture");
        }
        
        XMLElement parameterElem = passElem.GetChild("parameter");
        while (parameterElem)
        {
            String name = parameterElem.GetAttribute("name");
            Vector4 value = parameterElem.GetVector("value");
            pass->SetShaderParameter(name, value);
            
            parameterElem = parameterElem.GetNext("parameter");
        }
        
        passes_.Push(pass);
        passElem = passElem.GetNext("pass");
    }
    
    return true;
}

void PostProcess::SetNumPasses(unsigned passes)
{
    passes_.Resize(passes);
    
    for (unsigned i = 0; i < passes_.Size(); ++i)
    {
        if (!passes_[i])
            passes_[i] = new PostProcessPass();
    }
}

bool PostProcess::CreateRenderTarget(const String& name, unsigned width, unsigned height, unsigned format, bool sizeDivisor, bool filtered)
{
    if (name.Trimmed().Empty())
        return false;
    
    RenderTargetInfo target;
    target.name_ = name;
    target.format_ = format;
    target.size_ = IntVector2(width, height),
    target.sizeDivisor_ = sizeDivisor;
    target.filtered_ = filtered;
    
    renderTargets_[StringHash(name)] = target;
    return true;
}

void PostProcess::RemoveRenderTarget(const String& name)
{
    renderTargets_.Erase(StringHash(name));
}

void PostProcess::SetShaderParameter(const String& name, const Vector4& value)
{
    shaderParameters_[StringHash(name)] = value;
}

void PostProcess::RemoveShaderParameter(const String& name)
{
    shaderParameters_.Erase(StringHash(name));
}

void PostProcess::SetActive(bool active)
{
    active_ = active;
}

SharedPtr<PostProcess> PostProcess::Clone()
{
    SharedPtr<PostProcess> clone(new PostProcess(context_));
    clone->passes_.Resize(passes_.Size());
    for (unsigned i = 0; i < passes_.Size(); ++i)
        clone->passes_[i] = passes_[i]->Clone();
    clone->renderTargets_ = renderTargets_;
    clone->active_ = active_;
    
    return clone;
}

PostProcessPass* PostProcess::GetPass(unsigned index) const
{
    if (index < passes_.Size())
        return passes_[index];
    else
        return 0;
}

bool PostProcess::HasRenderTarget(const String& name) const
{
    return renderTargets_.Contains(StringHash(name));
}

const Vector4& PostProcess::GetShaderParameter(const String& name) const
{
    HashMap<StringHash, Vector4>::ConstIterator i = shaderParameters_.Find(StringHash(name));
    return i != shaderParameters_.End() ? i->second_ : Vector4::ZERO;
}

}
