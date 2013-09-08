
#
# This script is licensed as public domain.
# Based on the Ogre Importer from the Urho3D project
#

# http://docs.python.org/2/library/struct.html

from mathutils import Vector, Matrix, Quaternion
import operator
import struct
import os

import logging
log = logging.getLogger("ExportLogger")

'''
Sometimes editor crashes, maybe we have to lock files:
----
from lockfile import FileLock
lock = FileLock("/some/file/or/other")
with lock:
    print lock.path, 'is locked.'
----
lock = FileLock("/some/file/or/other")
while not lock.i_am_locking():
    try:
        lock.acquire(timeout=60)    # wait up to 60 seconds
    except LockTimeout:
        lock.break_lock()
        lock.acquire()
print "I locked", lock.path
lock.release()
----
class A(object):
    def __key(self):
        return (self.attr_a, self.attr_b, self.attr_c)

    def __eq__(x, y):
        return x.__key() == y.__key()

    def __hash__(self):
        return hash(self.__key())

'''

#--------------------
# Urho enums
#--------------------

ELEMENT_POSITION    = 0x0001
ELEMENT_NORMAL      = 0x0002
ELEMENT_COLOR       = 0x0004
ELEMENT_UV1         = 0x0008
ELEMENT_UV2         = 0x0010
ELEMENT_CUBE_UV1    = 0x0020
ELEMENT_CUBE_UV2    = 0x0040
ELEMENT_TANGENT     = 0x0080
ELEMENT_BWEIGHTS    = 0x0100
ELEMENT_BINDICES    = 0x0200

ELEMENT_BLEND       = 0x0300

BONE_BOUNDING_SPHERE = 0x0001
BONE_BOUNDING_BOX    = 0x0002

TRACK_POSITION      = 0x0001
TRACK_ROTATION      = 0x0002
TRACK_SCALE         = 0x0004

TRIANGLE_LIST       = 0
LINE_LIST           = 1
            
# Max number of bones supported by HW skinning
MAX_SKIN_MATRICES   = 64

#--------------------
# Classes
#--------------------

# Bounding box axes aligned
class BoundingBox:
    def __init__(self):
        self.min = None # Vector((0.0, 0.0, 0.0))
        self.max = None # Vector((0.0, 0.0, 0.0))

    def merge(self, point):
        if self.min is None:
            self.min = point.copy()
            self.max = point.copy()
            return
        if point.x < self.min.x:
            self.min.x = point.x
        if point.y < self.min.y:
            self.min.y = point.y
        if point.z < self.min.z:
            self.min.z = point.z
        if point.x > self.max.x:
            self.max.x = point.x
        if point.y > self.max.y:
            self.max.y = point.y
        if point.z > self.max.z:
            self.max.z = point.z

# Exception rasied when we add a vertex with more or less elements than
# the vertex buffer.
class MaskError(Exception):
    pass

# --- Model classes ---
    
class UrhoVertex:
    def __init__(self, tVertex, uVertexBuffer):
        # Note: cannot pass elementMask directly because it is immutable
        mask = 0
        # Only used by morphs, original vertex index in the not morphed vertex buffer
        self.index = None 
        # Vertex position: Vector((0.0, 0.0, 0.0)) of floats
        self.pos = tVertex.pos
        if tVertex.pos:
            mask |= ELEMENT_POSITION
        # Vertex normal: Vector((0.0, 0.0, 0.0)) of floats
        self.normal = tVertex.normal
        if tVertex.normal:
            mask |= ELEMENT_NORMAL
        # Vertex color: (0, 0, 0, 0) of unsigned bytes
        self.color = tVertex.color       
        if tVertex.color:
            mask |= ELEMENT_COLOR
        # Vertex UV texture coordinate: (0.0, 0.0) of floats
        self.uv = tVertex.uv
        if tVertex.uv:
            mask |= ELEMENT_UV1
        # Vertex tangent: Vector((0.0, 0.0, 0.0, 0.0)) of floats
        self.tangent = tVertex.tangent
        if tVertex.tangent:
            mask |= ELEMENT_TANGENT
        # TODO: move it out of here
        # List of 4 tuples: bone index (unsigned byte), blend weight (float)
        self.weights = []
        if not tVertex.weights is None:
            # Sort tuples (index, weight) by decreasing weight
            sortedList = sorted(tVertex.weights, key = operator.itemgetter(1), reverse = True)
            # Sum the first 4 weights
            totalWeight = sum([t[1] for t in sortedList[:4]])
            # Keep only the first 4 tuples, normalize weights, add at least 4 tuples
            for i in range(4):
                t = (0, 0.0)
                if i < len(sortedList):
                    t = sortedList[i]
                    t = (t[0], t[1] / totalWeight)
                self.weights.append(t) 
            mask |= ELEMENT_BLEND

        # Update buffer mask
        if uVertexBuffer.elementMask is None:
            uVertexBuffer.elementMask = mask
        elif uVertexBuffer.elementMask != mask:
            oldMask = uVertexBuffer.elementMask
            uVertexBuffer.elementMask &= mask
            raise MaskError("{:04X} AND {:04X} = {:04X}".format(oldMask, mask, uVertexBuffer.elementMask))
    
    # used by the function index() of lists
    def __eq__(self, other):
        return (self.pos == other.pos and self.normal == other.normal and 
                self.color == other.color and self.uv == other.uv)

    # id of this vertex (not unique)
    def __hash__(self):
        hashValue = 0
        if self.pos:
            hashValue ^= hash(self.pos.x) ^ hash(self.pos.y) ^ hash(self.pos.z)
        if self.normal:
            hashValue ^= hash(self.normal.x) ^ hash(self.normal.y) ^ hash(self.normal.z)
        if self.uv:
            hashValue ^= hash(self.uv.x) ^ hash(self.uv.y)
        return hashValue

    # used by moprh vertex calculations
    def subtract(self, other, mask):
        if mask & ELEMENT_POSITION:
            self.pos -= other.pos
        if mask & ELEMENT_NORMAL:
            self.normal -= other.normal
        if mask & ELEMENT_TANGENT:
            self.tangent -= other.tangent
            
