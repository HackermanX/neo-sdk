
#pragma once
#include "../math/vector_3d.h"
class player_t;
class c_usercmd;

using c_entity = player_t;
using c_user_cmd = c_cmd;
class IPhysicsSurfaceProps;
class c_game_trace;
class c_move_helper
{
public:
	virtual	char const* GetName(void* hEntity) const = 0;
	virtual void				set_host(c_entity* pHost) = 0;
	virtual void				ResetTouchList() = 0;
	virtual bool				AddToTouched(const c_game_trace& trace, const vec3_t& vecImpactVelocity) = 0;
	virtual void				ProcessImpacts() = 0;
	virtual void				Con_NPrintf(int nIndex, char const* fmt, ...) = 0;
	//virtual void				StartSound(const Vector& vecOrigin, int iChannel, char const* szSample, float flVolume, ESoundLevel soundlevel, int fFlags, int iPitch) = 0;
	virtual void				StartSound(const vec3_t& vecOrigin, const char* soundname) = 0;
	virtual void				PlaybackEventFull(int fFlags, int nClientIndex, unsigned short uEventIndex, float flDelay, vec3_t& vecOrigin, vec3_t& vecAngles, float flParam1, float flParam2, int iParam1, int iParam2, int bParam1, int bParam2) = 0;
	virtual bool				PlayerFallingDamage(void) = 0;
	virtual void				PlayerSetAnimation(int playerAnimation) = 0;
	virtual IPhysicsSurfaceProps* GetSurfaceProps() = 0;
	virtual bool				IsWorldEntity(const unsigned long& hEntity) = 0;
};

struct c_move_data
{
	char data[184];
};

class c_game_movement
{
public:
	virtual			~c_game_movement(void)
	{}

	virtual void	process_movement(c_entity* pPlayer, c_move_data* pMove) = 0;
	virtual void	Reset(void) = 0;
	virtual void	start_track_prediction_errors(c_entity* pPlayer) = 0;
	virtual void	finish_track_prediction_errors(c_entity* pPlayer) = 0;
	virtual void	DiffPrint(char const* fmt, ...) = 0;

	virtual vec3_t const& GetPlayerMins(bool ducked) const = 0;
	virtual vec3_t const& GetPlayerMaxs(bool ducked) const = 0;
	virtual vec3_t const& GetPlayerViewOffset(bool ducked) const = 0;

	virtual bool			IsMovingPlayerStuck(void) const = 0;
	virtual c_entity* GetMovingPlayer(void) const = 0;
	virtual void			UnblockPusher(c_entity* pPlayer, c_entity* pPusher) = 0;

	virtual void    SetupMovementBounds(c_move_data* pMove) = 0;
};

class c_prediction
{
	// Construction
public:

	virtual ~c_prediction(void) = 0;//

	virtual void Init(void) = 0;//
	virtual void Shutdown(void) = 0;//

									// Implement IPrediction
public:

	virtual void Update
	(
		int startframe, // World update ( un-modded ) most recently received
		bool validframe, // Is frame data valid
		int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command // Last command (most recent) sent to server (un-modded)
	);//

	virtual void PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet);//
	virtual void PostEntityPacketReceived(void);//5
	virtual void PostNetworkDataReceived(int commands_acknowledged);//

	virtual void OnReceivedUncompressedPacket(void);//

													// The engine needs to be able to access a few predicted values
	virtual void GetViewOrigin(vec3_t& org);//
	virtual void SetViewOrigin(vec3_t& org);//
	virtual void GetViewAngles(vec3_t& ang);//10
	virtual void SetViewAngles(vec3_t& ang);//

	virtual void GetLocalViewAngles(vec3_t& ang);//
	virtual void SetLocalViewAngles(vec3_t& ang);//

	virtual bool InPrediction(void) const;//14
	virtual bool IsFirstTimePredicted(void) const;//

	virtual int GetLastAcknowledgedCommandNumber(void) const;//

#if !defined( NO_ENTITY_PREDICTION )
	virtual int GetIncomingPacketNumber(void) const;//
#endif

	virtual void CheckMovingGround(c_entity* player, double frametime);//
	virtual void RunCommand(c_entity* player, c_user_cmd* cmd, c_move_helper* moveHelper);//

	virtual void setup_move(c_entity* player, c_user_cmd* cmd, c_move_helper* pHelper, c_move_data* move);//20
	virtual void finish_move(c_entity* player, c_user_cmd* cmd, c_move_data* move);//
	virtual void SetIdealPitch(int nSlot, c_entity* player, const vec3_t& origin, const vec3_t& angles, const vec3_t& viewheight);//

	virtual void CheckError(int nSlot, c_entity* player, int commands_acknowledged);//

public:
	virtual void _Update
	(
		int nSlot,
		bool received_new_world_update,
		bool validframe,            // Is frame data valid
		int incoming_acknowledged,  // Last command acknowledged to have been run by server (un-modded)
		int outgoing_command        // Last command (most recent) sent to server (un-modded)
	);

	// Actually does the prediction work, returns false if an error occurred
	bool PerformPrediction(int nSlot, c_entity* localPlayer, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);

	void ShiftIntermediateDataForward(int nSlot, int slots_to_remove, int previous_last_slot);

	void RestoreEntityToPredictedFrame(int nSlot, int predicted_frame);

	int ComputeFirstCommandToExecute(int nSlot, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);

	void DumpEntity(c_entity* ent, int commands_acknowledged);

	void ShutdownPredictables(void);

	void ReinitPredictables(void);

	void RemoveStalePredictedEntities(int nSlot, int last_command_packet);

	void RestoreOriginalEntityState(int nSlot);

	void RunSimulation(int current_command, float curtime, c_user_cmd* cmd, c_entity* localPlayer);

	void Untouch(int nSlot);

	void StorePredictionResults(int nSlot, int predicted_frame);

	bool ShouldDumpEntity(c_entity* ent);

	void SmoothViewOnMovingPlatform(c_entity* pPlayer, vec3_t& offset);

	void ResetSimulationTick();

	void ShowPredictionListEntry(int listRow, int showlist, c_entity* ent, int& totalsize, int& totalsize_intermediate);

	void FinishPredictionList(int listRow, int showlist, int totalsize, int totalsize_intermediate);

	void CheckPredictConvar();

#if !defined( NO_ENTITY_PREDICTION )

#endif
};