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

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/GraphicsEvents.h>
#include <Urho3D/Graphics/View.h>
#include <Urho3D/Graphics/TextureCube.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/RenderSurface.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Technique.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/IO/Log.h>
#include <cstdio>

#include "Lightmap.h"

#include <Urho3D/DebugNew.h>
//=============================================================================
//=============================================================================
void ImageSmooth(SharedPtr<Image> image, SharedPtr<Image> outImage);
void ImageDilate(SharedPtr<Image> image, SharedPtr<Image> outImage);

//=============================================================================
//=============================================================================
#define FIXED_INDIRECT_TEXSIZE      64

// this is defined by default and helps when having multiple 
// captureParsers to pump images to the thread queue
#define IRRADIANCE_THREADED

//=============================================================================
//=============================================================================
Lightmap::Lightmap(Context* context)
    : Component(context)
    , stateProcess_(State_UnInit)
    , texWidth_(512)
    , texHeight_(512)
    , saveFile_(true)
    , numCaptureParsers_(4)
    , lumaOutputColor_(true)
{
}

Lightmap::~Lightmap()
{
    threadProcess_ = NULL;

    indirectDataList_.Clear();
}

void Lightmap::RegisterObject(Context* context)
{
    context->RegisterFactory<Lightmap>();
}

void Lightmap::BeginIndirectLighting(const String &filepath, unsigned imageSize)
{
    staticModel_ = node_->GetComponent<StaticModel>();

    if (staticModel_)
    {
        texWidth_ = texHeight_ = imageSize;
        filepath_ = filepath;

        // hemisphere solid angle
        // 360       = 4 * pi and 
        // M_MAX_FOV = x * pi 
        const float x = M_MAX_FOV * 4.0f/360.0f;
        solidangle_ = x * M_PI /(float)(FIXED_INDIRECT_TEXSIZE * FIXED_INDIRECT_TEXSIZE);

        // setup geom and pixel data on the 1st round
        if (GetState() == State_UnInit)
        {
            SetState(State_CreateGeomData);
            SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Lightmap, HandleUpdate));
        }
        else
        {
            SetState(State_IndirectLightBegin);
        }
    }
}

void Lightmap::InitIndirectLightSettings()
{
    // init
    captureParser_.Resize(numCaptureParsers_);
    curPixelIdx_ = 0;
    pixelsCompleted_ = 0;

    for ( unsigned i = 0; i < captureParser_.Size(); ++i )
    {
        captureParser_[i].camNode_ = GetScene()->CreateChild("RenderCamera");
        captureParser_[i].camera_ = captureParser_[i].camNode_->CreateComponent<Camera>();

        // using hemisphere - not quite, M_MAX_FOV = 160
        captureParser_[i].camera_->SetFov(M_MAX_FOV);
        captureParser_[i].camera_->SetNearClip(0.0001f);
        captureParser_[i].camera_->SetFarClip(300.0f);

        captureParser_[i].viewport_ = new Viewport(context_, GetScene(), captureParser_[i].camera_);
        captureParser_[i].viewport_->SetRenderPath(GetSubsystem<Renderer>()->GetViewport(0)->GetRenderPath());

        // Construct render surface 
        captureParser_[i].renderTexture_ = new Texture2D(context_);
        captureParser_[i].renderTexture_->SetNumLevels(1);

        //**note** indirect capture texture size is fixed to 64x64
        captureParser_[i].renderTexture_->SetSize(FIXED_INDIRECT_TEXSIZE, FIXED_INDIRECT_TEXSIZE, Graphics::GetRGBAFormat(), TEXTURE_RENDERTARGET);
        captureParser_[i].renderTexture_->SetFilterMode(FILTER_BILINEAR);
        
        captureParser_[i].renderSurface_ = captureParser_[i].renderTexture_->GetRenderSurface();
        captureParser_[i].renderSurface_->SetViewport(0, captureParser_[i].viewport_);
        captureParser_[i].renderSurface_->SetUpdateMode(SURFACE_UPDATEALWAYS);

        // set cam pos rot
        SetCameraPosRotForCapture(i);
    }

    // start timer
    timerIndirect_.Reset();

    SubscribeToEvent(E_ENDVIEWRENDER, URHO3D_HANDLER(Lightmap, HandleEndViewRender));
}

