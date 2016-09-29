//
// Copyright (c) 2008-2016 the Urho3D project.
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

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../Core/CoreEvents.h"
#include "../Core/Profiler.h"
#include "../Container/Vector.h"
#include "../Graphics/Graphics.h"
#include "../Graphics/GraphicsEvents.h"
#include "../Graphics/ShaderVariation.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/VertexBuffer.h"
#include "../Input/Input.h"
#include "../Input/InputEvents.h"
#include "../IO/Log.h"
#include "../Math/Matrix3x4.h"
#include "../Resource/ResourceCache.h"
#include "../UI/Cursor.h"
#include "../Resource/Image.h"
#include "imgui/imgui.h"
#include "../IMUI/IMUI.h"
#include "../Network/Network.h"
#include "../Graphics/IndexBuffer.h"
#include "../IO/Log.h"
#include "../IO/FileSystem.h"
#include <SDL/SDL.h>

#include "../DebugNew.h"

namespace Urho3D
{
#define TOUCHID_MASK(id) (1 << id)

	ImVec2 ToImVec2(const String& source)
	{
		ImVec2 ret;

		unsigned elements = CountElements(source.CString(), ' '); //source.Split(' ').Size(); //
		if (elements < 2)
			return ret;

		char* ptr = (char*)source.CString();
		ret.x = (float)strtod(ptr, &ptr);
		ret.y = (float)strtod(ptr, &ptr);

		return ret;
	}

	ImVec4 ToImVec4(const String& source)
	{
		ImVec4 ret;

		unsigned elements = CountElements(source.CString(), ' '); //source.Split(' ').Size(); //
		if (elements < 4)
			return ret;

		char* ptr = (char*)source.CString();
		ret.x = (float)strtod(ptr, &ptr);
		ret.y = (float)strtod(ptr, &ptr);
		ret.z = (float)strtod(ptr, &ptr);
		ret.w = (float)strtod(ptr, &ptr);

		return ret;
	}

	String ToString(const ImVec2& vec2)
	{
		char tempBuffer[256];
		sprintf(tempBuffer, "%.g %.g", vec2.x, vec2.y);
		return String(tempBuffer);
	}

	String ToString(const ImVec4& vec4)
	{
		char tempBuffer[256];
		sprintf(tempBuffer, "%.g %.g %.g %.g", vec4.x, vec4.y, vec4.z, vec4.w);
		return String(tempBuffer);
	}

	static IMUI* g_IMUI = NULL;

	static const char* ImGui_GetClipboardText()
	{
		return SDL_GetClipboardText();
	}

	static void ImGui_SetClipboardText(const char* text)
	{
		SDL_SetClipboardText(text);
	}

	// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
	// If text or lines are blurry when integrating ImGui in your engine:
	// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
	static void ImGui_RenderDrawLists(ImDrawData* data)
	{
		if (g_IMUI)
		{
			g_IMUI->RenderDrawLists(data);
		}
	}

	IMUI::IMUI(Context* context) : Object(context),
		initialized_(false),
		debugMenu_(false),
		graphics_(NULL),
		input_(NULL),
		fontTexture_(NULL),
		touchId_(-1),
		touch_(false),
#if defined(ANDROID) || defined(IOS)
		useScreenKeyboard_(true)
#else
		useScreenKeyboard_(false)
#endif

	{
		assert(!g_IMUI);

		SubscribeToEvent(E_SCREENMODE, URHO3D_HANDLER(IMUI, HandleScreenMode));
		// Try to initialize right now, but skip if screen mode is not yet set
		Initialize();
		g_IMUI = this;
	}

	IMUI::~IMUI()
	{
		Shutdown();
		g_IMUI = NULL;
	}

