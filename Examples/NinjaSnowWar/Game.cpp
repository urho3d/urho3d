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
#include "AIController.h"
#include "Audio.h"
#include "BorderImage.h"
#include "Camera.h"
#include "Client.h"
#include "CollisionShape.h"
#include "Connection.h"
#include "DebugHud.h"
#include "Engine.h"
#include "EngineEvents.h"
#include "Exception.h"
#include "File.h"
#include "Font.h"
#include "Game.h"
#include "GameConfig.h"
#include "GameEvents.h"
#include "GameObjectFactory.h"
#include "Input.h"
#include "InputEvents.h"
#include "Light.h"
#include "Log.h"
#include "Material.h"
#include "MemoryBuffer.h"
#include "Ninja.h"
#include "PackageFile.h"
#include "PositionalChannel.h"
#include "Potion.h"
#include "PhysicsEvents.h"
#include "PhysicsWorld.h"
#include "Pipeline.h"
#include "ProcessUtils.h"
#include "Profiler.h"
#include "ProtocolEvents.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "RigidBody.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "ScriptEngine.h"
#include "ScriptFile.h"
#include "Server.h"
#include "Skybox.h"
#include "SnowBall.h"
#include "SnowCrate.h"
#include "StaticModel.h"
#include "StringUtils.h"
#include "Text.h"
#include "Texture2D.h"
#include "UI.h"
#include "UIEvents.h"
#include "XM.h"
#include "XMLFile.h"
#include "Zone.h"

#include <algorithm>

#include "DebugNew.h"

int simulatePacketLoss = 0;
int simulateLatency = 0;
std::string applicationDir;
std::string downloadDir;

Game::Game() :
    mTimeScale(1.0f),
    mCameraMinDist(0.0f),
    mCameraMaxDist(0.0f),
    mCameraSafetyDist(0.0f),
    mCameraRayLength(0.0f),
    mGameOn(false),
    mFirstFrame(false),
    mPaused(false),
    mClientEntityID(0)
{
    std::string userDir = getUserDocumentsDirectory();
    applicationDir = userDir + "NinjaSnowWar";
    
    // Test the "allowed path" feature. Access outside the working directory, and these paths, should cause an exception
    registerDirectory("Data");
    registerDirectory(getSystemFontDirectory());
    registerDirectory(applicationDir);
    
    createDirectory(applicationDir);
    applicationDir = fixPath(applicationDir); // Add the slash at the end
    downloadDir = applicationDir + "Cache";
    createDirectory(downloadDir); // Create package download cache
    
    subscribeToEvent(EVENT_UPDATE, EVENT_HANDLER(Game, handleUpdate));
    subscribeToEvent(EVENT_POSTUPDATE, EVENT_HANDLER(Game, handlePostUpdate));
    subscribeToEvent(EVENT_PHYSICSPRESTEP, EVENT_HANDLER(Game, handlePreStep));
    subscribeToEvent(EVENT_DIE, EVENT_HANDLER(Game, handleGameEvent));
    subscribeToEvent(EVENT_REMOVE, EVENT_HANDLER(Game, handleGameEvent));
    subscribeToEvent(EVENT_CLIENTIDENTITY, EVENT_HANDLER(Game, handleClientIdentity));
    subscribeToEvent(EVENT_JOINEDSCENE, EVENT_HANDLER(Game, handleJoinedScene));
    subscribeToEvent(EVENT_CONTROLSUPDATE, EVENT_HANDLER(Game, handleControlsUpdate));
    subscribeToEvent(EVENT_CONTROLSPLAYBACK, EVENT_HANDLER(Game, handleControlsPlayback));
    subscribeToEvent(EVENT_CLIENTJOINEDSCENE, EVENT_HANDLER(Game, handleClientJoined));
    subscribeToEvent(EVENT_CLIENTLEFTSCENE, EVENT_HANDLER(Game, handleClientLeft));
    subscribeToEvent(EVENT_PLAYERSPAWNED, EVENT_HANDLER(Game, handlePlayerSpawned));
    
    registerRemoteEvent(EVENT_PLAYERSPAWNED);
}

Game::~Game()
{
}

void Game::run()
{
    init();
    
    while (!mEngine->isExiting())
    {
        mEngine->runFrame(mScene, mCamera, !mPaused);
        
        // Save/load/exit
        // Check these outside the frame update, so that the engine does not render a black screen
        // for one frame after loading a game (the old camera has been destroyed at that point)
        Input* input = mEngine->getInput();
        if (input->getKeyPress(KEY_F5))
            saveGame();
        if (input->getKeyPress(KEY_F7))
            loadGame();
        if (input->getKeyPress(KEY_ESC))
            mEngine->exit();
    }
}

