-----------------------------------------------------------------------------
-- gets  keyframes from the controllers animation
-----------------------------------------------------------------------------
function getTimeList obj firstframe lastframe =
(
	local list,rotContr,posContr,  ;
	list = #(firstframe) ;
	list2 = #() ; -- this is the list which will be returned.
	
	-- Biped_Objects and Bones don't have the same properties
	
	-- Biped_Objets
	if (isKindOf obj Biped_Object) then (
		for e in obj.controller.keys do (
			t =e.time ;
			if (t>firstFrame and t<=lastFrame) then
				append list t ;
		)
	)
	-- Bones	
	else (
		rotContr = obj.rotation.controller ;
		posContr = obj.pos.controller ;
		
		for e in rotContr.keys do (
			t = e.time ;
			if (t>firstFrame and t<=lastFrame) then
				append list t ;
		)
		for e in posContr.keys do (
			t = e.time ;
			if (t>firstFrame and t<=lastFrame) then
				append list t ;
		)	
	)
	-- if several keyframes have the same value, we keep just one
	keepLoneValues list list2 ;
	list2 ;
)


-----------------------------------------------------------------------------
-- write <track />
-- Selected keys belongs to [firstframe,lastFrame]
-- time = (key.time - firstFrame)*length/(lastFrame-firstFrame)
--   (e.g. first key has time 0.)
-----------------------------------------------------------------------------

function writeTrack sk boneId firstframe lastframe length scale flipYZ outFile=
(
	local angle,timef,i,bname,d,mref,mparent ;
	
	-- displays information in the maxscript listener
	format "retrieving key information for % ...\n" (skinOps.GetBoneName sk boneId 1) ;
	
	-- gets bone acording to the parameter boneId
	bname= skinOps.GetBoneName sk boneId 1 ;
	replaceSpaces bname ;
	d = getNodeByName bname ;
	
	-- gets keyframe list
	timelist = getTimeList d firstframe lastframe ;
	
	-- track header
	format("\t\t\t\t<track bone = \"%\">\n") (replaceSpaces d.name) to:outFile ;
	format("\t\t\t\t\t<keyframes>\n") to:outFile ;
	
	-- gets initial transform at frame 0f
	at time 0f (
		initTform = d.transform ;
		if (not isRoot d) then (
			mparent = d.parent.transform ;
			initTform = initTform*inverse(mparent) ;
		)
		else if (flipYZ) then (
			format " - flipping root bone track..." ;
			initTform = flipYZTransform initTform ;
		)
	)
		
	-- for each frame in the list
	for i in timelist do
	(
		-- moves slider time and compute OGRE time
		at time i (
			timef = ((float) (i-firstFrame)*length)/(lastframe - firstframe ) ;
			
		-- First, rotation which depends on initial transformation
			Tform = d.transform ;
			-- if this is the root bone
			if (isRoot d) then (
				mparent = matrix3 1 ;
				-- if flipYZ == true
				if (flipYZ) then
					Tform = flipYZTransform Tform ;
			)			
			else
				mparent = d.parent.transform ; 
			
			-- computes rotation
			mref = initTform*mparent ;	
			Tform = Tform*inverse(mref) ;
			
			-- rotation part is saved.
			rot = Tform.rotation as angleaxis ;
			angle = - degToRad (rot.angle) ; -- don't know why there must be this minus :((((((
			
		-- Then, position which depends on parent			
			Tform=d.transform ;
			Tform=Tform*inverse(mparent) ;
			
			-- if this is the root bone and flipYZ == true
			if (isRoot d and flipYZ) then (
				Tform = flipYZTransform Tform ;
			)
			
			-- substracts position of the initial transform
			Tform.pos -= initTform.pos ;
			Tform.pos = Tform.pos * scale ;
			
			pos = Tform.pos ;

				
			-- writes them !
			format("\t\t\t\t\t\t<keyframe time=\"%\">\n") timef to: outFile ;
			format("\t\t\t\t\t\t\t<translate x=\"%\" y=\"%\" z=\"%\" />\n") pos.x pos.y pos.z to: outFile ;
			format("\t\t\t\t\t\t\t<rotate angle=\"%\">\n") angle to:outFile ; 
			format("\t\t\t\t\t\t\t\t<axis x=\"%\" y=\"%\" z=\"%\" />\n") (rot.axis.x) (rot.axis.y) (rot.axis.z) to:outFile ;
			format("\t\t\t\t\t\t\t</rotate>\n") to:outFile ;
			format("\t\t\t\t\t\t</keyframe>\n") to:outFile ;
		)
	)
	
	-- track end
	format("\t\t\t\t\t</keyframes>\n") to:outFile ;
	format("\t\t\t\t</track>\n") d.name to: outFile ;
)


