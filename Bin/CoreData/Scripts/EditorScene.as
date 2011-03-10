// Urho3D editor scene handling

#include "Scripts/EditorSceneWindow.as"
#include "Scripts/EditorComponentWindow.as"

Scene@ editorScene;
Window@ sceneSettingsDialog;

string sceneFileName;
string sceneResourcePath;
bool sceneModified = false;
bool runPhysics = false;
bool subscribedToSceneSettingsEdits = false;
bool octreeDebug = false;
int debugGeometryMode = 0;

Component@ selectedComponent;
Entity@ selectedEntity;

void createScene()
{
    @selectedComponent = null;
    @selectedEntity = null;

    // Create a scene with default values, these will be overridden when loading scenes
    @editorScene = engine.createScene("Urho3D Editor", BoundingBox(-1000.0, 1000.0), 8, true);

    // Always pause the scene for now
    editorScene.setPaused(true);

    if (sceneWindow !is null)
    {
        updateSceneWindow(false);
        updateComponentWindow();
    }

    runPhysics = false;
    sceneFileName = "";
    updateWindowTitle();
    createCamera();

    subscribeToEvent("PostRenderUpdate", "scenePostRenderUpdate");
    subscribeToEvent("UIMouseClick", "sceneMouseClick");
    
    engine.setDefaultScene(editorScene);
    
    updateSceneSettingsDialog();
}

void createSceneSettingsDialog()
{
    if (sceneSettingsDialog !is null)
        return;
    
    @sceneSettingsDialog = ui.loadLayout(cache.getResource("XMLFile", "UI/SceneSettingsDialog.xml"), uiStyle);
    uiRoot.addChild(sceneSettingsDialog);
    centerDialog(sceneSettingsDialog);
    updateSceneSettingsDialog();
    hideSceneSettingsDialog();
}

void updateSceneSettingsDialog()
{
    if (sceneSettingsDialog is null)
        return;
        
    // Fill the current values and subscribe to changes
    LineEdit@ octreeMinEdit = sceneSettingsDialog.getChild("OctreeMinEdit", true);
    octreeMinEdit.setText(editorScene.getOctree().getWorldBoundingBox().min.toString());
    
    LineEdit@ octreeMaxEdit = sceneSettingsDialog.getChild("OctreeMaxEdit", true);
    octreeMaxEdit.setText(editorScene.getOctree().getWorldBoundingBox().max.toString());
    
    LineEdit@ octreeLevelsEdit = sceneSettingsDialog.getChild("OctreeLevelsEdit", true);
    octreeLevelsEdit.setText(toString(editorScene.getOctree().getNumLevels()));
    
    LineEdit@ gravityEdit = sceneSettingsDialog.getChild("GravityEdit", true);
    gravityEdit.setText(editorScene.getPhysicsWorld().getGravity().toString());
    
    if (!subscribedToSceneSettingsEdits)
    {
        subscribeToEvent(octreeMinEdit, "TextFinished", "editOctreeMin");
        subscribeToEvent(octreeMaxEdit, "TextFinished", "editOctreeMax");
        subscribeToEvent(octreeLevelsEdit, "TextFinished", "editOctreeLevels");
        subscribeToEvent(gravityEdit, "TextFinished", "editGravity");
        subscribeToEvent(sceneSettingsDialog.getChild("CloseButton", true), "Released", "hideSceneSettingsDialog");
        subscribedToSceneSettingsEdits = true;
    }
}

void showSceneSettingsDialog()
{
    sceneSettingsDialog.setVisible(true);
    sceneSettingsDialog.bringToFront();
}

void hideSceneSettingsDialog()
{
    sceneSettingsDialog.setVisible(false);
}

void editOctreeMin(StringHash eventType, VariantMap& eventData)
{
    Octree@ octree = editorScene.getOctree();
    LineEdit@ edit = eventData["Element"].getUIElement();
    BoundingBox box = octree.getWorldBoundingBox();
    box.min = edit.getText().toVector3();
    edit.setText(box.min.toString());
    
    octree.resize(box, octree.getNumLevels());
}

void editOctreeMax(StringHash eventType, VariantMap& eventData)
{
    Octree@ octree = editorScene.getOctree();
    LineEdit@ edit = eventData["Element"].getUIElement();
    BoundingBox box = octree.getWorldBoundingBox();
    box.max = edit.getText().toVector3();
    edit.setText(box.max.toString());
    
    octree.resize(box, octree.getNumLevels());
}

void editOctreeLevels(StringHash eventType, VariantMap& eventData)
{
    Octree@ octree = editorScene.getOctree();
    LineEdit@ edit = eventData["Element"].getUIElement();
    octree.resize(octree.getWorldBoundingBox(), edit.getText().toInt());
    edit.setText(toString(octree.getNumLevels()));
}

