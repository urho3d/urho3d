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
#include "Engine.h"
#include "File.h"
#include "FileSystem.h"
#include "Log.h"
#include "ProcessUtils.h"
#include "ResourceCache.h"
#include "ScriptFile.h"

#ifdef WIN32
#include <windows.h>
#endif

#include "DebugNew.h"

using namespace Urho3D;

void CompileScript(Context* context, const String& fileName);

int main(int argc, char** argv)
{
    #ifdef WIN32
    const Vector<String>& arguments = ParseArguments(GetCommandLineW());
    #else
    const Vector<String>& arguments = ParseArguments(argc, argv);
    #endif
    
    String outputFile;
    if (arguments.Size() < 1)
        ErrorExit("Usage: ScriptCompiler <input file> [resource path for includes]");
    else
        outputFile = arguments[0];
    
    SharedPtr<Context> context(new Context());
    SharedPtr<Engine> engine(new Engine(context));
    context->RegisterSubsystem(new FileSystem(context));
    context->RegisterSubsystem(new ResourceCache(context));
    context->RegisterSubsystem(new Log(context));
    
    Log* log = context->GetSubsystem<Log>();
    log->SetLevel(LOG_WARNING);
    log->SetTimeStamp(false);
    
    if (!engine->InitializeScripting())
        ErrorExit("Unable to initialize script engine. The application will now exit.");
    
    String path, file, extension;
    SplitPath(outputFile, path, file, extension);
    
    ResourceCache* cache = context->GetSubsystem<ResourceCache>();
    
    // Add resource path to be able to resolve includes
    if (arguments.Size() > 1)
        cache->AddResourceDir(arguments[1]);
    else
        cache->AddResourceDir(cache->GetPreferredResourceDir(path));
    
    if (!file.StartsWith("*"))
        CompileScript(context, outputFile);
    else
    {
        Vector<String> scriptFiles;
        context->GetSubsystem<FileSystem>()->ScanDir(scriptFiles, path, file + extension, SCAN_FILES, false);
        for (unsigned i = 0; i < scriptFiles.Size(); ++i)
            CompileScript(context, path + scriptFiles[i]);
    }
    
    return EXIT_SUCCESS;
}

void CompileScript(Context* context, const String& fileName)
{
    PrintLine("Compiling script file " + fileName);
    
    File inFile(context, fileName, FILE_READ);
    if (!inFile.IsOpen())
        ErrorExit("Failed to open script file " + fileName);
    
    ScriptFile script(context);
    if (!script.Load(inFile))
        ErrorExit("Failed to compile script file " + fileName + ": " + context->GetSubsystem<Log>()->GetLastMessage());
    
    String outFileName = ReplaceExtension(fileName, ".asc");
    File outFile(context, outFileName, FILE_WRITE);
    if (!outFile.IsOpen())
        ErrorExit("Failed to open output file " + fileName);
    
    script.SaveByteCode(outFile);
}
