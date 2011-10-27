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

#include <windows.h>
#include <d3d9.h>
#include <d3dx9shader.h>

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
    
    Parameter(const String& name, unsigned reg, unsigned regCount) :
        name_(name),
        register_(reg),
        regCount_(regCount)
    {
    }
    
    bool operator < (const Parameter& rhs) const
    {
        if (register_ != rhs.register_)
            return register_ < rhs.register_;
        else if (name_ != rhs.name_)
            return name_ < rhs.name_;
        else
            return regCount_ < rhs.regCount_;
    }
    
    bool operator > (const Parameter& rhs) const
    {
        if (register_ != rhs.register_)
            return register_ > rhs.register_;
        else if (name_ != rhs.name_)
            return name_ > rhs.name_;
        else
            return regCount_ > rhs.regCount_;
    }
    
    bool operator == (const Parameter& rhs) const { return register_ == rhs.register_ && name_ == rhs.name_ && regCount_ == rhs.regCount_; }
    
    bool operator != (const Parameter& rhs) const { return register_ != rhs.register_ || name_ != rhs.name_ || regCount_ != rhs.regCount_; }
    
    String name_;
    unsigned register_;
    unsigned regCount_;
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

struct CompiledVariation
{
    ShaderType type_;
    String name_;
    Vector<String> defines_;
    PODVector<unsigned char> byteCode_;
    unsigned byteCodeOffset_;
    Set<Parameter> constants_;
    Set<Parameter> textureUnits_;
    String errorMsg_;
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
Vector<String> defines_;
bool useSM3_ = false;
volatile bool compileFailed_ = false;

List<CompiledVariation*> workList_;
Mutex globalParamMutex_;
Mutex workMutex_;
String hlslCode_;
Set<String> constants_;
Set<String> textureUnits_;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void CompileVariations(const Shader& baseShader, XMLElement& shaders);
void Compile(CompiledVariation* variation);
void CopyStrippedCode(PODVector<unsigned char>& dest, void* src, unsigned srcSize);

class WorkerThread : public RefCounted, public Thread
{
public:
    void ThreadFunction()
    {
        for (;;)
        {
            CompiledVariation* workItem = 0;
            {
                MutexLock lock(workMutex_);
                if (!workList_.Empty())
                {
                    workItem = workList_.Front();
                    workList_.Erase(workList_.Begin());
                    if (!workItem->name_.Empty())
                        PrintLine("Compiling shader variation " + workItem->name_);
                    else
                        PrintLine("Compiling base shader variation");
                }
            }
            if (!workItem)
                return;
            
            // If compile(s) failed, just empty the list, but do not compile more
            if (!compileFailed_)
                Compile(workItem);
        }
    }
};

class IncludeHandler : public ID3DXInclude
{
public:
    STDMETHOD(Open)(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
    {
        String fileName = inDir_ + String((const char*)pFileName);
        File file(context_, fileName);
        if (!file.IsOpen())
            return E_FAIL;
        
        unsigned fileSize = file.GetSize();
        void* fileData = new unsigned char[fileSize];
        *pBytes = fileSize;
        *ppData = fileData;
        file.Read(fileData, fileSize);
        
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
            "Usage: ShaderCompiler <definitionfile> <outputpath> [SM3] [define1] [define2]\n\n"
            "HLSL files will be loaded from definition file directory, and binary files will\n"
            "be output to the output path, preserving the subdirectory structure.\n"
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
            CompileVariations(baseShader, outShaders);
        else
        {
            baseShader.type_ = VS;
            CompileVariations(baseShader, outShaders);
            baseShader.type_ = PS;
            CompileVariations(baseShader, outShaders);
        }
        
        shader = shader.GetNext("shader");
    }
}

void CompileVariations(const Shader& baseShader, XMLElement& shaders)
{
    unsigned combinations = 1;
    Set<unsigned> usedCombinations;
    Map<String, unsigned> nameToIndex;
    Vector<CompiledVariation> compiledVariations;
    unsigned numVariationGroups = 0;
    
    const Vector<Variation>& variations = baseShader.variations_;
    
    if (variations.Size() > 32)
        ErrorExit("Maximum amount of variations exceeded");
    
    // Load the shader source code
    {
        String inputFileName = inDir_ + baseShader.name_ + ".hlsl";
        File hlslFile(context_, inputFileName);
        if (!hlslFile.IsOpen())
            ErrorExit("Could not open input file " + inputFileName);
        
        hlslCode_.Clear();
        while (!hlslFile.IsEof())
            hlslCode_ += hlslFile.ReadLine() + "\n";
    }
    
    for (unsigned i = 0; i < variations.Size(); ++i)
    {
        combinations *= 2;
        nameToIndex[variations[i].name_] = i;
        if (!variations[i].option_ && (i == 0 || variations[i - 1].option_))
            ++numVariationGroups;
    }
    
    for (unsigned i = 0; i < combinations; ++i)
    {
        unsigned active = i; // Variations/options active on this particular combination
        unsigned variationsActive = 0;
        bool skipThis = false;
        
        // Check for excludes/includes/requires
        for (unsigned j = 0; j < variations.Size(); ++j)
        {
            if ((active >> j) & 1)
            {
                for (unsigned k = 0; k < variations[j].includes_.Size(); ++k)
                {
                    if (nameToIndex.Contains(variations[j].includes_[k]))
                        active |= (1 << nameToIndex[variations[j].includes_[k]]);
                }
                
                for (unsigned k = 0; k < variations[j].excludes_.Size(); ++k)
                {
                    if (nameToIndex.Contains(variations[j].excludes_[k]))
                        active &= ~(1 << nameToIndex[variations[j].excludes_[k]]);
                }
                
                // Skip dummy separators (options without name and defines)
                if (variations[j].name_.Empty() && variations[j].option_ && variations[j].defines_.Empty())
                    active &= ~(1 << j);
                
                // If it's a variation, exclude all other variations in the same group
                if (!variations[j].option_)
                {
                    for (unsigned k = j - 1; k < variations.Size(); --k)
                    {
                        if (!variations[k].option_)
                            active &= ~(1 << k);
                        else
                            break;
                    }
                    for (unsigned k = j + 1; k < variations.Size(); ++k)
                    {
                        if (!variations[k].option_)
                            active &= ~(1 << k);
                        else
                            break;
                    }
                    
                    ++variationsActive;
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
        
        // If variations are included, check that one from each group is active
        if (variationsActive < numVariationGroups)
            continue;
        
        if (skipThis)
            continue;
        
        // Check that this combination is unique
        if (usedCombinations.Contains(active))
            continue;
        
        // Build shader variation name & defines active variations
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
        
        CompiledVariation compile;
        compile.type_ = baseShader.type_;
        compile.name_ = outName;
        compile.defines_ = defines;
        
        compiledVariations.Push(compile);
        usedCombinations.Insert(active);
    }
    
    // Prepare the work list
    // (all variations must be created first, so that vector resize does not change pointers)
    for (unsigned i = 0; i < compiledVariations.Size(); ++i)
        workList_.Push(&compiledVariations[i]);
    
    // Create and start worker threads. Use all cores except one to not lock up the computer completely
    unsigned numWorkerThreads = GetNumCPUCores() - 1;
    if (!numWorkerThreads)
        numWorkerThreads = 1;
    
    Vector<SharedPtr<WorkerThread> > workerThreads;
    workerThreads.Resize(numWorkerThreads);
    for (unsigned i = 0; i < workerThreads.Size(); ++i)
    {
        workerThreads[i] = new WorkerThread();
        workerThreads[i]->Start();
    }
    // This will wait until the thread functions have stopped
    for (unsigned i = 0; i < workerThreads.Size(); ++i)
        workerThreads[i]->Stop();
    
    // Check that all shaders compiled
    for (unsigned i = 0; i < compiledVariations.Size(); ++i)
    {
        if (!compiledVariations[i].errorMsg_.Empty())
            ErrorExit("Failed to compile shader " + baseShader.name_ + "_" + compiledVariations[i].name_ + ": " + compiledVariations[i].errorMsg_);
    }
    
    // Build the output file
    String outFileName = outDir_ + inDir_ + baseShader.name_;
    outFileName += (baseShader.type_ == VS) ? ".vs" : ".ps";
    outFileName += (useSM3_) ? "3" : "2";
    
    File outFile(context_, outFileName, FILE_WRITE);
    if (!outFile.IsOpen())
        ErrorExit("Could not open output file " + outFileName);
    
    outFile.WriteFileID("USHD");
    outFile.WriteShort(baseShader.type_);
    outFile.WriteShort(useSM3_ ? 3 : 2);
    
    outFile.WriteUInt(constants_.Size());
    for (Set<String>::ConstIterator i = constants_.Begin(); i != constants_.End(); ++i)
        outFile.WriteString(*i);
    
    outFile.WriteUInt(textureUnits_.Size());
    for (Set<String>::ConstIterator i = textureUnits_.Begin(); i != textureUnits_.End(); ++i)
        outFile.WriteString(*i);
    
    outFile.WriteUInt(compiledVariations.Size());
    for (unsigned i = 0; i < compiledVariations.Size(); ++i)
    {
        CompiledVariation& variation = compiledVariations[i];
        outFile.WriteString(variation.name_);
        
        outFile.WriteUInt(variation.constants_.Size());
        for (Set<Parameter>::ConstIterator i = variation.constants_.Begin(); i != variation.constants_.End(); ++i)
        {
            outFile.WriteStringHash(StringHash(i->name_));
            outFile.WriteUByte(i->register_);
            outFile.WriteUByte(i->regCount_);
        }
        
        outFile.WriteUInt(variation.textureUnits_.Size());
        for (Set<Parameter>::ConstIterator i = variation.textureUnits_.Begin(); i != variation.textureUnits_.End(); ++i)
        {
            outFile.WriteStringHash(StringHash(i->name_));
            outFile.WriteUByte(i->register_);
        }
        
        unsigned dataSize = variation.byteCode_.Size();
        outFile.WriteUInt(dataSize);
        if (dataSize)
            outFile.Write(&variation.byteCode_[0], dataSize);
    }
}

void Compile(CompiledVariation* variation)
{
    IncludeHandler includeHandler;
    PODVector<D3DXMACRO> macros;
    
    // Insert variation-specific and global defines
    for (unsigned i = 0; i < variation->defines_.Size(); ++i)
    {
        D3DXMACRO macro;
        macro.Name = variation->defines_[i].CString();
        macro.Definition = "1";
        macros.Push(macro);
    }
    for (unsigned i = 0; i < defines_.Size(); ++i)
    {
        D3DXMACRO macro;
        macro.Name = defines_[i].CString();
        macro.Definition = "1";
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
    String entryPoint;
    unsigned flags = D3DXSHADER_OPTIMIZATION_LEVEL3;
    
    if (variation->type_ == VS)
    {
        entryPoint = "VS";
        if (!useSM3_)
            profile = "vs_2_0";
        else
            profile = "vs_3_0";
    }
    else
    {
        entryPoint = "PS";
        if (!useSM3_)
            profile = "ps_2_0";
        else
        {
            profile = "ps_3_0";
            flags |= D3DXSHADER_PREFER_FLOW_CONTROL;
        }
    }
    
    // Compile using D3DX
    HRESULT hr = D3DXCompileShader(hlslCode_.CString(), hlslCode_.Length(), &macros.Front(), &includeHandler, 
        entryPoint.CString(), profile.CString(), flags, &shaderCode, &errorMsgs, &constantTable);
    if (FAILED(hr))
    {
        variation->errorMsg_ = String((const char*)errorMsgs->GetBufferPointer(), errorMsgs->GetBufferSize());
        compileFailed_ = true;
    }
    else
    {
        // Print warnings if any
        if (errorMsgs && errorMsgs->GetBufferSize())
        {
            String warning((const char*)errorMsgs->GetBufferPointer(), errorMsgs->GetBufferSize());
            printf("WARNING: %s\n", warning.CString());
        }
        
        CopyStrippedCode(variation->byteCode_, shaderCode->GetBufferPointer(), shaderCode->GetBufferSize());
        
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
            unsigned reg = constantDesc.RegisterIndex;
            unsigned regCount = constantDesc.RegisterCount;
            
            // Check if the parameter is a constant or a texture sampler
            bool isSampler = (name[0] == 's');
            name = name.Substring(1);
            
            MutexLock lock(globalParamMutex_);
            
            if (isSampler)
            {
                // Skip if it's a G-buffer sampler
                if (name.Find("Buffer") == String::NPOS)
                {
                    Parameter newTextureUnit(name, reg, 1);
                    variation->textureUnits_.Insert(newTextureUnit);
                    textureUnits_.Insert(name);
                }
            }
            else
            {
                Parameter newParam(name, reg, regCount);
                variation->constants_.Insert(newParam);
                constants_.Insert(name);
            }
        }
    }
    
    if (shaderCode)
        shaderCode->Release();
    if (constantTable)
        constantTable->Release();
    if (errorMsgs)
        errorMsgs->Release();
}

void CopyStrippedCode(PODVector<unsigned char>& dest, void* src, unsigned srcSize)
{
    unsigned* srcWords = (unsigned*)src;
    unsigned srcWordSize = srcSize >> 2;
    
    dest.Clear();
    
    for (unsigned i = 0; i < srcWordSize; ++i)
    {
        unsigned opcode = srcWords[i] & 0xffff;
        unsigned paramLength = (srcWords[i] & 0x0f000000) >> 24;
        unsigned commentLength = srcWords[i] >> 16;
        
        // For now, skip comment only at fixed position to prevent false positives
        if (i == 1 && opcode == D3DSIO_COMMENT)
        {
            // Skip the comment
            i += commentLength;
        }
        else
        {
            // Not a comment, copy the data
            unsigned char* srcBytes = (unsigned char*)(srcWords + i);
            dest.Push(*srcBytes++);
            dest.Push(*srcBytes++);
            dest.Push(*srcBytes++);
            dest.Push(*srcBytes++);
        }
    }
}