class UrhoVertexBuffer:
    def __init__(self):
        # Flags of the elements contained in every vertex of this buffer
        self.elementMask = None
        # Morph min index and max index in the list vertices TODO: check
        self.morphMinIndex = None
        self.morphMaxIndex = None
        # List of UrhoVertex
        self.vertices = []

class UrhoIndexBuffer:
    def __init__(self):
        # Size of each index: 2 for 16 bits, 4 for 32 bits
        self.indexSize = 0
        # List of triples of indices (in the vertex buffer) to draw triangles
        self.indexes = []
    
class UrhoLodLevel:
    def __init__(self):
        # Distance above which we draw this LOD
        self.distance = 0.0
        # How to draw triangles: TRIANGLE_LIST, LINE_LIST 
        self.primitiveType = 0
        # Index of the vertex buffer used by this LOD in the model list
        self.vertexBuffer = 0
        # Index of the index buffer used by this LOD in the model list
        self.indexBuffer = 0
        # Pointer in the index buffer where starts this LOD
        self.startIndex = 0
        # Length in the index buffer to complete draw this LOD
        self.countIndex = 0

class UrhoGeometry:
    def __init__(self):
        # If the bones in the skeleton are too many for the hardware skinning, we
        # search for only the bones used by this geometry, then create a map from
        # the new bone index to the old bone index (in the skeleton)
        self.boneMap = []
        # List of UrhoLodLevel
        self.lodLevels = []
        # Geometry center based on the position of each triangle of the first LOD
        self.center = Vector((0.0, 0.0, 0.0))
        
class UrhoVertexMorph:
    def __init__(self):
         # Morph name
        self.name = None
        # Maps from 'vertex buffer index' to 'list of vertex', these are only the 
        # vertices modified by the morph, not all the vertices in the buffer (each 
        # morphed vertex has an index to the original vertex)
        self.vertexBufferMap = {}

class UrhoBone:
    def __init__(self):
        # Bone name
        self.name = None
        # Index of the parent bone in the model bones list
        self.parentIndex = None
        # Bone position in parent space
        self.position = None
        # Bone rotation in parent space
        self.rotation = None
        # Bone scale
        self.scale = Vector((1.0, 1.0, 1.0))
        # Bone transformation in skeleton space
        self.matrix = None
        # Inverse of the above
        self.inverseMatrix = None
        # Position in skeleton space
        self.derivedPosition = None
        # Collision sphere and/or box
        self.collisionMask = 0
        self.radius = None
        self.boundingBox = BoundingBox()

class UrhoModel:
    def __init__(self):
        # Model name
        self.name = None
        # List of UrhoVertexBuffer
        self.vertexBuffers = []
        # List of UrhoIndexBuffer
        self.indexBuffers = []
        # List of UrhoGeometry
        self.geometries = []
        # List of UrhoVertexMorph
        self.morphs = []
        # List of UrhoBone
        self.bones = []
        # Bounding box, containd each LOD of each geometry
        self.boundingBox = BoundingBox()
        