unsigned Lightmap::GetState()
{
    MutexLock lock(mutexStateLock_);
    return stateProcess_;
}

void Lightmap::SetState(unsigned state)
{
    MutexLock lock(mutexStateLock_);
    stateProcess_ = state;
}

void Lightmap::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    ForegroundProcess();
}

void Lightmap::ForegroundProcess()
{
    switch (GetState())
    {
    case State_CreateGeomData:
        {
            SetupGeomData();
            SetState(State_CreatePixelData);

            // start background process
            threadProcess_ = new HelperThread<Lightmap>(this, &Lightmap::BackgroundBuildPixelData);
            threadProcess_->Start();
        }
        break;

    case State_CreatePixelData:
        // wait for background
        break;

    case State_IndirectLightBegin:
        {
            // kill thread
            threadProcess_ = NULL;

            SendTriangleInfoMsg();

            // setup indirect lighting
            InitIndirectLightSettings();

            SetState(State_IndirectLightProcess);

            #ifdef IRRADIANCE_THREADED
            // reserve a few spaces
            indirectDataList_.Reserve(10);

            // start background process
            threadProcess_ = new HelperThread<Lightmap>(this, &Lightmap::BackgroundProcessIndirectImage);
            threadProcess_->Start();
            #endif
        }
        break;

    case State_IndirectLightWaitBackground:
        {
            #ifdef IRRADIANCE_THREADED
            unsigned idx;
            if (GetFrontIndirectQueueImage(idx) == NULL)
            {
                FinalizeIndirectImage();

                // kill thread
                threadProcess_ = NULL;

                SetState(State_IndirectLightEnd);
            }
            #endif
        }
        break;
    }
}

void Lightmap::BackgroundBuildPixelData(void *data)
{
    Lightmap *lightmap = (Lightmap*)data;

    if (lightmap->GetState() == State_CreatePixelData)
    {
        lightmap->SetupPixelData();
        lightmap->SetState(State_IndirectLightBegin);
    }
}

void Lightmap::SendTriangleInfoMsg()
{
    using namespace TriangleInfo;

    unsigned triCnt = 0;
    for (unsigned i = 0; i < triangleData_.Size(); ++i )
    {
        if (triangleData_[i].pixelCnt_ > 0)
        {
            ++triCnt;
        }
    }

    VariantMap &eventData  = GetEventDataMap();
    eventData[P_TRICNT]    = triCnt;

    SendEvent(E_TRIANGLEINFO, eventData);
}

void Lightmap::SendTriangleCompleteMsg()
{
    using namespace TriangleCompleted;

    VariantMap& eventData  = GetEventDataMap();

    SendEvent(E_TRIANGLECOMPLETED, eventData);
}

void Lightmap::SendIndirectCompleteMsg()
{
    using namespace IndirectCompleted;

    VariantMap& eventData  = GetEventDataMap();
    eventData[P_NODE]      = node_;

    SendEvent(E_INDIRECTCOMPLETED, eventData);
}

void Lightmap::BackgroundProcessIndirectImage(void *data)
{
    Lightmap *lightmap = (Lightmap*)data;
    unsigned idx;
    SharedPtr<Image> image = lightmap->GetFrontIndirectQueueImage(idx);

    while (image)
    {
        lightmap->CalculateIrradiance(idx, image);
        lightmap->PopFrontIndirectQueue();
        image = lightmap->GetFrontIndirectQueueImage(idx);
    }
}

void Lightmap::QueueIndirectImage(unsigned idx, SharedPtr<Image> image)
{
    MutexLock lock(mutexIndirectQueueLock_);

    indirectDataList_.Resize(indirectDataList_.Size() + 1);
    IndirectData &indirectData = indirectDataList_[indirectDataList_.Size() - 1];

    indirectData.image_ = new Image(context_);
    indirectData.image_->SetSize(image->GetWidth(), image->GetHeight(), 4);
    indirectData.image_->SetData(image->GetData());
    indirectData.idx_ = idx;
}

SharedPtr<Image> Lightmap::GetFrontIndirectQueueImage(unsigned &idx)
{
    MutexLock lock(mutexIndirectQueueLock_);

    SharedPtr<Image> image;
    if (indirectDataList_.Size() > 0)
    {
        idx = indirectDataList_[0].idx_;
        image = indirectDataList_[0].image_;
    }
    return image;
}