void editGravity(StringHash eventType, VariantMap& eventData)
{
    LineEdit@ edit = eventData["Element"].getUIElement();
    editorScene.getPhysicsWorld().setGravity(edit.getText().toVector3());
    edit.setText(editorScene.getPhysicsWorld().getGravity().toString());
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

void reloadResources()
{
    array<Resource@> sceneResources = editorScene.getResourceRefs();
    uint numResources = sceneResources.size();
    for (uint i = 0; i < numResources; ++i)
    {
        // Material textures are not listed by getResourceRefs(), so have to handle them manually
        Material@ mat = cast<Material>(sceneResources[i]);
        if (mat !is null)
        {
            for (uint j = 0; j < mat.getNumTechniques(); ++j)
            {
                MaterialTechnique@ tech = mat.getTechnique(j);
                for (int k = 0; k < MAX_MATERIAL_TEXTURE_UNITS; ++k)
                {
                    Texture@ tex = tech.getTexture(TextureUnit(k));
                    if (tex !is null)
                    {
                        bool found = false;
                        for (uint l = numResources; l < sceneResources.size(); ++l)
                        {
                            if (sceneResources[l] is tex)
                            {
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            sceneResources.push(tex);
                    }
                }
            }
        }
    }

    print("Reloading resources");
    for (uint i = 0; i < sceneResources.size(); ++i)
        cache.reloadResource(sceneResources[i]);
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
    @selectedComponent = null;
    @selectedEntity = null;
    editorScene.removeAllEntities();

    // Add the new resource path
    setResourcePath(getPath(fileName));

    File file(fileName, FILE_READ);
    string extension = getExtension(fileName);
    if ((extension == ".bin") || (extension == ".dat"))
        editorScene.load(file);
    else
        editorScene.loadXML(file);
    
    sceneFileName = fileName;
    sceneModified = false;
    runPhysics = false;
    updateWindowTitle();
    updateSceneSettingsDialog();
    updateSceneWindow(false);
    updateComponentWindow();
    resetCamera();
}

void saveScene(string fileName)
{
    if ((fileName.empty()) || (getFileName(fileName).empty()))
        return;

    editorScene.setName(getFileName(fileName));

    File file(fileName, FILE_WRITE);
    string extension = getExtension(fileName);
    if ((extension == ".bin") || (extension == ".sav"))
        editorScene.save(file);
    else
        editorScene.saveXML(file);

    sceneFileName = fileName;
    sceneModified = false;
    updateWindowTitle();
}

void beginModify(uint entityID)
{
    // Undo/Redo can be implemented here
}

void endModify(uint entityID)
{
    // Undo/Redo can be implemented here

    if (!sceneModified)
    {
        sceneModified = true;
        updateWindowTitle();
    }
}

string getEntityTitle(Entity@ entity)
{
    string name = entity.getName();
    if (name.empty())
        return "Entity (ID " + entity.getID() + ")";
    else
        return name + " (ID " + entity.getID() + ")";
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
        return indentStr + name + " (" + component.getTypeName() + ")";
}

void scenePostRenderUpdate()
{
    DebugRenderer@ debug = editorScene.getDebugRenderer();
    
    // Visualize current selection (either renderables or rigidbodies can be visualized)
    if (selectedComponent !is null)
    {
        VolumeNode@ node = cast<VolumeNode>(selectedComponent);
        if (node !is null)
            node.drawDebugGeometry(debug, false);
        else
        {
            RigidBody@ body = cast<RigidBody>(selectedComponent);
            if (body !is null)
                body.drawDebugGeometry(debug, false);
        }
    }
    
    switch (debugGeometryMode)
    {
        // Draw all renderer debug geometry
    case 1:
        pipeline.drawDebugGeometry(false);
        break;
        
        // Draw all physics debug geometry
    case 2:
        editorScene.getPhysicsWorld().drawDebugGeometry(true);
        break;
    }
    
    // Additionally, draw octree debug
    if (octreeDebug)
        editorScene.getOctree().drawDebugGeometry(true);
    
    sceneRaycast(false);
}

void sceneMouseClick()
{
    sceneRaycast(true);
}

void sceneRaycast(bool mouseClick)
{
    DebugRenderer@ debug = editorScene.getDebugRenderer();
    IntVector2 pos = ui.getCursorPosition();

    //! \todo allow to switch between renderer and physics raycast
    if (ui.getElementAt(pos, true) is null)
    {
        Ray cameraRay = camera.getScreenRay(float(pos.x) / renderer.getWidth(), float(pos.y) / renderer.getHeight());
        array<RayQueryResult> result = editorScene.getOctree().raycast(cameraRay, NODE_GEOMETRY, camera.getFarClip(), RAY_TRIANGLE);
        GeometryNode@ node;
        if (!result.empty())
        {
            @node = result[0].node;
            node.drawDebugGeometry(debug, false);
        }
        if ((mouseClick) && (input.getMouseButtonPress(MOUSEB_LEFT)))
            selectComponent(node);
    }
}

void toggleDebugGeometry()
{
    ++debugGeometryMode;
    if (debugGeometryMode == 3)
        debugGeometryMode = 0;
}

void toggleOctreeDebug()
{
    octreeDebug = !octreeDebug;
}

void togglePhysics()
{
    runPhysics = !runPhysics;
}

