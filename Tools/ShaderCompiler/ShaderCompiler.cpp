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

#include <cstring>
#include <map>

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
    
    void addDefine(const String& def)
    {
        defines_.Push(def);
    }
    
    void addExclude(const String& excl)
    {
        excludes_.Push(excl);
    }
    
    void addInclude(const String& incl)
    {
        includes_.Push(incl);
    }
    
    void addRequire(const String& req)
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
    
    void addVariation(const Variation& var)
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
    void addVSParam(const String& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        vsParams_.Push(newParam);
    }
    
    void addPSParam(const String& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        psParams_.Push(newParam);
    }
    
    void addTextureUnit(const String& name, unsigned index)
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
bool Compile(ShaderType type, const String& input, const String& output, const Vector<String>& defines, Parameters& params);

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
    
    if (inDir_.Empty())
        inDir_ = ".\\";
    
    if (outDir_.Empty())
        outDir_ = ".\\";
    
    if (inDir_[inDir_.Length()-1] != '\\')
        inDir_ = inDir_ + "\\";
    
    if (outDir_[outDir_.Length()-1] != '\\')
        outDir_ = outDir_ + "\\";
    
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
                    newVar.addDefine(simpleDefine);
                    
                String simpleExclude = variation.GetString("exclude");
                if (!simpleExclude.Empty())
                    newVar.addExclude(simpleExclude);
                
                String simpleInclude = variation.GetString("include");
                if (!simpleInclude.Empty())
                    newVar.addInclude(simpleInclude);
                
                String simpleRequire = variation.GetString("require");
                if (!simpleRequire.Empty())
                    newVar.addRequire(simpleRequire);
                
                XMLElement define = variation.GetChildElement("define");
                while (define)
                {
                    String name = define.GetString("name");
                    newVar.addDefine(name);
                    
                    define = define.GetNextElement("define");
                }
                
                XMLElement exclude = variation.GetChildElement("exclude");
                while (exclude)
                {
                    String name = exclude.GetString("name");
                    newVar.addExclude(name);
                    
                    exclude = exclude.GetNextElement("exclude");
                }
                
                XMLElement include = variation.GetChildElement("include");
                while (include)
                {
                    String name = include.GetString("name");
                    newVar.addInclude(name);
                    
                    include = include.GetNextElement("include");
                }
                
                XMLElement require = variation.GetChildElement("require");
                while (require)
                {
                    String name = require.GetString("name");
                    newVar.addRequire(name);
                    
                    require = require.GetNextElement("require");
                }
                
                baseShader.addVariation(newVar);
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
                std::multimap<unsigned, String> sorted;
                for (Map<String, unsigned>::ConstIterator i = vsParams_.Begin(); i != vsParams_.End(); ++i)
                    sorted.insert(std::pair<unsigned, String>(i->second_, i->first_));
                
                for (std::multimap<unsigned, String>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.CreateChildElement("parameter");
                    param.SetString("name", i->second);
                    param.SetString("index", ToString(i->first));
                }
            }
            
            {
                XMLElement parameters = outShaders.CreateChildElement("psparameters");
                std::multimap<unsigned, String> sorted;
                for (Map<String, unsigned>::ConstIterator i = psParams_.Begin(); i != psParams_.End(); ++i)
                    sorted.insert(std::pair<unsigned, String>(i->second_, i->first_));
                
                for (std::multimap<unsigned, String>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.CreateChildElement("parameter");
                    param.SetString("name", i->second);
                    param.SetString("index", ToString(i->first));
                }
            }
            
            {
                XMLElement parameters = outShaders.CreateChildElement("textureunits");
                std::multimap<unsigned, String> sorted;
                for (Map<String, unsigned>::ConstIterator i = textureUnits_.Begin(); i != textureUnits_.End(); ++i)
                    sorted.insert(std::pair<unsigned, String>(i->second_, i->first_));
                
                for (std::multimap<unsigned, String>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.CreateChildElement("textureunit");
                    param.SetString("name", i->second);
                    param.SetString("index", ToString(i->first));
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
    Vector<unsigned> compiled;
    bool hasVariations = false;
    
    const Vector<Variation>& variations = baseShader.variations_;
    
    Map<String, unsigned> nameToIndex;
    
    if (variations.Size() > 32)
        ErrorExit("Maximum amount of variations exceeded");
    
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
            
            bool ok = Compile(baseShader.type_, baseShader.name_, outName, defines, params);
            
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

bool Compile(ShaderType type, const String& input, const String& output, const Vector<String>& defines,
    Parameters& params)
{
    bool compiled = false;
    
    String allDefines;
    for (unsigned i = 0; i < defines.Size(); ++i)
        allDefines += "/D" + defines[i] + " ";
    for (unsigned i = 0; i < defines_.Size(); ++i)
        allDefines += "/D" + defines_[i] + " ";
    
    if (type == VS)
    {
        if (!useSM3_)
        {
            String outFile = output + ".vs2";
            String command = "fxc /Tvs_2_0 /O3 /EVS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
                inDir_ + input + ".hlsl";
            
            if (fileSystem_->SystemCommand(command))
                ErrorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
        else
        {
            String outFile = output + ".vs3";
            String command = "fxc /Tvs_3_0 /O3 /EVS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
                inDir_ + input + ".hlsl";
            
            if (fileSystem_->SystemCommand(command))
                ErrorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
    }
    
    if (type == PS)
    {
        if (!useSM3_)
        {
            String outFile = output + ".ps2";
            String command = "fxc /Tps_2_0 /O3 /EPS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
                inDir_ + input + ".hlsl";
            
            if (fileSystem_->SystemCommand(command))
                ErrorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
        else
        {
            String outFile = output + ".ps3";
            String command = "fxc /Tps_3_0 /O3 /Gfp /EPS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
                inDir_ + input + ".hlsl";
            
            if (fileSystem_->SystemCommand(command))
                ErrorExit("Failed to compile shader" + outFile);
            
            compiled = true;
        }
    }
    
    if (!compiled)
        return false;
    
    SharedPtr<File> dump(new File(context_, "output.txt"));
    if (!dump->IsOpen())
        ErrorExit("Could not open dump file");
    
    bool paramsStarted = false;
    
    while (!dump->IsEof())
    {
        String lineStr = dump->ReadLine();
        Vector<String> elements = Split(lineStr, ' ');
        
        if (paramsStarted)
        {
            if ((!elements.Size()) || (elements[0] != "//"))
                break;
            
            if ((elements.Size() == 4) && (elements[0] == "//") && (elements[1][0] != '-'))
            {
                String name = elements[1];
                String reg = elements[2];
                
                bool isSampler = false;
                if (reg[0] == 's')
                    isSampler = true;
                
                if ((name[0] == 'c') || (name[0] == 's'))
                    name = name.Substring(1, name.Length() - 1);
                
                unsigned index = ToInt(reg.Substring(1, reg.Length() - 1));
                
                if (isSampler)
                {
                    // Skip if it's a G-buffer sampler
                    if (name.Find("Buffer") == String::NPOS)
                    {
                        params.addTextureUnit(name, index);
                        
                        if (textureUnits_.Find(name) != textureUnits_.End())
                        {
                            unsigned oldIndex = textureUnits_[name];
                            if (oldIndex != index)
                                ErrorExit("Texture " + name + " bound to several sampler Registers");
                        }
                        textureUnits_[name] = index;
                    }
                }
                else
                {
                    if (type == VS)
                    {
                        params.addVSParam(name, index);
                        
                        if (vsParams_.Find(name) != vsParams_.End())
                        {
                            unsigned oldIndex = vsParams_[name];
                            if (oldIndex != index)
                                ErrorExit("Parameter " + name + " bound to several constant Registers");
                        }
                        vsParams_[name] = index;
                    }
                    else
                    {
                        params.addPSParam(name, index);
                        
                        if (psParams_.Find(name) != psParams_.End())
                        {
                            unsigned oldIndex = psParams_[name];
                            if (oldIndex != index)
                                ErrorExit("Parameter " + name + " bound to several constant Registers");
                        }
                        psParams_[name] = index;
                    }
                }
            }
        }
        else
        {
            if ((elements.Size() == 4) && (elements[0] == "//") && (elements[1] == "Name"))
                paramsStarted = true;
        }
    }
    
    dump->Close();
    remove("output.txt");
    
    return true;
}
