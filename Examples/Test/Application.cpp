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

#include "Precompiled.h"
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationState.h"
#include "Audio.h"
#include "Application.h"
#include "BillboardSet.h"
#include "Button.h"
#include "CollisionShape.h"
#include "Cursor.h"
#include "CustomObject.h"
#include "DebugHud.h"
#include "DebugRenderer.h"
#include "Engine.h"
#include "EngineEvents.h"
#include "Exception.h"
#include "File.h"
#include "Font.h"
#include "Geometry.h"
#include "IndexBuffer.h"
#include "Input.h"
#include "InstancedModel.h"
#include "Joint.h"
#include "Light.h"
#include "Log.h"
#include "Material.h"
#include "Mod.h"
#include "OcclusionBuffer.h"
#include "Octree.h"
#include "OctreeQuery.h"
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#include "Pipeline.h"
#include "ParticleEmitter.h"
#include "Profiler.h"
#include "Renderer.h"
#include "RendererImpl.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "Scene.h"
#include "Skybox.h"
#include "StaticModel.h"
#include "Text.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "UI.h"
#include "UIEvents.h"
#include "VertexBuffer.h"
#include "Window.h"
#include "XM.h"
#include "XMLFile.h"
#include "Zone.h"

#include "DebugNew.h"

void calculateTangents(float* vertexData, unsigned vertexCount, const unsigned short* indexData, unsigned indexCount);

float vertexData[] =
{
    // Side 1
    -1, 1, -1,   0, 0, -1,  0, 0,  0, 0, 0, 0,
    1, 1, -1,    0, 0, -1,  1, 0,  0, 0, 0, 0,
    1, -1, -1,   0, 0, -1,  1, 1,  0, 0, 0, 0,
    -1, -1, -1,  0, 0, -1,  0, 1,  0, 0, 0, 0,

    // Side 2
    1, 1, -1,    1, 0, 0,   0, 0,  0, 0, 0, 0,
    1, 1, 1,     1, 0, 0,   1, 0,  0, 0, 0, 0,
    1, -1, 1,    1, 0, 0,   1, 1,  0, 0, 0, 0,
    1, -1, -1,   1, 0, 0,   0, 1,  0, 0, 0, 0,

    // Side 3
    1, 1, 1,     0, 0, 1,   0, 0,  0, 0, 0, 0,
    -1, 1, 1,    0, 0, 1,   1, 0,  0, 0, 0, 0,
    -1, -1, 1,   0, 0, 1,   1, 1,  0, 0, 0, 0,
    1, -1, 1,    0, 0, 1,   0, 1,  0, 0, 0, 0,
    
    // Side 4
    -1, 1, 1,    -1, 0, 0,  0, 0,  0, 0, 0, 0,
    -1, 1, -1,   -1, 0, 0,  1, 0,  0, 0, 0, 0,
    -1, -1, -1,  -1, 0, 0,  1, 1,  0, 0, 0, 0,
    -1, -1, 1,   -1, 0, 0,  0, 1,  0, 0, 0, 0,
    
    // Side 5
    -1, 1, 1,    0, 1, 0,   0, 0,  0, 0, 0, 0,
    1, 1, 1,     0, 1, 0,   1, 0,  0, 0, 0, 0,
    1, 1, -1,    0, 1, 0,   1, 1,  0, 0, 0, 0,
    -1, 1, -1,   0, 1, 0,   0, 1,  0, 0, 0, 0,
    
    // Side 6
    -1, -1, -1,  0, -1, 0,  0, 0,  0, 0, 0, 0,
    1, -1, -1,   0, -1, 0,  1, 0,  0, 0, 0, 0,
    1, -1, 1,    0, -1, 0,  1, 1,  0, 0, 0, 0,
    -1, -1, 1,   0, -1, 0,  0, 1,  0, 0, 0, 0
};

const unsigned short indexData[] =
{
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    8, 9, 10,
    10, 11, 8,
    12, 13, 14,
    14, 15, 12,
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20
};

float objectangle = 0;
float yaw = 0;
float pitch = 0;
bool paused = true;
int texturequality = 2;
int materialquality = 2;
int fallbacklevel = 0;
int shadowmapsize = 1024;
bool hiresshadowmap = false;
int texturefilter = 2;
bool usespecular = true;
int drawdebug = 0;
bool drawshadows = true;
bool attach = true;
bool useocclusion = true;
bool shadowfocus = true;