	void IMUI::SetSettings(const IMUISettings& settings)
	{
		settings_ = settings;
		if(initialized_)
		{
			ImGuiIO& io = ImGui::GetIO();

			ResourceCache* cache = GetSubsystem<ResourceCache>();
			// TODO: is a hack!
			String dataAssetPath = cache->GetResourceDirs()[0];

			// setup core imgui settings
			io.IniSavingRate = settings.mIniSavingRate;
			io.MouseDoubleClickTime = settings.mMouseDoubleClickTime;
			io.MouseDoubleClickMaxDist = settings.mMouseDoubleClickMaxDist;
			io.MouseDragThreshold = settings.mMouseDragThreshold;
			io.KeyRepeatDelay = settings.mKeyRepeatDelay;
			io.KeyRepeatRate = settings.mKeyRepeatRate;
			io.FontGlobalScale = settings.mFontGlobalScale;
			io.FontAllowUserScaling = settings.mFontAllowUserScaling;
			io.DisplayFramebufferScale = settings.mDisplayFramebufferScale;
			io.DisplayVisibleMin = settings.mDisplayVisibleMin;
			io.DisplayVisibleMax = settings.mDisplayVisibleMax;
			iniFilename_ = dataAssetPath + settings.mIniFilename;
			logFilename_ = dataAssetPath + settings.mLogFilename;
			io.IniFilename = iniFilename_.CString();
			io.LogFilename = logFilename_.CString();

			// setup fonts
			ImFontAtlas* fontAtlas = ImGui::GetIO().Fonts;
			fontAtlas->Clear();
			fonts_.Clear();

			// if no fonts added, add default font 	
			 if (settings.mFonts.Empty())  // does not work if font provied by settings are all in merge mode, need one font already loaded		
				io.Fonts->AddFontDefault();

			const HashMap< StringHash, IMUISettings::FontConfig >& fontconfigs_map = settings.getFonts();
			HashMap< StringHash, IMUISettings::FontConfig >::ConstIterator it;

			for (it = fontconfigs_map.Begin(); it != fontconfigs_map.End(); it++)
			{
				String name = GetFileName(it->second_.filename_);
				fonts_[name] = io.Fonts->AddFontFromFileTTF(cache->GetResourceFileName(it->second_.filename_).CString(),
					it->second_.size_, &it->second_.config_, it->second_.glyphRanges_.Empty() ? NULL : &it->second_.glyphRanges_[0]);
			}

			// setup font Texture
			if (fontTexture_)
			{
				delete fontTexture_;
				fontTexture_ = NULL;
			}
			unsigned char* pixels;
			int width, height;
			io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   
			fontTexture_ = new Texture2D(context_);
		//	SharedPtr<Urho3D::Image> image(new Urho3D::Image(context_));
		//	image->SetSize(width, height, 4);
		//	image->SetData(pixels);
		//	fontTexture_->SetData(image, false);
			fontTexture_->SetNumLevels(1);
			fontTexture_->SetSize(width, height, Graphics::GetRGBAFormat());
			fontTexture_->SetData(0, 0, 0, width, height, pixels);
			fontTexture_->SetFilterMode(FILTER_NEAREST);
			
			// Store our identifier
			io.Fonts->TexID = (void *)(intptr_t)fontTexture_;
			
			io.Fonts->ClearTexData();

			// set style
			const ImGuiStyle& style = settings.getStyle();
			ImGuiStyle& imGuiStyle = ImGui::GetStyle();
			imGuiStyle.Alpha = style.Alpha;
			imGuiStyle.WindowPadding = style.WindowPadding;
			imGuiStyle.WindowMinSize = style.WindowMinSize;
			imGuiStyle.WindowRounding = style.WindowRounding;
			imGuiStyle.WindowTitleAlign = style.WindowTitleAlign;
			imGuiStyle.ChildWindowRounding = style.ChildWindowRounding;
			imGuiStyle.FramePadding = style.FramePadding;
			imGuiStyle.FrameRounding = style.FrameRounding;
			imGuiStyle.ItemSpacing = style.ItemSpacing;
			imGuiStyle.ItemInnerSpacing = style.ItemInnerSpacing;
			imGuiStyle.TouchExtraPadding = style.TouchExtraPadding;
			imGuiStyle.IndentSpacing = style.IndentSpacing;
			imGuiStyle.ColumnsMinSpacing = style.ColumnsMinSpacing;
			imGuiStyle.ScrollbarSize = style.ScrollbarSize;
			imGuiStyle.ScrollbarRounding = style.ScrollbarRounding;
			imGuiStyle.GrabMinSize = style.GrabMinSize;
			imGuiStyle.GrabRounding = style.GrabRounding;
			imGuiStyle.DisplayWindowPadding = style.DisplayWindowPadding;
			imGuiStyle.DisplaySafeAreaPadding = style.DisplaySafeAreaPadding;
			imGuiStyle.AntiAliasedLines = style.AntiAliasedLines;
			imGuiStyle.AntiAliasedShapes = style.AntiAliasedShapes;

			// set colors
			for (int i = 0; i < ImGuiCol_COUNT; i++)
				imGuiStyle.Colors[i] = style.Colors[i];
		}
	}

