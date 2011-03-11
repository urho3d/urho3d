// Urho3D editor scene hierarchy window handling

const int ITEM_NONE = 0;
const int ITEM_ENTITY = 1;
const int ITEM_COMPONENT = 2;
const uint NO_ITEM = 0xffffffff;

Window@ sceneWindow;
uint listAddIndex;
uint copyBufferEntityID = 0;
XMLFile copyBuffer;

array<string> newEntityChoices = {"Replicated", "Local"};

void createSceneWindow()
{
    if (sceneWindow !is null)
        return;

    @sceneWindow = ui.loadLayout(cache.getResource("XMLFile", "UI/SceneWindow.xml"), uiStyle);
    uiRoot.addChild(sceneWindow);
    int height = min(uiRoot.getHeight() - 60, 500);
    sceneWindow.setSize(300, height);
    sceneWindow.setPosition(20, 40);
    updateSceneWindow(false);

    DropDownList@ newEntityList = sceneWindow.getChild("NewEntityList", true);
    for (uint i = 0; i < newEntityChoices.size(); ++i)
    {
        Text@ choice = Text();
        choice.setStyle(uiStyle, "FileSelectorFilterText");
        choice.setText(newEntityChoices[i]);
        newEntityList.addItem(choice);
    }

    DropDownList@ newComponentList = sceneWindow.getChild("NewComponentList", true);
    array<string> componentTypes = editorScene.getComponentTypes();
    for (uint i = 0; i < componentTypes.size(); ++i)
    {
        Text@ choice = Text();
        choice.setStyle(uiStyle, "FileSelectorFilterText");
        choice.setText(componentTypes[i]);
        newComponentList.addItem(choice);
    }

    subscribeToEvent(sceneWindow.getChild("CloseButton", true), "Released", "hideSceneWindow");
    subscribeToEvent(sceneWindow.getChild("ExpandAllButton", true), "Released", "expandSceneHierarchy");
    subscribeToEvent(sceneWindow.getChild("CollapseAllButton", true), "Released", "collapseSceneHierarchy");
    subscribeToEvent(sceneWindow.getChild("EntityList", true), "ItemSelected", "handleEntityListSelectionChange");
    subscribeToEvent(sceneWindow.getChild("EntityList", true), "ItemDeselected", "handleEntityListSelectionChange");
    subscribeToEvent(sceneWindow.getChild("EntityList", true), "UnhandledKey", "handleEntityListKey");
    subscribeToEvent(newEntityList, "ItemSelected", "handleCreateEntity");
    subscribeToEvent(newComponentList, "ItemSelected", "handleCreateComponent");
    subscribeToEvent("DragDropTest", "handleDragDropTest");
    subscribeToEvent("DragDropFinish", "handleDragDropFinish");
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
    list.getContentElement().disableLayoutUpdate();
    list.removeAllItems();

    array<Entity@> entities = editorScene.getAllEntities();
    for (uint i = 0; i < entities.size(); ++i)
    {
        uint itemIndex = list.getNumItems();
        Entity@ entity = entities[i];

        updateSceneWindowEntity(itemIndex, entity);
        list.setChildItemsVisible(itemIndex, showComponents);
    }
    
    list.getContentElement().enableLayoutUpdate();
    list.getContentElement().updateLayout();
    
    // Clear copybuffer when whole window refreshed
    copyBuffer.createRootElement("none");
}

void updateSceneWindowEntity(uint itemIndex, Entity@ entity)
{
    ListView@ list = sceneWindow.getChild("EntityList", true);

    // Remove old item if exists
    uint numItems = list.getNumItems();
    if (itemIndex < numItems)
        list.removeItem(itemIndex);
        
    if (entity is null)
        return;

    if (itemIndex >= numItems)
    {
        // Scan for correct place to insert at
        uint entityID = entity.getID();
        for (itemIndex = 0; itemIndex < numItems; ++itemIndex)
        {
            UIElement@ item = list.getItem(itemIndex);
            if (uint(item.userData["EntityID"].getInt()) > entityID)
                break;
        }
    }

    Text@ text = Text();
    text.setStyle(uiStyle, "FileSelectorListText");
    text.userData["Type"] = ITEM_ENTITY;
    text.userData["EntityID"] = entity.getID();
    text.userData["Indent"] = 0;
    text.setText(getEntityTitle(entity));
    text.setDragDropMode(DD_TARGET);

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
    text.setDragDropMode(DD_SOURCE_AND_TARGET);
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
    return getListComponent(item);
}

