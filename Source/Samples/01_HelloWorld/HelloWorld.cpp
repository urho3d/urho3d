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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/IO/VectorBuffer.h> // TO BE REMOVED

// TO BE REMOVED
// @{
#include <Urho3D/Core/Context.h>

static const char* enumNames[] =
{
    "Enum1",
    "Enum2",
    "Enum3"
};

enum class TestEnum
{
    Enum1,
    Enum2,
    Enum3,
};

class TestSerializable : public Urho3D::Serializable
{
    URHO3D_OBJECT(TestSerializable, Urho3D::Serializable);

public:
    TestSerializable(Urho3D::Context* context) : Urho3D::Serializable(context) { }

    static void RegisterObject(Urho3D::Context* context)
    {
        context->RegisterFactory<TestSerializable>();
        URHO3D_ATTRIBUTE("attribute", Urho3D::String, attribute_, "attribute", Urho3D::AM_DEFAULT);
        URHO3D_ATTRIBUTE_EX("attributeEx", Urho3D::String, attributeEx_, OnAttributeExSet, "attributeEx", Urho3D::AM_DEFAULT);
        URHO3D_ENUM_ATTRIBUTE("enumAttribute", enumAttribute_, enumNames, TestEnum::Enum2, Urho3D::AM_DEFAULT);
        URHO3D_ENUM_ATTRIBUTE_EX("enumAttributeEx", enumAttributeEx_, OnEnumAttributeExSet, enumNames, TestEnum::Enum2, Urho3D::AM_DEFAULT);
        URHO3D_ACCESSOR_ATTRIBUTE("accessorAttribute", GetAccessorAttribute, SetAccessorAttribute, Urho3D::String, "accessorAttribute", Urho3D::AM_DEFAULT);
        URHO3D_ENUM_ACCESSOR_ATTRIBUTE("enumAccessorAttribute", GetEnumAccessorAttribute, SetEnumAccessorAttribute, TestEnum, enumNames, TestEnum::Enum3, Urho3D::AM_DEFAULT);
        URHO3D_MIXED_ACCESSOR_ATTRIBUTE("mixedAccessorAttribute", GetMixedAccessorAttribute, SetMixedAccessorAttribute, Urho3D::String, "mixedAccessorAttribute", Urho3D::AM_DEFAULT);

        {
            Urho3D::String suffix = "_temp";
            auto getter = [=](const TestSerializable& self, Urho3D::Variant& value)
            {
                value = self.customAttribute_ + suffix;
            };
            auto setter = [=](TestSerializable& self, const Urho3D::Variant& value)
            {
                self.customAttribute_ = value.GetString() + suffix;
            };
            URHO3D_CUSTOM_ATTRIBUTE("customAttribute", getter, setter, Urho3D::String, "customAttribute", Urho3D::AM_DEFAULT);
        }

        {
            auto getter = [=](const TestSerializable& self, Urho3D::Variant& value)
            {
                value = static_cast<int>(self.customEnumAttribute_);
            };
            auto setter = [=](TestSerializable& self, const Urho3D::Variant& value)
            {
                self.customEnumAttribute_ = static_cast<TestEnum>(value.GetInt());
            };
            URHO3D_CUSTOM_ENUM_ATTRIBUTE("customAttribute", getter, setter, enumNames, TestEnum::Enum1, Urho3D::AM_DEFAULT);
        }
    }

    Urho3D::String attribute_;
    Urho3D::String attributeEx_;
    void OnAttributeExSet()
    {
        attributeEx_ = attributeEx_.ToUpper();
    }
    TestEnum enumAttribute_ = TestEnum::Enum1;
    TestEnum enumAttributeEx_ = TestEnum::Enum1;
    void OnEnumAttributeExSet()
    {
        enumAttributeEx_ = static_cast<TestEnum>(static_cast<int>(enumAttributeEx_) + 1);
    }

    Urho3D::String accessorAttribute_;
    const Urho3D::String& GetAccessorAttribute() const { return accessorAttribute_; }
    void SetAccessorAttribute(const Urho3D::String& value) { accessorAttribute_ = value; }

    TestEnum enumAccessorAttribute_ = TestEnum::Enum1;
    TestEnum GetEnumAccessorAttribute() const { return enumAccessorAttribute_; }
    void SetEnumAccessorAttribute(TestEnum value) { enumAccessorAttribute_ = value; }

    Urho3D::String mixedAccessorAttribute_;
    Urho3D::String GetMixedAccessorAttribute() const { return mixedAccessorAttribute_; }
    void SetMixedAccessorAttribute(const Urho3D::String& value) { mixedAccessorAttribute_ = value; }

    Urho3D::String customAttribute_;
    TestEnum customEnumAttribute_ = TestEnum::Enum1;
};
// @}

#include "HelloWorld.h"

#include <Urho3D/DebugNew.h>

// Expands to this example's entry-point
URHO3D_DEFINE_APPLICATION_MAIN(HelloWorld)

HelloWorld::HelloWorld(Context* context) :
    Sample(context)
{
    // TO BE REMOVED
    // @{
    TestSerializable::RegisterObject(context);
    auto obj = MakeShared<TestSerializable>(context_);
    obj->ResetToDefault();

    VectorBuffer buf;
    XMLFile xml(context_);
    XMLElement root = xml.CreateRoot("test");
    obj->SaveXML(root);
    xml.Save(buf);
    String text;
    text.Append(reinterpret_cast<const char*>(buf.GetData()), buf.GetSize());
    obj.Reset();
    // @}
}

void HelloWorld::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create "Hello World" Text
    CreateText();

    // Finally subscribe to the update event. Note that by subscribing events at this point we have already missed some events
    // like the ScreenMode event sent by the Graphics subsystem when opening the application window. To catch those as well we
    // could subscribe in the constructor instead.
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void HelloWorld::CreateText()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    // Construct new Text object
    SharedPtr<Text> helloText(new Text(context_));

    // Set String to display
    helloText->SetText("Hello World from Urho3D!");

    // Set font and text color
    helloText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 30);
    helloText->SetColor(Color(0.0f, 1.0f, 0.0f));

    // Align Text center-screen
    helloText->SetHorizontalAlignment(HA_CENTER);
    helloText->SetVerticalAlignment(VA_CENTER);

    // Add Text instance to the UI root element
    GetSubsystem<UI>()->GetRoot()->AddChild(helloText);
}

void HelloWorld::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(HelloWorld, HandleUpdate));
}

void HelloWorld::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Do nothing for now, could be extended to eg. animate the display
}
