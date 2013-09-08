
#
# This script is licensed as public domain.
#

# http://www.blender.org/documentation/blender_python_api_2_57_release/bpy.props.html
# http://www.blender.org/documentation/blender_python_api_2_59_0/bpy.props.html
# http://www.blender.org/documentation/blender_python_api_2_66_4/bpy.props.html
# http://www.blender.org/documentation/blender_python_api_2_57_release/bpy.types.Panel.html
# http://www.blender.org/documentation/blender_python_api_2_57_release/bpy.types.PropertyGroup.html
# http://www.blender.org/documentation/blender_python_api_2_66_4/bpy.types.WindowManager.html
# http://wiki.blender.org/index.php/Dev:2.5/Py/Scripts/Guidelines/Layouts
# http://wiki.blender.org/index.php/Dev:2.5/Py/Scripts/Cookbook/Code_snippets/Properties
# http://wiki.blender.org/index.php/Dev:2.5/Py/Scripts/Cookbook/Code_snippets/Interface
# http://wiki.blender.org/index.php/Dev:IT/2.5/Py/Scripts/Cookbook/Code_snippets/Interface
# http://wiki.blender.org/index.php/Dev:IT/2.5/Py/Scripts/Cookbook/Code_snippets/Multi-File_packages
# http://wiki.blender.org/index.php/Doc:2.6/Manual/Extensions/Python/Properties
# http://www.blender.org/documentation/blender_python_api_2_66_4/info_tutorial_addon.html

#print("Urho init ---------------------------------------------------")

bl_info = {
    "name": "Urho3D export",
    "description": "Urho3D export",
    "author": "reattiva",
    "version": (0, 3),
    "blender": (2, 66, 0),
    "location": "Properties > Render > Urho export",
    "warning": "big bugs, use at your own risk",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}

if "decompose" in locals():
    import imp
    imp.reload(decompose)
    imp.reload(export_urho)

from .decompose import TOptions, Scan
from .export_urho import UrhoExportData, UrhoExportOptions, UrhoWriteModel, UrhoWriteAnimation, UrhoWriteMaterial, UrhoExport
    
import os
import time
import sys
import shutil
import logging

import bpy
from bpy.props import StringProperty, BoolProperty, EnumProperty, FloatProperty, IntProperty

#--------------------
# Loggers
#--------------------

# A list to save export messages
logList = []

# Create a logger
log = logging.getLogger("ExportLogger")
log.setLevel(logging.DEBUG)

# Formatter for the logger
FORMAT = '%(levelname)s:%(message)s'
formatter = logging.Formatter(FORMAT)

# Console filter: no more than 3 identical messages 
consoleFilterMsg = None
consoleFilterCount = 0
class ConsoleFilter(logging.Filter):
    def filter(self, record):
        global consoleFilterMsg
        global consoleFilterCount
        if consoleFilterMsg == record.msg:
            consoleFilterCount += 1
            if consoleFilterCount > 2:
                return False
        else:
            consoleFilterCount = 0
            consoleFilterMsg = record.msg
        return True
consoleFilter = ConsoleFilter()

# Logger handler which saves unique messages in the list
logMaxCount = 500
class ExportLoggerHandler(logging.StreamHandler):
    def emit(self, record):
        global logList
        try:
            if len(logList) < logMaxCount:
                msg = self.format(record)
                if not msg in logList:
                    logList.append(msg)
            #self.flush()
        except (KeyboardInterrupt, SystemExit):
            raise
        except:
            self.handleError(record)

# Delete old handlers
for handler in reversed(log.handlers):
    log.removeHandler(handler)

# Create a logger handler for the list
listHandler = ExportLoggerHandler()
listHandler.setFormatter(formatter)
log.addHandler(listHandler)
    
# Create a logger handler for the console
consoleHandler = logging.StreamHandler()
consoleHandler.addFilter(consoleFilter)
log.addHandler(consoleHandler)