Component@ getListComponent(UIElement@ item)
{
    if (item is null)
        return null;
    if (item.userData["Type"].getInt() != ITEM_COMPONENT)
        return null;

    Entity@ entity = editorScene.getEntity(uint(item.userData["EntityID"].getInt()));
    if (entity is null)
        return null;

    array<Component@>@ components = entity.getComponents();
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

void handleEntityListKey(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].getInt();
    
    ListView@ list = sceneWindow.getChild("EntityList", true);
    
    uint index = list.getSelection();
    Entity@ entity = getListEntity(index);
    Component@ component = getListComponent(index);
    uint entityItem = getEntityListIndex(entity, index);
}

void handleDragDropTest(StringHash eventType, VariantMap& eventData)
{
    UIElement@ source = eventData["Source"].getUIElement();
    UIElement@ target = eventData["Target"].getUIElement();
    eventData["Accept"] = testSceneWindowElements(source, target);
}

void handleDragDropFinish(StringHash eventType, VariantMap& eventData)
{
    UIElement@ source = eventData["Source"].getUIElement();
    UIElement@ target = eventData["Target"].getUIElement();
    bool accept =  testSceneWindowElements(source, target);
    eventData["Accept"] = accept;
    if (!accept)
        return;

    // Now perform the action
    Entity@ sourceEntity = editorScene.getEntity(uint(source.userData["EntityID"].getInt()));
    Entity@ targetEntity = editorScene.getEntity(uint(target.userData["EntityID"].getInt()));
    Component@ sourceComponent = getListComponent(source);

    // Move component into another entity, and/or make unparented
    if (target.userData["Type"].getInt() == ITEM_ENTITY)
    {
        // Within same entity
        if (sourceEntity is targetEntity)
        {
            beginModify(sourceEntity.getID());

            Node@ sourceNode = cast<Node>(sourceComponent);
            if ((sourceNode !is null) && (sourceNode.getParent() !is null))
                sourceNode.getParent().removeChild(sourceNode, true);

            updateSceneWindowEntity(sourceEntity);
            endModify(sourceEntity.getID());
        }
        // Move to different entity
        else
        {
            beginModify(sourceEntity.getID());
            beginModify(targetEntity.getID());

            sourceEntity.removeComponent(sourceComponent);
            targetEntity.addComponent(sourceComponent);

            Node@ sourceNode = cast<Node>(sourceComponent);
            
            if (sourceNode !is null)
            {
                if (sourceNode.getParent() !is null)
                    sourceNode.getParent().removeChild(sourceNode, true);

                // Move also all children of the source node to the target entity to keep the hierarchy consistent
                // (note: under the current scene model, programmatically such limitation does not exist)
                array<Node@> allChildren = sourceNode.getChildren(NODE_ANY, true);
                for (uint i = 0; i < allChildren.size(); ++i)
                {
                    sourceEntity.removeComponent(allChildren[i]);
                    targetEntity.addComponent(allChildren[i]);
                }
            }

            updateSceneWindowEntity(sourceEntity);
            updateSceneWindowEntity(targetEntity);

            endModify(targetEntity.getID());
            endModify(sourceEntity.getID());
        }
    }
    else
    {
        Node@ sourceNode = getListComponent(source);
        Node@ targetNode = getListComponent(target);

        // Reparent a node
        // Entity is different: also move to different entity
        if (targetEntity !is sourceEntity)
        {
            beginModify(sourceEntity.getID());
            beginModify(targetEntity.getID());

            sourceEntity.removeComponent(sourceNode);
            targetEntity.addComponent(sourceNode);

            // Move also all children of the source node to the target entity to keep the hierarchy consistent
            // (note: under the current scene model, programmatically such limitation does not exist)
            array<Node@> allChildren = sourceNode.getChildren(NODE_ANY, true);
            for (uint i = 0; i < allChildren.size(); ++i)
            {
                sourceEntity.removeComponent(allChildren[i]);
                targetEntity.addComponent(allChildren[i]);
            }

            // Set transform so that the world transform stays through the parent change
            Vector3 newPos;
            Quaternion newRot;
            Vector3 newScale;
            calculateNewTransform(sourceNode, targetNode, newPos, newRot, newScale);
            targetNode.addChild(sourceNode);
            sourceNode.setTransform(newPos, newRot, newScale);

            updateSceneWindowEntity(sourceEntity);
            updateSceneWindowEntity(targetEntity);

            endModify(targetEntity.getID());
            endModify(sourceEntity.getID());
        }
        // Entity is same: only need to reparent
        else
        {
            beginModify(sourceEntity.getID());
            
            Vector3 newPos;
            Quaternion newRot;
            Vector3 newScale;
            calculateNewTransform(sourceNode, targetNode, newPos, newRot, newScale);
            targetNode.addChild(sourceNode);
            sourceNode.setTransform(newPos, newRot, newScale);

            updateSceneWindowEntity(sourceEntity);
            endModify(sourceEntity.getID());
        }
    }

    selectComponent(sourceComponent);
}

