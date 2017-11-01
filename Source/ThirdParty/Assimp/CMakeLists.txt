# Open Asset Import Library (assimp)
# ----------------------------------------------------------------------
#
# Copyright (c) 2006-2017, assimp team

# All rights reserved.
#
# Redistribution and use of this software in source and binary forms,
# with or without modification, are permitted provided that the
# following conditions are met:
#
# * Redistributions of source code must retain the above
#   copyright notice, this list of conditions and the
#   following disclaimer.
#
# * Redistributions in binary form must reproduce the above
#   copyright notice, this list of conditions and the
#   following disclaimer in the documentation and/or other
#   materials provided with the distribution.
#
# * Neither the name of the assimp team, nor the names of its
#   contributors may be used to endorse or promote products
#   derived from this software without specific prior
#   written permission of the assimp team.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#----------------------------------------------------------------------

#
# Listing and grouping of all the source files.
# 1) Set the file lists for each component
# 2) Create a Source Group for each component, for IDE project orginization
# 3) Add libassimp using the file lists (eliminates duplication of file names between
#    source groups and library command)
#

# Modified by Lasse Oorni and Yao Wei Tjong for Urho3D

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

INCLUDE_DIRECTORIES( . code include contrib contrib/unzip contrib/rapidjson/include contrib/irrXML )

SET( HEADER_PATH include/assimp )

SET( COMPILER_HEADERS
  ${HEADER_PATH}/Compiler/pushpack1.h
  ${HEADER_PATH}/Compiler/poppack1.h
  ${HEADER_PATH}/Compiler/pstdint.h
)
SOURCE_GROUP( Compiler FILES ${COMPILER_HEADERS})

SET( PUBLIC_HEADERS
  ${HEADER_PATH}/anim.h
  ${HEADER_PATH}/ai_assert.h
  ${HEADER_PATH}/camera.h
  ${HEADER_PATH}/color4.h
  ${HEADER_PATH}/color4.inl
  ${HEADER_PATH}/config.h
  ${HEADER_PATH}/defs.h
  ${HEADER_PATH}/cfileio.h
  ${HEADER_PATH}/light.h
  ${HEADER_PATH}/material.h
  ${HEADER_PATH}/material.inl
  ${HEADER_PATH}/matrix3x3.h
  ${HEADER_PATH}/matrix3x3.inl
  ${HEADER_PATH}/matrix4x4.h
  ${HEADER_PATH}/matrix4x4.inl
  ${HEADER_PATH}/mesh.h
  ${HEADER_PATH}/postprocess.h
  ${HEADER_PATH}/quaternion.h
  ${HEADER_PATH}/quaternion.inl
  ${HEADER_PATH}/scene.h
  ${HEADER_PATH}/metadata.h
  ${HEADER_PATH}/texture.h
  ${HEADER_PATH}/types.h
  ${HEADER_PATH}/vector2.h
  ${HEADER_PATH}/vector2.inl
  ${HEADER_PATH}/vector3.h
  ${HEADER_PATH}/vector3.inl
  ${HEADER_PATH}/version.h
  ${HEADER_PATH}/cimport.h
  ${HEADER_PATH}/importerdesc.h
  ${HEADER_PATH}/Importer.hpp
  ${HEADER_PATH}/DefaultLogger.hpp
  ${HEADER_PATH}/ProgressHandler.hpp
  ${HEADER_PATH}/IOStream.hpp
  ${HEADER_PATH}/IOSystem.hpp
  ${HEADER_PATH}/Logger.hpp
  ${HEADER_PATH}/LogStream.hpp
  ${HEADER_PATH}/NullLogger.hpp
  ${HEADER_PATH}/cexport.h
  ${HEADER_PATH}/Exporter.hpp
  ${HEADER_PATH}/DefaultIOStream.h
  ${HEADER_PATH}/DefaultIOSystem.h
  ${HEADER_PATH}/SceneCombiner.h
)

SET( Core_SRCS
  code/Assimp.cpp
)