#--------------------
# Blender UI
#--------------------

# Addon preferences, they are visible in the Users Preferences Addons page,
# under the Uhro exporter addon row
class UrhoAddonPreferences(bpy.types.AddonPreferences):
    bl_idname = __name__

    outputPath = StringProperty(
            name = "Default export path",
            description = "Default path where to export",
            default = "", 
            maxlen = 1024,
            subtype = "DIR_PATH")

    reportWidth = IntProperty(
            name = "Window width",
            description = "Width of the report window",
            default = 500)

    maxMessagesCount = IntProperty(
            name = "Max number of messages",
            description = "Max number of messages in the report window",
            default = 500)
            
    def draw(self, context):
        layout = self.layout
        layout.prop(self, "outputPath")
        row = layout.row()
        row.label("Report window:")
        row.prop(self, "reportWidth")
        row.prop(self, "maxMessagesCount")


# Here we define all the UI objects we'll add in the export panel
class UrhoExportSettings(bpy.types.PropertyGroup):

    # This is called each time a property (created with the parameter 'update')
    # changes its value
    def update_func(self, context):

        addonPrefs = context.user_preferences.addons[__name__].preferences
        if self.outputPath:
            addonPrefs.outputPath = self.outputPath
        if self.skeletons:
            self.geometryWei = True
        else:
            self.geometryWei = False
            self.animations = False
        if not self.geometries:
            self.morphs = False
        if not self.geometryPos or not self.geometryNor or not self.geometryUV:
            self.geometryTan = False
        if not self.morphNor:
            self.morphTan = False

    # Set all the export settings back to their default values
    def reset(self, context): 
        
        addonPrefs = context.user_preferences.addons[__name__].preferences
        if not self.outputPath:
            self.outputPath = addonPrefs.outputPath
        
        self.useStandardDirs = True
        self.fileOverwrite = False

        self.source = 'ONLY_SELECTED'
        self.scale = 1.0
        self.modifiers = False
        self.modifiersRes = 'PREVIEW'
        self.origin = 'LOCAL'
        self.forceElements = False
        self.merge = False
        self.geometrySplit = False
        self.lods = False
        self.optimizeIndices = False

        self.skeletons = True
        self.onlyKeyedBones = False

        self.animations = False
        self.actions = True
        self.onlyUsedActions = False
        self.tracks = False
        self.timeline = False
        self.animationPos = True
        self.animationRot = True
        self.animationSca = False

        self.geometries = True
        self.geometryPos = True
        self.geometryNor = True
        self.geometryCol = False
        self.geometryUV = False
        self.geometryTan = False
        self.geometryWei = False

        self.morphs = False
        self.morphNor = True
        self.morphTan = False

        self.materials = False
        self.textures = False

    # --- Output settings ---
    
    outputPath = StringProperty(
            name = "",
            description = "Path where to export",
            default = "", 
            maxlen = 1024,
            subtype = "DIR_PATH",
            update = update_func)   

    useStandardDirs = BoolProperty(
            name = "Use Urho standard folders",
            description = "Use Urho standard folders (Materials, Models, Textures ...)",
            default = True)

    fileOverwrite = BoolProperty(
            name = "Files overwrite",
            description = "If enabled existing files are overwritten without warnings",
            default = False)

    # --- Source settings ---
            
    source = EnumProperty(
            name = "Source",
            description = "Objects to be exported",
            items=(('ALL', "All", "export all the objects in the scene"),
                   ('ONLY_SELECTED', "Only selected", "export only the selected objects")),
            default='ONLY_SELECTED')

    scale = FloatProperty(
            name = "Scale", 
            description = "Scale to apply on the exported objects", 
            default = 1.0,
            min = 0.0, 
            max = 1000.0,
            step = 10,
            precision = 1)

    modifiers = BoolProperty(
            name = "Apply modifiers",
            description = "Apply the object modifiers before exporting",
            default = False)

    modifiersRes = EnumProperty(
            name = "Modifiers setting",
            description = "Resolution setting to use while applying modifiers",
            items=(('PREVIEW', "Preview", "use the Preview resolution setting"),
                   ('RENDER', "Render", "use the Render resolution setting")),
            default='PREVIEW')

    origin = EnumProperty(
            name = "Mesh origin",
            description = "Origin for the position of vertices/bones",
            items=(('GLOBAL', "Global", "Blender's global origin"),
                   ('LOCAL', "Local", "object's local origin (orange dot)")),
            default='LOCAL')

    forceElements = BoolProperty(
            name = "Force missing elements",
            description = "If a vertec elements is missing add it with a zero value (UV, color, weights)",
            default = False)

    merge = BoolProperty(
            name = "Merge objects (uses current object name)",
            description = "Merge all the objects in a single file (one geometry for object)",
            default = False)

    geometrySplit = BoolProperty(
            name = "One vertex buffer per object",
            description = "Split each object into its own vertex buffer",
            default = False)

    lods = BoolProperty(
            name = "Use LODs",
            description = "Search for the LOD distance if the object name, objects with the same name are added as LODs",
            default = False)

    optimizeIndices = BoolProperty(
            name = "Optimize indices (slow)",
            description = "Linear-Speed vertex cache optimisation",
            default = False)

    # --- Components settings ---

    skeletons = BoolProperty(
            name = "Skeletons",
            description = "Export model armature bones",
            default = False,
            update = update_func)

    onlyKeyedBones = BoolProperty(
            name = "Only keyed bones",
            description = "Export only bones with keys",
            default = False)

    animations = BoolProperty(
            name = "Animations",
            description = "Export animations (Skeletons needed)",
            default = False)
            
    actions = BoolProperty(
            name = "Actions",
            description = "Export actions",
            default = True)

    onlyUsedActions = BoolProperty(
            name = "Only actions used in tracks",
            description = "Export only actions used in the NLA tracks",
            default = True)

    tracks = BoolProperty(
            name = "Tracks (only not muted)",
            description = "Export not muted NLA tracks",
            default = False)

    timeline = BoolProperty(
            name = "Timeline",
            description = "Export the timeline (NLA tracks sum)",
            default = False)

    animationPos = BoolProperty(
            name = "Position",
            description = "Within animations export bone positions",
            default = True)

    animationRot = BoolProperty(
            name = "Rotation",
            description = "Within animations export bone rotations",
            default = True)

    animationSca = BoolProperty(
            name = "Scale",
            description = "Within animations export bone scales",
            default = False)

    geometries = BoolProperty(
            name = "Geometries",
            description = "Export vertex buffers, index buffers, geometries, lods",
            default = True,
            update = update_func)

    geometryPos = BoolProperty(
            name = "Position",
            description = "Within geometry export vertex position",
            default = True,
            update = update_func)

    geometryNor = BoolProperty(
            name = "Normal",
            description = "Within geometry export vertex normal",
            default = True,
            update = update_func)

    geometryCol = BoolProperty(
            name = "Color",
            description = "Within geometry export vertex color",
            default = False)

    geometryUV = BoolProperty(
            name = "UV",
            description = "Within geometry export vertex UV",
            default = True,
            update = update_func)

    geometryTan = BoolProperty(
            name = "Tangent",
            description = "Within geometry export vertex tangent",
            default = False)

    geometryWei = BoolProperty(
            name = "Weights",
            description = "Within geometry export vertex bones weights (Skeletons needed)",
            default = False)

    morphs = BoolProperty(
            name = "Morphs (shape keys)",
            description = "Export vertex morphs (Geometries needed)",
            default = False)

    morphNor = BoolProperty(
            name = "Normal",
            description = "Within morph export vertex normal",
            default = True,
            update = update_func)

    morphTan = BoolProperty(
            name = "Tangent",
            description = "Within morph export vertex tangent",
            default = False)

    materials = BoolProperty(
            name = "Export materials",
            description = "Export XML materials",
            default = False,
            update = update_func)

    textures = BoolProperty(
            name = "Copy textures",
            description = "Copy diffuse textures",
            default = False,
            update = update_func)            

    bonesGlobalOrigin = BoolProperty(name = "Bones global origin", default = False)
    actionsGlobalOrigin = BoolProperty(name = "Actions global origin", default = False)
    

