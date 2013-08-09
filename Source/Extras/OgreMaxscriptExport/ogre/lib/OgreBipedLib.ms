include "ogre/lib/ogreSkeletonLib_usefulfns.ms"

-----------------------------------------------------------------------------
-- gets  keyframes from the controllers animation
-----------------------------------------------------------------------------
function getTimeList obj firstframe lastframe samplerate IKsamplerate =
(
	local list,rotContr,posContr,e  ;
	list = #(firstframe) ;
	list2 = #() ; -- this is the list which will be returned.
	
	-- Biped Bones and the root: Bip01 for example don't have the same controller
	
	-- Root : Bip01
	if (isPelvis obj) then (
		-- vertical controller
		for e in obj.controller.vertical.controller.keys do (
			t =e.time ;
			if (t>firstFrame and t<=lastFrame) then (
				append list t ;
				--print t ;	
			)
		)
		-- horizontal controller
		for e in obj.controller.horizontal.controller.keys do (
			t =e.time ;
			if (t>firstFrame and t<=lastFrame) then
				append list t ;
		)
		-- turn controller
		for e in obj.controller.turning.controller.keys do (
			t =e.time ;
			if (t>firstFrame and t<=lastFrame) then
				append list t ;
		)
		sort list ;
	)
	-- Biped Bones
	else if (isKindOf obj Biped_Object) then (
		
		for e in obj.controller.keys do (
			t =e.time ;
			if (t>firstFrame and t<=lastFrame) then
				append list t ;
		)
	)
	-- Standard Bones
	else 
	(
		--print obj.name;
		--print (classof obj.controller) ;
		if (classof obj.controller == prs) then		-- standard controller
		(
			rotContr = obj.rotation.controller ;
			posContr = obj.pos.controller ;
		
			for e in rotContr.keys do 
			(
				t = e.time ;
				if (t>firstFrame and t<=lastFrame) then
					append list t ;
			)
			for e in posContr.keys do 
			(
				t = e.time ;
				if (t>firstFrame and t<=lastFrame) then
					append list t ;
			)	
		)
		else if ((classof obj.controller == IK_ControllerMatrix3Controller) or (classof obj.controller == IKControl)) then		-- IK controller
		(
			local IKSR = IKsamplerate;
			
			if (IKSR == 0.0) then
				IKSR = 1.0;
			
			i=firstFrame as Float;
			while (i<=lastFrame) do
			(
				append list (i as Float);			
				i = i + IKSR;
			)
		)
	)

	append list (firstFrame as Float);		-- add a keyframe on the first frame
	append list (lastFrame as Float);		-- add a keyframe on then last frame

	if (samplerate > 0) then				-- sample the animation by adding keyframes on regular intervals
	(
		i=firstFrame as Float;
		while (i<=lastFrame) do
		(
			append list (i as Float);			
			i = i + samplerate;
		)
	)
	sort list ;
	
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
function writeTrack bone_name boneId firstframe lastframe samplerate IKsamplerate length scale flipYZ outFile=
(
	local angle,timef,i,bname,d,mref,mparent ;
	
	-- displays information in the maxscript listener
	if (not g_MAX) then
		format "retrieving key information for % ...\n" (bone_name) ;

	-- gets bone acording to the parameter boneId
	bname = bone_name ;
	replaceSpaces bname ;
	d = getNodeByName bname ;
	
	-- gets keyframe list
	timelist = getTimeList d firstframe lastframe samplerate IKsamplerate;
	
	-- track header
	format("\t\t\t\t<track bone = \"%\">\n") bname to:outFile ;
	format("\t\t\t\t\t<keyframes>\n") to:outFile ;
	
	-- gets initial transform at frame 0f
	at time 0f (
		initTform = d.transform ;
		if (not isRootUniversal2 d) then (
			mparent = d.parent.transform ;
			initTform = initTform*inverse(mparent) ;
		)
		else if (flipYZ) then (
			if (not g_MAX) then
				format " - flipping root track..." ;
			-- we add the bip Transform
			--initTform = initTform * d.controller.rootNode.transform ;
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
			-- if this is the pelvis
			if (isRootUniversal2 d) then (
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
			--rot = Tform.rotation as angleaxis ;
			--angle = - degToRad (rot.angle) ; -- don't know why there must be this minus :((((((
			rot = toAngleAxis Tform.rotation ;
			axis = rot.axis;
			angle = - rot.angle;
			
			-- Then, position which depends on parent			
			Tform=d.transform ;
			Tform=Tform*inverse(mparent) ;
			
			-- if this is the root bone and flipYZ == true
			if (isRootUniversal2 d and flipYZ) then (
				Tform = flipYZTransform Tform ;
			)
			
			-- substracts position of the initial transform
			Tform.pos -= initTform.pos ;
			Tform.pos = Tform.pos * scale ;
			
			pos = Tform.pos ;

			-- writes them !
			if (abs(pos.x)<1e-5) then pos.x = 0 ;
			if (abs(pos.y)<1e-5) then pos.y = 0 ;
			if (abs(pos.z)<1e-5) then pos.z = 0 ;
			
			format("\t\t\t\t\t\t<keyframe time=\"%\">\n") timef to: outFile ;
			format("\t\t\t\t\t\t\t<translate x=\"%\" y=\"%\" z=\"%\" />\n") pos.x pos.y pos.z to: outFile ;
			format("\t\t\t\t\t\t\t<rotate angle=\"%\">\n") angle to:outFile ; 
			format("\t\t\t\t\t\t\t\t<axis x=\"%\" y=\"%\" z=\"%\" />\n") (axis.x) (axis.y) (axis.z) to:outFile ;
			format("\t\t\t\t\t\t\t</rotate>\n") to:outFile ;
			format("\t\t\t\t\t\t</keyframe>\n") to:outFile ;
		)
	)
	
	-- track end
	format("\t\t\t\t\t</keyframes>\n") to:outFile ;
	format("\t\t\t\t</track>\n") to: outFile ;
)

-------------------------------------------------------------------------------------------------
------------------------------------------- WRITE SKELETON --------------------------------------
-------------------------------------------------------------------------------------------------

-------------------------------------
-- List of bones in the hierarchy
-------------------------------------
global BonesList=#()
global RootsList=#()

-------------------------------------
-- helper functions to build skeleton
-------------------------------------

-----------------------------------------------------------------
-- recursive function to build the list of bones for the skeleton
-----------------------------------------------------------------
function computeBList b sk phy exportHelpers =
(
	bname = b ;
	bone = getNodeByName bname ;
	if (findItem BonesList bname == 0) then
		if (isKindOf bone BoneGeometry or iskindOf bone Biped_Object or (exportHelpers and (isPartOfModifier bone sk phy)) ) then
			append BonesList bname ;
	childrenArray = bone.children ;
	for i=1 to childrenArray.count do
	(
        if (isKindOf bone BoneGeometry or iskindOf bone Biped_Object or (exportHelpers and (isPartOfModifier bone sk phy))) then
			computeBList (replaceSpaces childrenArray[i].name) sk phy exportHelpers;
	)
)

function addHelpersToHierarchy phy sk =
(
	if (sk != undefined) then
	(
		for i=1 to (skinOps.GetNumberBones sk) do
		(
			bname = skinOps.GetBoneName sk i 1 ;
			replaceSpaces bname ;
			d = getNodeByName bname ;

			if (iskindof d helper) then
				append BonesList bname ;
		)	
	)
	else if (phy != undefined) then
	(
		for i=1 to (physiqueOps.GetBoneCount $) do
		(
			bname = (physiqueOps.GetBones $)[i].name;
			replaceSpaces bname ;
			d = getNodeByName bname ;
		
			if (iskindof d helper) then
				append BonesList bname ;
		)	
	)
)

-----------------------------------------------------------------
-- find the root(s) of the rhierarchy
-----------------------------------------------------------------
function getHierarchyRoots phy sk exportHelpers =
(
	local rootstab=#();
	
	if (sk != undefined) then
	(
		for i=1 to (skinOps.GetNumberBones sk) do
		(
			bname= skinOps.GetBoneName sk i 1 ;
			replaceSpaces bname ;
			d = getNodeByName bname ;
		
			while (d.parent!=undefined and (iskindof d.parent BoneGeometry or iskindOf d.parent Biped_Object or (exportHelpers and (isPartOfModifier d.parent sk phy)) )) do
			(
				d = d.parent
			)
			trouve = 0;
			--format("new potential root bone \"%\"\n") (replaceSpaces d.name) ;
			for j=1 to rootstab.count do
			(
				if (rootstab[j]!=undefined and (rootstab[j]==(replaceSpaces d.name)))then
				(
					trouve = 1;
					exit;
				)
			)
			if trouve==0 then
			(
				if (iskindof d BoneGeometry or iskindOf d Biped_Object or (exportHelpers and (isPartOfModifier d sk phy)) ) then
				(
					if (not g_MAX) then
						format("new root bone \"%\"\n") (replaceSpaces d.name) ;
					rootstab[rootstab.count+1] = (replaceSpaces d.name) ;
				)
			)
		)
	)
	else if (phy != undefined) then		-- physique modifier
	(
		for i=1 to (physiqueOps.GetBoneCount $) do
		(
			bname = (physiqueOps.GetBones $)[i].name;
			replaceSpaces bname ;
			d = getNodeByName bname ;
		
			while (d.parent!=undefined and (iskindof d.parent BoneGeometry or iskindOf d.parent Biped_Object  or (exportHelpers and (isPartOfModifier d.parent sk phy)) )) do
			(
				d = d.parent
			)
			trouve = 0;
			--format("new potential root bone \"%\"\n") (replaceSpaces d.name) ;
			for j=1 to rootstab.count do
			(
				if (rootstab[j]!=undefined and (rootstab[j]==(replaceSpaces d.name)))then
				(
					trouve = 1;
					exit;
				)
			)
			if trouve==0 then
			(
				if (iskindof d BoneGeometry or iskindOf d Biped_Object or (exportHelpers and (isPartOfModifier d sk phy))) then
				(
					if (not g_MAX) then
						format("new root bone \"%\"\n") (replaceSpaces d.name) ;
					rootstab[rootstab.count+1] = (replaceSpaces d.name) ;
				)
			)
		)
	)
	
	rootstab;
)

-----------------------------------------------------------------
-- function to build the list of bones for the skeleton
-----------------------------------------------------------------
function computeBonesList phy sk exportHelpers =
(
	RootsList = getHierarchyRoots phy sk exportHelpers;	-- find the roots of the current hierarchy
	print RootsList;
	for b in RootsList do
	(
		computeBList b sk phy exportHelpers;
	)
	
	-- add the nodes that are parts of the skin (or physique) modifier but are neither biped_object nor standard bones
	-- only helpers (Point, Dummy) at the moment...
	-- addHelpersToHierarchy phy sk ;
)

------------------
-- write <bones />
------------------
function writeB bone_name id scale flipYZ outFile =
(
	-- gets bone acording to the parameter boneId
	bname = bone_name ;
	replaceSpaces bname;
	d = getNodeByName bname ;
	
	-- gets initial transform at frame 0f
	format("\t\t<bone id=\"%\" name=\"%\">\n") (id-1) bname to:outFile ;

	slidertime = 0f ;
	Tform = d.transform ;
	if (not isRootUniversal2 d) then (
		mparent = d.parent.transform ;
		Tform = Tform*inverse(mparent) ;
	)
	
	Tform.pos = Tform.pos * scale ;
		
	if ((isRootUniversal2 d) and flipYZ) then (
		if (not g_MAX) then
			format "- Flipping root... \n" ;
		Tform = flipYZTransform Tform ;
	)
	
	pos = Tform.pos ;
	--rot = Tform.rotation as angleaxis ;
	--angle = - degToRad (rot.angle) ; -- don't know why there must be this minus :((((((
	rot = toAngleAxis Tform.rotation ;
	angle = - rot.angle ;
		
	--		if (abs(pos.x)<1e-5) then pos.x = 0 ;
	--		if (abs(pos.y)<1e-5) then pos.y = 0 ;
	--		if (abs(pos.z)<1e-5) then pos.z = 0 ;
	
	-- Only object.transform was taken into account, but when mirror is applied
    -- object.scale is modified and become [-1,-1,-1] that's why we do what follows:
	if ((d.parent != undefined) and (hasproperty d.parent "scale")) then (
        pos = pos * d.parent.scale ;
    ) 
				
	format("\t\t\t<position x=\"%\" y=\"%\" z=\"%\" />\n") pos.x pos.y pos.z to:outFile ;
    format("\t\t\t<rotation angle=\"%\">\n") angle to:outFile ;
    format("\t\t\t\t<axis x=\"%\" y=\"%\" z=\"%\" />\n") rot.axis.x rot.axis.y rot.axis.z to:outFile ;
   	format("\t\t\t</rotation>\n") to:outFile ;
	format("\t\t</bone>\n") to:outFile ;
)

-----------------------------
-- write Bones (using writeB)
-----------------------------
function writeBones phy sk scale flipYZ exportHelpers outFile =
(
	local i ;
	
	OgreExportObject.exportProgress.value = 0;

	if (BonesList.count == 0) then
		computeBonesList phy sk exportHelpers;
	
	format("\t<bones>\n") to:outFile;
	
	i = 0 ;
	
	for i=1 to BonesList.count do
	(
		OgreExportObject.exportProgress.value = (100.0*i/BonesList.count);

		writeB BonesList[i] i scale flipYZ outFile ;
	)	
	
	format("\t</bones>\n") to:outFile;
	
	OgreExportObject.exportProgress.value = 100;
)

--------------------------
-- write <bonehierarchy />
--------------------------
function writeH b outFile =
(
	if (not isRootUniversal2 b) then
	(
		p = b.parent ;
		format("\t\t<boneparent bone=\"%\" parent=\"%\" />\n") (replaceSpaces b.name) (replaceSpaces p.name) to:outFile ;
	)
)

function writeHierarchy outFile =
(
	OgreExportObject.exportProgress.value = 0;

	local bname,pelvis
	format("\t<bonehierarchy>\n") to:outFile ;

	for i=1 to BonesList.count do
	(
		OgreExportObject.exportProgress.value = (100.0*i/BonesList.count);

		b = getNodeByName BonesList[i] ;
		writeH b outFile ;	
	)

	format("\t</bonehierarchy>\n") to:outFile ;
	
	OgreExportObject.exportProgress.value = 100;
)

-----------------------
-- write <animations />
-----------------------
function writeAnim Anims samplerate IKsamplerate scale flipYZ outFile =
(
	local i,n ;
	
	OgreExportObject.exportProgress.value = 0;
	
	format("\t<animations>\n") to: outFile ;
	
	for anm=1 to Anims.names.count do
	(
	    format("\t\t<animation name=\"%\" length=\"%\">\n") Anims.names[anm] Anims.lengths[anm] to:outFile ;
		format("\t\t\t<tracks>\n") to:outFile
		
		n = BonesList.count ;
		for i = 1 to n do
		(
			OgreExportObject.exportProgress.value = (100.0*i/BonesList.count)/Anims.names.count;

			writeTrack BonesList[i] i Anims.startframes[anm] Anims.endframes[anm] samplerate IKsamplerate Anims.lengths[anm] scale flipYZ outFile ;
		)
	
		format("\t\t\t</tracks>\n") to:outFile					
		format("\t\t</animation>\n") to: outFile ;
	)
	
	format("\t</animations>\n") to: outFile ;

	OgreExportObject.exportProgress.value = 100;
)

-------------------------------------------------------------
-- write <skeleton /> main function
-- write the animation in the file out_name + ".skeleton.xml"
-- between the frame firstFrame and lastFrame 
-- and scale time according to length
-------------------------------------------------------------

function writeSkeleton pmesh exportOptions Anims out_name = 
(
	local sk,n,keys,initialKeys,messages,phy ;
	
	sk = getSkin pmesh ;
	phy = getPhysique pmesh ;
	
	if (sk == undefined and phy == undefined) then
	(
		MessageBox "There is no skin or physique modifier for this object" ;
		return false;
	)
	else
	(	
		-- in order to perform, skin should be opened
		max modify mode ;
		if (sk != undefined) then
			modPanel.setCurrentObject pmesh.modifiers[#Skin] ;
		else -- physique
			modPanel.setCurrentObject pmesh.modifiers[#Physique] ;

		if (not g_MAX) then
		(
			format "------------------------------------------\n"
			format "------ OGRE skeleton Exporter Log   ------\n"
			format "------------------------------------------\n"
			
			format "Exporter options :\n"
			for i=1 to Anims.names.count do
				format "Anim % - firstFrame: % - lastFrame: %\n" Anims.names[i] Anims.startframes[i] Anims.endframes[i] ;
			-- creates the output file
			outFile = createfile (out_name + ".skeleton.xml") ;
		)
		else
		(
			if (g_MAX_use_listener) then
				format("<ogrestartfile>%</ogrestartfile><ogrestartdata>\n") (outName + ".skeleton.xml");
			outFile = listener;
		)
	
		-- writes header
		format("<skeleton>\n") to:outFile ;	
	
		if (not g_MAX) then
			format "Writing bones :\n" ;
		writeBones phy sk exportOptions.scale exportOptions.flipYZ exportOptions.exportHelpers outFile ;

		if (not g_MAX) then
			format "Writing bone hierarchy.\n" ;
		writeHierarchy outFile ;

		if (not g_MAX) then
			format "Writing bone tracks.\n" ;
		writeAnim Anims exportOptions.sampleRate exportOptions.ikSampleRate exportOptions.scale exportOptions.flipYZ outFile ;

		-- ecriture, fin des balises
		format("</skeleton>\n") to: outFile ;
				
		if (not g_MAX) then
		(
			format "------------------------------------------\n"
			format "----------          END          ---------\n"
			format "------------------------------------------\n"
		
			close outFile ;
		)
		else
		(
			if (g_MAX_use_listener) then
				format("</ogrestartdata>\n") to: outFile;
		)
		
		messageBox "Exporting skeleton successful !"
		return true;
	)
)



