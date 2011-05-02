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
#include "StringUtils.h"
#include "XMLFile.h"

#include <cstring>
#include <fstream>
#include <iostream>

#include "DebugNew.h"

enum ShaderType
{
    VS,
    PS,
    Both
};

struct Variation
{
    Variation(const std::string& name, bool isOption) :
        name_(name),
        option_(isOption)
    {
    }
    
    void addDefine(const std::string& def)
    {
        defines_.push_back(def);
    }
    
    void addExclude(const std::string& excl)
    {
        excludes_.push_back(excl);
    }
    
    void addInclude(const std::string& incl)
    {
        includes_.push_back(incl);
    }
    
    void addRequire(const std::string& req)
    {
        requires_.push_back(req);
    }
    
    std::string name_;
    std::vector<std::string> defines_;
    std::vector<std::string> excludes_;
    std::vector<std::string> includes_;
    std::vector<std::string> requires_;
    bool option_;
};

struct Shader
{
    Shader(const std::string& name, ShaderType type) :
        name_(name),
        type_(type)
    {
    }
    
    void addVariation(const Variation& var)
    {
        variations_.push_back(var);
    }
    
    std::string name_;
    ShaderType type_;
    std::vector<Variation> variations_;
};

struct Parameter
{
    std::string name_;
    unsigned index_;
};

struct Parameters
{
    void addVSParam(const std::string& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        vsParams_.push_back(newParam);
    }
    
    void addPSParam(const std::string& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        psParams_.push_back(newParam);
    }
    
    void addTextureUnit(const std::string& name, unsigned index)
    {
        Parameter newParam;
        newParam.name_ = name;
        newParam.index_ = index;
        
        textureUnits_.push_back(newParam);
    }
    
    std::vector<Parameter> vsParams_;
    std::vector<Parameter> psParams_;
    std::vector<Parameter> textureUnits_;
};

SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
std::string inDir_;
std::string inFile_;
std::string outDir_;
std::map<std::string, unsigned> vsParams_;
std::map<std::string, unsigned> psParams_;
std::map<std::string, unsigned> textureUnits_;
std::vector<std::string> defines_;
bool useSM3_ = false;

int main(int argc, char** argv);
void Run(const std::vector<std::string>& arguments);
void CompileVariations(const Shader& baseShader, XMLElement& shaders);
bool Compile(ShaderType type, const std::string& input, const std::string& output, const std::vector<std::string>& defines, Parameters& params);
void ErrorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(Replace(std::string(argv[i]), '/', '\\'));
    
    Run(arguments);
    return 0;
}

