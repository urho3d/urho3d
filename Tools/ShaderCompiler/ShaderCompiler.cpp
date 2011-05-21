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

#include "Context.h"
#include "File.h"
#include "FileSystem.h"
#include "ProcessUtils.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <cstdio>
#include <cstring>

#include <Windows.h>
#include <d3d9.h>
#include <D3DX9Shader.h>

#include "DebugNew.h"

enum ShaderType
{
    VS,
    PS,
    Both
};

struct Variation
{
    Variation()
    {
    }
    
    Variation(const String& name, bool isOption) :
        name_(name),
        option_(isOption)
    {
    }
    
    void AddDefine(const String& def)
    {
        defines_.Push(def);
    }
    
    void AddExclude(const String& excl)
    {
        excludes_.Push(excl);
    }
    
    void AddInclude(const String& incl)
    {
        includes_.Push(incl);
    }
    
    void AddRequire(const String& req)
    {
        requires_.Push(req);
    }
    
    String name_;
    Vector<String> defines_;
    Vector<String> excludes_;
    Vector<String> includes_;
    Vector<String> requires_;
    bool option_;
};

struct Shader
{
    Shader(const String& name, ShaderType type) :
        name_(name),
        type_(type)
    {
    }
    
    void AddVariation(const Variation& var)
    {
        variations_.Push(var);
    }
    
    String name_;
    ShaderType type_;
    Vector<Variation> variations_;
};

struct Parameter
{
    String name_;
    unsigned index_;
};

struct Parameters
{
    void AddVSParam(const String& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        vsParams_.Push(newParam);
    }
    
    void AddPSParam(const String& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        psParams_.Push(newParam);
    }
    
    void AddTextureUnit(const String& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        textureUnits_.Push(newParam);
    }
    
    Vector<Parameter> vsParams_;
    Vector<Parameter> psParams_;
    Vector<Parameter> textureUnits_;
};

SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
String inDir_;
String inFile_;
String outDir_;
Map<String, unsigned> vsParams_;
Map<String, unsigned> psParams_;
Map<String, unsigned> textureUnits_;
Vector<String> defines_;
bool useSM3_ = false;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void CompileVariations(const Shader& baseShader, XMLElement& shaders);
bool Compile(ShaderType type, const String& hlslCode, const String& output, const Vector<String>& defines, Parameters& params);

class IncludeHandler : public ID3DXInclude
{
public:
    STDMETHOD(Open)(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
    {
        String fileName = inDir_ + String((const char*)pFileName);
        SharedPtr<File> file(new File(context_, fileName));
        if (!file->IsOpen())
            return E_FAIL;
        
        unsigned fileSize = file->GetSize();
        void* fileData = new unsigned char[fileSize];
        *pBytes = fileSize;
        *ppData = fileData;
        file->Read(fileData, fileSize);
        
        return S_OK;
    }
    
    STDMETHOD(Close)(LPCVOID pData)
    {
        delete[] (unsigned char*)pData;
        return S_OK;
    }
};

int main(int argc, char** argv)
{
    Vector<String> arguments;
    
    for (int i = 1; i < argc; ++i)
    {
        String argument(argv[i]);
        arguments.Push(argument.Replace('/', '\\'));
    }
    
    Run(arguments);
    return 0;
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 2)
    {
        ErrorExit(
            "Usage: ShaderCompiler <definitionfile> <outputpath> [SM3] [define1] [define2]\n\n"
            "HLSL files will be loaded from definition file directory, and binary code will\n"
            "be output to same directory as the output file.\n"
        );
    }
    
    unsigned pos = arguments[0].FindLast('\\');
    if (pos != String::NPOS)
    {
        inDir_ = arguments[0].Substring(0, pos);
        inFile_ = arguments[0].Substring(pos + 1);
    }
    else
    {
        inFile_ = arguments[0];
    }
    
    outDir_ = arguments[1];
    
    inDir_ = AddTrailingSlash(inDir_);
    outDir_ = AddTrailingSlash(outDir_);
    