	bool IMUI::LoadStyleXML(Deserializer& source, ImGuiStyle* outStyle)
	{
		SharedPtr<XMLFile> xml(new XMLFile(context_));
		if (!xml->Load(source))
			return false;
		return LoadStyleXML(xml->GetRoot());
	}

	bool IMUI::SaveStyleXML(Serializer& dest, ImGuiStyle* outStyle, const String& indentation) const
	{
		SharedPtr<XMLFile> xml(new XMLFile(context_));
		XMLElement rootElem = xml->CreateRoot("ImGuiStyle");
		if (!SaveStyleXML(rootElem))
			return false;
		return xml->Save(dest, indentation);
	}

	bool IMUI::LoadStyleXML(const XMLElement& source, ImGuiStyle* outStyle, bool setInstanceDefault)
	{
		ImGuiStyle* style = outStyle;
		// if no output style defined use default style
		if (!style)
			style = &ImGui::GetStyle();

		style->Alpha = source.GetChild("Alpha").GetFloat("value");
		style->WindowPadding = ToImVec2(source.GetChild("WindowPadding").GetAttribute("value"));
		style->WindowMinSize = ToImVec2(source.GetChild("WindowMinSize").GetAttribute("value"));
		style->WindowRounding = source.GetChild("WindowRounding").GetFloat("value");
		style->WindowTitleAlign = source.GetChild("WindowTitleAlign").GetInt("value");
		style->ChildWindowRounding = source.GetChild("ChildWindowRounding").GetFloat("value");
		style->FramePadding = ToImVec2(source.GetChild("FramePadding").GetAttribute("value"));
		style->FrameRounding = source.GetChild("FrameRounding").GetFloat("value");
		style->ItemSpacing = ToImVec2(source.GetChild("ItemSpacing").GetAttribute("value"));
		style->ItemInnerSpacing = ToImVec2(source.GetChild("ItemInnerSpacing").GetAttribute("value"));
		style->TouchExtraPadding = ToImVec2(source.GetChild("TouchExtraPadding").GetAttribute("value"));
		style->IndentSpacing = source.GetChild("IndentSpacing").GetFloat("value");
		style->ColumnsMinSpacing = source.GetChild("ColumnsMinSpacing").GetFloat("value");
		style->ScrollbarSize = source.GetChild("ScrollbarSize").GetFloat("value");
		style->ScrollbarRounding = source.GetChild("ScrollbarRounding").GetFloat("value");
		style->GrabMinSize = source.GetChild("GrabMinSize").GetFloat("value");
		style->GrabRounding = source.GetChild("GrabRounding").GetFloat("value");
		style->DisplayWindowPadding = ToImVec2(source.GetChild("DisplayWindowPadding").GetAttribute("value"));
		style->DisplaySafeAreaPadding = ToImVec2(source.GetChild("DisplaySafeAreaPadding").GetAttribute("value"));
		style->AntiAliasedLines = source.GetChild("AntiAliasedLines").GetFloat("value");
		style->AntiAliasedShapes = source.GetChild("AntiAliasedShapes").GetFloat("value");
		style->CurveTessellationTol = source.GetChild("CurveTessellationTol").GetFloat("value");


		XMLElement colors = source.GetChild("Colors");
		for (unsigned i = 0; i < ImGuiCol_COUNT; i++)
		{
			style->Colors[i] = ToImVec4(colors.GetChild(ImGui::GetStyleColName(i)).GetAttribute("value"));
		}

		return true;
	}

