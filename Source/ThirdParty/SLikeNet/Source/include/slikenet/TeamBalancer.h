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

/// \file TeamBalancer.h
/// \brief Set and network team selection (supports peer to peer or client/server)
/// \details Automatically handles transmission and resolution of team selection, including team switching and balancing
/// \deprecated Use TeamManager intead
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_TeamBalancer==1

#ifndef __TEAM_BALANCER_H
#define __TEAM_BALANCER_H

#include "PluginInterface2.h"
#include "memoryoverride.h"
#include "NativeTypes.h"
#include "DS_List.h"
#include "string.h"

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

/// \defgroup TEAM_BALANCER_GROUP TeamBalancer
/// \brief Set and network team selection (supports peer to peer or client/server)
/// \details Automatically handles transmission and resolution of team selection, including team switching and balancing
/// \deprecated Use TeamManager intead
/// \ingroup PLUGINS_GROUP

/// 0...254 for your team number identifiers. 255 is reserved as undefined.
/// \deprecated Use TeamManager intead
/// \ingroup TEAM_BALANCER_GROUP
typedef unsigned char TeamId;

#define UNASSIGNED_TEAM_ID 255

/// \brief Set and network team selection (supports peer to peer or client/server)
/// \details Automatically handles transmission and resolution of team selection, including team switching and balancing.<BR>
/// Usage: TODO
/// \deprecated Use TeamManager intead
/// \ingroup TEAM_BALANCER_GROUP
class RAK_DLL_EXPORT TeamBalancer : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(TeamBalancer)

	TeamBalancer();
	virtual ~TeamBalancer();

	/// \brief Set the limit to the number of players on the specified team
	/// \details SetTeamSizeLimit() must be called on the host, so the host can enforce the maximum number of players on each team.
	/// SetTeamSizeLimit() can be called on all systems if desired - for example, in a P2P environment you may wish to call it on all systems in advanced in case you become host.
	/// \param[in] team Which team to set the limit for
	/// \param[in] limit The maximum number of people on this team
	void SetTeamSizeLimit(TeamId team, unsigned short limit);

	enum DefaultAssigmentAlgorithm
	{
		/// Among all the teams, join the team with the smallest number of players
		SMALLEST_TEAM,
		/// Join the team with the lowest index that has open slots.
		FILL_IN_ORDER
	};
	/// \brief Determine how players' teams will be set when they call RequestAnyTeam()
	/// \details Based on the specified enumeration, a player will join a team automatically
	/// Defaults to SMALLEST_TEAM
	/// This function is only used by the host
	/// \param[in] daa Enumeration describing the algorithm to use
	void SetDefaultAssignmentAlgorithm(DefaultAssigmentAlgorithm daa);

	/// \brief By default, teams can be unbalanced up to the team size limit defined by SetTeamSizeLimits()
	/// \details If SetForceEvenTeams(true) is called on the host, then teams cannot be unbalanced by more than 1 player
	/// If teams are uneven at the time that SetForceEvenTeams(true) is called, players at randomly will be switched, and will be notified of ID_TEAM_BALANCER_TEAM_ASSIGNED
	/// If players disconnect from the host such that teams would not be even, and teams are not locked, then a player from the largest team is randomly moved to even the teams.
	/// Defaults to false
	/// \note SetLockTeams(true) takes priority over SetForceEvenTeams(), so if teams are currently locked, this function will have no effect until teams become unlocked.
	/// \param[in] force True to force even teams. False to allow teams to not be evenly matched
	void SetForceEvenTeams(bool force);

	/// \brief If set, calls to RequestSpecificTeam() and RequestAnyTeam() will return the team you are currently on.
	/// \details However, if those functions are called and you do not have a team, then you will be assigned to a default team according to SetDefaultAssignmentAlgorithm() and possibly SetForceEvenTeams(true)
	/// If \a lock is false, and SetForceEvenTeams() was called with \a force as true, and teams are currently uneven, they will be made even, and those players randomly moved will get ID_TEAM_BALANCER_TEAM_ASSIGNED
	/// Defaults to false
	/// \param[in] lock True to lock teams, false to unlock
	void SetLockTeams(bool lock);

	/// Set your requested team. UNASSIGNED_TEAM_ID means no team.
	/// After enough time for network communication, ID_TEAM_BALANCER_SET_TEAM will be returned with your current team, or
	/// If team switch is not possible, ID_TEAM_BALANCER_REQUESTED_TEAM_CHANGE_PENDING or ID_TEAM_BALANCER_TEAMS_LOCKED will be returned.
	/// In the case of ID_TEAM_BALANCER_REQUESTED_TEAM_CHANGE_PENDING the request will stay in memory. ID_TEAM_BALANCER_SET_TEAM will be returned when someone on the desired team leaves or wants to switch to your team.
	/// If SetLockTeams(true) is called while you have a request pending, you will get ID_TEAM_BALANCER_TEAMS_LOCKED
	/// \pre Call SetTeamSizeLimits() on the host and call SetHostGuid() on this system. If the host is not running the TeamBalancer plugin or did not have SetTeamSizeLimits() called, then you will not get any response.
	/// \param[in] memberId If there is more than one player per computer, this number identifies that player. Use any consistent value, such as UNASSIGNED_NETWORK_ID if there is only one player.
	/// \param[in] desiredTeam An index representing your team number. The index should range from 0 to one less than the size of the list passed to SetTeamSizeLimits() on the host. You can also pass UNASSIGNED_TEAM_ID to not be on any team (such as if spectating)
	void RequestSpecificTeam(NetworkID memberId, TeamId desiredTeam);

	/// If ID_TEAM_BALANCER_REQUESTED_TEAM_CHANGE_PENDING is returned after a call to RequestSpecificTeam(), the request will stay in memory on the host and execute when available, or until the teams become locked.
	/// You can cancel the request by calling CancelRequestSpecificTeam(), in which case you will stay on your existing team.
	/// \note Due to latency, even after calling CancelRequestSpecificTeam() you may still get ID_TEAM_BALANCER_SET_TEAM if the packet was already in transmission.
	/// \param[in] memberId If there is more than one player per computer, this number identifies that player. Use any consistent value, such as UNASSIGNED_NETWORK_ID if there is only one player.
	void CancelRequestSpecificTeam(NetworkID memberId);

	/// Allow host to pick your team, based on whatever algorithm it uses for default team assignments.
	/// This only has an effect if you are not currently on a team (GetMyTeam() returns UNASSIGNED_TEAM_ID)
	/// \pre Call SetTeamSizeLimits() on the host and call SetHostGuid() on this system
	/// \param[in] memberId If there is more than one player per computer, this number identifies that player. Use any consistent value, such as UNASSIGNED_NETWORK_ID if there is only one player.
	void RequestAnyTeam(NetworkID memberId);

	/// Returns your team.
	/// As your team changes, you are notified through the ID_TEAM_BALANCER_TEAM_ASSIGNED packet in byte 1.
	/// Returns UNASSIGNED_TEAM_ID initially
	/// \pre For this to return anything other than UNASSIGNED_TEAM_ID, connect to a properly initialized host and RequestSpecificTeam() or RequestAnyTeam() first
	/// \param[in] memberId If there is more than one player per computer, this number identifies that player. Use any consistent value, such as UNASSIGNED_NETWORK_ID if there is only one player.
	/// \return UNASSIGNED_TEAM_ID for no team. Otherwise, the index should range from 0 to one less than the size of the list passed to SetTeamSizeLimits() on the host
	TeamId GetMyTeam(NetworkID memberId) const;

	/// If you called RequestSpecificTeam() or RequestAnyTeam() with a value for \a memberId that
	/// Has since been deleted, call DeleteMember(). to notify this plugin of that event.
	/// Not necessary with only one team member per system
	/// \param[in] memberId If there is more than one player per computer, this number identifies that player. Use any consistent value, such as UNASSIGNED_NETWORK_ID if there is only one player.
	void DeleteMember(NetworkID memberId);

	struct TeamMember
	{
		RakNetGUID memberGuid;
		NetworkID memberId;
		TeamId currentTeam;
		TeamId requestedTeam;
	};
	struct MyTeamMembers
	{
		NetworkID memberId;
		TeamId currentTeam;
		TeamId requestedTeam;
	};