    for (unsigned i = 2; i < arguments.Size(); ++i)
    {
        String arg = arguments[i].ToUpper();
        
        if (arg == "SM3")
            useSM3_ = true;
        else if (arg == "SM2")
            useSM3_ = false;
        
        defines_.Push(arg);
    }
    
    XMLFile doc(context_);
    File source(context_);
    source.Open(arguments[0]);
    if (!doc.Load(source))
        ErrorExit("Could not open input file " + arguments[0]);
    
    XMLElement shaders = doc.GetRootElement("shaders");
    if (!shaders)
        ErrorExit("No shaders element in " + source.GetName());
    
    XMLFile outDoc(context_);
    XMLElement outShaders = outDoc.CreateRootElement("shaders");
    
    XMLElement shader = shaders.GetChildElement("shader");
    while (shader)
    {
        bool WriteOutput = false;
        
        String source = shader.GetString("name");
        
        ShaderType compileType = Both;
        String type = shader.GetString("type");
        if ((type == "VS") || (type == "vs"))
            compileType = VS;
        if ((type == "PS") || (type == "ps"))
            compileType = PS;
        if ((compileType == Both) || (compileType == PS))
            WriteOutput = true;
        
        Shader baseShader(source, compileType);
        
        XMLElement variation = shader.GetChildElement("");
        while (variation)
        {
            String value = variation.GetName();
            if ((value == "variation") || (value == "option"))
            {
                String name = variation.GetString("name");
                
                Variation newVar(name, value == "option");
                
                String simpleDefine = variation.GetString("define");
                if (!simpleDefine.Empty())
                    newVar.AddDefine(simpleDefine);
                    
                String simpleExclude = variation.GetString("exclude");
                if (!simpleExclude.Empty())
                    newVar.AddExclude(simpleExclude);
                
                String simpleInclude = variation.GetString("include");
                if (!simpleInclude.Empty())
                    newVar.AddInclude(simpleInclude);
                
                String simpleRequire = variation.GetString("require");
                if (!simpleRequire.Empty())
                    newVar.AddRequire(simpleRequire);
                
                XMLElement define = variation.GetChildElement("define");
                while (define)
                {
                    String name = define.GetString("name");
                    newVar.AddDefine(name);
                    
                    define = define.GetNextElement("define");
                }
                
                XMLElement exclude = variation.GetChildElement("exclude");
                while (exclude)
                {
                    String name = exclude.GetString("name");
                    newVar.AddExclude(name);
                    
                    exclude = exclude.GetNextElement("exclude");
                }
                
                XMLElement include = variation.GetChildElement("include");
                while (include)
                {
                    String name = include.GetString("name");
                    newVar.AddInclude(name);
                    
                    include = include.GetNextElement("include");
                }
                
                XMLElement require = variation.GetChildElement("require");
                while (require)
                {
                    String name = require.GetString("name");
                    newVar.AddRequire(name);
                    
                    require = require.GetNextElement("require");
                }
                
                baseShader.AddVariation(newVar);
            }
            
            variation = variation.GetNextElement();
        }
        
        if (baseShader.type_ != Both)
            CompileVariations(baseShader, outShaders);
        else
        {
            baseShader.type_ = VS;
            CompileVariations(baseShader, outShaders);
            baseShader.type_ = PS;
            CompileVariations(baseShader, outShaders);
        }
        
        if (WriteOutput)
        {
            String outFileName = outDir_ + inDir_ + source + ".xml";
            remove(outFileName.CString());
            
            // Add global parameter & texture sampler definitions
            {
                XMLElement parameters = outShaders.CreateChildElement("vsparameters");
                Map<unsigned, Vector<String> > sorted;
                for (Map<String, unsigned>::ConstIterator i = vsParams_.Begin(); i != vsParams_.End(); ++i)
                    sorted[i->second_].Push(i->first_);
                
                for (Map<unsigned, Vector<String> >::ConstIterator i = sorted.Begin(); i != sorted.End(); ++i)
                {
                    for (unsigned j = 0; j < i->second_.Size(); ++j)
                    {
                        XMLElement param = parameters.CreateChildElement("parameter");
                        param.SetString("name", i->second_[j]);
                        param.SetInt("index", i->first_);
                    }
                }
            }
            
            {
                XMLElement parameters = outShaders.CreateChildElement("psparameters");
                Map<unsigned, Vector<String> > sorted;
                for (Map<String, unsigned>::ConstIterator i = psParams_.Begin(); i != psParams_.End(); ++i)
                    sorted[i->second_].Push(i->first_);
                
                for (Map<unsigned, Vector<String> >::ConstIterator i = sorted.Begin(); i != sorted.End(); ++i)
                {
                    for (unsigned j = 0; j < i->second_.Size(); ++j)
                    {
                        XMLElement param = parameters.CreateChildElement("parameter");
                        param.SetString("name", i->second_[j]);
                        param.SetInt("index", i->first_);
                    }
                }
            }
            
            {
                XMLElement parameters = outShaders.CreateChildElement("textureunits");
                Map<unsigned, Vector<String> > sorted;
                for (Map<String, unsigned>::ConstIterator i = textureUnits_.Begin(); i != textureUnits_.End(); ++i)
                    sorted[i->second_].Push(i->first_);
                
                for (Map<unsigned, Vector<String> >::ConstIterator i = sorted.Begin(); i != sorted.End(); ++i)
                {
                    for (unsigned j = 0; j < i->second_.Size(); ++j)
                    {
                        XMLElement param = parameters.CreateChildElement("parameter");
                        param.SetString("name", i->second_[j]);
                        param.SetInt("index", i->first_);
                    }
                }
            }
            
            File outFile(context_);
            outFile.Open(outFileName, FILE_WRITE);
            if (!outDoc.Save(outFile))
                ErrorExit("Could not save output file " + outFileName);
        }
        
        shader = shader.GetNextElement("shader");
    }
}