static const int NUM_OBJECTS = 250;
static const int NUM_LIGHTS = 20;
static const int NUM_INSTANCENODES = 20;
static const int NUM_INSTANCES = 50;
static const int NUM_BILLBOARDNODES = 20;
static const int NUM_BILLBOARDS = 15;

Application::Application(const std::vector<std::string>& arguments) :
    mArguments(arguments)
{
    subscribeToEvent(EVENT_UPDATE, EVENT_HANDLER(Application, handleUpdate));
    subscribeToEvent(EVENT_POSTRENDERUPDATE, EVENT_HANDLER(Application, handlePostRenderUpdate));
    subscribeToEvent(EVENT_MOUSEMOVE, EVENT_HANDLER(Application, handleMouseMove));
    subscribeToEvent(EVENT_MOUSEBUTTONDOWN, EVENT_HANDLER(Application, handleMouseButtonDown));
    subscribeToEvent(EVENT_MOUSEBUTTONUP, EVENT_HANDLER(Application, handleMouseButtonUp));
}

Application::~Application()
{
    if (mEngine)
    {
        mEngine->dumpResources();
        mEngine->dumpProfilingData();
    }
}

void Application::run()
{
    init();
    
    while (!mEngine->isExiting())
        mEngine->runFrame(mScene, mCameraEntity->getComponent<Camera>());
}

void Application::init()
{
    mEngine = new Engine("Test.log");
    mEngine->init("Urho3D Test", mArguments);
    
    PROFILE(App_Init);
    
    mCache = mEngine->getResourceCache();
    mCache->addResourcePath(getSystemFontDirectory());
    
    Renderer* renderer = mEngine->getRenderer();
    UI* ui = mEngine->getUI();
    UIElement* uiRoot = ui->getRootElement();
    
    XMLFile* uiSetup = mCache->getResource<XMLFile>("UI/UI.xml");
    
    SharedPtr<Cursor> cursor(new Cursor("Cursor"));
    cursor->loadParameters(uiSetup, "Cursor", mCache);
    cursor->setPosition(renderer->getWidth() / 2, renderer->getHeight() / 2);
    ui->setCursor(cursor);
    
    mScene = mEngine->createScene();
    PhysicsWorld* world = mScene->getExtension<PhysicsWorld>();
    world->setGravity(Vector3(0.0f, -9.81f, 0.0f));
    world->setFps(100);
    world->setLinearRestThreshold(0.1f);
    world->setAngularRestThreshold(0.1f);
    world->setContactSurfaceLayer(0.001f);
    
    DebugHud* debugHud = mEngine->createDebugHud();
    debugHud->setFont(mCache->getResource<Font>("cour.ttf"), 12);
    debugHud->setMode(DEBUGHUD_SHOW_STATS | DEBUGHUD_SHOW_MODE);
    
    mCameraEntity = mScene->createEntity();
    Camera* camera = mCameraEntity->createComponent<Camera>();
    camera->setPosition(Vector3(-50.0f, 2.0f, -50.0f));
    camera->setAspectRatio((float)renderer->getWidth() / (float)renderer->getHeight());
    
    calculateTangents(vertexData, 24, indexData, 36);
    
    SharedPtr<VertexBuffer> vb(new VertexBuffer(renderer, false));
    vb->setSize(24, MASK_POSITION | MASK_NORMAL | MASK_TEXCOORD1 | MASK_TANGENT);
    vb->setData(vertexData);
    
    SharedPtr<IndexBuffer> ib(new IndexBuffer(renderer, false));
    ib->setSize(36, false);
    ib->setData(indexData);
    
    SharedPtr<Geometry> g(new Geometry());
    g->setVertexBuffer(0, vb);
    g->setIndexBuffer(ib);
    g->setDrawRange(TRIANGLE_LIST, 0, ib->getIndexCount());
    
    SharedPtr<Model> box(new Model(renderer, "Models/Box.mdl"));
    box->setNumGeometries(1);
    box->setNumGeometryLodLevels(0, 1);
    box->setGeometry(0, 0, g);
    box->setBoundingBox(BoundingBox(-1.0f, 1.0f));
    mCache->addManualResource(box);
    
    createScene();
    
    Entity* sun = mScene->createEntity();
    Light* sunLight = sun->createComponent<Light>();
    sunLight->setLightType(LIGHT_DIRECTIONAL);
    sunLight->setDirection(Vector3(0.5f, -1.0f, 0.5f));
    sunLight->setColor(Color(0.2f, 0.2f, 0.2f));
    sunLight->setSpecularIntensity(1.0);
    //sunLight->setCastShadows(true);
    //sunLight->setShadowCascade(CascadeParameters(3, 0.95f, 0.2f, 500.0f));
    
    Light* cameraLight = mCameraEntity->createComponent<Light>();
    cameraLight->setLightType(LIGHT_SPOT);
    cameraLight->setDirection(Vector3(0.0f, 0.0f, 1.0f));
    cameraLight->setRange(50.0f);
    cameraLight->setColor(Color(2.0f, 2.0f, 2.0f));
    cameraLight->setSpecularIntensity(2.0f);
    cameraLight->setCastShadows(true);
    cameraLight->setShadowResolution(0.5f);
    cameraLight->setShadowFocus(FocusParameters(false, false, false, 0.5f, 3.0f));
    cameraLight->setRampTexture(mCache->getResource<Texture2D>("Textures/RampWide.png"));
    cameraLight->setSpotTexture(mCache->getResource<Texture2D>("Textures/SpotWide.png"));
    camera->addChild(cameraLight);
}