SET( Logging_SRCS
  ${HEADER_PATH}/DefaultLogger.hpp
  ${HEADER_PATH}/LogStream.hpp
  ${HEADER_PATH}/Logger.hpp
  ${HEADER_PATH}/NullLogger.hpp
  code/Win32DebugLogStream.h
  code/DefaultLogger.cpp
  code/FileLogStream.h
  code/StdOStreamLogStream.h
)
SOURCE_GROUP(Logging FILES ${Logging_SRCS})

SET( Common_SRCS
  code/fast_atof.h
  code/qnan.h
  code/BaseImporter.cpp
  code/BaseImporter.h
  code/BaseProcess.cpp
  code/BaseProcess.h
  code/Importer.h
  code/ScenePrivate.h
  code/PostStepRegistry.cpp
  code/ImporterRegistry.cpp
  code/ByteSwapper.h
  code/DefaultProgressHandler.h
  code/DefaultIOStream.cpp
  code/DefaultIOSystem.cpp
  code/CInterfaceIOWrapper.cpp
  code/CInterfaceIOWrapper.h
  code/Hash.h
  code/Importer.cpp
  code/IFF.h
  code/MemoryIOWrapper.h
  code/ParsingUtils.h
  code/StreamReader.h
  code/StreamWriter.h
  code/StringComparison.h
  code/StringUtils.h
  code/SGSpatialSort.cpp
  code/SGSpatialSort.h
  code/VertexTriangleAdjacency.cpp
  code/VertexTriangleAdjacency.h
  code/GenericProperty.h
  code/SpatialSort.cpp
  code/SpatialSort.h
  code/SceneCombiner.cpp
  code/ScenePreprocessor.cpp
  code/ScenePreprocessor.h
  code/SkeletonMeshBuilder.cpp
  code/SkeletonMeshBuilder.h
  code/SplitByBoneCountProcess.cpp
  code/SplitByBoneCountProcess.h
  code/SmoothingGroups.h
  code/StandardShapes.cpp
  code/StandardShapes.h
  code/TargetAnimation.cpp
  code/TargetAnimation.h
  code/RemoveComments.cpp
  code/RemoveComments.h
  code/Subdivision.cpp
  code/Subdivision.h
  code/scene.cpp
  code/Vertex.h
  code/LineSplitter.h
  code/TinyFormatter.h
  code/Profiler.h
  code/LogAux.h
  code/Bitmap.cpp
  code/Bitmap.h
  code/XMLTools.h
  code/Version.cpp
  code/IOStreamBuffer.h
  code/CreateAnimMesh.h
  code/CreateAnimMesh.cpp
)
SOURCE_GROUP(Common FILES ${Common_SRCS})

IF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )
  SET( C4D_SRCS
    code/C4DImporter.cpp
    code/C4DImporter.h
  )
  SOURCE_GROUP( C4D FILES ${C4D_SRCS})
ENDIF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )

# if this variable is set to TRUE, the user can manually disable importers by setting
# ASSIMP_BUILD_XXX_IMPORTER to FALSE for each importer
# if this variable is set to FALSE, the user can manually enable importers by setting
# ASSIMP_BUILD_XXX_IMPORTER to TRUE for each importer
OPTION(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT "default value of all ASSIMP_BUILD_XXX_IMPORTER value" TRUE)

# macro to add the CMake Option ADD_ASSIMP_IMPORTER_<name> which enables compile of loader
# this way selective loaders can be compiled (reduces filesize + compile time)
MACRO(ADD_ASSIMP_IMPORTER name)
  OPTION(ASSIMP_BUILD_${name}_IMPORTER "build the ${name} importer" ${ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT})
  IF(ASSIMP_BUILD_${name}_IMPORTER)
    LIST(APPEND ASSIMP_LOADER_SRCS ${ARGN})
    SET(ASSIMP_IMPORTERS_ENABLED "${ASSIMP_IMPORTERS_ENABLED} ${name}")
    SET(${name}_SRCS ${ARGN})
    SOURCE_GROUP(${name} FILES ${ARGN})
  ELSE()
    SET(${name}_SRC "")
    SET(ASSIMP_IMPORTERS_DISABLED "${ASSIMP_IMPORTERS_DISABLED} ${name}")
    add_definitions(-DASSIMP_BUILD_NO_${name}_IMPORTER)
    add_definitions(-DASSIMP_BUILD_NO_${name}_EXPORTER)
  ENDIF()
ENDMACRO()

