include "ogre/lib/ogreSkeletonLib_usefulfns.ms"
include "ogre/lib/ogrebipedlib.ms"

----------------------------------------------------------------------------------------
-- ----------------------------------- WRITE MESH ----------------------------------- --
----------------------------------------------------------------------------------------

-----------------------------------------------------------------
-- Global 'variables'
-- There is an array with vertices datas for each submesh
-- There is also an array made up of faces.
-----------------------------------------------------------------

verticesArrays=#() ;
facesArrays=#() ;
boneAssignments=#() ;
submeshesId=#() ;
materialName = "" ;

-- verticesArrays[i] will describe the subMesh number i and its elements will be ogreVertices where
--	ogreVert = #(x,y,z,nx,ny,nz,r,g,b,a,u1,v1,u2,v2....) 
--   		     ----- -------- ------- ---------------
--          	 Pos     Nmal    RGBA       UVs sets
-- RGBA being the  vertex color when relevant 	(Optional)
-- A vertex can contain multiple UVs sets		(Optional)

-- facesArrays[i] is an array of Point3 describing the subMesh i. Each Point3 contains vertices indices for a face that is gonna be exported

-- boneAssignments[i] describes the bones assignements for subMesh i. It is an array of triplets like #(vertexIndex,boneIndex,weight)

-- submeshesId is the list of material Ids 

-- materialName is the name that Ogre will use


----------------------------------------------------------------
-- exploreMesh returns a string which is "OK" or an error message
-- if there are warnings, it displays message boxes.
-----------------------------------------------------------------
function exploreMesh pmesh exportUV exportColours=
(
	local material, answer, m ;
	
	answer = "" ;
	m = snapShotAsMesh pmesh ;
	
	-- first, is a material defined	?
	material = pmesh.material ;
	if (material == undefined) then
		answer = "This mesh doesn't have any material, please apply one\n" ;
	else
		-- then, are UVW coords set up ?
		if (exportUV and getNumTVerts m == 0) then
			answer = "This mesh must have UVW coords in order to be exported" ;
		
	if (answer == "") then 
		answer = "OK" ;
	
	delete m ;
	answer ;
)


----------------------------------------------------------------
-- returns the correct normal for the vertex
-- according to smoothing groups
-----------------------------------------------------------------
function getVertexNormalAccordingToSmoothingGroups selectedMesh faceIndex vertexIndex =
(
	local normal;
       	local faceSmoothingGroup = getFaceSmoothGroup selectedMesh faceIndex

        if faceSmoothingGroup == 0 then
        (
                -- if not smooth use face normal
                normal = getFaceNormal selectedMesh faceIndex
        )       
        else
        (
				local vertexIndexes = getFace selectedMesh faceIndex;
                local vI = vertexIndexes[vertexIndex] 
                local n = [0, 0, 0] -- point3
                for adjoiningFaceIndex in (meshop.getFacesUsingVert selectedMesh vI) do
                (
					sg = getFaceSmoothGroup selectedMesh adjoiningFaceIndex;
					and_sg = bit.and sg faceSmoothingGroup ;
					if (and_sg != 0) then
						n += getFaceNormal selectedMesh adjoiningFaceIndex ;
                )
                normal = normalize n;
        ) 	

	normal;
)

function tabEquals tab1 tab2 =
(
	if (tab1.count != tab2.count) then
		return false;

	for i=1 to tab1.count do
		if (tab1[i] != tab2[i]) then
			return false;
		
	return true;
)

function doesVertexExistAlready searchTable vertexIndex vertexNormal vertexColorIndex vertexAlphaIndex UVs exportUV exportColor =
(
	local start_uvs;
	vertex = #();
	--format "vertex a tester % % \n" vertexIndex vertexNormal;

	if (searchTable[vertexIndex]==undefined) then
		return 0;
	
	for vertex in searchTable[vertexIndex] do
	(
		if (vertex[2]!=vertexNormal) then
			continue;
			
		if (exportColor) then
		(
			if (vertex[3]!=vertexColorIndex) then
				continue;
				
			if (vertex[4]!=vertexAlphaIndex) then
				continue;
				
			start_uvs = 4;
		)
		else
		(
			start_uvs = 2;
		)
		
		if (exportUV) then
		(
			local equal = true;
			for i=1 to UVs.count do
			(
				if (vertex[start_uvs+i]!=UVs[i]) then
				(
					equal = false;
					exit;
				)
			)
			if (not equal) then 
				continue;
		)
		
		return vertex[1] ;
	)
	return 0;
)