void CompileVariations(const Shader& baseShader, XMLElement& shaders)
{
    unsigned combinations = 1;
    PODVector<unsigned> compiled;
    bool hasVariations = false;
    Map<String, unsigned> nameToIndex;
    String hlslCode;
    
    const Vector<Variation>& variations = baseShader.variations_;
    
    if (variations.Size() > 32)
        ErrorExit("Maximum amount of variations exceeded");
    
    // Load the shader source code
    String inputFileName = inDir_ + baseShader.name_ + ".hlsl";
    SharedPtr<File> hlslFile(new File(context_, inputFileName));
    if (!hlslFile->IsOpen())
        ErrorExit("Could not open input file " + inputFileName);
    
    while (!hlslFile->IsEof())
        hlslCode += hlslFile->ReadLine() + "\n";
    hlslFile->Close();
    
    for (unsigned i = 0; i < variations.Size(); ++i)
    {
        combinations *= 2;
        nameToIndex[variations[i].name_] = i;
        if (!variations[i].option_)
            hasVariations = true;
    }
    
    for (unsigned i = 0; i < combinations; ++i)
    {
        unsigned active = i; // Variations/options active on this particular combination
        bool variationActive = false;
        bool skipThis = false;
        
        // Check for excludes/includes/requires
        for (unsigned j = 0; j < variations.Size(); ++j)
        {
            if ((active >> j) & 1)
            {
                for (unsigned k = 0; k < variations[j].includes_.Size(); ++k)
                {
                    if (nameToIndex.Find(variations[j].includes_[k]) != nameToIndex.End())
                        active |= (1 << nameToIndex[variations[j].includes_[k]]);
                }
                
                for (unsigned k = 0; k < variations[j].excludes_.Size(); ++k)
                {
                    if (nameToIndex.Find(variations[j].excludes_[k]) != nameToIndex.End())
                        active &= ~(1 << nameToIndex[variations[j].excludes_[k]]);
                }
                
                // If it's a variation, exclude all other variations
                if (!variations[j].option_)
                {
                    for (unsigned k = 0; k < variations.Size(); ++k)
                    {
                        if ((k != j) && (!variations[k].option_))
                            active &= ~(1 << k);
                    }
                    
                    variationActive = true;
                }
                
                for (unsigned k = 0; k < variations[j].requires_.Size(); ++k)
                {
                    bool requireFound = false;
                    
                    for (unsigned l = 0; l < defines_.Size(); ++l)
                    {
                        if (defines_[l] == variations[j].requires_[k])
                        {
                            requireFound = true;
                            break;
                        }
                    }
                    
                    for (unsigned l = 0; l < variations.Size(); ++l)
                    {
                        if (((active >> l) & 1) && (l != j))
                        {
                            if (variations[l].name_ == variations[j].requires_[k])
                            {
                                requireFound = true;
                                break;
                            }
                            for (unsigned m = 0; m < variations[l].defines_.Size(); ++m)
                            {
                                if (variations[l].defines_[m] == variations[j].requires_[k])
                                {
                                    requireFound = true;
                                    break;
                                }
                            }
                        }
                        if (requireFound)
                            break;
                    }
                    
                    if (!requireFound)
                        skipThis = true;
                }
            }
        }
        
        // If variations are included, check that one of them is active
        if ((hasVariations) && (!variationActive))
            continue;
        
        if (skipThis)
            continue;
        
        // Check that this combination is unique
        bool unique = true;
        for (unsigned j = 0; j < compiled.Size(); ++j)
        {
            if (compiled[j] == active)
            {
                unique = false;
                break;
            }
        }
        
        if (unique)
        {
            bool firstSuffix = true;
            
            // Build output shader filename & defines from active variations
            String outName  = baseShader.name_;
            Vector<String> defines;
            for (unsigned j = 0; j < variations.Size(); ++j)
            {
                if (active & (1 << j))
                {
                    if (variations[j].name_.Length())
                    {
                        if (firstSuffix)
                        {
                            outName = outName + "_" + variations[j].name_;
                            firstSuffix = false;
                        }
                        else
                            outName = outName + variations[j].name_;
                    }
                    for (unsigned k = 0; k < variations[j].defines_.Size(); ++k)
                        defines.Push(variations[j].defines_[k]);
                }
            }
            
            Parameters params;
            
            bool ok = Compile(baseShader.type_, hlslCode, outName, defines, params);
            
            // If shader was unnecessary (for example SM2 does not support HQ variations)
            // no output may have been produced. Skip in that case.
            if (ok)
            {
                XMLElement shader = shaders.CreateChildElement("shader");
                shader.SetString("name", outName);
                switch (baseShader.type_)
                {
                case VS:
                    shader.SetString("type", "vs");
                    for (unsigned j = 0; j < params.vsParams_.Size(); ++j)
                    {
                        XMLElement vsParam = shader.CreateChildElement("parameter");
                        vsParam.SetString("name", params.vsParams_[j].name_);
                    }
                    break;
                    
                case PS:
                    shader.SetString("type", "ps");
                    for (unsigned j = 0; j < params.psParams_.Size(); ++j)
                    {
                        XMLElement psParam = shader.CreateChildElement("parameter");
                        psParam.SetString("name", params.psParams_[j].name_);
                    }
                    for (unsigned j = 0; j < params.textureUnits_.Size(); ++j)
                    {
                        XMLElement texture = shader.CreateChildElement("textureunit");
                        texture.SetString("name", params.textureUnits_[j].name_);
                    }
                    break;
                }
                
                compiled.Push(active);
            }
        }
    }
}