SET(ASSIMP_LOADER_SRCS "")
SET(ASSIMP_IMPORTERS_ENABLED "") # list of enabled importers
SET(ASSIMP_IMPORTERS_DISABLED "") # disabled list (used to print)

ADD_ASSIMP_IMPORTER( AMF
  code/AMFImporter.hpp
  code/AMFImporter_Macro.hpp
  code/AMFImporter_Node.hpp
  code/AMFImporter.cpp
  code/AMFImporter_Geometry.cpp
  code/AMFImporter_Material.cpp
  code/AMFImporter_Postprocess.cpp
)

ADD_ASSIMP_IMPORTER( 3DS
  code/3DSConverter.cpp
  code/3DSHelper.h
  code/3DSLoader.cpp
  code/3DSLoader.h
  code/3DSExporter.h
  code/3DSExporter.cpp
)

ADD_ASSIMP_IMPORTER( AC
  code/ACLoader.cpp
  code/ACLoader.h
)

ADD_ASSIMP_IMPORTER( ASE
  code/ASELoader.cpp
  code/ASELoader.h
  code/ASEParser.cpp
  code/ASEParser.h
)

ADD_ASSIMP_IMPORTER( ASSBIN
  code/AssbinExporter.h
  code/AssbinExporter.cpp
  code/AssbinLoader.h
  code/AssbinLoader.cpp
)

ADD_ASSIMP_IMPORTER( ASSXML
  code/AssxmlExporter.h
  code/AssxmlExporter.cpp
)

ADD_ASSIMP_IMPORTER( B3D
  code/B3DImporter.cpp
  code/B3DImporter.h
)

ADD_ASSIMP_IMPORTER( BVH
  code/BVHLoader.cpp
  code/BVHLoader.h
)

ADD_ASSIMP_IMPORTER( COLLADA
  code/ColladaHelper.h
  code/ColladaLoader.cpp
  code/ColladaLoader.h
  code/ColladaParser.cpp
  code/ColladaParser.h
  code/ColladaExporter.h
  code/ColladaExporter.cpp
)

ADD_ASSIMP_IMPORTER( DXF
  code/DXFLoader.cpp
  code/DXFLoader.h
  code/DXFHelper.h
)

ADD_ASSIMP_IMPORTER( CSM
  code/CSMLoader.cpp
  code/CSMLoader.h
)

ADD_ASSIMP_IMPORTER( HMP
  code/HMPFileData.h
  code/HMPLoader.cpp
  code/HMPLoader.h
  code/HalfLifeFileData.h
)

ADD_ASSIMP_IMPORTER( IRRMESH
  code/IRRMeshLoader.cpp
  code/IRRMeshLoader.h
  code/IRRShared.cpp
  code/IRRShared.h
)

ADD_ASSIMP_IMPORTER( IRR
  code/IRRLoader.cpp
  code/IRRLoader.h
  code/IRRShared.cpp
  code/IRRShared.h
)

ADD_ASSIMP_IMPORTER( LWO
  code/LWOAnimation.cpp
  code/LWOAnimation.h
  code/LWOBLoader.cpp
  code/LWOFileData.h
  code/LWOLoader.cpp
  code/LWOLoader.h
  code/LWOMaterial.cpp
)

ADD_ASSIMP_IMPORTER( LWS
  code/LWSLoader.cpp
  code/LWSLoader.h
)

ADD_ASSIMP_IMPORTER( MD2
  code/MD2FileData.h
  code/MD2Loader.cpp
  code/MD2Loader.h
  code/MD2NormalTable.h
)

ADD_ASSIMP_IMPORTER( MD3
  code/MD3FileData.h
  code/MD3Loader.cpp
  code/MD3Loader.h
)

ADD_ASSIMP_IMPORTER( MD5
  code/MD5Loader.cpp
  code/MD5Loader.h
  code/MD5Parser.cpp
  code/MD5Parser.h
)

ADD_ASSIMP_IMPORTER( MDC
  code/MDCFileData.h
  code/MDCLoader.cpp
  code/MDCLoader.h
  code/MDCNormalTable.h
)

ADD_ASSIMP_IMPORTER( MDL
  code/MDLDefaultColorMap.h
  code/MDLFileData.h
  code/MDLLoader.cpp
  code/MDLLoader.h
  code/MDLMaterialLoader.cpp
)

