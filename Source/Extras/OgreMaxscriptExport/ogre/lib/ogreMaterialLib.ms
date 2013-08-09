-- write into "outfile" the selected OgreMaterial
-- precondition: iskindof material OgreMAterial == true.
-- Use export OgreMaterial.
function writeOgreMaterial material outname =
(
	local t, matname, mat, ext ;

	mat = material ;
	local outFile ;
	
	if (mat != undefined) then 
	(
		matname = material.name ;
		ext = ".material" ;
		fname = outname +"_"+ matname + ext ;
		outFile = createfile fname ;

		format "<material>\n" to:outFile ;
		
		local tname="NoTexture" ;
		
		if ((material.diffusemap != undefined) and (iskindof material.diffusemap Bitmaptexture)) then
		(
			tname = "Diff" ;
			
			if ((material.bumpMap != undefined) and (iskindof material.bumpMap Bitmaptexture)) then
			(
				tname = tname + "Normal" ;
				
				if (material.specularLevel != 0.0) then
				(
					tname = tname + "Spec" ;
				)
				
				if ((material.opacityMap != undefined) and (iskindof material.opacityMap Bitmaptexture)) then
				(
					tname = tname + "AlphaMask" ;
				)
			)
			else
			(
				if (material.specularLevel != 0.0) then
				(
					tname = tname + "Spec" ;
				)
				if ((material.opacityMap != undefined) and (iskindof material.opacityMap Bitmaptexture)) then
				(
					tname = tname + "AlphaMask" ;
				)
			)
			
			format "    <technique name=\"Techniques/%.xml\" />\n" (tname) to:outFile ;
		)
		else
		(
			if (material.opacity != 100.0) then
			(
				tname = tname + "Alpha" ;
			)
			
			format "    <technique name=\"Techniques/%.xml\" />\n" (tname) to:outFile ;
		)
		
		format "    <parameter name=\"MatDiffColor\" value=\"% % % %\" />\n" (material.diffuse.r/255.0) (material.diffuse.g/255.0) (material.diffuse.b/255.0) ((100-material.opacity)/100.0) to:outFile ;
		format "    <parameter name=\"MatSpecColor\" value=\"% % % %\" />\n" (material.specular.r/255.0) (material.specular.g/255.0) (material.specular.b/255.0) (material.specularLevel*100.0) to:outFile ;
		
		if ((material.diffusemap != undefined) and (iskindof material.diffusemap Bitmaptexture)) then
		(
			t = filterstring material.diffusemap.filename "\\" ;
			format "    <texture unit=\"diffuse\" name=\"textures/%\" />\n" t[arrayLength t] to:outFile ;
		)
		
		if ((material.bumpMap != undefined) and (iskindof material.bumpMap Bitmaptexture)) then
		(
			t = filterstring material.diffusemap.filename "\\" ;
			format "    <texture unit=\"normal\" name=\"textures/%\" />\n" t[arrayLength t] to:outFile ;
		)
		
		if ((material.opacityMap != undefined) and (iskindof material.opacityMap Bitmaptexture)) then
		(
			tname = tname + "AlphaMask" ;
		)
		
		if (material.twoSided == true) then
		(
			format "    <cull value=\"none\" />\n" to:outFile ;
		)
		
		format "</material>\n" to:outFile ;
		close outFile ;
	)
)

function exportOgreMaterial material outName =
(
    local outFile ;
	if (classof material == OgreMaterial or classof material == ogreMaterial) then
	(
	    --outFile = createfile outName ;
		writeOgreMaterial material outname ;
		--close outFile ;
	)
	else
	(
		messageBox "You have to choose an OgreMaterial." ;
	)
)

