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
#include "List.h"
#include "Mutex.h"
#include "ProcessUtils.h"
#include "StringUtils.h"
#include "Thread.h"
#include "XMLFile.h"

#include <cstdio>
#include <cstring>

#include "DebugNew.h"

enum ShaderType
{
    VS = 0,
    PS,
    Both
};


struct Parameter
{
    Parameter()
    {
    }
    
    Parameter(const String& name, unsigned index) :
        name_(name),
        index_(index)
    {
    }
    
    bool operator < (const Parameter& rhs) const
    {
        if (index_ != rhs.index_)
            return index_ < rhs.index_;
        else
            return name_ < rhs.name_;
    }
    
    bool operator > (const Parameter& rhs) const
    {
        if (index_ != rhs.index_)
            return index_ > rhs.index_;
        else
            return name_ > rhs.name_;
    }
    
    bool operator == (const Parameter& rhs) const { return index_ == rhs.index_ && name_ == rhs.name_; }
    
    bool operator != (const Parameter& rhs) const { return index_ != rhs.index_ || name_ != rhs.name_; }
    
    String name_;
    unsigned index_;
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
    
    String name_;
    Vector<String> defines_;
    Vector<String> excludes_;
    Vector<String> includes_;
    Vector<String> requires_;
    bool option_;
};

struct ProcessedVariation
{
    ShaderType type_;
    String name_;
    Vector<String> defines_;
};

struct Shader
{
    Shader(const String& name, ShaderType type) :
        name_(name),
        type_(type)
    {
    }
    
    String name_;
    ShaderType type_;
    Vector<Variation> variations_;
};


SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
String inDir_;
String inFile_;
String outDir_;
Set<Parameter> constants_;
Set<Parameter> textureUnits_;
Vector<String> defines_;
Vector<String> glslCode_;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void ProcessVariations(const Shader& baseShader, XMLElement& shaders);

int main(int argc, char** argv)
{
    Vector<String> arguments;
    
    for (int i = 1; i < argc; ++i)
    {
        String argument(argv[i]);
        arguments.Push(GetInternalPath(argument));
    }
    
    Run(arguments);
    return 0;
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 2)
    {
        ErrorExit(
            "Usage: GLShaderProcessor <definitionfile> <outputpath> [define1] [define2]\n\n"
            "GLSL files will be loaded from definition file directory, and finalized GLSL +\n"
            "XML files are saved to the output path, preserving the subdirectory structure.\n"
        );
    }
    
    unsigned pos = arguments[0].FindLast('/');
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
        
        defines_.Push(arg);
    }
    
    XMLFile doc(context_);
    File source(context_);
    source.Open(arguments[0]);
    if (!doc.Load(source))
        ErrorExit("Could not open input file " + arguments[0]);
    
    XMLElement shaders = doc.GetRoot("shaders");
    if (!shaders)
        ErrorExit("No shaders element in " + source.GetName());
    
    XMLFile outDoc(context_);
    XMLElement outShaders = outDoc.CreateRoot("shaders");
    
    XMLElement shader = shaders.GetChild("shader");
    while (shader)
    {
        String source = shader.GetString("name");
        ShaderType compileType = Both;
        String type = shader.GetString("type");
        if (type == "VS" || type == "vs")
            compileType = VS;
        if (type == "PS" || type == "ps")
            compileType = PS;
        
        Shader baseShader(source, compileType);
        
        XMLElement variation = shader.GetChild("");
        while (variation)
        {
            String value = variation.GetName();
            if (value == "variation" || value == "option")
            {
                String name = variation.GetString("name");
                
                Variation newVar(name, value == "option");
                
                String simpleDefine = variation.GetString("define");
                if (!simpleDefine.Empty())
                    newVar.defines_.Push(simpleDefine);
                    
                String simpleExclude = variation.GetString("exclude");
                if (!simpleExclude.Empty())
                    newVar.excludes_.Push(simpleExclude);
                
                String simpleInclude = variation.GetString("include");
                if (!simpleInclude.Empty())
                    newVar.includes_.Push(simpleInclude);
                
                String simpleRequire = variation.GetString("require");
                if (!simpleRequire.Empty())
                    newVar.requires_.Push(simpleRequire);
                
                XMLElement define = variation.GetChild("define");
                while (define)
                {
                    newVar.defines_.Push(define.GetString("name"));
                    define = define.GetNext("define");
                }
                
                XMLElement exclude = variation.GetChild("exclude");
                while (exclude)
                {
                    newVar.excludes_.Push(exclude.GetString("name"));
                    exclude = exclude.GetNext("exclude");
                }
                
                XMLElement include = variation.GetChild("include");
                while (include)
                {
                    newVar.includes_.Push(include.GetString("name"));
                    include = include.GetNext("include");
                }
                
                XMLElement require = variation.GetChild("require");
                while (require)
                {
                    newVar.requires_.Push(require.GetString("name"));
                    require = require.GetNext("require");
                }
                
                baseShader.variations_.Push(newVar);
            }
            
            variation = variation.GetNext();
        }
        
        if (baseShader.type_ != Both)
            ProcessVariations(baseShader, outShaders);
        else
        {
            baseShader.type_ = VS;
            ProcessVariations(baseShader, outShaders);
            baseShader.type_ = PS;
            ProcessVariations(baseShader, outShaders);
        }
        
        shader = shader.GetNext("shader");
    }
}

