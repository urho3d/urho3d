class EditAction
{
    void Undo()
    {
    }
    
    void Redo()
    {
    }
    
    void RewriteNodeID(uint oldID, uint newID)
    {
    }

    void RewriteComponentID(uint oldID, uint newID)
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
            Node@ node = parent.CreateChild("", nodeID < FIRST_LOCAL_ID ? REPLICATED : LOCAL);
            node.LoadXML(nodeData.root);
            // Node gets a new ID. Rewrite it in all undo commands
            RewriteEditActionNodeIDs(nodeID, node.id);
        }
    }
    
    void RewriteNodeID(uint oldID, uint newID)
    {
        if (nodeID == oldID)
            nodeID = newID;
        if (parentID == oldID)
            parentID = newID;
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
            Node@ node = parent.CreateChild("", nodeID < FIRST_LOCAL_ID ? REPLICATED : LOCAL);
            node.LoadXML(nodeData.root);
            // Node gets a new ID. Rewrite it in all undo commands
            RewriteEditActionNodeIDs(nodeID, node.id);
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
    
    void RewriteNodeID(uint oldID, uint newID)
    {
        if (nodeID == oldID)
            nodeID = newID;
        if (parentID == oldID)
            parentID = newID;
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

    void RewriteNodeID(uint oldID, uint newID)
    {
        if (nodeID == oldID)
            nodeID = newID;
        if (oldParentID == oldID)
            oldParentID = newID;
        if (newParentID == oldID)
            newParentID = newID;
    }
}