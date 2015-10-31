//=============================================================================
// Copyright (c) 2015 LumakSoftware
//
//=============================================================================
#pragma once

#include "../Urho3D.h"
#include "../Container/Ptr.h"
#include "../Graphics/Texture2D.h"
#include "../UI/UIElement.h"

#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_renderer.h>
#include <TurboBadger/renderers/tb_renderer_batcher.h>

using namespace tb;

namespace Urho3D
{
class Context;
class VertexBuffer;

class UTBMain;

//=============================================================================
//=============================================================================
class URHO3D_API UTBBitmap : public TBBitmap
{
public:
    UTBBitmap(Context *_pContext, int _width, int _height); 
    ~UTBBitmap();

    // =========== virtual methods required for TBBitmap subclass =========
	virtual void SetData(uint32 *_pdata)
    {
        texture_->SetData( 0, 0, 0, width_, height_, _pdata );
    }

    virtual int Width() { return width_; }
    virtual int Height(){ return height_; }

public:
    SharedPtr<Texture2D>    texture_;
    int                     width_;
    int                     height_;
};

//=============================================================================
//=============================================================================
class URHO3D_API UTBRendererBatcher : public UIElement, public TBRendererBatcher
{
    URHO3D_OBJECT(UTBRendererBatcher, UIElement);

    friend class UTBMain;
public:
    // public accessor
    static UTBRendererBatcher& Singleton() { return *pSingleton_; }

    // methods
    void Init(const String &_strDataPath);

    TBWidget& Root() { return root_; }
    const String& GetDataPath() { return strDataPath_; }

    // UIElement override method to add TB batches
    virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);

    // ===== methods that need implementation in TBRendererBatcher subclasses =====
    virtual TBBitmap* CreateBitmap(int width, int height, uint32 *data);

    virtual void RenderBatch(Batch *batch);

    virtual void SetClipRect(const TBRect &rect)
    {
        m_clip_rect = rect;
    }

protected:
    // static funcs
    static void Create(Context *_context, int _iwidth, int _iheight)
    {
        if ( pSingleton_ == NULL )
        {
            pSingleton_ = new UTBRendererBatcher( _context, _iwidth, _iheight );
        }
    }

    static void Destroy()
    {
        if ( pSingleton_ )
        {
            pSingleton_->Remove();
            pSingleton_ = NULL;
        }
    }

    // ctor/dtor
    UTBRendererBatcher(Context *_pContext, int _iwidth, int _iheight);
    virtual ~UTBRendererBatcher();

    void LoadDefaultResources();
    void OnResizeWin(int _iwidth, int _iheight);
    void CreateKeyMap();
    void RegisterHandlers();

    void HandleUpdate(StringHash eventType, VariantMap& eventData);

    // renderer
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    void HandleBeginFrame(StringHash eventType, VariantMap& eventData);
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

    // inputs
    void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleMouseButtonUp(StringHash eventType, VariantMap& eventData);
    void HandleMouseMove(StringHash eventType, VariantMap& eventData);
    void HandleMouseWheel(StringHash eventType, VariantMap& eventData);
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    void HandleKeyUp(StringHash eventType, VariantMap& eventData);
    void HandleTextInput(StringHash eventType, VariantMap& eventData);

    // TB special and qualitier keys func
    int FindTBKey(int _ikey);

protected:
    static UTBRendererBatcher   *pSingleton_;

    TBWidget                    root_;
    PODVector<float>            vertexData_;
    PODVector<UIBatch>          batches_;

    String                      strDataPath_;

    HashMap<int, int>           uKeytoTBkeyMap;
    IntVector2                  lastMousePos_;
};

} // Urho3D namespace
