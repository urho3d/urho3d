#
# Listing and grouping of all the source files.
# 1) Set the file lists for each component
# 2) Create a Source Group for each component, for IDE project orginization
# 3) Add libassimp using the file lists (eliminates duplication of file names between
#    source groups and library command)
#

# Modified by Lasse Oorni and Yao Wei Tjong for Urho3D

if (MINGW)
    # The IFCReaderGen.cpp.obj has too many sections in DEBUG configuration build
    # Since GCC does not support /bigobj compiler flags as in MSVC, we use optimization flags to reduce the object file size
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O1")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1")
endif ()

INCLUDE_DIRECTORIES( code )
INCLUDE_DIRECTORIES( include )
INCLUDE_DIRECTORIES( code/BoostWorkaround )
INCLUDE_DIRECTORIES( contrib/unzip )
ADD_DEFINITIONS( -DASSIMP_BUILD_BOOST_WORKAROUND )

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
)

SET( Core_SRCS
  code/Assimp.cpp
)

SET( Boost_SRCS
  code/BoostWorkaround/boost/math/common_factor_rt.hpp
  code/BoostWorkaround/boost/foreach.hpp
  code/BoostWorkaround/boost/format.hpp
  code/BoostWorkaround/boost/scoped_array.hpp
  code/BoostWorkaround/boost/scoped_ptr.hpp
  code/BoostWorkaround/boost/shared_array.hpp
  code/BoostWorkaround/boost/shared_ptr.hpp
  code/BoostWorkaround/boost/make_shared.hpp
  code/BoostWorkaround/boost/static_assert.hpp
  code/BoostWorkaround/boost/tuple/tuple.hpp
)
SOURCE_GROUP(Boost FILES ${Boost_SRCS})

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
  code/DefaultIOStream.h
  code/DefaultIOSystem.cpp
  code/DefaultIOSystem.h
  code/CInterfaceIOWrapper.h
  code/Hash.h
  code/Importer.cpp
  code/IFF.h
  code/MemoryIOWrapper.h
  code/ParsingUtils.h
  code/StreamReader.h
  code/StreamWriter.h
  code/StringComparison.h
  code/SGSpatialSort.cpp
  code/SGSpatialSort.h
  code/VertexTriangleAdjacency.cpp
  code/VertexTriangleAdjacency.h
  code/GenericProperty.h
  code/SpatialSort.cpp
  code/SpatialSort.h
  code/SceneCombiner.cpp
  code/SceneCombiner.h
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
  code/Vertex.h
  code/LineSplitter.h
  code/TinyFormatter.h
  code/Profiler.h
  code/LogAux.h
  code/Bitmap.cpp
  code/Bitmap.h
  code/XMLTools.h
  code/Version.cpp
)
SOURCE_GROUP(Common FILES ${Common_SRCS})

IF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )
  SET( C4D_SRCS
    code/C4DImporter.cpp
    code/C4DImporter.h
  )
  SOURCE_GROUP( C4D FILES ${C4D_SRCS})
ENDIF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )

# macro to add the CMake Option ADD_ASSIMP_IMPORTER_<name> which enables compile of loader
# this way selective loaders can be compiled (reduces filesize + compile time)
MACRO(ADD_ASSIMP_IMPORTER name)
  OPTION(ASSIMP_BUILD_${name}_IMPORTER "build the ${name} importer" TRUE)
  IF(ASSIMP_BUILD_${name}_IMPORTER)
    LIST(APPEND ASSIMP_LOADER_SRCS ${ARGN})
    SET(ASSIMP_IMPORTERS_ENABLED "${ASSIMP_IMPORTERS_ENABLED} ${name}")
    SET(${name}_SRCS ${ARGN})
    SOURCE_GROUP(${name} FILES ${ARGN})
  ELSE()
    SET(${name}_SRC "")
    SET(ASSIMP_IMPORTERS_DISABLED "${ASSIMP_IMPORTERS_DISABLED} ${name}")
    add_definitions(-DASSIMP_BUILD_NO_${name}_IMPORTER)
  ENDIF()
ENDMACRO()

