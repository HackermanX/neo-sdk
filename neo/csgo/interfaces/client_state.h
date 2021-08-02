#pragma once
#include <cstdint>
#include "../math/vector_3d.h"

class i_net_channel
{
public:
	char pad_0000[20];           //0x0000
	bool processing_messages;  //0x0014
	bool should_delete;        //0x0015
	char pad_0016[2];            //0x0016
	int32_t out_sequence_nr;    //0x0018 last send outgoing sequence number
	int32_t in_sequence_nr;     //0x001C last received incoming sequnec number
	int32_t out_sequence_nr_ack; //0x0020 last received acknowledge outgoing sequnce number
	int32_t out_reliable_state; //0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
	int32_t in_reliable_state;  //0x0028 state of incoming reliable data
	int32_t choked_packets;    //0x002C number of choked packets
	char pad_0030[1044];         //0x0030
}; //Size: 0x0444

class CClockDriftMgr
{
public:
	float m_ClockOffsets[16];   //0x0000
	uint32_t m_iCurClockOffset; //0x0044
	uint32_t m_nServerTick;     //0x0048
	uint32_t m_nClientTick;     //0x004C
}; //Size: 0x0050

// Thanks soufiw 
class client_state
{
public:
	void ForceFullUpdate()
	{
		m_nDeltaTick = -1;
	}

	char pad000[0x9C];
	i_net_channel* net_channel;
	int	m_nChallengeNr;
	char pad001[0x4];
	double m_connect_time;
	int m_retry_number;
	char pad002[0x54];
	int m_nSignonState;
	char pad003[0x4];
	double m_flNextCmdTime;
	int m_nServerCount;
	int m_nCurrentSequence;
	char pad004[0x8];
	CClockDriftMgr m_ClockDriftMgr;
	int m_nDeltaTick;
	char pad005[0x4];
	int m_nViewEntity;
	int m_nPlayerSlot;
	bool m_bPaused;
	char pad006[0x3];
	char m_szLevelName[0x104];
	char m_szLevelNameShort[0x28];
	char pad007[0xD4];
	int m_nMaxClients;
	char pad008[0x4994];
	int oldtickcount;
	float m_tickRemainder;
	float m_frameTime;
	int lastoutgoingcommand;
	int chokedcommands;
	int last_command_ack;
	int m_last_server_tick;
	int command_ack;
	int m_nSoundSequence;
	int m_last_progress_percent;
	bool m_is_hltv;
	char pad009[0x4B];
	vec3_t viewangles;
	char pad010[0xCC];
	void* m_events;
};