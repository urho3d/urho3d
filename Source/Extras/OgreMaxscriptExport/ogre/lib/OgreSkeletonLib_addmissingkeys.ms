-- add key to Position tracks.
function addPosK obj time =
(
	local posContr,subPosContr,i ;
	posContr = obj.pos.controller ;
	subPosContr = getXYZControllers posContr ;
	for i = 1 to 3 do
	(
		addNewKey subPosContr[i] time ;
	)
)

-- add key to Rotation tracks.
function addRotK obj time =
(
	local rotContr,subRotContr,i ;
	rotContr = obj.rotation.controller ;
	subRotContr = getXYZControllers rotContr ;
	for i = 1 to 3 do
	(
		addNewKey subRotContr[i] time ;
	)
)


-------------------------------------------------------------------------------
-- add keys for example in position track when there are some in rotation track
-------------------------------------------------------------------------------

function addMissingKeys obj =
(
	local rotContr,posContr,nRotKeys,nPosKeys
	
	rotContr = obj.rotation.controller ;
	posContr = obj.pos.controller ;
	subRotContr = getXYZControllers rotContr ;
	subPosContr = getXYZControllers posContr ;
	nRotKeys = #() ;
	nPosKeys = #() ;
	
	if (subRotContr[1] != undefined and subPosContr[1] != undefined) then
	(
		nRotKeys[1] = numKeys subRotContr[1] ;
		nRotKeys[2] = numKeys subRotContr[2] ;
		nRotKeys[3] = numKeys subRotContr[3] ;
	
		nPosKeys[1] = numKeys subPosContr[1] ;
		nPosKeys[2] = numKeys subPosContr[2] ;
		nPosKeys[3] = numKeys subPosContr[3] ;
	
	
		for i=1 to 3 do -- i = controller index
		(
			for n = 1 to numKeys subRotContr[i] do -- n = number of keys
			(
				for j=1 to n do  -- j = key index
				(
					t = (getKey subRotContr[1] j).time ;
					addRotK obj t ;
					addPosK obj t ;
				)
			)
		
			for n = 1 to numKeys subPosContr[i] do -- n = number of keys
			(
				for j=1 to n do  -- j = key index
				(
					t = (getKey subPosContr[1] j).time ;
					addRotK obj t ;
					addPosK obj t ;
				)
			)	
		)
	)
)