# Reset settings button    
class UrhoExportResetOperator(bpy.types.Operator):
    """ Reset export settings """
    
    bl_idname = "urho.exportreset"
    bl_label = "Reset"
 
    def execute(self, context):
        context.scene.urho_exportsettings.reset(context)
        return {'FINISHED'}
     

# View log button
class UrhoReportDialog(bpy.types.Operator):
    """ View export log """
    
    bl_idname = "urho.report"
    bl_label = "Urho export report"
 
    def execute(self, context):
        return {'FINISHED'}
 
    def invoke(self, context, event):
        global logMaxCount
        wm = context.window_manager
        addonPrefs = context.user_preferences.addons[__name__].preferences
        logMaxCount = addonPrefs.maxMessagesCount
        return wm.invoke_props_dialog(self, width = addonPrefs.reportWidth)
        #return wm.invoke_popup(self, width = addonPrefs.reportWidth)
     
    def draw(self, context):
        layout = self.layout
        scene = context.scene
        
        for line in logList:
            lines = line.split(":", 1)
            if lines[0] == 'CRITICAL':
                lineicon = 'RADIO'
            elif lines[0] == 'ERROR':
                lineicon = 'CANCEL'
            elif lines[0] == 'WARNING':
                lineicon = 'ERROR'
            elif lines[0] == 'INFO':
                lineicon = 'INFO'
            else:
                lineicon = 'TEXT'
            layout.label(text = lines[1], icon = lineicon)
            
