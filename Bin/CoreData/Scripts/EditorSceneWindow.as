// Urho3D editor scene hierarchy window handling

const int ITEM_ENTITY = 1;
const int ITEM_COMPONENT = 2;
const uint NO_ITEM = 0xffffffff;

Window@ sceneWindow;
uint listAddIndex;

void createSceneWindow()
{
    if (sceneWindow !is null)
        return;

    @sceneWindow = ui.loadLayout(cache.getResource("XMLFile", "UI/SceneWindow.xml"), uiStyle);
    uiRoot.addChild(sceneWindow);
    sceneWindow.setPosition(50, 50);
    sceneWindow.setSize(250, 400);
    updateSceneWindow(false);

    subscribeToEvent(sceneWindow.getChild("CloseButton", true), "Released", "hideSceneWindow");
    subscribeToEvent(sceneWindow.getChild("ExpandAllButton", true), "Released", "expandSceneHierarchy");
    subscribeToEvent(sceneWindow.getChild("CollapseAllButton", true), "Released", "collapseSceneHierarchy");
    subscribeToEvent(sceneWindow.getChild("EntityList", true), "ItemSelected", "handleEntityListSelectionChange");
    subscribeToEvent(sceneWindow.getChild("EntityList", true), "ItemDeselected", "handleEntityListSelectionChange");
    subscribeToEvent(sceneWindow.getChild("EntityList", true), "ItemDoubleClicked", "handleEntityListDoubleClick");
    subscribeToEvent(sceneWindow.getChild("EntityList", true), "UnhandledKey", "handleEntityListKey");
}

void showSceneWindow()
{
    sceneWindow.setVisible(true);
    sceneWindow.bringToFront();
}

void hideSceneWindow()
{
    sceneWindow.setVisible(false);
}

void expandSceneHierarchy()
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    list.setChildItemsVisible(true);
}

void collapseSceneHierarchy()
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    list.setChildItemsVisible(false);
}

void updateSceneWindow(bool showComponents)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    list.removeAllItems();

    array<Entity@> entities = editorScene.getAllEntities();
    for (uint i = 0; i < entities.size(); ++i)
    {
        uint itemIndex = list.getNumItems();
        Entity@ entity = entities[i];

        updateSceneWindowEntity(itemIndex, entity);
        list.setChildItemsVisible(itemIndex, showComponents);
    }
}

void updateSceneWindowEntity(uint itemIndex, Entity@ entity)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);

    // Remove old item if exists
    if (itemIndex < list.getNumItems())
        list.removeItem(itemIndex);
    if (entity is null)
        return;

    Text@ text = Text();
    text.setStyle(uiStyle, "FileSelectorListText");
    text.userData["Type"] = ITEM_ENTITY;
    text.userData["EntityID"] = entity.getID();
    text.userData["Indent"] = 0;
    text.setText(getEntityTitle(entity));

    list.insertItem(itemIndex, text);

    listAddIndex = itemIndex + 1;

    array<Component@>@ components = entity.getComponents();
    for (uint j = 0; j < components.size(); ++j)
    {
        Node@ node = cast<Node@>(components[j]);
        // If is a scenenode, only add root-level node or node parented to a node in another entity
        if ((node is null) || (node.getParent() is null) || (node.getParent().getEntity() !is entity))
            addComponentToSceneWindow(entity, components, j, 1);
    }
}

void updateSceneWindowEntity(Entity@ entity)
{
    uint index = getEntityListIndex(entity);
    updateSceneWindowEntity(index, entity);
}

void addComponentToSceneWindow(Entity@ entity, array<Component@>@ components, uint componentID, int indent)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);

    Component@ component = components[componentID];
    Text@ text = Text();
    text.setStyle(uiStyle, "FileSelectorListText");
    text.userData["Type"] = ITEM_COMPONENT;
    text.userData["EntityID"] = entity.getID();
    // Note: must remember to update indices whenever components are added/removed.
    // Should have direct unique identification for components in the scene model
    text.userData["ComponentID"] = componentID;
    text.userData["Indent"] = indent;
    text.setText(getComponentTitle(component, indent));
    list.insertItem(listAddIndex, text);
    ++listAddIndex;
    
    // Check child scenenodes in the same entity and add them with increased indent
    Node@ node = cast<Node@>(component);
    if (node !is null)
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

uint getEntityListIndex(Entity@ entity)
{
    if (entity is null)
        return NO_ITEM;

    ListView@ list = sceneWindow.getChild("EntityList", true);
    uint numItems = list.getNumItems();
    uint entityID = entity.getID();

    for (uint i = 0; i < numItems; ++i)
    {
        UIElement@ item = list.getItem(i);
        if ((item.userData["Type"].getInt() == ITEM_ENTITY) && (item.userData["EntityID"].getInt() == int(entityID)))
            return i;
    }

    return NO_ITEM;
}

