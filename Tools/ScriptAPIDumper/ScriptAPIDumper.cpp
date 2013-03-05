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
#include "Log.h"
#include "Main.h"
#include "ProcessUtils.h"
#include "Script.h"
#include "ScriptAPI.h"

#include "DebugNew.h"

using namespace Urho3D;

int main(int argc, char** argv)
{
    #ifdef WIN32
    ParseArguments(GetCommandLineW());
    #else
    ParseArguments(argc, argv);
    #endif
    
    if (GetArguments().Size() < 1)
        ErrorExit("Usage: ScriptAPIDumper <output file>\n");

    SharedPtr<Context> context(new Context());
    SharedPtr<Engine> engine(new Engine(context));
    if (!engine->InitializeScripting())
        ErrorExit("Unabled to initialize script engine. The application will now exit.");
    Log* log;   // All subsystems are auto-disposed
    context->RegisterSubsystem(log = new Log(context));
    log->SetLevel(LOG_ERROR);
    log->SetQuiet(true);
    log->Open(GetArguments()[0]);
    context->GetSubsystem<Script>()->DumpAPI();
   
    return EXIT_SUCCESS;
}
