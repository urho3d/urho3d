//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "File.h"
#include "FileSystem.h"
#include "Graphics.h"
#include "Log.h"
#include "ShaderPrecache.h"
#include "ShaderVariation.h"

#include "DebugNew.h"

namespace Urho3D
{

ShaderPrecache::ShaderPrecache(Context* context, const String& fileName) :
    Object(context),
    fileName_(fileName),
    xmlFile_(context)
{
    if (GetSubsystem<FileSystem>()->FileExists(fileName))
    {
        // If file exists, read the already listed combinations
        File source(context_, fileName);
        xmlFile_.Load(source);
        
        XMLElement shader = xmlFile_.GetRoot().GetChild("shader");
        while (shader)
        {
            String oldCombination = shader.GetAttribute("vs") + " " + shader.GetAttribute("vsdefines") + " " +
                shader.GetAttribute("ps") + " " + shader.GetAttribute("psdefines");
            usedCombinations_.Insert(oldCombination);
            
            shader = shader.GetNext("shader");
        }
    }
    else
        xmlFile_.CreateRoot("shaders");
    
    LOGDEBUG("Begin dumping shaders to " + fileName_);
}

ShaderPrecache::~ShaderPrecache()
{
    LOGDEBUG("End dumping shaders");
    
    if (usedCombinations_.Empty())
        return;
    
    File dest(context_, fileName_, FILE_WRITE);
    xmlFile_.Save(dest);
}

void ShaderPrecache::StoreShaders(ShaderVariation* vs, ShaderVariation* ps)
{
    if (!vs || !ps)
        return;
    
    String vsName = vs->GetName().Substring(0, vs->GetName().Find('_'));
    String psName = ps->GetName().Substring(0, ps->GetName().Find('_'));
    const String& vsDefines = vs->GetDefines();
    const String& psDefines = ps->GetDefines();
    
    // Check for duplicate
    String newCombination = vsName + " " + vsDefines + " " + psName + " " + psDefines;
    if (usedCombinations_.Contains(newCombination))
        return;
    
    XMLElement shaderElem = xmlFile_.GetRoot().CreateChild("shader");
    shaderElem.SetAttribute("vs", vsName);
    shaderElem.SetAttribute("vsdefines", vsDefines);
    shaderElem.SetAttribute("ps", psName);
    shaderElem.SetAttribute("psdefines", psDefines);
    usedCombinations_.Insert(newCombination);
}

void ShaderPrecache::LoadShaders(Graphics* graphics, Deserializer& source)
{
    LOGDEBUG("Begin precaching shaders");
    
    XMLFile xmlFile(graphics->GetContext());
    xmlFile.Load(source);
    
    XMLElement shader = xmlFile.GetRoot().GetChild("shader");
    while (shader)
    {
        ShaderVariation* vs = graphics->GetShader(VS, shader.GetAttribute("vs"), shader.GetAttribute("vsdefines"));
        ShaderVariation* ps = graphics->GetShader(PS, shader.GetAttribute("ps"), shader.GetAttribute("psdefines"));
        // Set the shaders active to actually compile them
        graphics->SetShaders(vs, ps);
        
        shader = shader.GetNext("shader");
    }
    
    LOGDEBUG("End precaching shaders");
}

}
