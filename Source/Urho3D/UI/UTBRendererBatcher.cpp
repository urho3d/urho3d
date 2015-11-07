//=============================================================================
// Copyright (c) 2015 LumakSoftware
//
//=============================================================================
#include "../Core/Context.h"
#include "../Core/Object.h"
#include "../Core/CoreEvents.h"
#include "../UI/UI.h"
#include "../UI/UIElement.h"
#include "../UI/UIEvents.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/VertexBuffer.h"
#include "../Resource/ResourceCache.h"
#include "../IO/FileSystem.h"
#include "../Input/InputEvents.h"

#include <TurboBadger/tb_font_renderer.h>
#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_bitmap_fragment.h>
#include <TurboBadger/tb_system.h>
#include <TurboBadger/tb_msg.h>
#include <TurboBadger/tb_language.h>
#include <TurboBadger/animation/tb_animation.h>
#include <TurboBadger/animation/tb_widget_animation.h>

#include "UTBRendererBatcher.h"

#include "../DebugNew.h"

namespace Urho3D
{

//=============================================================================
//=============================================================================
#define QAL_VAL         0x60000000      // value to offset qualifier keys from all other keys in the same hash map

//=============================================================================
//=============================================================================
UTBRendererBatcher* UTBRendererBatcher::pSingleton_ = NULL;

//=============================================================================
//=============================================================================
UTBBitmap::UTBBitmap(Context *_context, int _width, int _height) 
    : width_( _width ) 
    , height_( _height )
    , texture_( NULL )
{
    texture_ = new Texture2D( _context );

    // set texture format
    texture_->SetMipsToSkip( QUALITY_LOW, 0 );
    texture_->SetNumLevels( 1 );
    texture_->SetSize( width_, height_, Graphics::GetRGBAFormat() );

    // set uv modes
    texture_->SetAddressMode( COORD_U, ADDRESS_WRAP );
    texture_->SetAddressMode( COORD_V, ADDRESS_WRAP );
}

//=============================================================================
//=============================================================================
UTBBitmap::~UTBBitmap()
{
    if ( texture_ )
    {
        texture_ = NULL;
    }
}

//=============================================================================
//=============================================================================
UTBRendererBatcher::UTBRendererBatcher(Context *_context, int _iwidth, int _iheight) 
    : UIElement( _context )
    , TBRendererBatcher() 
{
    SetPosition( 0, 0 );
    OnResizeWin( _iwidth, _iheight );
}

//=============================================================================
//=============================================================================
UTBRendererBatcher::~UTBRendererBatcher()
{
    vertexData_.Clear();
    batches_.Clear();
    uKeytoTBkeyMap.Clear();

    TBWidgetsAnimationManager::Shutdown();

    // shutdown
    tb_core_shutdown();
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::OnResizeWin(int _iwidth, int _iheight)
{
    m_screen_rect = TBRect( 0, 0, _iwidth, _iheight );

    SetSize( _iwidth, _iheight );

    root_.SetRect( m_screen_rect );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::Init(const String &_strDataPath)
{
    // register with UI
    GetSubsystem<UI>()->GetRoot()->AddChild( this );

    // store data path
    strDataPath_ = GetSubsystem<FileSystem>()->GetProgramDir() + _strDataPath;

    // init tb core
    tb_core_init( this );
    TBWidgetsAnimationManager::Init();

    // map keys
    CreateKeyMap();

    // register handlers
    RegisterHandlers();
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::CreateKeyMap()
{
    // special keys
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_UP       , TB_KEY_UP        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_DOWN     , TB_KEY_DOWN      ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_LEFT     , TB_KEY_LEFT      ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_RIGHT    , TB_KEY_RIGHT     ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_PAGEUP   , TB_KEY_PAGE_UP   ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_PAGEDOWN , TB_KEY_PAGE_DOWN ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_HOME     , TB_KEY_HOME      ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_END      , TB_KEY_END       ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_TAB      , TB_KEY_TAB       ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_BACKSPACE, TB_KEY_BACKSPACE ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_INSERT   , TB_KEY_INSERT    ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_DELETE   , TB_KEY_DELETE    ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_RETURN   , TB_KEY_ENTER     ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_ESC      , TB_KEY_ESC       ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F1       , TB_KEY_F1        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F2       , TB_KEY_F2        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F3       , TB_KEY_F3        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F4       , TB_KEY_F4        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F5       , TB_KEY_F5        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F6       , TB_KEY_F6        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F7       , TB_KEY_F7        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F8       , TB_KEY_F8        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F9       , TB_KEY_F9        ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F10      , TB_KEY_F10       ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F11      , TB_KEY_F11       ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( KEY_F12      , TB_KEY_F12       ) );

    // qualifiers: add QAL_VAL to qual keys to separate their range from rest of the keys
    uKeytoTBkeyMap.Insert( Pair<int,int>( QUAL_SHIFT + QAL_VAL, TB_SHIFT ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( QUAL_CTRL  + QAL_VAL, TB_CTRL  ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( QUAL_ALT   + QAL_VAL, TB_ALT   ) );
    uKeytoTBkeyMap.Insert( Pair<int,int>( QUAL_ANY   + QAL_VAL, TB_SUPER ) );
}

//=============================================================================
//=============================================================================
TBBitmap* UTBRendererBatcher::CreateBitmap(int width, int height, uint32 *data)
{
    UTBBitmap *pUTBBitmap = new UTBBitmap( GetContext(), width, height );

    FlushBitmap( (TBBitmap*)pUTBBitmap );

    pUTBBitmap->SetData( data );

    return (TBBitmap*)pUTBBitmap;
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
{
    for ( unsigned i = 0; i < batches_.Size(); ++i )
    {
        // get batch
        UIBatch &batch     = batches_[ i ];
        unsigned beg       = batch.vertexStart_;
        unsigned end       = batch.vertexEnd_;
        batch.vertexStart_ = vertexData.Size();
        batch.vertexEnd_   = vertexData.Size() + (end - beg);

        // resize and copy
        vertexData.Resize( batch.vertexEnd_ );
        memcpy( &vertexData[ batch.vertexStart_ ], &vertexData_[ beg ], (end - beg) * sizeof(float) );

        // store
        UIBatch::AddOrMerge( batch, batches );
    }

    // clear buffers
    vertexData_.Clear();
    batches_.Clear();
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::RenderBatch(Batch *_pb)
{
    if ( _pb && _pb->vertex_count > 0 )
    {
        UTBBitmap *pUTBBitmap = (UTBBitmap*)_pb->bitmap;
        SharedPtr<Texture2D> tdummy;
        SharedPtr<Texture2D> texture = pUTBBitmap?pUTBBitmap->texture_: tdummy;
        IntRect scissor( _pb->clipRect.x, _pb->clipRect.y, _pb->clipRect.x + _pb->clipRect.w, _pb->clipRect.y + _pb->clipRect.h );
        UIBatch batch( this, BLEND_ALPHA, scissor, texture, &vertexData_ );

        unsigned begin = batch.vertexData_->Size();
        batch.vertexData_->Resize(begin + _pb->vertex_count * UI_VERTEX_SIZE);
        float* dest = &(batch.vertexData_->At(begin));

        // set start/end
        batch.vertexStart_ = begin;
        batch.vertexEnd_   = batch.vertexData_->Size();

        for ( int i = 0; i < _pb->vertex_count; ++i )
        {
            dest[0+i*UI_VERTEX_SIZE]              = _pb->vertex[i].x; 
            dest[1+i*UI_VERTEX_SIZE]              = _pb->vertex[i].y; 
            dest[2+i*UI_VERTEX_SIZE]              = 0.0f;
            ((unsigned&)dest[3+i*UI_VERTEX_SIZE]) = _pb->vertex[i].col;
            dest[4+i*UI_VERTEX_SIZE]              = _pb->vertex[i].u; 
            dest[5+i*UI_VERTEX_SIZE]              = _pb->vertex[i].v;
        }

        // store
        UIBatch::AddOrMerge( batch, batches_ );
    }
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::RegisterHandlers()
{
    // timer
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(UTBRendererBatcher, HandleUpdate));

    // screen resize and renderer
    SubscribeToEvent(E_SCREENMODE, URHO3D_HANDLER(UTBRendererBatcher, HandleScreenMode));
    SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(UTBRendererBatcher, HandleBeginFrame));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(UTBRendererBatcher, HandlePostUpdate));
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(UTBRendererBatcher, HandlePostRenderUpdate));

    // inputs
    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(UTBRendererBatcher, HandleMouseButtonDown));
    SubscribeToEvent(E_MOUSEBUTTONUP, URHO3D_HANDLER(UTBRendererBatcher, HandleMouseButtonUp));
    SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(UTBRendererBatcher, HandleMouseMove));
    SubscribeToEvent(E_MOUSEWHEEL, URHO3D_HANDLER(UTBRendererBatcher, HandleMouseWheel));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(UTBRendererBatcher, HandleKeyDown));
    SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(UTBRendererBatcher, HandleKeyUp));
    SubscribeToEvent(E_TEXTINPUT, URHO3D_HANDLER(UTBRendererBatcher, HandleTextInput));
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // msg timer
    double t = TBMessageHandler::GetNextMessageFireTime();