bool Compile(ShaderType type, const String& hlslCode, const String& output, const Vector<String>& defines,
    Parameters& params)
{
    IncludeHandler includeHandler;
    PODVector<D3DXMACRO> macros;
    
    String value = "1";
    
    // Insert variation-specific and global defines
    for (unsigned i = 0; i < defines.Size(); ++i)
    {
        D3DXMACRO macro;
        macro.Name = defines[i].CString();
        macro.Definition = value.CString();
        macros.Push(macro);
    }
    for (unsigned i = 0; i < defines_.Size(); ++i)
    {
        D3DXMACRO macro;
        macro.Name = defines_[i].CString();
        macro.Definition = value.CString();
        macros.Push(macro);
    }
    
    D3DXMACRO endMacro;
    endMacro.Name = 0;
    endMacro.Definition = 0;
    macros.Push(endMacro);
    
    LPD3DXBUFFER shaderCode = 0;
    LPD3DXBUFFER errorMsgs = 0;
    LPD3DXCONSTANTTABLE constantTable = 0;
    
    // Set the profile, entrypoint and flags according to the shader being compiled
    String profile;
    String extension;
    String entryPoint;
    unsigned flags = 0;
    
    if (type == VS)
    {
        entryPoint = "VS";
        if (!useSM3_)
        {
            profile = "vs_2_0";
            extension = ".vs2";
        }
        else
        {
            profile = "vs_3_0";
            extension = ".vs3";
        }
    }
    else
    {
        entryPoint = "PS";
        if (!useSM3_)
        {
            profile = "ps_2_0";
            extension = ".ps2";
        }
        else
        {
            profile = "ps_3_0";
            extension = ".ps3";
            flags |= D3DXSHADER_PREFER_FLOW_CONTROL;
        }
    }
    
    String outFileName = outDir_ + inDir_ + output + extension;
    
    // Compile using D3DX
    PrintLine("Compiling shader " + outFileName);
    HRESULT hr = D3DXCompileShader(hlslCode.CString(), hlslCode.Length(), &macros.Front(), &includeHandler, 
        entryPoint.CString(), profile.CString(), flags, &shaderCode, &errorMsgs, &constantTable);
    if (FAILED(hr))
    {
        String error((const char*)errorMsgs->GetBufferPointer(), errorMsgs->GetBufferSize());
        errorMsgs->Release();
        ErrorExit("Failed to compile shader " + outFileName + ": " + error);
    }
    
    // Write the shader bytecode
    SharedPtr<File> outFile(new File(context_, outFileName, FILE_WRITE));
    if (outFile->IsOpen())
        outFile->Write(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize());
    else
        ErrorExit("Failed to write output file " + outFileName);
    
    // Parse the constant table for constants and texture units
    D3DXCONSTANTTABLE_DESC desc;
    constantTable->GetDesc(&desc);
    for (unsigned i = 0; i < desc.Constants; ++i)
    {
        D3DXHANDLE handle = constantTable->GetConstant(NULL, i);
        D3DXCONSTANT_DESC constantDesc;
        unsigned numElements = 1;
        constantTable->GetConstantDesc(handle, &constantDesc, &numElements);
        
        String name(constantDesc.Name);
        unsigned index = constantDesc.RegisterIndex;
        
        // Check if the parameter is a constant or a texture sampler
        bool isSampler = (name[0] == 's');
        name = name.Substring(1);
    
        if (isSampler)
        {
            // Skip if it's a G-buffer sampler
            if (name.Find("Buffer") == String::NPOS)
            {
                params.AddTextureUnit(name, index);
                
                if (textureUnits_.Find(name) != textureUnits_.End())
                {
                    unsigned oldIndex = textureUnits_[name];
                    if (oldIndex != index)
                        ErrorExit("Texture " + name + " bound to several sampler registers");
                }
                textureUnits_[name] = index;
            }
        }
        else
        {
            if (type == VS)
            {
                params.AddVSParam(name, index);
                
                if (vsParams_.Find(name) != vsParams_.End())
                {
                    unsigned oldIndex = vsParams_[name];
                    if (oldIndex != index)
                        ErrorExit("Parameter " + name + " bound to several constant registers");
                }
                vsParams_[name] = index;
            }
            else
            {
                params.AddPSParam(name, index);
                
                if (psParams_.Find(name) != psParams_.End())
                {
                    unsigned oldIndex = psParams_[name];
                    if (oldIndex != index)
                        ErrorExit("Parameter " + name + " bound to several constant registers");
                }
                psParams_[name] = index;
            }
        }
    }
    
    if (shaderCode)
        shaderCode->Release();
    if (constantTable)
        constantTable->Release();
    
    return true;
}
