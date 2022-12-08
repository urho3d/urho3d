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

// TODO: optimize the list of teams and team members to be O(1). Store in hashes, use linked lists to get ordered traversal

/// \file TeamManager.h
/// \brief Automates networking and list management for teams
/// \details TeamManager provides support for teams. A team is a list of team members.
/// Teams contain properties including the number of team members per team, whether or not tagged teams must have equal numbers of members, and if a team is locked or not to certain entry conditions
/// Team members contain properties including which teams they are on and which teams they want to join if a team is not immediately joinable
/// Advanced functionality includes the ability for a team member to be on multiple teams simultaneously, the ability to swap teams with other members, and the ability to resize the number of members supported per team
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_TeamManager==1

#ifndef __TEAM_MANAGER_H
#define __TEAM_MANAGER_H

#include "PluginInterface2.h"
#include "memoryoverride.h"
#include "NativeTypes.h"
#include "DS_List.h"
#include "types.h"
#include "DS_Hash.h"
#include "DS_OrderedList.h"

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

/// \defgroup TEAM_MANAGER_GROUP TeamManager
/// \brief Automates networking and list management for teams
/// \details When used with ReplicaManager3 and FullyConnectedMesh2, provides a complete solution to managing a distributed list of teams and team member objects with support for host migration.
/// \ingroup PLUGINS_GROUP

/// \ingroup TEAM_MANAGER_GROUP
/// \brief A subcategory of not being on a team. For example, 0 may mean no team for a player, while 1 may mean no team for a spectator. Defined by the user.
typedef unsigned char NoTeamId;

/// \ingroup TEAM_MANAGER_GROUP
/// Used for multiple worlds.
typedef uint8_t WorldId;

/// \ingroup TEAM_MANAGER_GROUP
/// Maximum number of members on one team. Use 65535 for unlimited.
typedef uint16_t TeamMemberLimit;

/// Allow members to join this team when they specify TeamSelection::JOIN_ANY_AVAILABLE_TEAM
#define ALLOW_JOIN_ANY_AVAILABLE_TEAM (1<<0)
/// Allow members to join this team when they specify TeamSelection::JOIN_SPECIFIC_TEAM
#define ALLOW_JOIN_SPECIFIC_TEAM (1<<1)
/// Allow the host to put members on this team when rebalancing with TM_World::SetBalanceTeams()
#define ALLOW_JOIN_REBALANCING (1<<2)

// Bitwise combination of ALLOW_JOIN_ANY_AVAILABLE_TEAM, ALLOW_JOIN_SPECIFIC_TEAM, ALLOW_JOIN_REBALANCING
typedef uint8_t JoinPermissions;

// Forward declarations
class TM_Team;
class TM_TeamMember;
class TM_World;
class TeamManager;

/// \ingroup TEAM_MANAGER_GROUP
enum JoinTeamType
{
	/// Attempt to join the first available team.
	JOIN_ANY_AVAILABLE_TEAM,
	/// Attempt to join a specific team, previously added with TM_World::ReferenceTeam()
	JOIN_SPECIFIC_TEAM,
	/// No team. Always succeeds.
	JOIN_NO_TEAM
};

/// \ingroup TEAM_MANAGER_GROUP
enum TMTopology
{
	// Each system will send all messages to all participants
	TM_PEER_TO_PEER,

	// The host will relay incoming messages to all participants
	TM_CLIENT_SERVER,
};

/// \brief Parameter to TM_World::ReferenceTeamMember()
/// \details Use TeamSelection::AnyAvailable(), TeamSelection::SpecificTeam(), or TeamSelection::NoTeam()
/// \ingroup TEAM_MANAGER_GROUP
struct TeamSelection
{
	TeamSelection();
	TeamSelection(JoinTeamType itt);
	TeamSelection(JoinTeamType itt, TM_Team *param);
	TeamSelection(JoinTeamType itt, NoTeamId param);
	JoinTeamType joinTeamType;
	
	union
	{
		TM_Team *specificTeamToJoin;
		NoTeamId noTeamSubcategory;
	} teamParameter;
	
	/// \brief Join any team that has available slots and is tagged with ALLOW_JOIN_ANY_AVAILABLE_TEAM
	/// \details ID_TEAM_BALANCER_TEAM_ASSIGNED, ID_TEAM_BALANCER_REQUESTED_TEAM_FULL, or ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED will be returned to all systems.
	static TeamSelection AnyAvailable(void);
	/// \brief Join a specific team if it has available slots, and is tagged with JOIN_SPECIFIC_TEAMS
	/// \details ID_TEAM_BALANCER_TEAM_ASSIGNED, ID_TEAM_BALANCER_REQUESTED_TEAM_FULL, or ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED will be returned to all systems.
	/// \param[in] specificTeamToJoin Which team to attempt to join.
	static TeamSelection SpecificTeam(TM_Team *specificTeamToJoin);
	/// \brief Do not join a team, or leave all current teams.
	/// \details This always succeeds. ID_TEAM_BALANCER_TEAM_ASSIGNED will be returned to all systems.
	/// \param[in] noTeamSubcategory Even when not on a team, you can internally identify a subcategory of not being on a team, such as AI or spectator.
	static TeamSelection NoTeam(NoTeamId noTeamSubcategory);
};