void ProcessVariations(const Shader& baseShader, XMLElement& shaders)
{
    constants_.Clear();
    textureUnits_.Clear();
    
    unsigned combinations = 1;
    PODVector<unsigned> usedCombinations;
    Map<String, unsigned> nameToIndex;
    Vector<ProcessedVariation> processedVariations;
    bool hasVariations = false;
    
    const Vector<Variation>& variations = baseShader.variations_;
    
    if (variations.Size() > 32)
        ErrorExit("Maximum amount of variations exceeded");
    
    // Load the shader source code
    String inputFileName = inDir_ + baseShader.name_;
    if (baseShader.type_ == VS)
        inputFileName += ".vert";
    if (baseShader.type_ == PS)
        inputFileName += ".frag";
    {
        File glslFile(context_, inputFileName);
        if (!glslFile.IsOpen())
            ErrorExit("Could not open input file " + inputFileName);
        
        glslCode_.Clear();
        while (!glslFile.IsEof())
            glslCode_.Push(glslFile.ReadLine());
    }
    
    // Process the code for includes
    for (unsigned i = 0; i < glslCode_.Size(); ++i)
    {
        if (glslCode_[i].Find("#include") == 0)
        {
            unsigned quoteStart = glslCode_[i].Find('<');
            unsigned quoteEnd = glslCode_[i].FindLast('>');
            if (quoteStart == String::NPOS)
            {
                quoteStart = glslCode_[i].Find('\"');
                quoteEnd = glslCode_[i].FindLast('\"');
            }
            if (quoteStart != String::NPOS)
            {
                ++quoteStart;
                String includeFileName = glslCode_[i].Substring(quoteStart, quoteEnd - quoteStart);
                String inputFilePath = GetPath(inputFileName);
                while (includeFileName.Find("../") == 0 || includeFileName.Find("..\\") == 0)
                {
                    includeFileName = includeFileName.Substring(3);
                    inputFilePath = GetParentPath(inputFilePath);
                }
                includeFileName = inputFilePath + includeFileName;
                
                File glslIncludeFile(context_, includeFileName);
                if (!glslIncludeFile.IsOpen())
                    ErrorExit("Could not open input file " + includeFileName);
                
                // Remove the #include line, then include the code
                glslCode_.Erase(i);
                unsigned pos = i;
                while (!glslIncludeFile.IsEof())
                {
                    glslCode_.Insert(pos, glslIncludeFile.ReadLine());
                    ++pos;
                }
                // Finally insert an empty line to mark the space between files
                glslCode_.Insert(pos, "");
            }
        }
    }
    
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
                        if (k != j && !variations[k].option_)
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
                        if ((active >> l) & 1 && l != j)
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
        if (hasVariations && !variationActive)
            continue;
        
        if (skipThis)
            continue;
        
        // Check that this combination is unique
        bool unique = true;
        for (unsigned j = 0; j < usedCombinations.Size(); ++j)
        {
            if (usedCombinations[j] == active)
            {
                unique = false;
                break;
            }
        }
        
        if (unique)
        {
            // Build shader variation name & define active variations
            String outName;
            Vector<String> defines;
            for (unsigned j = 0; j < variations.Size(); ++j)
            {
                if (active & (1 << j))
                {
                    if (variations[j].name_.Length())
                        outName += variations[j].name_;
                    for (unsigned k = 0; k < variations[j].defines_.Size(); ++k)
                        defines.Push(variations[j].defines_[k]);
                }
            }
            
            ProcessedVariation processed;
            processed.type_ = baseShader.type_;
            processed.name_ = outName;
            processed.defines_ = defines;
            
            processedVariations.Push(processed);
            usedCombinations.Push(active);
        }
    }
    
    // Build the output file
    String glslOutFileName = outDir_ + inDir_ + baseShader.name_;
    glslOutFileName += baseShader.type_ == VS ? ".vert" : ".frag";
    String xmlOutFileName = glslOutFileName + ".xml";
    
    File outFile(context_, glslOutFileName, FILE_WRITE);
    if (!outFile.IsOpen())
        ErrorExit("Could not open output file " + glslOutFileName);
    for (unsigned i = 0; i < glslCode_.Size(); ++i)
    {
        outFile.Write(&glslCode_[i][0], glslCode_[i].Length());
        outFile.WriteByte(10);
    }
    outFile.Close();
    
    XMLFile xmlOutFile(context_);
    XMLElement shaderElem = xmlOutFile.CreateRoot("shader");
    shaderElem.SetString("type", baseShader.type_ == VS ? "vs" : "ps");
    for (unsigned i = 0; i < processedVariations.Size(); ++i)
    {
        XMLElement variationElem = shaderElem.CreateChild("variation");
        variationElem.SetString("name", processedVariations[i].name_);
        
        String allDefines;
        for (unsigned j = 0; j < processedVariations[i].defines_.Size(); ++j)
        {
            if (j)
                allDefines += " ";
            allDefines += processedVariations[i].defines_[j];
        }
        
        variationElem.SetString("defines", allDefines);
    }
    
    outFile.Open(xmlOutFileName, FILE_WRITE);
    if (!outFile.IsOpen())
        ErrorExit("Could not open output file " + xmlOutFileName);
    xmlOutFile.Save(outFile);
    outFile.Close();
}

