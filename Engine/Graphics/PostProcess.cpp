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
#include "Graphics.h"
#include "Log.h"
#include "PostProcess.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "XMLFile.h"

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

const String& PostProcessPass::GetTexture(TextureUnit unit) const
{
    return textureNames_[unit];
}

const Vector4& PostProcessPass::GetShaderParameter(const String& name) const
{
    HashMap<StringHash, Vector4>::ConstIterator i = shaderParameters_.Find(StringHash(name));
    if (i != shaderParameters_.End())
        return i->second_;
    else
        return Vector4::ZERO;
}

PostProcessRenderTarget::~PostProcessRenderTarget()
{
}

PostProcess::PostProcess(Context* context) :
    Object(context)
{
}

PostProcess::~PostProcess()
{
}

bool PostProcess::LoadParameters(XMLFile* file)
{
    if (!file)
        return false;
    
    XMLElement rootElem = parameterSource_->GetRoot();
    if (!rootElem)
        return false;
    
    parameterSource_ = file;
    renderTargets_.Clear();
    passes_.Clear();
    
    XMLElement rtElem = rootElem.GetChild("rendertarget");
    while (rtElem)
    {
        String name = rtElem.GetString("name");
        unsigned width = rtElem.GetInt("width");
        unsigned height = rtElem.GetInt("height");
        unsigned format = Graphics::GetRGBFormat();
        bool relativeSize = rtElem.GetBool("relativesize");
        String formatName = rtElem.GetString("format").ToLower();
        if (formatName == "rgba")
            format = Graphics::GetRGBAFormat();
        else if (formatName == "float")
            format = Graphics::GetFloatFormat();
        CreateRenderTarget(name, width, height, format, relativeSize);
        
        rtElem = rtElem.GetNext("rendertarget");
    }
    
    XMLElement passElem = rootElem.GetChild("pass");
    while (passElem)
    {
        SharedPtr<PostProcessPass> pass(new PostProcessPass());
        pass->SetVertexShader(passElem.GetString("vs"));
        pass->SetPixelShader(passElem.GetString("ps"));
        pass->SetOutput(passElem.GetString("output"));
        
        XMLElement textureElem = passElem.GetChild("texture");
        while (textureElem)
        {
            TextureUnit unit = TU_DIFFUSE;
            if (textureElem.HasAttribute("unit"))
            {
                String unitName = textureElem.GetStringLower("unit");
                unit = ParseTextureUnitName(unitName);
                if (unit == MAX_MATERIAL_TEXTURE_UNITS)
                    LOGERROR("Unknown texture unit " + unitName);
            }
            if (unit != MAX_MATERIAL_TEXTURE_UNITS)
            {
                String name = textureElem.GetString("name");
                pass->SetTexture(unit, name);
            }
            textureElem = textureElem.GetNext("texture");
        }
        
        XMLElement parameterElem = passElem.GetChild("parameter");
        while (parameterElem)
        {
            String name = parameterElem.GetString("name");
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

bool PostProcess::CreateRenderTarget(const String& name, unsigned width, unsigned height, unsigned format, bool relativeSize)
{
    if (name.Trimmed().Empty())
        return false;
    
    PostProcessRenderTarget target;
    target.texture_ = new Texture2D(context_);
    target.format_ = format;
    target.relativeSize_ = relativeSize;
    // If size is absolute, can reserve the texture now. Otherwise must defer to later
    if (!relativeSize)
    {
        target.sizeDivisor_ = IntVector2(1, 1);
        if (!target.texture_->SetSize(width, height, format, TEXTURE_RENDERTARGET))
            return false;
    }
    else
        target.sizeDivisor_ = IntVector2(Max((int)width, 1), Max((int)height, 1));
    
    renderTargets_[StringHash(name)] = target;
    return true;
}

void PostProcess::RemoveRenderTarget(const String& name)
{
    renderTargets_.Erase(StringHash(name));
}

PostProcessPass* PostProcess::GetPass(unsigned index) const
{
    if (index < passes_.Size())
        return passes_[index];
    else
        return 0;
}

const PostProcessRenderTarget* PostProcess::GetRenderTarget(const String& name) const
{
    HashMap<StringHash, PostProcessRenderTarget>::ConstIterator i = renderTargets_.Find(StringHash(name));
    if (i != renderTargets_.End())
        return &i->second_;
    else
        return 0;
}
