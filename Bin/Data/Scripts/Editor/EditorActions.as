class EditAction
{
    void Undo()
    {
    }

    void Redo()
    {
    }
}

class EditActionGroup
{
    Array<EditAction@> actions;
}

class CreateNodeAction : EditAction
{
    uint nodeID;
    uint parentID;
    XMLFile@ nodeData;

    void Define(Node@ node)
    {
        nodeID = node.id;
        parentID = node.parent.id;
        nodeData = XMLFile();
        XMLElement rootElem = nodeData.CreateRoot("node");
        node.SaveXML(rootElem);
    }

    void Undo()
    {
        Node@ parent = editorScene.GetNode(parentID);
        Node@ node = editorScene.GetNode(nodeID);
        if (parent !is null && node !is null)
        {
            parent.RemoveChild(node);
            hierarchyList.ClearSelection();
        }
    }

    void Redo()
    {
        Node@ parent = editorScene.GetNode(parentID);
        if (parent !is null)
        {
            Node@ node = parent.CreateChild("", nodeID < FIRST_LOCAL_ID ? REPLICATED : LOCAL, nodeID);
            node.LoadXML(nodeData.root);
            FocusNode(node);
        }
    }
}

class DeleteNodeAction : EditAction
{
    uint nodeID;
    uint parentID;
    XMLFile@ nodeData;

    void Define(Node@ node)
    {
        nodeID = node.id;
        parentID = node.parent.id;
        nodeData = XMLFile();
        XMLElement rootElem = nodeData.CreateRoot("node");
        node.SaveXML(rootElem);
        rootElem.SetUInt("listItemIndex", GetListIndex(node));
    }

    void Undo()
    {
        Node@ parent = editorScene.GetNode(parentID);
        if (parent !is null)
        {
            // Handle update manually so that the node can be reinserted back into its previous list index
            suppressSceneChanges = true;

            Node@ node = parent.CreateChild("", nodeID < FIRST_LOCAL_ID ? REPLICATED : LOCAL, nodeID);
            if (node.LoadXML(nodeData.root))
            {
                uint listItemIndex = nodeData.root.GetUInt("listItemIndex");
                UIElement@ parentItem = hierarchyList.items[GetListIndex(parent)];
                UpdateHierarchyItem(listItemIndex, node, parentItem);
                FocusNode(node);
            }

            suppressSceneChanges = false;
        }
    }

    void Redo()
    {
        Node@ parent = editorScene.GetNode(parentID);
        Node@ node = editorScene.GetNode(nodeID);
        if (parent !is null && node !is null)
        {
            parent.RemoveChild(node);
            hierarchyList.ClearSelection();
        }
    }
}

class ReparentNodeAction : EditAction
{
    uint nodeID;
    uint oldParentID;
    uint newParentID;

    void Define(Node@ node, Node@ newParent)
    {
        nodeID = node.id;
        oldParentID = node.parent.id;
        newParentID = newParent.id;
    }

    void Undo()
    {
        Node@ parent = editorScene.GetNode(oldParentID);
        Node@ node = editorScene.GetNode(nodeID);
        if (parent !is null && node !is null)
            node.parent = parent;
    }

    void Redo()
    {
        Node@ parent = editorScene.GetNode(newParentID);
        Node@ node = editorScene.GetNode(nodeID);
        if (parent !is null && node !is null)
            node.parent = parent;
    }
}

class CreateComponentAction : EditAction
{
    uint nodeID;
    uint componentID;
    XMLFile@ componentData;

    void Define(Component@ component)
    {
        componentID = component.id;
        nodeID = component.node.id;
        componentData = XMLFile();
        XMLElement rootElem = componentData.CreateRoot("component");
        component.SaveXML(rootElem);
    }

    void Undo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        Component@ component = editorScene.GetComponent(componentID);
        if (node !is null && component !is null)
        {
            node.RemoveComponent(component);
            hierarchyList.ClearSelection();
        }
    }

    void Redo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
        {
            Component@ component = node.CreateComponent(componentData.root.GetAttribute("type"), componentID < FIRST_LOCAL_ID ?
                REPLICATED : LOCAL, componentID);
            component.LoadXML(componentData.root);
            component.ApplyAttributes();
            FocusComponent(component);
        }
    }

}

class DeleteComponentAction : EditAction
{
    uint nodeID;
    uint componentID;
    XMLFile@ componentData;

    void Define(Component@ component)
    {
        componentID = component.id;
        nodeID = component.node.id;
        componentData = XMLFile();
        XMLElement rootElem = componentData.CreateRoot("component");
        component.SaveXML(rootElem);
        rootElem.SetUInt("listItemIndex", GetComponentListIndex(component));
    }

    void Undo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
        {
            // Handle update manually so that the component can be reinserted back into its previous list index
            suppressSceneChanges = true;

            Component@ component = node.CreateComponent(componentData.root.GetAttribute("type"), componentID < FIRST_LOCAL_ID ?
                REPLICATED : LOCAL, componentID);
            if (component.LoadXML(componentData.root))
            {
                component.ApplyAttributes();

                uint listItemIndex = componentData.root.GetUInt("listItemIndex");
                UIElement@ parentItem = hierarchyList.items[GetListIndex(node)];
                UpdateHierarchyItem(listItemIndex, component, parentItem);
                FocusComponent(component);
            }

            suppressSceneChanges = false;
        }
    }

    void Redo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        Component@ component = editorScene.GetComponent(componentID);
        if (node !is null && component !is null)
        {
            node.RemoveComponent(component);
            hierarchyList.ClearSelection();
        }
    }
}

