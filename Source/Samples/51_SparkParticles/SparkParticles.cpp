//
// Copyright (c) 2008-2017 the Urho3D project.
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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/Technique.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include <Urho3D/Spark/SPARK_URHO3D.h>
#include <Spark/SPARK.h>

#include "SparkParticles.h"

#include <Urho3D/DebugNew.h>

URHO3D_DEFINE_APPLICATION_MAIN(SparkParticles)


///---------------------------------------------------------------------------------------------
/// Custom logic component for moving a node around a circle with sin/cos variations.
///---------------------------------------------------------------------------------------------
class FxMover : public LogicComponent
{
    URHO3D_OBJECT(FxMover, LogicComponent)

public:

    /// Construct.
    FxMover(Context* context) :
      LogicComponent(context),
        speed_(0.0f),
        radius_(0.0f),
        elapsedTime_(0.0f)
    {
        // Only the scene update event is needed: unsubscribe from the rest for optimization
        SetUpdateEventMask(USE_UPDATE);
    }

    /// Set motion parameters: forward movement speed, rotation speed
    void SetParameters(float speed, float radius)
    {
        speed_ = speed;
        radius_ = radius;
    }

    /// Handle scene update. Called by LogicComponent base class.
    void Update(float timeStep)
    {
        Vector3 pos = node_->GetPosition();
        pos.x_ = sin(elapsedTime_ * speed_) * radius_;
        pos.y_ = 1.2f + sin(elapsedTime_ * speed_ * 10.0f) * 1.0f;
        pos.z_ = cos(elapsedTime_ * speed_) * radius_;

        node_->SetPosition(pos);

        elapsedTime_ += timeStep;
    }

private:
    /// Moving speed
    float speed_;
    /// Circle radius
    float radius_;
    /// Elasped time
    float elapsedTime_;
};



///---------------------------------------------------------------------------------------------
/// Spark Particle Sample.
///---------------------------------------------------------------------------------------------
SparkParticles::SparkParticles(Context* context) :
    Sample(context)
{
    // Register Urho3D Spark Objects.
    SparkParticleEffect::RegisterObject(context_);
    SparkParticle::RegisterObject(context_);

    // Register the logic component used to move a node around a circle.
    context_->RegisterFactory<FxMover>();
}

void SparkParticles::Start()
{
    // Execute base class startup
    Sample::Start();

    // Build manually a Spark Effect explosion from scratch.
    CreateExplosionEffect();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateInstructions();

    // Hook up to the frame update events
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_RELATIVE);
}

