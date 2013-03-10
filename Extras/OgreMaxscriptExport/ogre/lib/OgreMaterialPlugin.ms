-- this is a level 3 plug-in, the beginnings of a custom glass material. 
-- It extends Standard material and replaces its UI with a single 
-- rollout with 2 spinners and a color picker 

plugin material OgreMaterial 
name:"OGRE Material" 
classID:#(695425,446581) 
extends:Standard replaceUI:true version:1 
( 
	parameters main rollout:paramsRollout 
	( 
		ambient type:#color default:blue ui:ambientColor  
		diffuse type:#color default:blue ui:diffuseColor
		specular type:#color default:black ui:specularColor
		selfIllumColor type:#color default:black ui:selfIllumColor
		specularLevel type:#Integer ui:specularLevel
	    diffuseMap type:#texturemap ui:diffuseMap
		
		on ambient set val do delegate.ambient_color = val 
		on diffuse set val do delegate.diffuse_color = val
		on specular set val do delegate.specular_color = val
		on selfIllumColor set val do delegate.self_Illum_color = val
		on specularLevel set val do delegate.specular_level = val
		on diffuseMap set val do delegate.diffuseMap = val
	) 
	
	rollout paramsRollout "OGRE Material Parameters" 
	( 
		colorpicker ambientColor "ambient color: " align:#right 
		colorpicker diffuseColor "diffuse color: " align:#right
		colorpicker specularColor "specular color: " align:#right
		colorpicker selfIllumColor "emissive color: " align:#right
		spinner specularLevel "specular level in %:" range:[0,1000,0] type:#Integer ;
		label l1 "Choose the diffuse map" align:#left;
		mapbutton diffuseMap "" align:#right ;
	) 
	
	on create do 
	( 
		-- setup initial material 
		-- delegate.opacityFalloff = 75 
		delegate.useSelfIllumColor=true ;
		-- delegate.diffuseMapEnable = false ;
	)

) 