# --- Animation classes ---

class UrhoKeyframe:
    def __init__(self, tKeyframe, uTrack):
        # Note: cannot pass mask directly because it is immutable
        mask = 0
        # Time position in seconds: float
        self.time = tKeyframe.time
        # Position: Vector((0.0, 0.0, 0.0))
        self.position = tKeyframe.position
        if tKeyframe.position:
            mask |= TRACK_POSITION
        # Rotation: Quaternion()
        self.rotation = tKeyframe.rotation
        if tKeyframe.rotation:
            mask |= TRACK_ROTATION
        # Scale: Vector((0.0, 0.0, 0.0))
        self.scale = tKeyframe.scale
        if tKeyframe.scale:
            mask |= TRACK_SCALE
        # Update track mask    
        if uTrack.mask is None:
            uTrack.mask = mask
        elif uTrack.mask != mask:
            oldMask = uTrack.elementMask
            uTrack.mask &= mask
            raise MaskError("{:04X} AND {:04X} = {:04X}".format(oldMask, mask, uTrack.elementMask))
            
class UrhoTrack:
    def __init__(self):
        # Track name (practically same as the bone name that should be driven)
        self.name = ""
        # Mask of included animation data
        self.mask = None
        # Keyframes
        self.keyframes = []
        
class UrhoAnimation:
    def __init__(self):
        # Animation name
        self.name = ""
        # Length in seconds: float
        self.length = 0.0
        # Tracks
        self.tracks = []

# --- Export options classes ---

class UrhoExportData:
    def __init__(self):
        # List of UrhoModel
        self.models = []
        # List of UrhoAnimation
        self.animations = []
        
class UrhoExportOptions:
    def __init__(self):
        self.splitSubMeshes = False
                

#--------------------
# Writers
#--------------------

class BinaryFileWriter:

    # Constructor.
    def __init__(self):
        # File stream.
        self.file = None
    
    # Open file stream.
    def open(self, filename):
        self.file = open(filename, "wb")
        return True

    def close(self):
        self.file.close()

    # Writes an ASCII string without terminator
    def writeAsciiStr(self, v):
        self.file.write(bytes(v, "ascii"))

    # Writes a 32 bits unsigned int
    def writeUInt(self, v):
        self.file.write(struct.pack("<I", v))

    # Writes a 16 bits unsigned int
    def writeUShort(self, v):
        self.file.write(struct.pack("<H", v))

    # Writes one 8 bits unsigned byte
    def writeUByte(self, v):
        self.file.write(struct.pack("<B", v))

    # Writes four 32 bits floats .w .x .y .z
    def writeQuaternion(self, v):
        self.file.write(struct.pack("<4f", v.w, v.x, v.y, v.z))

    # Writes three 32 bits floats .x .y .z
    def writeVector(self, v):
        self.file.write(struct.pack("<3f", v.x, v.y, v.z))

    # Writes a 32 bits float
    def writeFloat(self, v):
        self.file.write(struct.pack("<f", v))

        