void SparkParticles::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();

    // Create static scene content. First create a zone for ambient lighting and fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.2f, 0.2f, 0.4f));
    zone->SetFogStart(100.0f);
    zone->SetFogEnd(300.0f);
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));


    // There is 2 ways of using Spark Particles.

    // 1. Build manually in memory a spark effect using code.

    // Create Spark effect from scratch
    CreateFountainEffect();

    // Once effect is builded, assign it to a SparkParticleEffect and add it to the cache.
    SparkParticleEffect* effect = new SparkParticleEffect(context_);
    effect->SetSystem(effectFountain_);
    effect->SetName("MyNewSparkParticleEffectResource");
    cache->AddManualResource(effect); // ! important for clones

    // Now, we can use this effect inside a SparkParticle component.
    Node* node1 = scene_->CreateChild("Spark1");
    node1->SetPosition(Vector3(10.0f, 0.0f, 0.0f));
    SparkParticle * sparkComponent1 = node1->CreateComponent<SparkParticle>();
    sparkComponent1->SetEffect(effect);


    // 2. Load a spark effect file and use a SparkParticle component.

    // Create a new child scene node and a create a SparkParticle component into it.
    // Set effect by loading a SparkParticleEffect resource.
    // Note1: SparkParticleEffect can load .xml or .spk files
    // Note2: Spark effect .xml and .spk files can be created by exporting a manually builded effect or using a spark particle editor.


    // Create some particles nodes.

    Node* nodeEffect1 = scene_->CreateChild("Fire");
    nodeEffect1->SetPosition(Vector3(-10.0f, 0.0f, 0.0f));
    SparkParticle * spk1 = nodeEffect1->CreateComponent<SparkParticle>();
    spk1->SetEffect(cache->GetResource<SparkParticleEffect>("Spark/Effects/FireAtlas.xml"));

    Node* nodeEffect2 = scene_->CreateChild("Bubbles");
    nodeEffect2->SetPosition(Vector3(-5.0f, 5.0f, 0.0f));
    SparkParticle * spk2 = nodeEffect2->CreateComponent<SparkParticle>();
    spk2->SetEffect(cache->GetResource<SparkParticleEffect>("Spark/Effects/Bubbles.xml"));

    Node* nodeEffect3 = scene_->CreateChild("Vortex");
    nodeEffect3->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    SparkParticle * spk3 = nodeEffect3->CreateComponent<SparkParticle>();
    spk3->SetEffect(cache->GetResource<SparkParticleEffect>("Spark/Effects/Vortex.xml"));

    Node* nodeEffect4 = scene_->CreateChild("Spark");
    nodeEffect4->SetPosition(Vector3(5.0f, 2.0f, 0.0f));
    SparkParticle * spk4 = nodeEffect4->CreateComponent<SparkParticle>();
    spk4->SetEffect(cache->GetResource<SparkParticleEffect>("Spark/Effects/Spark1.xml"));

    // Create a node moving around a circle
    // Attach to it a ball model, a light and particles effect.
    {
        magicBallNode_ = scene_->CreateChild("MagicBall");
        magicBallNode_->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

        FxMover* mover = magicBallNode_->CreateComponent<FxMover>();
        mover->SetParameters(2.0f, 15.0f);

        StaticModel* ball = magicBallNode_->CreateComponent<StaticModel>();
        ball->SetModel(cache->GetResource<Model>("Models/Sphere.mdl"));
        ball->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));

        Light* lightBall = magicBallNode_->CreateComponent<Light>();
        lightBall->SetLightType(LIGHT_POINT);
        lightBall->SetRange(3.0f);
        lightBall->SetBrightness(2.0f);
        lightBall->SetColor(Color(0.9f, 0.6f, 0.1f));

        SparkParticle * spkMagicBall = magicBallNode_->CreateComponent<SparkParticle>();
        spkMagicBall->SetEffect(cache->GetResource<SparkParticleEffect>("Spark/Effects/MagicBall.xml"));
    }


    // Create some burning mushrooms.
    const unsigned NUM_OBJECTS = 18;
    for (unsigned i = 0; i < NUM_OBJECTS; ++i)
    {
        float posX = Cos(i * 20.0f) * 20.0f;
        float posY = Sin(i * 20.0f) * 20.0f;

        Node* mushroomNode = scene_->CreateChild("Mushroom");
        mushroomNode->SetPosition(Vector3(posX, 0.0f, posY));
        mushroomNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
        mushroomNode->SetScale(0.5f);

        StaticModel* mushroomObject = mushroomNode->CreateComponent<StaticModel>();
        mushroomObject->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
        mushroomObject->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));

        SparkParticle* spk = mushroomNode->CreateComponent<SparkParticle>();
        spk->SetEffect(cache->GetResource<SparkParticleEffect>("Spark/Effects/Fire1.xml"));
    }


    // Create a plane.
    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    // Create a directional light.
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);

    // Create a camera.
    cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, -20.0f));

    // Set up a viewport
    Renderer* renderer = GetSubsystem<Renderer>();
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}