SET( MaterialSystem_SRCS
  code/MaterialSystem.cpp
  code/MaterialSystem.h
)
SOURCE_GROUP( MaterialSystem FILES ${MaterialSystem_SRCS})

ADD_ASSIMP_IMPORTER( NFF
  code/NFFLoader.cpp
  code/NFFLoader.h
)

ADD_ASSIMP_IMPORTER( NDO
  code/NDOLoader.cpp
  code/NDOLoader.h
)

ADD_ASSIMP_IMPORTER( OFF
  code/OFFLoader.cpp
  code/OFFLoader.h
)

ADD_ASSIMP_IMPORTER( OBJ
  code/ObjFileData.h
  code/ObjFileImporter.cpp
  code/ObjFileImporter.h
  code/ObjFileMtlImporter.cpp
  code/ObjFileMtlImporter.h
  code/ObjFileParser.cpp
  code/ObjFileParser.h
  code/ObjTools.h
  code/ObjExporter.h
  code/ObjExporter.cpp
)

ADD_ASSIMP_IMPORTER( OGRE
  code/OgreImporter.h
  code/OgreStructs.h
  code/OgreParsingUtils.h
  code/OgreBinarySerializer.h
  code/OgreXmlSerializer.h
  code/OgreImporter.cpp
  code/OgreStructs.cpp
  code/OgreBinarySerializer.cpp
  code/OgreXmlSerializer.cpp
  code/OgreMaterial.cpp
)

ADD_ASSIMP_IMPORTER( OPENGEX
  code/OpenGEXExporter.cpp
  code/OpenGEXExporter.h
  code/OpenGEXImporter.cpp
  code/OpenGEXImporter.h
  code/OpenGEXStructs.h
)

ADD_ASSIMP_IMPORTER( PLY
  code/PlyLoader.cpp
  code/PlyLoader.h
  code/PlyParser.cpp
  code/PlyParser.h
  code/PlyExporter.cpp
  code/PlyExporter.h
)

ADD_ASSIMP_IMPORTER( MS3D
  code/MS3DLoader.cpp
  code/MS3DLoader.h
)

ADD_ASSIMP_IMPORTER( COB
  code/COBLoader.cpp
  code/COBLoader.h
  code/COBScene.h
)

ADD_ASSIMP_IMPORTER( BLEND
  code/BlenderLoader.cpp
  code/BlenderLoader.h
  code/BlenderDNA.cpp
  code/BlenderDNA.h
  code/BlenderDNA.inl
  code/BlenderScene.cpp
  code/BlenderScene.h
  code/BlenderSceneGen.h
  code/BlenderIntermediate.h
  code/BlenderModifier.h
  code/BlenderModifier.cpp
  code/BlenderBMesh.h
  code/BlenderBMesh.cpp
  code/BlenderTessellator.h
  code/BlenderTessellator.cpp
)

ADD_ASSIMP_IMPORTER( IFC
  code/IFCLoader.cpp
  code/IFCLoader.h
  code/IFCReaderGen1.cpp
  code/IFCReaderGen2.cpp
  code/IFCReaderGen.h
  code/IFCUtil.h
  code/IFCUtil.cpp
  code/IFCGeometry.cpp
  code/IFCMaterial.cpp
  code/IFCProfile.cpp
  code/IFCCurve.cpp
  code/IFCBoolean.cpp
  code/IFCOpenings.cpp
  code/STEPFile.h
  code/STEPFileReader.h
  code/STEPFileReader.cpp
  code/STEPFileEncoding.cpp
  code/STEPFileEncoding.h
)
if (ASSIMP_BUILD_IFC_IMPORTER)
  if (MSVC)
    set_source_files_properties(code/IFCReaderGen1.cpp code/IFCReaderGen2.cpp PROPERTIES COMPILE_FLAGS "/bigobj")
  elseif(CMAKE_COMPILER_IS_MINGW)
    set_source_files_properties(code/IFCReaderGen1.cpp code/IFCReaderGen2.cpp PROPERTIES COMPILE_FLAGS "-O2")   # Urho3D: Remove -Wa,-mbig-obj flag as some older MinGW version may not support it yet
  endif()