----------------------------------------------------------------------------
-- Retrieves al the datas which wil be used
-- tmesh is the mesh object
-- flipyz = true if you want coords to fit in OGRE.
-- flipNormal = true if you want to flip normals
-- scale : the scale factor
-- exportUV = true if you want to export texture
-- numUVsets : number of texture coordinates to export (if exportUV is true, the minimum is 1. if exportUV is false, this parameter is irrelevant)
-- exportColor = true if you want to export vertices colors
-- sk : the skin modifier (may be undefined)
-- phy : the physique modifier (may be undefined)
-- stores datas in verticesArrays and facesArrays.
----------------------------------------------------------------------------
function getDatas tmesh flipyz scale flipNormal exportUV numUVsets exportColours exportHelpers sk phy =
(
	local face;						--index of the current face
	local localVertexIndex; 		--index of the current vertex (relative to the current face) ie : 1, 2 or 3
	local vertexNormal;				--normal of the current vertex (Point3)
	local vertexPosition;			--position of the current vertex (Point3)
	local faceVerticesIndices;		--indices of the vertex for the current face (Point3)
	local vertexIndex;				--index of the current vertex (in the mesh)
	local matId;					--material Id of the current face
	local numFaces;					--number of faces in the mesh
	
	local faceVertexColorIndices;	--indices of the vertices for the current face in the vertex color table of the mesh (Point3)
	local vertexColorIndex;			--index of the current vertex in the vertex color table of the mesh
	local vertexColor;				--vertex color for the current vertex (color)
	local faceVertexAlphaIndices;	--indices of the vertices for the current face in the vertex alpha table of the mesh (Point3)
	local vertexAlpha;				--vertex alpha of the current alpha
	local vertexAlphaIndex;			--index of the current vertex in the vertex alpha map channel (-2)
	
	local ogreFace;					--indices of the vertices for the current face (references the list of vertices that is gonna be exported, not the vertices of the original mesh)
	
	local vertexWeightCount;		--number of bones influencing the current vertex
	local vertexWeight;				--current weight
	
	local searchTable ;
	local k ;
	local rootId ;
	
	local UVcoords;					-- will contain the texture coordinates for the current vertex. its size will be numUVsets*2 if exportUV is true.
	
	-- searchTables will contain a searchTable for every subMesh.
	-- searchTable will be the current table for the current subMesh.
	-- Every vertex will be stored here to check for duplicates.
	searchTable=#() ;
	searchTables=#() ;
	
	-- initialisation of the current ogre face as a vector
	ogreFace=Point3 12 12 12 ;
	
	-- Data arrays init.	
	verticesArrays=#() ;
	facesArrays=#() ;
	boneAssignments = #() ;
	submeshesId = #() ;
	UVcoords=#() ;

	-- compute bones list for the model.
	BonesList=#()
	computeBonesList phy sk exportHelpers ;

	numFaces = (getNumFaces tmesh);

	-- For each face
	for face = 1 to numFaces do 		-- LOOP on FACES --
	(		
		OgreExportObject.exportProgress.value = (100.0*face/numFaces);
	
		faceVerticesIndices = getFace tmesh face ;
		matId = getFaceMatId tmesh face ;		
		
		-- Vertex Color Face
		if (exportColours) then
		(
			faceVertexColorIndices = meshOp.getMapFace tmesh 0 face ;	-- 0 is the vertex color channel
			faceVertexAlphaIndices = meshOp.getMapFace tmesh -2 face ;	-- -2 is the vertex alpha channel
		)
		else
		(
			faceVertexColorIndices = Point3 1 1 1 ;
			faceVertexAlphaIndices = Point3 1 1 1 ;
		)
		
		-- For each vertex whose face is made up of.
		for localVertexIndex=1 to 3 do 				-- LOOP on VERTICES --
		(			
		    vertexIndex = (int) (faceVerticesIndices[localVertexIndex]) ;
			vertexColorIndex = (int) (faceVertexColorIndices[localVertexIndex]) ;
			vertexAlphaIndex = (int) (faceVertexAlphaIndices[localVertexIndex]);
			vertexNormal = getVertexNormalAccordingToSmoothingGroups tmesh face localVertexIndex;
			-- flip normal capability
			if (flipNormal) then
			(
				vertexNormal = vertexNormal * -1
			)
			
			-- we retrieve datas. it depends on options.
			-- UV face
			if (exportUV) then
			(
				UVcoords=#();
				for ch=1 to numUVsets do
				(
					local vertInds = meshOp.getMapFace tmesh ch face ;
					local UVW = meshOp.getMapVert tmesh ch vertInds[localVertexIndex] ;	-- retrieve the UV for the corresponding channel.
					append UVcoords UVW[1];
					append UVcoords UVW[2];							-- don't care about the W coordinate
				)
			)
			else
			(
				UVcoords=#();
			)
		
			-- we try to find the corresponding searchtable.											
			if (searchTables[matId] == undefined ) then
				searchTables[matId]=#() ;			-- we found a new subMesh, create the searchTable for it
			
			searchTable = searchTables[matId] ;		-- set the searchTable to the current subMesh
			
			newVertex = 1 ;
			ogreVertNum = 1;
			-- Maybe this vertex has already been found.
			-- So we use searchTable.
			res = doesVertexExistAlready searchTable vertexIndex vertexNormal vertexColorIndex vertexAlphaIndex UVcoords exportUV exportColours;
			if (res==0) then
			(
				newVertex = 1 ;
				--format "nouveau vertex % % %\n" vertexIndex vertexNormal UVcoords;
			)
			else
			(
				newVertex = 0;
				ogreVertNum = res;
			)

			if (newVertex == 1) then -- That is to say it has not been found. 
			(
				-- Maybe the material found defines a new submesh...
				if (verticesArrays[matId] == undefined) then
				(
					format "- Submesh detected: material ID = %\n" matId
					verticesArrays[matId] = #() ;
					boneAssignments[matId] = #() ;
					append submeshesId matId ;
				)

				-- the vertex number for the current submesh must be updated
				-- vertex number is increased
				ogreVertNum = verticesArrays[matId].count + 1; 
				
				-- it is added to the searchTable
				if (searchTable[vertexIndex]==undefined) then
				(
					searchTable[vertexIndex] = #() ;
				)
				local data = #();
				append data ogreVertNum ;
				n = copy vertexNormal ;
				append data n ;
				if (exportColours) then
				(
					append data VertexColorIndex ;
					append data VertexAlphaIndex ;
				)
				if (exportUV) then
				(
					if (UVcoords.count > 0) then
					(
						for uv=1 to UVcoords.count do
							append data UVcoords[uv];
					)
				)
				append searchTable[vertexIndex] data ;
					
				-- we retrieve data
				vertexPosition = getVert tmesh faceVerticesIndices[localVertexIndex] ;
				
				vertexColor = Point3 0 0 0;
				vertexAlpha = 255;
				if (exportColours) then
				(
					vertexColor = (meshOp.getMapVert tmesh 0 vertexColorIndex);
					vertexAlpha = (meshOp.getMapVert tmesh -2 vertexAlphaIndex)[1];
				)
				
				-- change scale
				vertexPosition = vertexPosition * scale ;
		
				-- flip axes		
				if (flipyz) then
				(
					vertTmp = copy vertexPosition ;
					vertexPosition[2] = vertTmp[3] ;
					vertexPosition[3] = -vertTmp[2] ;
					
					nmalTmp = copy vertexNormal ;
					vertexNormal[2] = nmalTmp[3] ;
					vertexNormal[3] = -nmalTmp[2] ;
				)
				
				-- store the vertex in verticesArrays
				vertexData = #(vertexPosition[1],vertexPosition[2],vertexPosition[3],vertexNormal[1],vertexNormal[2],vertexNormal[3],vertexColor[1],vertexColor[2],vertexColor[3],vertexAlpha) ;
				if (exportUV) then
				(
					for ch=1 to numUVsets do
					(
						append vertexData UVcoords[1+(ch-1)*2];
						append vertexData UVcoords[2+(ch-1)*2];
					)
				)
				append verticesArrays[matId] vertexData ;   -- Vertex is added to datas
				
				-- And now, bone assignments. (if a skin modifier is present)
				-- It seems that there are issues when just few vertices have bone assignments.
				-- So there is at least the root assignment.
				if (sk != undefined) then 
				(
					vertexWeightCount = skinOps.getVertexWeightCount sk vertexIndex ; 

					if (vertexWeightCount > 4) then
					(
						if (not g_MAX) then
						(
							format "*** vertex % has more than 4 bones assigned...\n" vertexIndex;	
						)
					)
					
					for k=1 to vertexWeightCount do
					(
						bid = skinOps.getVertexWeightBoneID sk vertexIndex k ;
						bname = skinOps.getBoneName sk bid 1 ;
						bname = replaceSpaces bname;
						vertexWeight = skinOps.getVertexWeight sk vertexIndex k ;
						
						id_bone = findItem BonesList bname;
						if (id_bone != 0) then
							append boneAssignments[matId] #(ogreVertNum-1,id_bone-1,vertexWeight) ;
					)
					-- assignment to the root bone.
					if (vertexWeightCount==0) then 
					(
						-- gets the root Id:
						rootId=getRootsId sk
						rootname = skinOps.getBoneName sk rootId[1] 1 ;
						id_bone = findItem BonesList rootname ;
						if (id_bone != 0) then
							append boneAssignments[matId] #(ogreVertNum-1,id_bone-1,1) ;
					)
				)
				-- same thing with physique modifier if defined
				if (phy != undefined) then 
				(
					vertexWeightCount = physiqueOps.getVertexBoneCount $ vertexIndex ;
					
					if (vertexWeightCount > 4) then
					(
						if (not g_MAX) then
						(
							format "*** vertex % has more than 4 bones assigned...\n" vertexIndex;	
						)
					)
					
					for k=1 to vertexWeightCount do
					(
						bone = physiqueOps.getVertexBone $ vertexIndex k
						vertexWeight = physiqueOps.getVertexWeight $ vertexIndex k
						
						-- search the bone number
						bname = replaceSpaces bone.name;
						id_bone = findItem BonesList bname ;
						if (id_bone!=0)	then				
							append boneAssignments[matId] #(ogreVertNum-1,id_bone-1,vertexWeight) ;
					)
					-- assignment to the first bone if the vertex was not assigned.
					if (vertexWeightCount==0) then 
					(
						-- gets the root Id:
						append boneAssignments[matId] #(ogreVertNum-1,0,1) ;
					)
				)				

			)
		
			ogreFace[localVertexIndex] = ogreVertNum - 1;		
		)
		
		-- flip normal capability
		if (flipNormal) then
		(
			faceTmp = copy ogreFace ;
			ogreFace[2] = faceTmp[3] ;
			ogreFace[3] = faceTmp[2] ;
		)

		if (facesArrays[matId] == undefined) then
			facesArrays[matId] = #() ;		
		append facesArrays[matId] #(ogreFace[1],ogreFace[2],ogreFace[3]) ;   -- Face is added to datas		
	)
)