void Lightmap::PopFrontIndirectQueue()
{
    MutexLock lock(mutexIndirectQueueLock_);

    if (indirectDataList_.Size() > 0)
    {
        indirectDataList_.Erase(0);
    }
}

void Lightmap::CalculateIrradiance(unsigned idx, SharedPtr<Image> srcImage)
{
    pixelData_[idx].col_ = Color::TRANSPARENT;
    for ( int y = 0; y < srcImage->GetHeight(); ++y )
    {
        for ( int x = 0; x < srcImage->GetWidth(); ++x )
        {
            pixelData_[idx].col_ += srcImage->GetPixel(x, y);
        }
    }
    pixelData_[idx].col_ = pixelData_[idx].col_ * solidangle_;

    if (lumaOutputColor_)
    {
        float luma = pixelData_[idx].col_.Luma();
        pixelData_[idx].col_ = Color(luma, luma, luma);
    }
}

void Lightmap::FinalizeIndirectImage()
{
    float elapsed = (float)((long)timerIndirect_.GetMSec(false))/1000.0f;
    char buff[20];
    sprintf(buff, "%.2f sec.", elapsed);
    URHO3D_LOGINFO(ToString("node%u: indirect completion = ", node_->GetID()) + String(buff));

    // write final image
    indirectLightImage_ = new Image(context_);
    indirectLightImage_->SetSize(texWidth_, texHeight_, 4);
    indirectLightImage_->Clear(Color::TRANSPARENT);
    for ( unsigned i = 0; i < pixelData_.Size(); ++i )
    {
        indirectLightImage_->SetPixel(pixelData_[i].iuv_.x_, pixelData_[i].iuv_.y_, pixelData_[i].col_);
    }

    // smooth and dilate
    SmoothAndDilate(indirectLightImage_);

    // requires save, ignore savefile flag
    String name = ToString("node%u_lightmap.png", node_->GetID());
    String path = filepath_ + name;
    indirectLightImage_->SavePNG(path);

    // send msgs
    SendTriangleCompleteMsg();
    SendIndirectCompleteMsg();
}

void Lightmap::SetCameraPosRotForCapture(unsigned idx)
{
    captureParser_[idx].isStopped_ = true;

    if (curPixelIdx_ < pixelData_.Size())
    {
        const PixelPoint &pixelPoint = pixelData_[curPixelIdx_];
        unsigned prevTriIdx = pixelPoint.triIdx_;
        Quaternion qrot;
        qrot.FromLookRotation(pixelPoint.normal_);

        captureParser_[idx].camNode_->SetPosition(pixelPoint.pos_);
        captureParser_[idx].camNode_->SetRotation(qrot);
        captureParser_[idx].pixelIdx_  = curPixelIdx_;
        captureParser_[idx].triIdx_    = pixelPoint.triIdx_;
        captureParser_[idx].isStopped_ = false;

        if (++curPixelIdx_ < pixelData_.Size())
        {
            // send tri complete msg
            if (prevTriIdx != pixelData_[curPixelIdx_].triIdx_)
            {
                SendTriangleCompleteMsg();
            }
        }
    }

    // remove components
    if (captureParser_[idx].isStopped_)
    {
        captureParser_[idx].camNode_->Remove();
        captureParser_[idx].camNode_ = NULL;
        captureParser_[idx].camera_ = NULL;
        captureParser_[idx].viewport_ = NULL;
        captureParser_[idx].renderSurface_ = NULL;
        captureParser_[idx].renderTexture_ = NULL;
    }
}

void Lightmap::ProcessIndirectRenderSurface(unsigned parserIdx)
{
    unsigned pixelIdx = captureParser_[parserIdx].pixelIdx_;

    #ifdef IRRADIANCE_THREADED
    QueueIndirectImage(pixelIdx, captureParser_[parserIdx].renderTexture_->GetImage());
    #else
    CalculateIrradiance(pixelIdx, captureParser_[parserIdx].renderTexture_->GetImage());
    #endif

    // update pixel idx and surfaceupdate mode 
    SetCameraPosRotForCapture(parserIdx);

    // check tri complete
    if (++pixelsCompleted_ >= pixelData_.Size())
    {
        UnsubscribeFromEvent(E_ENDVIEWRENDER);

        #ifdef IRRADIANCE_THREADED
        SetState(State_IndirectLightWaitBackground);
        #else
        FinalizeIndirectImage();
        SetState(State_IndirectLightEnd);
        #endif
    }
}

