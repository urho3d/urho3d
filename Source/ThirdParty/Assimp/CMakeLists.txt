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

INCLUDE_DIRECTORIES( include )
INCLUDE_DIRECTORIES( code/BoostWorkaround )
INCLUDE_DIRECTORIES( contrib/unzip )
ADD_DEFINITIONS( -DASSIMP_BUILD_BOOST_WORKAROUND )

SET( HEADER_PATH include/assimp )

SET( COMPILER_HEADERS
	${HEADER_PATH}/Compiler/pushpack1.h
	${HEADER_PATH}/Compiler/poppack1.h
	code/pstdint.h
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
	code/AssimpPCH.cpp
	code/AssimpPCH.h
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
	${HEADER_PATH}/IOStream.hpp
	${HEADER_PATH}/LogStream.hpp
	${HEADER_PATH}/Logger.hpp
	${HEADER_PATH}/NullLogger.hpp
	code/Win32DebugLogStream.h
	code/DefaultLogger.cpp
	code/FileLogStream.h
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
	code/ByteSwap.h
	code/DefaultProgressHandler.h
	code/DefaultIOStream.cpp
	code/DefaultIOStream.h
	code/DefaultIOSystem.cpp
	code/DefaultIOSystem.h
	code/CInterfaceIOWrapper.h
	code/Hash.h
	code/Importer.cpp
	code/IFF.h
	code/ParsingUtils.h
	code/StdOStreamLogStream.h
	code/StreamReader.h
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
)
SOURCE_GROUP(Common FILES ${Common_SRCS})

SET( 3DS_SRCS
	code/3DSConverter.cpp
	code/3DSHelper.h
	code/3DSLoader.cpp
	code/3DSLoader.h
)
SOURCE_GROUP(3DS FILES ${3DS_SRCS})

SET( AC_SRCS
	code/ACLoader.cpp
	code/ACLoader.h
)
SOURCE_GROUP( AC FILES ${AC_SRCS})

SET( ASE_SRCS
	code/ASELoader.cpp
	code/ASELoader.h
	code/ASEParser.cpp
	code/ASEParser.h
)
SOURCE_GROUP( ASE FILES ${ASE_SRCS})

SET( B3D_SRCS
	code/B3DImporter.cpp
	code/B3DImporter.h
)
SOURCE_GROUP( B3D FILES ${B3D_SRCS})

SET( BVH_SRCS
	code/BVHLoader.cpp
	code/BVHLoader.h
)
SOURCE_GROUP( BVH FILES ${BVH_SRCS})

SET( Collada_SRCS
	code/ColladaHelper.h
	code/ColladaLoader.cpp
	code/ColladaLoader.h
	code/ColladaParser.cpp
	code/ColladaParser.h
	code/ColladaExporter.h
	code/ColladaExporter.cpp
)
SOURCE_GROUP( Collada FILES ${Collada_SRCS})

SET( DXF_SRCS
	code/DXFLoader.cpp
	code/DXFLoader.h
	code/DXFHelper.h
)
SOURCE_GROUP( DXF FILES ${DXF_SRCS})

SET( CSM_SRCS
	code/CSMLoader.cpp
	code/CSMLoader.h
)
SOURCE_GROUP( CSM FILES ${CSM_SRCS})

SET( HMP_SRCS
	code/HMPFileData.h
	code/HMPLoader.cpp
	code/HMPLoader.h
	code/HalfLifeFileData.h
)
SOURCE_GROUP( HMP FILES ${HMP_SRCS})

SET( Irr_SRCS
	code/IRRLoader.cpp
	code/IRRLoader.h
	code/IRRMeshLoader.cpp
	code/IRRMeshLoader.h
	code/IRRShared.cpp
	code/IRRShared.h
)
SOURCE_GROUP( Irr FILES ${Irr_SRCS})

SET( LWO_SRCS
	code/LWOAnimation.cpp
	code/LWOAnimation.h
	code/LWOBLoader.cpp
	code/LWOFileData.h
	code/LWOLoader.cpp
	code/LWOLoader.h
	code/LWOMaterial.cpp
)
SOURCE_GROUP( LWO FILES ${LWO_SRCS})

SET( LWS_SRCS
	code/LWSLoader.cpp
	code/LWSLoader.h
)
SOURCE_GROUP( LWS FILES ${LWS_SRCS})

