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

#pragma once
#include <Urho3D/Core/Object.h>

using namespace Urho3D;
namespace Urho3D
{
class Scene;
class StaticModel;
}

class Lightmap;

//=============================================================================
//=============================================================================
URHO3D_EVENT(E_LIGHTMAPSTATUS, LightmapStatus)
{
    URHO3D_PARAM(P_TOTAL, TotalCnt);        // unsigned
    URHO3D_PARAM(P_COMPLETED, CompleteCnt); // unsigned
}

URHO3D_EVENT(E_INDIRECTLIGHTSTATUS, IndirectLightStatus)
{
    URHO3D_PARAM(P_TITLE, Title);           // String
    URHO3D_PARAM(P_TOTAL, TotalCnt);        // unsigned
    URHO3D_PARAM(P_COMPLETED, CompleteCnt); // unsigned
    URHO3D_PARAM(P_REMOVEMSG, RemoveMsg);   // bool
}

//=============================================================================
//=============================================================================
class LightmapCreator : public Object
{
    URHO3D_OBJECT(LightmapCreator, Object);

public:
    LightmapCreator(Context* context);
    virtual ~LightmapCreator();

    void Init(Scene *scene, const String& outputPath);
    void GenerateLightmaps();
    void ProcessAdditionalLightBounce();

protected:
    void CreateTechniquesToAvoidList();
    unsigned ParseModelsInScene();
    bool HasTexCoord2(StaticModel *staticModel);
    void EnableLightsInScene(bool enable);
    void SetupIndirectProcess();
    void SetupBakeIndirectProcess();
    void SwitchToLightmapTechnique();

    void QueueNodesForLightBaking();
    void QueueNodesForIndirectLightProcess();
    void BakeDirectLight(Node *node);
    void BakeIndirectLight(Node *node);

    void RemoveCompletedNode(Node *node);
    void SendEventMsg();
    void RestoreModelSettigs();
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void HandleBakeLightBuildEvent(StringHash eventType, VariantMap& eventData);
    void SendIndirectLightingStatus(bool removemsg=false);
    void HandleTriangleInfoEvent(StringHash eventType, VariantMap& eventData);
    void HandleTriangleCompletedEvent(StringHash eventType, VariantMap& eventData);
    void HandleIndirectCompletedEvent(StringHash eventType, VariantMap& eventData);

protected:
    SharedPtr<Scene> scene_;
    String outputPath_;
    Color origFogColor_;

    PODVector<Node*> buildRequiredNodeList_;
    PODVector<Node*> origNodeList_;
    PODVector<Node*> processingNodeList_;

    unsigned totalCnt_;
    unsigned numProcessed_;
    unsigned maxNodesToProcess_;

    // state
    unsigned lightmapState_;

    // status
    unsigned totalTriangleCnt_;
    unsigned trianglesCompleted_;
    unsigned numObjectsCompletedIndirect_;

    bool firstLightBounce_;

private:
    enum LightMapState
    {
        LightMap_UnInit,
        LightMap_BakeDirectLight,
        LightMap_IndirectLightBegin,
        LightMap_IndirectLightProcessing,
        LightMap_SwapToLightmapTexture,
        LightMap_BakeIndirectLight,
        LightMap_RestoreScene,
        LightMap_Complete,
    };
};