/// \brief A member of one or more teams.
/// \details Contains data and operations on data to manage which team your game's team members are on.
/// Best used as a composite member of your "User" or "Player" class(es).
/// When using with ReplicaManager3, call TM_TeamMember::ReferenceTeamMember() in Replica3::DeserializeConstruction() and TM_TeamMember::DeserializeConstruction() in Replica3::PostDeserializeConstruction()
/// There is otherwise no need to manually serialize the class, as operations are networked internally.
/// \ingroup TEAM_MANAGER_GROUP
class RAK_DLL_EXPORT TM_TeamMember
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(TM_TeamMember)

	TM_TeamMember();
	virtual ~TM_TeamMember();
	
	/// \brief Request to join any team, a specific team, or to leave all teams
	/// \details Function will return false on invalid operations, such as joining a team you are already on.
	/// Will also fail with TeamSelection::JOIN_ANY_AVAILABLE_TEAM if you are currently on a team.
	/// On success, every system will get ID_TEAM_BALANCER_TEAM_ASSIGNED. Use TeamManager::DecomposeTeamAssigned() to get details of which team member the message refers to.
	/// On failure, all systems will get ID_TEAM_BALANCER_REQUESTED_TEAM_FULL or ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED. Use TeamManager::DecomposeTeamFull() and TeamManager::DecomposeTeamLocked() to get details of which team member the message refers to.
	/// \note Joining a specific team with this function may result in being on more than one team at once, even if you call the function while locally only on one team. If your game depends on only being on one team at a team, use RequestTeamSwitch() instead with the parameter teamToLeave set to 0
	/// \param[in] TeamSelection::AnyAvailable(), TeamSelection::SpecificTeam(), or TeamSelection::NoTeam()
	/// \return false On invalid or unnecessary operation. Otherwise returns true
	bool RequestTeam(TeamSelection teamSelection);
	
	/// \brief Similar to RequestTeam with TeamSelection::SpecificTeam(), but leave a team simultaneously when the desired team is joinable
	/// \param[in] teamToJoin Which team to join
	/// \param[in] teamToLeave If 0, means leave all current teams. Otherwise, leave the specified team.
	/// \return false On invalid or unnecessary operation. Otherwise returns true
	bool RequestTeamSwitch(TM_Team *teamToJoin, TM_Team *teamToLeave);
	
	/// \brief Returns the first requested team in the list of requested teams, if you have a requested team at all.
	/// \return TeamSelection::SpecificTeam(), TeamSelection::NoTeam(), or TeamSelection::AnyAvailable()
	TeamSelection GetRequestedTeam(void) const;
	
	/// \brief Returns pending calls to RequestTeam() when using TeamSelection::JOIN_SPECIFIC_TEAM
	/// \param[out] All pending requested teams
	void GetRequestedSpecificTeams(DataStructures::List<TM_Team*> &requestedTeams) const;

	/// \brief Returns if the specified team is in the list of pending requested teams
	/// \param[in] The team we are checking
	/// \return Did we request to join this specific team?
	bool HasRequestedTeam(TM_Team *team) const;

	/// \brief Returns the index of \a team in the requested teams list
	/// \param[in] The team we are checking
	/// \return -1 if we did not requested to join this team. Otherwise the index.
	unsigned int GetRequestedTeamIndex(TM_Team *team) const;

	/// \return The number of teams that would be returned by a call to GetRequestedSpecificTeams()
	unsigned int GetRequestedTeamCount(void) const;
	
	/// \brief Cancels a request to join a specific team.
	/// \details Useful if you got ID_TEAM_BALANCER_REQUESTED_TEAM_FULL or ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED and changed your mind about joining the team.
	/// \note This is not guaranteed to work due to latency. To clarify, If the host switches your team at the same time you call CancelRequestTeam() you may still get ID_TEAM_BALANCER_TEAM_ASSIGNED for the team you tried to cancel.
	/// \param[in] specificTeamToCancel Which team to no longer join. Use 0 for all.
	/// \return false On invalid or unnecessary operation. Otherwise returns true
	bool CancelTeamRequest(TM_Team *specificTeamToCancel);
	
	/// \brief Leave a team
	/// \details Leaves a team that you are on. Always succeeds provided you are on that team
	/// Generates ID_TEAM_BALANCER_TEAM_ASSIGNED on all systems on success.
	/// If you leave the last team you are on, \a noTeamSubcategory is set as well.
	/// \param[in] team Which team to leave
	/// \param[in] _noTeamSubcategory If the team member has been removed from all teams, which subcategory of NoTeamId to set them to
	/// \return false On invalid or unnecessary operation. Otherwise returns true
	bool LeaveTeam(TM_Team* team, NoTeamId _noTeamSubcategory);

	/// \brief Leave all teams
	/// \Details Leaves all teams you are on, and sets \a noTeamSubcategory
	/// \note This is the same as and just calls RequestTeam(TeamSelection::NoTeam(noTeamSubcategory));
	/// \return false On invalid or unnecessary operation. Otherwise returns true
	bool LeaveAllTeams(NoTeamId inNoTeamSubcategory);
	
	/// \return Get the first team we are on, or 0 if we are not on a team.
	TM_Team* GetCurrentTeam(void) const;

	/// \return How many teams we are on
	unsigned int GetCurrentTeamCount(void) const;

	/// \return Returns one of the teams in the current team list, up to GetCurrentTeamCount()
	TM_Team* GetCurrentTeamByIndex(unsigned int index);
	
	/// \param[out] Get all teams we are on, as a list
	void GetCurrentTeams(DataStructures::List<TM_Team*> &_teams) const;

	/// For each team member, when you get ID_TEAM_BALANCER_TEAM_ASSIGNED for that member, the team list is saved.
	/// Use this function to get that list, for example to determine which teams we just left or joined
	/// \param[out] _teams The previous list of teams we were on
	void GetLastTeams(DataStructures::List<TM_Team*> &_teams) const;

	/// \param[in] The team we are checking
	/// \return Are we on this team?
	bool IsOnTeam(TM_Team *team) const;
	
	/// \return The teamMemberID parameter passed to TM_World::ReferenceTeamMember()
	NetworkID GetNetworkID(void) const;
	
	/// \return The TM_World instance that was used when calling TM_World::ReferenceTeamMember()
	TM_World* GetTM_World(void) const;
	
	/// \brief Serializes the current state of this object
	/// \details To replicate a TM_TeamMember on another system, first instantiate the object using your own code, or a system such as ReplicaManager3.
	/// Next, call SerializeConstruction() from whichever system owns the team member
	/// Last, call DeserializeConstruction() on the newly created TM_TeamMember
	/// \note You must instantiate and deserialize all TM_Team instances that the team member refers to before calling DesrializeConstruction(). ReplicaManager3::PostSerializeConstruction() and ReplicaManager3::PostDeserializeConstruction() will ensure this.
	/// \param[out] constructionBitstream This object serialized to a BitStream
	void SerializeConstruction(BitStream *constructionBitstream);
	
	/// \brief Deserializes the current state of this object
	/// \details See SerializeConstruction for more details()
	/// \note DeserializeConstruction also calls ReferenceTeamMember on the passed \a teamManager instance, there is no need to do so yourself
	/// \param[in] teamManager TeamManager instance
	/// \param[in] constructionBitstream This object serialized to a BitStream
	bool DeserializeConstruction(TeamManager *teamManager, BitStream *constructionBitstream);

	/// \param[in] o Stores a void* for your own use. If using composition, this is useful to store a pointer to the containing object.
	void SetOwner(void *o);

	/// \return Whatever was passed to SetOwner()
	void *GetOwner(void) const;

	/// \return If not on a team, returns the current NoTeamId value
	NoTeamId GetNoTeamId(void) const;

	/// Return world->GetTeamMemberIndex(this)
	unsigned int GetWorldIndex(void) const;

	/// \internal
	static unsigned long ToUint32( const NetworkID &g );

	/// \internal
	struct RequestedTeam
	{
		SLNet::Time whenRequested;
		unsigned int requestIndex;
		TM_Team *requested;
		bool isTeamSwitch;
		TM_Team *teamToLeave;
	};
	