protected:

	/// \internal
	virtual PluginReceiveResult OnReceive(Packet *packet);
	/// \internal
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	/// \internal
	void OnAttach(void);

	void OnStatusUpdateToNewHost(Packet *packet);
	void OnCancelTeamRequest(Packet *packet);
	void OnRequestAnyTeam(Packet *packet);
	void OnRequestSpecificTeam(Packet *packet);

	RakNetGUID hostGuid;
	DefaultAssigmentAlgorithm defaultAssigmentAlgorithm;
	bool forceTeamsToBeEven;
	bool lockTeams;
	// So if we lose the connection while processing, we request the same info of the new host
	DataStructures::List<MyTeamMembers> myTeamMembers;

	DataStructures::List<unsigned short> teamLimits;
	DataStructures::List<unsigned short> teamMemberCounts;
	DataStructures::List<TeamMember> teamMembers;
	unsigned int GetMemberIndex(NetworkID memberId, RakNetGUID guid) const;
	unsigned int AddTeamMember(const TeamMember &tm); // Returns index of new member
	void RemoveTeamMember(unsigned int index);
	void EvenTeams(void);
	unsigned int GetMemberIndexToSwitchTeams(const DataStructures::List<TeamId> &sourceTeamNumbers, TeamId targetTeamNumber);
	void GetOverpopulatedTeams(DataStructures::List<TeamId> &overpopulatedTeams, int maxTeamSize);
	void SwitchMemberTeam(unsigned int teamMemberIndex, TeamId destinationTeam);
	void NotifyTeamAssigment(unsigned int teamMemberIndex);
	bool WeAreHost(void) const;
	PluginReceiveResult OnTeamAssigned(Packet *packet);
	PluginReceiveResult OnRequestedTeamChangePending(Packet *packet);
	PluginReceiveResult OnTeamsLocked(Packet *packet);
	void GetMinMaxTeamMembers(int &minMembersOnASingleTeam, int &maxMembersOnASingleTeam);
	TeamId GetNextDefaultTeam(void); // Accounting for team balancing and team limits, get the team a player should be placed on
	bool TeamWouldBeOverpopulatedOnAddition(TeamId teamId, unsigned int teamMemberSize); // Accounting for team balancing and team limits, would this team be overpopulated if a member was added to it?
	bool TeamWouldBeUnderpopulatedOnLeave(TeamId teamId, unsigned int teamMemberSize);
	TeamId GetSmallestNonFullTeam(void) const;
	TeamId GetFirstNonFullTeam(void) const;
	void MoveMemberThatWantsToJoinTeam(TeamId teamId);
	TeamId MoveMemberThatWantsToJoinTeamInternal(TeamId teamId);
	void NotifyTeamsLocked(RakNetGUID target, TeamId requestedTeam);
	void NotifyTeamSwitchPending(RakNetGUID target, TeamId requestedTeam, NetworkID memberId);
	void NotifyNoTeam(NetworkID memberId, RakNetGUID target);
	void SwapTeamMembersByRequest(unsigned int memberIndex1, unsigned int memberIndex2);
	void RemoveByGuid(RakNetGUID rakNetGUID);
	bool TeamsWouldBeEvenOnSwitch(TeamId t1, TeamId t2);

};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
