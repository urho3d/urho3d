INCLUDE_DIRECTORIES( code/BoostWorkaround )
ADD_DEFINITIONS( -DASSIMP_BUILD_BOOST_WORKAROUND )

#
# Listing and grouping of all the source files for use with IDE project
# generators.
#
SET( HEADER_PATH include )

SET( COMPILER_HEADERS
	${HEADER_PATH}/Compiler/pushpack1.h
	${HEADER_PATH}/Compiler/poppack1.h
	code/pstdint.h
)

SET( PUBLIC_HEADERS
	${HEADER_PATH}/aiAnim.h
	${HEADER_PATH}/aiAssert.h
	${HEADER_PATH}/aiCamera.h
	${HEADER_PATH}/aiColor4D.h
	${HEADER_PATH}/aiColor4D.inl
	${HEADER_PATH}/aiConfig.h
	${HEADER_PATH}/aiDefines.h
	${HEADER_PATH}/aiFileIO.h
	${HEADER_PATH}/aiLight.h
	${HEADER_PATH}/aiMaterial.h
	${HEADER_PATH}/aiMaterial.inl
	${HEADER_PATH}/aiMatrix3x3.h
	${HEADER_PATH}/aiMatrix3x3.inl
	${HEADER_PATH}/aiMatrix4x4.h
	${HEADER_PATH}/aiMatrix4x4.inl
	${HEADER_PATH}/aiMesh.h
	${HEADER_PATH}/aiPostProcess.h
	${HEADER_PATH}/aiQuaternion.h
	${HEADER_PATH}/aiScene.h
	${HEADER_PATH}/aiTexture.h
	${HEADER_PATH}/aiTypes.h
	${HEADER_PATH}/aiVector2D.h
	${HEADER_PATH}/aiVector3D.h
	${HEADER_PATH}/aiVector3D.inl
	${HEADER_PATH}/aiVersion.h
	${HEADER_PATH}/assimp.h
	${HEADER_PATH}/assimp.hpp
	${HEADER_PATH}/DefaultLogger.h
	${HEADER_PATH}/ProgressHandler.h
	${HEADER_PATH}/IOStream.h
	${HEADER_PATH}/IOSystem.h
	${HEADER_PATH}/Logger.h
	${HEADER_PATH}/LogStream.h
	${HEADER_PATH}/NullLogger.h
)

SOURCE_GROUP( Compiler FILES	${HEADER_PATH}/Compiler/pushpack1.h
	${HEADER_PATH}/Compiler/poppack1.h
)

SOURCE_GROUP( Boost FILES
	code/BoostWorkaround/boost/math/common_factor_rt.hpp
	code/BoostWorkaround/boost/foreach.hpp
	code/BoostWorkaround/boost/format.hpp
	code/BoostWorkaround/boost/scoped_array.hpp
	code/BoostWorkaround/boost/scoped_ptr.hpp
	code/BoostWorkaround/boost/shared_array.hpp
	code/BoostWorkaround/boost/shared_ptr.hpp
	code/BoostWorkaround/boost/static_assert.hpp
	code/BoostWorkaround/boost/tuple/tuple.hpp
)

SOURCE_GROUP( Logging FILES
	${HEADER_PATH}/DefaultLogger.h
	${HEADER_PATH}/IOStream.h
	${HEADER_PATH}/LogStream.h
	${HEADER_PATH}/Logger.h
	${HEADER_PATH}/NullLogger.h
	code/Win32DebugLogStream.h
	code/DefaultLogger.cpp
	code/FileLogStream.h
)

SOURCE_GROUP( Common FILES
	code/aiAssert.cpp
	code/fast_atof.h
	code/qnan.h
	code/BaseImporter.cpp
	code/BaseImporter.h
	code/BaseProcess.cpp
	code/BaseProcess.h
	code/ByteSwap.h
	code/ProcessHelper.h
	code/DefaultProgressHandler.h
	code/DefaultIOStream.cpp
	code/DefaultIOStream.h
	code/DefaultIOSystem.cpp
	code/DefaultIOSystem.h
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
)

SOURCE_GROUP( 3DS FILES
	code/3DSConverter.cpp
	code/3DSHelper.h
	code/3DSLoader.cpp
	code/3DSLoader.h
)