void Application::createScene()
{
    PROFILE(App_CreateScene);
    
    Octree* octree = mScene->getExtension<Octree>();
    PhysicsWorld* world = mScene->getExtension<PhysicsWorld>();
    
    // Create a zone to control the ambient lighting
    Zone* zone = new Zone(octree);
    zone->setBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->setAmbientColor(Color(0.1f, 0.1f, 0.1f));
    Entity* newEntity = mScene->createEntity();
    newEntity->addComponent(zone);
    
    // Create the "floor"
    for (int y = -5; y <= 5; y++)
    {
        for (int x = -5; x <= 5; x++)
        {
            RigidBody* body = new RigidBody(world);
            body->setPosition(Vector3(x * 20.5f, -0.5f, y * 20.5f));
            body->setScale(Vector3(10.0f, 0.5f, 10.0f));
            body->setCollisionShape(mCache->getResource<CollisionShape>("Physics/Box.xml"));
            body->setCollisionGroup(2);
            body->setCollisionMask(1);
            
            StaticModel* object = new StaticModel(octree);
            object->setModel(mCache->getResource<Model>("Models/Box.mdl"));
            object->setMaterial(mCache->getResource<Material>("Materials/Test.xml"));
            body->addChild(object);
            
            Entity* newEntity = mScene->createEntity();
            newEntity->addComponent(body);
            newEntity->addComponent(object);
        }
    }
    
    // Create 2 occluder walls
    for (int x = 0; x < 2; x++)
    {
        RigidBody* body = new RigidBody(world);
        body->setPosition(Vector3(0.0f, 5.0f, 0.0f));
        body->setRotation(Quaternion(x * 90.0f, Vector3::sUp));
        body->setScale(Vector3(112.0f, 5.0f, 0.5f));
        body->setCollisionShape(mCache->getResource<CollisionShape>("Physics/Box.xml"));
        body->setCollisionGroup(2);
        body->setCollisionMask(1);
        
        StaticModel* object = new StaticModel(octree);
        object->setModel(mCache->getResource<Model>("Models/Box.mdl"));
        object->setMaterial(mCache->getResource<Material>("Materials/Test.xml"));
        object->setCastShadows(true);
        object->setOccluder(true);
        body->addChild(object);
        
        Entity* newEntity = mScene->createEntity();
        newEntity->addComponent(body);
        newEntity->addComponent(object);
    }
    
    // Create static mushroom with physics
    {
        RigidBody* body = new RigidBody(world);
        body->setPosition(Vector3(50.0f, 0.0f, 50.0f));
        body->setScale(10.0f);
        body->setCollisionShape(mCache->getResource<CollisionShape>("Physics/Mushroom.xml"));
        body->setCollisionGroup(2);
        body->setCollisionMask(1);
        
        StaticModel* object = new StaticModel(octree);
        object->setModel(mCache->getResource<Model>("Models/Mushroom.mdl"));
        object->setMaterial(mCache->getResource<Material>("Materials/MushroomStatic.xml"));
        object->setCastShadows(true);
        object->setOccluder(true);
        body->addChild(object);
        
        Entity* newEntity = mScene->createEntity();
        newEntity->addComponent(body);
        newEntity->addComponent(object);
    }
    
    // Create instanced mushrooms
    for (unsigned j = 0; j < NUM_INSTANCENODES; ++j)
    {
        InstancedModel* instanced = new InstancedModel(octree);
        instanced->setModel(mCache->getResource<Model>("Models/Mushroom.mdl"));
        instanced->setMaterial(mCache->getResource<Material>("Materials/MushroomInstanced.xml"));
        instanced->setPosition(Vector3(random() * 160.0f - 80.0f, 0.0f, random() * 160.0f - 80.0f));
        instanced->setCastShadows(true);
        instanced->setNumInstances(50);
        
        std::vector<Instance>& instances = instanced->getInstances();
        
        for (unsigned i = 0; i < NUM_INSTANCES; ++i)
        {
            Vector3 position(random() * 20.0f - 10.0f, 0.0f, random() * 20.0f - 10.0f);
            float angle = random() * 360.0f;
            float size = 1.0f + random() * 2.0f;
            
            instances[i].mPosition = position;
            instances[i].mRotation = Quaternion(angle, Vector3::sUp);
            instances[i].mScale = Vector3(size, size, size);
        }
        
        instanced->updated();
        
        Entity* newEntity = mScene->createEntity();
        newEntity->addComponent(instanced);
    }
    
    // Create animated models
    for (unsigned i = 0; i < NUM_OBJECTS; ++i)
    {
        AnimatedModel* object = new AnimatedModel(octree);
        
        Vector3 position(random() * 180.0f - 90.0f, 0.0f, random() * 180.0f - 90.0f);
        float angle = random() * 360.0f;
        
        object->setPosition(position);
        object->setRotation(Quaternion(angle, Vector3::sUp));
        object->setCastShadows(true);
        object->setScale(1.0f + random() * 0.25f);
        object->setModel(mCache->getResource<Model>("Models/Jack.mdl"));
        object->setMaterial(mCache->getResource<Material>("Materials/Jack.xml"));
        object->setShadowDistance(200.0f);
        object->setDrawDistance(300.0f);
        
        AnimationState* anim = object->addAnimationState(mCache->getResource<Animation>("Models/Jack_Walk.ani"));
        if (anim)
        {
            anim->setLooped(true);
            anim->setWeight(1.0f);
        }
        
        Entity* newEntity = mScene->createEntity();
        newEntity->addComponent(object);
        mAnimatingObjects.push_back(newEntity);
    }
    
    // Create floating smoke clouds
    for (unsigned b = 0; b < NUM_BILLBOARDNODES; ++b)
    {
        BillboardSet* billboard = new BillboardSet(octree);
        billboard->setNumBillboards(NUM_BILLBOARDS);
        billboard->setPosition(Vector3(random() * 200.0f - 100.0f, random() * 15.0f + 5.0f, random() * 200.0f - 100.0f));
        billboard->setMaterial(mCache->getResource<Material>("Materials/LitSmoke.xml"));
        billboard->setBillboardsSorted(true);
        
        std::vector<Billboard>& bb = billboard->getBillboards();
        
        for (unsigned i = 0; i < NUM_BILLBOARDS; ++i)
        {
            bb[i].mPosition = Vector3(random() * 15.0f - 7.5f, random() * 8.0f - 4.0f, random() * 15.0f - 7.5f);
            bb[i].mSize = Vector2(random() * 2.0f + 3.0f, random() * 2.0f + 3.0f);
            bb[i].mRotation = random() * 360.0f;
            bb[i].mEnabled = true;
        }
        
        billboard->updated();
        
        Entity* newEntity = mScene->createEntity();
        newEntity->addComponent(billboard);
        mBillboards.push_back(newEntity);
    }
    
    // Create lights
    for (unsigned i = 0; i < NUM_LIGHTS; ++i)
    {
        Light* light = new Light(octree);
        
        Vector3 position(
            random() * 150.0f - 75.0f,
            random() * 30.0f + 30.0f,
            random() * 150.0f - 75.0f
        );
        
        Color color(
            (rand() & 1) * 0.5f + 0.5f,
            (rand() & 1) * 0.5f + 0.5f,
            (rand() & 1) * 0.5f + 0.5f
        );
        
        if ((color.mR == 0.5f) && (color.mG == 0.5f) && (color.mB == 0.5f))
            color = Color(1.0f, 1.0f, 1.0f);
        
        float angle = random() * 360.0f;
        
        light->setPosition(position);
        light->setDirection(Vector3(sinf(angle * M_DEGTORAD), -1.0f, cosf(angle * M_DEGTORAD)));
        light->setLightType(LIGHT_SPOT);
        light->setRange(75.0f);
        light->setRampTexture(mCache->getResource<Texture2D>("Textures/RampExtreme.png"));
        light->setFov(15.0f);
        light->setColor(color);
        light->setSpecularIntensity(1.0f);
        light->setCastShadows(true);
        light->setShadowBias(BiasParameters(0.00002f, 0.0f));
        light->setShadowResolution(0.5f);
        // The spot lights will not have anything near them, so move the near plane of the shadow camera farther
        // for better shadow depth resolution
        light->setShadowNearFarRatio(0.01f);
        
        Entity* newEntity = mScene->createEntity();
        newEntity->addComponent(light);
        mLights.push_back(newEntity);
    }
}