void Game::init()
{
    PROFILE(Game_Init);
    
    bool runServer = false;
    bool runClient = false;
    std::string address;
    std::string logName = "NinjaSnowWar.log";
    
    // Force forward rendering
    std::vector<std::string> arguments = getArguments();
    arguments.insert(arguments.begin(), "-forward");
    
    for (unsigned i = 0; i < arguments.size(); ++i)
    {
        if (toLower(arguments[i]) == "server")
        {
            logName = "Server.log";
            runServer = true;
            runClient = false;
        }
        else
        {
            if ((arguments[i][0] != '-') && (!runClient))
            {
                logName = "Client.log";
                runServer = false;
                runClient = true;
                address = arguments[i];
                if ((arguments.size() > i + 1) && (arguments[i + 1][0] != '-'))
                    mUserName = arguments[i + 1];
            }
        }
    }
    
    // Initialize the engine. If running the server, use headless mode
    mEngine = new Engine("NinjaSnowWar", logName, runServer);
    
    // Add the resources as a package if available
    mCache = mEngine->getResourceCache();
    if (fileExists("Data.pak"))
        mCache->addPackageFile(new PackageFile("Data.pak"));
    else
        mCache->addResourcePath("Data");
    
    mEngine->init(arguments);
    
    mCache->addResourcePath(getSystemFontDirectory());
    
    DebugHud* debugHud = mEngine->createDebugHud();
    debugHud->setFont(mCache->getResource<Font>("cour.ttf"), 12);
    
    if (runServer)
    {
        mServer = mEngine->createServer();
        mServer->setNetFps(25); // Set FPS to match an even amount of physics updates
    }
    if (runClient)
        mClient = mEngine->createClient(downloadDir);
    
    // Setup sound. Play music in singleplayer only
    Audio* audio = mEngine->getAudio();
    audio->setMasterGain(CHANNEL_MASTER, 0.75f);
    audio->setMasterGain(CHANNEL_MUSIC, 0.75f);
    if ((!runServer) && (!runClient))
    {
        XM* song = mCache->getResource<XM>("Music/NinjaGods.xm");
        song->play();
    }
    
    setupOptions();
    createOverlays();
    createScene();
    
    // If running a server, add the scene to the server, and all packages to required packages
    if (mServer)
    {
        mServer->addScene(mScene);
        const std::vector<SharedPtr<PackageFile> >& packages = mCache->getPackageFiles();
        for (unsigned i = 0; i < packages.size(); ++i)
            mScene->addRequiredPackageFile(packages[i]);
        mServer->start(1234);
    }
    // If running a client, try connecting
    if (mClient)
    {
        mClient->setScene(mScene);
        mClient->connect(address, 1234, mUserName);
    }
    
    startGame();
}

void Game::setupOptions()
{
    GameConfig::load("NinjaSnowWar.xml", mCache);
    mSensitivity = GameConfig::getReal("Controls/MouseSensitivity");
    setupCamera();
    Ninja::setup();
    SnowBall::setup();
    SnowCrate::setup();
    Potion::setup();
}

void Game::createOverlays()
{
    UIElement* uiRoot = mEngine->getUIRoot();
    if (!uiRoot)
        return;
    
    Renderer* renderer = mEngine->getRenderer();
    mSight = new BorderImage();
    mSight->setTexture(mCache->getResource<Texture2D>("Textures/Sight.png"));
    mSight->setAlignment(HA_CENTER, VA_CENTER);
    int height = min(renderer->getHeight() / 22, 64);
    
    mSight->setSize(height, height);
    uiRoot->addChild(mSight);
    
    mScoreText = new Text();
    mScoreText->setFont(mCache->getResource<Font>("Fonts/BlueHighway.ttf"), 17);
    mScoreText->setAlignment(HA_LEFT, VA_TOP);
    mScoreText->setPosition(5, 5);
    mScoreText->setColor(C_BOTTOMLEFT, Color(1.0f, 1.0f, 0.25f));
    mScoreText->setColor(C_BOTTOMRIGHT, Color(1.0f, 1.0f, 0.25f));
    uiRoot->addChild(mScoreText);
    
    mHiScoreText = new Text();
    mHiScoreText->setFont(mCache->getResource<Font>("Fonts/BlueHighway.ttf"), 17);
    mHiScoreText->setAlignment(HA_RIGHT, VA_TOP);
    mHiScoreText->setPosition(-5, 5);
    mHiScoreText->setColor(C_BOTTOMLEFT, Color(1.0f, 1.0f, 0.25f));
    mHiScoreText->setColor(C_BOTTOMRIGHT, Color(1.0f, 1.0f, 0.25f));
    uiRoot->addChild(mHiScoreText);
    
    mMessage = new Text();
    mMessage->setFont(mCache->getResource<Font>("Fonts/BlueHighway.ttf"), 17);
    mMessage->setColor(Color(1.0f, 0.0f, 0.0f));
    mMessage->setAlignment(HA_CENTER, VA_CENTER);
    mMessage->setPosition(0, -height * 2);
    uiRoot->addChild(mMessage);
    
    mHealthBar = new BorderImage();
    mHealthBar->setTexture(mCache->getResource<Texture2D>("Textures/HealthBarBorder.png"));
    mHealthBar->setAlignment(HA_CENTER, VA_TOP);
    mHealthBar->setPosition(0, 8);
    mHealthBar->setSize(120, 20);
    SharedPtr<BorderImage> healthInside(new BorderImage());
    healthInside->setTexture(mCache->getResource<Texture2D>("Textures/HealthBarInside.png"));
    healthInside->setPosition(2, 2);
    healthInside->setSize(116, 16);
    mHealthBar->addChild(healthInside);
    uiRoot->addChild(mHealthBar);
}