void Run(const std::vector<std::string>& arguments)
{
    if (arguments.size() < 2)
    {
        ErrorExit(
            "Usage: ShaderCompiler <definitionfile> <outputpath> [SM3] [define1] [define2]\n\n"
            "HLSL files will be loaded from definition file directory, and binary code will\n"
            "be output to same directory as the output file.\n"
        );
    }
    
    size_t pos = arguments[0].rfind('\\');
    if (pos != std::string::npos)
    {
        inDir_ = arguments[0].substr(0, pos);
        inFile_ = arguments[0].substr(pos + 1);
    }
    else
    {
        inFile_ = arguments[0];
    }
    
    outDir_ = arguments[1];
    
    if (inDir_.empty())
        inDir_ = ".\\";
    
    if (outDir_.empty())
        outDir_ = ".\\";
    
    if (inDir_[inDir_.length()-1] != '\\')
        inDir_ = inDir_ + "\\";
    
    if (outDir_[outDir_.length()-1] != '\\')
        outDir_ = outDir_ + "\\";
    
    for (unsigned i = 2; i < arguments.size(); ++i)
    {
        std::string arg = ToUpper(arguments[i]);
        
        if (arg == "SM3")
            useSM3_ = true;
        else if (arg == "SM2")
            useSM3_ = false;
        
        defines_.push_back(arg);
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
        
        std::string source = shader.GetString("name");
        
        ShaderType compileType = Both;
        std::string type = shader.GetString("type");
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
            std::string value = variation.GetName();
            if ((value == "variation") || (value == "option"))
            {
                std::string name = variation.GetString("name");
                
                Variation newVar(name, value == "option");
                
                std::string simpleDefine = variation.GetString("define");
                if (!simpleDefine.empty())
                    newVar.addDefine(simpleDefine);
                    
                std::string simpleExclude = variation.GetString("exclude");
                if (!simpleExclude.empty())
                    newVar.addExclude(simpleExclude);
                
                std::string simpleInclude = variation.GetString("include");
                if (!simpleInclude.empty())
                    newVar.addInclude(simpleInclude);
                
                std::string simpleRequire = variation.GetString("require");
                if (!simpleRequire.empty())
                    newVar.addRequire(simpleRequire);
                
                XMLElement define = variation.GetChildElement("define");
                while (define)
                {
                    std::string name = define.GetString("name");
                    newVar.addDefine(name);
                    
                    define = define.GetNextElement("define");
                }
                
                XMLElement exclude = variation.GetChildElement("exclude");
                while (exclude)
                {
                    std::string name = exclude.GetString("name");
                    newVar.addExclude(name);
                    
                    exclude = exclude.GetNextElement("exclude");
                }
                
                XMLElement include = variation.GetChildElement("include");
                while (include)
                {
                    std::string name = include.GetString("name");
                    newVar.addInclude(name);
                    
                    include = include.GetNextElement("include");
                }
                
                XMLElement require = variation.GetChildElement("require");
                while (require)
                {
                    std::string name = require.GetString("name");
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
            std::string outFileName = outDir_ + inDir_ + source + ".xml";
            remove(outFileName.c_str());
            
            // Add global parameter & texture sampler definitions
            {
                XMLElement parameters = outShaders.CreateChildElement("vsparameters");
                std::multimap<unsigned, std::string> sorted;
                for (std::map<std::string, unsigned>::const_iterator i = vsParams_.begin(); i != vsParams_.end(); ++i)
                    sorted.insert(std::pair<unsigned, std::string>(i->second, i->first));
                
                for (std::multimap<unsigned, std::string>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.CreateChildElement("parameter");
                    param.SetString("name", i->second);
                    param.SetString("index", ToString(i->first));
                }
            }
            
            {
                XMLElement parameters = outShaders.CreateChildElement("psparameters");
                std::multimap<unsigned, std::string> sorted;
                for (std::map<std::string, unsigned>::const_iterator i = psParams_.begin(); i != psParams_.end(); ++i)
                    sorted.insert(std::pair<unsigned, std::string>(i->second, i->first));
                
                for (std::multimap<unsigned, std::string>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.CreateChildElement("parameter");
                    param.SetString("name", i->second);
                    param.SetString("index", ToString(i->first));
                }
            }
            
            {
                XMLElement parameters = outShaders.CreateChildElement("textureunits");
                std::multimap<unsigned, std::string> sorted;
                for (std::map<std::string, unsigned>::const_iterator i = textureUnits_.begin(); i != textureUnits_.end(); ++i)
                    sorted.insert(std::pair<unsigned, std::string>(i->second, i->first));
                
                for (std::multimap<unsigned, std::string>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
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
    std::vector<unsigned> compiled;
    bool hasVariations = false;
    
    const std::vector<Variation>& variations = baseShader.variations_;
    
    std::map<std::string, unsigned> nameToIndex;
    
    if (variations.size() > 32)
        ErrorExit("Maximum amount of variations exceeded");
    
    for (unsigned i = 0; i < variations.size(); ++i)
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
        for (unsigned j = 0; j < variations.size(); ++j)
        {
            if ((active >> j) & 1)
            {
                for (unsigned k = 0; k < variations[j].includes_.size(); ++k)
                {
                    if (nameToIndex.find(variations[j].includes_[k]) != nameToIndex.end())
                        active |= (1 << nameToIndex[variations[j].includes_[k]]);
                }
                
                for (unsigned k = 0; k < variations[j].excludes_.size(); ++k)
                {
                    if (nameToIndex.find(variations[j].excludes_[k]) != nameToIndex.end())
                        active &= ~(1 << nameToIndex[variations[j].excludes_[k]]);
                }
                
                // If it's a variation, exclude all other variations
                if (!variations[j].option_)
                {
                    for (unsigned k = 0; k < variations.size(); ++k)
                    {
                        if ((k != j) && (!variations[k].option_))
                            active &= ~(1 << k);
                    }
                    
                    variationActive = true;
                }
                
                for (unsigned k = 0; k < variations[j].requires_.size(); ++k)
                {
                    bool requireFound = false;
                    
                    for (unsigned l = 0; l < defines_.size(); ++l)
                    {
                        if (defines_[l] == variations[j].requires_[k])
                        {
                            requireFound = true;
                            break;
                        }
                    }
                    
                    for (unsigned l = 0; l < variations.size(); ++l)
                    {
                        if (((active >> l) & 1) && (l != j))
                        {
                            if (variations[l].name_ == variations[j].requires_[k])
                            {
                                requireFound = true;
                                break;
                            }
                            for (unsigned m = 0; m < variations[l].defines_.size(); ++m)
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
        for (unsigned j = 0; j < compiled.size(); ++j)
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
            std::string outName  = baseShader.name_;
            std::vector<std::string> defines;
            for (unsigned j = 0; j < variations.size(); ++j)
            {
                if (active & (1 << j))
                {
                    if (variations[j].name_.length())
                    {
                        if (firstSuffix)
                        {
                            outName = outName + "_" + variations[j].name_;
                            firstSuffix = false;
                        }
                        else
                            outName = outName + variations[j].name_;
                    }
                    for (unsigned k = 0; k < variations[j].defines_.size(); ++k)
                        defines.push_back(variations[j].defines_[k]);
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
                    for (unsigned j = 0; j < params.vsParams_.size(); ++j)
                    {
                        XMLElement vsParam = shader.CreateChildElement("parameter");
                        vsParam.SetString("name", params.vsParams_[j].name_);
                    }
                    break;
                    
                case PS:
                    shader.SetString("type", "ps");
                    for (unsigned j = 0; j < params.psParams_.size(); ++j)
                    {
                        XMLElement psParam = shader.CreateChildElement("parameter");
                        psParam.SetString("name", params.psParams_[j].name_);
                    }
                    for (unsigned j = 0; j < params.textureUnits_.size(); ++j)
                    {
                        XMLElement texture = shader.CreateChildElement("textureunit");
                        texture.SetString("name", params.textureUnits_[j].name_);
                    }
                    break;
                }
                
                compiled.push_back(active);
            }
        }
    }
}

bool Compile(ShaderType type, const std::string& input, const std::string& output, const std::vector<std::string>& defines,
    Parameters& params)
{
    bool compiled = false;
    
    std::string allDefines;
    for (unsigned i = 0; i < defines.size(); ++i)
        allDefines += "/D" + defines[i] + " ";
    for (unsigned i = 0; i < defines_.size(); ++i)
        allDefines += "/D" + defines_[i] + " ";
    
    if (type == VS)
    {
        if (!useSM3_)
        {
            std::string outFile = output + ".vs2";
            std::string command = "fxc /Tvs_2_0 /O3 /EVS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
                inDir_ + input + ".hlsl";
            
            if (fileSystem_->SystemCommand(command))
                ErrorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
        else
        {
            std::string outFile = output + ".vs3";
            std::string command = "fxc /Tvs_3_0 /O3 /EVS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
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
            std::string outFile = output + ".ps2";
            std::string command = "fxc /Tps_2_0 /O3 /EPS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
                inDir_ + input + ".hlsl";
            
            std::cout << command << std::endl;
            if (fileSystem_->SystemCommand(command))
                ErrorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
        else
        {
            std::string outFile = output + ".ps3";
            std::string command = "fxc /Tps_3_0 /O3 /Gfp /EPS /Fo" + outDir_ + inDir_ + outFile + " /Fcoutput.txt " + allDefines +
                inDir_ + input + ".hlsl";
            
            std::cout << command << std::endl;
            if (fileSystem_->SystemCommand(command))
                ErrorExit("Failed to compile shader" + outFile);
            
            compiled = true;
        }
    }
    
    if (!compiled)
        return false;
    
    std::ifstream dump("output.txt");
    if (!dump.good())
        ErrorExit("Could not open dump file");
    
    bool paramsStarted = false;
    
    while (!dump.eof())
    {
        char line[256];
        dump.getline(line, 256);
        std::string lineStr(line);
        std::vector<std::string> elements = Split(lineStr, ' ');
        
        if (paramsStarted)
        {
            if ((!elements.size()) || (elements[0] != "//"))
                break;
            
            if ((elements.size() == 4) && (elements[0] == "//") && (elements[1][0] != '-'))
            {
                std::string name = elements[1];
                std::string reg = elements[2];
                
                bool isSampler = false;
                if (reg[0] == 's')
                    isSampler = true;
                
                if ((name[0] == 'c') || (name[0] == 's'))
                    name = name.substr(1, name.size() - 1);
                
                unsigned index = ToInt(reg.substr(1, reg.size() - 1));
                
                if (isSampler)
                {
                    // Skip if it's a G-buffer sampler
                    if (name.find("Buffer") == std::string::npos)
                    {
                        params.addTextureUnit(name, index);
                        
                        if (textureUnits_.find(name) != textureUnits_.end())
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
                        
                        if (vsParams_.find(name) != vsParams_.end())
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
                        
                        if (psParams_.find(name) != psParams_.end())
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
            if ((elements.size() == 4) && (elements[0] == "//") && (elements[1] == "Name"))
                paramsStarted = true;
        }
    }
    
    dump.close();
    remove("output.txt");
    
    return true;
}

void ErrorExit(const std::string& error)
{
    std::cout << error;
    exit(1);
}