void Lightmap::SmoothAndDilate(SharedPtr<Image> inImage, bool dilate)
{
    SharedPtr<Image> outImage(new Image(context_));
    outImage->SetSize(inImage->GetWidth(), inImage->GetHeight(), 4);

    ImageSmooth(inImage, outImage);
    inImage->SetData(outImage->GetData());

    if (dilate)
    {
        for ( unsigned i = 0; i < 2; ++i )
        {
            ImageDilate(inImage, outImage);
            ImageDilate(outImage, inImage);
        }
    }
}

void Lightmap::HandleEndViewRender(StringHash eventType, VariantMap& eventData)
{
    using namespace EndViewRender;
    Camera* camera = (Camera*)eventData[P_CAMERA].GetVoidPtr();

    for ( unsigned i = 0; i < captureParser_.Size(); ++i )
    {
        CaptureData &captureData = captureParser_[i];

        if (captureParser_[i].camera_ && captureParser_[i].camera_ == camera)
        {
            // process render surface
            ProcessIndirectRenderSurface(i);
            break;
        }
    }
}

void Lightmap::DrawDebugGeometry(DebugRenderer* debug, const Color &color, bool depthTest, unsigned &triIdx)
{
    if (triIdx > pixelData_[pixelData_.Size() - 1].triIdx_)
    {
        triIdx = 0;
    }

    for (unsigned i = 0; i < pixelData_.Size(); ++i)
    {
        if (triIdx == pixelData_[i].triIdx_)
        {
            debug->AddLine(pixelData_[i].pos_, pixelData_[i].pos_ + pixelData_[i].normal_ * 0.05f, color, depthTest);
        }
    }
}

void Lightmap::SetupGeomData()
{
    Model *model = staticModel_->GetModel();
    Geometry *geometry = model->GetGeometry(0, 0);
    VertexBuffer *vbuffer = geometry->GetVertexBuffer(0);
    const unsigned char *vertexData = (const unsigned char*)vbuffer->Lock(0, vbuffer->GetVertexCount());

    // transform in world space
    const Matrix3x4 objMatrix = node_->GetWorldTransform();
    const Quaternion objRotation = node_->GetWorldRotation();

    // populate geom data
    if (vertexData)
    {
        unsigned elementMask = vbuffer->GetElementMask();
        unsigned numVertices = vbuffer->GetVertexCount();
        unsigned vertexSize = vbuffer->GetVertexSize();

        geomData_.Resize(numVertices);

        for ( unsigned i = 0; i < numVertices; ++i )
        {
            unsigned char *dataAlign = (unsigned char *)(vertexData + i * vertexSize);
            GeomData &geom = geomData_[i];

            if (elementMask & MASK_POSITION)
            {
                geom.pos_ = *reinterpret_cast<const Vector3*>(dataAlign);
                geom.pos_ = objMatrix * geom.pos_;
                dataAlign += sizeof(Vector3);
            }
            if (elementMask & MASK_NORMAL)
            {
                geom.normal_ = *reinterpret_cast<const Vector3*>(dataAlign);
                geom.normal_ = objRotation * geom.normal_;
                dataAlign += sizeof(Vector3);
            }
            if (elementMask & MASK_COLOR)
            {
                dataAlign += sizeof(unsigned);
            }
            if (elementMask & MASK_TEXCOORD1)
            {
                dataAlign += sizeof(Vector2);
            }
            if (elementMask & MASK_TEXCOORD2)
            {
                geom.uv_ = *reinterpret_cast<const Vector2*>(dataAlign);
            }
        }
        vbuffer->Unlock();
    }

    // get indices
    IndexBuffer *ibuffer = geometry->GetIndexBuffer();
    void *pdata = ibuffer->Lock(0, ibuffer->GetIndexCount());

    if (pdata)
    {
        numIndices_ = ibuffer->GetIndexCount();
        indexSize_ = ibuffer->GetIndexSize();

        if (indexSize_ == sizeof(unsigned short))
        {
            indexBuffShort_ = new unsigned short[numIndices_];
            memcpy(indexBuffShort_.Get(), pdata, numIndices_ * indexSize_);
        }
        else
        {
            indexBuff_ = new unsigned[numIndices_];
            memcpy(indexBuff_.Get(), pdata, numIndices_ * indexSize_);
        }

        ibuffer->Unlock();
    }
}

