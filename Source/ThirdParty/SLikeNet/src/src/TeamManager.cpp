/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_TeamManager==1

#include "slikenet/TeamManager.h"
#include "slikenet/BitStream.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/GetTime.h"

using namespace SLNet;


enum TeamManagerOperations
{
	ID_RUN_UpdateListsToNoTeam,
	ID_RUN_UpdateTeamsRequestedToAny,
	ID_RUN_JoinAnyTeam,
	ID_RUN_JoinRequestedTeam,
	ID_RUN_UpdateTeamsRequestedToNoneAndAddTeam,
	ID_RUN_RemoveFromTeamsRequestedAndAddTeam,
	ID_RUN_AddToRequestedTeams,
	ID_RUN_LeaveTeam,
	ID_RUN_SetMemberLimit,
	ID_RUN_SetJoinPermissions,
	ID_RUN_SetBalanceTeams,
	ID_RUN_SetBalanceTeamsInitial,
	ID_RUN_SerializeWorld,
};

STATIC_FACTORY_DEFINITIONS(TM_TeamMember,TM_TeamMember);
STATIC_FACTORY_DEFINITIONS(TM_Team,TM_Team);
STATIC_FACTORY_DEFINITIONS(TeamManager,TeamManager);

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int TM_World::JoinRequestHelperComp(const TM_World::JoinRequestHelper &key, const TM_World::JoinRequestHelper &data)
{
	if (key.whenRequestMade < data.whenRequestMade)
		return -1;
	if (key.whenRequestMade > data.whenRequestMade)
		return 1;
	if (key.requestIndex < data.requestIndex)
		return -1;
	if (key.requestIndex > data.requestIndex)
		return 1;
	return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection::TeamSelection() {}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection::TeamSelection(JoinTeamType itt) : joinTeamType(itt) {}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection::TeamSelection(JoinTeamType itt, TM_Team *param) : joinTeamType(itt) {teamParameter.specificTeamToJoin=param;}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection::TeamSelection(JoinTeamType itt, NoTeamId param) : joinTeamType(itt) {teamParameter.noTeamSubcategory=param;}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection TeamSelection::AnyAvailable(void) {return TeamSelection(JOIN_ANY_AVAILABLE_TEAM);}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection TeamSelection::SpecificTeam(TM_Team *specificTeamToJoin) {return TeamSelection(JOIN_SPECIFIC_TEAM, specificTeamToJoin);}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection TeamSelection::NoTeam(NoTeamId noTeamSubcategory) {return TeamSelection(JOIN_NO_TEAM, noTeamSubcategory);}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_TeamMember::TM_TeamMember()
{
	networkId=0;
	world=0;
	joinTeamType=JOIN_NO_TEAM;
	noTeamSubcategory=0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_TeamMember::~TM_TeamMember()
{
	if (world)
	{
		world->DereferenceTeamMember(this);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::RequestTeam(TeamSelection teamSelection)
{
	if (teamSelection.joinTeamType==JOIN_NO_TEAM)
	{
		// If joining no team:
		// - If already no team, and no team category is the same, return false.
		// - Execute JoinNoTeam() locally. Return ID_TEAM_BALANCER_TEAM_ASSIGNED locally.
		// - If we are host, broadcast event. Done.
		// - Send to remote host event to call JoinNoTeam()
		// - remote Host executes JoinNoTeam() and broadcasts event. This may cause may cause rebalance if team balancing is on. 
		// - - JoinNoTeam(): Remove from all current and requested teams. Set no-team category.

		if (teams.Size()==0 && noTeamSubcategory==teamSelection.teamParameter.noTeamSubcategory)
		{
			// No change
			return false;
		}

		BitStream bsOut;
		bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
		bsOut.WriteCasted<MessageID>(ID_RUN_UpdateListsToNoTeam);
		bsOut.Write(world->GetWorldId());
		bsOut.Write(networkId);
		bsOut.Write(teamSelection.teamParameter.noTeamSubcategory);
		world->BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);

		StoreLastTeams();

		UpdateListsToNoTeam(teamSelection.teamParameter.noTeamSubcategory);

		world->GetTeamManager()->PushTeamAssigned(this);
		if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified())
		{
			world->FillRequestedSlots();
			world->EnforceTeamBalance(teamSelection.teamParameter.noTeamSubcategory);
		}
	}
	else if (teamSelection.joinTeamType==JOIN_ANY_AVAILABLE_TEAM)
	{
		// If joining any team
		// Execute JoinAnyTeamCheck()
		// - JoinAnyTeamCheck(): 
		// - - If already on a team, return false
		// - - If any team is already in requested teams, return false.
		// On local, call UpdateTeamsRequestedToAny(). Send event to also execute this to remote host
		// If we are host, execute JoinAnyTeam(myguid).
		// - JoinAnyTeam(requesterGuid): Attempt to join any team immediately.  If fails, send to all except requestGuid UpdateTeamsRequestedToAny(). Else sends out new team, including to caller.
		// On remote host, execute JoinAnyTeamCheck(). If fails, this was because you were added to a team simultaneously on host. This is OK, just ignore the call.
		// Assuming JoinAnyTeamCheck() passed on remote host, call UpdateTeamsRequestedToAny() for this player. execute JoinAnyTeam(packet->guid). 

		if (JoinAnyTeamCheck()==false)
			return false;

		UpdateTeamsRequestedToAny();

		// Send request to host to execute JoinAnyTeam()
		BitStream bsOut;
		bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
		bsOut.WriteCasted<MessageID>(ID_RUN_JoinAnyTeam);
		bsOut.Write(world->GetWorldId());
		bsOut.Write(networkId);
		world->GetTeamManager()->SendUnified(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED, 0, world->GetHost(), false);
	}
	else
	{
		RakAssert(teamSelection.joinTeamType==JOIN_SPECIFIC_TEAM);

		// If joining specific team
		// Execute JoinSpecificTeamCheck()
		// JoinSpecificTeamCheck():
		// - If already on specific team, return false
		// - If specific team is in requested list, return false
		// On local, call AddToRequestedTeams(). Send event to also execute this to remote host
		// If we are host, execute JoinSpecificTeam(myguid)
		// - JoinSpecificTeam(requesterGuid): Attempt to join specific team immediately. If fails, send to all except requesterGuid to execute AddSpecificToRequested(). Else sends out new team, including to caller.
		// On remote host, execute JoinSpecificTeamCheck(). If fails, just ignore.
		// Assuming JoinSpecificTeamCheck() passed on host, call AddSpecificToRequestedList(). Execute JoinSpecificTeam(packet->guid)

		if (JoinSpecificTeamCheck(teamSelection.teamParameter.specificTeamToJoin,false)==false)
			return false;

		AddToRequestedTeams(teamSelection.teamParameter.specificTeamToJoin);

		// Send request to host to execute JoinRequestedTeam()
		BitStream bsOut;
		bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
		bsOut.WriteCasted<MessageID>(ID_RUN_JoinRequestedTeam);
		bsOut.Write(world->GetWorldId());
		bsOut.Write(networkId);
		bsOut.Write(teamSelection.teamParameter.specificTeamToJoin->GetNetworkID());
		bsOut.Write(false);
		world->GetTeamManager()->SendUnified(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED, 0, world->GetHost(), false);
	}

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::RequestTeamSwitch(TM_Team *teamToJoin, TM_Team *teamToLeave)
{
	if (SwitchSpecificTeamCheck(teamToJoin,teamToLeave,false)==false)
		return false;

	AddToRequestedTeams(teamToJoin, teamToLeave);

	// Send request to host to execute JoinRequestedTeam()
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
	bsOut.WriteCasted<MessageID>(ID_RUN_JoinRequestedTeam);
	bsOut.Write(world->GetWorldId());
	bsOut.Write(networkId);
	bsOut.Write(teamToJoin->GetNetworkID());
	bsOut.Write(true);
	if (teamToLeave)
	{
		bsOut.Write(true);
		bsOut.Write(teamToLeave->GetNetworkID());
	}
	else
	{
		bsOut.Write(false);
	}
	world->GetTeamManager()->SendUnified(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED, 0, world->GetHost(), false);

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamSelection TM_TeamMember::GetRequestedTeam(void) const
{
	if (teamsRequested.Size()>0)
		return TeamSelection::SpecificTeam(teamsRequested[0].requested);
	else if (joinTeamType==JOIN_NO_TEAM)
		return TeamSelection::NoTeam(noTeamSubcategory);
	else
		return TeamSelection::AnyAvailable();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::GetRequestedSpecificTeams(DataStructures::List<TM_Team*> &requestedTeams) const
{
	requestedTeams.Clear(true, _FILE_AND_LINE_);
	for (unsigned int i=0; i < teamsRequested.Size(); i++)
		requestedTeams.Push(teamsRequested[i].requested, _FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::HasRequestedTeam(TM_Team *team) const
{
	unsigned int i = GetRequestedTeamIndex(team);
	if (i==(unsigned int)-1)
		return false;
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_TeamMember::GetRequestedTeamIndex(TM_Team *team) const
{
	unsigned int i;
	for (i=0; i < teamsRequested.Size(); i++)
	{
		if (teamsRequested[i].requested==team)
			return i;
	}
	return (unsigned int) -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_TeamMember::GetRequestedTeamCount(void) const
{
	return teamsRequested.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::CancelTeamRequest(TM_Team *specificTeamToCancel)
{
	if (RemoveFromRequestedTeams(specificTeamToCancel)==false)
		return false;

	// Send request to host to execute JoinRequestedTeam()
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_TEAM_REQUESTED_CANCELLED);
	bsOut.Write(world->GetWorldId());
	bsOut.Write(networkId);
	if (specificTeamToCancel)
	{
		bsOut.Write(true);
		bsOut.Write(specificTeamToCancel->GetNetworkID());
	}
	else
	{
		bsOut.Write(false);
	}
	world->BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);

	world->GetTeamManager()->PushBitStream(&bsOut);

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::LeaveTeam(TM_Team* team, NoTeamId _noTeamSubcategory)
{
	if (LeaveTeamCheck(team)==false)
		return false;

	RemoveFromSpecificTeamInternal(team);
	if (teams.Size()==0)
	{
		noTeamSubcategory=_noTeamSubcategory;
		joinTeamType=JOIN_NO_TEAM;
	}

	// Execute LeaveTeamCheck()
	// - LeaveTeamCheck():
	// - - If not on this team, return false
	// On local, call RemoteFromTeamsList(). Send event to also execute this to remote host
	// If we are host, execute OnLeaveTeamEvent(myGuid)
	// - OnLeaveTeamEvent(requesterGuid):
	// - - If rebalancing is active, rebalance
	// - - If someone else wants to join this team, let them.
	// - - Send leave team event notification to all except requesterGuid-
	// On remote host, execute LeaveTeamCheck(). If fails, ignore.
	// On remote host, execute RemoteFromTeamsList() followed by OnLeaveTeamEvent(packet->guid)

	// Pattern:
	// Execute local check, if fails return false
	// Locally execute non-host guaranteed changes
	// If local system is also host, execute host changes. Relay to all but local
	// On remote host, execute check. If check passes, execute non-host changes, followed by host changes. Relay to all but sender.
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
	bsOut.WriteCasted<MessageID>(ID_RUN_LeaveTeam);
	bsOut.Write(world->GetWorldId());
	bsOut.Write(networkId);
	bsOut.Write(team->GetNetworkID());
	bsOut.Write(noTeamSubcategory);
	world->BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);

	if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified())
	{
		// Rebalance teams
		world->FillRequestedSlots();
		world->EnforceTeamBalance(noTeamSubcategory);
	}

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::LeaveAllTeams(NoTeamId inNoTeamSubcategory)
{
	return RequestTeam(TeamSelection::NoTeam(inNoTeamSubcategory));
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_Team* TM_TeamMember::GetCurrentTeam(void) const
{
	if (teams.Size()>0)
		return teams[0];
	return 0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_TeamMember::GetCurrentTeamCount(void) const
{
	return teams.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_Team* TM_TeamMember::GetCurrentTeamByIndex(unsigned int index)
{
	return teams[index];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::GetCurrentTeams(DataStructures::List<TM_Team*> &_teams) const
{
	_teams=teams;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::GetLastTeams(DataStructures::List<TM_Team*> &_teams) const
{
	_teams=lastTeams;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::IsOnTeam(TM_Team *team) const
{
	unsigned int i;
	for (i=0; i < teams.Size(); i++)
	{
		if (teams[i]==team)
			return true;
	}
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NetworkID TM_TeamMember::GetNetworkID(void) const
{
	return networkId;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_World* TM_TeamMember::GetTM_World(void) const
{
	return world;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::SerializeConstruction(BitStream *constructionBitstream)
{	
	// Write requested teams
	constructionBitstream->Write(world->GetWorldId());
	constructionBitstream->Write(networkId);
	constructionBitstream->WriteCasted<uint16_t>(teamsRequested.Size());
	for (unsigned int i=0; i < teamsRequested.Size(); i++)
	{
		constructionBitstream->Write(teamsRequested[i].isTeamSwitch);
		if (teamsRequested[i].teamToLeave)
		{
			constructionBitstream->Write(true);
			constructionBitstream->Write(teamsRequested[i].teamToLeave->GetNetworkID());
		}
		else
		{
			constructionBitstream->Write(false);
		}
		if (teamsRequested[i].requested)
		{
			constructionBitstream->Write(true);
			constructionBitstream->Write(teamsRequested[i].requested->GetNetworkID());
		}
		else
		{
			constructionBitstream->Write(false);
		}
	}

	world->teamManager->EncodeTeamAssigned(constructionBitstream, this);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::DeserializeConstruction(TeamManager *teamManager, BitStream *constructionBitstream)
{
	// Read requested teams
	bool success;
	uint16_t teamsRequestedSize;

	WorldId worldId;
	constructionBitstream->Read(worldId);
	TM_World *curWorld = teamManager->GetWorldWithId(worldId);
	RakAssert(curWorld);
	constructionBitstream->Read(networkId);
	curWorld->ReferenceTeamMember(this,networkId);

	success=constructionBitstream->Read(teamsRequestedSize);
	for (unsigned int i=0; i < teamsRequestedSize; i++)
	{
		RequestedTeam rt;
		rt.isTeamSwitch=false;
		rt.requested=0;
		rt.whenRequested=0;
		constructionBitstream->Read(rt.isTeamSwitch);
		bool hasTeamToLeave=false;
		constructionBitstream->Read(hasTeamToLeave);
		NetworkID teamToLeaveId;
		if (hasTeamToLeave)
		{
			constructionBitstream->Read(teamToLeaveId);
			rt.teamToLeave = curWorld->GetTeamByNetworkID(teamToLeaveId);
			RakAssert(rt.teamToLeave);
		}
		else
			rt.teamToLeave=0;
		bool hasTeamRequested=false;
		success=constructionBitstream->Read(hasTeamRequested);
		NetworkID teamRequestedId;
		if (hasTeamRequested)
		{
			success=constructionBitstream->Read(teamRequestedId);
			rt.requested = curWorld->GetTeamByNetworkID(teamRequestedId);
			RakAssert(rt.requested);
		}
		rt.whenRequested= SLNet::GetTime();
		rt.requestIndex= curWorld->teamRequestIndex++; // In case whenRequested is the same between two teams when sorting team requests
		if (
			(hasTeamToLeave==false || (hasTeamToLeave==true && rt.teamToLeave!=0)) &&
			(hasTeamRequested==false || (hasTeamRequested==true && rt.requested!=0))
			)
		{
			teamsRequested.Push(rt, _FILE_AND_LINE_);
		}
	}


	if (success)
		curWorld->teamManager->ProcessTeamAssigned(constructionBitstream);
	return success;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void *TM_TeamMember::GetOwner(void) const
{
	return owner;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::SetOwner(void *o)
{
	owner=o;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NoTeamId TM_TeamMember::GetNoTeamId(void) const
{
	return noTeamSubcategory;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_TeamMember::GetWorldIndex(void) const
{
	return world->GetTeamMemberIndex(this);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned long TM_TeamMember::ToUint32( const NetworkID &g )
{
	return g & 0xFFFFFFFF;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::UpdateListsToNoTeam(NoTeamId nti)
{
	teamsRequested.Clear(true, _FILE_AND_LINE_ );
	for (unsigned int i=0; i < teams.Size(); i++)
	{
		teams[i]->RemoveFromTeamMemberList(this);
	}
	teams.Clear(true, _FILE_AND_LINE_ );
	noTeamSubcategory=nti;
	joinTeamType=JOIN_NO_TEAM;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::JoinAnyTeamCheck(void) const
{
	// - - If already on a team, return false
	if (teams.Size() > 0)
		return false;

	// - - If any team is already in requested teams, return false.
	if (teamsRequested.Size()==0 && joinTeamType==JOIN_ANY_AVAILABLE_TEAM)
		return false;

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::JoinSpecificTeamCheck(TM_Team *specificTeamToJoin, bool ignoreRequested) const
{
	// - If already on specific team, return false
	if (IsOnTeam(specificTeamToJoin))
		return false;

	if (ignoreRequested)
		return true;

	unsigned int i;
	for (i=0; i < teamsRequested.Size(); i++)
	{
		if (teamsRequested[i].requested==specificTeamToJoin)
		{
			if (teamsRequested[i].isTeamSwitch==true)
				return true; // Turn off team switch

			// Same thing
			return false;
		}
	}

	// Not in teams requested
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::SwitchSpecificTeamCheck(TM_Team *teamToJoin, TM_Team *teamToLeave, bool ignoreRequested) const
{
	RakAssert(teamToJoin!=0);

	// - If already on specific team, return false
	if (IsOnTeam(teamToJoin))
		return false;

	if (teamToLeave!=0 && IsOnTeam(teamToLeave)==false)
		return false;

	if (teamToJoin==teamToLeave)
		return false;

	if (ignoreRequested)
		return true;

	unsigned int i;
	for (i=0; i < teamsRequested.Size(); i++)
	{
		if (teamsRequested[i].requested==teamToJoin)
		{
			if (teamsRequested[i].isTeamSwitch==false)
				return true; // Different - leave team was off, turn on
			
			if (teamsRequested[i].teamToLeave==teamToLeave)
				return false; // Same thing - leave all or a specific team

			// Change leave team
			return true;
		}
	}

	// Not in teams requested
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::LeaveTeamCheck(TM_Team *team) const
{
	if (IsOnTeam(team)==false)
		return false;
	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::UpdateTeamsRequestedToAny(void)
{
	teamsRequested.Clear(true, _FILE_AND_LINE_);
	joinTeamType=JOIN_ANY_AVAILABLE_TEAM;
	whenJoinAnyRequested= SLNet::GetTime();
	joinAnyRequestIndex=world->teamRequestIndex++; // In case whenRequested is the same between two teams when sorting team requests
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::UpdateTeamsRequestedToNone(void)
{
	teamsRequested.Clear(true, _FILE_AND_LINE_);
	joinTeamType=JOIN_NO_TEAM;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::AddToRequestedTeams(TM_Team *teamToJoin)
{
	RemoveFromRequestedTeams(teamToJoin);

	RequestedTeam rt;
	rt.isTeamSwitch=false;
	rt.requested=teamToJoin;
	rt.teamToLeave=0;
	rt.whenRequested= SLNet::GetTime();
	rt.requestIndex=world->teamRequestIndex++; // In case whenRequested is the same between two teams when sorting team requests
	teamsRequested.Push(rt, _FILE_AND_LINE_ );
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::AddToRequestedTeams(TM_Team *teamToJoin, TM_Team *teamToLeave)
{
	RemoveFromRequestedTeams(teamToJoin);

	RequestedTeam rt;
	rt.isTeamSwitch=true;
	rt.requested=teamToJoin;
	rt.teamToLeave=teamToLeave;
	rt.whenRequested= SLNet::GetTime();
	rt.requestIndex=world->teamRequestIndex++; // In case whenRequested is the same between two teams when sorting team requests
	teamsRequested.Push(rt, _FILE_AND_LINE_ );
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_TeamMember::RemoveFromRequestedTeams(TM_Team *team)
{
	if (team==0)
	{
		teamsRequested.Clear(true, _FILE_AND_LINE_);
		joinTeamType=JOIN_NO_TEAM;
		return true;
	}
	else
	{
		unsigned int i;
		for (i=0; i < teamsRequested.Size(); i++)
		{
			if (teamsRequested[i].requested==team)
			{
				teamsRequested.RemoveAtIndex(i);
				if (teamsRequested.Size()==0)
				{
					joinTeamType=JOIN_NO_TEAM;
				}
				return true;
			}
		}
	}
	return false;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::AddToTeamList(TM_Team *team)
{
	team->teamMembers.Push(this, _FILE_AND_LINE_ );
	teams.Push(team, _FILE_AND_LINE_ );
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::RemoveFromSpecificTeamInternal(TM_Team *team)
{
	unsigned int i,j;
	for (i=0; i < teams.Size(); i++)
	{
		if (teams[i]==team)
		{
			for (j=0; j < team->teamMembers.Size(); j++)
			{
				if (team->teamMembers[j]==this)
				{
					team->teamMembers.RemoveAtIndex(j);
					break;
				}
			}
			teams.RemoveAtIndex(i);
			break;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::RemoveFromAllTeamsInternal(void)
{
	TM_Team *team;
	unsigned int i,j;
	for (i=0; i < teams.Size(); i++)
	{
		team = teams[i];

		for (j=0; j < team->teamMembers.Size(); j++)
		{
			if (team->teamMembers[j]==this)
			{
				team->teamMembers.RemoveAtIndex(j);
				break;
			}
		}
	}
	teams.Clear(true, _FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_TeamMember::StoreLastTeams(void)
{
	lastTeams=teams;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_Team::TM_Team()
{
	ID=0;
	world=0;
	joinPermissions=ALLOW_JOIN_ANY_AVAILABLE_TEAM|ALLOW_JOIN_SPECIFIC_TEAM|ALLOW_JOIN_REBALANCING;
	balancingApplies=true;
	teamMemberLimit=65535;
	owner=0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_Team::~TM_Team()
{
	if (world)
		world->DereferenceTeam(this, 0);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_Team::SetMemberLimit(TeamMemberLimit _teamMemberLimit, NoTeamId noTeamId)
{
	if (teamMemberLimit==_teamMemberLimit)
		return false;

	teamMemberLimit=_teamMemberLimit;
	// Network this as request to host
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
	bsOut.WriteCasted<MessageID>(ID_RUN_SetMemberLimit);
	bsOut.Write(world->GetWorldId());
	bsOut.Write(GetNetworkID());
	bsOut.Write(teamMemberLimit);
	bsOut.Write(noTeamId);
	world->GetTeamManager()->Send(&bsOut, world->GetHost(), false);

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamMemberLimit TM_Team::GetMemberLimit(void) const
{
	if (world->GetBalanceTeams()==false)
	{
		return teamMemberLimit;
	}
	else
	{
		TeamMemberLimit limitWithBalancing=world->GetBalancedTeamLimit();
		if (limitWithBalancing < teamMemberLimit)
			return limitWithBalancing;
		return teamMemberLimit;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamMemberLimit TM_Team::GetMemberLimitSetting(void) const
{
	return teamMemberLimit;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_Team::SetJoinPermissions(JoinPermissions _joinPermissions)
{
	if (joinPermissions==_joinPermissions)
		return false;

	joinPermissions=_joinPermissions;

	// Network this as request to host
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
	bsOut.WriteCasted<MessageID>(ID_RUN_SetJoinPermissions);
	bsOut.Write(world->GetWorldId());
	bsOut.Write(GetNetworkID());
	bsOut.Write(_joinPermissions);
	world->GetTeamManager()->Send(&bsOut,world->GetHost(), false);

	return true;

	
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

JoinPermissions TM_Team::GetJoinPermissions(void) const
{
	return joinPermissions;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_Team::LeaveTeam(TM_TeamMember* teamMember, NoTeamId noTeamSubcategory)
{
	teamMember->LeaveTeam(this, noTeamSubcategory);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_Team::GetBalancingApplies(void) const
{
	return balancingApplies;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_Team::GetTeamMembers(DataStructures::List<TM_TeamMember*> &_teamMembers) const
{
	_teamMembers=teamMembers;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_Team::GetTeamMembersCount(void) const
{
	return teamMembers.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_TeamMember *TM_Team::GetTeamMemberByIndex(unsigned int index) const
{
	return teamMembers[index];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NetworkID TM_Team::GetNetworkID(void) const
{
	return ID;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_World* TM_Team::GetTM_World(void) const
{
	return world;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_Team::SerializeConstruction(BitStream *constructionBitstream)
{
	// Do not need to serialize member lists, the team members do this
	constructionBitstream->Write(world->GetWorldId());
	constructionBitstream->Write(ID);
	constructionBitstream->Write(joinPermissions);
	constructionBitstream->Write(balancingApplies);
	constructionBitstream->Write(teamMemberLimit);

}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_Team::DeserializeConstruction(TeamManager *teamManager, BitStream *constructionBitstream)
{
	WorldId worldId;
	constructionBitstream->Read(worldId);
	TM_World *curWorld = teamManager->GetWorldWithId(worldId);
	RakAssert(curWorld);
	constructionBitstream->Read(ID);
	constructionBitstream->Read(joinPermissions);
	constructionBitstream->Read(balancingApplies);
	bool b = constructionBitstream->Read(teamMemberLimit);
	RakAssert(b);
	if (b)
	{
		curWorld->ReferenceTeam(this,ID,balancingApplies);
	}
	return b;
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned long TM_Team::ToUint32( const NetworkID &g )
{
	return g & 0xFFFFFFFF;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void *TM_Team::GetOwner(void) const
{
	return owner;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


unsigned int TM_Team::GetWorldIndex(void) const
{
	return world->GetTeamIndex(this);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_Team::SetOwner(void *o)
{
	owner=o;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_Team::RemoveFromTeamMemberList(TM_TeamMember *teamMember)
{
	unsigned int index = teamMembers.GetIndexOf(teamMember);
	RakAssert(index != (unsigned int) -1);
	teamMembers.RemoveAtIndex(index);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_Team::GetMemberWithRequestedSingleTeamSwitch(TM_Team *team)
{
	unsigned int i;
	for (i=0; i < teamMembers.Size(); i++)
	{
		if (teamMembers[i]->GetCurrentTeamCount()==1)
		{
			unsigned int j = teamMembers[i]->GetRequestedTeamIndex(team);
			if (j!=(unsigned int)-1)
			{
				if (teamMembers[i]->teamsRequested[j].isTeamSwitch && 
					(teamMembers[i]->teamsRequested[j].teamToLeave==0 ||
					teamMembers[i]->teamsRequested[j].teamToLeave==teamMembers[i]->teams[0])
				)
				return i;
			}
		}
	}
	return (unsigned int) -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_World::TM_World()
{
	teamManager=0;
	balanceTeamsIsActive=false;
	hostGuid=UNASSIGNED_RAKNET_GUID;
	worldId=0;
	autoAddParticipants=true;
	teamRequestIndex=0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_World::~TM_World()
{
	Clear();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamManager *TM_World::GetTeamManager(void) const
{
	return teamManager;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::AddParticipant(RakNetGUID rakNetGUID)
{
	participants.Push(rakNetGUID, _FILE_AND_LINE_ );

	// Send to remote system status of balanceTeamsIsActive

	if (GetTeamManager()->GetMyGUIDUnified()==GetHost())
	{
		// Actually just transmitting initial value of balanceTeamsIsActive
		BitStream bsOut;
		bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
		bsOut.WriteCasted<MessageID>(ID_RUN_SetBalanceTeamsInitial);
		bsOut.Write(GetWorldId());
		bsOut.Write(balanceTeamsIsActive);
		teamManager->SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0,rakNetGUID, false);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::RemoveParticipant(RakNetGUID rakNetGUID)
{
	unsigned int i;
	i = participants.GetIndexOf(rakNetGUID);
	if (i!=(unsigned int)-1)
		participants.RemoveAtIndex(i);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::SetAutoManageConnections(bool autoAdd)
{
	autoAddParticipants=autoAdd;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::GetParticipantList(DataStructures::List<RakNetGUID> &participantList)
{
	participantList = participants;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::ReferenceTeam(TM_Team *team, NetworkID networkId, bool applyBalancing)
{
	unsigned int i;
	for (i=0; i < teams.Size(); i++)
	{
		if (teams[i]==team)
			return;
	}

	team->ID=networkId;
	team->balancingApplies=applyBalancing;
	team->world=this;

	// Add this team to the list of teams
	teams.Push(team, _FILE_AND_LINE_);

	teamsHash.Push(networkId,team,_FILE_AND_LINE_);

	// If autobalancing is on, and the team lock state supports it, then call EnforceTeamBalancing()
	if (applyBalancing && balanceTeamsIsActive)
	{
		EnforceTeamBalance(0);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::DereferenceTeam(TM_Team *team, NoTeamId noTeamSubcategory)
{
	unsigned int i;
	for (i=0; i < teams.Size(); i++)
	{
		if (teams[i]==team)
		{
			TM_Team *curTeam = teams[i];
			while (curTeam->teamMembers.Size())
			{
				curTeam->teamMembers[curTeam->teamMembers.Size()-1]->LeaveTeam(curTeam, noTeamSubcategory);
			}
			teams.RemoveAtIndex(i);

			teamsHash.Remove(curTeam->GetNetworkID(),_FILE_AND_LINE_);

			break;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_World::GetTeamCount(void) const
{
	return teams.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_Team *TM_World::GetTeamByIndex(unsigned int index) const
{
	return teams[index];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_Team *TM_World::GetTeamByNetworkID(NetworkID teamId)
{
	DataStructures::HashIndex hi = teamsHash.GetIndexOf(teamId);
	if (hi.IsInvalid())
		return 0;
	return teamsHash.ItemAtIndex(hi);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_World::GetTeamIndex(const TM_Team *team) const
{
	unsigned int i;
	for (i=0; i < teams.Size(); i++)
	{
		if (teams[i]==team)
			return i;
	}
	return (unsigned int) -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::ReferenceTeamMember(TM_TeamMember *teamMember, NetworkID networkId)
{
	unsigned int i;
	for (i=0; i < teamMembers.Size(); i++)
	{
		if (teamMembers[i]==teamMember)
			return;
	}

	teamMember->world=this;
	teamMember->networkId=networkId;

	teamMembers.Push(teamMember, _FILE_AND_LINE_);

	teamMembersHash.Push(networkId,teamMember,_FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::DereferenceTeamMember(TM_TeamMember *teamMember)
{
	unsigned int i;
	for (i=0; i < teamMembers.Size(); i++)
	{
		if (teamMembers[i]==teamMember)
		{
			teamMembers[i]->UpdateListsToNoTeam(0);
			teamMembersHash.Remove(teamMembers[i]->GetNetworkID(),_FILE_AND_LINE_);
			teamMembers.RemoveAtIndex(i);
			break;
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_World::GetTeamMemberCount(void) const
{
	return teamMembers.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_TeamMember *TM_World::GetTeamMemberByIndex(unsigned int index) const
{
	return teamMembers[index];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NetworkID TM_World::GetTeamMemberIDByIndex(unsigned int index) const
{
	return teamMembers[index]->GetNetworkID();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_TeamMember *TM_World::GetTeamMemberByNetworkID(NetworkID teamMemberId)
{
	DataStructures::HashIndex hi = teamMembersHash.GetIndexOf(teamMemberId);
	if (hi.IsInvalid())
		return 0;
	return teamMembersHash.ItemAtIndex(hi);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_World::GetTeamMemberIndex(const TM_TeamMember *teamMember) const
{
	unsigned int i;
	for (i=0; i < teamMembers.Size(); i++)
	{
		if (teamMembers[i]==teamMember)
			return i;
	}
	return (unsigned int) -1;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_World::SetBalanceTeams(bool balanceTeams, NoTeamId noTeamId)
{
	if (balanceTeams==balanceTeamsIsActive)
		return false;

	balanceTeamsIsActive=balanceTeams;

	// Network this as request to host
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
	bsOut.WriteCasted<MessageID>(ID_RUN_SetBalanceTeams);
	bsOut.Write(GetWorldId());
	bsOut.Write(balanceTeams);
	bsOut.Write(noTeamId);
	GetTeamManager()->SendUnified(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED, 0, GetHost(), false);

	return true;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TM_World::GetBalanceTeams(void) const
{
	return balanceTeamsIsActive;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::SetHost(RakNetGUID _hostGuid)
{
	if (hostGuid==_hostGuid)
		return;

	RakAssert(_hostGuid!=UNASSIGNED_RAKNET_GUID);

	hostGuid=_hostGuid;

	if (GetHost()==GetTeamManager()->GetMyGUIDUnified())
		FillRequestedSlots();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RakNetGUID TM_World::GetHost(void) const
{
	return hostGuid;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

WorldId TM_World::GetWorldId(void) const
{
	return worldId;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::Clear(void)
{
	for (unsigned int i=0; i < teams.Size(); i++)
	{
		teams[i]->world=0;
	}
	for (unsigned int i=0; i < teamMembers.Size(); i++)
	{
		teamMembers[i]->world=0;
	}
	participants.Clear(true, _FILE_AND_LINE_);
	teams.Clear(true, _FILE_AND_LINE_);
	teamMembers.Clear(true, _FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) systemAddress;

	RemoveParticipant(rakNetGUID);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	(void) isIncoming;
	(void) systemAddress;

	if (autoAddParticipants)
		AddParticipant(rakNetGUID);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::EnforceTeamBalance(NoTeamId noTeamId)
{
	// Host only function
	RakAssert(GetHost()==GetTeamManager()->GetMyGUIDUnified());

	KickExcessMembers(noTeamId);
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::KickExcessMembers(NoTeamId noTeamId)
{
	// Host only function
	RakAssert(GetHost()==GetTeamManager()->GetMyGUIDUnified());

	// For each team that applies balancing, if the team is overfull, put on a team that is not overfull if the team has ALLOW_JOIN_REBALANCING set
	// If cannot move the player to another team, just take the player off the team and set to noTeamId if they have no team at that point
	
	TeamMemberLimit balancedTeamLimit;
	if (balanceTeamsIsActive)
		balancedTeamLimit = GetBalancedTeamLimit();
	else
		balancedTeamLimit = (TeamMemberLimit) -1;

	TM_Team *team, *teamToJoin;
	unsigned int i, teamIndex;
	for (i=0; i < teams.Size(); i++)
	{
		team = teams[i];
		while (team->GetMemberLimitSetting() < team->GetTeamMembersCount() ||
			(balancedTeamLimit < team->GetTeamMembersCount() && team->GetBalancingApplies()) )
		{
			TM_TeamMember *teamMember = team->teamMembers[team->teamMembers.Size()-1];

			teamIndex = GetAvailableTeamIndexWithFewestMembers(balancedTeamLimit, ALLOW_JOIN_REBALANCING);
			if (teamIndex == (unsigned int)-1)
			{
				// Move this member to no team
				teamMember->LeaveTeam(team, noTeamId);
				teamManager->PushTeamAssigned(teamMember);
			}
			else
			{
				teamToJoin = teams[teamIndex];

				// Move this member
				teamMember->StoreLastTeams();
				teamManager->RemoveFromTeamsRequestedAndAddTeam(teamMember, teamToJoin, true, team);

				BitStream bsOut;
				bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
				bsOut.WriteCasted<MessageID>(ID_RUN_RemoveFromTeamsRequestedAndAddTeam);
				bsOut.Write(GetWorldId());
				bsOut.Write(teamMember->GetNetworkID());
				bsOut.Write(teamToJoin->GetNetworkID());
				bsOut.Write(true);
				bsOut.Write(true);
				bsOut.Write(team->GetNetworkID());
				BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);
			}

		}
	}
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::FillRequestedSlots(void)
{
	// Host only function
	RakAssert(GetHost()==GetTeamManager()->GetMyGUIDUnified());


	TeamMemberLimit balancedTeamLimit;
	if (balanceTeamsIsActive)
		balancedTeamLimit = GetBalancedTeamLimit();
	else
		balancedTeamLimit = (TeamMemberLimit) -1;

	unsigned int teamIndex, indexIntoTeamsRequested = (unsigned int)-1;
	TM_Team *team;
	TM_TeamMember *teamMember;
	DataStructures::OrderedList<TM_World::JoinRequestHelper, TM_World::JoinRequestHelper, JoinRequestHelperComp> joinRequests;
	GetSortedJoinRequests(joinRequests);
	unsigned int joinRequestIndex;

	for (joinRequestIndex=0; joinRequestIndex < joinRequests.Size(); joinRequestIndex++)
	{
		teamMember = teamMembers[joinRequests[joinRequestIndex].teamMemberIndex];
		if (teamMember->teamsRequested.Size()==0)
		{
			if (teamMember->joinTeamType==JOIN_ANY_AVAILABLE_TEAM)
				teamIndex = GetAvailableTeamIndexWithFewestMembers(balancedTeamLimit, ALLOW_JOIN_ANY_AVAILABLE_TEAM);
			else
				teamIndex=(unsigned int)-1;
		}
		else
		{
			indexIntoTeamsRequested = joinRequests[joinRequestIndex].indexIntoTeamsRequested;

			team = teamMember->teamsRequested[indexIntoTeamsRequested].requested;
			if (team->GetTeamMembersCount() < balancedTeamLimit && 
				team->GetTeamMembersCount() < team->GetMemberLimitSetting() &&
				(ALLOW_JOIN_SPECIFIC_TEAM & team->GetJoinPermissions())!=0)
			{
				teamIndex=teams.GetIndexOf(team);
			}
			else
			{
				teamIndex=(unsigned int)-1;
			}
		}

		if (teamIndex != (unsigned int)-1)
		{
			team = teams[teamIndex];

			if (teamMember->teamsRequested.Size()==0)
			{
				if (teamMember->joinTeamType==JOIN_ANY_AVAILABLE_TEAM)
				{
					// Join any
					teamMember->StoreLastTeams();
					teamMember->UpdateTeamsRequestedToNone();
					teamMember->AddToTeamList(teams[teamIndex]);
					teamManager->PushTeamAssigned(teamMember);

					BitStream bsOut;
					bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
					bsOut.WriteCasted<MessageID>(ID_RUN_UpdateTeamsRequestedToNoneAndAddTeam);
					bsOut.Write(GetWorldId());
					bsOut.Write(teamMember->GetNetworkID());
					bsOut.Write(team->GetNetworkID());
					BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);
				}
			}
			else
			{
				// Switch or join specific
				DataStructures::List<TM_Team*> teamsWeAreLeaving;
				bool isSwitch = teamMember->teamsRequested[indexIntoTeamsRequested].isTeamSwitch;
				TM_Team *teamToLeave;
				if (isSwitch)
				{
					teamToLeave=teamMember->teamsRequested[indexIntoTeamsRequested].teamToLeave;
					if (teamToLeave)
					{
						if (teamMember->IsOnTeam(teamToLeave))
						{
							teamsWeAreLeaving.Push(teamToLeave, _FILE_AND_LINE_);
						}
						else
						{
							teamToLeave=0;
							isSwitch=false;
						}
					}
					else
					{
						teamsWeAreLeaving=teamMember->teams;
					}
				}
				else
					teamToLeave=0;

				int teamJoined = JoinSpecificTeam(teamMember, team, isSwitch, teamToLeave, teamsWeAreLeaving);

				if (teamJoined==1)
				{
					BitStream bsOut;
					bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
					bsOut.WriteCasted<MessageID>(ID_RUN_RemoveFromTeamsRequestedAndAddTeam);
					bsOut.Write(GetWorldId());
					bsOut.Write(teamMember->GetNetworkID());
					bsOut.Write(team->GetNetworkID());
					bsOut.Write(isSwitch);
					if (teamToLeave!=0)
					{
						bsOut.Write(true);
						bsOut.Write(teamToLeave->GetNetworkID());
					}
					else
						bsOut.Write(false);
					BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);
				}
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TM_World::GetAvailableTeamIndexWithFewestMembers(TeamMemberLimit secondaryLimit, JoinPermissions joinPermissions)
{
	unsigned int teamIndex;

	unsigned int lowestTeamMembers = (unsigned int) -1;
	unsigned int lowestIndex = (unsigned int) -1;

	for (teamIndex=0; teamIndex < teams.Size(); teamIndex++)
	{
		if (teams[teamIndex]->GetTeamMembersCount() < secondaryLimit && 
			teams[teamIndex]->GetTeamMembersCount() < teams[teamIndex]->GetMemberLimitSetting() &&
			teams[teamIndex]->GetTeamMembersCount() < lowestTeamMembers &&
			(joinPermissions & teams[teamIndex]->GetJoinPermissions())!=0)
		{
			lowestTeamMembers = teams[teamIndex]->GetTeamMembersCount();
			lowestIndex = teamIndex;
		}
	}

	return lowestIndex;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::GetSortedJoinRequests(DataStructures::OrderedList<TM_World::JoinRequestHelper, TM_World::JoinRequestHelper, JoinRequestHelperComp> &joinRequests)
{
	unsigned int i;

	for (i=0; i < teamMembers.Size(); i++)
	{
		TM_TeamMember *teamMember = teamMembers[i];
		if (teamMember->teamsRequested.Size()==0)
		{
			if (teamMember->joinTeamType==JOIN_ANY_AVAILABLE_TEAM)
			{
				TM_World::JoinRequestHelper jrh;
				jrh.whenRequestMade=teamMember->whenJoinAnyRequested;
				jrh.teamMemberIndex=i;
				jrh.requestIndex=teamMember->joinAnyRequestIndex;
				joinRequests.Insert(jrh, jrh, true, _FILE_AND_LINE_);
			}
		}
		else
		{
			unsigned int j;
			for (j=0; j < teamMember->teamsRequested.Size(); j++)
			{
				TM_World::JoinRequestHelper jrh;
				jrh.whenRequestMade=teamMember->teamsRequested[j].whenRequested;
				jrh.teamMemberIndex=i;
				jrh.indexIntoTeamsRequested=j;
				jrh.requestIndex=teamMember->teamsRequested[j].requestIndex;
				joinRequests.Insert(jrh, jrh, true, _FILE_AND_LINE_);
			}

		}
	}
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::BroadcastToParticipants(SLNet::BitStream *bsOut, RakNetGUID exclusionGuid)
{
	for (unsigned int i=0; i < participants.Size(); i++)
	{
		if (participants[i]==exclusionGuid)
			continue;
		teamManager->SendUnified(bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, participants[i], false);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TM_World::BroadcastToParticipants(unsigned char *data, const int length, RakNetGUID exclusionGuid)
{
	for (unsigned int i=0; i < participants.Size(); i++)
	{
		if (participants[i]==exclusionGuid)
			continue;
		teamManager->SendUnified((const char*) data, length, HIGH_PRIORITY, RELIABLE_ORDERED, 0, participants[i], false);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_Team* TM_World::JoinAnyTeam(TM_TeamMember *teamMember, int *resultCode)
{
	TeamMemberLimit balancedLimit = GetBalancedTeamLimit();

	unsigned int idx = GetAvailableTeamIndexWithFewestMembers(balancedLimit, ALLOW_JOIN_ANY_AVAILABLE_TEAM);
	if (idx == (unsigned int ) -1)
	{
		// If any team is joinable but full, return full. Otherwise return locked
		for (idx=0; idx < teams.Size(); idx++)
		{
			if ((teams[idx]->GetTeamMembersCount() >= balancedLimit ||
				teams[idx]->GetTeamMembersCount()  >= teams[idx]->GetMemberLimitSetting()) &&
				teams[idx]->GetMemberLimitSetting() != 0 &&
				(ALLOW_JOIN_ANY_AVAILABLE_TEAM & teams[idx]->GetJoinPermissions())!=0)
			{
				// Full
				*resultCode=-2;
				return teams[idx];
			}
		}

		// Locked
		*resultCode=-1;
		return 0;
	}

	TM_Team* lowestMemberTeam = teams[idx];

	teamMember->StoreLastTeams();
	teamMember->UpdateTeamsRequestedToNone();
	teamMember->AddToTeamList(lowestMemberTeam);
	teamManager->PushTeamAssigned(teamMember);

	*resultCode=1;
	return lowestMemberTeam;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int TM_World::JoinSpecificTeam(TM_TeamMember *teamMember, TM_Team *team, bool isTeamSwitch, TM_Team *teamToLeave, DataStructures::List<TM_Team*> &teamsWeAreLeaving)
{
	if (team->GetJoinPermissions() & ALLOW_JOIN_SPECIFIC_TEAM)
	{
		if (balanceTeamsIsActive==false || teamsWeAreLeaving.Size()==0)
		{
			if (team->GetMemberLimit() > team->GetTeamMembersCount())
			{
				// Can join normally
				teamMember->StoreLastTeams();
				teamManager->RemoveFromTeamsRequestedAndAddTeam(teamMember, team, isTeamSwitch, teamToLeave);
				return 1;
			}
			else
			{
				// Full
				return -2;
			}
		}
		else
		{
			// Note: balanceTeamsIsActive==true && isTeamSwitch==true

			// Do limited team swap
			// We must be on one team, target must be on one team, and we want to exchange teams
			if (teamsWeAreLeaving.Size()==1)
			{
				unsigned int j = team->GetMemberWithRequestedSingleTeamSwitch(teamsWeAreLeaving[0]);
				if (j!=(unsigned int)-1)
				{
					TM_TeamMember *swappingMember = team->teamMembers[j];
					teamMember->StoreLastTeams();
					swappingMember->StoreLastTeams();
					teamManager->RemoveFromTeamsRequestedAndAddTeam(teamMember, team, true, 0);
					teamManager->RemoveFromTeamsRequestedAndAddTeam(swappingMember, teamsWeAreLeaving[0], true, 0);

					// Send ID_TEAM_BALANCER_TEAM_ASSIGNED to all, for swapped member
					// Calling function sends ID_RUN_RemoveFromTeamsRequestedAndAddTeam which pushes ID_TEAM_BALANCER_TEAM_ASSIGNED for teamMember
					SLNet::BitStream bitStream;
					bitStream.WriteCasted<MessageID>(ID_TEAM_BALANCER_TEAM_ASSIGNED);
					teamManager->EncodeTeamAssigned(&bitStream, swappingMember);
					BroadcastToParticipants(&bitStream, UNASSIGNED_RAKNET_GUID);

					return 1;
				}
			}

			// Full
			return -2;
		}
	}
	else
	{
		// Locked
		return -1;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamMemberLimit TM_World::GetBalancedTeamLimit(void) const
{
	if (teams.Size()==0)
		return 0;

	if (balanceTeamsIsActive==false)
		return (TeamMemberLimit) -1;

	unsigned int i;
	bool additionalTeamsExcluded;
	TeamMemberLimit balancedLimit;
	unsigned int teamsCount=teams.Size();
	unsigned int membersCount=teamMembers.Size();
	DataStructures::List<TM_Team*> consideredTeams = teams;

	do 
	{
		additionalTeamsExcluded=false;
		balancedLimit = (TeamMemberLimit) ((membersCount+(teamsCount-1))/(teamsCount));
		i=0;
		while (i < consideredTeams.Size())
		{
			if (consideredTeams[i]->GetMemberLimitSetting() < balancedLimit)
			{
				additionalTeamsExcluded=true;
				membersCount-=consideredTeams[i]->GetMemberLimitSetting();
				teamsCount--;
				consideredTeams.RemoveAtIndexFast(i);
			}
			else
			{
				i++;
			}
		}

	} while (additionalTeamsExcluded==true && teamsCount>0);
	
	return balancedLimit;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamManager::TeamManager()
{
	for (unsigned int i=0; i < 255; i++)
		worldsArray[i]=0;
	autoAddParticipants=true;
	topology=TM_PEER_TO_PEER;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TeamManager::~TeamManager()
{
	Clear();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_World* TeamManager::AddWorld(WorldId worldId)
{
	RakAssert(worldsArray[worldId]==0 && "World already in use");

	TM_World *newWorld = SLNet::OP_NEW<TM_World>(_FILE_AND_LINE_);
	newWorld->worldId=worldId;
	newWorld->teamManager=this;
	newWorld->hostGuid=GetMyGUIDUnified();
	worldsArray[worldId]=newWorld;
	worldsList.Push(newWorld,_FILE_AND_LINE_);
	return newWorld;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::RemoveWorld(WorldId worldId)
{
	RakAssert(worldsArray[worldId]!=0 && "World not in use");
	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		if (worldsList[i]==worldsArray[worldId])
		{
			SLNet::OP_DELETE(worldsList[i],_FILE_AND_LINE_);
			worldsList.RemoveAtIndexFast(i);
			break;
		}
	}
	worldsArray[worldId]=0;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int TeamManager::GetWorldCount(void) const
{
	return worldsList.Size();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_World* TeamManager::GetWorldAtIndex(unsigned int index) const
{
	return worldsList[index];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TM_World* TeamManager::GetWorldWithId(WorldId worldId) const
{
	return worldsArray[worldId];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::SetAutoManageConnections(bool autoAdd)
{
	autoAddParticipants=autoAdd;

	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		worldsList[i]->SetAutoManageConnections(autoAdd);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::SetTopology(TMTopology _topology)
{
	topology=_topology;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::EncodeTeamFull(SLNet::BitStream *bitStream, TM_TeamMember *teamMember, TM_Team *team)
{
	bitStream->WriteCasted<MessageID>(ID_TEAM_BALANCER_REQUESTED_TEAM_FULL);
	EncodeTeamFullOrLocked(bitStream, teamMember, team);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::DecomposeTeamFull(Packet *packet,
									TM_World **world, TM_TeamMember **teamMember, TM_Team **team,
									uint16_t &currentMembers, uint16_t &memberLimitIncludingBalancing, bool &balancingIsActive, JoinPermissions &joinPermissions)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	DecomposeTeamFullOrLocked(&bsIn, world, teamMember, team, currentMembers, memberLimitIncludingBalancing, balancingIsActive, joinPermissions);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::EncodeTeamLocked(SLNet::BitStream *bitStream, TM_TeamMember *teamMember, TM_Team *team)
{
	bitStream->WriteCasted<MessageID>(ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED);
	EncodeTeamFullOrLocked(bitStream, teamMember, team);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::EncodeTeamFullOrLocked(SLNet::BitStream *bitStream, TM_TeamMember *teamMember, TM_Team *team)
{
	bitStream->Write(teamMember->world->GetWorldId());
	bitStream->Write(teamMember->GetNetworkID());
	bitStream->Write(team->GetNetworkID());
	bitStream->WriteCasted<uint16_t>(team->GetTeamMembersCount());
	bitStream->Write(team->GetMemberLimit());
	bitStream->Write(team->GetBalancingApplies());
	bitStream->Write(team->GetJoinPermissions());
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::DecomposeTeamFullOrLocked(SLNet::BitStream *bsIn, TM_World **world, TM_TeamMember **teamMember, TM_Team **team,
							   uint16_t &currentMembers, uint16_t &memberLimitIncludingBalancing, bool &balancingIsActive, JoinPermissions &joinPermissions)
{
	WorldId worldId;
	NetworkID teamMemberId;
	NetworkID teamId;

	*teamMember=0;
	*team=0;
	*world=0;

	bsIn->Read(worldId);
	bsIn->Read(teamMemberId);
	bsIn->Read(teamId);
	bsIn->Read(currentMembers);
	bsIn->Read(memberLimitIncludingBalancing);
	bsIn->Read(balancingIsActive);
	bsIn->Read(joinPermissions);

	*world = GetWorldWithId(worldId);
	if (*world)
	{
		*teamMember = (*world)->GetTeamMemberByNetworkID(teamMemberId);
		*team = (*world)->GetTeamByNetworkID(teamId);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::DecomposeTeamLocked(Packet *packet,
									  TM_World **world, TM_TeamMember **teamMember, TM_Team **team,
									  uint16_t &currentMembers, uint16_t &memberLimitIncludingBalancing, bool &balancingIsActive, JoinPermissions &joinPermissions)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	DecomposeTeamFullOrLocked(&bsIn, world, teamMember, team, currentMembers, memberLimitIncludingBalancing, balancingIsActive, joinPermissions);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::EncodeTeamAssigned(SLNet::BitStream *bitStream, TM_TeamMember *teamMember)
{
	bitStream->Write(teamMember->world->GetWorldId());
	bitStream->Write(teamMember->GetNetworkID());
	bitStream->WriteCasted<uint16_t>(teamMember->teams.Size());
	for (unsigned int i=0; i < teamMember->teams.Size(); i++)
	{
		bitStream->Write(teamMember->teams[i]->GetNetworkID());
	}
	bitStream->Write(teamMember->noTeamSubcategory);
	bitStream->Write(teamMember->joinTeamType);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::ProcessTeamAssigned(SLNet::BitStream *bsIn)
{
	TM_World *world;
	TM_TeamMember *teamMember;
	NoTeamId noTeamId;
	JoinTeamType joinTeamType;
	DataStructures::List<TM_Team *> newTeam;
	DataStructures::List<TM_Team *> teamsLeft;
	DataStructures::List<TM_Team *> teamsJoined;
	DecodeTeamAssigned(bsIn, &world, &teamMember, noTeamId, joinTeamType, newTeam, teamsLeft, teamsJoined);
	if (teamMember)
	{
		teamMember->StoreLastTeams();
		for (unsigned int i=0; i < teamsLeft.Size(); i++)
		{
			teamMember->RemoveFromSpecificTeamInternal(teamsLeft[i]);
		}
		for (unsigned int i=0; i < teamsJoined.Size(); i++)
		{
			if (teamMember->IsOnTeam(teamsJoined[i])==false)
			{
				teamMember->RemoveFromRequestedTeams(teamsJoined[i]);
				teamMember->AddToTeamList(teamsJoined[i]);
			}
		}
		teamMember->noTeamSubcategory=noTeamId;
		teamMember->joinTeamType=joinTeamType;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::DecodeTeamAssigned(Packet *packet, TM_World **world, TM_TeamMember **teamMember)
{
	WorldId worldId;
	NetworkID teamMemberId;

	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(worldId);
	bsIn.Read(teamMemberId);
	*world = GetWorldWithId(worldId);
	if (*world)
	{
		*teamMember = (*world)->GetTeamMemberByNetworkID(teamMemberId);
	}
	else
	{
		*teamMember=0;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::DecodeTeamCancelled(Packet *packet, TM_World **world, TM_TeamMember **teamMember, TM_Team **teamCancelled)
{
	WorldId worldId;
	NetworkID teamMemberId;

	SLNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(worldId);
	bsIn.Read(teamMemberId);
	bool sp=false;
	*world = GetWorldWithId(worldId);
	if (*world)
	{
		*teamMember = (*world)->GetTeamMemberByNetworkID(teamMemberId);
	}
	else
	{
		*teamMember=0;
	}

	bsIn.Read(sp);
	if (sp)
	{
		NetworkID nid;
		bsIn.Read(nid);
		*teamCancelled = (*world)->GetTeamByNetworkID(nid);
	}
	else
	{
		*teamCancelled = 0;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::DecodeTeamAssigned(BitStream *bsIn, TM_World **world, TM_TeamMember **teamMember, NoTeamId &noTeamId,
										JoinTeamType &joinTeamType, DataStructures::List<TM_Team *> &newTeam,
										DataStructures::List<TM_Team *> &teamsLeft, DataStructures::List<TM_Team *> &teamsJoined
										)
{
	newTeam.Clear(true, _FILE_AND_LINE_);
	teamsLeft.Clear(true, _FILE_AND_LINE_);
	teamsJoined.Clear(true, _FILE_AND_LINE_);

	WorldId worldId;
	NetworkID teamMemberId;
	NetworkID teamId;

	bsIn->Read(worldId);
	bsIn->Read(teamMemberId);
	*world = GetWorldWithId(worldId);
	if (*world)
	{
		*teamMember = (*world)->GetTeamMemberByNetworkID(teamMemberId);
		uint16_t teamsCount;
		bsIn->Read(teamsCount);

		for (unsigned int i=0; i < teamsCount; i++)
		{
			bsIn->Read(teamId);
			TM_Team * team = (*world)->GetTeamByNetworkID(teamId);
			RakAssert(team);
			if (team)
				newTeam.Push(team, _FILE_AND_LINE_);
			// else probably didn't reference team first
		}

		if (*teamMember)
		{
			for (unsigned int i=0; i < (*teamMember)->teams.Size(); i++)
			{
				TM_Team *team = (*teamMember)->teams[i];
				if (newTeam.GetIndexOf(team)==(unsigned int)-1)
					teamsLeft.Push(team, _FILE_AND_LINE_);
			}
		}

		for (unsigned int i=0; i < newTeam.Size(); i++)
		{
			TM_Team *team = newTeam[i];
			if ((*teamMember)->teams.GetIndexOf(team)==(unsigned int)-1)
				teamsJoined.Push(team, _FILE_AND_LINE_);
		}

		bsIn->Read(noTeamId);
		bsIn->Read(joinTeamType);
	}
	else
	{
		*teamMember=0;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::Clear(void)
{
	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		worldsArray[worldsList[i]->worldId]=0;
		worldsList[i]->Clear();
		delete worldsList[i];
	}
	worldsList.Clear(false, _FILE_AND_LINE_);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::Update(void)
{
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PluginReceiveResult TeamManager::OnReceive(Packet *packet)
{
	switch (packet->data[0])
	{
	case ID_FCM2_NEW_HOST:
		{
			unsigned int i;
			for (i=0; i < worldsList.Size(); i++)
				worldsList[i]->SetHost(packet->guid);
		}
		break;
	case ID_TEAM_BALANCER_TEAM_ASSIGNED:
		{
			BitStream bsIn(packet->data,packet->length,false);
			bsIn.IgnoreBytes(sizeof(MessageID));

			ProcessTeamAssigned(&bsIn);
		}
		break;
	case ID_TEAM_BALANCER_TEAM_REQUESTED_CANCELLED:
		{
			BitStream bsIn(packet->data,packet->length,false);
			bsIn.IgnoreBytes(1);
			WorldId worldId;
			bsIn.Read(worldId);
			TM_World *world = GetWorldWithId(worldId);
			if (world==0)
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			bool validPacket = OnRemoveFromRequestedTeams(packet, world);
			if (validPacket==false)
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			break;
		}
	case ID_TEAM_BALANCER_INTERNAL:
		{
			if (packet->length>=2)
			{
				BitStream bsIn(packet->data,packet->length,false);
				bsIn.IgnoreBytes(2);
				WorldId worldId;
				bsIn.Read(worldId);
				TM_World *world = GetWorldWithId(worldId);
				if (world==0)
					return RR_STOP_PROCESSING_AND_DEALLOCATE;

				switch (packet->data[1])
				{
				case ID_RUN_UpdateListsToNoTeam:
					OnUpdateListsToNoTeam(packet, world);
					break;
				case ID_RUN_UpdateTeamsRequestedToAny:
					OnUpdateTeamsRequestedToAny(packet, world);
					break;
				case ID_RUN_JoinAnyTeam:
					OnJoinAnyTeam(packet, world);
					break;
				case ID_RUN_JoinRequestedTeam:
					OnJoinRequestedTeam(packet, world);
					break;
				case ID_RUN_UpdateTeamsRequestedToNoneAndAddTeam:
					OnUpdateTeamsRequestedToNoneAndAddTeam(packet, world);
					break;
				case ID_RUN_RemoveFromTeamsRequestedAndAddTeam:
					OnRemoveFromTeamsRequestedAndAddTeam(packet, world);
					break;
				case ID_RUN_AddToRequestedTeams:
					OnAddToRequestedTeams(packet, world);
					break;
				case ID_RUN_LeaveTeam:
					OnLeaveTeam(packet, world);
					break;
				case ID_RUN_SetMemberLimit:
					OnSetMemberLimit(packet, world);
					break;
				case ID_RUN_SetJoinPermissions:
					OnSetJoinPermissions(packet, world);
					break;
				case ID_RUN_SetBalanceTeams:
					OnSetBalanceTeams(packet, world);
					break;
				case ID_RUN_SetBalanceTeamsInitial:
					OnSetBalanceTeamsInitial(packet, world);
					break;
				}
			}
		}
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}

	return RR_CONTINUE_PROCESSING;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		worldsList[i]->OnClosedConnection(systemAddress, rakNetGUID, lostConnectionReason);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	for (unsigned int i=0; i < worldsList.Size(); i++)
	{
		worldsList[i]->OnNewConnection(systemAddress, rakNetGUID, isIncoming);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::Send( const SLNet::BitStream * bitStream, const AddressOrGUID systemIdentifier, bool broadcast )
{
	SendUnified(bitStream,HIGH_PRIORITY, RELIABLE_ORDERED, 0, systemIdentifier, broadcast);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::RemoveFromTeamsRequestedAndAddTeam(TM_TeamMember *teamMember, TM_Team *team, bool isTeamSwitch, TM_Team *teamToLeave)
{
	teamMember->RemoveFromRequestedTeams(team);
	if (isTeamSwitch)
	{
		if (teamToLeave==0)
		{
			// Leave all teams
			teamMember->RemoveFromAllTeamsInternal();
		}
		else
		{
			// Leave specific team if it exists
			teamMember->RemoveFromSpecificTeamInternal(teamToLeave);
		}
	}
	teamMember->AddToTeamList(team);
	PushTeamAssigned(teamMember);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::PushTeamAssigned(TM_TeamMember *teamMember)
{
	// Push ID_TEAM_BALANCER_TEAM_ASSIGNED locally
	SLNet::BitStream bitStream;
	bitStream.WriteCasted<MessageID>(ID_TEAM_BALANCER_TEAM_ASSIGNED);
	EncodeTeamAssigned(&bitStream, teamMember);

	PushBitStream(&bitStream);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::PushBitStream(SLNet::BitStream *bitStream)
{
	Packet *p = AllocatePacketUnified(bitStream->GetNumberOfBytesUsed());
	memcpy(p->data, bitStream->GetData(), bitStream->GetNumberOfBytesUsed());
	p->systemAddress=UNASSIGNED_SYSTEM_ADDRESS;
	p->systemAddress.systemIndex=(SystemIndex)-1;
	p->guid=UNASSIGNED_RAKNET_GUID;
	p->wasGeneratedLocally=true;
	PushBackPacketUnified(p, true);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnUpdateListsToNoTeam(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	NoTeamId noTeamId;
	bsIn.Read(noTeamId);
	if (teamMember)
	{
		teamMember->StoreLastTeams();
		teamMember->UpdateListsToNoTeam(noTeamId);
		PushTeamAssigned(teamMember);

		if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified())
		{
			world->FillRequestedSlots();
			world->EnforceTeamBalance(noTeamId);

			if (topology==TM_CLIENT_SERVER)
			{
				// Relay
				world->BroadcastToParticipants(packet->data, packet->length, packet->guid);
			}
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnUpdateTeamsRequestedToAny(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	if (teamMember)
	{
		teamMember->UpdateTeamsRequestedToAny();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnJoinAnyTeam(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	if (teamMember)
	{
		// This is a host-only operation
		RakAssert(world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified());

		teamMember->UpdateTeamsRequestedToAny();

		int resultCode;
		TM_Team *newTeam = world->JoinAnyTeam(teamMember, &resultCode);

		if (resultCode==1)
		{
			// Broadcast packet - remote systems should clear requested teams to none, and add the team we joined.
			// Broadcast includes non-host sender (all participants)
			BitStream bsOut;
			bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
			bsOut.WriteCasted<MessageID>(ID_RUN_UpdateTeamsRequestedToNoneAndAddTeam);
			bsOut.Write(world->GetWorldId());
			bsOut.Write(networkId);
			bsOut.Write(newTeam->GetNetworkID());
			world->BroadcastToParticipants(&bsOut, packet->guid);

			// Send to sender ID_TEAM_BALANCER_TEAM_ASSIGNED
			if (packet->guid!=GetMyGUIDUnified())
			{
				SLNet::BitStream bitStream;
				bitStream.WriteCasted<MessageID>(ID_TEAM_BALANCER_TEAM_ASSIGNED);
				EncodeTeamAssigned(&bitStream, teamMember);
				SendUnified(&bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
			}
		}
		else
		{
			// Relay packet to set requested teams to any
			BitStream bsOut;
			bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
			bsOut.WriteCasted<MessageID>(ID_RUN_UpdateTeamsRequestedToAny);
			bsOut.Write(world->GetWorldId());
			bsOut.Write(networkId);
			world->BroadcastToParticipants(&bsOut, packet->guid);

			bsOut.Reset();
			if (resultCode==-2)
			{
				EncodeTeamFull(&bsOut, teamMember, newTeam);
			}
			else if (resultCode==-1)
			{
				EncodeTeamLocked(&bsOut, teamMember, newTeam);
			}
			// SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
			world->BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);
			if (packet->guid!=GetMyGUIDUnified())
				PushBitStream(&bsOut);
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnJoinRequestedTeam(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	NetworkID teamToJoinNetworkId;
	bsIn.Read(teamToJoinNetworkId);
	TM_Team *teamToJoin = world->GetTeamByNetworkID(teamToJoinNetworkId);
	bool isTeamSwitch=false;
	bool switchSpecificTeam=false;
	NetworkID teamToLeaveNetworkId=UNASSIGNED_NETWORK_ID;
	TM_Team *teamToLeave=0;
	bsIn.Read(isTeamSwitch);
	if (isTeamSwitch)
	{
		bsIn.Read(switchSpecificTeam);
		if (switchSpecificTeam)
		{
			bsIn.Read(teamToLeaveNetworkId);
			teamToLeave = world->GetTeamByNetworkID(teamToLeaveNetworkId);
			if (teamToLeave==0)
				isTeamSwitch=false;
		}
	}
	if (teamToJoin && teamMember)
	{
		if (isTeamSwitch)
		{
			if (teamMember->SwitchSpecificTeamCheck(teamToJoin, teamToLeave, packet->guid==GetMyGUIDUnified())==false)
				return;

			teamMember->AddToRequestedTeams(teamToJoin, teamToLeave);
		}
		else
		{
			if (teamMember->JoinSpecificTeamCheck(teamToJoin, packet->guid==GetMyGUIDUnified())==false)
				return;

			teamMember->AddToRequestedTeams(teamToJoin);
		}

		DataStructures::List<TM_Team*> teamsWeAreLeaving;
		if (isTeamSwitch)
		{
			if (teamToLeave==0)
			{
				teamsWeAreLeaving=teamMember->teams;
			}
			else
			{
				if (teamMember->IsOnTeam(teamToLeave))
					teamsWeAreLeaving.Push(teamToLeave, _FILE_AND_LINE_);
			}

			if (teamsWeAreLeaving.Size()==0)
				isTeamSwitch=false;
		}

		int resultCode = world->JoinSpecificTeam(teamMember, teamToJoin, isTeamSwitch, teamToLeave, teamsWeAreLeaving);

		if (resultCode==1)
		{
			// Broadcast packet - remote systems should remove from requested teams and add the team we joined.
			// Broadcast includes non-host sender (all participants)
			BitStream bsOut;
			bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
			bsOut.WriteCasted<MessageID>(ID_RUN_RemoveFromTeamsRequestedAndAddTeam);
			bsOut.Write(world->GetWorldId());
			bsOut.Write(networkId);
			bsOut.Write(teamToJoin->GetNetworkID());
			bsOut.Write(isTeamSwitch);
			if (isTeamSwitch)
			{
				bsOut.Write(switchSpecificTeam);
				if (switchSpecificTeam)
					bsOut.Write(teamToLeaveNetworkId);
			}
			world->BroadcastToParticipants(&bsOut, packet->guid);

			// Send to sender ID_TEAM_BALANCER_TEAM_ASSIGNED
			if (packet->guid!=GetMyGUIDUnified())
			{
				SLNet::BitStream bitStream;
				bitStream.WriteCasted<MessageID>(ID_TEAM_BALANCER_TEAM_ASSIGNED);
				EncodeTeamAssigned(&bitStream, teamMember);
				SendUnified(&bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);
			}
		}
		else
		{
			// Relay packet to set requested teams to any
			BitStream bsOut;
			bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
			bsOut.WriteCasted<MessageID>(ID_RUN_AddToRequestedTeams);
			bsOut.Write(world->GetWorldId());
			bsOut.Write(networkId);
			bsOut.Write(teamToJoin->GetNetworkID());
			bsOut.Write(isTeamSwitch);
			if (isTeamSwitch)
			{
				bsOut.Write(switchSpecificTeam);
				if (switchSpecificTeam)
					bsOut.Write(teamToLeaveNetworkId);
			}
			world->BroadcastToParticipants(&bsOut, packet->guid);

			bsOut.Reset();
			if (resultCode==-2)
			{
				EncodeTeamFull(&bsOut, teamMember, teamToJoin);
			}
			else if (resultCode==-1)
			{
				EncodeTeamLocked(&bsOut, teamMember, teamToJoin);
			}
			// SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, false);

			world->BroadcastToParticipants(&bsOut, UNASSIGNED_RAKNET_GUID);
			if (packet->guid!=GetMyGUIDUnified())
				PushBitStream(&bsOut);
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnUpdateTeamsRequestedToNoneAndAddTeam(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	NetworkID teamNetworkId;
	bsIn.Read(teamNetworkId);
	TM_Team *team = world->GetTeamByNetworkID(teamNetworkId);

	if (team && teamMember)
	{
		teamMember->StoreLastTeams();
		teamMember->UpdateTeamsRequestedToNone();
		teamMember->AddToTeamList(team);
		world->GetTeamManager()->PushTeamAssigned(teamMember);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnRemoveFromTeamsRequestedAndAddTeam(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	NetworkID teamNetworkId;
	bsIn.Read(teamNetworkId);
	bool isTeamSwitch=false, switchSpecificTeam=false;
	NetworkID teamToLeaveNetworkId;
	TM_Team *teamToLeave=0;
	bsIn.Read(isTeamSwitch);
	if (isTeamSwitch)
	{
		bsIn.Read(switchSpecificTeam);
		if (switchSpecificTeam)
		{
			bsIn.Read(teamToLeaveNetworkId);
			teamToLeave = world->GetTeamByNetworkID(teamToLeaveNetworkId);
		}
	}

	TM_Team *team = world->GetTeamByNetworkID(teamNetworkId);
	if (team && teamMember)
	{
		teamMember->StoreLastTeams();
		if (teamToLeave)
			teamMember->RemoveFromSpecificTeamInternal(teamToLeave);
		else if (isTeamSwitch==true && switchSpecificTeam==false)
			teamMember->RemoveFromAllTeamsInternal();
		RemoveFromTeamsRequestedAndAddTeam(teamMember, team, false, 0);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnAddToRequestedTeams(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	NetworkID teamNetworkId;
	bsIn.Read(teamNetworkId);
	TM_Team *team = world->GetTeamByNetworkID(teamNetworkId);

	bool isTeamSwitch=false;
	bool switchSpecificTeam=false;
	NetworkID teamToLeaveNetworkId=UNASSIGNED_NETWORK_ID;
	TM_Team *teamToLeave=0;
	bsIn.Read(isTeamSwitch);
	if (isTeamSwitch)
	{
		bsIn.Read(switchSpecificTeam);
		if (switchSpecificTeam)
		{
			bsIn.Read(teamToLeaveNetworkId);
			teamToLeave = world->GetTeamByNetworkID(teamToLeaveNetworkId);
			if (teamToLeave==0)
				isTeamSwitch=false;
		}
	}

	if (team && teamMember)
	{
		if (isTeamSwitch)
			teamMember->AddToRequestedTeams(team, teamToLeave);
		else
			teamMember->AddToRequestedTeams(team);
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool TeamManager::OnRemoveFromRequestedTeams(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(1+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	bool hasSpecificTeam=false;
	NetworkID teamNetworkId;
	TM_Team *team;
	bsIn.Read(hasSpecificTeam);
	if (hasSpecificTeam)
	{
		bsIn.Read(teamNetworkId);
		team = world->GetTeamByNetworkID(teamNetworkId);
		if (team==0)
			return false;
	}
	else
	{
		team=0;
	}

	if (teamMember)
	{
		teamMember->RemoveFromRequestedTeams(team);

		// Relay as host
		if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified() && topology==TM_CLIENT_SERVER)
		{
			world->BroadcastToParticipants(packet->data, packet->length, packet->guid);
		}
		return true;
	}
	else
	{
		return false;
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnLeaveTeam(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID networkId;
	bsIn.Read(networkId);
	TM_TeamMember *teamMember = world->GetTeamMemberByNetworkID(networkId);
	NetworkID teamNetworkId;
	bsIn.Read(teamNetworkId);
	TM_Team *team = world->GetTeamByNetworkID(teamNetworkId);
	NoTeamId noTeamId;
	bsIn.Read(noTeamId);

	if (team && teamMember)
	{
		if (teamMember->LeaveTeamCheck(team)==false)
			return;

		teamMember->StoreLastTeams();
		teamMember->RemoveFromSpecificTeamInternal(team);
		if (teamMember->GetCurrentTeamCount()==0)
		{
			teamMember->noTeamSubcategory=noTeamId;
			teamMember->joinTeamType=JOIN_NO_TEAM;
		}
		PushTeamAssigned(teamMember);

		if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified())
		{
			// Rebalance teams
			world->FillRequestedSlots();
			world->EnforceTeamBalance(noTeamId);

			// Relay as host
			if (topology==TM_CLIENT_SERVER)
				world->BroadcastToParticipants(packet->data, packet->length, packet->guid);
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnSetMemberLimit(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID teamNetworkId;
	bsIn.Read(teamNetworkId);
	TeamMemberLimit teamMemberLimit;
	NoTeamId noTeamId;
	bsIn.Read(teamMemberLimit);
	bsIn.Read(noTeamId);

	TM_Team *team = world->GetTeamByNetworkID(teamNetworkId);
	if (team)
	{
		team->teamMemberLimit=teamMemberLimit;

		if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified())
		{
			if (packet->guid==GetMyGUIDUnified())
				world->BroadcastToParticipants(packet->data, packet->length, packet->guid);
			else
				world->BroadcastToParticipants(packet->data, packet->length, UNASSIGNED_RAKNET_GUID);
			world->FillRequestedSlots();
			world->KickExcessMembers(noTeamId);
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnSetJoinPermissions(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	NetworkID teamNetworkId;
	bsIn.Read(teamNetworkId);
	JoinPermissions joinPermissions;
	bsIn.Read(joinPermissions);

	TM_Team *team = world->GetTeamByNetworkID(teamNetworkId);
	if (team)
	{
		team->joinPermissions=joinPermissions;

		if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified())
		{
			if (packet->guid==GetMyGUIDUnified())
				world->BroadcastToParticipants(packet->data, packet->length, packet->guid);
			else
				world->BroadcastToParticipants(packet->data, packet->length, UNASSIGNED_RAKNET_GUID);
			world->FillRequestedSlots();
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnSetBalanceTeams(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	bool balanceTeams=false;
	bsIn.Read(balanceTeams);
	NoTeamId noTeamId;
	bsIn.Read(noTeamId);

	world->balanceTeamsIsActive=balanceTeams;
	if (world->GetHost()==world->GetTeamManager()->GetMyGUIDUnified())
	{
		if (packet->guid==GetMyGUIDUnified())
			world->BroadcastToParticipants(packet->data, packet->length, packet->guid);
		else
			world->BroadcastToParticipants(packet->data, packet->length, UNASSIGNED_RAKNET_GUID);
		
		if (balanceTeams)
			world->EnforceTeamBalance(noTeamId);
		else
			world->FillRequestedSlots();
	}
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void TeamManager::OnSetBalanceTeamsInitial(Packet *packet, TM_World *world)
{
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2+sizeof(WorldId));
	bool balanceTeams=false;
	bsIn.Read(balanceTeams);
	world->balanceTeamsIsActive=balanceTeams;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // _RAKNET_SUPPORT_TeamManager==1