endif (ASSIMP_BUILD_IFC_IMPORTER)

ADD_ASSIMP_IMPORTER( XGL
  code/XGLLoader.cpp
  code/XGLLoader.h
)


ADD_ASSIMP_IMPORTER( FBX
  code/FBXImporter.cpp
  code/FBXCompileConfig.h
  code/FBXImporter.h
  code/FBXParser.cpp
  code/FBXParser.h
  code/FBXTokenizer.cpp
  code/FBXTokenizer.h
  code/FBXImportSettings.h
  code/FBXConverter.h
  code/FBXConverter.cpp
  code/FBXUtil.h
  code/FBXUtil.cpp
  code/FBXDocument.h
  code/FBXDocument.cpp
  code/FBXProperties.h
  code/FBXProperties.cpp
  code/FBXMeshGeometry.h
  code/FBXMeshGeometry.cpp
  code/FBXMaterial.cpp
  code/FBXModel.cpp
  code/FBXAnimation.cpp
  code/FBXNodeAttribute.cpp
  code/FBXDeformer.cpp
  code/FBXBinaryTokenizer.cpp
  code/FBXDocumentUtil.cpp
)

SET( PostProcessing_SRCS
  code/CalcTangentsProcess.cpp
  code/CalcTangentsProcess.h
  code/ComputeUVMappingProcess.cpp
  code/ComputeUVMappingProcess.h
  code/ConvertToLHProcess.cpp
  code/ConvertToLHProcess.h
  code/FindDegenerates.cpp
  code/FindDegenerates.h
  code/FindInstancesProcess.cpp
  code/FindInstancesProcess.h
  code/FindInvalidDataProcess.cpp
  code/FindInvalidDataProcess.h
  code/FixNormalsStep.cpp
  code/FixNormalsStep.h
  code/GenFaceNormalsProcess.cpp
  code/GenFaceNormalsProcess.h
  code/GenVertexNormalsProcess.cpp
  code/GenVertexNormalsProcess.h
  code/PretransformVertices.cpp
  code/PretransformVertices.h
  code/ImproveCacheLocality.cpp
  code/ImproveCacheLocality.h
  code/JoinVerticesProcess.cpp
  code/JoinVerticesProcess.h
  code/LimitBoneWeightsProcess.cpp
  code/LimitBoneWeightsProcess.h
  code/RemoveRedundantMaterials.cpp
  code/RemoveRedundantMaterials.h
  code/RemoveVCProcess.cpp
  code/RemoveVCProcess.h
  code/SortByPTypeProcess.cpp
  code/SortByPTypeProcess.h
  code/SplitLargeMeshes.cpp
  code/SplitLargeMeshes.h
  code/TextureTransform.cpp
  code/TextureTransform.h
  code/TriangulateProcess.cpp
  code/TriangulateProcess.h
  code/ValidateDataStructure.cpp
  code/ValidateDataStructure.h
  code/OptimizeGraph.cpp
  code/OptimizeGraph.h
  code/OptimizeMeshes.cpp
  code/OptimizeMeshes.h
  code/DeboneProcess.cpp
  code/DeboneProcess.h
  code/ProcessHelper.h
  code/ProcessHelper.cpp
  code/PolyTools.h
  code/MakeVerboseFormat.cpp
  code/MakeVerboseFormat.h
)
SOURCE_GROUP( PostProcessing FILES ${PostProcessing_SRCS})

SET( IrrXML_SRCS code/irrXMLWrapper.h )
SOURCE_GROUP( IrrXML FILES ${IrrXML_SRCS})

ADD_ASSIMP_IMPORTER( Q3D
  code/Q3DLoader.cpp
  code/Q3DLoader.h
)

ADD_ASSIMP_IMPORTER( Q3BSP
  code/Q3BSPFileData.h
  code/Q3BSPFileParser.h
  code/Q3BSPFileParser.cpp
  code/Q3BSPFileImporter.h
  code/Q3BSPFileImporter.cpp
  code/Q3BSPZipArchive.h
  code/Q3BSPZipArchive.cpp
)

ADD_ASSIMP_IMPORTER( RAW
  code/RawLoader.cpp
  code/RawLoader.h
)