void Lightmap::SetupPixelData()
{
    const int texSizeX = texWidth_;
    const int texSizeY = texHeight_;
    const float ftexSizeX = (float)texWidth_;
    const float ftexSizeY = (float)texHeight_;
    const float texSizeXINV = 1.0f/ftexSizeX;
    const float texSizeYINV = 1.0f/ftexSizeY;

    pixelData_.Clear();
    pixelData_.Reserve((int)(ftexSizeX * ftexSizeY * 1.05f));
    triangleData_.Resize(numIndices_/3);
    bool isShort = (indexSize_ == sizeof(unsigned short));

    // build sh coeff
    for( unsigned i = 0; i < numIndices_; i += 3 )
    {
        const unsigned idx0 = (const unsigned)(isShort?indexBuffShort_[i+0]:indexBuff_[i+0]);
        const unsigned idx1 = (const unsigned)(isShort?indexBuffShort_[i+1]:indexBuff_[i+1]);
        const unsigned idx2 = (const unsigned)(isShort?indexBuffShort_[i+2]:indexBuff_[i+2]);

        const Vector3 &v0 = geomData_[idx0].pos_;	
        const Vector3 &v1 = geomData_[idx1].pos_;	
        const Vector3 &v2 = geomData_[idx2].pos_;	

        const Vector3 &n0 = geomData_[idx0].normal_;   
        const Vector3 &n1 = geomData_[idx1].normal_;   
        const Vector3 &n2 = geomData_[idx2].normal_;  

        const Vector2 &uv0 = geomData_[idx0].uv_;
        const Vector2 &uv1 = geomData_[idx1].uv_;
        const Vector2 &uv2 = geomData_[idx2].uv_;

        float xMin = 1.0f;	
        float xMax = 0.0f;	
        float yMin = 1.0f;
        float yMax = 0.0f;

        if (uv0.x_ < xMin) xMin = uv0.x_; 
        if (uv1.x_ < xMin) xMin = uv1.x_; 
        if (uv2.x_ < xMin) xMin = uv2.x_; 

        if (uv0.x_ > xMax) xMax = uv0.x_; 
        if (uv1.x_ > xMax) xMax = uv1.x_; 
        if (uv2.x_ > xMax) xMax = uv2.x_; 

        if (uv0.y_ < yMin) yMin = uv0.y_; 
        if (uv1.y_ < yMin) yMin = uv1.y_; 
        if (uv2.y_ < yMin) yMin = uv2.y_; 

        if (uv0.y_ > yMax) yMax = uv0.y_;
        if (uv1.y_ > yMax) yMax = uv1.y_;
        if (uv2.y_ > yMax) yMax = uv2.y_;

        const int pixMinX = (int)Max(Floor(xMin * ftexSizeX)-1, 0.0f); 
        const int pixMaxX = (int)Min( Ceil(xMax * ftexSizeX)+1, ftexSizeX); 
        const int pixMinY = (int)Max(Floor(yMin * ftexSizeY)-1, 0.0f); 
        const int pixMaxY = (int)Min( Ceil(yMax * ftexSizeY)+1, ftexSizeY);

        // gather info on triangle data
        TriangleData &triangleData = triangleData_[i/3];
        triangleData.pixelCnt_ = 0;
        triangleData.minXY_    = IntVector2(M_MAX_INT, M_MAX_INT);
        triangleData.maxXY_    = IntVector2(-1, -1);

        Vector3 point, normal, bary;

        for ( int x = pixMinX; x < pixMaxX; ++x ) 
        {
            for ( int y = pixMinY; y < pixMaxY; ++y ) 
            {
                bary = Barycentric(uv0, uv1, uv2, Vector2((float)x * texSizeXINV, (float)y * texSizeYINV));

                if (BaryInsideTriangle(bary))
                {
                    point = bary.x_ * v0 + bary.y_ * v1 + bary.z_ * v2;
                    normal = (bary.x_ * n0 + bary.y_ * n1 + bary.z_ * n2).Normalized();

                    // save pixel pt data
                    pixelData_.Resize(pixelData_.Size() + 1);
                    PixelPoint &pixelPt = pixelData_[pixelData_.Size() - 1];

                    pixelPt.triIdx_ = i;
                    pixelPt.pos_    = point;
                    pixelPt.normal_ = normal;
                    pixelPt.iuv_    = IntVector2(x, y);
                    pixelPt.col_    = Color::TRANSPARENT;

                    // update triangle data
                    ++triangleData.pixelCnt_;
                    triangleData.minXY_.x_ = Min(x, triangleData.minXY_.x_);
                    triangleData.maxXY_.x_ = Max(x, triangleData.maxXY_.x_);
                    triangleData.minXY_.y_ = Min(y, triangleData.minXY_.y_);
                    triangleData.maxXY_.y_ = Max(y, triangleData.maxXY_.y_);
                }
            }
        }
    }
}