-------------------------------------------------
-- writes in the mesh.xml file
-- outName : filename
-- exportUV = true if you want to export texture
-- numUVsets : number of UVs sets per vertex to be exported (only relevant if exportUV = true)
-- exportColor = true if you want to export vertices colors
-- material : material used by the mesh
-- Uses the arrays verticesArrays and facesArrays
-------------------------------------------------
function writeM exportUV numUVsets exportColours material outName =
(
	local a,v,f,submatname,hasSkeleton,outFile,hasColours,matId ;
	
	hasSkeleton = false ;
	texCoordString = "" ;
	if (exportUV) then 
	(
		texCoordString = "texture_coords=\"" + (numUVsets as string) + "\" " ;
		for num=1 to numUVsets do
		(
			texCoordString =  texCoordString + "texture_coords_dimensions_" + ((num-1) as string) + "=\"2\" "; -- I really don't care about the W coordinates
		)
	)
	hasColours = "false" ;	
	if (exportColours) then
		hasColours = "true" ;		
	

	-- the final file is created
	if (g_MAX) then
	(
		ClearListener();
		if (g_MAX_use_listener) then
			format("<ogrestartfile>%</ogrestartfile><ogrestartdata>\n") (outName + ".mesh.xml");
		outFile = listener;
	)
	else
	(
		outFile = createfile (outName + ".mesh.xml") ;
	)

	-- writes the header
	format("<mesh>\n") to:outFile ;

	-- submeshes start
	format("\t<submeshes>\n") to:outFile ;
	
	-- for each submesh
	for matId in submeshesId do 
	(
		-- Do we need 32-bit indexes?
		use32bitindexes = "false";
		if arrayLength verticesArrays[matId] > 65535 then
			use32bitindexes = "true";
		
		-- get the name of the sub material if needed.
		submatname = replacespaces material.name ;
		
		if (classof material == MultiMaterial) then
		(
			if (material.materialList[matId]==undefined) then
			(
				msg = "";
				format "You are using in your mesh a material Id (%) that does not exist in your MultiMaterial (%)\nMaterial information won't be properly exported." matId submatname to:msg ;
				messageBox msg;	
			)
			else
			(
		    	submatname  += "/" + replacespaces material.materiallist[matId].name ;
			)
		)
			
									-- HELLO ! --
			---------------------------------------------------------------------------------
			-- IF YOU COME HERE BECAUSE YOUR OBJECT FAILED EXPORTING, MAYBE THAT'S BECAUSE --
			-- YOU USE MATERIAL ID IN YOUR MESH THAT DOESN'T EXIST  IN YOUR MULTIMATERIAL  --
			---------------------------------------------------------------------------------
		
		format("\t\t<submesh material = \"%\" usesharedvertices=\"false\" use32bitindexes=\"%\">\n") submatname use32bitindexes to:outFile ;
	
		if (not g_MAX) then
			format "- writing faces...\n"		
		format("\t\t\t<faces count=\"%\">\n") (arraylength facesArrays[matId]) to:outFile;
		
		-- for each face
		for f in facesArrays[matId] do 
		(
			format("\t\t\t\t<face ") to:outFile ;
			format("v1=\"%\" v2=\"%\" v3=\"%\" />\n") ((int)f[1]) ((int)f[2]) ((int)f[3]) to:outFile ;
		)
		format("\t\t\t</faces>\n") to:outFile ;

		if (not g_MAX) then
			format "- writing vertices...\n"	
		format("\t\t\t<geometry vertexcount=\"%\">\n") (arrayLength verticesArrays[matId] ) to:outFile;
		format("\t\t\t\t<vertexbuffer positions=\"true\" normals=\"true\" colours_diffuse=\"%\" %>\n") hasColours TexCoordString to:outFile ;		
		
		-- for each vertex
		for v in verticesArrays[matId] do
		(	
			format("\t\t\t\t\t<vertex>\n") to:outFile ;
			format("\t\t\t\t\t\t<position x=\"%\" y=\"%\" z=\"%\" />\n") v[1] v[2] v[3] to:outFile ;
			format("\t\t\t\t\t\t<normal x=\"%\" y=\"%\" z=\"%\" />\n") v[4] v[5] v[6] to:outFile ;
			if (exportUV) then
			(
				for ch=1 to numUVsets do
					format("\t\t\t\t\t\t<texcoord u=\"%\" v=\"%\" />\n") v[11+((ch-1)*2)] (1 - v[12+((ch-1)*2)]) to:outFile ;		
			)
			if (exportColours) then 
			(
				color_string = (v[7] as string) + " " + (v[8] as string) + " " + (v[9] as string) + " " +(v[10] as string);
				format("\t\t\t\t\t\t<colour_diffuse value=\"%\" />\n") color_string to:outFile ;
			)
			format("\t\t\t\t\t</vertex>\n") to:outFile ;
		)	
		format("\t\t\t\t</vertexbuffer>\n") to:outFile ;
		format("\t\t\t</geometry>\n") to:outFile ;
					
	
		-- and now bone assignments (and skeleton), if there is at least one element in boneAssignments array.		
		if ((arrayLength boneAssignments[matId]) != 0) then 
		(
			hasSkeleton = true ;
			if (not g_MAX) then
				format "- writing bone assignments...\n"	
			format("\t\t\t<boneassignments>\n") to:outFile ;
				
			for a in boneAssignments[matId] do 
			(
				format("\t\t\t\t<vertexboneassignment vertexindex=\"%\" boneindex=\"%\" weight=\"%\" />\n") a[1] a[2] a[3] to:outFile ;
			)
			format("\t\t\t</boneassignments>\n") to:outFile ;
		)
	
		-- submesh end
		format("\t\t</submesh>\n") to:outFile ;
	)
	
	-- submeshes end
	format("\t</submeshes>\n") to:outFile ;

	-- Skeleton link if there is at least one bone assignement.	
	if (hasSkeleton) then 
	(
		t = filterstring outName "\\" ;
		format ("\t<skeletonlink name=\"%\"/>\n") (t[arrayLength t] + ".skeleton") to:outFile ;				
	)
				
	format("</mesh>\n") to: outFile ;
	
	if (not g_MAX) then
	(
		close outFile ;
	)
	else
	(
		if (g_MAX_use_listener) then
			format("</ogrestartdata>\n") to: outFile;
	)
)


