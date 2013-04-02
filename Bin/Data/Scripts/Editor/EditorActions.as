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
            ClearSceneSelection();
            parent.RemoveChild(node);
        }
    }
    
    void Redo()
    {
        Node@ parent = editorScene.GetNode(parentID);
        if (parent !is null)
        {
            Node@ node = parent.CreateChild("", nodeID < FIRST_LOCAL_ID ? REPLICATED : LOCAL, nodeID);
            node.LoadXML(nodeData.root);
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
    }

    void Undo()
    {
        Node@ parent = editorScene.GetNode(parentID);
        if (parent !is null)
        {
            Node@ node = parent.CreateChild("", nodeID < FIRST_LOCAL_ID ? REPLICATED : LOCAL, nodeID);
            node.LoadXML(nodeData.root);
        }
    }
    
    void Redo()
    {
        Node@ parent = editorScene.GetNode(parentID);
        Node@ node = editorScene.GetNode(nodeID);
        if (parent !is null && node !is null)
        {
            ClearSceneSelection();
            parent.RemoveChild(node);
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
            ClearSceneSelection();
            node.RemoveComponent(component);
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
    }

    void Undo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
        {
            Component@ component = node.CreateComponent(componentData.root.GetAttribute("type"), componentID < FIRST_LOCAL_ID ?
                REPLICATED : LOCAL, componentID);
            component.LoadXML(componentData.root);
            component.ApplyAttributes();
        }
    }
    
    void Redo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        Component@ component = editorScene.GetComponent(componentID);
        if (node !is null && component !is null)
        {
            ClearSceneSelection();
            node.RemoveComponent(component);
        }
    }
}

enum AttributeTargetType
{
    TARGET_NODE,
    TARGET_COMPONENT,
    TARGET_UIELEMENT
}

class EditAttributeAction : EditAction
{
    // \todo How to identify UI elements for undo/redo? They don't have IDs
    uint targetID;
    AttributeTargetType targetType;
    uint attrIndex;
    Variant undoValue;
    Variant redoValue;

    void Define(Serializable@ target, uint index, const Variant&in oldValue)
    {
        attrIndex = index;
        undoValue = oldValue;
        redoValue = target.attributes[index];

        if (cast<Node>(target) !is null)
        {
            Node@ targetNode = target;
            targetType = TARGET_NODE;
            targetID = targetNode.id;
        }
        else if (cast<Component>(target) !is null)
        {
            Component@ targetComponent = target;
            targetType = TARGET_COMPONENT;
            targetID = targetComponent.id;
        }
        else
        {
            targetType = TARGET_UIELEMENT;
        }
    }

    Serializable@ GetTarget()
    {
        switch (targetType)
        {
        case TARGET_NODE:
            return editorScene.GetNode(targetID);
        case TARGET_COMPONENT:
            return editorScene.GetComponent(targetID);
        default:
            break;
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