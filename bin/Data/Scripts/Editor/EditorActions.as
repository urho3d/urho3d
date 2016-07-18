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

class CreateDrawableMaskAction : EditAction
{
    uint nodeID;
    uint drawableID;
    int oldMask;
    int redoMask;
    int typeMask;

    void Define(Drawable@ drawable, int editMaskType)
    {
        drawableID = drawable.id;
        nodeID = drawable.node.id;
        
        switch (editMaskType) 
        {
            case EDIT_VIEW_MASK:
                oldMask = drawable.viewMask;
                break;
            case EDIT_LIGHT_MASK:
                oldMask = drawable.lightMask;
                break;
            case EDIT_SHADOW_MASK:
                oldMask = drawable.shadowMask;
                break;
            case EDIT_ZONE_MASK:
                oldMask = drawable.zoneMask;
                break;
        } 
                
        typeMask = editMaskType;
        redoMask = oldMask;
    }

    void Undo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        Drawable@ drawable = editorScene.GetComponent(drawableID);
        if (node !is null && drawable !is null)
        {
            switch (typeMask) 
            {
            case EDIT_VIEW_MASK:
                redoMask = drawable.viewMask;
                drawable.viewMask = oldMask;
                break;
            case EDIT_LIGHT_MASK:
                redoMask = drawable.lightMask;
                drawable.lightMask = oldMask;
                break;
            case EDIT_SHADOW_MASK:
                redoMask = drawable.shadowMask;
                drawable.shadowMask = oldMask;
                break;
            case EDIT_ZONE_MASK:
                redoMask = drawable.zoneMask;
                drawable.zoneMask = oldMask;
                break;
            }
        }
    }

    void Redo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        Drawable@ drawable = editorScene.GetComponent(drawableID);
        if (node !is null && drawable !is null)
        {
            switch (typeMask) 
            {
            case EDIT_VIEW_MASK:
                oldMask = drawable.viewMask;
                drawable.viewMask = redoMask;
                break;
            case EDIT_LIGHT_MASK:
                oldMask = drawable.lightMask;
                drawable.lightMask = redoMask;
                break;
            case EDIT_SHADOW_MASK:
                oldMask = drawable.shadowMask;
                drawable.shadowMask = redoMask;
                break;
            case EDIT_ZONE_MASK:
                oldMask = drawable.zoneMask;
                drawable.zoneMask = redoMask;
                break;
            }
        }
    }
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
    Array<uint> nodeList; // 2 uints get inserted per node (node, node.parent)
    bool multiple;

    void Define(Node@ node, Node@ newParent)
    {
        multiple = false;
        nodeID = node.id;
        oldParentID = node.parent.id;
        newParentID = newParent.id;
    }

    void Define(Array<Node@> nodes, Node@ newParent)
    {
        multiple = true;
        newParentID = newParent.id;
        for(uint i = 0; i < nodes.length; ++i)
        {
            Node@ node = nodes[i];
            nodeList.Push(node.id);
            nodeList.Push(node.parent.id);
        }
    }

    void Undo()
    {
        if (multiple)
        {
            for (uint i = 0; i < nodeList.length; i+=2)
            {
                uint nodeID_ = nodeList[i];
                uint oldParentID_ = nodeList[i+1];
                Node@ parent = editorScene.GetNode(oldParentID_);
                Node@ node = editorScene.GetNode(nodeID_);
                if (parent !is null && node !is null)
                    node.parent = parent;
            }
        }
        else
        {
            Node@ parent = editorScene.GetNode(oldParentID);
            Node@ node = editorScene.GetNode(nodeID);
            if (parent !is null && node !is null)
                node.parent = parent;
        }
    }

    void Redo()
    {
        if (multiple)
        {
            Node@ parent = editorScene.GetNode(newParentID);
            if (parent is null)
                return;

            for (uint i = 0; i < nodeList.length; i+=2)
            {
                uint nodeID_ = nodeList[i];
                Node@ node = editorScene.GetNode(nodeID_);
                if (node !is null)
                    node.parent = parent;
            }
        }
        else
        {
            Node@ parent = editorScene.GetNode(newParentID);
            Node@ node = editorScene.GetNode(nodeID);
            if (parent !is null && node !is null)
                node.parent = parent;
        }
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

            if (targetType == ITEM_UI_ELEMENT)
                SetUIElementModified(target);
            else
                SetSceneModified();
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

            if (targetType == ITEM_UI_ELEMENT)
                SetUIElementModified(target);
            else
                SetSceneModified();
        }
    }
}