uint getEntityListIndex(Entity@ entity, uint startPos)
{
    if (entity is null)
        return NO_ITEM;

    ListView@ list = sceneWindow.getChild("EntityList", true);
    uint numItems = list.getNumItems();
    uint entityID = entity.getID();

    for (uint i = startPos; i < numItems; --i)
    {
        UIElement@ item = list.getItem(i);
        if ((item.userData["Type"].getInt() == ITEM_ENTITY) && (item.userData["EntityID"].getInt() == int(entityID)))
            return i;
    }
    
    return NO_ITEM;
}

Entity@ getListEntity(uint index)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    UIElement@ item = list.getItem(index);
    if (item is null)
        return null;

    return editorScene.getEntity(uint(item.userData["EntityID"].getInt()));
}

Component@ getListComponent(uint index)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    UIElement@ item = list.getItem(index);
    if (item is null)
        return null;
    if (item.userData["Type"] != ITEM_COMPONENT)
        return null;

    Entity@ entity = editorScene.getEntity(uint(item.userData["EntityID"].getInt()));
    if (entity is null)
        return null;

    array<Component@>@ components = selectedEntity.getComponents();
    uint componentID = uint(item.userData["ComponentID"].getInt());
    if (componentID < components.size())
        return components[componentID];
    else
        return null;
}

uint getComponentListIndex(Component@ component)
{
    if (component is null)
        return NO_ITEM;

    Entity@ entity = component.getEntity();
    if (entity is null)
        return NO_ITEM;

    // Find the index of component in the entity's component list
    array<Component@>@ components = entity.getComponents();
    uint componentID = 0;
    for (uint i = 0; i < components.size(); ++i)
    {
        if (components[i] is component)
        {
            componentID = i;
            break;
        }
    }

    ListView@ list = sceneWindow.getChild("EntityList", true);

    uint entityIndex = getEntityListIndex(component.getEntity());
    uint numItems = list.getNumItems();

    for (uint i = entityIndex + 1; i < numItems; ++i)
    {
        UIElement@ item = list.getItem(i);
        if (item.userData["Type"].getInt() == ITEM_ENTITY)
            break;
        if (item.userData["ComponentID"].getInt() == int(componentID))
            return i;
    }
    
    return NO_ITEM;
}


void selectComponent(Component@ component)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);

    if (component is null)
    {
        list.clearSelection();
        return;
    }
    Entity@ entity = component.getEntity();
    if (entity is null)
    {
        list.clearSelection();
        return;
    }

    uint numItems = list.getNumItems();
    uint entityItem = getEntityListIndex(entity);
    uint componentItem = getComponentListIndex(component);

    if ((entityItem < numItems) && (componentItem < numItems))
    {
        // Make sure the selected entity is expanded
        list.setChildItemsVisible(entityItem, true);
       // This causes an event to be sent, in response we set selectedComponent & selectedEntity, and refresh editors
        list.setSelection(componentItem);
    }
    else
        list.clearSelection();
}

void handleEntityListSelectionChange()
{
    ListView@ list = sceneWindow.getChild("EntityList", true);

    uint index = list.getSelection();
    @selectedEntity = getListEntity(index);
    @selectedComponent = getListComponent(index);

    updateComponentWindow();
}

void handleEntityListDoubleClick()
{
    //! \todo Doubleclick is problematic, because it also collapses/expands list items

    /*
    ListView@ list = sceneWindow.getChild("EntityList", true);
    UIElement@ item = list.getSelectedItem();
    if ((item !is null) && (item.userData["Type"] == ITEM_COMPONENT))
        showComponentWindow();
    */
}

void handleEntityListKey(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].getInt();

    ListView@ list = sceneWindow.getChild("EntityList", true);

    uint index = list.getSelection();
    Entity@ entity = getListEntity(index);
    Component@ component = getListComponent(index);
    uint entityItem = getEntityListIndex(entity, index);

    if (key == KEY_DELETE)
    {
        // Remove component
        if ((entity !is null) && (component !is null))
        {
            if (selectedComponent is component)
                @selectedComponent = null;

            entity.removeComponent(component);
            // If component is a node, also remove it from the parent node
            Node@ node = cast<Node>(component);
            if ((node !is null) && (node.getParent() !is null))
                node.getParent().removeChild(node, true);
            updateSceneWindowEntity(entityItem, entity);
            // Select the next item in the same index
            list.setSelection(index);
        }
        // Remove entity
        if ((entity !is null) && (component is null))
        {
            if (selectedEntity is entity)
                @selectedEntity = null;

            editorScene.removeEntity(entity);
            updateSceneWindowEntity(entityItem, null);
            list.setSelection(index);
        }
    }
}
