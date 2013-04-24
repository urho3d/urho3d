//
// Copyright (c) 2008-2013 the Urho3D project.
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
#include "GraphicsDefs.h"
#include "List.h"
#include "Mutex.h"
#include "ProcessUtils.h"
#include "ShaderParser.h"
#include "StringUtils.h"
#include "Thread.h"
#include "XMLFile.h"

#include <cstdio>
#include <cstring>

#include <windows.h>
#include <d3dcompiler.h>
#include <mojoshader.h>

#include "DebugNew.h"

using namespace Urho3D;

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

struct CompiledVariation
{
    ShaderType type_;
    String name_;
    String outFileName_;
    Vector<String> defines_;
    Vector<String> defineValues_;
    PODVector<unsigned char> byteCode_;
    Vector<Parameter> constants_;
    Vector<Parameter> textureUnits_;
    String errorMsg_;
};

SharedPtr<Context> context_(new Context());
SharedPtr<FileSystem> fileSystem_(new FileSystem(context_));
String inDir_;
String outDir_;
Vector<String> defines_;
Vector<String> defineValues_;
String variationName_;
volatile bool compileFailed_ = false;
bool useSM3_ = false;
bool compileVariation_ = false;
bool compileVS_ = true;
bool compilePS_ = true;

List<CompiledVariation> variations_;
List<CompiledVariation*> workList_;
Mutex workMutex_;
String hlslCode_;

int main(int argc, char** argv);
void Run(const Vector<String>& arguments);
void CompileShader(const String& fileName);
void CompileVariation(CompiledVariation* variation);
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
                }
            }
            if (!workItem)
                return;
            
            // If compile(s) failed, just empty the list, but do not compile more
            if (!compileFailed_)
                CompileVariation(workItem);
        }
    }
};

