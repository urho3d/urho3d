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
#include "Scene.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "StringUtils.h"

#include "DebugNew.h"

Application::Application()
{
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
    // Create application directory
    std::string applicationDir = getUserDocumentsDirectory() + "Urho3D";
    createDirectory(applicationDir);
    
    // Parse scene or script file name from the command line
    const std::vector<std::string>& arguments = getArguments();
    std::string fullName, pathName, fileName, extension;
    if ((arguments.size()) && (arguments[0][0] != '-'))
        fullName = replace(arguments[0], '\\', '/');
    if (fullName.empty())
        EXCEPTION("Usage: Urho3D <scriptfile | scenefile> [options]\n\n"
            "Either a script file or a scene file can be specified. The script file should implement the function void start(), "
            "which should in turn subscribe to all necessary events, such as the application update. If a scene is loaded, it "
            "should contain script objects to implement the application logic. Refer to the readme for the command line options.");
    splitPath(fullName, pathName, fileName, extension);
    
    // Instantiate the engine
    mEngine = new Engine();
    
    // Try to open the file before setting screen mode
    // Check first the resource cache
    SharedPtr<File> file;
    mCache = mEngine->getResourceCache();
    if (mCache->exists(fullName))
        file = mCache->getFile(fullName);
    // If not found, open using the full filename, and add the path as a resource directory
    else
    {
        file = new File(fullName);
        if (!pathName.empty())
            mCache->addResourcePath(pathName);
        else
            mCache->addResourcePath(getCurrentDirectory());
    }
    
    // Initialize engine & scripting
    mEngine->init(arguments);
    mEngine->createScriptEngine();
    
    // Script mode: execute the rest of initialization, including scene creation, in script
    if ((extension != ".xml") && (extension != ".scn"))
    {
        mScriptFile = new ScriptFile(mEngine->getScriptEngine(), fileName + extension);
        mScriptFile->load(*file, mCache);
        if (!mScriptFile->execute("void start()"))
            EXCEPTION("Failed to execute the start() function");
    }
    // Scene mode: create and load a scene, then let it run
    else
    {
        mScene = mEngine->createScene("Urho3D");
        if (extension == ".xml")
            mScene->loadXML(*file);
        else
            mScene->load(*file);
    }
    
    // Run until exited
    while (!mEngine->isExiting())
        mEngine->runFrame();
}
