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
    : Object( _context )
{
    // only a single instance of UTBMain can be created
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
    UTBRendererBatcher::Singleton().Init( _strDataPath );

    // set language map
    strDataPath_ = GetSubsystem<FileSystem>()->GetProgramDir() + _strDataPath;
    InitLanguage();
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
void UTBMain::InitLanguage()
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
    UTBRendererBatcher::Singleton().Root().SetSkinBg( TBIDC( _strSkinName.CString() ) );

    return true;
}


} //namespace Urho3D