protected:
	NetworkID networkId;
	TM_World* world;
	// Teams we are a member of. We can be on more than one team, but not on the same team more than once
	DataStructures::List<TM_Team*> teams;
	// If teams is empty, which subcategory of noTeam we are on
	NoTeamId noTeamSubcategory;
	// Teams we have requested to join. Mutually exclusive with teams we are already on. Cannot request the same team more than once.
	DataStructures::List<RequestedTeam> teamsRequested;
	// If teamsRequested is not empty, we want to join a specific team
	// If teamsRequested is empty, then joinTeamType is either JOIN_NO_TEAM or JOIN_ANY_AVAILABLE_TEAM
	JoinTeamType joinTeamType;
	// Set by StoreLastTeams()
	DataStructures::List<TM_Team*> lastTeams;
	SLNet::Time whenJoinAnyRequested;
	unsigned int joinAnyRequestIndex;
	void *owner;

	// Remove from all requested and current teams.
	void UpdateListsToNoTeam(NoTeamId nti);
	bool JoinAnyTeamCheck(void) const;
	bool JoinSpecificTeamCheck(TM_Team *specificTeamToJoin, bool ignoreRequested) const;
	bool SwitchSpecificTeamCheck(TM_Team *teamToJoin, TM_Team *teamToLeave, bool ignoreRequested) const;
	bool LeaveTeamCheck(TM_Team *team) const;
	void UpdateTeamsRequestedToAny(void);
	void UpdateTeamsRequestedToNone(void);
	void AddToRequestedTeams(TM_Team *teamToJoin);
	void AddToRequestedTeams(TM_Team *teamToJoin, TM_Team *teamToLeave);
	bool RemoveFromRequestedTeams(TM_Team *team);
	void AddToTeamList(TM_Team *team);
	void RemoveFromSpecificTeamInternal(TM_Team *team);
	void RemoveFromAllTeamsInternal(void);
	void StoreLastTeams(void);

	friend class TM_World;
	friend class TM_Team;
	friend class TeamManager;
};