void Game::createScene()
{
    mScene = mEngine->createScene("NinjaSnowWar", BoundingBox(-100000.0f, 100000.f));
    mScene->addComponentFactory(new GameObjectFactory());
    
    // If not a multiplayer client, load the scene contents from file
    if (!mClient)
    {
        SharedPtr<File> sceneFile = mCache->getFile(GameConfig::get("Game/LevelName"));
        mScene->loadXML(*sceneFile);
        // Create the camera if not server
        if (!mServer)
            createCamera();
    }
}

void Game::createCamera()
{
    // Note: camera is local, so it will not be affected by net replication
    Entity* cameraEntity = mScene->createEntity("Camera", true);
    mCamera = cameraEntity->createComponent<Camera>();
    Camera* camera = mCamera.getPtr();
    Renderer* renderer = mEngine->getRenderer();
    if (renderer)
        camera->setAspectRatio((float)renderer->getWidth() / (float)renderer->getHeight());
    // View distance is optional
    try
    {
        camera->setNearClip(GameConfig::getReal("Engine/ViewStart"));
        camera->setFarClip(GameConfig::getReal("Engine/ViewEnd"));
    }
    catch (...) {}
}

void Game::startGame()
{
    // Do not start game on your own in client mode
    if (mClient)
        return;
    
    // Set gameon flag
    mGameOn = true;
    
    // Reset game parameters
    mEnemies = GameConfig::getInt("Game/Enemies");
    mPowerUps = GameConfig::getInt("Game/PowerUps");
    mEnemySpawnTime = GameConfig::getReal("Game/EnemySpawnRate");
    mPowerUpSpawnTime = GameConfig::getReal("Game/PowerUpSpawnRate");
    mIncrementCount = GameConfig::getInt("Game/IncrementEach");
    
    // Reset AI difficulty
    AIController::setup();
    
    // Clear all previous game objects
    std::map<EntityID, SharedPtr<Entity> > entities = mScene->getEntities();
    for (std::map<EntityID, SharedPtr<Entity> >::iterator i = entities.begin(); i != entities.end(); ++i)
    {
        if (i->second->getName().find("Obj") != std::string::npos)
            mScene->removeEntity(i->second->getID());
    }
    mPlayers.clear();
    
    // In singleplayer, create the lone player ninja & player structure, as well as a hiscore entry
    if (!mServer)
    {
        mFirstFrame = true;
        setMessage("");
        
        Entity* entity = mScene->createEntity("ObjPlayer");
        Ninja* ninja = entity->createComponent<Ninja>();
        ninja->setMaxHealth(GameConfig::getInt("Game/PlayerHealth"));
        ninja->create(GameConfig::getVector3("Game/PlayerStart"));
        ninja->setSide(SIDE_PLAYER);
        
        Player newPlayer;
        newPlayer.mScore = 0;
        newPlayer.mEntity = entity;
        mPlayers.push_back(newPlayer);
        
        HiScore newHiScore;
        newHiScore.mScore = 0;
        mHiScores.push_back(newHiScore);
    }
}

void Game::endGame()
{
    mGameOn = false;
    setMessage("Press Fire or Jump to restart!");
}

void Game::loadGame()
{
    // Do not load game in multiplayer mode
    if ((mClient) || (mServer))
        return;
    
    if (mPaused)
        return;
    
    if (!fileExists(applicationDir + "Save.dat"))
        return;
    
    // Load the scene
    File saveFile(applicationDir + "Save.dat", FILE_READ);
    mScene->load(saveFile);
    
    // Load global game state
    mPlayers.clear();
    Player newPlayer;
    newPlayer.mScore = saveFile.readInt();
    
    mGameOn = saveFile.readBool();
    mFirstFrame = saveFile.readBool();
    mMessage->setText(saveFile.readString());
    mEnemies = saveFile.readInt();
    mPowerUps = saveFile.readInt();
    mEnemySpawnTime = saveFile.readFloat();
    mPowerUpSpawnTime = saveFile.readFloat();
    mIncrementCount = saveFile.readInt();
    mControls.read(saveFile);
    AIController::load(saveFile);
    
    mPrevControls = mControls;
    
    // Reacquire the player entity if possible
    Entity* playerEntity = mScene->getEntity("ObjPlayer");
    newPlayer.mEntity = playerEntity;
    mPlayers.push_back(newPlayer);
    
    // Check singleplayer hiscore
    if (mPlayers[0].mScore > mHiScores[0].mScore)
        mHiScores[0].mScore = mPlayers[0].mScore;
    
    // Update the camera position
    updateCamera();
}