void Application::handleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    
    float timeStep = eventData[P_TIMESTEP].getFloat();
    
    if (!paused)
    {
        objectangle += 10.0f * timeStep;
        
        for (unsigned i = 0; i < mLights.size(); ++i)
        {
            Light* light = mLights[i]->getComponent<Light>();
            light->setRotation(Quaternion(0, objectangle * 2, 0));
        }
        
        for (unsigned i = 0; i < mAnimatingObjects.size(); ++i)
        {
            AnimatedModel* model = mAnimatingObjects[i]->getComponent<AnimatedModel>();
            const std::vector<AnimationState*>& anims = model->getAnimationStates();
            for (unsigned j = 0; j < anims.size(); ++j)
                anims[j]->addTime(timeStep);
        }
        
        for (unsigned i = 0; i < mBillboards.size(); ++i)
        {
            BillboardSet* billboard = mBillboards[i]->getComponent<BillboardSet>();
            std::vector<Billboard>& bb = billboard->getBillboards();
            for (unsigned j = 0; j < bb.size(); ++j)
                bb[j].mRotation += 50.0f * timeStep;
            billboard->updated();
        }
    }
    
    Input* input = mEngine->getInput();
    
    float speedMultiplier = 1.0f;
    if (input->getKeyDown(KEY_SHIFT))
        speedMultiplier = 5.0f;
    if (input->getKeyDown(KEY_CONTROL))
        speedMultiplier = 0.1f;
    
    if (input->getKeyDown('W'))
        mCameraEntity->getComponent<Camera>()->translateRelative(Vector3(0.0f,0.0f,10.0f) * timeStep * speedMultiplier);
    if (input->getKeyDown('S'))
        mCameraEntity->getComponent<Camera>()->translateRelative(Vector3(0.0f,0.0f,-10.0f) * timeStep * speedMultiplier);
    if (input->getKeyDown('A'))
        mCameraEntity->getComponent<Camera>()->translateRelative(Vector3(-10.0f,0.0f,0.0f) * timeStep * speedMultiplier);
    if (input->getKeyDown('D'))
        mCameraEntity->getComponent<Camera>()->translateRelative(Vector3(10.0f,0.0f,0.0f) * timeStep * speedMultiplier);
    
    if (input->getKeyPress('1'))
    {
        Renderer* renderer = mEngine->getRenderer();
        
        int nextRenderMode = renderer->getRenderMode();
        if (input->getKeyDown(KEY_SHIFT))
        {
            --nextRenderMode;
            if (nextRenderMode < 0)
                nextRenderMode = 2;
        }
        else
        {
            ++nextRenderMode;
            if (nextRenderMode > 2)
                nextRenderMode = 0;
        }
        
        renderer->setMode((RenderMode)nextRenderMode, renderer->getWidth(), renderer->getHeight(), renderer->getFullscreen(),
            renderer->getVsync(), renderer->getMultiSample());
    }
    
    if (input->getKeyPress('2'))
    {
        texturequality++;
        if (texturequality > 2)
            texturequality = 0;
        
        mEngine->getPipeline()->setTextureQuality(texturequality);
    }
    
    if (input->getKeyPress('3'))
    {
        materialquality++;
        if (materialquality > 2)
            materialquality = 0;
        mEngine->getPipeline()->setMaterialQuality(materialquality);
    }
    
    if (input->getKeyPress('4'))
    {
        usespecular = !usespecular;
        mEngine->getPipeline()->setSpecularLighting(usespecular);
    }
    
    if (input->getKeyPress('5'))
    {
        drawshadows = !drawshadows;
        mEngine->getPipeline()->setDrawShadows(drawshadows);
    }
    
    if (input->getKeyPress('6'))
    {
        shadowmapsize *= 2;
        if (shadowmapsize > 2048)
            shadowmapsize = 512;
        
        mEngine->getPipeline()->setShadowMapSize(shadowmapsize);
    }
    
    if (input->getKeyPress('7'))
    {
        hiresshadowmap = !hiresshadowmap;
        mEngine->getPipeline()->setShadowMapHiresDepth(hiresshadowmap);
    }
    
    if (input->getKeyPress('8'))
    {
        useocclusion = !useocclusion;
        mEngine->getPipeline()->setMaxOccluderTriangles(useocclusion ? 5000 : 0);
    }
    
    if (input->getKeyPress('L'))
    {
        Light* cameraLight = mCameraEntity->getComponent<Light>();
        attach = !attach;
        if (attach)
        {
            cameraLight->setPosition(Vector3::sZero);
            cameraLight->setRotation(Quaternion::sIdentity);
            mCameraEntity->getComponent<Camera>()->addChild(cameraLight);
        }
        else
        {
            // Detach child and set world transform to match what it was before detach
            mCameraEntity->getComponent<Camera>()->removeChild(cameraLight, true);
        }
    }
    
    if (input->getKeyPress(' '))
    {
        drawdebug++;
        if (drawdebug > 2) drawdebug = 0;
        mEngine->setDebugDrawMode(drawdebug);
    }
    
    if (input->getKeyPress('P'))
    {
        paused = !paused;
    }
    
    if (input->getKeyPress('C'))
    {
        Camera* camera = mCameraEntity->getComponent<Camera>();
        camera->setOrthographic(!camera->isOrthographic());
    }
    
    if (input->getKeyPress('O'))
    {
        if (!mOcclusionDebugImage)
        {
            try
            {
                Renderer* renderer = mEngine->getRenderer();
                UIElement* uiRoot = mEngine->getUIRoot();
                
                mOcclusionDebugTexture = new Texture2D(renderer, TEXTURE_DYNAMIC);
                mOcclusionDebugTexture->setNumLevels(1);
                mOcclusionDebugTexture->setSize(256, 256, D3DFMT_R32F);
                mOcclusionDebugImage = new BorderImage();
                mOcclusionDebugImage->setSize(256, 256);
                mOcclusionDebugImage->setTexture(mOcclusionDebugTexture);
                mOcclusionDebugImage->setAlignment(HA_RIGHT, VA_BOTTOM);
                uiRoot->addChild(mOcclusionDebugImage);
            }
            catch (...)
            {
            }
        }
        else
        {
            mOcclusionDebugImage->setVisible(!mOcclusionDebugImage->isVisible());
        }
    }
    
    if (input->getKeyPress('T'))
        mEngine->getDebugHud()->toggle(DEBUGHUD_SHOW_PROFILER);
    
    if (input->getKeyPress('F'))
    {
        Pipeline* pipeline = mEngine->getPipeline();
        EdgeFilterParameters params = pipeline->getEdgeFilter();
        if (params.mMaxFilter > 0.0f)
            params.mMaxFilter = 0.0f;
        else
            params.mMaxFilter = 1.0f;
        pipeline->setEdgeFilter(params);
    }
    
    if (input->getKeyPress(KEY_ESCAPE))
        mEngine->exit();
}