/// \brief A team, containing a list of TM_TeamMember instances
/// \details Contains lists of TM_TeamMember instances
/// Best used as a composite member of your "Team" or "PlayerList" class(es).
/// When using with ReplicaManager3, call TM_Team::ReferenceTeam() in Replica3::DeserializeConstruction() and TM_Team::DeserializeConstruction() in Replica3::PostDeserializeConstruction()
/// There is otherwise no need to manually serialize the class, as operations are networked internally.
/// \ingroup TEAM_MANAGER_GROUP
class RAK_DLL_EXPORT TM_Team
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(TM_Team)

	TM_Team();
	virtual ~TM_Team();
	
	/// \brief Set the maximum number of members that can join this team.
	/// Defaults to 65535
	/// Setting the limit lower than the existing number of members kicks members out, and assigns noTeamSubcategory to them if they have no other team to go to
	/// Setting the limit higher allows members to join in. If a member has a pending request to join this team, they join automatically and ID_TEAM_BALANCER_TEAM_ASSIGNED will be returned for those members.
	/// \param[in] _teamMemberLimit The new limit
	/// \param[in] noTeamSubcategory Which noTeamSubcategory to assign to members that now have no team.
	/// \return false On invalid or unnecessary operation. Otherwise returns true
	bool SetMemberLimit(TeamMemberLimit _teamMemberLimit, NoTeamId noTeamSubcategory);
	
	/// \return If team balancing is on, the most members that can be on this team that would not either unbalance it or exceed the value passed to SetMemberLimit(). If team balancing is off, the same as GetMemberLimitSetting()
	TeamMemberLimit GetMemberLimit(void) const;

	/// \return What was passed to SetMemberLimit() or the default
	TeamMemberLimit GetMemberLimitSetting(void) const;
	
	/// \brief Who can join this team under what conditions, while the team is not full
	/// To not allow new joins, pass 0
	/// To allow all new joins under any circumstances, bitwise-OR all permission defines.
	/// For an invite-only team, use ALLOW_JOIN_SPECIFIC_TEAM only and only allow the requester to call TM_TeamMember::RequestTeam() upon invitiation through your game code.
	/// Defaults to allow all
	/// \param[in] _joinPermissions Bitwise combination of ALLOW_JOIN_ANY_AVAILABLE_TEAM, ALLOW_JOIN_SPECIFIC_TEAM, ALLOW_JOIN_REBALANCING
	/// \return false On invalid or unnecessary operation. Otherwise returns true
	bool SetJoinPermissions(JoinPermissions _joinPermissions);
	
	/// \return Whatever was passed to SetJoinPermissions(), or the default.
	JoinPermissions GetJoinPermissions(void) const;
	
	/// \brief Removes a member from a team he or she is on
	/// \details Identical to teamMember->LeaveTeam(this, noTeamSubcategory); See TeamMember::LeaveTeam() for details.
	/// \param[in] teamMember Which team member to remove
	/// \param[in] noTeamSubcategory If the team member has been removed from all teams, which subcategory of NoTeamId to set them to
	void LeaveTeam(TM_TeamMember* teamMember, NoTeamId noTeamSubcategory);
	
	/// \return What was passed as the \a applyBalancing parameter TM_World::ReferenceTeam() when this team was added.
	bool GetBalancingApplies(void) const;
	
	/// \param[out] All team members of this team
	void GetTeamMembers(DataStructures::List<TM_TeamMember*> &_teamMembers) const;

	/// \return The number of team members on this team
	unsigned int GetTeamMembersCount(void) const;

	/// \return A team member on this team. Members are stored in the order they are added
	/// \param[in] index A value between 0 and GetTeamMembersCount()
	TM_TeamMember *GetTeamMemberByIndex(unsigned int index) const;
	
	/// \return The teamID parameter passed to TM_World::ReferenceTeam()
	NetworkID GetNetworkID(void) const;
	
	/// \return The TM_World instance that was used when calling TM_World::ReferenceTeamMember()
	TM_World* GetTM_World(void) const;
	
	/// \brief Used by the host to serialize the initial state of this object to a new system
	/// \details On the host, when sending existing objects to a new system, call SerializeConstruction() on each of those objects to serialize creation state.
	/// Creating the actual Team and TeamMember objects should be handled by your game code, or a system such as ReplicaManager3
	void SerializeConstruction(BitStream *constructionBitstream);
	
	/// \brief Used by non-host systems to read the bitStream written by SerializeConstruction()
	/// \details On non-host systems, after creating existing objects, call DeserializeConstruction() to read and setup that object
	/// Creating the actual Team and TeamMember objects should be handled by your game code, or a system such as ReplicaManager3
	bool DeserializeConstruction(TeamManager *teamManager, BitStream *constructionBitstream);

	/// \param[in] o Stores a void* for your own use. If using composition, this is useful to store a pointer to the containing object.
	void SetOwner(void *o);

	/// \return Whatever was passed to SetOwner()
	void *GetOwner(void) const;

	/// Return world->GetTeamIndex(this)
	unsigned int GetWorldIndex(void) const;

	/// \internal
	static unsigned long ToUint32( const NetworkID &g );
	
protected:
	NetworkID ID;
	TM_World* world;
	// Which members are on this team. The same member cannot be on the same team more than once
	DataStructures::List<TM_TeamMember*> teamMembers;
	// Permissions on who can join this team
	JoinPermissions joinPermissions;
	// Whether or not to consider this team when balancing teams
	bool balancingApplies;
	TeamMemberLimit teamMemberLimit;
	void *owner;

	// Remove input from list teamMembers
	void RemoveFromTeamMemberList(TM_TeamMember *teamMember);

	// Find the member index that wants to join the indicated team, is only on one team, and wants to leave that team
	unsigned int GetMemberWithRequestedSingleTeamSwitch(TM_Team *team);
	

	friend class TM_World;
	friend class TM_TeamMember;
	friend class TeamManager;
};