void Game::saveGame()
{
    // Do not save game in multiplayer mode
    if ((mClient) || (mServer))
        return;
    
    if ((mPaused) || (!mGameOn))
        return;
    
    // Save the scene
    File saveFile(applicationDir + "Save.dat", FILE_WRITE);
    mScene->save(saveFile);
    
    // Save global game state
    saveFile.writeInt(mPlayers[0].mScore);
    saveFile.writeBool(mGameOn);
    saveFile.writeBool(mFirstFrame);
    saveFile.writeString(mMessage->getText());
    saveFile.writeInt(mEnemies);
    saveFile.writeInt(mPowerUps);
    saveFile.writeFloat(mEnemySpawnTime);
    saveFile.writeFloat(mPowerUpSpawnTime);
    saveFile.writeInt(mIncrementCount);
    mControls.write(saveFile);
    AIController::save(saveFile);
    
    setMessage("GAME SAVED");
    mSaveMessageTime = 0.0f;
}

void Game::handleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    
    float timeStep = eventData[P_TIMESTEP].getFloat();
    
    // Read input
    getControls();
}

void Game::handlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;
    
    float timeStep = eventData[P_TIMESTEP].getFloat();
    
    // Update camera to player position
    updateCamera();
    
    // Update status panel
    updateStatus(timeStep);
}

void Game::handlePreStep(StringHash eventType, VariantMap& eventData)
{
    using namespace PhysicsPreStep;
    
    float timeStep = eventData[P_TIMESTEP].getFloat();
    
    // Create new objects
    spawnObjects(timeStep);
    
    // Singleplayer: set controls
    // (multiplayer client sets controls through the SetControls & ControlsPlayback events only)
    if ((!mServer) && (!mClient))
    {
        // Check new game start
        if (!mGameOn)
        {
            if ((mControls.isPressed(CTRL_FIRE, mPrevControls)) || (mControls.isPressed(CTRL_JUMP, mPrevControls)))
                startGame();
        }
        
        Entity* playerEntity = mPlayers[0].mEntity.getPtr();
        if (playerEntity)
        {
            Ninja* player = playerEntity->getComponent<Ninja>();
            if (player)
            {
                // First frame shoot/jump prevention hack
                if (mFirstFrame)
                {
                    player->mPrevControls = mControls;
                    mFirstFrame = false;
                }
                
                player->mControls = mControls;
            }
        }
    }
    
    mPrevControls = mControls;
    
    // Multiplayer server: set controls for clients and handle respawn
    if (mServer)
    {
        for (unsigned i = 0; i < mPlayers.size(); ++i)
        {
            Connection* connection = mPlayers[i].mConnection;
            
            if (mPlayers[i].mEntity.isExpired())
            {
                if (connection->getControls().isPressed(CTRL_FIRE, mPlayers[i].mPrevControls))
                {
                    mPlayers[i].mScore = 0;
                    mPlayers[i].mEntity = spawnRemotePlayer(connection, false);
                }
            }
            else
            {
                Entity* entity = mPlayers[i].mEntity.getPtr();
                Ninja* player = entity->getComponent<Ninja>();
                if (player)
                    player->mControls = connection->getControls();
            }
            
            mPlayers[i].mPrevControls = connection->getControls();
        }
    }
}