class IncludeHandler : public ID3DInclude
{
public:
    STDMETHOD(Open)(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
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
    
    #ifdef WIN32
    arguments = ParseArguments(GetCommandLineW());
    #else
    arguments = ParseArguments(argc, argv);
    #endif
    
    Run(arguments);
    return 0;
}

void Run(const Vector<String>& arguments)
{
    if (arguments.Size() < 1)
    {
        ErrorExit(
            "Usage: ShaderCompiler <definitionfile> [outputpath] [options]\n\n"
            "Options:\n"
            "-tVS|PS Compile only vertex or pixel shaders, by default compile both\n"
            "-vX     Compile only the shader variation X\n"
            "-dX     Add a define. Add SM3 to compile for Shader Model 3\n\n"
            "If output path is not specified, shader binaries will be output into the same\n"
            "directory as the definition file. Specify a wildcard to compile multiple\n"
            "shaders."
        );
    }
    
    String path, file, extension;
    SplitPath(arguments[0], path, file, extension);
    inDir_ = AddTrailingSlash(path);
    if (arguments.Size() > 1 && arguments[1][0] != '-')
        outDir_ = AddTrailingSlash(arguments[1]);
    else
        outDir_ = inDir_;
    
    for (unsigned i = 1; i < arguments.Size(); ++i)
    {
        if (arguments[i][0] == '-' && arguments[i].Length() > 1)
        {
            char option = arguments[i][1];
            String arg = arguments[i].Substring(2);
            
            switch (option)
            {
            case 'd':
                {
                    Vector<String> nameAndValue = arg.Split('=');
                    if (nameAndValue.Size() == 2)
                    {
                        defines_.Push(nameAndValue[0]);
                        defineValues_.Push(nameAndValue[1]);
                        if (nameAndValue[0] == "SM3" && ToInt(nameAndValue[1]) > 0)
                            useSM3_ = true;
                    }
                    else
                    {
                        defines_.Push(arg);
                        defineValues_.Push("1");
                        if (arg == "SM3")
                            useSM3_ = true;
                    }
                }
                break;
                
            case 't':
                if (arg.ToLower() == "vs")
                {
                    compileVS_ = true;
                    compilePS_ = false;
                }
                else if (arg.ToLower() == "ps")
                {
                    compileVS_ = false;
                    compilePS_ = true;
                }
                break;
                
            case 'v':
                compileVariation_ = true;
                variationName_ = arg;
                break;
            }
        }
    }
    
    if (!file.StartsWith("*"))
        CompileShader(arguments[0]);
    else
    {
        Vector<String> shaderFiles;
        fileSystem_->ScanDir(shaderFiles, inDir_, file + extension, SCAN_FILES, false);
        for (unsigned i = 0; i < shaderFiles.Size(); ++i)
            CompileShader(inDir_ + shaderFiles[i]);
    }
}

void CompileShader(const String& fileName)
{
    String file = GetFileName(fileName);
    
    XMLFile doc(context_);
    File source(context_);
    source.Open(fileName);
    if (!doc.Load(source))
        ErrorExit("Could not open input file " + fileName);
    
    XMLElement shaders = doc.GetRoot("shaders");
    if (!shaders)
        ErrorExit("No shaders element in " + source.GetName());
    
    if (compileVS_)
    {
        ShaderParser vsParser;
        if (!vsParser.Parse(VS, shaders, defines_, defineValues_))
            ErrorExit("VS: " + vsParser.GetErrorMessage());
        
        const HashMap<String, unsigned>& combinations = vsParser.GetAllCombinations();
        for (HashMap<String, unsigned>::ConstIterator i = combinations.Begin(); i != combinations.End(); ++i)
        {
            if (!compileVariation_ || i->first_ == variationName_)
            {
                ShaderCombination src = vsParser.GetCombination(i->first_);
                CompiledVariation compile;
                
                compile.type_ = VS;
                compile.name_ = file;
                compile.outFileName_ = outDir_ + file;
                if (!src.name_.Empty())
                {
                    compile.name_ += "_" + src.name_;
                    compile.outFileName_ += "_" + src.name_;
                }
                compile.outFileName_ += useSM3_ ? ".vs3" : ".vs2";
                compile.defines_ = src.defines_;
                compile.defineValues_ = src.defineValues_;
                
                variations_.Push(compile);
                workList_.Push(&variations_.Back());
            }
        }
    }
    
    if (compilePS_)
    {
        ShaderParser psParser;
        if (!psParser.Parse(PS, shaders, defines_, defineValues_))
            ErrorExit("PS: " + psParser.GetErrorMessage());
        
        const HashMap<String, unsigned>& combinations = psParser.GetAllCombinations();
        for (HashMap<String, unsigned>::ConstIterator i = combinations.Begin(); i != combinations.End(); ++i)
        {
            if (!compileVariation_ || i->first_ == variationName_)
            {
                ShaderCombination src = psParser.GetCombination(i->first_);
                CompiledVariation compile;
                
                compile.type_ = PS;
                compile.name_ = file;
                compile.outFileName_ = outDir_ + file;
                if (!src.name_.Empty())
                {
                    compile.name_ += "_" + src.name_;
                    compile.outFileName_ += "_" + src.name_;
                }
                compile.outFileName_ += useSM3_ ? ".ps3" : ".ps2";
                compile.defines_ = src.defines_;
                compile.defineValues_ = src.defineValues_;
                
                variations_.Push(compile);
                workList_.Push(&variations_.Back());
            }
        }
    }
    
    if (variations_.Empty())
    {
        PrintLine("No variations to compile");
        return;
    }
    
    // Load the shader source code
    {
        String inputFileName = inDir_ + file + ".hlsl";
        File hlslFile(context_, inputFileName);
        if (!hlslFile.IsOpen())
            ErrorExit("Could not open input file " + inputFileName);
        
        hlslCode_.Clear();
        while (!hlslFile.IsEof())
            hlslCode_ += hlslFile.ReadLine() + "\n";
    }
    
    if (!compileVariation_)
    {
        // Create and start worker threads. Use all logical CPUs except one to not lock up the computer completely
        unsigned numWorkerThreads = GetNumLogicalCPUs() - 1;
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
    }
    else
    {
        WorkerThread dummyThread;
        dummyThread.ThreadFunction();
    }
    
    // Check that all shaders compiled
    for (List<CompiledVariation>::Iterator i = variations_.Begin(); i != variations_.End(); ++i)
    {
        if (!i->errorMsg_.Empty())
        {
            if (i->type_ == VS)
                ErrorExit("Failed to compile vertex shader " + i->name_ + ": " + i->errorMsg_);
            else
                ErrorExit("Failed to compile pixel shader " + i->name_ + ": " + i->errorMsg_);
        }
    }
}

void CompileVariation(CompiledVariation* variation)
{
    IncludeHandler includeHandler;
    PODVector<D3D_SHADER_MACRO> macros;
    
    // Insert variation-specific and global defines
    for (unsigned i = 0; i < variation->defines_.Size(); ++i)
    {
        D3D_SHADER_MACRO macro;
        macro.Name = variation->defines_[i].CString();
        macro.Definition = variation->defineValues_[i].CString();
        macros.Push(macro);
    }
    for (unsigned i = 0; i < defines_.Size(); ++i)
    {
        D3D_SHADER_MACRO macro;
        macro.Name = defines_[i].CString();
        macro.Definition = defineValues_[i].CString();
        macros.Push(macro);
    }
    
    D3D_SHADER_MACRO endMacro;
    endMacro.Name = 0;
    endMacro.Definition = 0;
    macros.Push(endMacro);
    
    LPD3DBLOB shaderCode = NULL;
    LPD3DBLOB errorMsgs = NULL;
    
    // Set the profile, entrypoint and flags according to the shader being compiled
    String profile;
    String entryPoint;
    unsigned flags = D3DCOMPILE_OPTIMIZATION_LEVEL3;
    
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
            flags |= D3DCOMPILE_PREFER_FLOW_CONTROL;
        }
    }
    
    // Compile using D3DCompiler
    HRESULT hr = D3DCompile(hlslCode_.CString(), hlslCode_.Length(), NULL, &macros.Front(), &includeHandler,
        entryPoint.CString(), profile.CString(), flags, 0, &shaderCode, &errorMsgs);

    if (FAILED(hr))
    {
        variation->errorMsg_ = String((const char*)errorMsgs->GetBufferPointer(), errorMsgs->GetBufferSize());
        compileFailed_ = true;
    }
    else
    {
        BYTE const *const bufData = static_cast<BYTE *>(shaderCode->GetBufferPointer());
        SIZE_T const bufSize = shaderCode->GetBufferSize();
        MOJOSHADER_parseData const *parseData = MOJOSHADER_parse("bytecode", bufData, bufSize, NULL, 0, NULL, 0, NULL, NULL, NULL);

        CopyStrippedCode(variation->byteCode_, shaderCode->GetBufferPointer(), shaderCode->GetBufferSize());
        
        if (!variation->name_.Empty())
            PrintLine("Compiled shader variation " + variation->name_ + ", code size " + String(variation->byteCode_.Size()));
        else
            PrintLine("Compiled base shader variation, code size " + String(variation->byteCode_.Size()));
            
        // Print warnings if any
        if (errorMsgs && errorMsgs->GetBufferSize())
        {
            String warning((const char*)errorMsgs->GetBufferPointer(), errorMsgs->GetBufferSize());
            PrintLine("WARNING: " + warning);
        }

        for(int i = 0; i < parseData->symbol_count; i++)
        {
            MOJOSHADER_symbol const& symbol = parseData->symbols[i];

            String name(symbol.name);
            unsigned const reg = symbol.register_index;
            unsigned const regCount = symbol.register_count;

            // Check if the parameter is a constant or a texture sampler
            bool const isSampler = (name[0] == 's');
            name = name.Substring(1);
            
            if (isSampler)
            {
                // Skip if it's a G-buffer sampler
                if (!name.Contains("Buffer"))
                {
                    Parameter newTextureUnit(name, reg, 1);
                    variation->textureUnits_.Push(newTextureUnit);
                }
            }
            else
            {
                Parameter newParam(name, reg, regCount);
                variation->constants_.Push(newParam);
            }
        }

        MOJOSHADER_freeParseData(parseData);

        File outFile(context_);
        if (!outFile.Open(variation->outFileName_, FILE_WRITE))
        {
            variation->errorMsg_ = "Could not open output file " + variation->outFileName_;
            compileFailed_ = true;
        }
        else
        {
            outFile.WriteFileID("USHD");
            outFile.WriteShort((unsigned short)variation->type_);
            outFile.WriteShort(useSM3_ ? 3 : 2);
            
            outFile.WriteUInt(variation->constants_.Size());
            for (unsigned i = 0; i < variation->constants_.Size(); ++i)
            {
                outFile.WriteString(variation->constants_[i].name_);
                outFile.WriteUByte(variation->constants_[i].register_);
                outFile.WriteUByte(variation->constants_[i].regCount_);
            }
            
            outFile.WriteUInt(variation->textureUnits_.Size());
            for (unsigned i = 0; i < variation->textureUnits_.Size(); ++i)
            {
                outFile.WriteString(variation->textureUnits_[i].name_);
                outFile.WriteUByte(variation->textureUnits_[i].register_);
            }
            
            unsigned dataSize = variation->byteCode_.Size();
            outFile.WriteUInt(dataSize);
            if (dataSize)
                outFile.Write(&variation->byteCode_[0], dataSize);
        }
    }
    
    if (shaderCode)
        shaderCode->Release();
    if (errorMsgs)
        errorMsgs->Release();
}

void CopyStrippedCode(PODVector<unsigned char>& dest, void* src, unsigned srcSize)
{
    unsigned const D3DSIO_COMMENT = 0xFFFE;
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