def UrhoWriteModel(model, filename):

    if not model.vertexBuffers or not model.indexBuffers or not model.geometries:
        log.error("No model data to export in {:s}".format(filename))
        return

    fw = BinaryFileWriter()
    try:
        fw.open(filename)
    except Exception as e:
        log.error("Cannot open file {:s} {:s}".format(filename, e))
        return

    # File Identifier
    fw.writeAsciiStr("UMDL")
    
    # Number of vertex buffers
    fw.writeUInt(len(model.vertexBuffers))
    # For each vertex buffer
    for buffer in model.vertexBuffers:
        # Vertex count
        fw.writeUInt(len(buffer.vertices))
        # Vertex element mask (determines vertex size)
        mask = buffer.elementMask
        fw.writeUInt(mask)
        # Morphable vertex range start index
        fw.writeUInt(buffer.morphMinIndex)
        # Morphable vertex count
        if buffer.morphMaxIndex != 0:
            fw.writeUInt(buffer.morphMaxIndex - buffer.morphMinIndex + 1)
        else:
            fw.writeUInt(0)
        # Vertex data (vertex count * vertex size)
        for vertex in buffer.vertices:
            if mask & ELEMENT_POSITION:
                fw.writeVector(vertex.pos)
            if mask & ELEMENT_NORMAL:
                fw.writeVector(vertex.normal)
            if mask & ELEMENT_COLOR:
                for c in vertex.color:
                    fw.writeUByte(c)
            if mask & ELEMENT_UV1:
                for uv in vertex.uv:
                    fw.writeFloat(uv)
            if mask & ELEMENT_TANGENT:
                fw.writeVector(vertex.tangent)
                fw.writeFloat(vertex.tangent.w)
            if mask & ELEMENT_BWEIGHTS:
                for iw in vertex.weights:
                    fw.writeFloat(iw[1])
            if mask & ELEMENT_BINDICES:
                for iw in vertex.weights:
                    fw.writeUByte(iw[0])

    # Number of index buffers
    fw.writeUInt(len(model.indexBuffers))
    # For each index buffer
    for buffer in model.indexBuffers:
        # Index count
        fw.writeUInt(len(buffer.indexes))
        # Index size (2 for 16-bit indices, 4 for 32-bit indices)
        fw.writeUInt(buffer.indexSize)
        # Index data (index count * index size)
        for i in buffer.indexes:
            if buffer.indexSize == 2:
                fw.writeUShort(i)
            else:
                fw.writeUInt(i)

    # Number of geometries
    fw.writeUInt(len(model.geometries))
    # For each geometry
    for geometry in model.geometries:
        # Number of bone mapping entries
        fw.writeUInt(len(geometry.boneMap))
        # For each bone
        for bone in geometry.boneMap:
            fw.writeUInt(bone)
        # Number of LOD levels
        fw.writeUInt(len(geometry.lodLevels))
        # For each LOD level
        for lod in geometry.lodLevels:
            # LOD distance
            fw.writeFloat(lod.distance)
            # Primitive type (0 = triangle list, 1 = line list)
            fw.writeUInt(lod.primitiveType)
            # Vertex buffer index, starting from 0
            fw.writeUInt(lod.vertexBuffer)
            # Index buffer index, starting from 0
            fw.writeUInt(lod.indexBuffer)
            # Draw range: index start
            fw.writeUInt(lod.startIndex)
            # Draw range: index count
            fw.writeUInt(lod.countIndex)

    # Number of morphs
    fw.writeUInt(len(model.morphs))
    # For each morph
    for morph in model.morphs:
        # Name of morph
        fw.writeAsciiStr(morph.name)
        fw.writeUByte(0)
        # Number of affected vertex buffers
        fw.writeUInt(len(morph.vertexBufferMap))
        # For each affected vertex buffers
        for morphBufferIndex, morphBuffer in sorted(morph.vertexBufferMap.items()):
            # Vertex buffer index, starting from 0
            fw.writeUInt(morphBufferIndex)
            # Vertex element mask for morph data
            mask = morphBuffer.elementMask
            fw.writeUInt(mask)
            # Vertex count
            fw.writeUInt(len(morphBuffer.vertices))
            # For each vertex:
            for vertex in morphBuffer.vertices:
                # Moprh vertex index
                fw.writeUInt(vertex.index)
                # Moprh vertex Position
                if mask & ELEMENT_POSITION:
                    fw.writeVector(vertex.pos)
                # Moprh vertex Normal
                if mask & ELEMENT_NORMAL:
                    fw.writeVector(vertex.normal)
                # Moprh vertex Tangent
                if mask & ELEMENT_TANGENT:
                    fw.writeVector(vertex.tangent)
                    fw.writeFloat(vertex.tangent.w)
                    
    # Number of bones (may be 0)
    fw.writeUInt(len(model.bones))
    # For each bone
    for bone in model.bones:
        # Bone name
        fw.writeAsciiStr(bone.name)
        fw.writeUByte(0)
        # Parent bone index starting from 0
        fw.writeUInt(bone.parentIndex)
        # Initial position
        fw.writeVector(bone.position)
        # Initial rotation
        fw.writeQuaternion(bone.rotation)
        # Initial scale
        fw.writeVector(bone.scale)
        # 4x3 offset matrix for skinning
        for row in bone.inverseMatrix[:3]:
            for v in row:
                fw.writeFloat(v)
        # Bone collision info bitmask
        fw.writeUByte(bone.collisionMask)
        # Bone radius
        if bone.collisionMask & BONE_BOUNDING_SPHERE:
            fw.writeFloat(bone.radius)
        # Bone bounding box minimum and maximum
        if bone.collisionMask & BONE_BOUNDING_BOX:
            fw.writeVector(bone.boundingBox.min)    
            fw.writeVector(bone.boundingBox.max)    
         
    # Model bounding box minimum  
    fw.writeVector(model.boundingBox.min)
    # Model bounding box maximum
    fw.writeVector(model.boundingBox.max)

    # For each geometry
    for geometry in model.geometries:
        # Geometry center
        fw.writeVector(geometry.center)
    
    fw.close()

    