void Game::handleGameEvent(StringHash eventType, VariantMap& eventData)
{
    using namespace Die;
    
    GameObject* obj = static_cast<GameObject*>(eventData[P_OBJECT].getPtr());
    
    if (eventType == EVENT_DIE)
    {
        if (obj->getSide() != SIDE_PLAYER)
        {
            EntityID damageOrigin = obj->getLastDamageOrigin();
            Entity* entity = mScene->getEntity(damageOrigin);
            if (entity)
            {
                // Check who of the players gets points, if any
                for (unsigned i = 0; i < mPlayers.size(); ++i)
                {
                    if (mPlayers[i].mEntity.getPtr() == entity)
                    {
                        mPlayers[i].mScore += obj->getPoints();
                        
                        // Check for updating hiscore, or adding new hiscore entry
                        bool hiScoreFound = false;
                        for (unsigned j = 0; j < mHiScores.size(); ++j)
                        {
                            if (mHiScores[j].mName == mPlayers[i].mName)
                            {
                                if (mPlayers[i].mScore > mHiScores[j].mScore)
                                    mHiScores[j].mScore = mPlayers[i].mScore;
                                
                                hiScoreFound = true;
                                break;
                            }
                        }
                        if (!hiScoreFound)
                        {
                            HiScore newHiScore;
                            newHiScore.mName = mPlayers[i].mName;
                            newHiScore.mScore = mPlayers[i].mScore;
                            mHiScores.push_back(newHiScore);
                        }
                        
                        std::sort(mHiScores.begin(), mHiScores.end(), compareHiScores);
                        
                        // Multiplayer: put score & hiscores to synced entity properties for replication
                        if (mServer)
                        {
                            entity->setProperty(PROP_SCORE, Variant(mPlayers[i].mScore), true);
                            
                            VectorBuffer hiScoreBuffer;
                            hiScoreBuffer.writeVLE(mHiScores.size());
                            for (unsigned j = 0; j < mHiScores.size(); ++j)
                            {
                                hiScoreBuffer.writeString(mHiScores[j].mName);
                                hiScoreBuffer.writeInt(mHiScores[j].mScore);
                            }
                            
                            Entity* hiScoreEntity = mScene->getEntity("HiScores");
                            if (!hiScoreEntity)
                                hiScoreEntity = mScene->createEntity("HiScores");
                            hiScoreEntity->setProperty(PROP_HISCORES, Variant(hiScoreBuffer.getBuffer()), true);
                        }
                        
                        break;
                    }
                }
            }
            if (obj->getType() == Ninja::getTypeStatic())
                makeHarder();
        }
    }
    
    // End of singleplayer game (note: multiplayer never ends)
    if (eventType == EVENT_REMOVE)
    {
        if ((!mClient) && (!mServer))
        {
            if (obj->getEntity() == mPlayers[0].mEntity.getPtr())
                endGame();
        }
    }
}

void Game::handleClientIdentity(StringHash eventType, VariantMap& eventData)
{
    // When a client joins and tells identity, assign to the NinjaSnowWar scene
    using namespace ClientIdentity;
    
    Connection* connection = static_cast<Connection*>(eventData[P_CONNECTION].getPtr());
    mServer->setClientScene(connection, mScene);
}

void Game::handleJoinedScene(StringHash eventType, VariantMap& eventData)
{
    // The multiplayer scene does not include camera, so create it now
    createCamera();
}

void Game::handleControlsUpdate(StringHash eventType, VariantMap& eventData)
{
    // Set controls to be sent over network
    mClient->setControls(mControls);
    
    // Also set the controls immediately for predicted game logic
    Entity* playerEntity = mScene->getEntity(mClientEntityID);
    if (playerEntity)
    {
        Ninja* player = playerEntity->getComponent<Ninja>();
        RigidBody* body = playerEntity->getComponent<RigidBody>();
        if (player)
            player->mControls = mControls;
        
        // Set player position for entity relevancy calculations
        if (body)
            mClient->setPosition(body->getPosition());
    }
}

void Game::handleControlsPlayback(StringHash eventType, VariantMap& eventData)
{
    using namespace ControlsPlayback;
    
    Entity* playerEntity = mScene->getEntity(mClientEntityID);
    if (playerEntity)
    {
        Ninja* player = playerEntity->getComponent<Ninja>();
        if (player)
        {
            player->mPrevControls = player->mControls;
            player->mControls.mButtons = eventData[P_BUTTONS].getInt();
            player->mControls.mYaw = eventData[P_YAW].getFloat();
            player->mControls.mPitch = eventData[P_PITCH].getFloat();
        }
    }
}

void Game::handleClientJoined(StringHash eventType, VariantMap& eventData)
{
    if (!mServer)
        return;
    
    // If beginning with one player, reset the game
    if (mPlayers.empty())
    {
        LOGINFO("Resetting the game");
        startGame();
    }
    
    // Create ninja for new player and send back spawn event
    using namespace ClientJoinedScene;
    
    Connection* connection = static_cast<Connection*>(eventData[P_CONNECTION].getPtr());
    
    spawnRemotePlayer(connection, true);
}

void Game::handleClientLeft(StringHash eventType, VariantMap& eventData)
{
    if (!mServer)
        return;
    
    // Remove player's ninja if exists
    using namespace ClientLeftScene;
    
    Connection* connection = static_cast<Connection*>(eventData[P_CONNECTION].getPtr());
    for (unsigned i = 0; i < mPlayers.size(); ++i)
    {
        if (mPlayers[i].mConnection == connection)
        {
            Entity* entity = mPlayers[i].mEntity.getPtr();
            if (entity)
            {
                // Perform seppuku (?)
                Ninja* ninja = entity->getComponent<Ninja>();
                if (ninja)
                    ninja->setHealth(0);
            }
            mPlayers.erase(mPlayers.begin() + i);
            break;
        }
    }
}