	bool IMUI::SaveStyleXML(XMLElement& dest, ImGuiStyle* outStyle) const
	{
		ImGuiStyle* style = outStyle;
		// if no output style defined use default style
		if (!style)
			style = &ImGui::GetStyle();

		dest.CreateChild("Alpha").SetFloat("value", style->Alpha);
		dest.CreateChild("WindowPadding").SetAttribute("value", ToString(style->WindowPadding));
		dest.CreateChild("WindowMinSize").SetAttribute("value", ToString(style->WindowMinSize));
		dest.CreateChild("WindowRounding").SetFloat("value", style->WindowRounding);
		dest.CreateChild("WindowTitleAlign").SetInt("value", style->WindowTitleAlign);
		dest.CreateChild("ChildWindowRounding").SetFloat("value", style->ChildWindowRounding);
		dest.CreateChild("FramePadding").SetAttribute("value", ToString(style->FramePadding));
		dest.CreateChild("FrameRounding").SetFloat("value", style->FrameRounding);
		dest.CreateChild("ItemSpacing").SetAttribute("value", ToString(style->ItemSpacing));
		dest.CreateChild("ItemInnerSpacing").SetAttribute("value", ToString(style->ItemInnerSpacing));
		dest.CreateChild("TouchExtraPadding").SetAttribute("value", ToString(style->TouchExtraPadding));
		dest.CreateChild("IndentSpacing").SetFloat("value", style->IndentSpacing);
		dest.CreateChild("ColumnsMinSpacing").SetFloat("value", style->ColumnsMinSpacing);
		dest.CreateChild("ScrollbarSize").SetFloat("value", style->ScrollbarSize);
		dest.CreateChild("ScrollbarRounding").SetFloat("value", style->ScrollbarRounding);
		dest.CreateChild("GrabMinSize").SetFloat("value", style->GrabMinSize);
		dest.CreateChild("GrabRounding").SetFloat("value", style->GrabRounding);
		dest.CreateChild("DisplayWindowPadding").SetAttribute("value", ToString(style->DisplayWindowPadding));
		dest.CreateChild("DisplaySafeAreaPadding").SetAttribute("value", ToString(style->DisplaySafeAreaPadding));
		dest.CreateChild("AntiAliasedLines").SetFloat("value", style->AntiAliasedLines);
		dest.CreateChild("AntiAliasedShapes").SetFloat("value", style->AntiAliasedShapes);
		dest.CreateChild("CurveTessellationTol").SetFloat("value", style->CurveTessellationTol);

		XMLElement colors =dest.CreateChild("Colors");
		for (unsigned i = 0; i < ImGuiCol_COUNT; i++)
		{
			colors.CreateChild(ImGui::GetStyleColName(i)).SetAttribute("value", ToString(style->Colors[i]));
		}

		return true;
	}

	void IMUI::PushFont(const String& name)
	{
		HashMap<StringHash, ImFont* >::ConstIterator it =  fonts_.Find(name);
		if(it == fonts_.End())
		{
			//URHO3D_LOGERRORF("IMUI::PushFont: Font %s not found!! ",name.CString());  will be called multiple times -> use assert ?  
			return;
		}

		ImGui::PushFont(it->second_);
	}

	void IMUI::PopFont()
	{
		ImGui::PopFont();
	}

	void IMUI::Initialize()
	{
		Graphics* graphics = GetSubsystem<Graphics>();
		if (!graphics || !graphics->IsInitialized())
			return;
		if (initialized_)
			return;

		graphics_ = graphics;
		screenSize_ = IntRect(0, 0, graphics->GetWidth(), graphics->GetHeight());
		vertexBuffer_ = new VertexBuffer(context_);
		indexBuffer_ = new IndexBuffer(context_);
		input_ = GetSubsystem<Input>();

		SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(IMUI, HandleBeginFrame));
		SubscribeToEvent(E_ENDRENDERING, URHO3D_HANDLER(IMUI, HandleEndRendering));