class EditAttributeAction : EditAction
{
    int targetType;
    uint targetID;
    uint attrIndex;
    Variant undoValue;
    Variant redoValue;

    void Define(Serializable@ target, uint index, const Variant&in oldValue)
    {
        attrIndex = index;
        undoValue = oldValue;
        redoValue = target.attributes[index];

        targetType = GetType(target);
        targetID = GetID(target, targetType);
    }

    Serializable@ GetTarget()
    {
        switch (targetType)
        {
        case ITEM_NODE:
            return editorScene.GetNode(targetID);
        case ITEM_COMPONENT:
            return editorScene.GetComponent(targetID);
        case ITEM_UI_ELEMENT:
            return GetUIElementByID(targetID);
        }

        return null;
    }

    void Undo()
    {
        Serializable@ target = GetTarget();
        if (target !is null)
        {
            target.attributes[attrIndex] = undoValue;
            target.ApplyAttributes();
            // Can't know if need a full update, so assume true
            attributesFullDirty = true;
            // Apply side effects
            PostEditAttribute(target, attrIndex);
        }
    }

    void Redo()
    {
        Serializable@ target = GetTarget();
        if (target !is null)
        {
            target.attributes[attrIndex] = redoValue;
            target.ApplyAttributes();
            // Can't know if need a full update, so assume true
            attributesFullDirty = true;
            // Apply side effects
            PostEditAttribute(target, attrIndex);
        }
    }
}

class ToggleNodeEnabledAction : EditAction
{
    uint nodeID;
    bool undoValue;

    void Define(Node@ node, bool oldEnabled)
    {
        nodeID = node.id;
        undoValue = oldEnabled;
    }

    void Undo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
            node.SetEnabled(undoValue, true);
    }

    void Redo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
            node.SetEnabled(!undoValue, true);
    }
}

class Transform
{
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;

    void Define(Node@ node)
    {
        position = node.position;
        rotation = node.rotation;
        scale = node.scale;
    }

    void Apply(Node@ node)
    {
        node.SetTransform(position, rotation, scale);
    }
}

class EditNodeTransformAction : EditAction
{
    uint nodeID;
    Transform undoTransform;
    Transform redoTransform;

    void Define(Node@ node, const Transform&in oldTransform)
    {
        nodeID = node.id;
        undoTransform = oldTransform;
        redoTransform.Define(node);
    }

    void Undo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
        {
            undoTransform.Apply(node);
            UpdateNodeAttributes();
        }
    }

    void Redo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
        {
            redoTransform.Apply(node);
            UpdateNodeAttributes();
        }
    }
}

class CreateUIElementAction : EditAction
{
    Variant elementID;
    Variant parentID;
    XMLFile@ elementData;

    void Define(UIElement@ element)
    {
        elementID = GetUIElementID(element);
        parentID = GetUIElementID(element.parent);
        elementData = XMLFile();
        XMLElement rootElem = elementData.CreateRoot("element");
        // Need another nested element tag otherwise the LoadXML() does not work as expected
        XMLElement childElem = rootElem.CreateChild("element");
        element.SaveXML(childElem);
    }

    void Undo()
    {
        UIElement@ parent = GetUIElementByID(parentID);
        UIElement@ element = GetUIElementByID(elementID);
        if (parent !is null && element !is null)
        {
            parent.RemoveChild(element);
            hierarchyList.ClearSelection();
        }
    }

    void Redo()
    {
        UIElement@ parent = GetUIElementByID(parentID);
        if (parent !is null)
        {
            // Have to update manually because the element ID var is not set yet when the E_ELEMENTADDED event is sent
            suppressUIElementChanges = true;

            if (parent.LoadXML(elementData.root))
            {
                UIElement@ element = parent.children[parent.numChildren - 1];
                UpdateHierarchyItem(element);
                FocusUIElement(element);
            }

            suppressUIElementChanges = false;

        }
    }
}

class DeleteUIElementAction : EditAction
{
    Variant elementID;
    Variant parentID;
    XMLFile@ elementData;

    void Define(UIElement@ element)
    {
        elementID = GetUIElementID(element);
        parentID = GetUIElementID(element.parent);
        elementData = XMLFile();
        XMLElement rootElem = elementData.CreateRoot("element");
        XMLElement childElem = rootElem.CreateChild("element");
        element.SaveXML(childElem);
        childElem.SetUInt("index", element.parent.FindChild(element));
        childElem.SetUInt("listItemIndex", GetListIndex(element));
    }

    void Undo()
    {
        UIElement@ parent = GetUIElementByID(parentID);
        if (parent !is null)
        {
            // Have to update manually because the element ID var is not set yet when the E_ELEMENTADDED event is sent
            suppressUIElementChanges = true;

            if (parent.LoadXML(elementData.root))
            {
                XMLElement childElem = elementData.root.GetChild("element");
                uint index = childElem.GetUInt("index");
                uint listItemIndex = childElem.GetUInt("listItemIndex");
                UIElement@ element = parent.children[index];
                UIElement@ parentItem = hierarchyList.items[GetListIndex(parent)];
                UpdateHierarchyItem(listItemIndex, element, parentItem);
                FocusUIElement(element);
            }

            suppressUIElementChanges = false;

        }
    }

    void Redo()
    {
        UIElement@ parent = GetUIElementByID(parentID);
        UIElement@ element = GetUIElementByID(elementID);
        if (parent !is null && element !is null)
        {
            parent.RemoveChild(element);
            hierarchyList.ClearSelection();
        }
    }
}