bool testSceneWindowElements(UIElement@ source, UIElement@ target)
{
    Entity@ sourceEntity = editorScene.getEntity(uint(source.userData["EntityID"].getInt()));
    Entity@ targetEntity = editorScene.getEntity(uint(target.userData["EntityID"].getInt()));
    Node@ sourceNode = getListComponent(source);

    // Move component into another entity, or make unparented
    if (target.userData["Type"].getInt() == ITEM_ENTITY)
    {
        if (sourceEntity !is targetEntity)
            return true;
        if ((sourceNode !is null) && (sourceNode.getParent() !is null))
            return true;
        return false;
    }

    // Reparent a node
    Node@ targetNode = getListComponent(target);
    if ((sourceNode is null) || (targetNode is null))
        return false;
    if (sourceNode.getParent() is targetNode)
        return false;
    // Check for looped parent-child assignment
    array<Node@> allChildren = sourceNode.getChildren(NODE_ANY, true);
    for (uint i = 0; i < allChildren.size(); ++i)
    {
        if (allChildren[i] is targetNode)
            return false;
    }
    return true;
}

void calculateNewTransform(Node@ source, Node@ target, Vector3& pos, Quaternion& rot, Vector3& scale)
{
    Vector3 sourceWorldPos = source.getWorldPosition();
    Quaternion sourceWorldRot = source.getWorldRotation();
    Vector3 sourceWorldScale = source.getWorldScale();

    Quaternion inverseTargetWorldRot = target.getWorldRotation().getInverse();
    Vector3 inverseTargetWorldScale = Vector3(1, 1, 1) / target.getWorldScale();
    scale = inverseTargetWorldScale * sourceWorldScale;
    rot = inverseTargetWorldRot * sourceWorldRot;
    pos = inverseTargetWorldScale * (inverseTargetWorldRot * (sourceWorldPos - target.getWorldPosition()));
}

void handleCreateEntity(StringHash eventType, VariantMap& eventData)
{
    DropDownList@ list = eventData["Element"].getUIElement();
    uint mode = list.getSelection();
    if (mode > list.getNumItems())
        return;
    bool local = (mode == 1);
    
    Entity@ newEntity = editorScene.createEntity("", local);
    updateSceneWindowEntity(newEntity);
    uint index = getEntityListIndex(newEntity);

    ListView@ entityList = sceneWindow.getChild("EntityList", true);
    entityList.setSelection(index);
}

void handleCreateComponent(StringHash eventType, VariantMap& eventData)
{
    if (selectedEntity is null)
        return;

    DropDownList@ list = eventData["Element"].getUIElement();
    Text@ text = list.getSelectedItem();
    if (text is null)
        return;

    selectedEntity.createComponent(text.getText(), "");
    updateSceneWindowEntity(selectedEntity);
}

bool checkSceneWindowFocus(bool allowNoElement)
{
    // Allow scene edits only when either no item focused, or the 
    ListView@ list = sceneWindow.getChild("EntityList", true);
    UIElement@ focusElement = ui.getFocusElement();
    if (focusElement is list)
        return true;
    if (focusElement !is null)
        return false;
    return allowNoElement;
}

void sceneDelete()
{
    ListView@ list = sceneWindow.getChild("EntityList", true);
    uint index = list.getSelection();
    uint entityIndex = getEntityListIndex(selectedEntity);
    
    // Remove component
    if ((selectedEntity !is null) && (selectedComponent !is null))
    {
        if (!checkSceneWindowFocus(true))
            return;
        
        uint id = selectedEntity.getID();
        beginModify(id);
        selectedEntity.removeComponent(selectedComponent);
        endModify(id);
        
        // If component is a node, remove it from the parent node
        Node@ node = cast<Node>(selectedComponent);
        if ((node !is null) && (node.getParent() !is null))
            node.getParent().removeChild(node, true);
        
        @selectedComponent = null;
        
        updateSceneWindowEntity(entityIndex, entity);
        
        // Select the next item in the same index
        list.setSelection(index);
    }
    // Remove entity
    if ((selectedEntity !is null) && (selectedComponent is null))
    {
        // Entity operations are dangerous. Require the scene hierarchy to be focused
        if (!checkSceneWindowFocus(false))
            return;
         
        uint id = selectedEntity.getID();
        
        beginModify(id);
        editorScene.removeEntity(selectedEntity);
        endModify(id);
        
        @selectedComponent = null;
        @selectedEntity = null;
        
        updateSceneWindowEntity(entityIndex, null);
        
        // Select the next item in the same index
        list.setSelection(index);
    }
}

