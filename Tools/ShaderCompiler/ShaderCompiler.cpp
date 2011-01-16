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

#include "Exception.h"
#include "File.h"
#include "StringUtils.h"
#include "XMLFile.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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
    Variation(const std::string& name, bool isOption) :
        mName(name),
        mOption(isOption)
    {
    }
    
    void addDefine(const std::string& def)
    {
        mDefines.push_back(def);
    }
    
    void addExclude(const std::string& excl)
    {
        mExcludes.push_back(excl);
    }
    
    void addInclude(const std::string& incl)
    {
        mIncludes.push_back(incl);
    }
    
    void addRequire(const std::string& req)
    {
        mRequires.push_back(req);
    }
    
    std::string mName;
    std::vector<std::string> mDefines;
    std::vector<std::string> mExcludes;
    std::vector<std::string> mIncludes;
    std::vector<std::string> mRequires;
    bool mOption;
};

struct Shader
{
    Shader(const std::string& name, ShaderType type) :
        mName(name),
        mType(type)
    {
    }
    
    void addVariation(const Variation& var)
    {
        mVariations.push_back(var);
    }
    
    std::string mName;
    ShaderType mType;
    std::vector<Variation> mVariations;
};

struct Parameter
{
    std::string mName;
    unsigned mIndex;
};

struct Parameters
{
    void addVSParam(const std::string& name, unsigned index)
    {
        Parameter newParam;
        newParam.mName = name;
        newParam.mIndex = index;
        
        mVSParams.push_back(newParam);
    }
    
    void addPSParam(const std::string& name, unsigned index)
    {
        Parameter newParam;
        newParam.mName = name;
        newParam.mIndex = index;
        
        mPSParams.push_back(newParam);
    }
    
    void addTextureUnit(const std::string& name, unsigned index)
    {
        Parameter newParam;
        newParam.mName = name;
        newParam.mIndex = index;
        
        mTextureUnits.push_back(newParam);
    }
    
    std::vector<Parameter> mVSParams;
    std::vector<Parameter> mPSParams;
    std::vector<Parameter> mTextureUnits;
};

std::string gInDir;
std::string gInFile;
std::string gOutDir;
std::map<std::string, unsigned> gVSParams;
std::map<std::string, unsigned> gPSParams;
std::map<std::string, unsigned> gTextureUnits;

bool gUseSM3 = false;
std::vector<std::string> gDefines;

int main(int argc, char** argv);
void run(const std::vector<std::string>& arguments);
void compileVariations(const Shader& baseShader, XMLElement& shaders);
bool compile(ShaderType type, const std::string& input, const std::string& output, const std::vector<std::string>& defines, Parameters& params);
void errorExit(const std::string& error);

int main(int argc, char** argv)
{
    std::vector<std::string> arguments;
    
    for (int i = 1; i < argc; ++i)
        arguments.push_back(replace(std::string(argv[i]), '/', '\\'));
    
    try
    {
        run(arguments);
    }
    catch (Exception& e)
    {
        std::cout << e.whatStr() << std::endl;
        return 1;
    }
    
    return 0;
}

