function writeMaterial material outFile =
(
	local t, matname, mat;

	mat = material ;
	
	if (mat != undefined) then 
	(
		matname = material.name ;	
		format "3ds/%\n" matname to:outFile ;
		format "{\n" ;
    	format("   ambient % % %\n") (mat.ambient.r/255.0) (mat.ambient.g/255.0) (mat.ambient.b/255.0) to:outFile ;
	    format("   diffuse % % %\n") (mat.diffuse.r/255.0) (mat.diffuse.g/255.0) (mat.diffuse.b/255.0) to:outFile ;
    	format("   specular % % % %\n") (mat.specular.r/255.0) (mat.specular.g/255.0) (mat.specularLevel*100.0) to:outFile ;
		format("   emissive % % % %\n") (mat.selfIllumColor.r/255.0) (mat.selfIllumColor.g/255.0) (mat.selfIllumColor.b/255.0) (mat.selfIllumAmount) to:outFile ;
		
	    -- if mesh has a material: reading the diffuse map:
		if ((mat.diffusemap != undefined) and (iskindof mat.diffusemap Bitmaptexture)) then
		(	
			t = filterstring mat.diffusemap.filename "\\" ;
			format "{\n  texture % \n}" t[arrayLength t] to:outFile ;
		)
		format "}\n" ;
	)
)
