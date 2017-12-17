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

#include <Urho3D/Scene/Component.h>
#include <Urho3D/Core/HelperThread.h>
#include <Urho3D/Graphics/Texture2D.h>

using namespace Urho3D;
namespace Urho3D
{
class Node;
class Texture2D;
class Camera;
class RenderSurface;
class BoundingBox;
class Material;
class StaticModel;
class Viewport;
class DebugRenderer;
}

//=============================================================================
//=============================================================================
URHO3D_EVENT(E_TRIANGLEINFO, TriangleInfo)
{
    URHO3D_PARAM(P_TRICNT, TriCnt);  // unsigned
}

URHO3D_EVENT(E_TRIANGLECOMPLETED, TriangleCompleted)
{
    //URHO3D_PARAM(P_TRICNT, TriCnt);  // unsigned
}

URHO3D_EVENT(E_INDIRECTCOMPLETED, IndirectCompleted)
{
    URHO3D_PARAM(P_NODE, Node);      // node ptr
}

//=============================================================================
//=============================================================================
const unsigned DEFAULT_INDIRECT_IMAGE_SIZE = 64;

//=============================================================================
//=============================================================================
class Lightmap : public Component
{
    URHO3D_OBJECT(Lightmap, Component);
    
public:
    Lightmap(Context* context);
    virtual ~Lightmap();
    
    static void RegisterObject(Context* context);

    void BeginIndirectLighting(const String &filepath, unsigned imageSize=DEFAULT_INDIRECT_IMAGE_SIZE);

    SharedPtr<Image> GetIndirectLightImage() { return indirectLightImage_; }

    void SetLumaOutputColor(bool bset)       { lumaOutputColor_ = bset; }
    bool GetLumaOutputColor() const          { return lumaOutputColor_; }

    // dbg
    void DrawDebugGeometry(DebugRenderer* debug, const Color &color, bool depthTest, unsigned &triIdx);

protected:
    void InitBakeLightSettings(const BoundingBox& worldBoundingBox);
    void InitIndirectLightSettings();
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void HandleEndViewRender(StringHash eventType, VariantMap& eventData);

    unsigned GetState();
    void SetState(unsigned state);
    void SetupGeomData();
    void SetupPixelData();
    void ForegroundProcess();
    void BackgroundBuildPixelData(void *data);
    void SendTriangleInfoMsg();
    void SendTriangleCompleteMsg();
    void SendIndirectCompleteMsg();
    void SetCameraPosRotForCapture(unsigned idx);

    // indirect background solidangle computation
    void BackgroundProcessIndirectImage(void *data);
    void QueueIndirectImage(unsigned idx, SharedPtr<Image> image);
    SharedPtr<Image> GetFrontIndirectQueueImage(unsigned &idx);
    void PopFrontIndirectQueue();
    void CalculateIrradiance(unsigned idx, SharedPtr<Image> scrnImage);
    void FinalizeIndirectImage();
    void ProcessIndirectRenderSurface(unsigned parserIdx);
    void SmoothAndDilate(SharedPtr<Image> image, bool dilate=true);

protected:
    WeakPtr<StaticModel>    staticModel_;
    String                  filepath_;

    SharedPtr<Image>        indirectLightImage_;
    float                   solidangle_;

    unsigned                texWidth_;
    unsigned                texHeight_;
    bool                    saveFile_;
    bool                    lumaOutputColor_;

    Mutex                   mutexStateLock_;
    Mutex                   mutexIndirectQueueLock_;

    unsigned                stateProcess_;
    unsigned                curPixelIdx_;
    Timer                   timerIndirect_;

    SharedPtr<HelperThread<Lightmap> > threadProcess_;

private:
    enum StateType
    {
        State_UnInit,
        State_CreateGeomData,
        State_CreatePixelData,
        State_IndirectLightSetup,
        State_IndirectLightBegin,
        State_IndirectLightProcess,
        State_IndirectLightWaitBackground,
        State_IndirectLightEnd
    };

    struct IndirectData
    {
        SharedPtr<Image> image_;
        unsigned         idx_;
    };
    Vector<IndirectData>    indirectDataList_;

    struct CaptureData
    {
        WeakPtr<Node>           camNode_;
        WeakPtr<Camera>         camera_;
        SharedPtr<Viewport>     viewport_;
        SharedPtr<Texture2D>    renderTexture_;
        WeakPtr<RenderSurface>  renderSurface_;

        unsigned                pixelIdx_;
        unsigned                triIdx_;
        bool                    isStopped_;
    };

    Vector<CaptureData>         captureParser_;
    unsigned                    numCaptureParsers_;
    unsigned                    pixelsCompleted_;

    struct GeomData
    {
        Vector3 pos_;
        Vector3 normal_;
        Vector2 uv_;
    };
    struct PixelPoint
    {
        unsigned    triIdx_;
        Vector3     pos_;
        Vector3     normal_;
        IntVector2  iuv_;
        Color       col_;
    };

    struct TriangleData
    {
        unsigned pixelCnt_;
        IntVector2 minXY_;
        IntVector2 maxXY_;
    };

    PODVector<GeomData> geomData_;
    PODVector<PixelPoint> pixelData_;
    PODVector<TriangleData> triangleData_;
    SharedArrayPtr<unsigned short> indexBuffShort_;
    SharedArrayPtr<unsigned> indexBuff_;
    unsigned numIndices_;
    unsigned indexSize_;
    String name_;

    //=============================================================================
    // http://answers.unity3d.com/questions/383804/calculate-uv-coordinates-of-3d-point-on-plane-of-m.html
    // describes a barycentric calculation for 3D using proportional area calculation
    //=============================================================================
    static inline Vector3 Barycentric(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2, const Vector2 &vp)
    {
        Vector3 bary(Vector3::ONE);
        float area = CrossProduct(v1 - v0, v2 - v0);

        if (area > M_EPSILON)
        {
            // edge seg
            Vector2 e0 = v0 - vp;
            Vector2 e1 = v1 - vp;
            Vector2 e2 = v2 - vp;

            // the subscripts a0, a1, and a2 are derived 
            // from the opposite subscripts of e0, e1, and e2
            float a0 = CrossProduct(e1, e2) / area;
            float a1 = CrossProduct(e2, e0) / area;
            float a2 = CrossProduct(e0, e1) / area;

            bary = Vector3(a0, a1, a2);
        }

        return bary;
    }

    // missing in Urh3D::Vector2
    static inline float CrossProduct(const Vector2 &a, const Vector2 &b)
    {
        return Abs(a.x_ * b.y_ - a.y_ * b.x_);
    }

    //=============================================================================
    // **note: proportinal comparator - the sum of the three segment areas is equal to the area of triangle, 
    // hence you can also prove that the sum of the barycentric is equal to one, if it's inside the triangle
    //=============================================================================
    static inline bool BaryInsideTriangle(const Vector3 &bary)
    {
        return (bary.x_ + bary.y_ + bary.z_) < (1.0f + M_EPSILON);
    }

};