void Application::handlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace PostRenderUpdate;
    
    float timeStep = eventData[P_TIMESTEP].getFloat();
    
    // Test world raycast
    Camera* camera = mCameraEntity->getComponent<Camera>();
    UI* ui = mEngine->getUI();
    Renderer* renderer = mEngine->getRenderer();
    DebugRenderer* debug = mEngine->getDebugRenderer();
    
    if (camera)
    {
        IntVector2 pos = ui->getCursorPosition();
        if (!ui->getElementAt(pos))
        {
            Ray cameraRay = camera->getScreenRay(((float)pos.mX) / renderer->getWidth(), ((float)pos.mY) / renderer->getHeight());
            std::vector<RayQueryResult> result;
            RayOctreeQuery query(cameraRay, result, NODE_GEOMETRY, NODE_BILLBOARDSET, false, false, 250.0f, RAY_TRIANGLE);
            
            mScene->getExtension<Octree>()->getNodes(query);
            if (result.size())
            {
                VolumeNode* node = result[0].mNode;
                Vector3 rayHitPos = cameraRay.mOrigin + query.mResult[0].mDistance * cameraRay.mDirection;
                debug->addBoundingBox(BoundingBox(-0.01f, 0.01f), Matrix4x3(rayHitPos, Quaternion::sIdentity, Vector3::sUnity), Color(1.0f, 1.0f, 1.0f));
                
                // Check for sub-object results (node-specific)
                if (result[0].mSubObject < M_MAX_UNSIGNED)
                {
                    // Bone
                    if (node->getNodeFlags() & NODE_ANIMATEDMODEL)
                    {
                        AnimatedModel* anim = static_cast<AnimatedModel*>(node);
                        Bone* bone = anim->getSkeleton().getBone(result[0].mSubObject);
                        debug->addBoundingBox(bone->getBoundingBox(), bone->getWorldTransform(), Color(1.0f, 1.0f, 1.0f));
                    }
                    // Instance
                    else if (node->getNodeFlags() & NODE_INSTANCEDMODEL)
                    {
                        InstancedModel* instanced = static_cast<InstancedModel*>(node);
                        Instance* instance = instanced->getInstance(result[0].mSubObject);
                        Matrix4x3 transform(instance->mPosition, instance->mRotation, instance->mScale);
                        if (instanced->getInstancesRelative())
                            transform = instanced->getWorldTransform() * transform;
                        debug->addBoundingBox(instanced->getBoundingBox().getTransformed(transform), Color(1.0f, 1.0f, 1.0f));
                    }
                    // Custom object subgeometry
                    else if (node->getNodeFlags() & NODE_CUSTOMOBJECT)
                    {
                        CustomObject* custom = static_cast<CustomObject*>(node);
                        const CustomGeometry* geom = custom->getGeometry(result[0].mSubObject);
                        debug->addBoundingBox(geom->mBoundingBox.getTransformed(custom->getWorldTransform()), Color(1.0f, 1.0f, 1.0f));
                    }
                }
                else
                    debug->addBoundingBox(node->getWorldBoundingBox(), Color(1.0f, 1.0f, 1.0f));
            }
        }
    }
    
    // Update occlusion debug texture if visible
    if ((mOcclusionDebugImage) && (mOcclusionDebugImage->isVisible()))
    {
        PROFILE(App_UpdateOcclusionDebugTextures);
        
        static const float INV_Z_SCALE = 1.0f / (OCCLUSION_Z_SCALE);
        
        // Dump occlusion depth buffer to debug texture
        // Get an occlusion buffer matching the aspect ratio, it should be the main view occlusion buffer
        const OcclusionBuffer* buffer = mEngine->getPipeline()->getOcclusionBuffer(camera->getAspectRatio());
        if (buffer)
        {
            int width = buffer->getWidth();
            int height = buffer->getHeight();
            if (buffer->getBuffer())
            {
                mOcclusionDebugTexture->setSize(width, height, D3DFMT_R32F);
                mOcclusionDebugImage->setSize(width, height);
                mOcclusionDebugImage->setFullImageRect();
                D3DLOCKED_RECT hwRect;
                mOcclusionDebugTexture->lock(0, 0, &hwRect);
                for (int y = 0; y < height; ++y)
                {
                    float* dest = (float*)(((unsigned char*)hwRect.pBits) + y * hwRect.Pitch);
                    int* src = buffer->getBuffer() + y * width;
                    for (int x = 0; x < width; ++x)
                    {
                        float depth = src[x] * INV_Z_SCALE;
                        dest[x] = depth * 0.5f;
                    }
                }
                mOcclusionDebugTexture->unlock();
            }
        }
    }
}