//=============================================================================
// ImageSmooth and ImageDilate fns, ref: https://github.com/ands/lightmapper.git
//=============================================================================
void ImageSmooth(SharedPtr<Image> image, SharedPtr<Image> outImage)
{
    int w = (int)image->GetWidth();
    int h = (int)image->GetHeight();

    for ( int y = 0; y < h; ++y )
    {
        for ( int x = 0; x < w; ++x )
        {
            Color ocolor = image->GetPixel(x, y);
            bool ovalid = false;

            // avoid having black transp value blend with valid colors
            for ( int i = 0; i < 4; ++i )
            {
                ovalid |= ocolor.Data()[i] > 0.0f;
            }
            if (!ovalid)
            {
                outImage->SetPixel(x, y, Color::TRANSPARENT);
                continue;
            }

            Color color(Color::TRANSPARENT);
            int n = 0;

            for ( int dy = -1; dy <= 1; ++dy )
            {
                int cy = y + dy;
                for ( int dx = -1; dx <= 1; ++dx )
                {
                    int cx = x + dx;
                    if (cx >= 0 && cx < w && cy >= 0 && cy < h)
                    {
                        Color dcolor = image->GetPixel(cx, cy);
                        bool valid = false;
                        for ( int i = 0; i < 4; ++i )
                        {
                            valid |= dcolor.Data()[i] > 0.0f;
                        }

                        if (valid)
                        {
                            color += dcolor;
                            n++;
                        }
                    }
                }
            }

            if (n > 0)
            {
                color = color * (1.0f/(float)n);
                outImage->SetPixel(x, y, color);
            }
            else
            {
                outImage->SetPixel(x, y, Color::TRANSPARENT);
            }
        }
    }
}

void ImageDilate(SharedPtr<Image> image, SharedPtr<Image> outImage)
{
    int w = (int)image->GetWidth();
    int h = (int)image->GetHeight();

    for ( int y = 0; y < h; ++y )
    {
        for ( int x = 0; x < w; ++x )
        {
            Color color = image->GetPixel(x, y);
            bool valid = false;
            for ( int i = 0; i < 4; ++i )
            {
                valid |= color.Data()[i] > 0.0f;
            }
            if (!valid)
            {
                int n = 0;
                const int dx[] = { -1, 0, 1,  0 };
                const int dy[] = {  0, 1, 0, -1 };
                for ( int d = 0; d < 4; ++d )
                {
                    int cx = x + dx[d];
                    int cy = y + dy[d];
                    if (cx >= 0 && cx < w && cy >= 0 && cy < h)
                    {
                        Color dcolor= image->GetPixel(cx, cy);
                        bool dvalid = false;
                        for (int i = 0; i < 4; i++)
                        {
                            dvalid |= dcolor.Data()[i] > 0.0f;
                        }
                        if (dvalid)
                        {
                            color += dcolor;
                            n++;
                        }
                    }
                }
                if (n)
                {
                    color = color * (1.0f/(float)n);
                }
            }

            outImage->SetPixel(x, y, color);
        }
    }
}