void SparkParticles::CreateExplosionEffect()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Load base material
    Material* baseMaterial = cache->GetResource<Material>("Materials/Particle.xml");

    // Create material clones and set textures

    SharedPtr<Material> textureExplosion = baseMaterial->Clone();
    textureExplosion->SetTexture(TU_DIFFUSE, cache->GetResource<Texture2D>("Spark/Textures/explosion.bmp"));

    SharedPtr<Material> textureFlash = baseMaterial->Clone();
    textureFlash->SetTexture(TU_DIFFUSE, cache->GetResource<Texture2D>("Spark/Textures/flash.bmp"));

    SharedPtr<Material> textureSpark1 = baseMaterial->Clone();
    textureSpark1->SetTexture(TU_DIFFUSE, cache->GetResource<Texture2D>("Spark/Textures/Arrow.png"));

    SharedPtr<Material> textureSpark2 = baseMaterial->Clone();
    textureSpark2->SetTexture(TU_DIFFUSE, cache->GetResource<Texture2D>("Spark/Textures/point.bmp"));

    SharedPtr<Material> textureWave = baseMaterial->Clone();
    textureWave->SetTexture(TU_DIFFUSE, cache->GetResource<Texture2D>("Spark/Textures/wave.bmp"));


    ///////////////
    // Renderers //
    ///////////////

    // smoke renderer
    SPK::Ref<SPK::URHO::Urho3DQuadRenderer> smokeRenderer = SPK::URHO::Urho3DQuadRenderer::create(context_);
    smokeRenderer->setTexturingMode(SPK::TEXTURE_MODE_2D);
    smokeRenderer->setMaterial(textureExplosion);
    smokeRenderer->setAtlasDimensions(2,2); // uses 4 different patterns in the texture
    smokeRenderer->setShared(true);

    // flame renderer
    SPK::Ref<SPK::URHO::Urho3DQuadRenderer> flameRenderer = SPK::URHO::Urho3DQuadRenderer::create(context_);
    flameRenderer->setTexturingMode(SPK::TEXTURE_MODE_2D);
    flameRenderer->setMaterial(textureExplosion);
    flameRenderer->setAtlasDimensions(2,2);
    flameRenderer->setShared(true);

    // flash renderer
    SPK::Ref<SPK::URHO::Urho3DQuadRenderer> flashRenderer = SPK::URHO::Urho3DQuadRenderer::create(context_);
    flashRenderer->setTexturingMode(SPK::TEXTURE_MODE_2D);
    flashRenderer->setMaterial(textureFlash);
    flashRenderer->setShared(true);

    // spark 1 renderer
    SPK::Ref<SPK::URHO::Urho3DQuadRenderer> spark1Renderer = SPK::URHO::Urho3DQuadRenderer::create(context_);
    spark1Renderer->setTexturingMode(SPK::TEXTURE_MODE_2D);
    spark1Renderer->setMaterial(textureSpark1);
    spark1Renderer->setOrientation(SPK::DIRECTION_ALIGNED); // sparks are oriented function of their velocity
    spark1Renderer->setScale(1.05f,1.0f); // thin rectangles
    spark1Renderer->setShared(true);

    // spark 2 renderer
    SPK::Ref<SPK::URHO::Urho3DQuadRenderer> spark2Renderer = SPK::URHO::Urho3DQuadRenderer::create(context_);
    spark2Renderer->setTexturingMode(SPK::TEXTURE_MODE_2D);
    spark2Renderer->setMaterial(textureSpark2);
    spark2Renderer->setShared(true);

    // wave renderer
    SPK::Ref<SPK::URHO::Urho3DQuadRenderer> waveRenderer = SPK::URHO::Urho3DQuadRenderer::create(context_);
    waveRenderer->setTexturingMode(SPK::TEXTURE_MODE_2D);
    waveRenderer->setMaterial(textureWave);
    waveRenderer->setAlphaTestThreshold(0.0f);
    waveRenderer->setOrientation(SPK::FIXED_ORIENTATION); // the orientation is fixed
    waveRenderer->lookVector.set(0.0f,1.0f,0.0f);
    waveRenderer->upVector.set(1.0f,0.0f,0.0f); // we dont really care about the up axis
    waveRenderer->setShared(true);

    //////////////
    // Emitters //
    //////////////

    // This zone will be used by several emitters
    SPK::Ref<SPK::Sphere> explosionSphere = SPK::Sphere::create(SPK::Vector3D(0.0f,0.0f,0.0f),0.4f);

    // smoke emitter
    SPK::Ref<SPK::RandomEmitter> smokeEmitter = SPK::RandomEmitter::create();
    smokeEmitter->setZone(SPK::Sphere::create(SPK::Vector3D(0.0f,0.0f,0.0f),0.6f),false);
    smokeEmitter->setTank(15);
    smokeEmitter->setFlow(-1);
    smokeEmitter->setForce(0.02f,0.04f);

    // flame emitter
    SPK::Ref<SPK::NormalEmitter> flameEmitter = SPK::NormalEmitter::create();
    flameEmitter->setZone(explosionSphere);
    flameEmitter->setTank(15);
    flameEmitter->setFlow(-1);
    flameEmitter->setForce(0.06f,0.1f);

    // flash emitter
    SPK::Ref<SPK::StaticEmitter> flashEmitter = SPK::StaticEmitter::create();
    flashEmitter->setZone(SPK::Sphere::create(SPK::Vector3D(0.0f,0.0f,0.0f),0.1f));
    flashEmitter->setTank(3);
    flashEmitter->setFlow(-1);

    // spark 1 emitter
    SPK::Ref<SPK::NormalEmitter> spark1Emitter = SPK::NormalEmitter::create();
    spark1Emitter->setZone(explosionSphere);
    spark1Emitter->setTank(20);
    spark1Emitter->setFlow(-1);
    spark1Emitter->setForce(2.0f,3.0f);
    spark1Emitter->setInverted(true);

    // spark 2 emitter
    SPK::Ref<SPK::NormalEmitter> spark2Emitter = SPK::NormalEmitter::create();
    spark2Emitter->setZone(explosionSphere);
    spark2Emitter->setTank(400);
    spark2Emitter->setFlow(-1);
    spark2Emitter->setForce(0.4f,1.0f);
    spark2Emitter->setInverted(true);

    // wave emitter
    SPK::Ref<SPK::StaticEmitter> waveEmitter = SPK::StaticEmitter::create();
    waveEmitter->setZone(SPK::Point::create());
    waveEmitter->setTank(1);
    waveEmitter->setFlow(-1);

    ////////////
    // Groups //
    ////////////

    effectExplosion_ = SPK::System::create(false); // not initialized at start, will be when spawned.
    effectExplosion_->setName("Explosion");

    SPK::Ref<SPK::ColorGraphInterpolator> colorInterpolator;
    SPK::Ref<SPK::FloatGraphInterpolator> paramInterpolator;

    // smoke group
    colorInterpolator = SPK::ColorGraphInterpolator::create();
    colorInterpolator->addEntry(0.0f,0x33333300);
    colorInterpolator->addEntry(0.4f,0x33333366,0x33333399);
    colorInterpolator->addEntry(0.6f,0x33333366,0x33333399);
    colorInterpolator->addEntry(1.0f,0x33333300);

    SPK::Ref<SPK::Group> smokeGroup = effectExplosion_->createGroup(15);
    smokeGroup->setName("Smoke");
    smokeGroup->setPhysicalRadius(0.0f);
    smokeGroup->setLifeTime(2.5f,3.0f);
    smokeGroup->setRenderer(smokeRenderer);
    smokeGroup->addEmitter(smokeEmitter);
    smokeGroup->setColorInterpolator(colorInterpolator);
    smokeGroup->setParamInterpolator(SPK::PARAM_SCALE,SPK::FloatRandomInterpolator::create(0.3f,0.4f,0.5f,0.7f));
    smokeGroup->setParamInterpolator(SPK::PARAM_TEXTURE_INDEX,SPK::FloatRandomInitializer::create(0.0f,4.0f));
    smokeGroup->setParamInterpolator(SPK::PARAM_ANGLE,SPK::FloatRandomInterpolator::create(0.0f,M_PI * 0.5f,0.0f,M_PI * 0.5f));
    smokeGroup->addModifier(SPK::Gravity::create(SPK::Vector3D(0.0f,0.05f,0.0f)));

    // flame group
    colorInterpolator = SPK::ColorGraphInterpolator::create();
    colorInterpolator->addEntry(0.0f,0xFF8033FF);
    colorInterpolator->addEntry(0.5f,0x995933FF);
    colorInterpolator->addEntry(1.0f,0x33333300);

    paramInterpolator = SPK::FloatGraphInterpolator::create();
    paramInterpolator->addEntry(0.0f,0.125f);
    paramInterpolator->addEntry(0.02f,0.3f,0.4f);
    paramInterpolator->addEntry(1.0f,0.5f,0.7f);

    SPK::Ref<SPK::Group> flameGroup = effectExplosion_->createGroup(15);
    flameGroup->setName("Flame");
    flameGroup->setLifeTime(1.5f,2.0f);
    flameGroup->setRenderer(flameRenderer);
    flameGroup->addEmitter(flameEmitter);
    flameGroup->setColorInterpolator(colorInterpolator);
    flameGroup->setParamInterpolator(SPK::PARAM_SCALE,paramInterpolator);
    flameGroup->setParamInterpolator(SPK::PARAM_TEXTURE_INDEX,SPK::FloatRandomInitializer::create(0.0f,4.0f));
    flameGroup->setParamInterpolator(SPK::PARAM_ANGLE,SPK::FloatRandomInterpolator::create(0.0f,M_PI * 0.5f,0.0f,M_PI * 0.5f));

    // flash group
    paramInterpolator = SPK::FloatGraphInterpolator::create();
    paramInterpolator->addEntry(0.0f,0.1f);
    paramInterpolator->addEntry(0.25f,0.5f,1.0f);

    SPK::Ref<SPK::Group> flashGroup = effectExplosion_->createGroup(3);
    flashGroup->setName("Flash");
    flashGroup->setLifeTime(0.2f,0.2f);
    flashGroup->addEmitter(flashEmitter);
    flashGroup->setRenderer(flashRenderer);
    flashGroup->setColorInterpolator(SPK::ColorSimpleInterpolator::create(0xFFFFFFFF,0xFFFFFF00));
    flashGroup->setParamInterpolator(SPK::PARAM_SCALE,paramInterpolator);
    flashGroup->setParamInterpolator(SPK::PARAM_ANGLE,SPK::FloatRandomInitializer::create(0.0f,2.0f * M_PI));

    // spark 1 group
    SPK::Ref<SPK::Group> spark1Group = effectExplosion_->createGroup(20);
    spark1Group->setName("Spark 1");
    spark1Group->setPhysicalRadius(0.0f);
    spark1Group->setLifeTime(0.2f,1.0f);
    spark1Group->addEmitter(spark1Emitter);
    spark1Group->setRenderer(spark1Renderer);
    spark1Group->setColorInterpolator(SPK::ColorSimpleInterpolator::create(0xFFFFFFFF,0xFFFFFF00));
    spark1Group->setParamInterpolator(SPK::PARAM_SCALE,SPK::FloatRandomInitializer::create(0.1f,0.2f));
    spark1Group->addModifier(SPK::Gravity::create(SPK::Vector3D(0.0f,-0.75f,0.0f)));

    // spark 2 group
    SPK::Ref<SPK::Group> spark2Group = effectExplosion_->createGroup(400);
    spark2Group->setName("Spark 2");
    spark2Group->setGraphicalRadius(0.01f);
    spark2Group->setLifeTime(1.0f,3.0f);
    spark2Group->addEmitter(spark2Emitter);
    spark2Group->setRenderer(spark2Renderer);
    spark2Group->setColorInterpolator(SPK::ColorRandomInterpolator::create(0xFFFFB2FF,0xFFFFB2FF,0xFF4C4C00,0xFFFF4C00));
    spark2Group->setParamInterpolator(SPK::PARAM_MASS,SPK::FloatRandomInitializer::create(0.5f,2.5f));
    spark2Group->addModifier(SPK::Gravity::create(SPK::Vector3D(0.0f,-0.1f,0.0f)));
    spark2Group->addModifier(SPK::Friction::create(0.4f));

    // wave group
    paramInterpolator = SPK::FloatGraphInterpolator::create();
    paramInterpolator->addEntry(0.0f,0.0f);
    paramInterpolator->addEntry(0.2f,0.0f);
    paramInterpolator->addEntry(1.0f,3.0f);

    SPK::Ref<SPK::Group> waveGroup = effectExplosion_->createGroup(1);
    waveGroup->setName("Wave");
    waveGroup->setLifeTime(0.8f,0.8f);
    waveGroup->addEmitter(waveEmitter);
    waveGroup->setRenderer(waveRenderer);
    waveGroup->setColorInterpolator(SPK::ColorSimpleInterpolator::create(0xFFFFFF20,0xFFFFFF00));
    waveGroup->setParamInterpolator(SPK::PARAM_SCALE,paramInterpolator);
}