/// \brief Stores a list of teams which may be enforcing a balanced number of members
/// \details Each TM_World instance is independent of other TM_World world instances. This enables you to host multiple games on a single computer.
/// Not currently supported to have the same TM_Team or TM_TeamMember in more than one world at a time, but easily added on request.
/// \ingroup TEAM_MANAGER_GROUP
class TM_World
{
public:
	TM_World();
	virtual ~TM_World();

	/// \return Returns the plugin that created this TM_World instance
	TeamManager *GetTeamManager(void) const;

	/// \brief Add a new system to send team and team member updates to.
	/// \param[in] rakNetGUID GUID of the system you are adding. See Packet::rakNetGUID or RakPeerInterface::GetGUIDFromSystemAddress()
	void AddParticipant(RakNetGUID rakNetGUID);

	/// \brief Remove a system that was previously added with AddParticipant()
	/// \details Systems that disconnect are removed automatically
	/// \param[in] rakNetGUID GUID of the system you are removing. See Packet::rakNetGUID or RakPeerInterface::GetGUIDFromSystemAddress()
	void RemoveParticipant(RakNetGUID rakNetGUID);

	/// \brief If true, all new connections are added to this world using AddParticipant()
	/// \details Defaults to true
	/// \param[in] autoAdd Setting to set
	void SetAutoManageConnections(bool autoAdd);

	/// Get the participants added with AddParticipant()
	/// \param[out] participantList Participants added with AddParticipant();
	void GetParticipantList(DataStructures::List<RakNetGUID> &participantList);

	/// \brief Register a TM_Team object with this system.
	/// \details Your game should contain instances of TM_Team, for example by using composition with your game's Team or PlayerList class
	/// Tell TeamManager about these instances using ReferenceTeam().
	/// \note The destrutor of TM_Team calls DereferenceTeam() automatically.
	/// \param[in] team The instance you are registering
	/// \param[in] networkId Identifies this instance. This value is independent of values used by NetworkIDManager. You can use the same value as the object that contains this instance.
	/// \param[in] applyBalancing Whether or not to include this team for balancing when calling SetBalanceTeams().
	void ReferenceTeam(TM_Team *team, NetworkID networkId, bool applyBalancing);

	/// \brief Unregisters the associated TM_Team object with this system.
	/// Call when a TM_Team instance is no longer needed
	/// \param[in] team Which team instance to unregister
	/// \param[in] noTeamSubcategory All players on this team are kicked off. If these players then have no team, they are set to this no team category.
	void DereferenceTeam(TM_Team *team, NoTeamId noTeamSubcategory);

	/// \return Number of teams uniquely added with ReferenceTeam()
	unsigned int GetTeamCount(void) const;

	/// \param[in] index A value between 0 and GetTeamCount()
	/// \return Returns whatever was passed to \a team in the function ReferenceTeam() in the order it was called.
	TM_Team *GetTeamByIndex(unsigned int index) const;

	/// \param[in] teamId Value passed to ReferenceTeam()
	/// \return Returns whatever was passed to \a team in the function ReferenceTeam() with this NetworkID.
	TM_Team *GetTeamByNetworkID(NetworkID teamId);

	/// \brief Inverse of GetTeamByIndex()
	/// \param[in] team Which taem
	/// \return The index of the specified team, or -1 if not found
	unsigned int GetTeamIndex(const TM_Team *team) const;

	/// \brief Register a TM_TeamMember object with this system.
	/// \details Your game should contain instances of TM_TeamMember, for example by using composition with your game's User or Player classes
	/// Tell TeamManager about these instances using ReferenceTeamMember().
	/// \note The destrutor of TM_TeamMember calls DereferenceTeamMember() automatically.
	/// \param[in] teamMember The instance you are registering
	/// \param[in] networkId Identifies this instance. This value is independent of values used by NetworkIDManager. You can use the same value as the object that contains this instance
	void ReferenceTeamMember(TM_TeamMember *teamMember, NetworkID networkId);

	/// \brief Unregisters the associated TM_TeamMember object with this system.
	/// Call when a TM_TeamMember instance is no longer needed
	/// \note This is called by the destructor of TM_TeamMember automatically, so you do not normally need to call this function
	void DereferenceTeamMember(TM_TeamMember *teamMember);

	/// \return Number of team members uniquely added with ReferenceTeamMember()
	unsigned int GetTeamMemberCount(void) const;

	/// \param[in] index A value between 0 and GetTeamMemberCount()
	/// \return Returns whatever was passed to \a team in the function ReferenceTeamMember() in the order it was called.
	TM_TeamMember *GetTeamMemberByIndex(unsigned int index) const;

	/// \param[in] index A value between 0 and GetTeamMemberCount()
	/// \return Returns whatever was passed to \a teamMemberID in the function ReferenceTeamMember() in the order it was called.
	NetworkID GetTeamMemberIDByIndex(unsigned int index) const;

	/// \param[in] teamId Value passed to ReferenceTeamMember()
	/// \return Returns Returns whatever was passed to \a team in the function ReferenceTeamMember() with this NetworkID
	TM_TeamMember *GetTeamMemberByNetworkID(NetworkID teamMemberId);