SET(ASSIMP_LOADER_SRCS "")
SET(ASSIMP_IMPORTERS_ENABLED "") # list of enabled importers
SET(ASSIMP_IMPORTERS_DISABLED "") # disabled list (used to print)

ADD_ASSIMP_IMPORTER(3DS
  code/3DSConverter.cpp
  code/3DSHelper.h
  code/3DSLoader.cpp
  code/3DSLoader.h
  code/3DSExporter.h
  code/3DSExporter.cpp
)

ADD_ASSIMP_IMPORTER(AC
  code/ACLoader.cpp
  code/ACLoader.h
)

ADD_ASSIMP_IMPORTER(ASE
  code/ASELoader.cpp
  code/ASELoader.h
  code/ASEParser.cpp
  code/ASEParser.h
)

ADD_ASSIMP_IMPORTER(ASSBIN
  code/AssbinExporter.h
  code/AssbinExporter.cpp
  code/AssbinLoader.h
  code/AssbinLoader.cpp
)

ADD_ASSIMP_IMPORTER(ASSXML
  code/AssxmlExporter.h
  code/AssxmlExporter.cpp
)

ADD_ASSIMP_IMPORTER(B3D
  code/B3DImporter.cpp
  code/B3DImporter.h
)

ADD_ASSIMP_IMPORTER(BVH
  code/BVHLoader.cpp
  code/BVHLoader.h
)

ADD_ASSIMP_IMPORTER(COLLADA
  code/ColladaHelper.h
  code/ColladaLoader.cpp
  code/ColladaLoader.h
  code/ColladaParser.cpp
  code/ColladaParser.h
  code/ColladaExporter.h
  code/ColladaExporter.cpp
)

ADD_ASSIMP_IMPORTER(DXF
  code/DXFLoader.cpp
  code/DXFLoader.h
  code/DXFHelper.h
)

ADD_ASSIMP_IMPORTER(CSM
  code/CSMLoader.cpp
  code/CSMLoader.h
)

ADD_ASSIMP_IMPORTER(HMP
  code/HMPFileData.h
  code/HMPLoader.cpp
  code/HMPLoader.h
  code/HalfLifeFileData.h
)

#FIXME: allow to set IRRMESH by option
ADD_ASSIMP_IMPORTER(IRR
  code/IRRLoader.cpp
  code/IRRLoader.h
  code/IRRMeshLoader.cpp
  code/IRRMeshLoader.h
  code/IRRShared.cpp
  code/IRRShared.h
)

ADD_ASSIMP_IMPORTER(LWO
  code/LWOAnimation.cpp
  code/LWOAnimation.h
  code/LWOBLoader.cpp
  code/LWOFileData.h
  code/LWOLoader.cpp
  code/LWOLoader.h
  code/LWOMaterial.cpp
)

ADD_ASSIMP_IMPORTER(LWS
  code/LWSLoader.cpp
  code/LWSLoader.h
)

ADD_ASSIMP_IMPORTER(MD2
  code/MD2FileData.h
  code/MD2Loader.cpp
  code/MD2Loader.h
  code/MD2NormalTable.h
)

ADD_ASSIMP_IMPORTER(MD3
  code/MD3FileData.h
  code/MD3Loader.cpp
  code/MD3Loader.h
)

ADD_ASSIMP_IMPORTER(MD5
  code/MD5Loader.cpp
  code/MD5Loader.h
  code/MD5Parser.cpp
  code/MD5Parser.h
)

ADD_ASSIMP_IMPORTER(MDC
  code/MDCFileData.h
  code/MDCLoader.cpp
  code/MDCLoader.h
  code/MDCNormalTable.h
)