class ResetAttributesAction : EditAction
{
    int targetType;
    uint targetID;
    Array<Variant> undoValues;
    VariantMap internalVars;    // UIElement specific

    void Define(Serializable@ target)
    {
        for (uint i = 0; i < target.numAttributes; ++i)
            undoValues.Push(target.attributes[i]);

        targetType = GetType(target);
        targetID = GetID(target, targetType);

        if (targetType == ITEM_UI_ELEMENT)
        {
            // Special handling for UIElement to preserve the internal variables containing the element's generated ID among others
            UIElement@ element = target;
            Array<StringHash> keys = element.vars.keys;
            for (uint i = 0; i < keys.length; ++i)
            {
                // If variable name is empty (or unregistered) then it is an internal variable and should be preserved
                String name = GetVarName(keys[i]);
                if (name.empty)
                    internalVars[keys[i]] = element.vars[keys[i]];
            }
        }
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

    void SetInternalVars(UIElement@ element)
    {
        // Revert back internal variables
        Array<StringHash> keys = internalVars.keys;
        for (uint i = 0; i < keys.length; ++i)
            element.vars[keys[i]] = internalVars[keys[i]];

        if (element.vars.Contains(FILENAME_VAR))
            CenterDialog(element);
    }

    void Undo()
    {
        ui.cursor.shape = CS_BUSY;

        Serializable@ target = GetTarget();
        if (target !is null)
        {
            for (uint i = 0; i < target.numAttributes; ++i)
            {
                AttributeInfo info = target.attributeInfos[i];
                if (info.mode & AM_NOEDIT != 0 || info.mode & AM_NODEID != 0 || info.mode & AM_COMPONENTID != 0)
                    continue;

                target.attributes[i] = undoValues[i];
            }
            target.ApplyAttributes();

            // Apply side effects
            for (uint i = 0; i < target.numAttributes; ++i)
                PostEditAttribute(target, i);

            if (targetType == ITEM_UI_ELEMENT)
                SetUIElementModified(target);
            else
                SetSceneModified();

            attributesFullDirty = true;
        }
    }

    void Redo()
    {
        ui.cursor.shape = CS_BUSY;

        Serializable@ target = GetTarget();
        if (target !is null)
        {
            for (uint i = 0; i < target.numAttributes; ++i)
            {
                AttributeInfo info = target.attributeInfos[i];
                if (info.mode & AM_NOEDIT != 0 || info.mode & AM_NODEID != 0 || info.mode & AM_COMPONENTID != 0)
                    continue;

                target.attributes[i] = target.attributeDefaults[i];
            }
            if (targetType == ITEM_UI_ELEMENT)
                SetInternalVars(target);
            target.ApplyAttributes();

            // Apply side effects
            for (uint i = 0; i < target.numAttributes; ++i)
                PostEditAttribute(target, i);

            if (targetType == ITEM_UI_ELEMENT)
                SetUIElementModified(target);
            else
                SetSceneModified();

            attributesFullDirty = true;
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
            node.SetEnabledRecursive(undoValue);
    }

    void Redo()
    {
        Node@ node = editorScene.GetNode(nodeID);
        if (node !is null)
            node.SetEnabledRecursive(!undoValue);
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
    XMLFile@ styleFile;

    void Define(UIElement@ element)
    {
        elementID = GetUIElementID(element);
        parentID = GetUIElementID(element.parent);
        elementData = XMLFile();
        XMLElement rootElem = elementData.CreateRoot("element");
        element.SaveXML(rootElem);
        styleFile = element.defaultStyle;
    }

    void Undo()
    {
        UIElement@ parent = GetUIElementByID(parentID);
        UIElement@ element = GetUIElementByID(elementID);
        if (parent !is null && element !is null)
        {
            parent.RemoveChild(element);
            hierarchyList.ClearSelection();
            SetUIElementModified(parent);
        }
    }

    void Redo()
    {
        UIElement@ parent = GetUIElementByID(parentID);
        if (parent !is null)
        {
            // Have to update manually because the element ID var is not set yet when the E_ELEMENTADDED event is sent
            suppressUIElementChanges = true;

            if (parent.LoadChildXML(elementData.root, styleFile))
            {
                UIElement@ element = parent.children[parent.numChildren - 1];
                UpdateHierarchyItem(element);
                FocusUIElement(element);
                SetUIElementModified(parent);
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
    XMLFile@ styleFile;

    void Define(UIElement@ element)
    {
        elementID = GetUIElementID(element);
        parentID = GetUIElementID(element.parent);
        elementData = XMLFile();
        XMLElement rootElem = elementData.CreateRoot("element");
        element.SaveXML(rootElem);
        rootElem.SetUInt("index", element.parent.FindChild(element));
        rootElem.SetUInt("listItemIndex", GetListIndex(element));
        styleFile = element.defaultStyle;
    }

    void Undo()
    {
        UIElement@ parent = GetUIElementByID(parentID);
        if (parent !is null)
        {
            // Have to update manually because the element ID var is not set yet when the E_ELEMENTADDED event is sent
            suppressUIElementChanges = true;

            if (parent.LoadChildXML(elementData.root, styleFile))
            {
                XMLElement rootElem = elementData.root;
                uint index = rootElem.GetUInt("index");
                uint listItemIndex = rootElem.GetUInt("listItemIndex");
                UIElement@ element = parent.children[index];
                UIElement@ parentItem = hierarchyList.items[GetListIndex(parent)];
                UpdateHierarchyItem(listItemIndex, element, parentItem);
                FocusUIElement(element);
                SetUIElementModified(parent);
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
            SetUIElementModified(parent);
        }
    }
}

class ReparentUIElementAction : EditAction
{
    Variant elementID;
    Variant oldParentID;
    uint oldChildIndex;
    Variant newParentID;

    void Define(UIElement@ element, UIElement@ newParent)
    {
        elementID = GetUIElementID(element);
        oldParentID = GetUIElementID(element.parent);
        oldChildIndex = element.parent.FindChild(element);
        newParentID = GetUIElementID(newParent);
    }

    void Undo()
    {
        UIElement@ parent = GetUIElementByID(oldParentID);
        UIElement@ element = GetUIElementByID(elementID);
        if (parent !is null && element !is null)
        {
            element.SetParent(parent, oldChildIndex);
            SetUIElementModified(parent);
        }
    }

    void Redo()
    {
        UIElement@ parent = GetUIElementByID(newParentID);
        UIElement@ element = GetUIElementByID(elementID);
        if (parent !is null && element !is null)
        {
            element.parent = parent;
            SetUIElementModified(parent);
        }
    }
}

class ApplyUIElementStyleAction : EditAction
{
    Variant elementID;
    Variant parentID;
    XMLFile@ elementData;
    XMLFile@ styleFile;
    String elementOldStyle;
    String elementNewStyle;

    void Define(UIElement@ element, const String&in newStyle)
    {
        elementID = GetUIElementID(element);
        parentID = GetUIElementID(element.parent);
        elementData = XMLFile();
        XMLElement rootElem = elementData.CreateRoot("element");
        element.SaveXML(rootElem);
        rootElem.SetUInt("index", element.parent.FindChild(element));
        rootElem.SetUInt("listItemIndex", GetListIndex(element));
        styleFile = element.defaultStyle;
        elementOldStyle = element.style;
        elementNewStyle = newStyle;
    }

    void ApplyStyle(const String&in style)
    {
        UIElement@ parent = GetUIElementByID(parentID);
        UIElement@ element = GetUIElementByID(elementID);
        if (parent !is null && element !is null)
        {
            // Apply the style in the XML data
            elementData.root.SetAttribute("style", style);

            // Have to update manually because the element ID var is not set yet when the E_ELEMENTADDED event is sent
            suppressUIElementChanges = true;

            parent.RemoveChild(element);
            if (parent.LoadChildXML(elementData.root, styleFile))
            {
                XMLElement rootElem = elementData.root;
                uint index = rootElem.GetUInt("index");
                uint listItemIndex = rootElem.GetUInt("listItemIndex");
                UIElement@ elem = parent.children[index];
                UIElement@ parentItem = hierarchyList.items[GetListIndex(parent)];
                UpdateHierarchyItem(listItemIndex, elem, parentItem);
                SetUIElementModified(elem);
                hierarchyUpdateSelections.Push(listItemIndex);
            }

            suppressUIElementChanges = false;
        }
    }

    void Undo()
    {
        ApplyStyle(elementOldStyle);
    }

    void Redo()
    {
        ApplyStyle(elementNewStyle);
    }
}

class EditMaterialAction : EditAction
{
    XMLFile@ oldState;
    XMLFile@ newState;
    WeakHandle material;

    void Define(Material@ material_, XMLFile@ oldState_)
    {
        material = material_;
        oldState = oldState_;
        newState = XMLFile();

        XMLElement materialElem = newState.CreateRoot("material");
        material_.Save(materialElem);
    }

    void Undo()
    {
        Material@ mat = material.Get();
        if (mat !is null)
        {
            mat.Load(oldState.root);
            RefreshMaterialEditor();
        }
    }

    void Redo()
    {
        Material@ mat = material.Get();
        if (mat !is null)
        {
            mat.Load(newState.root);
            RefreshMaterialEditor();
        }
    }
}

class EditParticleEffectAction : EditAction
{
    XMLFile@ oldState;
    XMLFile@ newState;
    WeakHandle particleEffect;
    ParticleEmitter@ particleEmitter;

    void Define(ParticleEmitter@ particleEmitter_, ParticleEffect@ particleEffect_, XMLFile@ oldState_)
    {
        particleEmitter = particleEmitter_;
        particleEffect = particleEffect_;
        oldState = oldState_;
        newState = XMLFile();

        XMLElement particleElem = newState.CreateRoot("particleeffect");
        particleEffect_.Save(particleElem);
    }

    void Undo()
    {
        ParticleEffect@ effect = particleEffect.Get();
        if (effect !is null)
        {
            effect.Load(oldState.root);
            particleEmitter.ApplyEffect();
            RefreshParticleEffectEditor();
        }
    }

    void Redo()
    {
        ParticleEffect@ effect = particleEffect.Get();
        if (effect !is null)
        {
            effect.Load(newState.root);
            particleEmitter.ApplyEffect();
            RefreshParticleEffectEditor();
        }
    }
}

class AssignMaterialAction : EditAction
{
    WeakHandle model;
    Array<String> oldMaterials;
    String newMaterialName;

    void Define(StaticModel@ model_, Array<String> oldMaterials_, Material@ newMaterial_)
    {
        model = model_;
        oldMaterials = oldMaterials_;
        newMaterialName = newMaterial_.name;
    }

    void Undo()
    {
        StaticModel@ staticModel = model.Get();
        if (staticModel is null)
            return;

        for(uint i=0; i<oldMaterials.length; ++i)
        {
            Material@ material = cache.GetResource("Material", oldMaterials[i]);
            staticModel.materials[i] = material;
        }
    }

    void Redo()
    {
        StaticModel@ staticModel = model.Get();
        if (staticModel is null)
            return;

        Material@ material = cache.GetResource("Material", newMaterialName);
        staticModel.material = material;
    }
}

class AssignModelAction : EditAction
{
    WeakHandle staticModel;
    String oldModel;
    String newModel;

    void Define(StaticModel@ staticModel_, Model@ oldModel_, Model@ newModel_)
    {
        staticModel = staticModel_;
        oldModel = oldModel_.name;
        newModel = newModel_.name;
    }

    void Undo()
    {
        StaticModel@ staticModel_ = staticModel.Get();
        if (staticModel_ is null)
            return;

        Model@ model = cache.GetResource("Model", oldModel);
        if (model is null)
            return;
        staticModel_.model = model;
    }

    void Redo()
    {
        StaticModel@ staticModel_ = staticModel.Get();
        if (staticModel_ is null)
            return;

        Model@ model = cache.GetResource("Model", newModel);
        if (model is null)
            return;
        staticModel_.model = model;
    }

}
