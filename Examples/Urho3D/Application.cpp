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

#include "Application.h"
#include "Engine.h"
#include "Exception.h"
#include "Font.h"
#include "Input.h"
#include "Log.h"
#include "PackageFile.h"
#include "ProcessUtils.h"
#include "ResourceCache.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "StringUtils.h"

#include "DebugNew.h"

Application::Application()
{
    std::string userDir = getUserDocumentsDirectory();
    std::string applicationDir = userDir + "Urho3D";
    
    createDirectory(applicationDir);
}

Application::~Application()
{
    // The scripts possibly hold references to engine subsystems, not releasing them shows up as numerous memory leaks
    if (mEngine)
    {
        mScriptFile.reset();
        mCache->releaseResources(ShortStringHash("ScriptFile"), true);
    }
}

void Application::run()
{
    init();
    
    while (!mEngine->isExiting())
    {
        if (!mScriptFile->execute("void runFrame()"))
            EXCEPTION("Failed to execute the runFrame() function");
        
        // Script garbage collection
        mEngine->getScriptEngine()->garbageCollect(false);
    }
}

void Application::init()
{
    const std::vector<std::string>& arguments = getArguments();
    std::string scriptFileName;
    if ((arguments.size()) && (arguments[0][0] != '-'))
        scriptFileName = replace(arguments[0], '\\', '/');
    if (scriptFileName.empty())
        EXCEPTION("Usage: Urho3D <scriptfile> [options]\n\n"
            "The script file should implement the functions void start() and void runFrame(). See the readme for options.\n");
    
    mEngine = new Engine();
    
    // Add resources
    mCache = mEngine->getResourceCache();
    if (fileExists("CoreData.pak"))
        mCache->addPackageFile(new PackageFile("CoreData.pak"));
    if (fileExists("Data.pak"))
        mCache->addPackageFile(new PackageFile("Data.pak"));
    else
        mCache->addResourcePath("Data");
    
    mCache->addResourcePath(getSystemFontDirectory());
    
    mEngine->init(arguments);
    mEngine->createScriptEngine();
    
    // Execute the rest of initialization, including scene creation, in script
    mScriptFile = mCache->getResource<ScriptFile>(scriptFileName);
    if (!mScriptFile->execute("void start()"))
        EXCEPTION("Failed to execute the start() function");
}