void Application::handleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonDown;
    
    int button = eventData[P_BUTTON].getInt();
    if (button == MOUSEB_RIGHT)
    {
        UIElement* cursor = mEngine->getUICursor();
        if (cursor)
            cursor->setVisible(false);
    }
    if (button == MOUSEB_LEFT)
    {
        // Test creating a new physics object
        if (mCameraEntity)
        {
            Camera* camera = mCameraEntity->getComponent<Camera>();
            Octree* octree = mScene->getExtension<Octree>();
            PhysicsWorld* world = mScene->getExtension<PhysicsWorld>();
            
            Entity* newEntity = mScene->createEntity();
            
            RigidBody* body = new RigidBody(world);
            body->setMode(PHYS_DYNAMIC);
            body->setPosition(camera->getPosition());
            body->setRotation(camera->getRotation());
            body->setScale(0.1f);
            body->setFriction(1.0f);
            body->setAngularMaxVelocity(500.0f);
            body->setCollisionShape(mCache->getResource<CollisionShape>("Physics/Box.xml"));
            body->setCollisionGroup(1);
            body->setCollisionMask(3);
            body->setLinearVelocity(camera->getUpVector() + camera->getForwardVector() * 10.0f);
            
            StaticModel* object = new StaticModel(octree);
            object->setModel(mCache->getResource<Model>("Models/Box.mdl"));
            object->setMaterial(mCache->getResource<Material>("Materials/Test.xml"));
            object->setCastShadows(true);
            object->setShadowDistance(75.0f);
            object->setDrawDistance(100.0f);
            body->addChild(object);
            
            newEntity->addComponent(body);
            newEntity->addComponent(object);
        }
    }
}