    if ( t != TB_NOT_SOON && t <= TBSystem::GetTimeMS() )
    {
        TBMessageHandler::ProcessMessages();
    }
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleScreenMode(StringHash eventType, VariantMap& eventData)
{
    using namespace ScreenMode;

    OnResizeWin( eventData[P_WIDTH].GetInt(), eventData[P_HEIGHT].GetInt() );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
{
    TBAnimationManager::Update();
    root_.InvokeProcessStates();
    root_.InvokeProcess();
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    TBRendererBatcher::BeginPaint( root_.GetRect().w, root_.GetRect().h );

    root_.InvokePaint( TBWidget::PaintProps() );

    // If animations are running, reinvalidate immediately
    if ( TBAnimationManager::HasAnimationsRunning() )
    {
        root_.Invalidate();
    }
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
    TBRendererBatcher::EndPaint();
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleMouseButtonDown(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonDown;

    int mouseButtons = eventData[P_BUTTONS].GetInt();
    int qualifiers = eventData[P_QUALIFIERS].GetInt();
    MODIFIER_KEYS modKey = (MODIFIER_KEYS)FindTBKey( qualifiers + QAL_VAL );

    // exit if not the left mb
    if ( mouseButtons != MOUSEB_LEFT )
    {
        return;
    }

    root_.InvokePointerDown( lastMousePos_.x_, lastMousePos_.y_, 1, modKey, false );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleMouseButtonUp(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseButtonUp;

    int qualifiers = eventData[P_QUALIFIERS].GetInt();
    MODIFIER_KEYS modKey = (MODIFIER_KEYS)FindTBKey( qualifiers + QAL_VAL );

    root_.InvokePointerUp( lastMousePos_.x_, lastMousePos_.y_, modKey, false );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleMouseMove(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseMove;

    int qualifiers = eventData[P_QUALIFIERS].GetInt();
    MODIFIER_KEYS modKey = (MODIFIER_KEYS)FindTBKey( qualifiers + QAL_VAL );

    lastMousePos_ = IntVector2( eventData[P_X].GetInt(), eventData[P_Y].GetInt() );

    root_.InvokePointerMove( lastMousePos_.x_, lastMousePos_.y_, modKey, false );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleMouseWheel(StringHash eventType, VariantMap& eventData)
{
    using namespace MouseWheel;

    int qualifiers = eventData[P_QUALIFIERS].GetInt();
    int delta = eventData[P_WHEEL].GetInt();
    MODIFIER_KEYS modKey = (MODIFIER_KEYS)FindTBKey( qualifiers + QAL_VAL );

    root_.InvokeWheel( lastMousePos_.x_, lastMousePos_.y_, 0, -delta, modKey );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyDown;

    int qualifiers = eventData[P_QUALIFIERS].GetInt();
    int key = eventData[P_KEY].GetInt();
    MODIFIER_KEYS modKey = (MODIFIER_KEYS)FindTBKey( qualifiers + QAL_VAL );
    SPECIAL_KEY spKey = (SPECIAL_KEY)FindTBKey( key );

    // exit if not a special key
    if ( spKey == TB_KEY_UNDEFINED )
    {
        return;
    }

    root_.InvokeKey( key, spKey, modKey, true );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleKeyUp(StringHash eventType, VariantMap& eventData)
{
    using namespace KeyUp;

    int qualifiers = eventData[P_QUALIFIERS].GetInt();
    int key = eventData[P_KEY].GetInt();
    MODIFIER_KEYS modKey = (MODIFIER_KEYS)FindTBKey( qualifiers + QAL_VAL );
    SPECIAL_KEY spKey = (SPECIAL_KEY)FindTBKey( key );

    root_.InvokeKey( key, spKey, modKey, false );
}

//=============================================================================
//=============================================================================
void UTBRendererBatcher::HandleTextInput(StringHash eventType, VariantMap& eventData)
{
    using namespace TextInput;

    int qualifiers = eventData[P_QUALIFIERS].GetInt();
    int key = (int)eventData[P_TEXT].GetString().CString()[ 0 ];
    MODIFIER_KEYS modKey = (MODIFIER_KEYS)FindTBKey( qualifiers + QAL_VAL );

    root_.InvokeKey( key, TB_KEY_UNDEFINED, modKey, true );
}

//=============================================================================
//=============================================================================
int UTBRendererBatcher::FindTBKey(int _ikey)
{
    HashMap<int, int>::Iterator itr = uKeytoTBkeyMap.Find( _ikey );
    int itbkey = 0;

    if ( itr != uKeytoTBkeyMap.End() )
    {
        itbkey = itr->second_;
    }
    return itbkey;
}

//=============================================================================
//=============================================================================
class UTBFile : public TBFile
{
public:
    UTBFile(Context *_context) 
        : fileSize_( 0 )
    {
        pfile_ = new File( _context );
    }

    virtual ~UTBFile() 
    { 
        if ( pfile_ )
        {
            pfile_->Close();
            pfile_ = NULL;
        }
    }

    bool OpenFile(const char* fileName)
    {
        bool bopen = pfile_->Open( fileName );

        if ( bopen )
        {
            fileSize_ = (long)pfile_->Seek( (unsigned)-1 );
            pfile_->Seek( 0 );
        }

        return bopen;
    }

    virtual long Size()
    {
        return fileSize_;
    }

    virtual size_t Read(void *buf, size_t elemSize, size_t count)
    {
        return pfile_->Read( buf, elemSize * count );
    }

protected:
    SharedPtr<File> pfile_;
    long fileSize_;
};

} // Urho3D namespace

using namespace Urho3D;

//=============================================================================
// static
//=============================================================================
TBFile* TBFile::Open(const char *filename, TBFileMode )
{
    UTBFile *pFile = new UTBFile( UTBRendererBatcher::Singleton().GetContext() );
    String strFilename = UTBRendererBatcher::Singleton().GetDataPath() + String( filename );

    if ( !pFile->OpenFile( strFilename.CString() ) )
    {
        delete pFile;
        pFile = NULL;
    }

    return pFile;
}