ADD_ASSIMP_IMPORTER( SIB
  code/SIBImporter.cpp
  code/SIBImporter.h
)

ADD_ASSIMP_IMPORTER( SMD
  code/SMDLoader.cpp
  code/SMDLoader.h
)

ADD_ASSIMP_IMPORTER( STL
  code/STLLoader.cpp
  code/STLLoader.h
  code/STLExporter.h
  code/STLExporter.cpp
)

ADD_ASSIMP_IMPORTER( TERRAGEN
  code/TerragenLoader.cpp
  code/TerragenLoader.h
)

ADD_ASSIMP_IMPORTER( 3D
  code/UnrealLoader.cpp
  code/UnrealLoader.h
)

ADD_ASSIMP_IMPORTER( X
  code/XFileHelper.h
  code/XFileImporter.cpp
  code/XFileImporter.h
  code/XFileParser.cpp
  code/XFileParser.h
  code/XFileExporter.h
  code/XFileExporter.cpp
)

ADD_ASSIMP_IMPORTER(X3D
  code/X3DExporter.cpp
  code/X3DExporter.hpp
  code/X3DImporter.cpp
  code/X3DImporter.hpp
  code/X3DImporter_Geometry2D.cpp
  code/X3DImporter_Geometry3D.cpp
  code/X3DImporter_Group.cpp
  code/X3DImporter_Light.cpp
  code/X3DImporter_Macro.hpp
  code/X3DImporter_Metadata.cpp
  code/X3DImporter_Networking.cpp
  code/X3DImporter_Node.hpp
  code/X3DImporter_Postprocess.cpp
  code/X3DImporter_Rendering.cpp
  code/X3DImporter_Shape.cpp
  code/X3DImporter_Texturing.cpp
  code/FIReader.hpp
  code/FIReader.cpp
  code/X3DVocabulary.cpp
)

ADD_ASSIMP_IMPORTER( GLTF
  code/glTFAsset.h
  code/glTFAsset.inl
  code/glTFAssetWriter.h
  code/glTFAssetWriter.inl
  code/glTFImporter.cpp
  code/glTFImporter.h
  code/glTFExporter.h
  code/glTFExporter.cpp
)

ADD_ASSIMP_IMPORTER( 3MF
    code/D3MFImporter.h
    code/D3MFImporter.cpp
    code/D3MFOpcPackage.h
    code/D3MFOpcPackage.cpp
)

ADD_ASSIMP_IMPORTER( MMD
  code/MMDCpp14.h
  code/MMDImporter.cpp
  code/MMDImporter.h
  code/MMDPmdParser.h
  code/MMDPmxParser.h
  code/MMDPmxParser.cpp
  code/MMDVmdParser.h
)

SET( Step_SRCS
  code/StepExporter.h
  code/StepExporter.cpp
)
SOURCE_GROUP( Step FILES ${Step_SRCS})

SET( Exporter_SRCS
  code/Exporter.cpp
  code/AssimpCExport.cpp
  code/BlobIOSystem.h
)
SOURCE_GROUP( Exporter FILES ${Exporter_SRCS})

SET( Extra_SRCS
  code/MD4FileData.h
)
SOURCE_GROUP( Extra FILES ${Extra_SRCS})

SET( IrrXML_SRCS
  code/irrXMLWrapper.h
  contrib/irrXML/CXMLReaderImpl.h
  contrib/irrXML/heapsort.h
  contrib/irrXML/irrArray.h
  contrib/irrXML/irrString.h
  contrib/irrXML/irrTypes.h
  contrib/irrXML/irrXML.cpp
  contrib/irrXML/irrXML.h
)
SOURCE_GROUP( IrrXML FILES ${IrrXML_SRCS})

SET( Clipper_SRCS
  contrib/clipper/clipper.hpp
  contrib/clipper/clipper.cpp
)
SOURCE_GROUP( Clipper FILES ${Clipper_SRCS})