---------------------------------
-- writes the mesh: main function
---------------------------------

function writeMesh pmesh exportOptions out_name =
(
	local m,sk,outFile,message,phy ;

	m = snapshotAsMesh pmesh ;
		
	-- tries to find errors
	message = exploreMesh pmesh exportOptions.exportUV exportOptions.exportColours;
	if (message != "OK") then
	(
		MessageBox ("\n There is a problem with your mesh:\n" + message + "\n\nOperation aborted") ;
		delete m ;
		return false ;
	)
	else
	(			
		format "\n\n"
		format "------------------------------------------\n"
		format "-------   OGRE Mesh Exporter Log   -------\n"
		format "-----                                -----\n"
		
		-- get the skin modifier ( may be undefined )
		-- and physique modifier
		phy = getPhysique pmesh ;
		sk = getSkin pmesh;
		
		if (sk != undefined) then
			format "Skin modifier detected.\n"
			
		if (phy != undefined) then
			format "Physique modifier detected.\n"
					
		-- if not undefined, skin modifier is selected in modifier tab. Or there will be an error.
		if (sk != undefined) then
		(
			-- in order to perform, skin should be opened
			max modify mode ;
			modPanel.setCurrentObject pmesh.modifiers[#Skin] ;		
		)
		
		-- physique
		if (phy != undefined) then
		(
			-- in order to perform, skin should be opened
			max modify mode ;
			modPanel.setCurrentObject pmesh.modifiers[#Physique] ;
			--physiqueOps.setInitialPose pmesh true ;
		)

		OgreExportObject.exportProgress.value = 0;
	
		-- retieving material
		if (pmesh.material != undefined) then (
			materialName = pmesh.material.name ;
			replaceSpaces materialName ;
		)
		else materialName = pmesh.name + "Material" ;
		
		format "Material name exported : \n- %/*** \n" materialName ;
		
		-- retrieving all datas
		format "Retrieving vertices and faces data : \n" ;
	
		getDatas m exportOptions.flipyz exportOptions.scale exportOptions.flipNormal exportOptions.exportUV exportOptions.UVchannels exportOptions.exportColours exportOptions.exportHelpers sk phy;
		
		-- writing in the file
		format "Writing in file %.mesh.xml : \n" out_name ;
		WriteM exportOptions.exportUV exportOptions.UVchannels exportOptions.exportColours pmesh.material out_name ;
		
		if (not g_MAX) then
			format "Export successful.\n"		
		
		delete m ;		
	
		if (not g_MAX) then	
		(
			format "-----                                -----\n"
			format "----------          END          ---------\n"
			format "------------------------------------------\n"
		)
		
		--MessageBox ("Exporting mesh successful !") ;
		
		OgreExportObject.exportProgress.value = 100;
	)
	return true ;
)



