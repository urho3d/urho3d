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
    updateSceneWindow();
    resetCamera();
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
    updateSceneWindow();
}

void updateSceneWindow()
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    list.removeAllItems();

    array<Entity@> entities = editorScene.getAllEntities();
    for (uint i = 0; i < entities.size(); ++i)
    {
        uint itemIndex = list.getNumItems();

        Entity@ entity = entities[i];
        Text@ text = Text();
        text.setStyle(uiStyle, "FileSelectorListText");
        text.userData["Type"] = ITEM_ENTITY;
        text.userData["EntityID"] = entity.getID();
        text.userData["Indent"] = 0;
        text.setText(getEntityTitle(entity));
        list.addItem(text);

        array<Component@> components = entity.getComponents();
        for (uint j = 0; j < components.size(); ++j)
        {
            Node@ node = cast<Node@>(components[j]);
            // If is a scenenode, only add root-level node or node parented to a node in another entity
            if ((node is null) || (node.getParent() is null) || (!(node.getParent().getEntity() is entity)))
                addComponentToSceneWindow(entity, components, j, 1);
        }
        // Collapse components by default
        list.setChildItemsVisible(itemIndex, false);
    }
}

void addComponentToSceneWindow(Entity@ entity, array<Component@> components, uint index, int indent)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);

    Component@ component = components[index];
    Text@ text = Text();
    text.setStyle(uiStyle, "FileSelectorListText");
    text.userData["Type"] = ITEM_COMPONENT;
    text.userData["EntityID"] = entity.getID();
    // Note: must remember to update indices whenever components are added/removed.
    // Should have direct unique identification for components in the scene model
    text.userData["ComponentID"] = index;
    text.userData["Indent"] = indent;
    text.setText(getComponentTitle(component, indent));
    list.addItem(text);
    
    // Check child scenenodes in the same entity and add them with increased indent
    Node@ node = cast<Node@>(component);
    if (!(node is null))
    {
        array<Node@> childNodes = node.getChildren(NODE_ANY, false);
        for (uint i = 0; i < childNodes.size(); ++i)
        {
            Node@ childNode = childNodes[i];
            if (childNode.getEntity() is entity)
            {
                // Must find the corresponding component index
                for (uint j = 0; j < components.size(); ++j)
                {
                    if (components[j] is childNode)
                    {
                        addComponentToSceneWindow(entity, components, j, indent + 1);
                        break;
                    }
                }
            }
        }
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

string getComponentTitle(Component@ component, int indent)
{
    string indentStr;
    indentStr.resize(indent);
    for (int i = 0; i < indent; ++i)
        indentStr[i] = ' ';

    string name = component.getName();
    if (name.empty())
        return indentStr + component.getTypeName();
    else
        return indentStr + component.getTypeName() + " (" + name + ")";
}