SET ( M3_SRCS
	code/M3Importer.cpp
	code/M3Importer.h
)
SOURCE_GROUP( M3 FILES ${M3_SRCS} )

SET( MD2_SRCS
	code/MD2FileData.h
	code/MD2Loader.cpp
	code/MD2Loader.h
	code/MD2NormalTable.h
)
SOURCE_GROUP( MD2 FILES ${MD2_SRCS})

SET( MD3_SRCS
	code/MD3FileData.h
	code/MD3Loader.cpp
	code/MD3Loader.h
)
SOURCE_GROUP( MD3 FILES ${MD3_SRCS})

SET( MD5_SRCS
	code/MD5Loader.cpp
	code/MD5Loader.h
	code/MD5Parser.cpp
	code/MD5Parser.h
)
SOURCE_GROUP( MD5 FILES ${MD5_SRCS})

SET( MDC_SRCS
	code/MDCFileData.h
	code/MDCLoader.cpp
	code/MDCLoader.h
	code/MDCNormalTable.h
)
SOURCE_GROUP( MDC FILES ${MDC_SRCS})

SET( MDL_SRCS
	code/MDLDefaultColorMap.h
	code/MDLFileData.h
	code/MDLLoader.cpp
	code/MDLLoader.h
	code/MDLMaterialLoader.cpp
)
SOURCE_GROUP( MDL FILES ${MDL_SRCS})

SET( MaterialSystem_SRCS
	code/MaterialSystem.cpp
	code/MaterialSystem.h
)
SOURCE_GROUP( MaterialSystem FILES ${MaterialSystem_SRCS})

SET( NFF_SRCS
	code/NFFLoader.cpp
	code/NFFLoader.h
)
SOURCE_GROUP( NFF FILES ${NFF_SRCS})

SET( NDO_SRCS
	code/NDOLoader.cpp
	code/NDOLoader.h
)
SOURCE_GROUP( NDO FILES ${NDO_SRCS})

SET( OFFFormat_SRCS
	code/OFFLoader.cpp
	code/OFFLoader.h
)
SOURCE_GROUP( OFFFormat FILES ${OFFFormat_SRCS})

