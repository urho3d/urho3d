// Urho3D editor user interface

const int uiSpacing = 2;
const IntRect uiSpacingRect(uiSpacing, uiSpacing, uiSpacing, uiSpacing);
UIElement@ uiMenuBar;

void createUI()
{
    XMLFile@ uiStyle = cache.getResource("XMLFile", "UI/DefaultStyle.xml");

    createCursor(uiStyle);
    createMenuBar(uiStyle);
    
    subscribeToEvent("ScreenMode", "handleScreenMode");
}

void createCursor(XMLFile@ uiStyle)
{
    Cursor@ cursor = Cursor("Cursor");
    cursor.setStyleAuto(uiStyle);
    cursor.setPosition(input.getMousePosition());
    ui.setCursor(cursor);
}

void createMenuBar(XMLFile@ uiStyle)
{
    @uiMenuBar = BorderImage("MenuBar");
    uiMenuBar.setStyle(uiStyle, "EditorMenuBar");
    uiMenuBar.setLayout(LM_HORIZONTAL, uiSpacing, uiSpacingRect);
    uiRoot.addChild(uiMenuBar);

    Menu@ fileMenu = createMenu(uiStyle, "File");
    uiMenuBar.addChild(fileMenu);
    UIElement@ spacer = UIElement("MenuBarSpacer");
    uiMenuBar.addChild(spacer);

    resizeUI();
}

Menu@ createMenu(XMLFile@ uiStyle, string title)
{
    Menu@ menu = Menu(title);
    menu.setStyleAuto(uiStyle);
    menu.setLayout(LM_HORIZONTAL, 0, IntRect(uiSpacing, 0, uiSpacing, 0));

    Text@ menuText = Text(title + "Text");
    menuText.setStyle(uiStyle, "EditorMenuText");
    menuText.setText(title);
    menu.addChild(menuText);
    menu.setFixedWidth(menu.getWidth());

    return menu;
}

void resizeUI()
{
    uiMenuBar.setFixedWidth(renderer.getWidth());
}

void handleScreenMode(StringHash eventType, VariantMap& eventData)
{
    resizeUI();
}