def UrhoWriteAnimation(animation, filename):

    if not animation.tracks:
        log.error("No animation data to export in {:s}".format(filename))
        return

    fw = BinaryFileWriter()
    try:
        fw.open(filename)
    except Exception as e:
        log.error("Cannot open file {:s} {:s}".format(filename, e))
        return

    # File Identifier
    fw.writeAsciiStr("UANI")
    # Animation name
    fw.writeAsciiStr(animation.name)
    fw.writeUByte(0)
    # Length in seconds
    fw.writeFloat(animation.length)
    
    # Number of tracks
    fw.writeUInt(len(animation.tracks))
    # For each track
    for track in animation.tracks:
        # Track name (practically same as the bone name that should be driven)
        fw.writeAsciiStr(track.name)
        fw.writeUByte(0)
        # Mask of included animation data
        mask = track.mask
        fw.writeUByte(track.mask)
        
        # Number of tracks
        fw.writeUInt(len(track.keyframes))
        # For each keyframe
        for keyframe in track.keyframes:
            # Time position in seconds: float
            fw.writeFloat(keyframe.time)
            # Keyframe position
            if mask & TRACK_POSITION:
                fw.writeVector(keyframe.position)
            # Keyframe rotation
            if mask & TRACK_ROTATION:
                fw.writeQuaternion(keyframe.rotation)
            # Keyframe scale
            if mask & TRACK_SCALE:
                fw.writeVector(keyframe.scale)

    fw.close()

def UrhoWriteMaterial(material, filename, useStandardDirs):

    try:
        file = open(filename, "w")
    except Exception as e:
        log.error("Cannot open file {:s} {:s}".format(filename, e))
        return
    
    # TODO
    material.specularColor = Vector((0.0, 0.0, 0.0, 1.0))
    
    imageRelPath = material.imageName
    if useStandardDirs:
        #imageRelPath = os.path.join("Textures", imageRelPath)
        imageRelPath = "Textures/" + imageRelPath
    
    file.write("<material>\n"
               "    <technique name=\"Techniques/Diff.xml\" />\n")
    file.write("    <texture unit=\"diffuse\" name=\"{:s}\" />\n"
               .format(imageRelPath) )
    file.write("    <parameter name=\"MatSpecColor\" value=\"{:.1f} {:.1f} {:.1f} {:.1f}\" />\n"
               .format(material.specularColor[0], material.specularColor[1], material.specularColor[2], material.specularColor[3]) )
    file.write("</material>")

    file.close()

#---------------------------------------

# NOTE: only different geometries use different buffers

# NOTE: LODs must use the same vertex buffer, and so the same vertices. This means
# normals and tangents are a bit off, but they are good infact they are approximations 
# of the first LOD which uses those vertices.
# Creating a LOD we search for the similar vertex.

# NOTE: vertex buffers can have different mask (ex. skeleton weights)

# NOTE: morph must have what geometry they refer to, or the vertex buffer or better
# the index buffer as vertex buffer is in common.
    
# NOTE: a morph can affect more than one vertex buffer

# NOTE: if a vertex buffer has blendweights then all its vertices must have it

# NOTE: if we use index() we must have __EQ__ in the class.
# NOTE: don't use index(), it's slow.

#--------------------
# Urho exporter
#--------------------