ADD_ASSIMP_IMPORTER(MDL
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

ADD_ASSIMP_IMPORTER(NFF
  code/NFFLoader.cpp
  code/NFFLoader.h
)

ADD_ASSIMP_IMPORTER(NDO
  code/NDOLoader.cpp
  code/NDOLoader.h
)

ADD_ASSIMP_IMPORTER(OFF
  code/OFFLoader.cpp
  code/OFFLoader.h
)

ADD_ASSIMP_IMPORTER(OBJ
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

ADD_ASSIMP_IMPORTER(OGRE
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

ADD_ASSIMP_IMPORTER(OPENGEX
  code/OpenGEXExporter.cpp
  code/OpenGEXExporter.h
  code/OpenGEXImporter.cpp
  code/OpenGEXImporter.h
  code/OpenGEXStructs.h
)

ADD_ASSIMP_IMPORTER(PLY
  code/PlyLoader.cpp
  code/PlyLoader.h
  code/PlyParser.cpp
  code/PlyParser.h
  code/PlyExporter.cpp
  code/PlyExporter.h
)

ADD_ASSIMP_IMPORTER(MS3D
  code/MS3DLoader.cpp
  code/MS3DLoader.h
)

ADD_ASSIMP_IMPORTER(COB
  code/COBLoader.cpp
  code/COBLoader.h
  code/COBScene.h
)

ADD_ASSIMP_IMPORTER(BLEND
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

ADD_ASSIMP_IMPORTER(IFC
  code/IFCLoader.cpp
  code/IFCLoader.h
  code/IFCReaderGen.cpp
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

ADD_ASSIMP_IMPORTER(XGL
  code/XGLLoader.cpp
  code/XGLLoader.h
)


ADD_ASSIMP_IMPORTER(FBX
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

ADD_ASSIMP_IMPORTER(Q3D
  code/Q3DLoader.cpp
  code/Q3DLoader.h
)

ADD_ASSIMP_IMPORTER(Q3BSP
  code/Q3BSPFileData.h
  code/Q3BSPFileParser.h
  code/Q3BSPFileParser.cpp
  code/Q3BSPFileImporter.h
  code/Q3BSPFileImporter.cpp
  code/Q3BSPZipArchive.h
  code/Q3BSPZipArchive.cpp
)

ADD_ASSIMP_IMPORTER(RAW
  code/RawLoader.cpp
  code/RawLoader.h
)

ADD_ASSIMP_IMPORTER(SMD
  code/SMDLoader.cpp
  code/SMDLoader.h
)

ADD_ASSIMP_IMPORTER(STL
  code/STLLoader.cpp
  code/STLLoader.h
  code/STLExporter.h
  code/STLExporter.cpp
)

ADD_ASSIMP_IMPORTER(TERRAGEN
  code/TerragenLoader.cpp
  code/TerragenLoader.h
)

ADD_ASSIMP_IMPORTER(3D
  code/UnrealLoader.cpp
  code/UnrealLoader.h
)

ADD_ASSIMP_IMPORTER(X
  code/XFileHelper.h
  code/XFileImporter.cpp
  code/XFileImporter.h
  code/XFileParser.cpp
  code/XFileParser.h
  code/XFileExporter.h
  code/XFileExporter.cpp
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

SET( ConvertUTF_SRCS
  contrib/ConvertUTF/ConvertUTF.h
  contrib/ConvertUTF/ConvertUTF.c
)
SOURCE_GROUP( ConvertUTF FILES ${ConvertUTF_SRCS})

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
  contrib/openddlparser/code/OpenDDLParser.cpp
  contrib/openddlparser/code/DDLNode.cpp
  contrib/openddlparser/code/Value.cpp
  contrib/openddlparser/include/openddlparser/OpenDDLParser.h
  contrib/openddlparser/include/openddlparser/OpenDDLParserUtils.h
  contrib/openddlparser/include/openddlparser/OpenDDLCommon.h
  contrib/openddlparser/include/openddlparser/DDLNode.h
  contrib/openddlparser/include/openddlparser/Value.h
)
SOURCE_GROUP( openddl_parser FILES ${openddl_parser_SRCS})

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
  ${ConvertUTF_SRCS}
  ${unzip_SRCS}
  ${zlib_SRCS}
  ${Poly2Tri_SRCS}
  ${Clipper_SRCS}
  ${openddl_parser_SRCS}
  # Necessary to show the headers in the project when using the VC++ generator:
  ${Boost_SRCS}

  ${PUBLIC_HEADERS}
  ${COMPILER_HEADERS}

)
add_definitions( -DOPENDDLPARSER_BUILD )

INCLUDE_DIRECTORIES(
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