void Game::handlePlayerSpawned(StringHash eventType, VariantMap& eventData)
{
    if (!mClient)
        return;
    
    using namespace PlayerSpawned;
    
    mClientEntityID = eventData[P_ENTITYID].getInt();
}

void Game::getControls()
{
    Input* input = mEngine->getInput();
    
    if (input->getKeyPress(KEY_F1))
        toggleDebugOverlay();
    if (input->getKeyPress(KEY_F2))
        toggleDebugGeometry();
    
    // Toggle edge filter (deferred only)
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
    
    // Game control keys
    if ((input->getKeyPress('P')) || (input->getKeyPress(KEY_PAUSE)))
        togglePause();
    
    // Packet loss test
    if ((input->getKeyPress('X')) && (mClient) && (mClient->getServerConnection()))
    {
        static const float lossRatios[3] =
        {
            0.0f, 0.33f, 0.66f
        };
        
        ++simulatePacketLoss;
        if (simulatePacketLoss > 2)
            simulatePacketLoss = 0;
        
        mClient->getServerConnection()->getPeer()->setSimulatedPacketLoss(lossRatios[simulatePacketLoss]);
    }
    
    // Latency test
    if ((input->getKeyPress('Z')) && (mClient) && (mClient->getServerConnection()))
    {
        static const unsigned latencyValues[3] =
        {
            0, 100, 250
        };
        
        ++simulateLatency;
        if (simulateLatency > 2)
            simulateLatency = 0;
        
        mClient->getServerConnection()->getPeer()->setSimulatedLatency(latencyValues[simulateLatency]);
    }
    
    // Player controls
    if (!mServer)
    {
        mControls.set(CTRL_ALL, false);
        if ((!mFirstFrame) && (!mPaused))
        {
            if (input->getKeyDown('W')) mControls.set(CTRL_UP);
            if (input->getKeyDown('S')) mControls.set(CTRL_DOWN);
            if (input->getKeyDown('A')) mControls.set(CTRL_LEFT);
            if (input->getKeyDown('D')) mControls.set(CTRL_RIGHT);
            if (input->getKeyDown(KEY_CTRL)) mControls.set(CTRL_FIRE);
            if (input->getKeyDown(' ')) mControls.set(CTRL_JUMP);
            if (input->getMouseButtonDown(MOUSEB_LEFT)) mControls.set(CTRL_FIRE);
            if (input->getMouseButtonDown(MOUSEB_RIGHT)) mControls.set(CTRL_JUMP);
            mControls.mYaw += mSensitivity * (float)input->getMouseMoveX();
            mControls.mPitch += mSensitivity * (float)input->getMouseMoveY();
            mControls.mPitch = clamp(mControls.mPitch, -60.0f, 60.0f);
        }
    }
}

void Game::toggleDebugOverlay()
{
    mEngine->getDebugHud()->toggleAll();
}

void Game::toggleDebugGeometry()
{
    mEngine->setDebugDrawMode(mEngine->getDebugDrawMode() ^ DEBUGDRAW_PHYSICS);
}

void Game::togglePause()
{
    // Can not pause in multiplayer
    if ((mClient) || (mServer))
        return;
    
    mPaused = !mPaused;
    
    if (mGameOn)
    {
        if (mPaused)
            setMessage("PAUSED");
        else
            setMessage("");
    }
}

void Game::makeHarder()
{
    AIController::makeHarder();
    
    // After certain amount of kills, increase number of simultaneous enemies
    mIncrementCount--;
    if (mIncrementCount <= 0)
    {
        mIncrementCount = GameConfig::getInt("Game/IncrementEach");
        if (mEnemies < GameConfig::getInt("Game/MaxEnemies"))
          mEnemies++;
    }
}