-------------------------------------------------------------------------------------------------
------------------------------------------- WRITE SKELETON --------------------------------------
-------------------------------------------------------------------------------------------------

-- Nota :
-- A vertex 0 and a bone 0 are added because 3dsmax starts with vertex 1 and bone 1.


------------------
-- write <bones />
------------------

function writeB sk id scale flipYZ outFile =
(
	-- gets bone acording to the parameter boneId
	bname= skinOps.GetBoneName sk id 1 ;
	replaceSpaces bname ;
	d = getNodeByName bname ;
	
	-- gets initial transform at frame 0f
	format("\t\t<bone id=\"%\" name=\"%\">\n") id (replaceSpaces d.name) to:outFile ;
	
	slidertime = 0f ;
	Tform = d.transform ;
	if (not isRoot d) then (
		mparent = d.parent.transform ;
		Tform = Tform*inverse(mparent) ;
	)
	
	Tform.pos = Tform.pos * scale ;
		
	if ((isRoot d) and flipYZ) then (
		format "- Flipping root bone... \n" ;
		Tform = flipYZTransform Tform ;
	)
	
	pos = Tform.pos ;
	rot = Tform.rotation as angleaxis ;
	angle = - degToRad (rot.angle) ; -- don't know why there must be this minus :((((((
	
	format("\t\t\t<position x=\"%\" y=\"%\" z=\"%\" />\n") pos.x pos.y pos.z to:outFile ;
    format("\t\t\t<rotation angle=\"%\">\n") angle to:outFile ;
    format("\t\t\t\t<axis x=\"%\" y=\"%\" z=\"%\" />\n") rot.axis.x rot.axis.y rot.axis.z to:outFile ;
   	format("\t\t\t</rotation>\n") to:outFile ;
	format("\t\t</bone>\n") to:outFile ;
)
-----------------------------
-- write Bones (using writeB)
-----------------------------

function writeBones sk scale flipYZ outFile =
(
	local i ;
	
	format("\t<bones>\n") to:outFile;
	
	-- we create a virtual bone number 0.
	format("\t\t<bone id=\"0\" name=\"zzwxy\">\n") to:outFile ;
	format("\t\t\t<position x=\"0\" y=\"0\" z=\"0\" />\n") to:outFile ;
    format("\t\t\t<rotation angle=\"0\">\n") to:outFile ;
    format("\t\t\t\t<axis x=\"1\" y=\"0\" z=\"0\" />\n") to:outFile ;
    format("\t\t\t</rotation>\n") to:outFile ;
	format("\t\t</bone>\n") to:outFile ;
	i = 0 ;
	for i=1 to (skinOps.GetNumberBones sk) do
	(
		writeB sk i scale flipYZ outFile ;
	)
	format("\t</bones>\n") to:outFile;
)

-----------------------------------
-- recursive fun to write hierarchy
-----------------------------------

function writeH b outFile =
(
	if ( b.parent != undefined and (isKindOf b.parent BoneGeometry or iskindOf b.parent Biped_Object)) then
	(
		p = b.parent ;
		format("\t\t<boneparent bone=\"%\" parent=\"%\" />\n") (replaceSpaces b.name) (replaceSpaces p.name) to:outFile ;
	)
	childrenArray = b.children ;
	for i=1 to childrenArray.count do
	(
        if (isKindOf b BoneGeometry or iskindOf b Biped_Object) then
			writeH childrenArray[i] outFile ;
	)
	
)