SOURCE_GROUP( AC FILES
	code/ACLoader.cpp
	code/ACLoader.h
)

SOURCE_GROUP( ASE FILES
	code/ASELoader.cpp
	code/ASELoader.h
	code/ASEParser.cpp
	code/ASEParser.h
)
SOURCE_GROUP( B3D FILES
	code/B3DImporter.cpp
	code/B3DImporter.h
)

SOURCE_GROUP( BVH FILES
	code/BVHLoader.cpp
	code/BVHLoader.h
)

SOURCE_GROUP( Collada FILES
	code/ColladaHelper.h
	code/ColladaLoader.cpp
	code/ColladaLoader.h
	code/ColladaParser.cpp
	code/ColladaParser.h
)

SOURCE_GROUP( DXF FILES
	code/DXFLoader.cpp
	code/DXFLoader.h
)

SOURCE_GROUP( CSM FILES
	code/CSMLoader.cpp
	code/CSMLoader.h
)

SOURCE_GROUP( HMP FILES
	code/HMPFileData.h
	code/HMPLoader.cpp
	code/HMPLoader.h
	code/HalfLifeFileData.h
)

SOURCE_GROUP( Irr FILES
	code/IRRLoader.cpp
	code/IRRLoader.h
	code/IRRMeshLoader.cpp
	code/IRRMeshLoader.h
	code/IRRShared.cpp
	code/IRRShared.h
)

SOURCE_GROUP( LWO FILES
	code/LWOAnimation.cpp
	code/LWOAnimation.h
	code/LWOBLoader.cpp
	code/LWOFileData.h
	code/LWOLoader.cpp
	code/LWOLoader.h
	code/LWOMaterial.cpp
)

SOURCE_GROUP( LWS FILES
	code/LWSLoader.cpp
	code/LWSLoader.h
)

SOURCE_GROUP( MD2 FILES
	code/MD2FileData.h
	code/MD2Loader.cpp
	code/MD2Loader.h
	code/MD2NormalTable.h
)

SOURCE_GROUP( MD3 FILES
	code/MD3FileData.h
	code/MD3Loader.cpp
	code/MD3Loader.h
)

SOURCE_GROUP( MD5 FILES
	code/MD5Loader.cpp
	code/MD5Loader.h
	code/MD5Parser.cpp
	code/MD5Parser.h
)

SOURCE_GROUP( MDC FILES
	code/MDCFileData.h
	code/MDCLoader.cpp
	code/MDCLoader.h
	code/MDCNormalTable.h
)

SOURCE_GROUP( MDL FILES
	code/MDLDefaultColorMap.h
	code/MDLFileData.h
	code/MDLLoader.cpp
	code/MDLLoader.h
	code/MDLMaterialLoader.cpp
)

SOURCE_GROUP( MaterialSystem FILES
	code/MaterialSystem.cpp
	code/MaterialSystem.h
)

SOURCE_GROUP( NFF FILES
	code/NFFLoader.cpp
	code/NFFLoader.h
)

SOURCE_GROUP( NDO FILES
	code/NDOLoader.cpp
	code/NDOLoader.h
)

SOURCE_GROUP( OFFFormat FILES
	code/OFFLoader.cpp
	code/OFFLoader.h
)

SOURCE_GROUP( Obj FILES
	code/ObjFileData.h
	code/ObjFileImporter.cpp
	code/ObjFileImporter.h
	code/ObjFileMtlImporter.cpp
	code/ObjFileMtlImporter.h
	code/ObjFileParser.cpp
	code/ObjFileParser.h
	code/ObjTools.h
)

SOURCE_GROUP( Ogre FILES
	code/OgreImporter.h
	code/OgreImporter.cpp
	code/OgreImporterMaterial.cpp
)

SOURCE_GROUP( Ply FILES
	code/PlyLoader.cpp
	code/PlyLoader.h
	code/PlyParser.cpp
	code/PlyParser.h
)

SOURCE_GROUP(MS3D FILES
	code/MS3DLoader.cpp
	code/MS3DLoader.h
)

SOURCE_GROUP(COB FILES
	code/COBLoader.cpp
	code/COBLoader.h
	code/COBScene.h
)

SOURCE_GROUP(BLENDER FILES
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
)

SOURCE_GROUP( PostProcessing FILES
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
)

