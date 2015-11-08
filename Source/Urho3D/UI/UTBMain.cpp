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
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Texture2D.h"
#include "../Resource/ResourceCache.h"
#include "../IO/FileSystem.h"
#include "../Input/InputEvents.h"
#include "../Container/HashMap.h"

#include <TurboBadger/tb_font_renderer.h>
#include <TurboBadger/tb_widgets.h>
#include <TurboBadger/tb_bitmap_fragment.h>
#include <TurboBadger/tb_system.h>
#include <TurboBadger/tb_msg.h>
#include <TurboBadger/tb_language.h>
#include <TurboBadger/animation/tb_animation.h>
#include <TurboBadger/animation/tb_widget_animation.h>

#include "UTBMain.h"
#include "UTBRendererBatcher.h"
#include "UTBDemo.h"

#include "../DebugNew.h"

#include <cassert>

namespace Urho3D
{

//=============================================================================
//=============================================================================
UTBMain::UTBMain(Context *_context, int _width, int _height)
    : UIElement( _context )
{
    // only a single instance of UTBMain can be created, do this by checking the singleton ptr
    assert( &UTBRendererBatcher::Singleton() == NULL );

    UTBRendererBatcher::Create( _context, _width, _height );
}

//=============================================================================
//=============================================================================
UTBMain::~UTBMain()
{
    LanguageHashMap_.Clear();
    UTBRendererBatcher::Destroy();
}

//=============================================================================
//=============================================================================
void UTBMain::Init(const String &_strDataPath)
{
    GetSubsystem<UI>()->GetRoot()->AddChild( this );

    UTBRendererBatcher::Singleton().Init( _strDataPath );

    // store data path
    strDataPath_ = GetSubsystem<FileSystem>()->GetProgramDir() + _strDataPath;

    // load resources
    LoadDefaultResources();
    
    // create language map
    CreateLanguageMap();
}

//=============================================================================
//=============================================================================
void UTBMain::RunDemo()
{
#ifdef URHO3D_TB_DEMO
    UTBDemo::Start();
#endif
}

//=============================================================================
//=============================================================================
TBWidget& UTBMain::Root() 
{ 
    return UTBRendererBatcher::Singleton().Root(); 
}

//=============================================================================
//=============================================================================
void UTBMain::CreateLanguageMap()
{
    // default to en
    strLanguageSetting_ = "en";

    LanguageHashMap_.Insert( Pair<String,String>( "en", "resources/language/lng_en.tb.txt" ) );
    LanguageHashMap_.Insert( Pair<String,String>( "sv", "resources/language/lng_sv.tb.txt" ) );
}

//=============================================================================
//=============================================================================
const String& UTBMain::GetLanguageSetting()
{
    return strLanguageSetting_;
}

//=============================================================================
//=============================================================================
bool UTBMain::SetLanguage(const String &_strLang)
{
    HashMap<String, String>::Iterator itr = LanguageHashMap_.Find( _strLang.ToLower() );
    bool bset = false;

    // avoid arbitrarily clearing TB language without first verifying the new language file exists
    if ( itr != LanguageHashMap_.End() )
    {
        String strName = itr->second_;
        String filenamePath = strDataPath_ + strName;

        if ( GetSubsystem<FileSystem>()->FileExists( filenamePath ) )
        {
            g_tb_lng->Clear();

            if ( g_tb_lng->Load( strName.CString() ) )
            {
                strLanguageSetting_ = _strLang.ToLower();
                bset = true;
            }
            else
            {
                // restore previous setting
                itr = LanguageHashMap_.Find( strLanguageSetting_.ToLower() );

                if ( itr != LanguageHashMap_.End() )
                {
                    g_tb_lng->Load( itr->second_.CString() );
                }
            }
        }
    }
    return bset;
}

//=============================================================================
//=============================================================================
bool UTBMain::AddLanguageType(const String &_strAbbr, const String &_strFilename)
{
    HashMap<String, String>::Iterator itr = LanguageHashMap_.Find( _strAbbr.ToLower() );
    bool binserted = false;

    // add it if the type doesn't exist
    if ( itr == LanguageHashMap_.End() )
    {
        String filenamePath = strDataPath_ + _strFilename;

        if ( GetSubsystem<FileSystem>()->FileExists( filenamePath ) )
        {
            LanguageHashMap_.Insert( Pair<String,String>( _strAbbr.ToLower(), _strFilename ) );
            binserted = true;
        }
    }
    return binserted;
}

//=============================================================================
//=============================================================================
bool UTBMain::AddFontInfo(const String &_strFilename, const String &_strName)
{
    String filenamePath = strDataPath_ + _strFilename;
    bool badded = false;

    if ( GetSubsystem<FileSystem>()->FileExists( filenamePath ) )
    {
        g_font_manager->AddFontInfo( _strFilename.CString(), _strName.CString() );
        badded = true;
    }
    return badded;
}

//=============================================================================
//=============================================================================
bool UTBMain::SetSkinBackground(const String &_strSkinName)
{
    Root().SetSkinBg( TBIDC( _strSkinName.CString() ) );

    return true;
}

//=============================================================================
//=============================================================================
void UTBMain::LoadDefaultResources()
{
    g_tb_lng->Load("resources/language/lng_en.tb.txt");

    // Load the default skin, and override skin that contains the graphics specific to the demo.
    g_tb_skin->Load("resources/default_skin/skin.tb.txt", "demo01/skin/skin.tb.txt");

#ifdef TB_FONT_RENDERER_TBBF
    void register_tbbf_font_renderer();
    register_tbbf_font_renderer();
#endif
#ifdef TB_FONT_RENDERER_STB
    void register_stb_font_renderer();
    register_stb_font_renderer();
#endif
#ifdef TB_FONT_RENDERER_FREETYPE
    void register_freetype_font_renderer();
    register_freetype_font_renderer();
#endif

    // Add fonts we can use to the font manager.
#if defined(TB_FONT_RENDERER_STB) || defined(TB_FONT_RENDERER_FREETYPE)
    g_font_manager->AddFontInfo("resources/vera.ttf", "Vera");
#endif
#ifdef TB_FONT_RENDERER_TBBF
    g_font_manager->AddFontInfo("resources/default_font/segoe_white_with_shadow.tb.txt", "Segoe");
    g_font_manager->AddFontInfo("fonts/neon.tb.txt", "Neon");
    g_font_manager->AddFontInfo("fonts/orangutang.tb.txt", "Orangutang");
    g_font_manager->AddFontInfo("fonts/orange.tb.txt", "Orange");
#endif

    // Set the default font description for widgets to one of the fonts we just added
    TBFontDescription fd;
#ifdef TB_FONT_RENDERER_TBBF
    fd.SetID(TBIDC("Segoe"));
#else
    fd.SetID(TBIDC("Vera"));
#endif
    fd.SetSize(g_tb_skin->GetDimensionConverter()->DpToPx(14));
    g_font_manager->SetDefaultFontDescription(fd);

    // Create the font now.
    TBFontFace *font = g_font_manager->CreateFontFace(g_font_manager->GetDefaultFontDescription());

    // Render some glyphs in one go now since we know we are going to use them. It would work fine
    // without this since glyphs are rendered when needed, but with some extra updating of the glyph bitmap.
    if ( font )
    {
        font->RenderGlyphs(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ï∑Â‰ˆ≈ƒ÷");
    }

    Root().SetSkinBg( TBIDC( "background" ) );
}


} //namespace Urho3D
