// This example for work with Android
// Furthermore it shows:
//     - Using the Sample utility functions as a base for the application
//     - Subscribing to and handling of update events

#include "Scripts/Utilities/Sample.as"
Text@ textSysInfo;
Text@ textBattery;

void Start()
{
    // Execute the common startup for samples
    SampleStart();
    XMLFile@ style = cache.GetResource("XMLFile", "UI/DefaultStyle.xml");

    // Set the loaded style as default style
    ui.root.defaultStyle = style;

    // Create "Hello World" Text
    CreateText();

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);

    // Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents();

    if (GetPlatform() == "Android") {
        postCommandToAndroid("startReceiveBatteryStatus");
        postCommandToAndroid("getSystemInfo");
    }
}

void CreateText()
{
    // Construct new Text object
    Text@ helloText = createText(HA_CENTER, VA_CENTER, IntVector2::ZERO, Color(0.0f, 1.0f, 0.0f));
    // Set String to display
    if (GetPlatform() == "Android")
    {
        helloText.text = "Welcome to Android!!!";
        @textBattery = createText(HA_RIGHT, VA_TOP, IntVector2(-110, 10), WHITE);
        @textSysInfo = createText(HA_LEFT, VA_TOP, IntVector2(10, 10), WHITE);
        textBattery.text = "- Battery Info -";
        textSysInfo.text = "- SystemInfo -";
       
        Button@ btn = createButton(80, -80, 200, 60, HA_LEFT, VA_BOTTOM, "Show toast");
        SubscribeToEvent(btn, "Pressed", "onShowToast");

        @btn = createButton(290, -80, 200, 60, HA_LEFT, VA_BOTTOM, "Open site");
        SubscribeToEvent(btn, "Pressed", "onOpenUrl");

        @btn = createButton(500, -80, 200, 60, HA_LEFT, VA_BOTTOM, "Open playmarket");
        SubscribeToEvent(btn, "Pressed", "onOpenPlaymarket");

        @btn = createButton(710, -80, 200, 60, HA_LEFT, VA_BOTTOM, "Share text");
        SubscribeToEvent(btn, "Pressed", "onShareText");
    }
    else
        helloText.text = "No Android platform";
}

void SubscribeToEvents()
{
    // Set Android notification handlers
    androidHandlers["SysInfo"] = @onAndroidSysInfo;
    androidHandlers["Battery"] = @onAndroidBattery;
    // Subscribe to Android notifications
    SubscribeToEvent("AndroidNotify", "onAndroidNotify");
}

Text@ createText(HorizontalAlignment ha, VerticalAlignment va, const IntVector2& pos, const Color& clr)
{
    Text txt;
    // Set font and text color
    txt.SetFont(cache.GetResource("Font", "Fonts/Anonymous Pro.ttf"), 30);
    txt.color = clr;
    txt.SetAlignment(ha, va);
    txt.position = pos;

    // Add Text instance to the UI root element
    ui.root.AddChild(txt);
    return txt;
}

Button@ createButton(int x, int y, int xSize, int ySize, HorizontalAlignment ha, VerticalAlignment va, const String& text)
{
    Font@ font = cache.GetResource("Font", "Fonts/Anonymous Pro.ttf");

    // Create the button and center the text onto it
    Button button;
    button.SetStyleAuto(ui.root.defaultStyle);
    button.SetPosition(x, y);
    button.SetSize(xSize, ySize);
    button.SetAlignment(ha, va);
    button.focusMode = FM_NOTFOCUSABLE;

    Text@ buttonText = button.CreateChild("Text");
    buttonText.SetAlignment(HA_CENTER, VA_CENTER);
    buttonText.SetFont(font, ySize * 0.3);
    buttonText.text = text;
    ui.root.AddChild(button);
    return button;
}

funcdef void AndroidHandler(const String&, JSONValue&);
Dictionary androidHandlers;

void onAndroidNotify(StringHash, VariantMap& d)
{
    JSONFile json;
    if (!json.FromString(d["Data"].GetString()))
        return;
    String source = json.root["source"].GetString();
    String event = json.root["event"].GetString();
    AndroidHandler@ handler;
    if (androidHandlers.Get(source, @handler))
        handler(event, json.root);
}

// For activity can handle message, we must sen it as JSON string, where attribute "method"
// point to called method. And it JSON data sended in this method as parameter.
// More about exists methods and their params see at 
// android\launcher-app\src\main\java\com\github\urho3d\launcher\MainActivity.kt
// Also you can add more methods in activity to hold you are need
void postCommandToAndroid(const String& method, JSONFile@ f = JSONFile())
{
    f.root["method"] = method;
    PostCommandToAndroid(f);
}

void onShowToast()
{
    postCommandToAndroid("showToast", JsonBuilder()("text", "Hello from Urho3D!!!")("lengthLong", true).f);
}

void onOpenUrl()
{
    postCommandToAndroid("openUrl", JsonBuilder()("url", "https://urho3d.github.io/").f);
}

void onOpenPlaymarket()
{
    postCommandToAndroid("openUrl", JsonBuilder()("url", "market://details?id=com.horovo.games.bb.r").f);
}

void onShareText()
{
    postCommandToAndroid("shareText",
        JsonBuilder()
        ("text", "Hello from Urho3D!!!")
        ("subject", "Urho3D")
        ("title", "Share info").f);
}

String jsonToText(JSONValue& data)
{
    String txt;
    Array<String>@ keys = data.keys;
    for (uint i = 0; i < keys.length; i++)
    {
        JSONValue val = data[keys[i]];
        txt = txt + keys[i] + ": ";
        if (val.valueType == JSON_STRING)
            txt += val.GetString();
        else if (val.valueType == JSON_NUMBER)
            txt += val.GetInt();
        else if (val.valueType == JSON_BOOL)
            txt += val.GetBool();
        txt += "\n";
    }
    return txt;
}

void onAndroidSysInfo(const String&, JSONValue& data)
{
    textSysInfo.text = jsonToText(data);
}

void onAndroidBattery(const String&, JSONValue& data)
{
    textBattery.text = jsonToText(data);
}

class JsonBuilder
{
    JSONFile f;
    JsonBuilder@ opCall(const String& key, int v)
    {
        f.root[key] = v;
        return this;
    }
    JsonBuilder@ opCall(const String& key, const String& v)
    {
        f.root[key] = v;
        return this;
    }
    JsonBuilder@ opCall(const String& key, bool v)
    {
        f.root[key] = v;
        return this;
    }
    JsonBuilder@ opCall(const String& key, Array<String>@ v)
    {
        JSONValue var;
        if (v.length == 0) {
            var.Push(JSONValue());
            var.Pop();
        } else {
            for (uint k = 0; k < v.length; k++)
                var.Push(JSONValue(v[k]));
        }
        f.root[key] = var;
        return this;
    }
};


// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
