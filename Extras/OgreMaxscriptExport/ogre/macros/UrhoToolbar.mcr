-- ogreToolbar.mcr
--
-- cin - 2013
--
-- Macroscript for the Urho Toolbar 1.0
--
-- Thanks to John Martin and Etienne Mallard for the work they did in the previous versions
--

-- library functions
include "ogre/lib/ogreSkeletonLib.ms"
include "ogre/lib/ogreMaterialLib.ms"
include "ogre/lib/ogreMaterialPlugin.ms"

macroScript showOgreExportTools
	category:"Urho Tools"
	internalCategory:"Urho Tools"
	buttonText:"Urho Exporter"
	tooltip:"Urho Exporter"
	Icon:#("Maintoolbar",49)
(
	-- create a floater
	OgreExportFloater = newRolloutFloater "Urho Ogre Exporter - 1.00" 280 800 ;
	
	rollout OgreExportOptions "Options" width:270 height:140 rolledUp:true
	(
		button openScript "open OgreScript.ini" pos:[7,8] width:116 height:26 toolTip:"open the script to edit your settings"
		checkbox CBconvertXML "convert XML file after export" pos:[8,42] width:255 height:22 checked:true
		label lbl01 "OgreImporter.exe path" pos:[8,64] width:256 height:18
		editText editXMLconverter "" pos:[7,80] width:253 height:23
		button browseXMLconverter "Browse" pos:[188,106] width:72 height:25 toolTip:"choose your OgreImporter.exe"
		groupBox grp1 "Conversion settings" pos:[8,132] width:254 height:125
		checkbox CBgenerateedges "Generate Edges List (for stencil shadows)" pos:[12,145] width:245 height:20 checked:true
		checkbox CBgeneratetangents "Generate Tangent Vectors (for normal mapping)" pos:[12,163] width:245 height:20 checked:false
		checkbox CBgenerateLOD "Generate LOD" pos:[12,181] width:245 height:20 checked:false
		label lbl02 "LOD levels" pos:[30,200] width:156 height:18
		label lbl03 "LOD distance" pos:[30,218] width:156 height:18
		label lbl04 "LOD reduction (%)" pos:[30,236] width:156 height:18
		spinner SPlodlevels "" pos:[120,200] width:114 height:16 range:[1,20,1] type:#integer scale:1 enabled:false
		spinner SPloddistance "" pos:[120,218] width:114 height:16 range:[0.0,100000.0,10.0] type:#float scale:1.0 enabled:false
		spinner SPlodreduction "" pos:[120,236] width:114 height:16 range:[0.0,100.0,20.0] type:#float scale:5.0 enabled:false

		on CBgenerateLOD changed state do
		(
			SPlodlevels.enabled = state;
			SPloddistance.enabled = state;
			SPlodreduction.enabled = state;
		)
		on openScript pressed  do
		(
			shellLaunch ((getDir #scripts) + "\\ogre\\ogreScript.ini") "" ;
		)
		on CBconvertXML changed state do
		(
			if (state and (editXMLconverter.text!="")) then
			(
				if (not (doesFileExist editXMLconverter.text)) then
				(
					editXMLconverter.text = "The file/directory specified in the .ini for the OgreImporter.exe does not exist !";
					CBconvertXML.checked = false;
				)
			)
		)
		on browseXMLconverter pressed  do
		(
			filename = getOpenFileName types:"Executables(*.exe)|*.exe|" ;			
			if (filename != undefined) then
			(
				editXMLconverter.text = filename ;
				CBconvertXML.checked = true;
				if (not (doesFileExist editXMLconverter.text)) then
				(
					editXMLconverter.text = "The file/directory specified in the .ini for the XML converter does not exist !";
					CBconvertXML.checked = false;
				)
				else
				(
					xmlConvPath = getFilenamePath editXMLconverter.text;
					xmlexe = getFilenameFile editXMLconverter.text;
					setINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Directories" "XMLConverterPath" xmlConvPath;
					setINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Exe" "XMLConverterExe" xmlexe;
				)
			)
		)
		on OgreExportOptions open  do
		(
			runXMLConverter = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Tools" "runXMLConverter"
			if (runXMLConverter=="yes") then
			(
				CBconvertXML.enabled = true;
				CBconvertXML.checked = true;
			)
			else
			(
				CBconvertXML.enabled = false;
			)
			
			xmlConvPath = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Directories" "XMLConverterPath"
			xmlexe = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Exe" "XMLConverterExe"
			
			ext = substring xmlexe (xmlexe.count-4) 4;
			if ( (ext[2]!="e" and ext[2]!="E") or (ext[3]!="x" and ext[3]!="X") or (ext[4]!="e" and ext[4]!="E") ) then
				editXMLconverter.text = xmlConvPath + "\\" + xmlexe + ".exe";
			else
				editXMLconverter.text = xmlConvPath + "\\" + xmlexe;

			print editXMLconverter.text;
			if (not (doesFileExist editXMLconverter.text)) then
			(
				editXMLconverter.text = "The file/directory specified in the .ini for the OgreImporter.exe does not exist !";
				CBconvertXML.checked = false;
			)
			else
			(
				CBconvertXML.checked = true;
			)
		)
		on OgreExportOptions close  do
		(
		
		)		
	)

	rollout OgreExportObject "Object" width:270 height:259
	(
		label lbl01 "Selected Object :" pos:[6,35] width:260 height:17
		editText editObject "" pos:[0,51] width:263 height:20
		button selectMesh "Select a mesh..." pos:[115,2] width:152 height:28 toolTip:"select the mesh you want to export"
		spinner SPscale "Scale" pos:[149,75] width:114 height:16 range:[0.0,1000.0,1.0] type:#float scale:0.1
		checkbox CBFlipYZ "Flip Y/Z" pos:[203,96] width:60 height:19 checked:true
		groupBox grp1 "Output" pos:[8,112] width:254 height:75
		label lbl03 "File name" pos:[17,125] width:238 height:17
		editText editFilename "" pos:[11,140] width:242 height:22
		button chooseFilename "Browse" pos:[170,164] width:82 height:20 toolTip:"chooose the name of your output files"
		button export "Export !" pos:[29,191] width:214 height:40 toolTip:"export your mesh, skeleton ......"
		progressBar exportProgress pos:[9,235] width:250 height:10
		
		on OgreExportObject open  do
		(
			if (maxOps.productAppID == #max) then	
				g_MAX = false;
			else
				g_MAX = true;
			
			lastFile = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastFile"
			lastAnimName = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastAnimName"
			lastfirstFrame = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastFrameStart"
			lastlastFrame = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastFrameEnd"
			lastAnimLength = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastAnimLength"
			lastScale = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastScale"
			
			editFilename.text = lastFile ;
			OgreExportMesh.CBexportUV.checked = true ;
			CBFlipYZ.checked = true ;
			SPscale.value = lastScale as Float;
			if (SPscale.value == 0.0) then
				SPscale.value = 1.0;

			select = getCurrentSelection() ;
			if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
			(
				editObject.text = select[1].name ;
				OgreExportMesh.CBexportMesh.enabled = true;
				OgreExportMesh.CBexportMesh.checked = true;
				OgreExportMesh.CBflipnormals.enabled = true ;
				OgreExportMesh.CBexportColor.enabled = true ;
				OgreExportMesh.CBexportUV.enabled = true ;
				OgreExportMesh.CBexportUV.checked = true ;
				OgreExportMesh.SPchannels.enabled = true ;
				OgreExportAnimation.CBexportSkeleton.enabled = (getSkin(select[1]) != undefined) or (getPhysique(select[1]) != undefined) ;
			)
		)
		on OgreExportObject close  do
		(
		
		)
		on selectMesh pressed do
		(
			max tool hlist ;
			select = getCurrentSelection() ;
			if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
			(
				editObject.text = select[1].name ;
			
				-- options accessible ou non
				OgreExportMesh.CBexportMesh.enabled = true;
				OgreExportMesh.CBexportMesh.checked = true;
				OgreExportMesh.CBflipnormals.enabled = true ;
				OgreExportMesh.CBexportColor.enabled = true ;
				OgreExportMesh.CBexportUV.enabled = true ;
				OgreExportMesh.CBexportUV.checked = true ;
				OgreExportMesh.SPchannels.enabled = true ;
				OgreExportAnimation.CBexportSkeleton.enabled = (getSkin(select[1]) != undefined) or (getPhysique(select[1]) != undefined) ;
			)
		)
		on chooseFilename pressed  do
		(
			filename = getSaveFileName types:"All Files(*.*)|*.*|" ;			
			if (filename != undefined) then
			(
				editFilename.text = filename ;
			)
		)
		
		-------------------------------------
		-- EXPORT ---------------------------
		-------------------------------------
		on export pressed  do
		(
			sliderTime = 0 ;
			m = getNodeByName editObject.text ;
			if (editFilename.text == "" or m == undefined ) then
			(
				messageBox "You have to choose a filename and a valid object." ;
			)
			else
			(
				clearlistener() ;
				
				if (SPscale.value == 0.0) then
					SPscale.value = 1.0;
				
				Options = exportOptions scale:SPscale.value flipYZ:false flipNormal:false exportColours:false exportUV:false ;
				exportingMeshDone = false ;
				exportingSkelDone = false ;
				-- sets options
				---------------
				if (CBFlipYZ.checked) then
					Options.flipYZ= true ;					
				if (OgreExportMesh.CBflipnormals.checked and OgreExportMesh.CBflipnormals.enabled) then
					Options.flipNormal = true ;
				if (OgreExportMesh.CBexportColor.checked and OgreExportMesh.CBexportColor.enabled) then
					Options.exportColours = true ;
				if (OgreExportMesh.CBexportUV.checked and OgreExportMesh.CBexportUV.enabled) then
				(
					Options.exportUV = true ;	
					Options.UVchannels = OgreExportMesh.SPchannels.value;	
				)
				Options.exportHelpers = (OgreExportAnimation.CBexporthelpers.enabled and OgreExportAnimation.CBexporthelpers.checked);
				
				if (not g_MAX) then
					setINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastScale" (SPscale.value as string)

				-- exports mesh
				---------------
				if (OgreExportMesh.CBexportMesh.enabled and OgreExportMesh.CBexportMesh.checked) then
				(
					if (not g_MAX) then
						setINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Settings" "lastFile" editFilename.text	
					--progressStart "Mesh Export" ;
					exportingMeshDone = writeMesh m Options (editFilename.text) ;
					--progressStop ;
				)
			
				-- exports skeleton
				-------------------
				if (OgreExportAnimation.CBexportSkeleton.enabled and OgreExportAnimation.CBexportSkeleton.checked) then
				(
					Options.sampleRate = OgreExportAnimation.SPsamplerate.value ;
					Options.ikSampleRate = OgreExportAnimation.SPiksamplerate.value ;
				
					exportingSkelDone =	writeSkeleton m Options Anims editFilename.text ;
				)
				
				-- exports material
				if (OgreExportMaterial.CBexportmaterial.enabled and OgreExportMaterial.CBexportmaterial.checked) then
				(
					select = getCurrentSelection() ;
					if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
					(
						mat = select[1].material
						if (exportSomeMaterial!=undefined) then		-- export with Octopus functions
						(
							local outFile ;
							if (not g_MAX) then
							(
								outFile = createfile (editFilename.text + ".material");
							)
							else
							(
								ClearListener();
								if (g_MAX_use_listener) then
									format("<ogrestartfile>%</ogrestartfile><ogrestartdata>\n") (editFilename.text + ".material");
								outFile = listener;
							)

							exportSomeMaterial mat "" outFile;

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
						else
						(
							exportMaterial mat (editFilename.text);
						)
					)
				)
				
				-- post traitement
				------------------
				if (exportingMeshDone or exportingSkelDone) then 
				(					
					if (OgreExportOptions.CBconvertXML.checked) then
					(
						if (not g_MAX) then
						(
							OptionConv = "";
							mediaPath = getINISetting ((getDir #scripts) + "\\ogre\\ogreScript.ini") "Directories" "MediaPath"
					
							if (exportingMeshDone) then 
							(
								--if (OgreExportOptions.CBgenerateedges.enabled==false or OgreExportOptions.CBgenerateedges.checked==false) then
								--	OptionConv = OptionConv + " -e";
								--if (OgreExportOptions.CBgeneratetangents.enabled and OgreExportOptions.CBgeneratetangents.checked) then
								--(
									--if (OgreExportMesh.CBexportUV.enabled and OgreExportMesh.CBexportUV.checked and (OgreExportMesh.SPchannels.value>0)) then
									--	OptionConv = OptionConv + " -t";
									--else
									--	messageBox "Tangent vectors cannot be generated without UV sets. Generation will be deactivated." ;
								--)
								--if (OgreExportOptions.CBgeneratelod.enabled and OgreExportOptions.CBgeneratelod.checked) then
								--	OptionConv = OptionConv + " -l " + (OgreExportOptions.SPlodlevels.value as string) + " -d " + (OgreExportOptions.SPloddistance.value as string) + " -p " + (OgreExportOptions.SPlodreduction.value as string);
								
								print (OgreExportOptions.editXMLconverter.text +       " \"" + editFilename.text + ".mesh.xml\" \"" + editFilename.text + ".mdl\"") ;								
								DOSCommand (OgreExportOptions.editXMLconverter.text +  " \"" + editFilename.text + ".mesh.xml\" \"" + editFilename.text + ".mdl\"") ;
								--DOSCommand ("copy \"" + editFilename.text + ".mesh\" \"" + mediaPath + "\"") ;
							)
							--if (exportingSkelDone) then 
							--(
								--DOSCommand (OgreExportOptions.editXMLconverter.text + " \"" + editFilename.text + ".skeleton.xml\" \"" + editFilename.text + ".skeleton\"") ;
								--DOSCommand ("copy \"" + editFilename.text + ".skeleton\" \"" + mediaPath + "\"") ;						
							--)
							--messageBox "OgreXMLConverter has been run and files copied to the media directory."

						)
					)
				)
			)
		)
	)
	
	rollout OgreExportMesh "Mesh" width:270 height:120
	(
		checkbox CBexportMesh "Export Mesh" pos:[5,5] width:150 height:17
		groupBox grp2 "Export settings" pos:[4,25] width:262 height:102
		checkbox CBflipnormals "Flip normals" pos:[14,42] width:140 height:19
		checkbox CBexportUV "Export UV sets" pos:[14,64] width:140 height:20
		spinner SPchannels "# UV channels" pos:[36,85] width:173 height:16 range:[1,8,1] type:#integer scale:1
		checkbox CBexportColor "Export Vertex Color" pos:[13,105] width:140 height:19
		on OgreExportMesh open  do
		(
			OgreExportMesh.CBexportMesh.enabled = false;
			OgreExportMesh.CBexportMesh.checked = true;
			OgreExportMesh.CBflipnormals.enabled = false ;
			OgreExportMesh.CBexportColor.enabled = false ;
			OgreExportMesh.CBexportUV.enabled = false ;
			OgreExportMesh.CBexportUV.checked = true ;
			OgreExportMesh.SPchannels.enabled = false ;

			select = getCurrentSelection() ;
			if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
			(
				OgreExportMesh.CBexportMesh.enabled = true;
				OgreExportMesh.CBexportMesh.checked = true;
				OgreExportMesh.CBflipnormals.enabled = true ;
				OgreExportMesh.CBexportColor.enabled = true ;
				OgreExportMesh.CBexportUV.enabled = true ;
				if (classof select[1] == Editable_Mesh) then
				(
					if (getNumTVerts select[1] == 0) then
						OgreExportMesh.CBexportUV.checked = false ;
					else
						OgreExportMesh.CBexportUV.checked = true ;
				)
				else
				(
					OgreExportMesh.CBexportUV.checked = false ;
				)
				OgreExportMesh.SPchannels.enabled = true ;
			)
		)
		on OgreExportMesh close  do
		(
		
		)
		on CBexportMesh changed state do
		(
			OgreExportMesh.CBflipnormals.enabled = state ;
			OgreExportMesh.CBexportColor.enabled = state ;
			OgreExportMesh.CBexportUV.enabled = state ;
			OgreExportMesh.SPchannels.enabled = state ;
		)
		on CBexportUV changed state do
		(
			SPchannels.enabled = state ;
		)
		on SPchannels changed state do
		(
			name = OgreExportObject.editObject.text;
			replaceSpaces name;
			d = getNodeByName name ;
			num_channels = (meshOp.getNumMaps d) - 1;
			if (state > num_channels) then
				SPchannels.value = num_channels;
		)
	)
	
	rollout OgreExportAnimation "Animation" width:270 height:347 rolledUp:true
	(
		checkbox CBexportSkeleton "Export Skeleton" pos:[5,4] width:150 height:19 enabled:false
		groupBox grp3 "Export settings" pos:[4,26] width:262 height:76
		--checkbox CBbiped "Biped Export" pos:[13,44] width:246 height:19 enabled:false
		spinner SPsamplerate "Sample Rate" pos:[11,45] width:186 height:16 enabled:false range:[0.0,10000,0.0] type:#float scale:0.5 
		spinner SPiksamplerate "IK Sample Rate" pos:[17,63] width:180 height:16 enabled:false range:[0.0,10000,5.0] type:#float scale:0.5 
		checkbox CBexporthelpers "Export non-bones objects (must be in the modifier)" pos:[11,81] width:254 height:16 enabled:false checked:false
		groupBox grp4 "Animation settings" pos:[4,106] width:261 height:252
		button getFromModifier "<-" pos:[14,124] width:61 height:21 enabled:false toolTip:"retrieve information from OctopusExport Modifier"
		label lbl4 "Get settings from Octopus modifier" pos:[86,128] width:167 height:14 enabled:true
		groupBox grp5 "Animations" pos:[8,149] width:253 height:203
		button addAnimation "Add" pos:[16,164] width:80 height:22 enabled:false toolTip:"add an animation to the list"
		button deleteAnimation "Delete" pos:[172,165] width:80 height:22 enabled:false toolTip:"remove an animation from the list"
		comboBox ListAnimations "" pos:[17,191] width:235 height:6 enabled:false
		label lbl5 "Frames" pos:[17,290] width:236 height:16
		spinner SPframestart "from" pos:[25,307] width:106 height:16 enabled:false range:[0,10000,0] type:#integer scale:1
		spinner SPframeend "to" pos:[154,307] width:96 height:16 enabled:false range:[0,10000,100] type:#integer scale:1
		label lbl6 "Length (in seconds)" pos:[18,330] width:115 height:16
		spinner SPanimlength "" pos:[120,329] width:130 height:16 range:[0,10000,10] type:#float scale:0.1
		on OgreExportAnimation open  do
		(
			OgreExportAnimation.CBexportSkeleton.enabled = false;
			--OgreExportAnimation.CBbiped.enabled = false;
			--OgreExportAnimation.CBbiped.checked = false;
			OgreExportAnimation.getFromModifier.enabled = false;
			OgreExportAnimation.SPsamplerate.enabled = false;
			OgreExportAnimation.SPiksamplerate.enabled = false;
			OgreExportAnimation.CBexporthelpers.enabled = false;
			OgreExportAnimation.addAnimation.enabled = false;
			OgreExportAnimation.deleteAnimation.enabled = false;
			OgreExportAnimation.ListAnimations.enabled = false;
			OgreExportAnimation.SPframestart.enabled = false;
			OgreExportAnimation.SPframeend.enabled = false;
			OgreExportAnimation.SPanimlength.enabled = false;

			select = getCurrentSelection() ;
			if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
			(
				OgreExportAnimation.CBexportSkeleton.enabled = (getSkin(select[1]) != undefined) or (getPhysique(select[1]) != undefined) ;
				if (OgreExportAnimation.CBexportSkeleton.enabled and OgreExportAnimation.CBexportSkeleton.checked) then
				(
					--OgreExportAnimation.CBbiped.enabled = true;
					--OgreExportAnimation.CBbiped.checked = (getPhysique(select[1]) != undefined);
					OgreExportAnimation.getFromModifier.enabled = true;
					OgreExportAnimation.SPsamplerate.enabled = true;
					OgreExportAnimation.SPiksamplerate.enabled = true;
					OgreExportAnimation.CBexporthelpers.enabled = true;
					OgreExportAnimation.addAnimation.enabled = true;
					OgreExportAnimation.deleteAnimation.enabled = true;
					OgreExportAnimation.ListAnimations.enabled = true;
					OgreExportAnimation.SPframestart.enabled = true;
					OgreExportAnimation.SPframeend.enabled = true;
					OgreExportAnimation.SPanimlength.enabled = true;
				)
			)
			
			Anims = exportAnims names:#() startframes:#() endframes:#() lengths:#();
		)
		--on CBbiped changed state do
		--(
		--)
		on CBexportSkeleton changed state do
		(
			select = getCurrentSelection() ;
			if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
			(
				--OgreExportAnimation.CBbiped.enabled = state;
				--OgreExportAnimation.CBbiped.checked = (getPhysique(select[1]) != undefined);
				OgreExportAnimation.getFromModifier.enabled = state;
				OgreExportAnimation.SPsamplerate.enabled = state;
				OgreExportAnimation.SPiksamplerate.enabled = state;
				OgreExportAnimation.CBexporthelpers.enabled = state;
				OgreExportAnimation.addAnimation.enabled = state;
				OgreExportAnimation.deleteAnimation.enabled = state;
				OgreExportAnimation.ListAnimations.enabled = state;
				OgreExportAnimation.SPframestart.enabled = state;
				OgreExportAnimation.SPframeend.enabled = state;
				OgreExportAnimation.SPanimlength.enabled = state;
			)
		)
		on OgreExportAnimation close  do
		(
		
		)
		on getFromModifier pressed  do
		(
			select = getCurrentSelection()
			if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
			(
				max modify mode ;
				--if (select[1].modifiers["OctopusExport"]!=undefined) then
				--	modPanel.setCurrentObject select[1].modifiers["OctopusExport"] ;
				octexp = getOctopusExport select[1];
				
				if (octexp!=undefined) then
				(
					local array=#();
					for n in octexp.anames do
						append array n;
					
					ListAnimations.items = array;
					ListAnimations.selection = 1;

					Anims.names = array;
					
					array=#();
					for n in octexp.afframes do
						append Anims.startframes n;

					array=#();
					for n in octexp.alframes do
						append Anims.endframes n;
					
					array=#();
					for n in octexp.artimes do
						append Anims.lengths n;

					if (ListAnimations.items.count!=0) then
					(
						SPframestart.value = Anims.startframes[1]
						SPframeend.value = Anims.endframes[1]
						SPanimlength.value = Anims.lengths[1]
					)
				)
			)
		)
		on addAnimation pressed  do
		(
			if (ListAnimations.text != "") then
			(
				local array=#();
				for n in ListAnimations.items do
					append array n;
				append array ListAnimations.text;
				ListAnimations.items = array;
				append Anims.names ListAnimations.items[ListAnimations.items.count];
				append Anims.startframes SPframestart.value;
				append Anims.endframes SPframeend.value;
				append Anims.lengths SPanimlength.value;
				ListAnimations.selection = 0;
			)		
		)
		on deleteAnimation pressed  do
		(
			if ((ListAnimations.items.count > 0) and (ListAnimations.selection > 0)) then
			(
				local array=#();
				ind = ListAnimations.selection
				deleteItem Anims.names ind
				deleteItem Anims.startframes ind
				deleteItem Anims.endframes ind
				deleteItem Anims.lengths ind
				for n in Anims.names do
					append array n;
				ListAnimations.items = array;
				ListAnimations.selection = 1;
			)
		)
		on ListAnimations selected num  do
		(
			if (ListAnimations.items.count >= num) then
			(
				SPframestart.value = Anims.startframes[num]
				SPframeend.value = Anims.endframes[num]
				SPanimlength.value = Anims.lengths[num]
			)		
		)
		on SPframestart changed val do
		(
			if ((ListAnimations.items.count > 0) and (ListAnimations.selection > 0)) then
			(
				if (ListAnimations.text == Anims.names[ListAnimations.selection]) then
					Anims.startframes[ListAnimations.selection] = SPframestart.value;
			)		
		)
		on SPframeend changed val do
		(
			if ((ListAnimations.items.count > 0) and (ListAnimations.selection > 0)) then
			(
				if (ListAnimations.text == Anims.names[ListAnimations.selection]) then
					Anims.endframes[ListAnimations.selection] = SPframeend.value;
			)		
		)
		on SPanimlength changed val do
		(
			if ((ListAnimations.items.count > 0) and (ListAnimations.selection > 0)) then
			(
				if (ListAnimations.text == Anims.names[ListAnimations.selection]) then
					Anims.lengths[ListAnimations.selection] = SPanimlength.value;
			)		
		)
	)
	
	rollout OgreExportMaterial "Material" width:270 height:33
	(
		checkbox CBexportmaterial "Export Material" pos:[5,7] width:260 height:17 enabled:false checked:true
		on OgreExportMaterial open  do
		(
			CBexportmaterial.enabled = false;

			select = getCurrentSelection() ;
			if ((select[1]!=undefined) and (iskindof select[1] GeometryClass)) then
			(
				CBexportmaterial.enabled = true;
			)		
		)
		on OgreExportMaterial close  do
		(
		
		)
	)
	
	rollout OgreExportAbout "About" rolledUp:true
	(
		label label11 "For use with the Urho graphics engine." align:#center;
		label label12 "See website for details: http://code.google.com/p/urho3d/" align:#center;
		label label13 "This software is distributed under the terms of the LGPL." align:#center ;
		label label16 "Based on the exporter realised by" align:#center ;
		label label14 "EarthquakeProof - mallard@iie.cnam.fr 2003 and Banania - 2004" align:#center ;
		label label15 "cin - March 2013" align:#center ;	
	)
	
	-- add the rollout, which contains the dialog	
	addRollout OgreExportOptions OgreExportFloater ;
	addRollout OgreExportObject OgreExportFloater ;
	addRollout OgreExportMesh OgreExportFloater ;
	addRollout OgreExportAnimation OgreExportFloater ;
	addRollout OgreExportMaterial OgreExportFloater ;
	addRollout OgreExportAbout OgreExportFloater ;
)