void run(const std::vector<std::string>& arguments)
{
    if (arguments.size() < 2)
    {
        errorExit(
            "Usage: ShaderCompiler <definitionfile> <outputpath> [SM3] [define1] [define2]\n"
            "Note: .hlsl files will be loaded from definition file directory, and binary\n"
            "code will be output to same directory as the output file."
        );
    }
    
    size_t pos = arguments[0].rfind('\\');
    if (pos != std::string::npos)
    {
        gInDir = arguments[0].substr(0, pos);
        gInFile = arguments[0].substr(pos + 1);
    }
    else
    {
        gInFile = arguments[0];
    }
    
    gOutDir = arguments[1];
    
    if (gInDir.empty())
        gInDir = ".\\";
    
    if (gOutDir.empty())
        gOutDir = ".\\";
    
    if (gInDir[gInDir.length()-1] != '\\')
        gInDir = gInDir + "\\";
    
    if (gOutDir[gOutDir.length()-1] != '\\')
        gOutDir = gOutDir + "\\";
    
    for (unsigned i = 2; i < arguments.size(); ++i)
    {
        std::string arg = toUpper(arguments[i]);
        
        if (arg == "SM3")
            gUseSM3 = true;
        else if (arg == "SM2")
            gUseSM3 = false;
        
        gDefines.push_back(arg);
    }
    
    XMLFile doc;
    File source(arguments[0]);
    doc.load(source);
    XMLElement shaders = doc.getRootElement("shaders");
    
    XMLFile outDoc;
    XMLElement outShaders = outDoc.createRootElement("shaders");
    
    XMLElement shader = shaders.getChildElement("shader", false);
    while (shader.notNull())
    {
        bool writeOutput = false;
        
        std::string source = shader.getString("name");
        
        ShaderType compileType = Both;
        std::string type = shader.getString("type", false);
        if ((type == "VS") || (type == "vs"))
            compileType = VS;
        if ((type == "PS") || (type == "ps"))
            compileType = PS;
        if ((compileType == Both) || (compileType == PS))
            writeOutput = true;
        
        Shader baseShader(source, compileType);
        
        XMLElement variation = shader.getChildElement("", false);
        while (variation.notNull())
        {
            std::string value = variation.getName();
            if ((value == "variation") || (value == "option"))
            {
                std::string name = variation.getString("name");
                
                Variation newVar(name, value == "option");
                
                std::string simpleDefine = variation.getString("define", false);
                if (!simpleDefine.empty())
                    newVar.addDefine(simpleDefine);
                    
                std::string simpleExclude = variation.getString("exclude", false);
                if (!simpleExclude.empty())
                    newVar.addExclude(simpleExclude);
                
                std::string simpleInclude = variation.getString("include", false);
                if (!simpleInclude.empty())
                    newVar.addInclude(simpleInclude);
                
                std::string simpleRequire = variation.getString("require", false);
                if (!simpleRequire.empty())
                    newVar.addRequire(simpleRequire);
                
                XMLElement define = variation.getChildElement("define", false);
                while (define.notNull())
                {
                    std::string name = define.getString("name");
                    newVar.addDefine(name);
                    
                    define = define.getNextElement("define");
                }
                
                XMLElement exclude = variation.getChildElement("exclude", false);
                while (exclude.notNull())
                {
                    std::string name = exclude.getString("name");
                    newVar.addExclude(name);
                    
                    exclude = exclude.getNextElement("exclude");
                }
                
                XMLElement include = variation.getChildElement("include", false);
                while (include.notNull())
                {
                    std::string name = include.getString("name");
                    newVar.addInclude(name);
                    
                    include = include.getNextElement("include");
                }
                
                XMLElement require = variation.getChildElement("require", false);
                while (require.notNull())
                {
                    std::string name = require.getString("name");
                    newVar.addRequire(name);
                    
                    require = require.getNextElement("require");
                }
                
                baseShader.addVariation(newVar);
            }
            
            variation = variation.getNextElement();
        }
        
        if (baseShader.mType != Both)
            compileVariations(baseShader, outShaders);
        else
        {
            baseShader.mType = VS;
            compileVariations(baseShader, outShaders);
            baseShader.mType = PS;
            compileVariations(baseShader, outShaders);
        }
        
        if (writeOutput)
        {
            std::string outFileName = gOutDir + gInDir + source + ".xml";
            remove(outFileName.c_str());
            
            // Add global parameter & texture sampler definitions
            {
                XMLElement parameters = outShaders.createChildElement("vsparameters");
                std::multimap<unsigned, std::string> sorted;
                for (std::map<std::string, unsigned>::const_iterator i = gVSParams.begin(); i != gVSParams.end(); ++i)
                    sorted.insert(std::pair<unsigned, std::string>(i->second, i->first));
                
                for (std::multimap<unsigned, std::string>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.createChildElement("parameter");
                    param.setString("name", i->second);
                    param.setString("index", toString(i->first));
                }
            }
            
            {
                XMLElement parameters = outShaders.createChildElement("psparameters");
                std::multimap<unsigned, std::string> sorted;
                for (std::map<std::string, unsigned>::const_iterator i = gPSParams.begin(); i != gPSParams.end(); ++i)
                    sorted.insert(std::pair<unsigned, std::string>(i->second, i->first));
                
                for (std::multimap<unsigned, std::string>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.createChildElement("parameter");
                    param.setString("name", i->second);
                    param.setString("index", toString(i->first));
                }
            }
            
            {
                XMLElement parameters = outShaders.createChildElement("textureunits");
                std::multimap<unsigned, std::string> sorted;
                for (std::map<std::string, unsigned>::const_iterator i = gTextureUnits.begin(); i != gTextureUnits.end(); ++i)
                    sorted.insert(std::pair<unsigned, std::string>(i->second, i->first));
                
                for (std::multimap<unsigned, std::string>::const_iterator i = sorted.begin(); i != sorted.end(); ++i)
                {
                    XMLElement param = parameters.createChildElement("textureunit");
                    param.setString("name", i->second);
                    param.setString("index", toString(i->first));
                }
            }
            
            File outFile(outFileName, FILE_WRITE);
            outDoc.save(outFile);
        }
        
        shader = shader.getNextElement("shader");
    }
}