# Export button
class UrhoExportOperator(bpy.types.Operator):
    """ Start exporting """
    
    bl_idname = "urho.export"
    bl_label = "Export"
  
    def execute(self, context):
        ExecuteUrhoExport(context)
        return {'FINISHED'}
 
    def invoke(self, context, event):
        return self.execute(context)
    
# The export panel, here we draw the panel using properties we have created earlier
class UrhoExportRenderPanel(bpy.types.Panel):
    
    bl_idname = "urho.exportrenderpanel"
    bl_label = "Urho export"
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = "render"
    #bl_options = {'DEFAULT_CLOSED'}
    
    # Draw the export panel
    def draw(self, context):
        layout = self.layout
        scene = context.scene
        settings = scene.urho_exportsettings

        row = layout.row()
        #row=layout.row(align=True)
        row.operator("urho.export", icon='EXPORT')
        #split = layout.split(percentage=0.1)
        row.operator("urho.report", text="", icon='TEXT')

        layout.label("Output:")
        box = layout.box()      

        box.label("Output folder:")
        box.prop(settings, "outputPath")
        box.prop(settings, "useStandardDirs")
        box.prop(settings, "fileOverwrite")

        row = layout.row()    
        row.label("Settings:")
        row.operator("urho.exportreset", text="", icon='FILE')
        
        box = layout.box()

        row = box.row()
        row.label("Objects:")
        row.prop(settings, "source", expand=True)

        row = box.row()
        row.label("Origin:")
        row.prop(settings, "origin", expand=True)

        box.prop(settings, "scale")
        
        box.prop(settings, "modifiers")
        if settings.modifiers:
            row = box.row()
            row.separator()
            row.prop(settings, "modifiersRes", expand=True)

        box.prop(settings, "forceElements")
        box.prop(settings, "merge")
        box.prop(settings, "geometrySplit")
        box.prop(settings, "lods")
        box.prop(settings, "optimizeIndices")

        box = layout.box()

        row = box.row()
        row.prop(settings, "skeletons")
        row.label("", icon='BONE_DATA')
        #if settings.skeletons:
            #row = box.row()
            #row.separator()
            #row.prop(settings, "bonesGlobalOrigin")
            #row.prop(settings, "actionsGlobalOrigin")

        row = box.row()
        row.enabled = settings.skeletons
        row.prop(settings, "animations")
        row.label("", icon='ANIM_DATA')
        if settings.skeletons and settings.animations:
            row = box.row()
            row.separator()
            column = row.column()
            column.prop(settings, "actions")
            if settings.actions:
                row = column.row()
                row.separator()
                row.prop(settings, "onlyUsedActions")
            column.prop(settings, "tracks")
            column.prop(settings, "timeline")
            column.prop(settings, "onlyKeyedBones")
            row = column.row()
            row.prop(settings, "animationPos")
            row.prop(settings, "animationRot")
            row.prop(settings, "animationSca")
        
        row = box.row()
        row.prop(settings, "geometries")
        row.label("", icon='MESH_DATA')
        if settings.geometries:
            row = box.row()
            row.separator()
            row.prop(settings, "geometryPos")
            row.prop(settings, "geometryNor")
            row.prop(settings, "geometryUV")
            row = box.row()
            row.separator()
            col = row.column()
            col.enabled = settings.geometryPos and settings.geometryNor and settings.geometryUV
            col.prop(settings, "geometryTan")
            col = row.column()
            col.enabled = settings.skeletons
            col.prop(settings, "geometryWei")
            row.prop(settings, "geometryCol")

        row = box.row()
        row.enabled = settings.geometries
        row.prop(settings, "morphs")
        row.label("", icon='SHAPEKEY_DATA')
        if settings.geometries and settings.morphs:
            row = box.row()
            row.separator()
            row.prop(settings, "morphNor")
            col = row.column()
            col.enabled = settings.morphNor
            col.prop(settings, "morphTan")

        row = box.row()
        row.prop(settings, "materials")
        row.label("", icon='MATERIAL_DATA')

        row = box.row()
        row.prop(settings, "textures")
        row.label("", icon='TEXTURE_DATA')
        
