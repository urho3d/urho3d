/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_TeamBalancer==1

#include "slikenet/TeamBalancer.h"
#include "slikenet/BitStream.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/peerinterface.h"
#include "slikenet/Rand.h"

using namespace SLNet;

enum TeamBalancerOperations
{
	ID_STATUS_UPDATE_TO_NEW_HOST,
	ID_CANCEL_TEAM_REQUEST,
	ID_REQUEST_ANY_TEAM,
	ID_REQUEST_SPECIFIC_TEAM
};

STATIC_FACTORY_DEFINITIONS(TeamBalancer,TeamBalancer);

TeamBalancer::TeamBalancer()
{
	defaultAssigmentAlgorithm=SMALLEST_TEAM;
	forceTeamsToBeEven=false;
	lockTeams=false;
	hostGuid=UNASSIGNED_RAKNET_GUID;
}
TeamBalancer::~TeamBalancer()
{

}
void TeamBalancer::SetTeamSizeLimit(TeamId team, unsigned short limit)
{
	teamLimits.Replace(limit,0,team,_FILE_AND_LINE_);
	if (teamLimits.Size() > teamMemberCounts.Size())
		teamMemberCounts.Replace(0,0,teamLimits.Size()-1,_FILE_AND_LINE_);
}
void TeamBalancer::SetDefaultAssignmentAlgorithm(DefaultAssigmentAlgorithm daa)
{
	// Just update the default. Currently active teams are not affected.
	defaultAssigmentAlgorithm=daa;
}
void TeamBalancer::SetForceEvenTeams(bool force)
{
	// Set flag to indicate that teams should be even.
	forceTeamsToBeEven=force;

	// If teams are locked, just return.
	if (lockTeams==true)
		return;

	if (forceTeamsToBeEven==true)
	{
		// Run the even team algorithm
		EvenTeams();
	}
}
void TeamBalancer::SetLockTeams(bool lock)
{
	if (lock==lockTeams)
		return;

	// Set flag to indicate that teams can no longer be changed.
	lockTeams=lock;

	// If lock is false, and teams were set to be forced as even, then run through the even team algorithm
	if (lockTeams==false)
	{
		// Process even swaps
		TeamId i,j;
		for (i=0; i < teamMembers.Size(); i++)
		{
			if (teamMembers[i].requestedTeam!=UNASSIGNED_TEAM_ID)
			{
				for (j=i+1; j < teamMembers.Size(); j++)
				{
					if (teamMembers[j].requestedTeam==teamMembers[i].currentTeam &&
						teamMembers[i].requestedTeam==teamMembers[j].currentTeam)
					{
						SwapTeamMembersByRequest(i,j);
						NotifyTeamAssigment(i);
						NotifyTeamAssigment(j);
					}
				}
			}
		}

		if (forceTeamsToBeEven==true)
		{
			EvenTeams();
		}
		else
		{
			// Process requested team changes
			// Process movement while not full
			for (i=0; i < teamMembers.Size(); i++)
			{
				TeamId requestedTeam = teamMembers[i].requestedTeam;
				if (requestedTeam!=UNASSIGNED_TEAM_ID)
				{
					if (teamMemberCounts[requestedTeam]<teamLimits[requestedTeam])
					{
						SwitchMemberTeam(i,requestedTeam);
						NotifyTeamAssigment(i);
					}
				}
			}
		}
	}
}
void TeamBalancer::RequestSpecificTeam(NetworkID memberId, TeamId desiredTeam)
{
	bool foundMatch=false;
	for (unsigned int i=0; i < myTeamMembers.Size(); i++)
	{
		if (myTeamMembers[i].memberId==memberId)
		{
			foundMatch=true;
			if (myTeamMembers[i].requestedTeam==desiredTeam && myTeamMembers[i].currentTeam==desiredTeam)
			{
				return;
			}
			else
			{
				myTeamMembers[i].requestedTeam=desiredTeam;
			}
		}
	}

	if (foundMatch==false)
	{
		MyTeamMembers mtm;
		mtm.currentTeam=UNASSIGNED_TEAM_ID;
		mtm.memberId=memberId;
		mtm.requestedTeam=desiredTeam;
		myTeamMembers.Push(mtm, _FILE_AND_LINE_);
	}

	// Send desiredTeam to the current host.
	// Also flag that we have requested a team, and record desiredTeam in case the host changes and it needs to be resent.
	BitStream bsOut;
	bsOut.Write((MessageID)ID_TEAM_BALANCER_INTERNAL);
	bsOut.Write((MessageID)ID_REQUEST_SPECIFIC_TEAM);
	bsOut.Write(memberId);
	bsOut.Write(desiredTeam);
	rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,hostGuid,false);
}
void TeamBalancer::CancelRequestSpecificTeam(NetworkID memberId)
{
	for (unsigned int i=0; i < myTeamMembers.Size(); i++)
	{
		if (myTeamMembers[i].memberId==memberId)
		{
			myTeamMembers[i].requestedTeam=UNASSIGNED_TEAM_ID;

			// Send packet to the host to remove our request flag.
			BitStream bsOut;
			bsOut.Write((MessageID)ID_TEAM_BALANCER_INTERNAL);
			bsOut.Write((MessageID)ID_CANCEL_TEAM_REQUEST);
			bsOut.Write(memberId);
			rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,hostGuid,false);

			return;
		}
	}
}
void TeamBalancer::RequestAnyTeam(NetworkID memberId)
{
	bool foundMatch=false;

	for (unsigned int i=0; i < myTeamMembers.Size(); i++)
	{
		if (myTeamMembers[i].memberId==memberId)
		{
			foundMatch=true;
			if (myTeamMembers[i].currentTeam!=UNASSIGNED_TEAM_ID)
				return;
			else
				myTeamMembers[i].requestedTeam=UNASSIGNED_TEAM_ID;
			break;
		}
	}

	if (foundMatch==false)
	{
		MyTeamMembers mtm;
		mtm.currentTeam=UNASSIGNED_TEAM_ID;
		mtm.memberId=memberId;
		mtm.requestedTeam=UNASSIGNED_TEAM_ID;
		myTeamMembers.Push(mtm, _FILE_AND_LINE_);
	}

	// Else send to the current host that we need a team.
	BitStream bsOut;
	bsOut.Write((MessageID)ID_TEAM_BALANCER_INTERNAL);
	bsOut.Write((MessageID)ID_REQUEST_ANY_TEAM);
	bsOut.Write(memberId);
	rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,hostGuid,false);
}
TeamId TeamBalancer::GetMyTeam(NetworkID memberId) const
{
	// Return team returned by last ID_TEAM_BALANCER_TEAM_ASSIGNED packet
	for (unsigned int i=0; i < myTeamMembers.Size(); i++)
	{
		if (myTeamMembers[i].memberId==memberId)
		{
			return myTeamMembers[i].currentTeam;
		}
	}

	return UNASSIGNED_TEAM_ID;
}
void TeamBalancer::DeleteMember(NetworkID memberId)
{
	for (unsigned int i=0; i < myTeamMembers.Size(); i++)
	{
		if (myTeamMembers[i].memberId==memberId)
		{
			myTeamMembers.RemoveAtIndexFast(i);
			break;
		}
	}

	for (unsigned int i=0; i < teamMembers.Size(); i++)
	{
		if (teamMembers[i].memberId==memberId)
		{
			RemoveTeamMember(i);
			break;
		}
	}
}
PluginReceiveResult TeamBalancer::OnReceive(Packet *packet)
{
	switch (packet->data[0])
	{
		case ID_FCM2_NEW_HOST:
		{
			hostGuid=packet->guid;

			if (myTeamMembers.Size()>0)
			{
				BitStream bsOut;
				bsOut.Write((MessageID)ID_TEAM_BALANCER_INTERNAL);
				bsOut.Write((MessageID)ID_STATUS_UPDATE_TO_NEW_HOST);
				
				bsOut.WriteCasted<uint8_t>(myTeamMembers.Size());
				for (unsigned int i=0; i < myTeamMembers.Size(); i++)
				{
					bsOut.Write(myTeamMembers[i].memberId);
					bsOut.Write(myTeamMembers[i].currentTeam);
					bsOut.Write(myTeamMembers[i].requestedTeam);
				}
				rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,hostGuid,false);
			}
		}
		break;
		case ID_TEAM_BALANCER_INTERNAL:
		{
			if (packet->length>=2)
			{
				switch (packet->data[1])
				{
					case ID_STATUS_UPDATE_TO_NEW_HOST:
						OnStatusUpdateToNewHost(packet);
						break;
					case ID_CANCEL_TEAM_REQUEST:
						OnCancelTeamRequest(packet);
						break;
					case ID_REQUEST_ANY_TEAM:
						OnRequestAnyTeam(packet);
						break;
					case ID_REQUEST_SPECIFIC_TEAM:
						OnRequestSpecificTeam(packet);
						break;
				}
			}
		}
		return RR_STOP_PROCESSING_AND_DEALLOCATE;

		case ID_TEAM_BALANCER_TEAM_ASSIGNED:
		{
			return OnTeamAssigned(packet);
		}

		case ID_TEAM_BALANCER_REQUESTED_TEAM_FULL:
		{
			return OnRequestedTeamChangePending(packet);
		}

		case ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED:
		{
			return OnTeamsLocked(packet);
		}
	}

	// Got RequestSpecificTeam
	// If teams are locked
	// - If this user already has a team, return ID_TEAM_BALANCER_TEAMS_LOCKED
	// - This user does not already have a team. Assign a team as if the user called RequestAnyTeam(), with a preference for the requested team. Return ID_TEAM_BALANCER_TEAM_ASSIGNED once the team has been assigned.
	// If teams are not locked
	// - If even team balancing is on, only assign this user if this would not cause teams to be unbalanced. If teams WOULD be unbalanced, then flag this user as wanting to join this team. Return ID_TEAM_BALANCER_REQUESTED_TEAM_CHANGE_PENDING
	// - If the destination team is full, flag this user as wanting to join this team. Return ID_TEAM_BALANCER_REQUESTED_TEAM_CHANGE_PENDING
	// - Else, join this team. Return ID_TEAM_BALANCER_TEAM_ASSIGNED

	// Got RequestAnyTeam
	// Put user on a team following the algorithm. No team is set as preferred.

	return RR_CONTINUE_PROCESSING;
}
void TeamBalancer::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) systemAddress;
	(void) lostConnectionReason;

	RemoveByGuid(rakNetGUID);
}
void TeamBalancer::OnAttach(void)
{
	hostGuid = rakPeerInterface->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);
}
void TeamBalancer::RemoveByGuid(RakNetGUID rakNetGUID)
{
	// If we are the host, and the closed connection has a team, and teams are not locked:
	if (WeAreHost())
	{
		unsigned int droppedMemberIndex=0;
		while (droppedMemberIndex < teamMembers.Size())
		{
			if (teamMembers[droppedMemberIndex].memberGuid==rakNetGUID)
			{
				TeamId droppedTeam = teamMembers[droppedMemberIndex].currentTeam;
				RemoveTeamMember(droppedMemberIndex);
				if (lockTeams==false)
				{
					if (forceTeamsToBeEven)
					{
						// - teams were forced to be even, then run the even team algorithm
						EvenTeams();
					}
					else
					{
						// - teams were NOT forced to be even, and the team the dropped player on was full, then move users wanting to join that team (if any)
						if (teamMemberCounts[ droppedTeam ]==teamLimits[ droppedTeam ]-1)
						{
							MoveMemberThatWantsToJoinTeam(droppedTeam);
						}
					}
				}
			}
			else
			{
				droppedMemberIndex++;
			}
		}
	}
}
void TeamBalancer::OnStatusUpdateToNewHost(Packet *packet)
{
	if (WeAreHost()==false)
		return;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2);
	uint8_t requestedTeamChangeListSize;
	bsIn.Read(requestedTeamChangeListSize);
	TeamMember tm;
	tm.memberGuid=packet->guid;
	for (uint8_t i=0; i < requestedTeamChangeListSize; i++)
	{
		bsIn.Read(tm.memberId);
		bsIn.Read(tm.currentTeam);
		bsIn.Read(tm.requestedTeam);

		if (tm.currentTeam!=UNASSIGNED_TEAM_ID && tm.currentTeam>teamLimits.Size())
		{
			RakAssert("Current team out of range in TeamBalancer::OnStatusUpdateToNewHost" && 0);
			return;
		}

		if (tm.requestedTeam!=UNASSIGNED_TEAM_ID && tm.requestedTeam>teamLimits.Size())
		{
			RakAssert("Requested team out of range in TeamBalancer::OnStatusUpdateToNewHost" && 0);
			return;
		}

		if (tm.currentTeam==UNASSIGNED_TEAM_ID && tm.requestedTeam==UNASSIGNED_TEAM_ID)
			return;

		unsigned int memberIndex = GetMemberIndex(tm.memberId, packet->guid);
		if (memberIndex==(unsigned int) -1)
		{
			// Add this system (by GUID) to the list of members if he is not already there
			// Also update his requested team flag.
			// Do not process balancing on requested teams, since we don't necessarily have all data from all systems yet and hopefully the state during the host migration was stable.
			if (tm.currentTeam==UNASSIGNED_TEAM_ID)
			{
				// Assign a default team, then add team member
				if (tm.requestedTeam==UNASSIGNED_TEAM_ID)
				{
					// Assign a default team
					tm.currentTeam=GetNextDefaultTeam();
				}
				else
				{
					// Assign to requested team if possible. Otherwise, assign to a default team
					if (TeamWouldBeOverpopulatedOnAddition(tm.requestedTeam, teamMembers.Size())==false)
					{
						tm.currentTeam=tm.requestedTeam;
					}
					else
					{
						tm.currentTeam=GetNextDefaultTeam();
					}
				}
			}

			if (tm.currentTeam==UNASSIGNED_TEAM_ID)
			{
				RakAssert("Too many members asking for teams!" && 0);
				return;
			}
			NotifyTeamAssigment(AddTeamMember(tm));
		}
	}
}
void TeamBalancer::OnCancelTeamRequest(Packet *packet)
{
	if (WeAreHost()==false)
		return;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2);
	NetworkID memberId;
	bsIn.Read(memberId);

	unsigned int memberIndex = GetMemberIndex(memberId, packet->guid);
	if (memberIndex!=(unsigned int)-1)
		teamMembers[memberIndex].requestedTeam=UNASSIGNED_TEAM_ID;
}
void TeamBalancer::OnRequestAnyTeam(Packet *packet)
{
	if (WeAreHost()==false)
		return;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2);
	NetworkID memberId;
	bsIn.Read(memberId);

	unsigned int memberIndex = GetMemberIndex(memberId, packet->guid);
	if (memberIndex==(unsigned int)-1)
	{
		TeamMember tm;
		tm.currentTeam=GetNextDefaultTeam();
		tm.requestedTeam=UNASSIGNED_TEAM_ID;
		tm.memberGuid=packet->guid;
		tm.memberId=memberId;
		if (tm.currentTeam==UNASSIGNED_TEAM_ID)
		{
			RakAssert("Too many members asking for teams!" && 0);
			return;
		}
		NotifyTeamAssigment(AddTeamMember(tm));
	}
}
void TeamBalancer::OnRequestSpecificTeam(Packet *packet)
{
	if (WeAreHost()==false)
		return;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(2);
	TeamMember tm;
	bsIn.Read(tm.memberId);
	bsIn.Read(tm.requestedTeam);

	unsigned int memberIndex = GetMemberIndex(tm.memberId, packet->guid);
	if (tm.requestedTeam==UNASSIGNED_TEAM_ID)
	{
		NotifyNoTeam(tm.memberId, packet->guid);
		if (memberIndex != (unsigned int) -1)
			RemoveTeamMember(memberIndex);
		return;
	}

	if (tm.requestedTeam>teamLimits.Size())
	{
		RakAssert("Requested team out of range in TeamBalancer::OnRequestSpecificTeam" && 0);
		return;
	}
	if (memberIndex==(unsigned int) -1)
	{
		tm.memberGuid=packet->guid;

		// Assign to requested team if possible. Otherwise, assign to a default team
		if (TeamWouldBeOverpopulatedOnAddition(tm.requestedTeam, teamMembers.Size())==false)
		{
			tm.currentTeam=tm.requestedTeam;
			tm.requestedTeam=UNASSIGNED_TEAM_ID;
		}
		else
		{
			tm.currentTeam=GetNextDefaultTeam();
		}
		if (tm.currentTeam==UNASSIGNED_TEAM_ID)
		{
			RakAssert("Too many members asking for teams!" && 0);
			return;
		}
		NotifyTeamAssigment(AddTeamMember(tm));
	}
	else
	{
		teamMembers[memberIndex].requestedTeam=tm.requestedTeam;
		TeamId oldTeamThisUserWasOn = teamMembers[memberIndex].currentTeam;

		if (lockTeams)
		{
			NotifyTeamsLocked(packet->guid, tm.requestedTeam);
			return;
		}

		// Assign to requested team if possible. Otherwise, assign to a default team
		if (TeamsWouldBeEvenOnSwitch(tm.requestedTeam,oldTeamThisUserWasOn)==true)
		{
			SwitchMemberTeam(memberIndex,tm.requestedTeam);
			NotifyTeamAssigment(memberIndex);
		}
		else
		{
			// If someone wants to join this user's old team, and we want to join their team, they can swap
			unsigned int swappableMemberIndex;
			for (swappableMemberIndex=0; swappableMemberIndex < teamMembers.Size(); swappableMemberIndex++)
			{
				if (teamMembers[swappableMemberIndex].currentTeam==tm.requestedTeam && teamMembers[swappableMemberIndex].requestedTeam==oldTeamThisUserWasOn)
					break;
			}

			if (swappableMemberIndex!=teamMembers.Size())
			{
				SwapTeamMembersByRequest(memberIndex,swappableMemberIndex);
				NotifyTeamAssigment(memberIndex);
				NotifyTeamAssigment(swappableMemberIndex);
			}
			else
			{
				// Full or would not be even
				NotifyTeamSwitchPending(packet->guid, tm.requestedTeam, tm.memberId);
			}
		}	
	}
}
unsigned int TeamBalancer::GetMemberIndex(NetworkID memberId, RakNetGUID guid) const
{
	for (unsigned int i=0; i < teamMembers.Size(); i++)
	{
		if (teamMembers[i].memberGuid==guid && teamMembers[i].memberId==memberId)
			return i;
	}
	return (unsigned int) -1;
}
unsigned int TeamBalancer::AddTeamMember(const TeamMember &tm)
{
	if (tm.currentTeam>teamLimits.Size())
	{
		RakAssert("TeamBalancer::AddTeamMember team index out of bounds" && 0);
		return (unsigned int) -1;
	}

	RakAssert(tm.currentTeam!=UNASSIGNED_TEAM_ID);

	teamMembers.Push(tm,_FILE_AND_LINE_);
	if (teamMemberCounts.Size()<tm.currentTeam)
		teamMemberCounts.Replace(1,0,tm.currentTeam,_FILE_AND_LINE_);
	else
		teamMemberCounts[tm.currentTeam]=teamMemberCounts[tm.currentTeam]+1;
	return teamMembers.Size()-1;
}
void TeamBalancer::RemoveTeamMember(unsigned int index)
{
	RakAssert( teamMemberCounts[ teamMembers[index].currentTeam ] != 0);
	teamMemberCounts[ teamMembers[index].currentTeam ]=teamMemberCounts[ teamMembers[index].currentTeam ]-1;
	teamMembers.RemoveAtIndexFast(index);
}
void TeamBalancer::GetMinMaxTeamMembers(int &minMembersOnASingleTeam, int &maxMembersOnASingleTeam)
{
	minMembersOnASingleTeam = teamMembers.Size()/teamLimits.Size();
	if ((teamMembers.Size() % teamLimits.Size()) == 0)
		maxMembersOnASingleTeam = minMembersOnASingleTeam;
	else
		maxMembersOnASingleTeam = minMembersOnASingleTeam+1;
}
void TeamBalancer::EvenTeams(void)
{
	// Ensure all teams are even. If not, pick players at random from overpopulated teams, and move to underpopulated teams.
	int minMembersOnASingleTeam;
	int maxMembersOnASingleTeam;
	GetMinMaxTeamMembers(minMembersOnASingleTeam,maxMembersOnASingleTeam);

	// First select among players that have requested to switch teams, if any, before choosing players that did not want to switch teams.
	// Players that are moved should be notified of ID_TEAM_BALANCER_TEAM_ASSIGNED
	DataStructures::List<TeamId> overpopulatedTeams;
	TeamId teamMemberCountsIndex;
	unsigned int memberIndexToSwitch;
	for (teamMemberCountsIndex=0; teamMemberCountsIndex<teamMemberCounts.Size(); teamMemberCountsIndex++)
	{
		while (teamMemberCounts[teamMemberCountsIndex]<minMembersOnASingleTeam && teamMemberCounts[teamMemberCountsIndex]<teamLimits[teamMemberCountsIndex])
		{
			GetOverpopulatedTeams(overpopulatedTeams,maxMembersOnASingleTeam);
			RakAssert(overpopulatedTeams.Size()>0);
			memberIndexToSwitch=GetMemberIndexToSwitchTeams(overpopulatedTeams,teamMemberCountsIndex);
			RakAssert(memberIndexToSwitch!=(unsigned int)-1);
			SwitchMemberTeam(memberIndexToSwitch,teamMemberCountsIndex);
			// Tell this member he switched teams
			NotifyTeamAssigment(memberIndexToSwitch);
		}
	}
}
unsigned int TeamBalancer::GetMemberIndexToSwitchTeams(const DataStructures::List<TeamId> &sourceTeamNumbers, TeamId targetTeamNumber)
{
	DataStructures::List<unsigned int> preferredSwapIndices;
	DataStructures::List<unsigned int> potentialSwapIndices;
	unsigned int i,j;
	for (j=0; j < sourceTeamNumbers.Size(); j++)
	{
		RakAssert(sourceTeamNumbers[j]!=targetTeamNumber);
		for (i=0; i < teamMembers.Size(); i++)
		{
			if (teamMembers[i].currentTeam==sourceTeamNumbers[j])
			{
				if (teamMembers[i].requestedTeam==targetTeamNumber)
					preferredSwapIndices.Push(i,_FILE_AND_LINE_);
				else
					potentialSwapIndices.Push(i,_FILE_AND_LINE_);
			}
		}
	}

	if (preferredSwapIndices.Size()>0)
	{
		return preferredSwapIndices[ randomMT() % preferredSwapIndices.Size() ];
	}
	else if (potentialSwapIndices.Size()>0)
	{
		return potentialSwapIndices[ randomMT() % potentialSwapIndices.Size() ];
	}
	else
	{
		return (unsigned int) -1;
	}
}
void TeamBalancer::SwitchMemberTeam(unsigned int teamMemberIndex, TeamId destinationTeam)
{
	teamMemberCounts[ teamMembers[teamMemberIndex].currentTeam ]=teamMemberCounts[ teamMembers[teamMemberIndex].currentTeam ]-1;
	teamMemberCounts[ destinationTeam ]=teamMemberCounts[ destinationTeam ]+1;
	teamMembers[teamMemberIndex].currentTeam=destinationTeam;
	if (teamMembers[teamMemberIndex].requestedTeam==destinationTeam)
		teamMembers[teamMemberIndex].requestedTeam=UNASSIGNED_TEAM_ID;
}
void TeamBalancer::GetOverpopulatedTeams(DataStructures::List<TeamId> &overpopulatedTeams, int maxTeamSize)
{
	overpopulatedTeams.Clear(true,_FILE_AND_LINE_);
	for (TeamId i=0; i < teamMemberCounts.Size(); i++)
	{
		if (teamMemberCounts[i]>=maxTeamSize)
			overpopulatedTeams.Push(i,_FILE_AND_LINE_);
	}
}
void TeamBalancer::NotifyTeamAssigment(unsigned int teamMemberIndex)
{
	RakAssert(teamMemberIndex < teamMembers.Size());
	if (teamMemberIndex>=teamMembers.Size())
		return;

	BitStream bsOut;
	bsOut.Write((MessageID)ID_TEAM_BALANCER_TEAM_ASSIGNED);
	bsOut.Write(teamMembers[teamMemberIndex].currentTeam);
	bsOut.Write(teamMembers[teamMemberIndex].memberId);
	rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,teamMembers[teamMemberIndex].memberGuid,false);
}
bool TeamBalancer::WeAreHost(void) const
{
	return hostGuid==rakPeerInterface->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);
}
PluginReceiveResult TeamBalancer::OnTeamAssigned(Packet *packet)
{
	if (packet->guid!=hostGuid)
		return RR_STOP_PROCESSING_AND_DEALLOCATE;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(1);

	MyTeamMembers mtm;
	bsIn.Read(mtm.currentTeam);
	bsIn.Read(mtm.memberId);
	mtm.requestedTeam=UNASSIGNED_TEAM_ID;

	bool foundMatch=false;
	for (unsigned int i=0; i < myTeamMembers.Size(); i++)
	{
		if (myTeamMembers[i].memberId==mtm.memberId)
		{
			foundMatch=true;
			if (myTeamMembers[i].requestedTeam==mtm.currentTeam)
				myTeamMembers[i].requestedTeam=UNASSIGNED_TEAM_ID;
			myTeamMembers[i].currentTeam=mtm.currentTeam;
			break;
		}
	}

	if (foundMatch==false)
	{
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}

	return RR_CONTINUE_PROCESSING;
}
PluginReceiveResult TeamBalancer::OnRequestedTeamChangePending(Packet *packet)
{
	if (packet->guid!=hostGuid)
		return RR_STOP_PROCESSING_AND_DEALLOCATE;

	return RR_CONTINUE_PROCESSING;
}
PluginReceiveResult TeamBalancer::OnTeamsLocked(Packet *packet)
{
	if (packet->guid!=hostGuid)
		return RR_STOP_PROCESSING_AND_DEALLOCATE;

	return RR_CONTINUE_PROCESSING;
}
TeamId TeamBalancer::GetNextDefaultTeam(void)
{
	// Accounting for team balancing and team limits, get the team a player should be placed on
	switch (defaultAssigmentAlgorithm)
	{
		case SMALLEST_TEAM:
		{
			return GetSmallestNonFullTeam();
		}

		case FILL_IN_ORDER:
		{
			return GetFirstNonFullTeam();
		}

		default:
		{
			RakAssert("TeamBalancer::GetNextDefaultTeam unknown algorithm enumeration" && 0);
			return UNASSIGNED_TEAM_ID;
		}
	}
}
bool TeamBalancer::TeamWouldBeOverpopulatedOnAddition(TeamId teamId, unsigned int teamMemberSize)
{
	// Accounting for team balancing and team limits, would this team be overpopulated if a member was added to it?
	if (teamMemberCounts[teamId]>=teamLimits[teamId])
	{
		return true;
	}

	if (forceTeamsToBeEven)
	{
		int allowedLimit = teamMemberSize/teamLimits.Size() + 1;
		return teamMemberCounts[teamId]>=allowedLimit;
	}

	return false;
}
bool TeamBalancer::TeamWouldBeUnderpopulatedOnLeave(TeamId teamId, unsigned int teamMemberSize)
{
	if (forceTeamsToBeEven)
	{
		unsigned int minMembersOnASingleTeam = (teamMemberSize-1)/teamLimits.Size();
		return teamMemberCounts[teamId]<=minMembersOnASingleTeam;
	}
	return false;
}
TeamId TeamBalancer::GetSmallestNonFullTeam(void) const
{
	TeamId idx;
	unsigned long smallestTeamCount=MAX_UNSIGNED_LONG;
	TeamId smallestTeamIndex = UNASSIGNED_TEAM_ID;
	for (idx=0; idx < teamMemberCounts.Size(); idx++)
	{
		if (teamMemberCounts[idx]<smallestTeamCount && teamMemberCounts[idx]<teamLimits[idx])
		{
			smallestTeamCount=teamMemberCounts[idx];
			smallestTeamIndex=idx;
		}
	}
	return smallestTeamIndex;
}
TeamId TeamBalancer::GetFirstNonFullTeam(void) const
{
	TeamId idx;
	for (idx=0; idx < teamMemberCounts.Size(); idx++)
	{
		if (teamMemberCounts[idx]<teamLimits[idx])
		{
			return idx;
		}
	}
	return UNASSIGNED_TEAM_ID;
}
void TeamBalancer::MoveMemberThatWantsToJoinTeam(TeamId teamId)
{
	RakAssert(forceTeamsToBeEven==false && lockTeams==false);

	do 
	{
		teamId = MoveMemberThatWantsToJoinTeamInternal(teamId);
	} while (teamId!=UNASSIGNED_TEAM_ID);
}
TeamId TeamBalancer::MoveMemberThatWantsToJoinTeamInternal(TeamId teamId)
{
	DataStructures::List<TeamId> membersThatWantToJoinTheTeam;
	for (TeamId i=0; i < teamMembers.Size(); i++)
	{
		if (teamMembers[i].requestedTeam==teamId)
			membersThatWantToJoinTheTeam.Push(i,_FILE_AND_LINE_);
	}

	if (membersThatWantToJoinTheTeam.Size()>0)
	{
		TeamId oldTeam;
		unsigned int swappedMemberIndex = membersThatWantToJoinTheTeam[ randomMT() % membersThatWantToJoinTheTeam.Size() ];
		oldTeam=teamMembers[swappedMemberIndex].currentTeam;
		SwitchMemberTeam(swappedMemberIndex,teamId);
		NotifyTeamAssigment(swappedMemberIndex);
		return oldTeam;
	}
	return UNASSIGNED_TEAM_ID;
}
void TeamBalancer::NotifyTeamsLocked(RakNetGUID target, TeamId requestedTeam)
{
	BitStream bsOut;
	bsOut.Write((MessageID)ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED);
	bsOut.Write(requestedTeam);
	rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,target,false);
}
void TeamBalancer::NotifyTeamSwitchPending(RakNetGUID target, TeamId requestedTeam, NetworkID memberId)
{
	BitStream bsOut;
	bsOut.Write((MessageID)ID_TEAM_BALANCER_REQUESTED_TEAM_FULL);
	bsOut.Write(requestedTeam);
	bsOut.Write(memberId);
	rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,target,false);
}
void TeamBalancer::SwapTeamMembersByRequest(unsigned int memberIndex1, unsigned int memberIndex2)
{
	TeamId index1Team = teamMembers[memberIndex1].currentTeam;
	teamMembers[memberIndex1].currentTeam=teamMembers[memberIndex2].currentTeam;
	teamMembers[memberIndex2].currentTeam=index1Team;
	teamMembers[memberIndex1].requestedTeam=UNASSIGNED_TEAM_ID;
	teamMembers[memberIndex2].requestedTeam=UNASSIGNED_TEAM_ID;
}
void TeamBalancer::NotifyNoTeam(NetworkID memberId, RakNetGUID target)
{
	BitStream bsOut;
	bsOut.Write((MessageID)ID_TEAM_BALANCER_TEAM_ASSIGNED);
	bsOut.Write((unsigned char)UNASSIGNED_TEAM_ID);
	bsOut.Write(memberId);
	rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,target,false);
}
bool TeamBalancer::TeamsWouldBeEvenOnSwitch(TeamId t1, TeamId t2)
{
	RakAssert(teamMembers.Size()!=0);
	return TeamWouldBeOverpopulatedOnAddition(t1, teamMembers.Size()-1)==false &&
		TeamWouldBeUnderpopulatedOnLeave(t2, teamMembers.Size()-1)==false;
}

#endif // _RAKNET_SUPPORT_*