def UrhoExport(tData, uExportOptions, uExportData):
    
    uModel = UrhoModel()
    uModel.name = tData.objectName
    uExportData.models.append(uModel)    
    
    # For each bone
    for boneName, bone in tData.bonesMap.items():
        uBoneIndex = len(uModel.bones)
        # Sanity check for the OrderedDict
        assert bone.index == uBoneIndex
        
        uBone = UrhoBone()
        uModel.bones.append(uBone)
        
        uBone.name = boneName
        if bone.parentName:
            # Child bone
            uBone.parentIndex = tData.bonesMap[bone.parentName].index
        else:
            # Root bone
            uBone.parentIndex = uBoneIndex
        uBone.position = bone.bindPosition
        uBone.rotation = bone.bindRotation
        uBone.scale = bone.bindScale
        uBone.matrix = bone.worldTransform
        uBone.inverseMatrix = uBone.matrix.inverted()
        uBone.derivedPosition = uBone.matrix.to_translation()        
    
    totalVertices = len(tData.verticesList) 
    
    # Search in geometries for the maximum number of vertices 
    maxLodVertices = 0
    for tGeometry in tData.geometriesList:
        for tLodLevel in tGeometry.lodLevels:
            vertexCount = len(tLodLevel.indexSet)
            if vertexCount > maxLodVertices:
                maxLodVertices = vertexCount
    
    # If one big buffer needs a 32 bits index but each geometry needs only a 16 bits
    # index then try to use a different buffer for each geometry
    useOneBuffer = True
    if uExportOptions.splitSubMeshes or (totalVertices > 65535 and maxLodVertices <= 65535):
        useOneBuffer = False

    # Urho lod vertex buffer
    vertexBuffer = None
    # Urho lod index buffer
    indexBuffer = None
    # Model bounding box
    minVertexPos = None
    maxVertexPos = None
    # Maps old vertex index to Urho vertex buffer index and Urho vertex index
    modelIndexMap = {}

    # For each geometry
    for tGeometry in tData.geometriesList:
        
        uGeometry = UrhoGeometry()
        uModel.geometries.append(uGeometry)

        # Start value for geometry center (one for each geometry)
        center = Vector((0.0, 0.0, 0.0))
        
        # For each LOD level
        for i, tLodLevel in enumerate(tGeometry.lodLevels):
            uLodLevel = UrhoLodLevel()
            uGeometry.lodLevels.append(uLodLevel)
            
            if i == 0 and tLodLevel.distance != 0.0:
                log.warning("First lod of object {:s} should have 0.0 distance".format(uModel.name))

            uLodLevel.distance = tLodLevel.distance
            uLodLevel.primitiveType = TRIANGLE_LIST

            # If needed add a new vertex buffer (only for first lod of a geometry)
            if vertexBuffer is None or (i == 0 and not useOneBuffer):
                vertexBuffer = UrhoVertexBuffer()
                uModel.vertexBuffers.append(vertexBuffer)
                uVerticesMap = {}

            # If needed add a new index buffer (only for first lod of a geometry)
            if indexBuffer is None or (i == 0 and not useOneBuffer):
                indexBuffer = UrhoIndexBuffer()
                uModel.indexBuffers.append(indexBuffer)
                uLodLevel.startIndex = 0
            else:
                uLodLevel.startIndex = len(indexBuffer.indexes)    

            # Set how many indices the LOD level will use
            uLodLevel.countIndex = len(tLodLevel.triangleList) * 3
            # Set lod vertex and index buffers
            uLodLevel.vertexBuffer = len(uModel.vertexBuffers) - 1
            uLodLevel.indexBuffer = len(uModel.indexBuffers) - 1
            
            # Maps old vertex index to new vertex index in the new Urho buffer
            indexMap = {}
            
            # Add vertices to the vertex buffer
            for tVertexIndex in tLodLevel.indexSet:
            
                tVertex = tData.verticesList[tVertexIndex]

                # Create a Urho vertex
                try:
                    uVertex = UrhoVertex(tVertex, vertexBuffer)
                except MaskError as e:
                    log.warning("Incompatible vertex element mask in object {:s} ({:s})".format(uModel.name, e))
                                
                # All this code do is "uVertexIndex = vertexBuffer.vertices.index(uVertex)", but we use
                # a map to speed up.
            
                # Get an hash of the vertex (more vertices can have the same hash)
                uVertexHash = hash(uVertex)
            
                try:
                    # Get the list of vertices indices with the same hash
                    uVerticesMapList = uVerticesMap[uVertexHash]
                except KeyError:
                    # If the hash is not mapped, create a new list (we should use sets but lists are faster)
                    uVerticesMapList = []
                    uVerticesMap[uVertexHash] = uVerticesMapList
                
                # For each index in the list, get the corresponding vertex and test if it is equal to tVertex.
                # If Position, Normal and UV are the same, it must be the same vertex, get its index.
                uVertexIndex = None
                for ivl in uVerticesMapList:
                    if vertexBuffer.vertices[ivl] == uVertex:
                        uVertexIndex = ivl
                        break

                # If we cannot find it, the vertex is new, add it to the list, and its index to the map list
                if uVertexIndex is None:
                    uVertexIndex = len(vertexBuffer.vertices)
                    vertexBuffer.vertices.append(uVertex)
                    uVerticesMapList.append(uVertexIndex)
                    if i != 0:
                        log.warning("LOD {:d} of object {:s} has new vertices.".format(i, uModel.name))
                
                # Populate the 'old tVertex index' to 'new uVertex index' map
                if not tVertexIndex in indexMap:
                    indexMap[tVertexIndex] = uVertexIndex
                elif indexMap[tVertexIndex] != uVertexIndex:
                    log.error("Conflict in vertex index map of object {:s}".format(uModel.name))
                
                '''    
                # Limit weights count to 4 and normalize them
                if (vertexBuffer.elementMask & ELEMENT_BLEND) == ELEMENT_BLEND:
                    # Sort tuples (index, weight) by decreasing weight
                    sortedList = sorted(uVertex.weights, key = operator.itemgetter(1), reverse = True)
                    # Cleat the vertex weights list and delete the old tuples (maybe)
                    uVertex.weights[:] = []
                    # Sum the first 4 weights
                    totalWeight = sum([t[1] for t in sortedList[:4]])
                    # Keep only the first 4 tuples, map index, normalize weights, add at least 4 tuples
                    for i in range(4):
                        t = (0, 0.0)
                        if i < len(sortedList):
                            t = sortedList[i]
                            t = (t[0], t[1] / totalWeight)
                        uVertex.weights.append(t) 
                '''
                
                # Update the model bounding box (common to all geometries)
                if vertexBuffer.elementMask & ELEMENT_POSITION:
                    uModel.boundingBox.merge(uVertex.pos)

            # Add the local vertex map to the global map
            for oldIndex, newIndex in indexMap.items():
                # We create a map: Map[old index] = Set( Tuple(new buffer index, new vertex index) )
                # Search if this vertex index was already mapped, get its Set or add a new one.
                # We need a Set because a vertex can be copied in more than one vertex buffer.
                try:
                    vbviSet = modelIndexMap[oldIndex]
                except KeyError:
                    vbviSet = set()
                    modelIndexMap[oldIndex] = vbviSet
                # Add a tuple to the Set: new buffer index, new vertex index
                vbvi = (uLodLevel.vertexBuffer, newIndex)
                vbviSet.add(vbvi)
                
            # Add indices to the index buffer
            centerCount = 0
            for triangle in tLodLevel.triangleList:
                for tVertexIndex in triangle:
                    uVertexIndex = indexMap[tVertexIndex]
                    indexBuffer.indexes.append(uVertexIndex)
                    # Update geometry center (only for the first LOD)
                    if (i == 0) and (vertexBuffer.elementMask & ELEMENT_POSITION):
                        centerCount += 1
                        center += vertexBuffer.vertices[uVertexIndex].pos;

            # Update geometry center (only for the first LOD)
            if i == 0 and centerCount:
                uGeometry.center = center / centerCount;
                        
            # If this geometry has bone weights but the number of total bones is over the limit 
            # then let's hope our geometry uses only a subset of the total bones within the limit.
            # If this is true then we can remap the original bone index, which can be over the 
            # limit, to a local, in this geometry, bone index within the limit.
            if (len(uModel.bones) > MAX_SKIN_MATRICES and 
               (vertexBuffer.elementMask & ELEMENT_BLEND) == ELEMENT_BLEND):
                # For each vertex in the buffer
                for vertex in vertexBuffer.vertices:
                    for i, (boneIndex, weight) in enumerate(vertex.weights):
                        # Search if the bone is already present in the map
                        try:
                            newBoneIndex = uGeometry.boneMap.index(boneIndex)
                        except ValueError:
                            # New bone, add it in the map
                            newBoneIndex = len(uGeometry.boneMap)
                            if newBoneIndex < MAX_SKIN_MATRICES:
                                uGeometry.boneMap.append(boneIndex)
                            else:
                                log.error("Too many bones in object {:s} geometry {:d}.".format(uModel.name, i))
                                newBoneIndex = 0
                                weight = 0.0
                        # Change from the global bone index to the local bone index
                        vertex.weights[i] = (newBoneIndex, weight)

    if tData.geometriesList and uModel.boundingBox.min is None:
        uModel.boundingBox.min = Vector((0.0, 0.0, 0.0))
        uModel.boundingBox.max = Vector((0.0, 0.0, 0.0))
        log.warning("Vertices of object {:s} have no position.".format(uModel.name))

    # Set index size for indexes buffers
    for uIndexBuffer in uModel.indexBuffers:
        if len(uIndexBuffer.indexes) > 65535:
            # 32 bits indexes
            uIndexBuffer.indexSize = 4
        else:
            # 16 bits indexes
            uIndexBuffer.indexSize = 2

    # Update bones bounding sphere and box
    # For each vertex buffer
    for uVertexBuffer in uModel.vertexBuffers:
        # Skip if the buffer doesn't have bone weights
        if (uVertexBuffer.elementMask & ELEMENT_BLEND) != ELEMENT_BLEND:
            continue
        # For each vertex in the buffer
        for uVertex in uVertexBuffer.vertices:
            vertexPos = uVertex.pos
            for boneIndex, weight in uVertex.weights:
                # The 0.33 threshold check is to avoid including vertices in the bone hitbox 
                # to which the bone contributes only a little. It is rather arbitrary. (Lasse)
                if weight > 0.33:
                    uBone = uModel.bones[boneIndex]
                    # Bone head position (in model space)
                    bonePos = uBone.derivedPosition
                    # Distance between vertex and bone head
                    distance = (bonePos - vertexPos).length
                    # Search for the maximum distance
                    if uBone.radius is None or distance > uBone.radius:
                        uBone.collisionMask |= BONE_BOUNDING_SPHERE
                        uBone.radius = distance
                    # Calculate the vertex position in bone space
                    boneVertexPos = uBone.inverseMatrix * vertexPos
                    # Update the bone boundingBox
                    uBone.collisionMask |= BONE_BOUNDING_BOX
                    uBone.boundingBox.merge(boneVertexPos)

    
    for tMorph in tData.morphsList:
        uMorph = UrhoVertexMorph()
        uMorph.name = tMorph.name
        uModel.morphs.append(uMorph)
        
        # For each vertex affected by the morph
        for tVertexIndex, tMorphVertex in tMorph.vertexMap.items():
            # Get the correspondent Urho vertex buffer and vertex index (there can be more than one)
            vbviSet = modelIndexMap[tVertexIndex]
            # For each corresponding vertex buffer
            for uVertexBufferIndex, uVertexIndex in vbviSet:
                # Search for the vertex buffer in the morph, if not present add it
                try:
                    uMorphVertexBuffer = uMorph.vertexBufferMap[uVertexBufferIndex]
                except KeyError:
                    uMorphVertexBuffer = UrhoVertexBuffer()
                    uMorph.vertexBufferMap[uVertexBufferIndex] = uMorphVertexBuffer
                
                # Create the morphed vertex
                try:
                    uMorphVertex = UrhoVertex(tMorphVertex, uMorphVertexBuffer)
                except MaskError as e:
                    log.warning("Incompatible vertex element mask in morph {:s} of object {:s} ({:s})".format(uMorph.name, uModel.name, e))

                # Get the original vertex
                uVertexBuffer = uModel.vertexBuffers[uVertexBufferIndex]
                uVertex = uVertexBuffer.vertices[uVertexIndex]
                
                # Calculate morph values (pos, normal, tangent) relative to the original vertex
                uMorphVertex.subtract(uVertex, uMorphVertexBuffer.elementMask)
                    
                # Add the vertex to the morph buffer
                uMorphVertex.index = uVertexIndex
                uMorphVertexBuffer.vertices.append(uMorphVertex)

                # Update min and max morphed vertex index in the vertex buffer
                if uVertexBuffer.morphMinIndex is None:
                    uVertexBuffer.morphMinIndex = uVertexIndex
                    uVertexBuffer.morphMaxIndex = uVertexIndex
                elif uVertexIndex < uVertexBuffer.morphMinIndex:
                    uVertexBuffer.morphMinIndex = uVertexIndex
                elif uVertexIndex > uVertexBuffer.morphMaxIndex:
                    uVertexBuffer.morphMaxIndex = uVertexIndex

    # Set to zero min and max morphed vertex index of buffers with no morphs
    for i, uVertexBuffer in enumerate(uModel.vertexBuffers):
        if uVertexBuffer.morphMinIndex is None:
            uVertexBuffer.morphMinIndex = 0
            uVertexBuffer.morphMaxIndex = 0

            
    uAnimations = uExportData.animations
    for tAnimation in tData.animationsList:
        uAnimation = UrhoAnimation()
        uAnimation.name = tAnimation.name
        uAnimation.length = None
        
        for tTrack in tAnimation.tracks:
            uTrack = UrhoTrack()
            uTrack.name = tTrack.name
            uTrack.mask = None
            
            for tFrame in tTrack.frames:
                try:
                    uKeyframe = UrhoKeyframe(tFrame, uTrack)
                except MaskError as e:
                    log.warning("Incompatible element mask in track {:s} of animation {:s} ({:s})".format(uTrack.name, uAnimation.name, e))
                uTrack.keyframes.append(uKeyframe)

            # Make sure keyframes are sorted from beginning to end
            uTrack.keyframes.sort(key = operator.attrgetter('time'))

            # Add only tracks with keyframes
            if uTrack.keyframes and uTrack.mask:
                uAnimation.tracks.append(uTrack)
                # Update animation length
                length = uTrack.keyframes[-1].time
                if uAnimation.length is None or uAnimation.length < length:
                    uAnimation.length = length
        
        # Add only animations with tracks
        if uAnimation.tracks:
            uAnimations.append(uAnimation)
    
                