---------------------------------------------------------------
-- Writes a standard material in a material script
-- prefix will be before material name. (prefix+name)
-- used for multi material
---------------------------------------------------------------
function writeStandardMaterial material outname =
(
	local outFile ;
	local t, matname, mat, ext, fname ;
	
	matname = replaceSpaces material.name ;
	ext = ".material" ;
	fname = outname + "_" + matname + ext ;
	outFile = createfile fname ;
	
	format "<material>\n" to:outFile ;
	
	local tname="NoTexture" ;
	
	if ((material.diffusemap != undefined) and (iskindof material.diffusemap Bitmaptexture)) then
	(
		tname = "Diff" ;
		
		if ((material.bumpMap != undefined) and (iskindof material.bumpMap Bitmaptexture)) then
		(
			tname = tname + "Normal" ;
			
			if (material.specularLevel != 0.0) then
			(
				tname = tname + "Spec" ;
			)
			
			if ((material.opacityMap != undefined) and (iskindof material.opacityMap Bitmaptexture)) then
			(
				tname = tname + "AlphaMask" ;
			)
		)
		else
		(
			if (material.specularLevel != 0.0) then
			(
				tname = tname + "Spec" ;
			)
			if ((material.opacityMap != undefined) and (iskindof material.opacityMap Bitmaptexture)) then
			(
				tname = tname + "AlphaMask" ;
			)
		)
		
		format "    <technique name=\"Techniques/%.xml\" />\n" (tname) to:outFile ;
	)
	else
	(
		if (material.opacity != 100.0) then
		(
			tname = tname + "Alpha" ;
		)
		
		format "    <technique name=\"Techniques/%.xml\" />\n" (tname) to:outFile ;
	)
	
	format "    <parameter name=\"MatDiffColor\" value=\"% % % %\" />\n" (material.diffuse.r/255.0) (material.diffuse.g/255.0) (material.diffuse.b/255.0) ((100-material.opacity)/100.0) to:outFile ;
	format "    <parameter name=\"MatSpecColor\" value=\"% % % %\" />\n" (material.specular.r/255.0) (material.specular.g/255.0) (material.specular.b/255.0) (material.specularLevel*100.0) to:outFile ;
	
	if ((material.diffusemap != undefined) and (iskindof material.diffusemap Bitmaptexture)) then
	(
		t = filterstring material.diffusemap.filename "\\" ;
		format "    <texture unit=\"diffuse\" name=\"textures/%\" />\n" t[arrayLength t] to:outFile ;
	)
	
	if ((material.bumpMap != undefined) and (iskindof material.bumpMap Bitmaptexture)) then
	(
		t = filterstring material.diffusemap.filename "\\" ;
		format "    <texture unit=\"normal\" name=\"textures/%\" />\n" t[arrayLength t] to:outFile ;
	)
	
	if ((material.opacityMap != undefined) and (iskindof material.opacityMap Bitmaptexture)) then
	(
		tname = tname + "AlphaMask" ;
	)
	
	if (material.twoSided == true) then
	(
		format "    <cull value=\"none\" />\n" to:outFile ;
	)
	
	format "</material>\n" to:outFile ;

	close outFile ;
)

---------------------------------------------------------------
-- Exports a standard material
-- PRE: material is a standard material
-- Use exportMaterial function.
---------------------------------------------------------------
function exportStandardMaterial material outname =
(
	local sub,i,matname ;
	matname = replaceSpaces material.name ;
	writeStandardMaterial material outname ;
)


---------------------------------------------------------------
-- Exports a multi material
-- PRE: material is a multi material
-- Use exportMaterial function.
---------------------------------------------------------------
function exportMultiMaterial material outname=
(
	local sub,i,matname ;

	matname = replaceSpaces material.name ;
	
	i=0 ;
	for sub in material.materiallist do 
	(
		i+=1 ;
		writeStandardMaterial sub outname ;
		--format "\n" to:outFile ;
	)
)



---------------------------------------------------------------
-- Exports a material
-- call the fonction linked to the material type
---------------------------------------------------------------
function exportMaterial material outname =
(
	local outFile ;
		
	if (material!=undefined and classof material == MultiMaterial) then
	(
		exportMultiMaterial material outname ;
	)
	else 
	(
		if (material!=undefined and classof material == StandardMaterial) then
		(
			exportStandardMaterial material outname ;
		)
		else
		(
			messageBox "You have to choose a Standard Material or a MultiMaterial." ;
			return 0 ;
		)
	)
	--messageBox "Exporting material successful !" ;
)


---------------------------------------------------------------
-- Exports all the materials used in the scene
---------------------------------------------------------------
function exportAllSceneMaterials outname =
(
	for material in sceneMaterials do
	(			
		if (material!=undefined and classof material == MultiMaterial) then
			exportMultiMaterial material outname ;
		else (
			if (material!=undefined and classof material == StandardMaterial) then
				exportStandardMaterial material outname ;
		)
		format "\n" to:outFile ;
	)		
	-- messageBox "Exporting all materials in the scene successful !" ;
)