SET( Poly2Tri_SRCS
  contrib/poly2tri/poly2tri/common/shapes.cc
  contrib/poly2tri/poly2tri/common/shapes.h
  contrib/poly2tri/poly2tri/common/utils.h
  contrib/poly2tri/poly2tri/sweep/advancing_front.h
  contrib/poly2tri/poly2tri/sweep/advancing_front.cc
  contrib/poly2tri/poly2tri/sweep/cdt.cc
  contrib/poly2tri/poly2tri/sweep/cdt.h
  contrib/poly2tri/poly2tri/sweep/sweep.cc
  contrib/poly2tri/poly2tri/sweep/sweep.h
  contrib/poly2tri/poly2tri/sweep/sweep_context.cc
  contrib/poly2tri/poly2tri/sweep/sweep_context.h
)
SOURCE_GROUP( Poly2Tri FILES ${Poly2Tri_SRCS})

SET( unzip_SRCS
  contrib/unzip/crypt.h
  contrib/unzip/ioapi.c
  contrib/unzip/ioapi.h
  contrib/unzip/unzip.c
  contrib/unzip/unzip.h
)
SOURCE_GROUP( unzip FILES ${unzip_SRCS})

SET( zlib_SRCS
  contrib/zlib/adler32.c
  contrib/zlib/compress.c
  contrib/zlib/crc32.c
  contrib/zlib/crc32.h
  contrib/zlib/deflate.c
  contrib/zlib/deflate.h
#  contrib/zlib/gzclose.c
#  contrib/zlib/gzguts.h
#  contrib/zlib/gzlib.c
#  contrib/zlib/gzread.c
#  contrib/zlib/gzwrite.c
  contrib/zlib/infback.c
  contrib/zlib/inffast.c
  contrib/zlib/inffast.h
  contrib/zlib/inffixed.h
  contrib/zlib/inflate.c
  contrib/zlib/inflate.h
  contrib/zlib/inftrees.c
  contrib/zlib/inftrees.h
  contrib/zlib/trees.c
  contrib/zlib/trees.h
  contrib/zlib/uncompr.c
  contrib/zlib/zconf.h
  contrib/zlib/zlib.h
  contrib/zlib/zutil.c
  contrib/zlib/zutil.h
)
SOURCE_GROUP( zlib FILES ${zlib_SRCS})

SET ( openddl_parser_SRCS
  contrib/openddlparser/code/OpenDDLExport.cpp 
  contrib/openddlparser/code/OpenDDLCommon.cpp
  contrib/openddlparser/code/OpenDDLParser.cpp
  contrib/openddlparser/code/DDLNode.cpp
  contrib/openddlparser/code/Value.cpp
  contrib/openddlparser/code/OpenDDLStream.cpp
  contrib/openddlparser/include/openddlparser/OpenDDLParser.h
  contrib/openddlparser/include/openddlparser/OpenDDLParserUtils.h
  contrib/openddlparser/include/openddlparser/OpenDDLCommon.h
  contrib/openddlparser/include/openddlparser/OpenDDLExport.h
  contrib/openddlparser/include/openddlparser/OpenDDLStream.h
  contrib/openddlparser/include/openddlparser/DDLNode.h
  contrib/openddlparser/include/openddlparser/Value.h
)
SOURCE_GROUP( openddl_parser FILES ${openddl_parser_SRCS})

SET ( open3dgc_SRCS
  contrib/Open3DGC/o3dgcAdjacencyInfo.h
  contrib/Open3DGC/o3dgcArithmeticCodec.cpp
  contrib/Open3DGC/o3dgcArithmeticCodec.h
  contrib/Open3DGC/o3dgcBinaryStream.h
  contrib/Open3DGC/o3dgcCommon.h
  contrib/Open3DGC/o3dgcDVEncodeParams.h
  contrib/Open3DGC/o3dgcDynamicVectorDecoder.cpp
  contrib/Open3DGC/o3dgcDynamicVectorDecoder.h
  contrib/Open3DGC/o3dgcDynamicVectorEncoder.cpp
  contrib/Open3DGC/o3dgcDynamicVectorEncoder.h
  contrib/Open3DGC/o3dgcDynamicVector.h
  contrib/Open3DGC/o3dgcFIFO.h
  contrib/Open3DGC/o3dgcIndexedFaceSet.h
  contrib/Open3DGC/o3dgcIndexedFaceSet.inl
  contrib/Open3DGC/o3dgcSC3DMCDecoder.h
  contrib/Open3DGC/o3dgcSC3DMCDecoder.inl
  contrib/Open3DGC/o3dgcSC3DMCEncodeParams.h
  contrib/Open3DGC/o3dgcSC3DMCEncoder.h
  contrib/Open3DGC/o3dgcSC3DMCEncoder.inl
  contrib/Open3DGC/o3dgcTimer.h
  contrib/Open3DGC/o3dgcTools.cpp
  contrib/Open3DGC/o3dgcTriangleFans.cpp
  contrib/Open3DGC/o3dgcTriangleFans.h
  contrib/Open3DGC/o3dgcTriangleListDecoder.h
  contrib/Open3DGC/o3dgcTriangleListDecoder.inl
  contrib/Open3DGC/o3dgcTriangleListEncoder.h
  contrib/Open3DGC/o3dgcTriangleListEncoder.inl
  contrib/Open3DGC/o3dgcVector.h
  contrib/Open3DGC/o3dgcVector.inl
)
SOURCE_GROUP( open3dgc FILES ${open3dgc_SRCS})

