// HSV Color Wheel

Window@ colorWheelWindow;
UIElement@ colorCursor = null;
UIElement@ colorWheel = null;

UIElement@ closeButton = null;
UIElement@ okButton = null;
UIElement@ cancelButton = null;

UIElement@ bwGradient = null;
UIElement@ bwCursor = null;

UIElement@ AGradient = null;
UIElement@ ACursor = null;

LineEdit@ rLineEdit = null;
LineEdit@ gLineEdit = null;
LineEdit@ bLineEdit = null;

LineEdit@ hLineEdit = null;
LineEdit@ sLineEdit = null;
LineEdit@ vLineEdit = null;

LineEdit@ aLineEdit = null;

BorderImage@ colorCheck = null;
Array<BorderImage@> colorFastItem;
Array<Color> colorFast;
int colorFastSelectedIndex = -1;
int colorFastHoverIndex = -1;

IntVector2 lastColorWheelWindowPosition;


bool isColorWheelHovering = false;
bool isBWGradientHovering = false;
bool isAGradientHovering = false;

Color wheelIncomingColor = Color(1,1,1,1);
Color wheelColor = Color(1,1,1,1);
float colorHValue = 1;
float colorSValue = 1;
float colorVValue = 1;
float colorAValue = 0.5;
int high = 0;
float aValue = 1;

const int IMAGE_SIZE = 256;
const int HALF_IMAGE_SIZE = 128;
const float MAX_ANGLE = 360;
const float ROUND_VALUE_MAX = 0.99f;
const float ROUND_VALUE_MIN = 0.01f;

// for handlers outside
String eventTypeWheelChangeColor = "WheelChangeColor";
String eventTypeWheelSelectColor = "WheelSelectColor";
String eventTypeWheelDiscardColor ="WheelDiscardColor";

void CreateColorWheel()
{
    if (colorWheelWindow !is null)
        return;

    colorWheelWindow = LoadEditorUI("UI/EditorColorWheel.xml");
    ui.root.AddChild(colorWheelWindow);
    colorWheelWindow.opacity = uiMaxOpacity;

    colorWheel = colorWheelWindow.GetChild("ColorWheel", true);
    colorCursor = colorWheelWindow.GetChild("ColorCursor", true);

    closeButton = colorWheelWindow.GetChild("CloseButton", true);
    okButton = colorWheelWindow.GetChild("okButton", true);
    cancelButton = colorWheelWindow.GetChild("cancelButton", true);

    colorCheck = colorWheelWindow.GetChild("ColorCheck", true);
    bwGradient = colorWheelWindow.GetChild("BWGradient", true);
    bwCursor = colorWheelWindow.GetChild("BWCursor", true);

    AGradient = colorWheelWindow.GetChild("AGradient", true);
    ACursor = colorWheelWindow.GetChild("ACursor", true);

    rLineEdit = colorWheelWindow.GetChild("R", true);
    gLineEdit = colorWheelWindow.GetChild("G", true);
    bLineEdit = colorWheelWindow.GetChild("B", true);

    hLineEdit = colorWheelWindow.GetChild("H", true);
    sLineEdit = colorWheelWindow.GetChild("S", true);
    vLineEdit = colorWheelWindow.GetChild("V", true);

    aLineEdit = colorWheelWindow.GetChild("A", true);

    colorFastItem.Resize(8);
    colorFast.Resize(8);

    // Init some gradient for fast colors palette
    for (int i=0; i<8; i++) 
    {
        colorFastItem[i] = colorWheelWindow.GetChild("h"+String(i), true);
        colorFast[i] = Color(i*0.125,i*0.125,i*0.125);
        colorFastItem[i].color = colorFast[i]; 
    }

    SubscribeToEvent(closeButton, "Pressed", "HandleWheelButtons");
    SubscribeToEvent(okButton, "Pressed", "HandleWheelButtons");
    SubscribeToEvent(cancelButton, "Pressed", "HandleWheelButtons");

    lastColorWheelWindowPosition = IntVector2(300,400);

    HideColorWheel();
}

bool ShowColorWheelWithColor(Color oldColor) 
{
    wheelIncomingColor = oldColor;
    wheelColor = oldColor;
    return ShowColorWheel();
}

bool ShowColorWheel()
{
    if (ui.focusElement !is null && colorWheelWindow.visible) 
        return false;

    colorFastSelectedIndex = -1;
    colorFastHoverIndex = -1;

    EstablishColorWheelUIFromColor(wheelColor); 

    colorWheelWindow.opacity = 1;
    colorWheelWindow.position = lastColorWheelWindowPosition;
    colorWheelWindow.visible = true;
    colorWheelWindow.BringToFront();

    return true;
}

void HideColorWheel()
{
    if (colorWheelWindow.visible) 
    {
        colorWheelWindow.visible = false;
        lastColorWheelWindowPosition = colorWheelWindow.position;
    }
}

