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

#include "Camera.h"
#include "Engine.h"
#include "Font.h"
#include "Game.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Input.h"
#include "Log.h"
#include "Model.h"
#include "PackageFile.h"
#include "Pipeline.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "StringUtils.h"
#include "VertexBuffer.h"

#include <angelscript.h>

#include "DebugNew.h"

Game::Game(const std::vector<std::string>& arguments) :
    mArguments(arguments)
{
    std::string userDir = getUserDocumentsDirectory();
    std::string applicationDir = userDir + "ScriptTest";
    
    // Test the "allowed path" feature. Access outside the working directory, and these paths, should cause an exception
    registerDirectory("Data");
    registerDirectory(getSystemFontDirectory());
    registerDirectory(applicationDir);
    
    createDirectory(applicationDir);
}

Game::~Game()
{
    // The scripts hold references to engine subsystems, not releasing them shows up as numerous memory leaks
    mScriptFile.reset();
    mCache->releaseResources(ShortStringHash("ScriptFile"), true);
}

void Game::run()
{
    init();
    
    if (!mRunFrameFunction)
        return;
    
    while (!mEngine->isExiting())
        mScriptFile->execute(mRunFrameFunction);
}

void Game::init()
{
    PROFILE(Game_Init);
    
    std::string logName = "ScriptTest.log";
    
    mEngine = new Engine(logName);
    
    // Add the resources as a package if available
    mCache = mEngine->getResourceCache();
    if (fileExists("Data.pak"))
        mCache->addPackageFile(new PackageFile("Data.pak"));
    
    // Force forward rendering
    mArguments.insert(mArguments.begin(), "-forward");
    
    mEngine->init("ScriptTest", mArguments);
    mEngine->createScriptEngine();
    
    mCache->addResourcePath(getSystemFontDirectory());
    
    Pipeline* pipeline = mEngine->getPipeline();
    for (unsigned i = 0; i < mArguments.size(); ++i)
    {
        if ((pipeline) && (toLower(mArguments[i]) == "-noshadows"))
            pipeline->setDrawShadows(false);
        if (toLower(mArguments[i]) == "-nolimit")
            mEngine->setMaxFps(0);
    }
    
    createSkyPlaneModel();
    
    // Execute the rest of initialization, including scene creation, in script
    mScriptFile = mCache->getResource<ScriptFile>("Scripts/NinjaSnowWar.as");
    mInitFunction = mScriptFile->getFunction("void init()");
    mRunFrameFunction = mScriptFile->getFunction("void runFrame()");
    
    mScriptFile->execute(mInitFunction);
}

void Game::createSkyPlaneModel()
{
    const float skyplanevertices[] = 
    {
        -1, 0, -1, 0, 0,
        1, 0, -1, 2, 0,
        1, 0, 1, 2, 2,
        -1, 0, 1, 0, 2
    };
    const unsigned short skyplaneindices[] =
    {
        0, 1, 3,
        1, 2, 3
    };
    
    Renderer* renderer = mEngine->getRenderer();
    
    SharedPtr<VertexBuffer> vb(new VertexBuffer(renderer));
    vb->setSize(4, MASK_POSITION | MASK_TEXCOORD1);
    vb->setData(skyplanevertices);
    
    SharedPtr<IndexBuffer> ib(new IndexBuffer(renderer));
    ib->setSize(6, false);
    ib->setData(skyplaneindices);
    
    SharedPtr<Geometry> geom(new Geometry());
    geom->setVertexBuffer(0, vb);
    geom->setIndexBuffer(ib);
    geom->setDrawRange(TRIANGLE_LIST, 0, ib->getIndexCount());
    
    SharedPtr<Model> model(new Model(renderer, "Models/CloudPlane.mdl"));
    model->setNumGeometries(1);
    model->setNumGeometryLodLevels(0, 1);
    model->setGeometry(0, 0, geom);
    model->setBoundingBox(BoundingBox(-1, 1));
    // Add the cloudplane model as a manual resource so it can be retrieved during savegame load
    mCache->addManualResource(model);
}