# Check dependencies for glTF importer with Open3DGC-compression.
# RT-extensions is used in "contrib/Open3DGC/o3dgcTimer.h" for collecting statistics. Pointed file
# has implementation for different platforms: WIN32, __MACH__ and other ("else" block).
FIND_PACKAGE(RT QUIET)
IF (RT_FOUND OR MSVC)
  SET( ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC 1 )
  ADD_DEFINITIONS( -DASSIMP_IMPORTER_GLTF_USE_OPEN3DGC=1 )
ELSE ()
  SET (open3dgc_SRCS "")
  # Urho3D: disable status prints
  # MESSAGE (INFO " RT-extension not found. glTF import/export will be built without Open3DGC-compression.")
  #!TODO: off course is better to remove statistics timers from o3dgc codec. Or propose to choose what to use.
ENDIF ()

# VC2010 fixes
if(MSVC10)
  option( VC10_STDINT_FIX "Fix for VC10 Compiler regarding pstdint.h redefinition errors" OFF )
  if( VC10_STDINT_FIX )
    ADD_DEFINITIONS( -D_STDINT )
  endif( VC10_STDINT_FIX )
endif(MSVC10)

if ( MSVC )
  ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
endif ( MSVC )

# Urho3D: disable status prints
# MESSAGE(STATUS "Enabled formats:${ASSIMP_IMPORTERS_ENABLED}")
# MESSAGE(STATUS "Disabled formats:${ASSIMP_IMPORTERS_DISABLED}")

SET( SOURCE_FILES
  # Assimp Files
  ${Core_SRCS}
  ${Common_SRCS}
  ${Logging_SRCS}
  ${Exporter_SRCS}
  ${PostProcessing_SRCS}
  ${MaterialSystem_SRCS}
  ${Step_SRCS}

  # Model Support
  ${ASSIMP_LOADER_SRCS}

  # Third-party libraries
  ${IrrXML_SRCS}
  ${unzip_SRCS}
  ${zlib_SRCS}
  ${Poly2Tri_SRCS}
  ${Clipper_SRCS}
  ${openddl_parser_SRCS}
  ${open3dgc_SRCS}
  # Necessary to show the headers in the project when using the VC++ generator:

  ${PUBLIC_HEADERS}
  ${COMPILER_HEADERS}

)
ADD_DEFINITIONS( -DOPENDDLPARSER_BUILD )

INCLUDE_DIRECTORIES(
  ${IRRXML_INCLUDE_DIR}
  contrib/openddlparser/include
)

# Urho3D: set the corresponding "no importer" define
IF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  SET( SOURCE_FILES ${SOURCE_FILES} ${C4D_SRCS})
  INCLUDE_DIRECTORIES(${C4D_INCLUDES})
ELSE (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  add_definitions(-DASSIMP_BUILD_NO_C4D_IMPORTER)
ENDIF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)

set (TARGET_NAME Assimp)
list (APPEND TARGET_PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES)   # Since we only build AssetImporter as a single-arch native tool, there is no point to build Assimp as universal binary library
setup_library ()

# When performing Xcode CI build suppress all the warnings for 3rd party libraries because there are just too many of them
if (XCODE AND DEFINED ENV{CI})
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif ()