void HandleWheelButtons(StringHash eventType, VariantMap& eventData) 
{
    UIElement@ edit = eventData["Element"].GetPtr();

    if (edit is null) return;

    if (edit is cancelButton) 
    {
        VariantMap vm;
        eventData["Color"] = wheelIncomingColor;
        SendEvent(eventTypeWheelDiscardColor, vm);
        HideColorWheel();
    }

    if (edit is closeButton)
    {
        VariantMap vm;
        eventData["Color"] = wheelIncomingColor;
        SendEvent(eventTypeWheelDiscardColor, vm);
        HideColorWheel();
    }

    if (edit is okButton) 
    {
        VariantMap vm;
        eventData["Color"] = wheelColor;
        SendEvent(eventTypeWheelSelectColor, vm);
        HideColorWheel();
    }
}

void HandleColorWheelKeyDown(StringHash eventType, VariantMap& eventData) 
{
    if (colorWheelWindow.visible == false) return;

    int key = eventData["Key"].GetInt();

    if (key == KEY_ESC)
    {
        SendEvent(eventTypeWheelDiscardColor, eventData);
        HideColorWheel();
    }
}

void HandleColorWheelMouseButtonDown(StringHash eventType, VariantMap& eventData) 
{
    if (colorWheelWindow.visible == false) return;

    int x = eventData["X"].GetInt();
    int y = eventData["Y"].GetInt();
    int button = eventData["Button"].GetInt();

    if (button == 1) 
    {
        // check for select
        if (colorFastHoverIndex != -1)
        {
            colorFastSelectedIndex = colorFastHoverIndex;
            EstablishColorWheelUIFromColor(colorFast[colorFastSelectedIndex]);
            SendEventChangeColor();    
        }
    }
}

// handler only for BWGradient
void HandleColorWheelMouseWheel(StringHash eventType, VariantMap& eventData) 
{
    if (colorWheelWindow.visible == false || !isBWGradientHovering ) return;

    int multipler = 16;
    int wheelValue = eventData["Wheel"].GetInt();

    wheelValue = wheelValue * multipler;

    if (wheelValue != 0) 
    {
        if (wheelValue > 0) 
        {
            high = high + wheelValue;
            high = Min(high, IMAGE_SIZE); // limit BWGradietn by high 
        }
        else if (wheelValue < 0)
        {
            high = high + wheelValue;
            high = Max(high, 0);
        }

        bwCursor.SetPosition(bwCursor.position.x, high - 7);
        colorVValue = float(IMAGE_SIZE - high) / IMAGE_SIZE;

        wheelColor.FromHSV(colorHValue, colorSValue, colorVValue, colorAValue);
        SendEventChangeColor();
        UpdateColorInformation(); 
    }
}