void SparkParticles::AddExplosion(Vector3 pos)
{
    // Create a new node.
    Node* spkSystemNode = scene_->CreateChild("Explosion");
    spkSystemNode->SetPosition(pos);

    // Create SparkParticle component
    SparkParticle* spkSystem = spkSystemNode->CreateComponent<SparkParticle>();
    spkSystem->SetSystem(effectExplosion_);

    // Initialize system to start effect.
    spkSystem->GetSystem()->initialize();
}

void SparkParticles::CreateFountainEffect()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    SPK::Ref<SPK::System> system_ = SPK::System::create(true);
    system_->setName("Test System");

    // Renderer
    SPK::Ref<SPK::URHO::Urho3DQuadRenderer> renderer = SPK::URHO::Urho3DQuadRenderer::create(context_);
    renderer->setTexturingMode(SPK::TEXTURE_MODE_2D);
    renderer->setScale(0.1f,0.1f);
    renderer->setMaterial(cache->GetResource<Material>("Spark/Materials/SparkParticleAddAlpha.xml"));
    renderer->setOrientation(SPK::OrientationPreset::CAMERA_PLANE_ALIGNED);

    // Emitter
    SPK::Ref<SPK::SphericEmitter> particleEmitter = SPK::SphericEmitter::create(SPK::Vector3D(0.0f,1.0f,0.0f),0.1f * M_PI, 0.1f * M_PI);
    particleEmitter->setZone(SPK::Point::create(SPK::Vector3D(0.0f,0.015f,0.0f)));
    particleEmitter->setFlow(300);
    particleEmitter->setForce(1.5f,1.5f);

    // Obstacle
    SPK::Ref<SPK::Plane> groundPlane = SPK::Plane::create();
    SPK::Ref<SPK::Obstacle> obstacle = SPK::Obstacle::create(groundPlane,0.9f,1.0f);
    obstacle->setBouncingRatio(0.2f);
    obstacle->setFriction(0.9f);

    // Group
    SPK::Ref<SPK::Group> particleGroup = system_->createGroup(10000);
    particleGroup->addEmitter(particleEmitter);
    particleGroup->addModifier(obstacle);
    particleGroup->setRenderer(renderer);
    particleGroup->addModifier(SPK::Gravity::create(SPK::Vector3D(0.0f,-1.0f,0.0f)));
    particleGroup->setLifeTime(4.2f,4.5f);
    particleGroup->setColorInterpolator(SPK::ColorSimpleInterpolator::create(0xFF880035,0xFF0050FF));
    particleGroup->enableSorting(true);

    // get a final copy af this effect.
    effectFountain_ = SPK::SPKObject::copy(system_);
}

void SparkParticles::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();

    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText("Use WASD keys and mouse/touch to move\nPress Space bar to create explosions");
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void SparkParticles::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    Input* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;

    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);

    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    // Use the Translate() function (default local space) to move relative to the node's orientation.
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);


    // Add an explosion effect at random position when press space
    if (input->GetKeyPress(KEY_SPACE))
    {
        AddExplosion(Vector3(Random(40.0f) - 20.0f, 3.0f, Random(40.0f) - 20.0f));
    }
}

void SparkParticles::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(SparkParticles, HandleUpdate));
}

void SparkParticles::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
}
