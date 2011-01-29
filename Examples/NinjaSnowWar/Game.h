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

#ifndef GAME_H
#define GAME_H

#include "EventListener.h"
#include "Component.h"
#include "Controls.h"
#include "GameObject.h"
#include "SharedPtr.h"
#include "Vector3.h"

#include <string>

class BorderImage;
class Camera;
class Client;
class Connection;
class DebugHud;
class Engine;
class Entity;
class ResourceCache;
class Scene;
class Server;
class Song;
class Text;

struct Player
{
    std::string mName;
    SharedPtr<Connection> mConnection;
    WeakPtr<Entity> mEntity;
    Controls mPrevControls;
    int mScore;
};

struct HiScore
{
    std::string mName;
    int mScore;
};

static bool compareHiScores(const HiScore& lhs, const HiScore& rhs)
{
    return lhs.mScore > rhs.mScore;
}

class Game : public EventListener
{
public:
    Game();
    ~Game();
    
    void run();
    
private:
    void init();
    void setupOptions();
    void setupCamera();
    void createOverlays();
    void createScene();
    void createCamera();
    void startGame();
    void endGame();
    void loadGame();
    void saveGame();
    void handleUpdate(StringHash eventType, VariantMap& eventData);
    void handlePreStep(StringHash eventType, VariantMap& eventData);
    void handlePostUpdate(StringHash eventType, VariantMap& eventData);
    void handleGameEvent(StringHash eventType, VariantMap& eventData);
    void handleClientIdentity(StringHash eventType, VariantMap& eventData);
    void handleJoinedScene(StringHash eventType, VariantMap& eventData);
    void handleControlsUpdate(StringHash eventType, VariantMap& eventData);
    void handleControlsPlayback(StringHash eventType, VariantMap& eventData);
    void handleClientJoined(StringHash eventType, VariantMap& eventData);
    void handleClientLeft(StringHash eventType, VariantMap& eventData);
    void handlePlaySound(StringHash eventType, VariantMap& eventData);
    void handlePlayerSpawned(StringHash eventType, VariantMap& eventData);
    void handleHealth(StringHash eventType, VariantMap& eventData);
    void handleScore(StringHash eventType, VariantMap& eventData);
    void handleHiScore(StringHash eventType, VariantMap& eventData);
    void getControls();
    void toggleDebugOverlay();
    void toggleDebugGeometry();
    void togglePause();
    void makeHarder();
    void spawnObjects(float timeStep);
    Entity* spawnRemotePlayer(Connection* connection, bool newPlayer);
    void setMessage(const std::string& text);
    void updateCamera();
    void updateStatus(float timeStep);
    int getObjectCount(ShortStringHash type, int side = SIDE_UNDEFINED);
    
    SharedPtr<Engine> mEngine;
    SharedPtr<ResourceCache> mCache;
    SharedPtr<Server> mServer;
    SharedPtr<Client> mClient;
    SharedPtr<Scene> mScene;
    WeakPtr<Camera> mCamera;
    SharedPtr<BorderImage> mSight;
    SharedPtr<BorderImage> mHealthBar;
    SharedPtr<Text> mScoreText;
    SharedPtr<Text> mHiScoreText;
    SharedPtr<Text> mMessage;
    
    std::vector<Player> mPlayers;
    std::vector<HiScore> mHiScores;
    
    EntityID mClientEntityID;
    std::string mUserName;
    
    Controls mControls;
    Controls mPrevControls;
    float mTimeScale;
    float mCameraMinDist;
    float mCameraMaxDist;
    float mCameraSafetyDist;
    float mCameraRayLength;
    float mSensitivity;
    bool mPaused;
    bool mGameOn;
    bool mFirstFrame;
    int mEnemies;
    int mPowerUps;
    int mIncrementCount;
    float mEnemySpawnTime;
    float mPowerUpSpawnTime;
    float mSaveMessageTime;
};

#endif // GAME_H
