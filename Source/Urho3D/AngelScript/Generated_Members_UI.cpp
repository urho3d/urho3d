// DO NOT EDIT. This file is generated

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/GeneratedIncludes.h"
#include "../AngelScript/GeneratedClassMembers.h"
#include "../AngelScript/Manual.h"

namespace Urho3D
{

// struct CharLocation | File: ../UI/Text.h
void CollectMembers_CharLocation(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 CharLocation::position_", "Vector2 position", offsetof(CharLocation, position_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 CharLocation::size_", "Vector2 size", offsetof(CharLocation, size_)));

}

// struct CursorShapeInfo | File: ../UI/Cursor.h
void CollectMembers_CursorShapeInfo(MemberCollection& members)
{
    // SharedPtr<Image> CursorShapeInfo::image_
    // Error: type "SharedPtr<Image>" can not automatically bind
    // SharedPtr<Texture> CursorShapeInfo::texture_
    // Error: type "SharedPtr<Texture>" can not automatically bind
    // SDL_Cursor* CursorShapeInfo::osCursor_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("IntRect CursorShapeInfo::imageRect_", "IntRect imageRect", offsetof(CursorShapeInfo, imageRect_)));
    members.fields_.Push(RegisterObjectPropertyArgs("IntVector2 CursorShapeInfo::hotSpot_", "IntVector2 hotSpot", offsetof(CursorShapeInfo, hotSpot_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool CursorShapeInfo::systemDefined_", "bool systemDefined", offsetof(CursorShapeInfo, systemDefined_)));
    members.fields_.Push(RegisterObjectPropertyArgs("int CursorShapeInfo::systemCursor_", "int systemCursor", offsetof(CursorShapeInfo, systemCursor_)));

}

// struct FileSelectorEntry | File: ../UI/FileSelector.h
void CollectMembers_FileSelectorEntry(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("String FileSelectorEntry::name_", "String name", offsetof(FileSelectorEntry, name_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool FileSelectorEntry::directory_", "bool directory", offsetof(FileSelectorEntry, directory_)));

}

// struct FontGlyph | File: ../UI/FontFace.h
void CollectMembers_FontGlyph(MemberCollection& members)
{
    members.fields_.Push(RegisterObjectPropertyArgs("short FontGlyph::x_", "int16 x", offsetof(FontGlyph, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("short FontGlyph::y_", "int16 y", offsetof(FontGlyph, y_)));
    members.fields_.Push(RegisterObjectPropertyArgs("short FontGlyph::texWidth_", "int16 texWidth", offsetof(FontGlyph, texWidth_)));
    members.fields_.Push(RegisterObjectPropertyArgs("short FontGlyph::texHeight_", "int16 texHeight", offsetof(FontGlyph, texHeight_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FontGlyph::width_", "float width", offsetof(FontGlyph, width_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FontGlyph::height_", "float height", offsetof(FontGlyph, height_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FontGlyph::offsetX_", "float offsetX", offsetof(FontGlyph, offsetX_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FontGlyph::offsetY_", "float offsetY", offsetof(FontGlyph, offsetY_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float FontGlyph::advanceX_", "float advanceX", offsetof(FontGlyph, advanceX_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned FontGlyph::page_", "uint page", offsetof(FontGlyph, page_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool FontGlyph::used_", "bool used", offsetof(FontGlyph, used_)));

}

// struct GlyphLocation | File: ../UI/Text.h
void CollectMembers_GlyphLocation(MemberCollection& members)
{
    // const FontGlyph* GlyphLocation::glyph_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("float GlyphLocation::x_", "float x", offsetof(GlyphLocation, x_)));
    members.fields_.Push(RegisterObjectPropertyArgs("float GlyphLocation::y_", "float y", offsetof(GlyphLocation, y_)));

}

// class UIBatch | File: ../UI/UIBatch.h
void CollectMembers_UIBatch(MemberCollection& members)
{
    // static void UIBatch::AddOrMerge(const UIBatch& batch, PODVector<UIBatch>& batches)
    // Error: type "PODVector<UIBatch>&" can not automatically bind

    // UIElement* UIBatch::element_
    // Not registered because pointer
    // Texture* UIBatch::texture_
    // Not registered because pointer
    // PODVector<float>* UIBatch::vertexData_
    // Not registered because pointer
    // Material* UIBatch::customMaterial_
    // Not registered because pointer

    members.fields_.Push(RegisterObjectPropertyArgs("BlendMode UIBatch::blendMode_", "BlendMode blendMode", offsetof(UIBatch, blendMode_)));
    members.fields_.Push(RegisterObjectPropertyArgs("IntRect UIBatch::scissor_", "IntRect scissor", offsetof(UIBatch, scissor_)));
    members.fields_.Push(RegisterObjectPropertyArgs("Vector2 UIBatch::invTextureSize_", "Vector2 invTextureSize", offsetof(UIBatch, invTextureSize_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned UIBatch::vertexStart_", "uint vertexStart", offsetof(UIBatch, vertexStart_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned UIBatch::vertexEnd_", "uint vertexEnd", offsetof(UIBatch, vertexEnd_)));
    members.fields_.Push(RegisterObjectPropertyArgs("unsigned UIBatch::color_", "uint color", offsetof(UIBatch, color_)));
    members.fields_.Push(RegisterObjectPropertyArgs("bool UIBatch::useGradient_", "bool useGradient", offsetof(UIBatch, useGradient_)));

    members.staticFields_.Push(RegisterGlobalPropertyArgs("static Vector3 UIBatch::posAdjust", "Vector3 posAdjust", (void*)&UIBatch::posAdjust));

}

// class FontFace | File: ../UI/FontFace.h
void CollectMembers_FontFace(MemberCollection& members)
{
    CollectMembers_RefCounted(members);

    // virtual const FontGlyph* FontFace::GetGlyph(unsigned c)
    // Error: type "const FontGlyph*" can not automatically bind
    // virtual bool FontFace::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) = 0
    // Error: type "const unsigned char*" can not automatically bind

}

// class FileSelector | File: ../UI/FileSelector.h
void CollectMembers_FileSelector(MemberCollection& members)
{
    CollectMembers_Object(members);

    // static void FileSelector::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class FontFaceBitmap | File: ../UI/FontFaceBitmap.h
void CollectMembers_FontFaceBitmap(MemberCollection& members)
{
    CollectMembers_FontFace(members);

    Remove(members.methods_, "virtual bool FontFace::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) = 0");

}

// class FontFaceFreeType | File: ../UI/FontFaceFreeType.h
void CollectMembers_FontFaceFreeType(MemberCollection& members)
{
    CollectMembers_FontFace(members);

    Remove(members.methods_, "virtual bool FontFace::HasMutableGlyphs() const");
    Remove(members.methods_, "virtual bool FontFace::Load(const unsigned char* fontData, unsigned fontDataSize, float pointSize) = 0");
    Remove(members.methods_, "virtual const FontGlyph* FontFace::GetGlyph(unsigned c)");

}

// class MessageBox | File: ../UI/MessageBox.h
void CollectMembers_MessageBox(MemberCollection& members)
{
    CollectMembers_Object(members);

    // static void MessageBox::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class UI | File: ../UI/UI.h
void CollectMembers_UI(MemberCollection& members)
{
    CollectMembers_Object(members);

    // const Vector<UIElement*> UI::GetDragElements()
    // Error: type "const Vector<UIElement*>" can not automatically bind

}

// class Font | File: ../UI/Font.h
void CollectMembers_Font(MemberCollection& members)
{
    CollectMembers_Resource(members);

    Remove(members.methods_, "virtual bool Resource::BeginLoad(Deserializer& source)");

    // static void Font::RegisterObject(Context* context)
    // Not registered because have @nobind mark

}

// class UIElement | File: ../UI/UIElement.h
void CollectMembers_UIElement(MemberCollection& members)
{
    CollectMembers_Animatable(members);

    Remove(members.methods_, "bool Animatable::LoadXML(const XMLElement& source) override");
    Remove(members.methods_, "bool Animatable::SaveXML(XMLElement& dest) const override");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

    // virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetBatchesWithOffset(IntVector2& offset, PODVector<UIBatch>& batches, PODVector<float>& vertexData, IntRect currentScissor)
    // Error: type "PODVector<UIBatch>&" can not automatically bind
    // void UIElement::GetChildren(PODVector<UIElement*>& dest, bool recursive = false) const
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // void UIElement::GetChildrenWithTag(PODVector<UIElement*>& dest, const String& tag, bool recursive = false) const
    // Error: type "PODVector<UIElement*>&" can not automatically bind
    // virtual void UIElement::GetDebugDrawBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)
    // Error: type "PODVector<UIBatch>&" can not automatically bind

    // template <class T> T* UIElement::CreateChild(const String& name = String::EMPTY, unsigned index = M_MAX_UNSIGNED)
    // Not registered because template
    // template <class T> T* UIElement::GetChildDynamicCast(unsigned index) const
    // Not registered because template
    // template <class T> T* UIElement::GetChildDynamicCast(const String& name, bool recursive = false) const
    // Not registered because template
    // template <class T> T* UIElement::GetChildDynamicCast(const StringHash& key, const Variant& value = Variant::EMPTY, bool recursive = false) const
    // Not registered because template
    // template <class T> T* UIElement::GetChildStaticCast(unsigned index) const
    // Not registered because template
    // template <class T> T* UIElement::GetChildStaticCast(const String& name, bool recursive = false) const
    // Not registered because template
    // template <class T> T* UIElement::GetChildStaticCast(const StringHash& key, const Variant& value = Variant::EMPTY, bool recursive = false) const
    // Not registered because template

}

// class BorderImage | File: ../UI/BorderImage.h
void CollectMembers_BorderImage(MemberCollection& members)
{
    CollectMembers_UIElement(members);

    Remove(members.methods_, "virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)");

    Remove(members.staticMethods_, "static void UIElement::RegisterObject(Context* context)");

}

// class ScrollView | File: ../UI/ScrollView.h
void CollectMembers_ScrollView(MemberCollection& members)
{
    CollectMembers_UIElement(members);

    Remove(members.methods_, "virtual bool UIElement::IsWheelHandler() const");
    Remove(members.methods_, "virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)");
    Remove(members.methods_, "virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta)");
    Remove(members.methods_, "virtual void UIElement::OnWheel(int delta, MouseButtonFlags buttons, QualifierFlags qualifiers)");
    Remove(members.methods_, "virtual void UIElement::Update(float timeStep)");
    Remove(members.methods_, "void UIElement::ApplyAttributes() override");

    Remove(members.staticMethods_, "static void UIElement::RegisterObject(Context* context)");

}

// class Sprite | File: ../UI/Sprite.h
void CollectMembers_Sprite(MemberCollection& members)
{
    CollectMembers_UIElement(members);

    Remove(members.methods_, "const IntVector2& UIElement::GetPosition() const");
    Remove(members.methods_, "virtual IntVector2 UIElement::ElementToScreen(const IntVector2& position)");
    Remove(members.methods_, "virtual IntVector2 UIElement::ScreenToElement(const IntVector2& screenPosition)");
    Remove(members.methods_, "virtual bool UIElement::IsWithinScissor(const IntRect& currentScissor)");
    Remove(members.methods_, "virtual const IntVector2& UIElement::GetScreenPosition() const");
    Remove(members.methods_, "virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)");
    Remove(members.methods_, "virtual void UIElement::OnPositionSet(const IntVector2& newPosition)");
    Remove(members.methods_, "void UIElement::SetPosition(const IntVector2& position)");
    Remove(members.methods_, "void UIElement::SetPosition(int x, int y)");

    Remove(members.staticMethods_, "static void UIElement::RegisterObject(Context* context)");

}

// class ToolTip | File: ../UI/ToolTip.h
void CollectMembers_ToolTip(MemberCollection& members)
{
    CollectMembers_UIElement(members);

    Remove(members.methods_, "virtual void UIElement::Update(float timeStep)");

    Remove(members.staticMethods_, "static void UIElement::RegisterObject(Context* context)");

}

// class UIComponent | File: ../UI/UIComponent.h
void CollectMembers_UIComponent(MemberCollection& members)
{
    CollectMembers_Component(members);

    Remove(members.staticMethods_, "static void Animatable::RegisterObject(Context* context)");

}

// class UISelectable | File: ../UI/UISelectable.h
void CollectMembers_UISelectable(MemberCollection& members)
{
    CollectMembers_UIElement(members);

    Remove(members.methods_, "explicit UIElement::UIElement(Context* context)");
    Remove(members.methods_, "virtual void UIElement::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor)");

    Remove(members.staticMethods_, "static void UIElement::RegisterObject(Context* context)");

}

// class Button | File: ../UI/Button.h
void CollectMembers_Button(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement)");
    Remove(members.methods_, "virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)");
    Remove(members.methods_, "virtual void UIElement::Update(float timeStep)");
    Remove(members.methods_, "void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

}

// class CheckBox | File: ../UI/CheckBox.h
void CollectMembers_CheckBox(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)");
    Remove(members.methods_, "void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

}

// class Cursor | File: ../UI/Cursor.h
void CollectMembers_Cursor(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

    // VariantVector Cursor::GetShapesAttr() const
    // Error: type "VariantVector" can not automatically bind
    // void Cursor::SetShapesAttr(const VariantVector& value)
    // Error: type "const VariantVector&" can not automatically bind

}

// class LineEdit | File: ../UI/LineEdit.h
void CollectMembers_LineEdit(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "virtual bool UIElement::OnDragDropFinish(UIElement* source)");
    Remove(members.methods_, "virtual bool UIElement::OnDragDropTest(UIElement* source)");
    Remove(members.methods_, "virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDoubleClick(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers)");
    Remove(members.methods_, "virtual void UIElement::OnTextInput(const String& text)");
    Remove(members.methods_, "virtual void UIElement::Update(float timeStep)");
    Remove(members.methods_, "void UIElement::ApplyAttributes() override");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

}

// class ListView | File: ../UI/ListView.h
void CollectMembers_ListView(MemberCollection& members)
{
    CollectMembers_ScrollView(members);

    Remove(members.methods_, "bool UIElement::IsSelected() const");
    Remove(members.methods_, "void ScrollView::OnKey(Key key, MouseButtonFlags buttons, QualifierFlags qualifiers) override");
    Remove(members.methods_, "void ScrollView::OnResize(const IntVector2& newSize, const IntVector2& delta) override");

    Remove(members.staticMethods_, "static void ScrollView::RegisterObject(Context* context)");

}

// class ProgressBar | File: ../UI/ProgressBar.h
void CollectMembers_ProgressBar(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta)");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

}

// class ScrollBar | File: ../UI/ScrollBar.h
void CollectMembers_ScrollBar(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta)");
    Remove(members.methods_, "virtual void UIElement::OnSetEditable()");
    Remove(members.methods_, "void UIElement::ApplyAttributes() override");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

}

// class Slider | File: ../UI/Slider.h
void CollectMembers_Slider(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "virtual void UIElement::OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnClickEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor, UIElement* beginElement)");
    Remove(members.methods_, "virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta)");
    Remove(members.methods_, "virtual void UIElement::Update(float timeStep)");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

}

// class Text | File: ../UI/Text.h
void CollectMembers_Text(MemberCollection& members)
{
    CollectMembers_UISelectable(members);

    Remove(members.methods_, "UISelectable::URHO3D_OBJECT(UISelectable, UIElement)");
    Remove(members.methods_, "virtual void UIElement::OnIndentSet()");
    Remove(members.methods_, "virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta)");
    Remove(members.methods_, "void UIElement::ApplyAttributes() override");
    Remove(members.methods_, "void UISelectable::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override");

    Remove(members.staticMethods_, "static void UISelectable::RegisterObject(Context* context)");

}

// class Text3D | File: ../UI/Text3D.h
void CollectMembers_Text3D(MemberCollection& members)
{
    CollectMembers_Drawable(members);

    Remove(members.methods_, "virtual UpdateGeometryType Drawable::GetUpdateGeometryType()");
    Remove(members.methods_, "virtual void Drawable::UpdateBatches(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Drawable::UpdateGeometry(const FrameInfo& frame)");
    Remove(members.methods_, "virtual void Serializable::ApplyAttributes()");

    Remove(members.staticMethods_, "static void Drawable::RegisterObject(Context* context)");

}

// class Window | File: ../UI/Window.h
void CollectMembers_Window(MemberCollection& members)
{
    CollectMembers_BorderImage(members);

    Remove(members.methods_, "virtual void UIElement::OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDragCancel(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags cancelButtons, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "void BorderImage::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override");

    Remove(members.staticMethods_, "static void BorderImage::RegisterObject(Context* context)");

}

// class Menu | File: ../UI/Menu.h
void CollectMembers_Menu(MemberCollection& members)
{
    CollectMembers_Button(members);

    Remove(members.methods_, "bool UIElement::LoadXML(Deserializer& source)");
    Remove(members.methods_, "bool UIElement::LoadXML(const XMLElement& source) override");
    Remove(members.methods_, "bool UIElement::SaveXML(Serializer& dest, const String& indentation = \"\t\") const");
    Remove(members.methods_, "bool UIElement::SaveXML(XMLElement& dest) const override");
    Remove(members.methods_, "virtual bool UIElement::LoadXML(const XMLElement& source, XMLFile* styleFile)");
    Remove(members.methods_, "virtual void UIElement::OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor)");
    Remove(members.methods_, "void Button::Update(float timeStep) override");

    Remove(members.staticMethods_, "static void Button::RegisterObject(Context* context)");

}

// class View3D | File: ../UI/View3D.h
void CollectMembers_View3D(MemberCollection& members)
{
    CollectMembers_Window(members);

    Remove(members.methods_, "virtual void UIElement::OnResize(const IntVector2& newSize, const IntVector2& delta)");

    Remove(members.staticMethods_, "static void Window::RegisterObject(Context* context)");

}

// class DropDownList | File: ../UI/DropDownList.h
void CollectMembers_DropDownList(MemberCollection& members)
{
    CollectMembers_Menu(members);

    Remove(members.methods_, "virtual void Menu::OnHidePopup()");
    Remove(members.methods_, "virtual void Menu::OnShowPopup()");
    Remove(members.methods_, "virtual void UIElement::OnSetEditable()");
    Remove(members.methods_, "void Button::GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override");
    Remove(members.methods_, "void UIElement::ApplyAttributes() override");

    Remove(members.staticMethods_, "static void Menu::RegisterObject(Context* context)");

}

} // namespace Urho3D