void sceneCut()
{
    sceneCopy();
    sceneDelete();
}

void sceneCopy()
{
    // Copy component
    if ((selectedEntity !is null) && (selectedComponent !is null))
    {
        if (!checkSceneWindowFocus(true))
            return;
        
        XMLElement rootElem = copyBuffer.createRootElement("component");
        selectedComponent.saveXML(rootElem);
        
        // If component is a node, save the world transform instead, and delete the parent reference
        Node@ node = cast<Node>(selectedComponent);
        if (node !is null)
        {
            XMLElement transformElem = rootElem.getChildElement("transform");
            transformElem.setVector3("pos", node.getWorldPosition());
            transformElem.setVector3("rot", node.getWorldRotation().getEulerAngles());
            transformElem.setVector3("scale", node.getWorldScale());
            rootElem.removeChildElement("parent", false);
        }
        
        copyBufferEntityID = selectedEntity.getID();
    }
    // Copy entity
    if ((selectedEntity !is null) && (selectedComponent is null))
    {
        if (!checkSceneWindowFocus(false))
            return;
        
        XMLElement rootElem = copyBuffer.createRootElement("entity");
        selectedEntity.saveXML(rootElem);
        copyBufferEntityID = selectedEntity.getID();
    }
}

void scenePaste()
{
    XMLElement rootElem = copyBuffer.getRootElement();
    string mode = rootElem.getName();
    
    if ((mode == "component") && (selectedEntity !is null))
    {
        if (!checkSceneWindowFocus(true))
            return;
        
        beginModify(selectedEntity.getID());
        
        Component@ newComponent = selectedEntity.createComponent(rootElem.getAttribute("type"), rootElem.getAttribute("name"));
        if (newComponent is null)
            return;
        newComponent.loadXML(rootElem);
        newComponent.postLoad();
        
        // If component is a scene node, parent it to the selected component if exists
        Node@ selectedNode = cast<Node>(selectedComponent);
        Node@ newNode = cast<Node>(newComponent);
        if ((newNode !is null) && (selectedNode !is null))
        {
            Vector3 pos;
            Quaternion rot;
            Vector3 scale;
            calculateNewTransform(newNode, selectedNode, pos, rot, scale);
            newNode.setTransform(pos, rot, scale);
            selectedNode.addChild(newNode);
        }
        
        endModify(selectedEntity.getID());
        
        updateSceneWindowEntity(selectedEntity);
    }
    
    if (mode == "entity")
    {
        if (!checkSceneWindowFocus(false))
            return;
        
        // If copied entity was local, make the new local too
        Entity@ newEntity = editorScene.createEntity(rootElem.getAttribute("name"), copyBufferEntityID >= 65536);
        uint newEntityID = newEntity.getID();
        
        beginModify(newEntityID);
        
        // Before loading, rewrite scene node references to the copied entity
        XMLElement compElem = rootElem.getChildElement("component");
        bool rewrite = false;
        while (compElem.notNull())
        {
            XMLElement parentElem = compElem.getChildElement("parent");
            if ((parentElem.notNull()) && (uint(parentElem.getInt("id")) == copyBufferEntityID))
            {
                parentElem.setInt("id", newEntityID);
                rewrite = true;
            }
            compElem = compElem.getNextElement("component");
        }
        
        // If we modified the copybuffer, change the "stored ID" value to reflect the change
        if (rewrite)
            copyBufferEntityID = newEntity.getID();
        
        newEntity.loadXML(rootElem);
        newEntity.postLoad();
        
        endModify(newEntityID);
        
        updateSceneWindowEntity(newEntity);
        uint index = getEntityListIndex(newEntity);
        
        ListView@ list = sceneWindow.getChild("EntityList", true);
        list.setSelection(index);
    }
}