		SubscribeToEvent(E_KEYUP, URHO3D_HANDLER(IMUI, HandleKeyUp));
		SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(IMUI, HandleKeyDown));
		SubscribeToEvent(E_TEXTINPUT, URHO3D_HANDLER(IMUI, HandleTextInput));

		SubscribeToEvent(E_TOUCHBEGIN, URHO3D_HANDLER(IMUI, HandleTouchBegin));
		SubscribeToEvent(E_TOUCHEND, URHO3D_HANDLER(IMUI, HandleTouchEnd));
		SubscribeToEvent(E_TOUCHMOVE, URHO3D_HANDLER(IMUI, HandleTouchMove));

		/// init imgui
		ImGuiIO& io = ImGui::GetIO();

		io.UserData = (void*) this;

		io.KeyMap[ImGuiKey_Tab] = SCANCODE_TAB;                 // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
		io.KeyMap[ImGuiKey_LeftArrow] = SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_Home] = SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SCANCODE_END;
		io.KeyMap[ImGuiKey_Delete] = SCANCODE_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SCANCODE_BACKSPACE;
		io.KeyMap[ImGuiKey_Enter] = SCANCODE_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SCANCODE_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SCANCODE_A;
		io.KeyMap[ImGuiKey_C] = SCANCODE_C;
		io.KeyMap[ImGuiKey_V] = SCANCODE_V;
		io.KeyMap[ImGuiKey_X] = SCANCODE_X;
		io.KeyMap[ImGuiKey_Y] = SCANCODE_Y;
		io.KeyMap[ImGuiKey_Z] = SCANCODE_Z;

		// setup callback functions
		io.RenderDrawListsFn = ImGui_RenderDrawLists;
		io.SetClipboardTextFn = ImGui_SetClipboardText;
		io.GetClipboardTextFn = ImGui_GetClipboardText;

		initialized_ = true;
		SetSettings(settings_);
		URHO3D_LOGINFO("IMUI::Initialized");
	}

	void IMUI::Shutdown()
	{
		ImGui::Shutdown();
		if (fontTexture_)
		{
			delete fontTexture_;
			fontTexture_ = NULL;
		}
		URHO3D_LOGINFO("IMUI::Shutdown");
	}

	void IMUI::HandleScreenMode(StringHash eventType, VariantMap& eventData)
	{
		using namespace ScreenMode;

		if (!initialized_)
			Initialize();
		else
		{
			screenSize_ = IntRect(0, 0, eventData[P_WIDTH].GetInt(), eventData[P_HEIGHT].GetInt());
		}
	}

	void IMUI::HandleBeginFrame(StringHash eventType, VariantMap& eventData)
	{
		URHO3D_PROFILE(IMUI_BeginFrame);
		using namespace BeginFrame;
		float timeStep = eventData[P_TIMESTEP].GetFloat();

		// Setup display size (every frame to accommodate for window resizing)
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)graphics_->GetWidth(), (float)graphics_->GetHeight());

		// Setup time step
		io.DeltaTime = timeStep > 0.0f ? timeStep : 1.0f / 60.0f;

		// Setup inputs
		// mouse input handling
		if (input_->IsMouseVisible() && !input_->GetTouchEmulation())
		{
			IntVector2 pos = input_->GetMousePosition();
			// Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
			io.MousePos.x = (float)pos.x_;
			io.MousePos.y = (float)pos.y_;
		}
		else
		{
			io.MousePos.x = -1.0f;
			io.MousePos.y = -1.0f;
		}
		// TODO: Joystick input handling

		// TODO: touch input handling
		if (touchId_ != -1)
		{
			io.MousePos.x = (float)touchPos_.x_;
			io.MousePos.y = (float)touchPos_.y_;
			io.MouseDown[0] = touch_;
			// disable tracking
			if (!touch_)
				touchId_ = -1;
		}
		else
			io.MouseDown[0] = input_->GetMouseButtonDown(MOUSEB_LEFT);

		io.MouseDown[1] = input_->GetMouseButtonDown(MOUSEB_RIGHT);
		io.MouseDown[2] = input_->GetMouseButtonDown(MOUSEB_MIDDLE);
		io.MouseWheel = (float)input_->GetMouseMoveWheel();

		io.KeyCtrl = input_->GetQualifierDown(QUAL_CTRL);
		io.KeyShift = input_->GetQualifierDown(QUAL_SHIFT);
		io.KeyAlt = input_->GetQualifierDown(QUAL_ALT);

		// Start the frame
		ImGui::NewFrame();

		// show screenkeyboard on text edit
		if (useScreenKeyboard_)
			input_->SetScreenKeyboardVisible(io.WantTextInput);
	}

	void IMUI::HandleEndRendering(StringHash eventType, VariantMap& eventData)
	{
		URHO3D_PROFILE(IMUI_Rendering);
		ImGui::Render();
	}

	void IMUI::HandleKeyUp(StringHash eventType, VariantMap& eventData)
	{
		using namespace KeyUp;

		ImGuiIO& io = ImGui::GetIO();
		//	int key = eventData[P_KEY].GetInt();
		int Scancode = eventData[P_SCANCODE].GetInt();
		//	int Qualifiers = eventData[P_QUALIFIERS].GetInt();
		if (Scancode < 512)
			io.KeysDown[Scancode] = false;
	}

	void IMUI::HandleKeyDown(StringHash eventType, VariantMap& eventData)
	{
		using namespace KeyDown;
		ImGuiIO& io = ImGui::GetIO();
		//	int key = eventData[P_KEY].GetInt();
		int Scancode = eventData[P_SCANCODE].GetInt();
		//	int Qualifiers = eventData[P_QUALIFIERS].GetInt();
		if (Scancode < 512)
			io.KeysDown[Scancode] = true;
	}

	void IMUI::HandleTextInput(StringHash eventType, VariantMap& eventData)
	{
		using namespace TextInput;
		const String& text = eventData[P_TEXT].GetString();
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharactersUTF8(text.CString());
	}

	void IMUI::HandleTouchBegin(StringHash eventType, VariantMap& eventData)
	{
		using namespace TouchBegin;
		/// check if already tracking of the first touch point
		if (touchId_ == -1)
		{
			// Get the touch index
			touchId_ = TOUCHID_MASK(eventData[P_TOUCHID].GetInt());
			touchPos_.x_ = eventData[P_X].GetInt();
			touchPos_.y_ = eventData[P_Y].GetInt();
			touch_ = true;
		}
		// track only the first touch point
	}

	void IMUI::HandleTouchEnd(StringHash eventType, VariantMap& eventData)
	{
		using namespace TouchEnd;
		// Get the touch index
		int touchId = TOUCHID_MASK(eventData[P_TOUCHID].GetInt());
		// check if touchid is the tracked one
		if (touchId_ == touchId)
		{
			touchPos_.x_ = eventData[P_X].GetInt();
			touchPos_.y_ = eventData[P_Y].GetInt();
			touch_ = false;
		}
	}

	void IMUI::HandleTouchMove(StringHash eventType, VariantMap& eventData)
	{
		using namespace TouchMove;
		// Get the touch index
		int touchId = TOUCHID_MASK(eventData[P_TOUCHID].GetInt());
		// check if touchid is the tracked one
		if (touchId_ == touchId)
		{
			touchPos_.x_ = eventData[P_X].GetInt();
			touchPos_.y_ = eventData[P_Y].GetInt();
		}
	}

	void IMUI::RenderDrawLists(ImDrawData* data)
	{
		ImDrawList** const cmd_lists = data->CmdLists;
		int cmd_lists_count = data->CmdListsCount;

		// Engine does not render when window is closed or device is lost
		assert(graphics_ && graphics_->IsInitialized() && !graphics_->IsDeviceLost());

		if (cmd_lists_count == 0)
			return;

		Vector2 invScreenSize(1.0f / (float)graphics_->GetWidth(), 1.0f / (float)graphics_->GetHeight());
		Vector2 scale(2.0f * invScreenSize.x_, -2.0f * invScreenSize.y_);
		Vector2 offset(-1.0f, 1.0f);

		Matrix4 projection(Matrix4::IDENTITY);
		projection.m00_ = scale.x_;
		projection.m03_ = offset.x_;
		projection.m11_ = scale.y_;
		projection.m13_ = offset.y_;
		projection.m22_ = 1.0f;
		projection.m23_ = 0.0f;
		projection.m33_ = 1.0f;

		graphics_->ClearParameterSources();
		graphics_->SetColorWrite(true);
		graphics_->SetCullMode(CULL_NONE);
		graphics_->SetDepthTest(CMP_ALWAYS);
		graphics_->SetDepthWrite(false);
		graphics_->SetFillMode(FILL_SOLID);
		graphics_->SetStencilTest(false);
		graphics_->ResetRenderTargets();
		graphics_->SetBlendMode(BLEND_ALPHA);

		ShaderVariation* noTextureVS = graphics_->GetShader(VS, "IMGUI", "VERTEXCOLOR");
		ShaderVariation* diffTextureVS = graphics_->GetShader(VS, "IMGUI", "DIFFMAP VERTEXCOLOR");
		ShaderVariation* noTexturePS = graphics_->GetShader(PS, "IMGUI", "VERTEXCOLOR");
		ShaderVariation* diffTexturePS = graphics_->GetShader(PS, "IMGUI", "DIFFMAP VERTEXCOLOR");
		ShaderVariation* diffMaskTexturePS = graphics_->GetShader(PS, "IMGUI", "DIFFMAP ALPHAMASK VERTEXCOLOR");
		ShaderVariation* alphaTexturePS = graphics_->GetShader(PS, "IMGUI", "ALPHAMAP VERTEXCOLOR");

		unsigned alphaFormat = Graphics::GetAlphaFormat();

		/// resize buffers
#if defined(URHO3D_D3D11)
		// TODO: for D3D11 : cannot set vertex/index buffer to dynamic. bug ? does it need to be dynamic ?
		if ((int)vertexBuffer_->GetVertexCount() < data->TotalVtxCount || (int)vertexBuffer_->GetVertexCount() > data->TotalVtxCount * 2)
			vertexBuffer_->SetSize(data->TotalVtxCount, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1, false);

		if ((int)indexBuffer_->GetIndexCount() < data->TotalIdxCount || (int)indexBuffer_->GetIndexCount() > data->TotalIdxCount * 2)
			indexBuffer_->SetSize(data->TotalIdxCount, false, false);
#else
		if ((int)vertexBuffer_->GetVertexCount() < data->TotalVtxCount || (int)vertexBuffer_->GetVertexCount() > data->TotalVtxCount * 2)
			vertexBuffer_->SetSize(data->TotalVtxCount, MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1, true);

		if ((int)indexBuffer_->GetIndexCount() < data->TotalIdxCount || (int)indexBuffer_->GetIndexCount() > data->TotalIdxCount * 2)
			indexBuffer_->SetSize(data->TotalIdxCount, false, true);
#endif

		// Copy and convert all vertices into a single contiguous buffer

		// 		int vtx_list_offset = 0;
		// 		int idx_list_offset = 0;
		// 		for (int n = 0; n < data->CmdListsCount; n++)
		// 		{
		// 			const ImDrawList* cmd_list = data->CmdLists[n];
		//
		// 			vertexBuffer_->SetDataRange(&cmd_list->VtxBuffer[0], vtx_list_offset, cmd_list->VtxBuffer.size());
		// 			indexBuffer_->SetDataRange(&cmd_list->IdxBuffer[0], idx_list_offset, cmd_list->IdxBuffer.size());
		//
		// 			vtx_list_offset += cmd_list->VtxBuffer.size();
		// 			idx_list_offset += cmd_list->IdxBuffer.size();
		// 		}

#ifndef GL_ES_VERSION_2_0
		ImDrawVert* vtx_dst = (ImDrawVert*)vertexBuffer_->Lock(0, data->TotalVtxCount);
		ImDrawIdx* idx_dst = (ImDrawIdx*)indexBuffer_->Lock(0, data->TotalIdxCount);
		for (int n = 0; n < data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = data->CmdLists[n];
			memcpy(vtx_dst, &cmd_list->VtxBuffer[0], cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
			memcpy(idx_dst, &cmd_list->IdxBuffer[0], cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
			vtx_dst += cmd_list->VtxBuffer.size();
			idx_dst += cmd_list->IdxBuffer.size();
		}
		vertexBuffer_->Unlock();
		indexBuffer_->Unlock();
#endif

		graphics_->SetVertexBuffer(vertexBuffer_);
		graphics_->SetIndexBuffer(indexBuffer_);

		// Render command lists
		int vtx_offset = 0;
		int idx_offset = 0;
		for (int n = 0; n < data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = data->CmdLists[n];
#ifdef GL_ES_VERSION_2_0

			vertexBuffer_->SetDataRange(&cmd_list->VtxBuffer[0], 0, cmd_list->VtxBuffer.size());
			indexBuffer_->SetDataRange(&cmd_list->IdxBuffer[0], 0, cmd_list->IdxBuffer.size());

			idx_offset = 0;
#endif

			for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
			{
				const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
				if (pcmd->UserCallback)
				{
					pcmd->UserCallback(cmd_list, pcmd);
				}
				else
				{
					Texture* texture = (Urho3D::Texture*)(intptr_t)pcmd->TextureId;
					ShaderVariation* ps;
					ShaderVariation* vs;
					if (!texture)
					{
						ps = noTexturePS;
						vs = noTextureVS;
					}
					else
					{
						vs = diffTextureVS;
						// If texture contains only an alpha channel, use alpha shader (for fonts)
						if (texture->GetFormat() == alphaFormat)
							ps = alphaTexturePS;
						// 						else if (blendMode_ != BLEND_ALPHA && batch.blendMode_ != BLEND_ADDALPHA && batch.blendMode_ != BLEND_PREMULALPHA)
						//			 						ps = diffMaskTexturePS;
						else
							ps = diffTexturePS;
					}

					graphics_->SetShaders(vs, ps);

					if (graphics_->NeedParameterUpdate(SP_OBJECT, this))
						graphics_->SetShaderParameter(VSP_MODEL, Matrix3x4::IDENTITY);
					if (graphics_->NeedParameterUpdate(SP_CAMERA, this))
						graphics_->SetShaderParameter(VSP_VIEWPROJ, projection);
					if (graphics_->NeedParameterUpdate(SP_MATERIAL, this))
						graphics_->SetShaderParameter(PSP_MATDIFFCOLOR, Color(1.0f, 1.0f, 1.0f, 1.0f));

					graphics_->SetScissorTest(true, IntRect((int)pcmd->ClipRect.x, (int)(pcmd->ClipRect.y),
						(int)(pcmd->ClipRect.z), (int)(pcmd->ClipRect.w)));

					graphics_->SetTexture(0, texture);

#if defined(URHO3D_OPENGL)

#ifdef GL_ES_VERSION_2_0
					graphics_->Draw(TRIANGLE_LIST, idx_offset, pcmd->ElemCount, 0, cmd_list->VtxBuffer.size());
#else
					graphics_->Draw(TRIANGLE_LIST, idx_offset, pcmd->ElemCount, vtx_offset, 0, cmd_list->VtxBuffer.size());
#endif
#else
					graphics_->Draw(TRIANGLE_LIST, idx_offset, pcmd->ElemCount, vtx_offset, 0, cmd_list->VtxBuffer.size());
#endif
				}
				idx_offset += pcmd->ElemCount;
			}
			vtx_offset += cmd_list->VtxBuffer.size();
		}
	}
}