# This is a test to set the default path if the path edit box is empty        
def PostLoad(dummy):

    addonPrefs = bpy.context.user_preferences.addons[__name__].preferences
    settings = bpy.context.scene.urho_exportsettings
    if addonPrefs.outputPath:
        settings.outputPath = addonPrefs.outputPath

# Called when the addon is enabled. Here we register out UI classes so they can be 
# used by Python scripts.
def register():
    print("Urho export register")
    
    #bpy.utils.register_module(__name__)
        
    bpy.utils.register_class(UrhoAddonPreferences)
    bpy.utils.register_class(UrhoExportSettings)
    bpy.utils.register_class(UrhoExportOperator) 
    bpy.utils.register_class(UrhoExportResetOperator) 
    bpy.utils.register_class(UrhoExportRenderPanel)
    bpy.utils.register_class(UrhoReportDialog)
    
    bpy.types.Scene.urho_exportsettings = bpy.props.PointerProperty(type=UrhoExportSettings)
    
    bpy.context.user_preferences.filepaths.use_relative_paths = False
    
    #if not PostLoad in bpy.app.handlers.load_post:
    #    bpy.app.handlers.load_post.append(PostLoad)


# Note: the script __init__.py is executed only the first time the addons is enabled. After that
# disabling or enabling the script will only call unregister() or register(). So in unregister()
# delete only objects created with register(), do not delete global objects as they will not be
# created re-enabling the addon.
# __init__.py is re-executed pressing F8 or randomly(?) enabling the addon.