void compileVariations(const Shader& baseShader, XMLElement& shaders)
{
    unsigned combinations = 1;
    std::vector<unsigned> compiled;
    bool hasVariations = false;
    
    const std::vector<Variation>& variations = baseShader.mVariations;
    
    std::map<std::string, unsigned> nameToIndex;
    
    if (variations.size() > 32)
        errorExit("Maximum amount of variations exceeded");
    
    for (unsigned i = 0; i < variations.size(); ++i)
    {
        combinations *= 2;
        nameToIndex[variations[i].mName] = i;
        if (!variations[i].mOption)
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
                for (unsigned k = 0; k < variations[j].mIncludes.size(); ++k)
                {
                    if (nameToIndex.find(variations[j].mIncludes[k]) != nameToIndex.end())
                        active |= (1 << nameToIndex[variations[j].mIncludes[k]]);
                }
                
                for (unsigned k = 0; k < variations[j].mExcludes.size(); ++k)
                {
                    if (nameToIndex.find(variations[j].mExcludes[k]) != nameToIndex.end())
                        active &= ~(1 << nameToIndex[variations[j].mExcludes[k]]);
                }
                
                // If it's a variation, exclude all other variations
                if (!variations[j].mOption)
                {
                    for (unsigned k = 0; k < variations.size(); ++k)
                    {
                        if ((k != j) && (!variations[k].mOption))
                            active &= ~(1 << k);
                    }
                    
                    variationActive = true;
                }
                
                for (unsigned k = 0; k < variations[j].mRequires.size(); ++k)
                {
                    bool requireFound = false;
                    
                    for (unsigned l = 0; l < gDefines.size(); ++l)
                    {
                        if (gDefines[l] == variations[j].mRequires[k])
                        {
                            requireFound = true;
                            break;
                        }
                    }
                    
                    for (unsigned l = 0; l < variations.size(); ++l)
                    {
                        if (((active >> l) & 1) && (l != j))
                        {
                            if (variations[l].mName == variations[j].mRequires[k])
                            {
                                requireFound = true;
                                break;
                            }
                            for (unsigned m = 0; m < variations[l].mDefines.size(); ++m)
                            {
                                if (variations[l].mDefines[m] == variations[j].mRequires[k])
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
            std::string outName  = baseShader.mName;
            std::vector<std::string> defines;
            for (unsigned j = 0; j < variations.size(); ++j)
            {
                if (active & (1 << j))
                {
                    if (variations[j].mName.length())
                    {
                        if (firstSuffix)
                        {
                            outName = outName + "_" + variations[j].mName;
                            firstSuffix = false;
                        }
                        else
                            outName = outName + variations[j].mName;
                    }
                    for (unsigned k = 0; k < variations[j].mDefines.size(); ++k)
                        defines.push_back(variations[j].mDefines[k]);
                }
            }
            
            Parameters params;
            
            bool ok = compile(baseShader.mType, baseShader.mName, outName, defines, params);
            
            // If shader was unnecessary (for example SM2 does not support HQ variations)
            // no output may have been produced. Skip in that case.
            if (ok)
            {
                XMLElement shader = shaders.createChildElement("shader");
                shader.setString("name", outName);
                switch (baseShader.mType)
                {
                case VS:
                    shader.setString("type", "vs");
                    for (unsigned j = 0; j < params.mVSParams.size(); ++j)
                    {
                        XMLElement vsParam = shader.createChildElement("parameter");
                        vsParam.setString("name", params.mVSParams[j].mName);
                    }
                    break;
                    
                case PS:
                    shader.setString("type", "ps");
                    for (unsigned j = 0; j < params.mPSParams.size(); ++j)
                    {
                        XMLElement psParam = shader.createChildElement("parameter");
                        psParam.setString("name", params.mPSParams[j].mName);
                    }
                    for (unsigned j = 0; j < params.mTextureUnits.size(); ++j)
                    {
                        XMLElement texture = shader.createChildElement("textureunit");
                        texture.setString("name", params.mTextureUnits[j].mName);
                    }
                    break;
                }
                
                compiled.push_back(active);
            }
        }
    }
}

bool compile(ShaderType type, const std::string& input, const std::string& output, const std::vector<std::string>& defines,
    Parameters& params)
{
    bool compiled = false;
    
    if (type == VS)
    {
        if (!gUseSM3)
        {
            std::string outFile = output + ".vs2";
            std::string command = "fxc /Tvs_2_0 /O3 /Evs /Fo" + gOutDir + gInDir + outFile + " /Fcoutput.txt ";
            for (unsigned i = 0; i < defines.size(); ++i)
            {
                command += "/D" + defines[i] + " ";
            }
            for (unsigned i = 0; i < gDefines.size(); ++i)
            {
                command += "/D" + gDefines[i] + " ";
            }
            
            command += gInDir + input + ".hlsl";
            
            if (system(command.c_str()))
                errorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
        else
        {
            std::string outFile = output + ".vs3";
            std::string command = "fxc /Tvs_3_0 /O3 /Evs /Fo" + gOutDir + gInDir + outFile + " /Fcoutput.txt ";
            for (unsigned i = 0; i < defines.size(); ++i)
            {
                command += "/D" + defines[i] + " ";
            }
            for (unsigned i = 0; i < gDefines.size(); ++i)
            {
                command += "/D" + gDefines[i] + " ";
            }
            
            
            command += gInDir + input + ".hlsl";
            
            if (system(command.c_str()))
                errorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
    }
    
    if (type == PS)
    {
        if (!gUseSM3)
        {
            std::string outFile = output + ".ps2";
            std::string command = "fxc /Tps_2_0 /O3 /Eps /Fo" + gOutDir + gInDir + outFile + " /Fcoutput.txt ";
            for (unsigned i = 0; i < defines.size(); ++i)
            {
                command += "/D" + defines[i] + " ";
            }
            for (unsigned i = 0; i < gDefines.size(); ++i)
            {
                command += "/D" + gDefines[i] + " ";
            }
            
            command += gInDir + input + ".hlsl";
            
            std::cout << command << std::endl;
            if (system(command.c_str()))
                errorExit("Failed to compile shader " + outFile);
            
            compiled = true;
        }
        else
        {
            std::string outFile = output + ".ps3";
            std::string command = "fxc /Tps_3_0 /O3 /Gfp /Eps /Fo" + gOutDir + gInDir + outFile + " /Fcoutput.txt ";
            for (unsigned i = 0; i < defines.size(); ++i)
            {
                command += "/D" + defines[i] + " ";
            }
            for (unsigned i = 0; i < gDefines.size(); ++i)
            {
                command += "/D" + gDefines[i] + " ";
            }
            
            command += gInDir + input + ".hlsl";
            
            std::cout << command << std::endl;
            if (system(command.c_str()))
                errorExit("Failed to compile shader" + outFile);
            
            compiled = true;
        }
    }
    
    if (!compiled)
        return false;
    
    std::ifstream dump("output.txt");
    if (!dump.good())
        errorExit("Could not open dump file");
    
    bool paramsStarted = false;
    
    while (!dump.eof())
    {
        char line[256];
        dump.getline(line, 256);
        std::string lineStr(line);
        std::vector<std::string> elements = split(lineStr, ' ');
        
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
                
                unsigned index = toInt(reg.substr(1, reg.size() - 1));
                
                if (isSampler)
                {
                    // Skip if it's a G-buffer sampler
                    if (name.find("Buffer") == std::string::npos)
                    {
                        params.addTextureUnit(name, index);
                        
                        if (gTextureUnits.find(name) != gTextureUnits.end())
                        {
                            unsigned oldIndex = gTextureUnits[name];
                            if (oldIndex != index)
                                errorExit("Texture " + name + " bound to several sampler registers");
                        }
                        gTextureUnits[name] = index;
                    }
                }
                else
                {
                    if (type == VS)
                    {
                        params.addVSParam(name, index);
                        
                        if (gVSParams.find(name) != gVSParams.end())
                        {
                            unsigned oldIndex = gVSParams[name];
                            if (oldIndex != index)
                                errorExit("Parameter " + name + " bound to several constant registers");
                        }
                        gVSParams[name] = index;
                    }
                    else
                    {
                        params.addPSParam(name, index);
                        
                        if (gPSParams.find(name) != gPSParams.end())
                        {
                            unsigned oldIndex = gPSParams[name];
                            if (oldIndex != index)
                                errorExit("Parameter " + name + " bound to several constant registers");
                        }
                        gPSParams[name] = index;
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

void errorExit(const std::string& error)
{
    throw Exception(error);
}