void Game::spawnObjects(float timeStep)
{
    // No spawning after game has ended, or if this is a multiplayer client
    if ((!mGameOn) || (mClient))
        return;
    
    mEnemySpawnTime -= timeStep;
    mPowerUpSpawnTime -= timeStep;
  
    // Time to spawn a new powerup?
    if (mPowerUpSpawnTime <= 0)
    {
        mPowerUpSpawnTime = GameConfig::getReal("Game/PowerUpSpawnRate");
        
        // Check for combined amount of crates & potions
        if ((getObjectCount(SnowCrate::getTypeStatic()) + getObjectCount(Potion::getTypeStatic())) < mPowerUps)
        {
            float maxOffset = GameConfig::getReal("Game/PowerUpSpawnOffset");
            float xOffset = random(maxOffset * 2.0f) - maxOffset;
            float zOffset = random(maxOffset * 2.0f) - maxOffset;
            
            Vector3 position(xOffset, GameConfig::getReal("Game/PowerUpSpawnHeight"), zOffset);
            Entity* entity = mScene->createEntity("ObjCrate");
            GameObject* obj = entity->createComponent<SnowCrate>();
            obj->create(position);
        }
    }
    
    // Time to spawn a new enemy ninja?
    if (mEnemySpawnTime <= 0)
    {
        mEnemySpawnTime = GameConfig::getReal("Game/EnemySpawnRate");
        
        if (getObjectCount(Ninja::getTypeStatic(), SIDE_ENEMY) < mEnemies)
        {
            float maxOffset = GameConfig::getReal("Game/EnemySpawnOffset");
            float offset = random(maxOffset * 2.0f) - maxOffset;
            // Random north/east/south/west direction
            int dir = rand() & 3;
            dir *= 90;
            Quaternion q((float)dir, Vector3::sUp);
            Vector3 position(q * (GameConfig::getVector3("Game/EnemySpawnPosition") + Vector3(offset, 0, 0)));
            
            Entity* entity = mScene->createEntity("ObjEnemy");
            GameObject* obj = entity->createComponent<Ninja>();
            obj->create(position, q);
            obj->setSide(SIDE_ENEMY);
            obj->getBody()->setLinearVelocity(q * GameConfig::getVector3("Game/EnemySpawnVelocity"));
        }
    }
}

Entity* Game::spawnRemotePlayer(Connection* connection, bool newPlayer)
{
    Entity* entity = mScene->createEntity("ObjRemotePlayer");
    entity->setOwner(connection);
    Ninja* ninja = entity->createComponent<Ninja>();
    ninja->setMaxHealth(GameConfig::getInt("Game/PlayerHealth"));
    Vector3 startPos = GameConfig::getVector3("Game/PlayerStart");
    startPos.mX += random(1000.0f) - 500.0f;
    startPos.mZ += random(1000.0f) - 500.0f;
    ninja->create(startPos);
    ninja->setSide(SIDE_PLAYER);
    
    if (newPlayer)
    {
        Player newPlayer;
        newPlayer.mScore = 0;
        newPlayer.mEntity = entity;
        newPlayer.mConnection = connection;
        newPlayer.mName = connection->getUserName();
        mPlayers.push_back(newPlayer);
    }
    else
    {
        // Respawn: set the firebutton held down in the controls to prevent first frame shoot
        ninja->mControls.mButtons = CTRL_FIRE;
        ninja->mPrevControls.mButtons = CTRL_FIRE;
    }
    
    using namespace PlayerSpawned;
    
    VariantMap eventData;
    eventData[P_ENTITYID] = entity->getID();
    mScene->sendRemoteEvent(EVENT_PLAYERSPAWNED, eventData, connection);
    
    return entity;
}

void Game::setupCamera()
{
    GameConfig::setSection("Camera");
    
    mCameraMinDist = GameConfig::getReal("MinDistance");
    mCameraMaxDist = GameConfig::getReal("MaxDistance");
    mCameraSafetyDist = GameConfig::getReal("SafetyDistance");
    mCameraRayLength = GameConfig::getReal("RayLength");
    
    GameConfig::setSection();
}

void Game::setMessage(const std::string& text)
{
    if (mMessage)
        mMessage->setText(text);
}

void Game::updateStatus(float timeStep)
{
    if ((!mScene) || (!mScoreText) || (!mHiScoreText) || (!mHealthBar))
        return;
    
    // Singleplayer status update
    if ((!mClient) && (!mServer))
    {
        mScoreText->setText("Score " + toString(mPlayers[0].mScore));
        if (mHiScores.size())
            mHiScoreText->setText("Hiscore " + toString(mHiScores[0].mScore));
        Entity* playerEntity = mPlayers[0].mEntity.getPtr();
        if (playerEntity)
        {
            GameObject* player = playerEntity->getDerivedComponent<GameObject>();
            if (player)
                mHealthBar->getChild(0)->setWidth((116 * player->getHealth()) / player->getMaxHealth());
        }
    }
    else
    {
        if (mClient)
        {
            // Get score/health/maxhealth from the player entity, if it exists
            Entity* playerEntity = mScene->getEntity(mClientEntityID);
            if (playerEntity)
            {
                int clientScore = playerEntity->getProperty(PROP_SCORE).getInt();
                mScoreText->setText("Score " + toString(clientScore));
                GameObject* player = playerEntity->getDerivedComponent<GameObject>();
                if (player)
                    mHealthBar->getChild(0)->setWidth((116 * player->getHealth()) / player->getMaxHealth());
            }
            
            // Get the hiscores from the hiscores entity, if it exists
            //! \todo It is wasteful to do this each frame even if the hiscores have not changed
            Entity* hiScoresEntity = mScene->getEntity("HiScores");
            if ((hiScoresEntity) && (hiScoresEntity->hasProperty(PROP_HISCORES)))
            {
                std::string text;
                const std::vector<unsigned char>& hiScoreVector = hiScoresEntity->getProperty(PROP_HISCORES).getBuffer();
                if (hiScoreVector.size())
                {
                    MemoryBuffer hiScoreBuffer(&hiScoreVector[0], hiScoreVector.size());
                    unsigned numHiScores = hiScoreBuffer.readVLE();
                    mHiScores.resize(numHiScores);
                    for (unsigned i = 0; i < numHiScores; ++i)
                    {
                        mHiScores[i].mName = hiScoreBuffer.readString();
                        mHiScores[i].mScore = hiScoreBuffer.readInt();
                        
                        text += mHiScores[i].mName + " " + toString(mHiScores[i].mScore) + "\n";
                    }
                    
                    mHiScoreText->setText(text);
                }
            }
            
            static float fileTransferAcc = 0.0f;
            fileTransferAcc += timeStep;
            if (fileTransferAcc > 0.1f)
            {
                fileTransferAcc -= 0.1f;
                mMessage->setText(mClient->getFileTransferStatus());
            }
        }
    }
    
    // If the save message is being displayed, remove it after a set time
    if (mMessage->getText() == "GAME SAVED")
    {
        mSaveMessageTime += timeStep;
        if (mSaveMessageTime > 1.0f)
            setMessage("");
    }
}