SET( Obj_SRCS
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
SOURCE_GROUP( Obj FILES ${Obj_SRCS})

SET( Ogre_SRCS
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
SOURCE_GROUP( Ogre FILES ${Ogre_SRCS})

SET( Ply_SRCS
	code/PlyLoader.cpp
	code/PlyLoader.h
	code/PlyParser.cpp
	code/PlyParser.h
	code/PlyExporter.cpp
	code/PlyExporter.h
)
SOURCE_GROUP( Ply FILES ${Ply_SRCS})

SET(MS3D_SRCS
	code/MS3DLoader.cpp
	code/MS3DLoader.h
)
SOURCE_GROUP( MS3D FILES ${MS3D_SRCS})

SET(COB_SRCS
	code/COBLoader.cpp
	code/COBLoader.h
	code/COBScene.h
)
SOURCE_GROUP( COB FILES ${COB_SRCS})

SET(BLENDER_SRCS
	code/BlenderBMesh.cpp
	code/BlenderBMesh.h
	code/BlenderLoader.cpp
	code/BlenderLoader.h
	code/BlenderDNA.cpp
	code/BlenderDNA.h
	code/BlenderDNA.inl
	code/BlenderScene.cpp
	code/BlenderScene.h
	code/BlenderSceneGen.h
	code/BlenderTessellator.cpp
	code/BlenderTessellator.h
	code/BlenderIntermediate.h
	code/BlenderModifier.h
	code/BlenderModifier.cpp
)
SOURCE_GROUP( BLENDER FILES ${BLENDER_SRCS})

SET(IFC_SRCS
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
	code/STEPFileEncoding.h
	code/STEPFileEncoding.cpp
)
SOURCE_GROUP( IFC FILES ${IFC_SRCS})

SET( XGL_SRCS
	code/XGLLoader.cpp
	code/XGLLoader.h
)
SOURCE_GROUP( XGL FILES ${XGL_SRCS})

SET(FBX_SRCS
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
SOURCE_GROUP( FBX FILES ${FBX_SRCS})

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
	code/TerragenLoader.cpp
	code/TerragenLoader.h
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

SET( Q3D_SRCS
	code/Q3DLoader.cpp
	code/Q3DLoader.h
)
SOURCE_GROUP( Q3D FILES ${Q3D_SRCS})

SET( Q3BSP_SRCS
	code/Q3BSPFileData.h
	code/Q3BSPFileParser.h
	code/Q3BSPFileParser.cpp
	code/Q3BSPFileImporter.h
	code/Q3BSPFileImporter.cpp
	code/Q3BSPZipArchive.h
	code/Q3BSPZipArchive.cpp
)
SOURCE_GROUP( Q3BSP FILES ${Q3BSP_SRCS})

SET( Raw_SRCS
	code/RawLoader.cpp
	code/RawLoader.h
)
SOURCE_GROUP( Raw FILES ${Raw_SRCS})

SET( SMD_SRCS
	code/SMDLoader.cpp
	code/SMDLoader.h
)
SOURCE_GROUP( SMD FILES ${SMD_SRCS})

SET( STL_SRCS
	code/STLLoader.cpp
	code/STLLoader.h
	code/STLExporter.h
	code/STLExporter.cpp
)
SOURCE_GROUP( STL FILES ${STL_SRCS})

SET( Unreal_SRCS
	code/UnrealLoader.cpp
	code/UnrealLoader.h
)
SOURCE_GROUP( Unreal FILES ${Unreal_SRCS})

SET( XFile_SRCS
	code/XFileHelper.h
	code/XFileImporter.cpp
	code/XFileImporter.h
	code/XFileParser.cpp
	code/XFileParser.h
)
SOURCE_GROUP( XFile FILES ${XFile_SRCS})

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
#	contrib/zlib/gzclose.c
#	contrib/zlib/gzguts.h
#	contrib/zlib/gzlib.c
#	contrib/zlib/gzread.c
#	contrib/zlib/gzwrite.c
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
	contrib/zlib/zconf.h
	contrib/zlib/zlib.h
	contrib/zlib/zutil.c
	contrib/zlib/zutil.h
)
SOURCE_GROUP( zlib FILES ${zlib_SRCS})

if ( MSVC80 OR MSVC90 OR MSVC10 )
	ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
	ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
endif ( MSVC80 OR MSVC90 OR MSVC10 )

SET( SOURCE_FILES
	# Assimp Files
	${Core_SRCS}
	${Common_SRCS}
	${Logging_SRCS}
	${Exporter_SRCS}
	${PostProcessing_SRCS}

	# Model Support
	${3DS_SRCS}
	${AC_SRCS}
	${ASE_SRCS}
	${B3D_SRCS}
	${BVH_SRCS}
	${Collada_SRCS}
	${DXF_SRCS}
	${CSM_SRCS}
	${HMP_SRCS}
	${Irr_SRCS}
	${LWO_SRCS}
	${LWS_SRCS}
	${M3_SRCS}
	${MD2_SRCS}
	${MD3_SRCS}
	${MD5_SRCS}
	${MDC_SRCS}
	${MDL_SRCS}
	${MaterialSystem_SRCS}
	${NFF_SRCS}
	${OFFFormat_SRCS}
	${Obj_SRCS}
	${Ogre_SRCS}
	${Ply_SRCS}
	${Q3D_SRCS}
	${Q3BSP_SRCS}
	${Raw_SRCS}
	${SMD_SRCS}
	${STL_SRCS}
	${Unreal_SRCS}
	${XFile_SRCS}
	${Extra_SRCS}
	${MS3D_SRCS}
	${COB_SRCS}
	${BLENDER_SRCS}
	${NDO_SRCS}
	${IFC_SRCS}
	${XGL_SRCS}
	${FBX_SRCS}
)

SET( CONTRIB_FILES
	# Third-party libraries
	${IrrXML_SRCS}
	${ConvertUTF_SRCS}
	${unzip_SRCS}
	${zlib_SRCS}
	${Poly2Tri_SRCS}
	${Clipper_SRCS}
	# Necessary to show the headers in the project when using the VC++ generator:
	${Boost_SRCS}
)

set (TARGET_NAME Assimp)
list (APPEND SOURCE_FILES ${CONTRIB_FILES} ${PUBLIC_HEADERS} ${COMPILER_HEADERS})

set_source_files_properties (contrib/clipper/clipper.cpp contrib/irrXML/irrXML.cpp PROPERTIES NO_PCH TRUE)
enable_pch (code/AssimpPCH.h)

setup_library ()