SOURCE_GROUP( Q3D FILES
	code/Q3DLoader.cpp
	code/Q3DLoader.h
)

SOURCE_GROUP( Q3BSP FILES
	code/Q3BSPFileData.h
	code/Q3BSPFileParser.h
	code/Q3BSPFileParser.cpp
	code/Q3BSPFileImporter.h
	code/Q3BSPFileImporter.cpp
	code/Q3BSPZipArchive.h
	code/Q3BSPZipArchive.cpp
)

SOURCE_GROUP( Raw FILES
	code/RawLoader.cpp
	code/RawLoader.h
)

SOURCE_GROUP( SMD FILES
	code/SMDLoader.cpp
	code/SMDLoader.h
)

SOURCE_GROUP( STL FILES
	code/STLLoader.cpp
	code/STLLoader.h
)

SOURCE_GROUP( Unreal FILES
	code/UnrealLoader.cpp
	code/UnrealLoader.h
)

SOURCE_GROUP( XFile FILES
	code/XFileHelper.h
	code/XFileImporter.cpp
	code/XFileImporter.h
	code/XFileParser.cpp
	code/XFileParser.h
)

SOURCE_GROUP( Extra FILES
	code/MakeVerboseFormat.cpp
	code/MakeVerboseFormat.h
	code/MD4FileData.h
)

SOURCE_GROUP( IrrXML FILES
	irrXMLWrapper.h
	contrib/irrXML/CXMLReaderImpl.h
	contrib/irrXML/heapsort.h
	contrib/irrXML/irrArray.h
	contrib/irrXML/irrString.h
	contrib/irrXML/irrTypes.h
	contrib/irrXML/irrXML.cpp
	contrib/irrXML/irrXML.h
)

SOURCE_GROUP( ConvertUTF FILES
	contrib/ConvertUTF/ConvertUTF.h
	contrib/ConvertUTF/ConvertUTF.c
)

SOURCE_GROUP( zlib FILES
	contrib/zlib/adler32.c
	contrib/zlib/compress.c
	contrib/zlib/crc32.c
	contrib/zlib/crc32.h
	contrib/zlib/deflate.c
	contrib/zlib/deflate.h
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
	contrib/zlib/zconf.in.h
	contrib/zlib/zlib.h
	contrib/zlib/zutil.c
	contrib/zlib/zutil.h
)

SOURCE_GROUP( unzip FILES
	contrib/unzip/crypt.h
	contrib/unzip/ioapi.c
	contrib/unzip/ioapi.h
	contrib/unzip/unzip.c
	contrib/unzip/unzip.h
)