--------------------------
-- write <bonehierarchy />
--------------------------

function writeHierarchy sk outFile =
(
	format("\t<bonehierarchy>\n") to:outFile ;
	roots = getRoots sk ;
	
	-- ecriture de la track pour le bone 0.
	format("\t\t<boneparent bone=\"zzwxy\" parent=\"%\" />\n") roots[1].name to:outFile ;
	for b in roots do
	(
		writeH b outFile;
	)
	format("\t</bonehierarchy>\n") to:outFile ;
)

-----------------------
-- write <animations />
-----------------------
function writeAnim sk firstFrame lastFrame length scale flipYZ name outFile =
(
	local i,n ;
	
	format("\t<animations>\n") to: outFile ;
    format("\t\t<animation name=\"%\" length=\"%\">\n") name length to:outFile ;
	format("\t\t\t<tracks>\n") to:outFile
	
	-- ecriture track 0
	format("\t\t\t\t<track bone = \"zzwxy\">\n") to: outFile ;
	format("\t\t\t\t\t<keyframes>\n") to:outFile ;
	format("\t\t\t\t\t\t<keyframe  time=\"0\">\n") to:outFile ;
	format("\t\t\t\t\t\t\t<translate x=\"0\" y=\"0\" z=\"0\" />\n") to: outFile ;
	format("\t\t\t\t\t\t\t<rotate angle=\"0\">\n")  to:outFile ; 
	format("\t\t\t\t\t\t\t\t<axis x=\"1\" y=\"0\" z=\"0\" />\n")  to:outFile ;
	format("\t\t\t\t\t\t\t</rotate>\n") to:outFile ;
	format("\t\t\t\t\t\t</keyframe>\n") to:outFile ;
	format("\t\t\t\t\t</keyframes>\n") to:outFile ;
	format("\t\t\t\t</track>\n") to: outFile ;
	
	n = skinOps.GetNumberBones sk ;
	liste = #(0,20,30,40) ;
	for i = 1 to n do
		writeTrack sk i firstframe lastframe length scale flipYZ outFile ;

	format("\t\t\t</tracks>\n") to:outFile					
	format("\t\t</animation>\n") to: outFile ;
	format("\t</animations>\n") to: outFile ;
)

-------------------------------------------------------------
-- write <skeleton /> main function
-- write the animation in the file out_name + ".skeleton.xml"
-- between the frame firstFrame and lastFrame 
-- and scale time according to length
-------------------------------------------------------------

function writeSkeleton pmesh exportOptions out_name = 
(
	local sk,n,keys,initialKeys,messages ;
	sk = getSkin pmesh ;
	
	if (sk == undefined) then
	(
		MessageBox "There is no skin modifier for this object" ;
	)
	else
	(	
		-- in order to perform, skin should be opened
		max modify mode ;
		modPanel.setCurrentObject pmesh.modifiers[#Skin] ;
		
			format "------------------------------------------\n"
			format "------ OGRE skeleton Exporter Log   ------\n"
			format "------------------------------------------\n"
		
			format "Exporter options :\n"
			format "- firstFrame: % \n- lastFrame: %\n" exportOptions.firstFrame exportOptions.lastFrame ;
			-- creates the output file
			outFile = createfile (out_name + ".skeleton.xml") ;

				-- writes header
				format("<skeleton>\n") to:outFile ;	
	
				format "Writing bones :\n" ;
				writeBones sk exportOptions.scale exportOptions.flipYZ outFile ;
				format "Writing bone hierarchy.\n" ;
				writeHierarchy sk outFile ;
				format "Writing bone tracks.\n" ;
				writeAnim sk exportOptions.firstFrame exportOptions.lastFrame exportOptions.length exportOptions.scale exportOptions.flipYZ exportOptions.animName outFile ;

				-- ecriture, fin des balises
				format("</skeleton>\n") to: outFile ;
				
			format "------------------------------------------\n"
			format "----------          END          ---------\n"
			format "------------------------------------------\n"
		
				close outFile ;
				messageBox "Exporting skeleton successful !"
	)
	
)