void Application::handleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonDown;
    
    if (eventData[P_BUTTON].getInt() == MOUSEB_RIGHT)
    {
        UIElement* cursor = mEngine->getUICursor();
        if (cursor)
            cursor->setVisible(true);
    }
}

void Application::handleMouseMove(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;
    
    if (eventData[P_BUTTONS].getInt() & MOUSEB_RIGHT)
    {
        int mousedx = eventData[P_X].getInt();
        int mousedy = eventData[P_Y].getInt();
        yaw += mousedx / 10.0f;
        pitch += mousedy / 10.0f;
        if (pitch < -90.0f)
            pitch = -90.0f;
        if (pitch > 90.0f)
            pitch = 90.0f;
        
        if (mCameraEntity)
            mCameraEntity->getComponent<Camera>()->setRotation(Quaternion(yaw, Vector3::sUp) * Quaternion(pitch, Vector3::sRight));
    }
}

void calculateTangents(float* vertexData, unsigned vertexCount, const unsigned short* indexData, unsigned indexCount)
{
    // Tangent generation from
    // http://www.terathon.com/code/tangent.html
    
    static const int V_OFS = 0;
    static const int N_OFS = 3;
    static const int UV_OFS = 6;
    static const int T_OFS = 8;
    static const int V_SIZE = 12;
    
    Vector3 *tan1 = new Vector3[vertexCount * 2];
    Vector3 *tan2 = tan1 + vertexCount;
    memset(tan1, 0, sizeof(Vector3) * vertexCount * 2);
    
    for (unsigned a = 0; a < indexCount; a += 3)
    {
        unsigned short i1 = indexData[a+0];
        unsigned short i2 = indexData[a+1];
        unsigned short i3 = indexData[a+2];
        
        const Vector3 v1 = Vector3(&vertexData[i1 * V_SIZE + V_OFS]);
        const Vector3 v2 = Vector3(&vertexData[i2 * V_SIZE + V_OFS]);
        const Vector3 v3 = Vector3 (&vertexData[i3 * V_SIZE + V_OFS]);
        
        const Vector2 w1 = Vector2(&vertexData[i1 * V_SIZE + UV_OFS]);
        const Vector2 w2 = Vector2(&vertexData[i2 * V_SIZE + UV_OFS]);
        const Vector2 w3 = Vector2(&vertexData[i3 * V_SIZE + UV_OFS]);
        
        float x1 = v2.mX - v1.mX;
        float x2 = v3.mX - v1.mX;
        float y1 = v2.mY - v1.mY;
        float y2 = v3.mY - v1.mY;
        float z1 = v2.mZ - v1.mZ;
        float z2 = v3.mZ - v1.mZ;
        
        float s1 = w2.mX - w1.mX;
        float s2 = w3.mX - w1.mX;
        float t1 = w2.mY - w1.mY;
        float t2 = w3.mY - w1.mY;
        
        float r = 1.0f / (s1 * t2 - s2 * t1);
        Vector3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
                (t2 * z1 - t1 * z2) * r);
        Vector3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
                (s1 * z2 - s2 * z1) * r);
        
        tan1[i1] += sdir;
        tan1[i2] += sdir;
        tan1[i3] += sdir;
        
        tan2[i1] += tdir;
        tan2[i2] += tdir;
        tan2[i3] += tdir;
    }
    
    for (unsigned a = 0; a < vertexCount; a++)
    {
        const Vector3 n = Vector3(&vertexData[a * V_SIZE + N_OFS]);
        const Vector3 t = Vector3(tan1[a]);
        Vector3 xyz;
        float w;
        
        // Gram-Schmidt orthogonalize
        xyz = (t - n * n.dotProduct(t)).getNormalized();
        
        // Calculate handedness
        w = n.crossProduct(t).dotProduct(tan2[a]) < 0.0f ? -1.0f : 1.0f;
        
        vertexData[a * V_SIZE + T_OFS] = xyz.mX;
        vertexData[a * V_SIZE + T_OFS + 1] = xyz.mY;
        vertexData[a * V_SIZE + T_OFS + 2] = xyz.mZ;
        vertexData[a * V_SIZE + T_OFS + 3] = w;
    }
    
    delete[] tan1;
}