void Game::updateCamera()
{
    if (!mScene)
        return;
    if (mServer)
        return;
    
    Camera* camera = 0;
    if (mCamera.isExpired())
    {
        // Reacquire the camera pointer if necessary
        Entity* cameraEntity = mScene->getEntity("Camera");
        if (cameraEntity)
        {
            mCamera = cameraEntity->getComponent<Camera>();
            camera = mCamera.getPtr();
            if (camera)
            {
                // Reset aspect ratio, might have changed
                Renderer* renderer = mEngine->getRenderer();
                if (renderer)
                    camera->setAspectRatio((float)renderer->getWidth() / (float)renderer->getHeight());
            }
        }
    }
    else
        camera = mCamera.getPtr();
    
    if (!camera)
        return;
    
    // Player tracking
    Entity* playerEntity = 0;
    if ((!mClient) && (!mServer))
        playerEntity = mPlayers[0].mEntity.getPtr();
    else
        playerEntity = mScene->getEntity(mClientEntityID);
    
    if (!playerEntity)
        return;
    RigidBody* body = playerEntity->getComponent<RigidBody>();
    Ninja* player = playerEntity->getComponent<Ninja>();
    if ((!body) || (!player))
        return;
    
    Vector3 pos = body->getWorldPosition();
    // Use yaw & pitch from own controls for immediate response
    Quaternion dir = Quaternion::sIdentity;
    dir = dir * Quaternion(mControls.mYaw, Vector3::sUp);
    dir = dir * Quaternion(mControls.mPitch, Vector3::sRight);
    // Force the player character rotation, so that there is no stuttering
    bool alive = player->getHealth() > 0;
    if (alive)
    {
        Quaternion rot(mControls.mYaw, Vector3::sUp);
        body->setRotation(rot);
        if (mClient)
            body->Node::setRotation(rot); // This disables client-side rotation smoothing
    }
    
    Vector3 aimPoint = pos + Vector3(0,100,0);
    Vector3 minDist = aimPoint + dir * Vector3(0, 0, -mCameraMinDist);
    Vector3 maxDist = aimPoint + dir * Vector3(0, 0, -mCameraMaxDist);
    
    // Collide camera ray with static objects
    Vector3 rayDir = (maxDist - minDist).getNormalized();
    float rayDistance = mCameraMaxDist - mCameraMinDist + mCameraSafetyDist;
    std::vector<PhysicsRaycastResult> result;
    mScene->getExtension<PhysicsWorld>()->raycast(Ray(minDist, rayDir), result, rayDistance, 2);
    if (result.size())
        rayDistance = min(rayDistance, result[0].mDistance - mCameraSafetyDist);
    
    camera->setPosition(minDist + rayDir * rayDistance);
    camera->setRotation(dir);
    
    Audio* audio = mEngine->getAudio();
    if (audio)
    {
        audio->setListenerPosition(pos);
        audio->setListenerRotation(dir);
    }
}

int Game::getObjectCount(ShortStringHash type, int side)
{
    int count = 0;
    
    const std::map<EntityID, SharedPtr<Entity> >& entities = mScene->getEntities();
    for (std::map<EntityID, SharedPtr<Entity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
    {
        GameObject* object = i->second->getDerivedComponent<GameObject>();
        if ((object) && (object->getType() == type) && ((side == SIDE_UNDEFINED) || (object->getSide() == side)))
            ++count;
    }
    
    return count;
}