	/// \brief Inverse of GetTeamMemberByIndex()
	/// \param[in] team Which team member
	/// \return The index of the specified team member, or -1 if not found
	unsigned int GetTeamMemberIndex(const TM_TeamMember *teamMember) const;

	/// \brief Force or stop forcing teams to be balanced.
	/// \details For each team added with ReferenceTeam() and \a applyBalancing set to true, players on unbalanced teams will be redistributed
	/// While active, players can only join balanced teams if doing so would not cause that team to become unbalanced.
	/// If a player on the desired team also wants to switch, then both players will switch simultaneously. Otherwise, ID_TEAM_BALANCER_REQUESTED_TEAM_FULL will be returned to the requester and switching will occur when possible.
	/// If balanceTeams is true and later set to false, players waiting on ID_TEAM_BALANCER_REQUESTED_TEAM_FULL will be able to join the desired team immediately provided it is not full.
	/// \param[in] balanceTeams Whether to activate or deactivate team balancing.
	/// \param[in] noTeamSubcategory If a player is kicked off a team and is no longer on any team, his or her noTeamSubcategory is set to this value
	bool SetBalanceTeams(bool balanceTeams, NoTeamId noTeamSubcategory);

	/// \return \a balanceTeams parameter of SetBalanceTeams(), or the default
	bool GetBalanceTeams(void) const;

	/// \brief Set the host that will perform balancing calculations and send notifications
	/// \details Operations that can cause conflicts due to latency, such as joining teams, are operated on by the host. The result is sent to all systems added with AddParticipant()
	/// For a client/server game, call SetHost() with the server's RakNetGUID value on all systems (including the server itself). If you call TeamManager::SetTopology(TM_CLIENT_SERVER), the server will also relay messages between participants.
	/// For a peer to peer game, call SetHost() on the same peer when host migration occurs. Use TeamManager::SetTopology(TM_PEER_TO_PEER) in this case.
	/// \note If using FullyConnectedMesh2, SetHost() is called automatically when ID_FCM2_NEW_HOST is returned.
	/// \param[in] _hostGuid The host, which is the system that will serialize and resolve team disputes and calculate team balancing.
	void SetHost(RakNetGUID _hostGuid);

	/// \return Returns the current host, or UNASSIGNED_RAKNET_GUID if unknown
	RakNetGUID GetHost(void) const;

	/// \return The \a worldId passed to TeamManagr::AddWorld()
	WorldId GetWorldId(void) const;

	/// \brief Clear all memory and reset everything.
	/// \details It is up to the user to deallocate pointers passed to ReferenceTeamMember() or ReferenceTeam(), if so desired.
	void Clear(void);

	/// \internal
	struct JoinRequestHelper
	{
		SLNet::Time whenRequestMade;
		unsigned int teamMemberIndex;
		unsigned int indexIntoTeamsRequested;
		unsigned int requestIndex;
	};
	/// \internal
	static int JoinRequestHelperComp(const TM_World::JoinRequestHelper &key, const TM_World::JoinRequestHelper &data);

protected:
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	virtual void OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming);

	// Teams with too many members have those members go to other teams.
	void EnforceTeamBalance(NoTeamId noTeamSubcategory);
	void KickExcessMembers(NoTeamId noTeamSubcategory);
	void FillRequestedSlots(void);
	unsigned int GetAvailableTeamIndexWithFewestMembers(TeamMemberLimit secondaryLimit, JoinPermissions joinPermissions);

	void GetSortedJoinRequests(DataStructures::OrderedList<JoinRequestHelper, JoinRequestHelper, JoinRequestHelperComp> &joinRequests);


	// Send a message to all participants
	void BroadcastToParticipants(SLNet::BitStream *bsOut, RakNetGUID exclusionGuid);
	void BroadcastToParticipants(unsigned char *data, const int length, RakNetGUID exclusionGuid);

	// 1. If can join a team:
	// A. teamMember->UpdateTeamsRequestedToNone();
	// B. teamMember->AddToTeamList()
	// C. Return new team
	// 2. Else return 0
	TM_Team* JoinAnyTeam(TM_TeamMember *teamMember, int *resultCode);

	int JoinSpecificTeam(TM_TeamMember *teamMember, TM_Team *team, bool isTeamSwitch, TM_Team *teamToLeave, DataStructures::List<TM_Team*> &teamsWeAreLeaving);

	TeamMemberLimit GetBalancedTeamLimit(void) const;

	// For fast lookup. Shares pointers with list teams
	DataStructures::Hash<NetworkID, TM_Team*, 256, TM_Team::ToUint32> teamsHash;
	// For fast lookup. Shares pointers with list teamMembers
	DataStructures::Hash<NetworkID, TM_TeamMember*, 256, TM_TeamMember::ToUint32> teamMembersHash;

	TeamManager *teamManager;
	DataStructures::List<RakNetGUID> participants;
	DataStructures::List<TM_Team*> teams;
	DataStructures::List<TM_TeamMember*> teamMembers;
	bool balanceTeamsIsActive;
	RakNetGUID hostGuid;
	WorldId worldId;
	bool autoAddParticipants;
	int teamRequestIndex;

	friend class TeamManager;
	friend class TM_TeamMember;
	friend class TM_Team;
};