void HandleColorWheelMouseMove(StringHash eventType, VariantMap& eventData)
{
    if (colorWheelWindow.visible == false) return;

    int x = eventData["X"].GetInt();
    int y = eventData["Y"].GetInt();
    int button = eventData["Button"].GetInt();

    if (colorWheelWindow.IsInside(IntVector2(x,y), true))
        colorWheelWindow.opacity = 1.0f;

    int cwx = 0;
    int cwy = 0;
    int cx = 0;
    int cy = 0;
    IntVector2 i;
    bool inWheel = false;

    isBWGradientHovering = false;
    isColorWheelHovering = false;

    // if mouse cursor move on wheel rectangle    
    if (colorWheel.IsInside(IntVector2(x,y), true)) 
    {
        isColorWheelHovering = true;
        // get element pos win screen
        IntVector2 ep = colorWheel.screenPosition;

        // math diff between mouse cursor & element pos = mouse pos on element
        cwx = x - ep.x;
        cwy = y - ep.y;

        // shift mouse pos to center of wheel 
        cx = cwx - HALF_IMAGE_SIZE;
        cy = cwy - HALF_IMAGE_SIZE;

        // get direction vector of H on circle
        Vector2 d = Vector2(cx, cy);

        // if out  of circle place colorCurcor back to circle
        if (d.length > HALF_IMAGE_SIZE) 
        {
            d.Normalize();
            d = d * HALF_IMAGE_SIZE;

            i = IntVector2(int(d.x), int(d.y));
            inWheel = false;

        }
        else 
        {
            inWheel = true;
        }

        if (isColorWheelHovering && inWheel && input.mouseButtonDown[MOUSEB_LEFT] || input.mouseButtonDown[MOUSEB_RIGHT])
        {
            Vector2 pointOnCircle = Vector2(cx,-cy);
            float angle = GetAngle(pointOnCircle);

            i = i + IntVector2(cwx,cwy);
            colorCursor.position = IntVector2(i.x-7, i.y-7);

            colorHValue = GetHueFromWheelDegAngle(angle);

            if (colorHValue < ROUND_VALUE_MIN) colorHValue = 0.0;
            if (colorHValue > ROUND_VALUE_MAX) colorHValue = 1.0;

            colorSValue = d.length / HALF_IMAGE_SIZE;

            if (colorSValue < ROUND_VALUE_MIN) colorSValue = 0.0;
            if (colorSValue > ROUND_VALUE_MAX) colorSValue = 1.0;

            wheelColor.FromHSV(colorHValue, colorSValue, colorVValue, colorAValue);
            SendEventChangeColor();
            UpdateColorInformation();
        }
    }
    // if mouse cursor move on bwGradient rectangle
    else if (bwGradient.IsInside(IntVector2(x,y), true)) 
    {
        isBWGradientHovering = true;
        IntVector2 ep = bwGradient.screenPosition; 
        int high = y - ep.y;

        if (input.mouseButtonDown[MOUSEB_LEFT] || input.mouseButtonDown[MOUSEB_RIGHT])
        {
            bwCursor.SetPosition(bwCursor.position.x, high - 7);
            colorVValue = float(IMAGE_SIZE - high) / IMAGE_SIZE;

            if (colorVValue < 0.01) colorVValue = 0.0;
            if (colorVValue > 0.99) colorVValue = 1.0;

            wheelColor.FromHSV(colorHValue, colorSValue, colorVValue, colorAValue);
            SendEventChangeColor();
        }

        UpdateColorInformation();
    }
    // if mouse cursor move on AlphaGradient rectangle 
    else if (AGradient.IsInside(IntVector2(x,y), true))
    {
        IntVector2 ep = AGradient.screenPosition; 
        int aValue = x - ep.x;

        if (input.mouseButtonDown[MOUSEB_LEFT] || input.mouseButtonDown[MOUSEB_RIGHT])
        {
            ACursor.SetPosition(aValue - 7, ACursor.position.y);
            colorAValue = float((aValue) / 200); // 200pix image

            // round values for min or max
            if (colorAValue < 0.01) colorAValue = 0.0;
            if (colorAValue > 0.99) colorAValue = 1.0;

            wheelColor.FromHSV(colorHValue, colorSValue, colorVValue, colorAValue);
            SendEventChangeColor();
        }

        UpdateColorInformation();
    }

    // cheking for history select
    for (int j=0; j<8; j++)
    {
        if (colorFastItem[j].IsInside(IntVector2(x,y), true))
            colorFastHoverIndex = j;
    }
}

void UpdateColorInformation() 
{
    // fill UI from current color
    hLineEdit.text = String(colorHValue).Substring(0,5);
    sLineEdit.text = String(colorSValue).Substring(0,5);
    vLineEdit.text = String(colorVValue).Substring(0,5);

    rLineEdit.text = String(wheelColor.r).Substring(0,5);
    gLineEdit.text = String(wheelColor.g).Substring(0,5);
    bLineEdit.text = String(wheelColor.b).Substring(0,5);

    aLineEdit.text = String(colorAValue).Substring(0,5); 

    colorCheck.color = wheelColor;
    colorWheel.color = Color(colorVValue,colorVValue,colorVValue);
    AGradient.color = Color(wheelColor.r, wheelColor.g, wheelColor.b);

    // update selected fast-colors
    if (colorFastSelectedIndex != -1) 
    {
        colorFastItem[colorFastSelectedIndex].color = wheelColor;
        colorFast[colorFastSelectedIndex] = wheelColor; 
    }
}

void SendEventChangeColor()
{
    VariantMap eventData;
    eventData["Color"] = wheelColor;
    SendEvent("WheelChangeColor", eventData);
}

void EstablishColorWheelUIFromColor(Color c) 
{
    wheelColor = c;
    colorHValue = c.Hue();
    colorSValue = c.SaturationHSV();
    colorVValue = c.Value();
    colorAValue = c.a;

    // convert color value to BWGradient high
    high = int(IMAGE_SIZE - colorVValue * IMAGE_SIZE);
    bwCursor.SetPosition(bwCursor.position.x, high - 7);

    // convert color alpha to shift on x-axis for ACursor
    aValue = 200 * colorAValue;
    ACursor.SetPosition(int(aValue - 7), ACursor.position.y);

    // rotate vector to H-angle with scale(shifting) by S to calculate final point position
    Quaternion q(colorHValue * -MAX_ANGLE);
    Vector3 pos = Vector3(1, 0, 0);
    pos = q * pos;
    pos = pos * (colorSValue * HALF_IMAGE_SIZE);
    pos = pos + Vector3(HALF_IMAGE_SIZE, HALF_IMAGE_SIZE);

    colorCursor.position = IntVector2(int(pos.x) - 7, int(pos.y) - 7);

    // Update information on UI about color
    UpdateColorInformation();
}

float GetHueFromWheelDegAngle(float angle)
{
    return angle / MAX_ANGLE;
}

float GetAngle(Vector2 point)
{
    float angle = Atan2( point.y, point.x );

    if (angle < 0) 
        angle += MAX_ANGLE;

    return angle;
}