SET (HEADER_FILES
	code/3DSHelper.h
	code/3DSLoader.h
	code/ACLoader.h
	code/ASELoader.h
	code/ASEParser.h
	code/AssimpPCH.h
	code/B3DImporter.h
	code/BVHLoader.h
	code/BaseImporter.h
	code/BaseProcess.h
	code/BlenderScene.h
	code/BlenderSceneGen.h
	code/BlenderIntermediate.h
	code/BlenderLoader.h
	code/BlenderModifier.h
	code/BlenderDNA.h
	code/BlenderDNA.inl
	code/ByteSwap.h
	code/CalcTangentsProcess.h
	code/COBLoader.h
	code/COBScene.h
	code/ColladaHelper.h
	code/ColladaLoader.h
	code/ColladaParser.h
	code/ComputeUVMappingProcess.h
	code/ConvertToLHProcess.h
	code/DXFLoader.h
	code/CSMLoader.h
	code/DefaultIOStream.h
	code/DefaultIOSystem.h
	code/DefaultProgressHandler.h
	code/FileLogStream.h
    code/FindDegenerates.h
	code/FindInstancesProcess.h
	code/FindInvalidDataProcess.h
	code/FixNormalsStep.h
	code/GenFaceNormalsProcess.h
	code/GenVertexNormalsProcess.h
	code/GenericProperty.h
	code/HMPFileData.h
	code/HMPLoader.h
	code/HalfLifeFileData.h
	code/Hash.h
	code/IFF.h
	code/IRRLoader.h
	code/IRRMeshLoader.h
	code/IRRShared.h
	code/ImproveCacheLocality.h
	code/JoinVerticesProcess.h
	code/LimitBoneWeightsProcess.h
	code/LineSplitter.h
    code/LWOAnimation.h
	code/LWOFileData.h
 	code/LWOLoader.h
	code/LWSLoader.h
	code/MakeVerboseFormat.h
	code/MD2FileData.h
	code/MD2Loader.h
	code/MD2NormalTable.h
	code/MD3FileData.h
    code/MD3Loader.h
	code/MD4FileData.h
	code/MDCLoader.h
	code/MDCNormalTable.h
	code/MDLDefaultColorMap.h
	code/MDLFileData.h
	code/MaterialSystem.h
	code/MD5Loader.h
	code/MD5Parser.h
	code/MDCFileData.h
	code/MDLLoader.h
	code/MS3DLoader.h
	code/NDOLoader.h
	code/NFFLoader.h
	code/OFFLoader.h
	code/ObjFileData.h
	code/ObjFileImporter.h
	code/ObjFileMtlImporter.h
	code/ObjFileParser.h
	code/ObjTools.h
	code/OgreImporter.h
	code/OptimizeGraph.h
	code/OptimizeMeshes.h
	code/ParsingUtils.h
	code/PlyLoader.h
	code/PlyParser.h
	code/PretransformVertices.h
	code/ProcessHelper.h
	code/Profiler.h
	code/RawLoader.h
	code/RemoveComments.h
	code/RemoveRedundantMaterials.h
	code/Q3DLoader.h
	code/Q3BSPFileData.h
	code/Q3BSPFileParser.h
	code/Q3BSPFileImporter.h
	code/Q3BSPZipArchive.h
	code/RemoveVCProcess.h
	code/SGSpatialSort.h
	code/SMDLoader.h
	code/STLLoader.h
	code/SceneCombiner.h
	code/ScenePreprocessor.h
	code/SkeletonMeshBuilder.h
	code/SmoothingGroups.h
	code/SortByPTypeProcess.h
	code/SpatialSort.h
	code/SplitLargeMeshes.h
	code/StandardShapes.h
	code/StdOStreamLogStream.h
	code/StreamReader.h
	code/StringComparison.h
	code/Subdivision.h
	code/TargetAnimation.h
	code/TerragenLoader.h
	code/TextureTransform.h
	code/TinyFormatter.h
	code/TriangulateProcess.h
	code/UnrealLoader.h
	code/ValidateDataStructure.h
	code/Vertex.h
	code/VertexTriangleAdjacency.h
	code/Win32DebugLogStream.h
	code/XFileHelper.h
	code/XFileImporter.h
	code/XFileParser.h
	code/fast_atof.h
	code/irrXMLWrapper.h
	code/qnan.h
	code/BoostWorkaround/boost/math/common_factor_rt.hpp
	code/BoostWorkaround/boost/foreach.hpp
	code/BoostWorkaround/boost/format.hpp
	code/BoostWorkaround/boost/scoped_array.hpp
	code/BoostWorkaround/boost/scoped_ptr.hpp
	code/BoostWorkaround/boost/shared_array.hpp
	code/BoostWorkaround/boost/shared_ptr.hpp
	code/BoostWorkaround/boost/static_assert.hpp
	code/BoostWorkaround/boost/tuple/tuple.hpp
	${PUBLIC_HEADERS}
	${COMPILER_HEADERS}
)