/// \brief Automates networking and list management for teams
/// \details TeamManager provides support for teams. A team is a list of team members.
/// Teams contain properties including the number of team members per team, whether or not tagged teams must have equal numbers of members, and if a team is locked or not to certain entry conditions
/// Team members contain properties including which teams they are on and which teams they want to join if a team is not immediately joinable
/// Advanced functionality includes the ability for a team member to be on multiple teams simultaneously, the ability to swap teams with other members, and the ability to resize the number of members supported per team
/// The architecture is designed for easy integration with ReplicaManager3 
///
/// Usage:<BR>
/// 1. Define your game classes to represent teams and team members. Your game classes should hold game-specific information such as team name and color.<BR>
/// 2. Have those game classes contain a corresponding TM_Team or TM_TeamMember instance. Operations on teams will be performed by those instances. Use SetOwner() to refer to the parent object when using composition.<BR>
/// 3. Call TeamManager::SetTopology() for client/server or peer to peer.<BR>
/// 4. Call AddWorld() to instantiate a TM_World object which will contain references to your TM_TeamMember and TM_Team instances.<BR>
/// 5. When you instantiate a TM_TeamMember or TM_Team object, call ReferenceTeam() and ReferenceTeamMember() for each corresponding object<BR>
/// 6. When sending world state to a new connection, for example in ReplicaManager3::SerializeConstruction(), call TM_SerializeConstruction() on the corresponding TM_TeamMember and TM_Team objects. TM_Team instances on the new connection must be created before TM_TeamMember instances.<BR>
/// 7. Call TM_DeserializeConstruction() on your new corresponding TM_TeamMember and TM_Team instances.<BR>
/// 8. Execute team operations. ID_TEAM_BALANCER_REQUESTED_TEAM_FULL, ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED, ID_TEAM_BALANCER_TEAM_REQUESTED_CANCELLED, and ID_TEAM_BALANCER_TEAM_ASSIGNED are returned to all systems when the corresponding event occurs for a team member.<BR>
/// 9. As the peer to peer session host changes, call SetHost() (Not necessary if using FullyConnectedMesh2). If using client/server, you must set the host<BR>
/// \note This replaces TeamBalancer. You cannot use TeamBalancer and TeamManager at the same time.
/// \ingroup TEAM_MANAGER_GROUP
class RAK_DLL_EXPORT TeamManager : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(TeamManager)

	TeamManager();
	virtual ~TeamManager();

	/// \brief Allocate a world to hold a list of teams and players for that team.
	/// Use the returned TM_World object for actual team functionality.
	/// \note The world is tracked by TeamManager and deallocated by calling Clear()
	/// \param[in] worldId Arbitrary user-defined id of the world to create. Each world instance must have a unique id.
	TM_World* AddWorld(WorldId worldId);

	/// \brief Deallocate a world created with AddWorld()
	/// \param[in] worldId The world to deallocate
	void RemoveWorld(WorldId worldId);

	/// \return Returns the number of worlds created with AddWorld()
	unsigned int GetWorldCount(void) const;

	/// \param[in] index A value beteween 0 and GetWorldCount()-1 inclusive.
	/// \return Returns a world created with AddWorld()
	TM_World* GetWorldAtIndex(unsigned int index) const;

	/// \param[in] worldId \a worldId value passed to AddWorld()
	/// \return Returns a world created with AddWorld(), or 0 if no such \a worldId
	TM_World* GetWorldWithId(WorldId worldId) const;
	
	/// \brief When auto managing connections, call TM_World::AddParticipant() on all worlds for all new connections automatically
	/// Defaults to true
	/// \note You probably want this set to false if using multiple worlds	
	/// \param[in] autoAdd Automatically call TM_World::AddParticipant() all worlds each new connection. Defaults to true.
	void SetAutoManageConnections(bool autoAdd);

	/// \brief If \a _topology is set to TM_CLIENT_SERVER, the host will relay messages to participants.
	/// \details If topology is set to TM_PEER_TO_PEER, the host assumes the original message source was connected to all other participants and does not relay messages.
	/// \note If TM_PEER_TO_PEER, this plugin will listen for ID_FCM2_NEW_HOST and call SetHost() on all worlds automatically
	/// \note Defaults to TM_PEER_TO_PEER
	/// \param[in] _topology Topology to use
	void SetTopology(TMTopology _topology);
	
	/// \brief When you get ID_TEAM_BALANCER_REQUESTED_TEAM_FULL, pass the packet to this function to read out parameters
	/// \param[in] A packet where packet->data[0]==ID_TEAM_BALANCER_REQUESTED_TEAM_FULL
	/// \return true on success, false on read error
	void DecomposeTeamFull(Packet *packet,
		TM_World **world, TM_TeamMember **teamMember, TM_Team **team,
		uint16_t &currentMembers, uint16_t &memberLimitIncludingBalancing, bool &balancingIsActive, JoinPermissions &joinPermissions);

	/// \brief When you get ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED, pass the packet to this function to read out parameters
	/// \param[in] A packet where packet->data[0]==ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED
	/// \return true on success, false on read error
	void DecomposeTeamLocked(Packet *packet,
		TM_World **world, TM_TeamMember **teamMember, TM_Team **team,
		uint16_t &currentMembers, uint16_t &memberLimitIncludingBalancing, bool &balancingIsActive, JoinPermissions &joinPermissions);

	/// \brief Clear all memory and reset everything.
	/// \details Deallocates TM_World instances. It is up to the user to deallocate pointers passed to ReferenceTeamMember() or ReferenceTeam(), if so desired.
	void Clear(void);
	
	/// \brief Reads out the world and teamMember from ID_TEAM_BALANCER_TEAM_ASSIGNED
	/// \note You can get the current and prior team list from the teamMember itself
	/// \param[in] A packet where packet->data[0]==ID_TEAM_BALANCER_TEAM_ASSIGNED
	/// \param[out] world Set to the world this \a teamMember is on. 0 on bad lookup.
	/// \param[out] teamMember Set to the teamMember affected. 0 on bad lookup.
	void DecodeTeamAssigned(Packet *packet, TM_World **world, TM_TeamMember **teamMember);

	// \brief Reads out the world and teamMember from ID_TEAM_BALANCER_TEAM_REQUESTED_CANCELLED
	/// \note You can get the requested team list from the teamMember itself
	/// \param[in] A packet where packet->data[0]==ID_TEAM_BALANCER_TEAM_REQUESTED_CANCELLED
	/// \param[out] world Set to the world this \a teamMember is on. 0 on bad lookup.
	/// \param[out] teamMember Set to the teamMember affected. 0 on bad lookup.
	/// \param[out] teamCancelled Set to the team that was cancelled. 0 for all teams.
	void DecodeTeamCancelled(Packet *packet, TM_World **world, TM_TeamMember **teamMember, TM_Team **teamCancelled);

