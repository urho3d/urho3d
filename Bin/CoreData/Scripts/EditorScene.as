// Urho3D editor scene handling

const int ITEM_ENTITY = 1;
const int ITEM_COMPONENT = 2;

Scene@ editorScene;
Window@ sceneWindow;
string sceneFileName;
string sceneResourcePath;
bool sceneUnsaved = false;

void createScene()
{
    // Create a scene with default values, these will be overridden when loading scenes
    @editorScene = engine.createScene("GraphicsTest", BoundingBox(-1000.0, 1000.0), 8, true);
    
    // Always pause the scene for now
    editorScene.setPaused(true);
}

void setResourcePath(string newPath)
{
    if (newPath == sceneResourcePath)
        return;

    cache.releaseAllResources(false);

    // Remove the old scene resource path if any. However make sure that CoreData path never gets removed
    if ((!sceneResourcePath.empty()) && (sceneResourcePath.find("CoreData") < 0))
        cache.removeResourcePath(sceneResourcePath);

    cache.addResourcePath(newPath);
    sceneResourcePath = newPath;
}

void loadScene(string fileName)
{
    // Always load the scene from the filesystem, not from resource paths
    if (!fileExists(fileName))
    {
        logError("No such scene " + fileName);
        return;
    }

    // Clear the old scene
    editorScene.removeAllEntities();

    // Add the new resource path
    setResourcePath(getPath(fileName));

    File file(fileName, FILE_READ);
    string extension = getExtension(fileName);
    if ((extension == ".bin") || (extension == ".sav"))
        editorScene.load(file);
    else
        editorScene.loadXML(file);
        
    sceneFileName = fileName;
    sceneUnsaved = false;
    updateWindowTitle();
    refillSceneWindow();
}

void saveScene(string fileName)
{
    if ((fileName.empty()) || (getFileName(fileName).empty()))
        return;

    File file(fileName, FILE_WRITE);
    string extension = getExtension(fileName);
    if ((extension == ".bin") || (extension == ".sav"))
        editorScene.save(file);
    else
        editorScene.saveXML(file);

    sceneFileName = fileName;
    sceneUnsaved = false;
    updateWindowTitle();
}

void createSceneWindow()
{
    if (!(sceneWindow is null))
        return;
    
    @sceneWindow = ui.loadLayout(cache.getResource("XMLFile", "UI/SceneWindow.xml"), uiStyle);
    uiRoot.addChild(sceneWindow);
    sceneWindow.setPosition(40, 40);
    sceneWindow.setSize(250, 400);
    refillSceneWindow();
}

void refillSceneWindow()
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    list.removeAllItems();

    array<Entity@> entities = editorScene.getAllEntities();
    for (uint i = 0; i < entities.size(); ++i)
    {
        uint itemIndex = list.getNumItems();

        Entity@ entity = entities[i];
        uint id = entity.getID();
        Text@ text = Text();
        text.setStyle(uiStyle, "FileSelectorListText");
        text.userData["Type"] = ITEM_ENTITY;
        text.userData["EntityID"] = id;
        text.userData["Indent"] = 0;
        text.setText(getEntityTitle(entity));
        list.addItem(text);

        array<Component@> components = entity.getComponents();
        for (uint j = 0; j < components.size(); ++j)
        {
            Component@ component = components[j];
            Text@ text = Text();
            text.setStyle(uiStyle, "FileSelectorListText");
            text.userData["Type"] = ITEM_COMPONENT;
            text.userData["EntityID"] = id;
            // Note: must remember to update indices whenever components are added/removed.
            // Should have direct unique identification for components in the scene model
            text.userData["ComponentID"] = j;
            text.userData["Indent"] = 1;
            text.setText(" " + getComponentTitle(component));
            list.addItem(text);

            //! \todo recurse child scene nodes here if the component is a scene node
        }

        // Collapse components by default
        list.setChildItemsVisible(itemIndex, false);
    }
}

string getEntityTitle(Entity@ entity)
{
    string name = entity.getName();
    if (name.empty())
        return "Entity (" + entity.getID() + ")";
    else
        return name + " (" + entity.getID() + ")";
}

string getComponentTitle(Component@ component)
{
    string name = component.getName();
    if (name.empty())
        return component.getTypeName();
    else
        return component.getTypeName() + " (" + name + ")";
}