SET (SOURCE_FILES
	code/3DSConverter.cpp
	code/3DSLoader.cpp
	code/ACLoader.cpp
	code/ASELoader.cpp
	code/ASEParser.cpp
	code/Assimp.cpp
	code/AssimpPCH.cpp
	code/B3DImporter.cpp
	code/BVHLoader.cpp
	code/BaseImporter.cpp
	code/BaseProcess.cpp
	code/BlenderLoader.cpp
	code/BlenderDNA.cpp
	code/BlenderScene.cpp
	code/BlenderModifier.cpp
	code/CalcTangentsProcess.cpp
	code/COBLoader.cpp
	code/ColladaLoader.cpp
	code/ColladaParser.cpp
	code/ComputeUVMappingProcess.cpp
	code/ConvertToLHProcess.cpp
	code/DXFLoader.cpp
	code/CSMLoader.cpp
	code/DefaultIOStream.cpp
	code/DefaultIOSystem.cpp
	code/DefaultLogger.cpp
	code/FindDegenerates.cpp
	code/FindInstancesProcess.cpp
	code/FindInvalidDataProcess.cpp
	code/FixNormalsStep.cpp
	code/GenFaceNormalsProcess.cpp
	code/GenVertexNormalsProcess.cpp
	code/HMPLoader.cpp
	code/IRRLoader.cpp
	code/IRRMeshLoader.cpp
	code/IRRShared.cpp
	code/Importer.cpp
	code/ImproveCacheLocality.cpp
	code/JoinVerticesProcess.cpp
	code/LWOAnimation.cpp
	code/LWOBLoader.cpp
	code/LWOLoader.cpp
	code/LWOMaterial.cpp
	code/LWSLoader.cpp
	code/LimitBoneWeightsProcess.cpp
	code/MakeVerboseFormat.cpp
	code/MD2Loader.cpp
	code/MD3Loader.cpp
	code/MD5Loader.cpp
	code/MD5Parser.cpp
	code/MDCLoader.cpp
	code/MDLLoader.cpp
	code/MDLMaterialLoader.cpp
	code/MS3DLoader.cpp
	code/MaterialSystem.cpp
	code/NDOLoader.cpp
	code/NFFLoader.cpp
	code/OFFLoader.cpp
	code/ObjFileImporter.cpp
	code/ObjFileMtlImporter.cpp
	code/ObjFileParser.cpp
	code/OgreImporter.cpp
	code/OgreImporterMaterial.cpp
	code/OptimizeGraph.cpp
	code/OptimizeMeshes.cpp
	code/PlyLoader.cpp
	code/PlyParser.cpp
	code/PretransformVertices.cpp
	code/Q3DLoader.cpp
	code/Q3BSPFileParser.cpp
	code/Q3BSPFileImporter.cpp
	code/Q3BSPZipArchive.cpp
	code/RawLoader.cpp
	code/RemoveComments.cpp
	code/RemoveRedundantMaterials.cpp
	code/RemoveVCProcess.cpp
	code/SGSpatialSort.cpp
	code/SMDLoader.cpp
	code/STLLoader.cpp
	code/SceneCombiner.cpp
	code/ScenePreprocessor.cpp
	code/SkeletonMeshBuilder.cpp
	code/SortByPTypeProcess.cpp
	code/SpatialSort.cpp
	code/SplitLargeMeshes.cpp
	code/StandardShapes.cpp
	code/Subdivision.cpp
	code/TargetAnimation.cpp
	code/TerragenLoader.cpp
	code/TextureTransform.cpp
	code/TriangulateProcess.cpp
	code/UnrealLoader.cpp
	code/ValidateDataStructure.cpp
	code/VertexTriangleAdjacency.cpp
	code/XFileImporter.cpp
	code/XFileParser.cpp
	code/aiAssert.cpp
)

SET (CONTRIB_FILES
	contrib/irrXML/CXMLReaderImpl.h
	contrib/irrXML/heapsort.h
	contrib/irrXML/irrArray.h
	contrib/irrXML/irrString.h
	contrib/irrXML/irrTypes.h
	contrib/irrXML/irrXML.cpp
	contrib/irrXML/irrXML.h
	contrib/zlib/adler32.c
	contrib/zlib/compress.c
	contrib/zlib/crc32.c
	contrib/zlib/crc32.h
	contrib/zlib/deflate.c
	contrib/zlib/deflate.h
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
	contrib/zlib/zconf.in.h
	contrib/zlib/zlib.h
	contrib/zlib/zutil.c
	contrib/zlib/zutil.h
	contrib/ConvertUTF/ConvertUTF.c
	contrib/unzip/crypt.h
	contrib/unzip/ioapi.c
	contrib/unzip/ioapi.h
	contrib/unzip/unzip.c
	contrib/unzip/unzip.h
)

ADD_LIBRARY ( Assimp STATIC ${HEADER_FILES} ${SOURCE_FILES} ${CONTRIB_FILES} )

if (MSVC)
    foreach(FILE ${SOURCE_FILES})
        if (${FILE} MATCHES "AssimpPCH.cpp$")
            set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YcAssimpPCH.h")
        else()
            set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/YuAssimpPCH.h")
        endif()
    endforeach ()
endif ()