protected:

	virtual void Update(void);
	virtual PluginReceiveResult OnReceive(Packet *packet);
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	virtual void OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming);
	void Send( const SLNet::BitStream * bitStream, const AddressOrGUID systemIdentifier, bool broadcast );

	void EncodeTeamFullOrLocked(SLNet::BitStream *bitStream, TM_TeamMember *teamMember, TM_Team *team);
	void DecomposeTeamFullOrLocked(SLNet::BitStream *bsIn, TM_World **world, TM_TeamMember **teamMember, TM_Team **team,
		uint16_t &currentMembers, uint16_t &memberLimitIncludingBalancing, bool &balancingIsActive, JoinPermissions &joinPermissions);
	void ProcessTeamAssigned(SLNet::BitStream *bsIn);

	void EncodeTeamAssigned(SLNet::BitStream *bitStream, TM_TeamMember *teamMember);
	void RemoveFromTeamsRequestedAndAddTeam(TM_TeamMember *teamMember, TM_Team *team, bool isTeamSwitch, TM_Team *teamToLeave);

	void PushTeamAssigned(TM_TeamMember *teamMember);
	void PushBitStream(SLNet::BitStream *bitStream);
	void OnUpdateListsToNoTeam(Packet *packet, TM_World *world);
	void OnUpdateTeamsRequestedToAny(Packet *packet, TM_World *world);
	void OnJoinAnyTeam(Packet *packet, TM_World *world);
	void OnJoinRequestedTeam(Packet *packet, TM_World *world);
	void OnUpdateTeamsRequestedToNoneAndAddTeam(Packet *packet, TM_World *world);
	void OnRemoveFromTeamsRequestedAndAddTeam(Packet *packet, TM_World *world);
	void OnAddToRequestedTeams(Packet *packet, TM_World *world);
	bool OnRemoveFromRequestedTeams(Packet *packet, TM_World *world);
	void OnLeaveTeam(Packet *packet, TM_World *world);
	void OnSetMemberLimit(Packet *packet, TM_World *world);
	void OnSetJoinPermissions(Packet *packet, TM_World *world);
	void OnSetBalanceTeams(Packet *packet, TM_World *world);
	void OnSetBalanceTeamsInitial(Packet *packet, TM_World *world);


	void EncodeTeamFull(SLNet::BitStream *bitStream, TM_TeamMember *teamMember, TM_Team *team);
	void EncodeTeamLocked(SLNet::BitStream *bitStream, TM_TeamMember *teamMember, TM_Team *team);

	/// \brief When you get ID_TEAM_BALANCER_TEAM_ASSIGNED, pass the packet to this function to read out parameters
	/// \param[in] A packet where packet->data[0]==ID_TEAM_BALANCER_TEAM_ASSIGNED
	/// \return true on success, false on read error
	void DecodeTeamAssigned(SLNet::BitStream *bsIn, TM_World **world, TM_TeamMember **teamMember, NoTeamId &noTeamSubcategory,
		JoinTeamType &joinTeamType, DataStructures::List<TM_Team *> &newTeam,
		DataStructures::List<TM_Team *> &teamsLeft, DataStructures::List<TM_Team *> &teamsJoined);

	// O(1) lookup for a given world. If I need more worlds, change this to a hash or ordered list
	TM_World *worldsArray[255];
	// All allocated worlds for linear traversal
	DataStructures::List<TM_World*> worldsList;
	bool autoAddParticipants;
	TMTopology topology;

	friend class TM_TeamMember; 
	friend class TM_World;
	friend class TM_Team;
};

} // namespace SLNet

#endif // __TEAM_MANAGER_H

#endif // _RAKNET_SUPPORT_*