# Called when the addon is disabled. Here we remove our UI classes.
def unregister():
    print("Urho export unregister")
    
    #bpy.utils.unregister_module(__name__)
    
    bpy.utils.unregister_class(UrhoAddonPreferences)
    bpy.utils.unregister_class(UrhoExportSettings)
    bpy.utils.unregister_class(UrhoExportOperator) 
    bpy.utils.unregister_class(UrhoExportResetOperator) 
    bpy.utils.unregister_class(UrhoExportRenderPanel)
    bpy.utils.unregister_class(UrhoReportDialog)
    
    del bpy.types.Scene.urho_exportsettings
    
    #if PostLoad in bpy.app.handlers.load_post:
    #    bpy.app.handlers.load_post.remove(PostLoad)


#-------------------------------------------------------------------------
    
def ExecuteUrhoExport(context):
    global logList

    startTime = time.time()
    
    print("----------------------Urho export start----------------------")
    
    # Clear log list
    logList[:] = []
    
    # Get exporter UI settings
    settings = context.scene.urho_exportsettings
    
    # List where to store tData (decomposed object)
    tDataList = []
    # Decompose options
    tOptions = TOptions()
        
    # Copy from exporter UI settings to Decompose options
    tOptions.mergeObjects = settings.merge
    tOptions.doForceElements = settings.forceElements
    tOptions.useLods = settings.lods
    tOptions.onlySelected = (settings.source == 'ONLY_SELECTED')
    tOptions.scale = settings.scale
    tOptions.globalOrigin = (settings.origin == 'GLOBAL')
    tOptions.applyModifiers = settings.modifiers
    tOptions.applySettings = settings.modifiersRes
    tOptions.doBones = settings.skeletons
    tOptions.doOnlyKeyedBones = settings.onlyKeyedBones
    tOptions.doAnimations = settings.animations
    tOptions.doActions = settings.actions
    tOptions.doOnlyUsedActions = settings.onlyUsedActions
    tOptions.doTracks = settings.tracks
    tOptions.doTimeline = settings.timeline
    tOptions.doAnimationPos = settings.animationPos
    tOptions.doAnimationRot = settings.animationRot
    tOptions.doAnimationSca = settings.animationSca
    tOptions.doGeometries = settings.geometries
    tOptions.doGeometryPos = settings.geometryPos
    tOptions.doGeometryNor = settings.geometryNor
    tOptions.doGeometryCol = settings.geometryCol
    tOptions.doGeometryUV  = settings.geometryUV
    tOptions.doGeometryTan = settings.geometryTan
    tOptions.doGeometryWei = settings.geometryWei
    tOptions.doMorphs = settings.morphs
    tOptions.doMorphNor = settings.morphNor
    tOptions.doMorphTan = settings.morphTan
    tOptions.doMorphUV = settings.morphTan
    tOptions.doOptimizeIndices = settings.optimizeIndices
    tOptions.doMaterials = settings.materials or settings.textures
    tOptions.bonesGlobalOrigin = settings.bonesGlobalOrigin
    tOptions.actionsGlobalOrigin = settings.actionsGlobalOrigin
    
    if tOptions.mergeObjects and not tOptions.globalOrigin:
        log.warning("Probably you should use Origin = Global")

    # Decompose
    ttt = time.time() #!TIME
    Scan(context, tDataList, tOptions)
    print("[TIME] Decompose in {:.4f} sec".format(time.time() - ttt) ) #!TIME

    if not settings.outputPath:
        log.error( "Output path is not set" )
        tDataList.clear()

    # Export each decomposed object
    for tData in tDataList:
        log.info("---- Exporting {:s} ----".format(tData.objectName))

        uExportData = UrhoExportData()
        uExportOptions = UrhoExportOptions()
        uExportOptions.splitSubMeshes = settings.geometrySplit

        ttt = time.time() #!TIME
        UrhoExport(tData, uExportOptions, uExportData)
        print("[TIME] Export in {:.4f} sec".format(time.time() - ttt) ) #!TIME
        ttt = time.time() #!TIME

        #PrintUrhoData(uExportData, 0)
        #PrintUrhoData(uExportData, PRINTMASK_COORD | PRINTMASK_NORMAL | PRINTMASK_TANGENT | PRINTMASK_WEIGHT)
        
        modelsPath = settings.outputPath
        if settings.useStandardDirs:
            modelsPath = os.path.join(modelsPath, 'Models')

        if not os.path.isdir(modelsPath):
            log.info( "Creating path {:s}".format(modelsPath) )
            os.makedirs(modelsPath)
            
        for uModel in uExportData.models:
            if uModel.geometries:
                filename = os.path.join(modelsPath, uModel.name + os.path.extsep + "mdl")
                #filename = bpy.path.ensure_ext(filename, ".mdl")
                #filename = bpy.path.clean_name(filename)
                if not os.path.exists(filename) or settings.fileOverwrite:
                    log.info( "Creating file {:s}".format(filename) )
                    UrhoWriteModel(uModel, filename)
                else:
                    log.error( "File already exist {:s}".format(filename) )
            
        for uAnimation in uExportData.animations:
            filename = os.path.join(modelsPath, uAnimation.name + os.path.extsep + "ani")
            if not os.path.exists(filename) or settings.fileOverwrite:
                log.info( "Creating file {:s}".format(filename) )
                UrhoWriteAnimation(uAnimation, filename)
            else:
                log.error( "File already exist {:s}".format(filename) )
    
        if settings.materials:
            materailsPath = settings.outputPath
            if settings.useStandardDirs:
                materailsPath = os.path.join(materailsPath, 'Materials')

            if not os.path.isdir(materailsPath):
                log.info( "Creating path {:s}".format(materailsPath) )
                os.makedirs(materailsPath)

            for tMaterial in tData.materialsList:
                if not tMaterial.name or not tMaterial.imageName:
                    continue
                filename = os.path.join(materailsPath, tMaterial.name + os.path.extsep + "xml")
                if not os.path.exists(filename) or settings.fileOverwrite:
                    log.info( "Creating file {:s}".format(filename) )
                    UrhoWriteMaterial(tMaterial, filename, settings.useStandardDirs)
                else:
                    log.error( "File already exist {:s}".format(filename) )

        if settings.textures:
            texturesPath = settings.outputPath
            if settings.useStandardDirs:
                texturesPath = os.path.join(texturesPath, 'Textures')

            if not os.path.isdir(texturesPath):
                log.info( "Creating path {:s}".format(texturesPath) )
                os.makedirs(texturesPath)

            for tMaterial in tData.materialsList:
                if not tMaterial.name or not tMaterial.image:
                    continue
                filename = os.path.join(texturesPath, tMaterial.imageName)
                
                if '.' not in filename:
                    filename += '.png'
                
                image = tMaterial.image
                if image.packed_file:
                    originalPath = image.filepath
                    image.filepath = filename
                    image.save()
                    # TODO: this gives errors if the path does not exist. 
                    # What to do? set it to None? replace with the new?
                    image.filepath = originalPath  
                    log.info( "Texture unpacked {:s}".format(filename) )
                elif not os.path.exists(tMaterial.imagePath):
                    log.error( "Cannot find texture {:s}".format(tMaterial.imagePath) )
                elif not os.path.exists(filename) or settings.fileOverwrite:
                    try:
                        shutil.copyfile(src = tMaterial.imagePath, dst = filename)
                        log.info( "Texture copied {:s}".format(filename) )
                    except:
                        log.error( "Cannot copy texture in {:s}".format(filename) )
                else:
                    log.error( "File already exist {:s}".format(filename) )
                
        print("[TIME] Write in {:.4f} sec".format(time.time() - ttt) ) #!TIME
        
    log.info("Export ended in {:.4f} sec".format(time.time() - startTime) )
    
    bpy.ops.urho.report('INVOKE_DEFAULT')

    
if __name__ == "__main__":
	register()
