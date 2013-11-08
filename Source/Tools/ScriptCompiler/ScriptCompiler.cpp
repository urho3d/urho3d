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
#include "Script.h"
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

    bool dumpApiMode = false;
    String outputFile;

    if (arguments.Size() < 1)
        ErrorExit("Usage: ScriptCompiler <input file> [resource path for includes]\n"
                  "       ScriptCompiler -dumpapi <Oxygen output file> [C header output file]");
    else
    {
        if (arguments[0] != "-dumpapi")
            outputFile = arguments[0];
        else
        {
            dumpApiMode = true;
            if (arguments.Size() > 1)
                outputFile = arguments[1];
        }
    }

    SharedPtr<Context> context(new Context());

    // Note: creating the Engine registers most subsystems which don't require engine initialization
    SharedPtr<Engine> engine(new Engine(context));
    context->RegisterSubsystem(new Script(context));

    Log* log = context->GetSubsystem<Log>();
    // Register Log subsystem manually if compiled without logging support
    if (!log)
    {
        context->RegisterSubsystem(new Log(context));
        log = context->GetSubsystem<Log>();
    }

    log->SetLevel(LOG_WARNING);
    log->SetTimeStamp(false);

    if (!dumpApiMode)
    {
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
    }
    else
    {
        if (!outputFile.Empty())
        {
            log->SetQuiet(true);
            log->Open(outputFile);
        }
        // If without output file, dump to stdout instead
        context->GetSubsystem<Script>()->DumpAPI(DOXYGEN);

        // Only dump API as C Header when an output file name is explicitly given
        if (arguments.Size() > 2)
        {
            outputFile = arguments[2];
            log->Open(outputFile);
            context->GetSubsystem<Script>()->DumpAPI(C_HEADER);
        }
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
        ErrorExit();

    String outFileName = ReplaceExtension(fileName, ".asc");
    File outFile(context, outFileName, FILE_WRITE);
    if (!outFile.IsOpen())
        ErrorExit("Failed to open output file " + fileName);

    script.SaveByteCode(outFile);
}
