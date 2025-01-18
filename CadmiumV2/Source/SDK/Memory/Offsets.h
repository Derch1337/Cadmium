#pragma once
#include <cstdint>


enum MainOffsets {
	ptrLocalPlayer = 0x4C88E8,
	ptrEntityList = 0x4D5AE4,
	ptrNameList = 0x0050E368,
};

enum EngineOffsets {
	ptr_engine_playerCount = 0x5EC82C,
	ptr_mapName = 0x47796D,
	ptr_VIEW_MATRIX = 0x5B0D68,
	ptr_bIsInGame = 0x3C32C4,
};



enum PlayerOffsets {
	m_vecAimPunch = 0x6C,
	m_fHeadingY = 0x026C,
	m_fHeadingX = 0x0270,

	m_iClientId = 0x0054,
	m_iHealth = 0x0094,
	m_iTeamNum = 0x009C,
	m_fHeadPosZ = 0x00F0,
	m_lifeState = 0x93,
	m_iState = 0x0178,
	m_bDormant = 0x017E,
	m_vecPosition = 0x0260,

	m_iFlags = 0x0350,
	m_BoneMatrix = 0x0578,
	m_iFov = 0x0FD4,
	m_iFovStart = 0x0FD8,
	m_fFovTime = 0x0FDC,
	m_defaultFov = 0x0FE0,
	m_fMaxFlashAlpha = 0x1450,
	m_flFlashDuration = 0x1454,
	m_iArmor = 0x1498,
	m_iCrosshairEntityId = 0x14F0,
	m_bIsDefusing = 0x140c,
	m_bHasDefuser = 0x14A8,
	m_fOnTarget = 0xfe8,
	m_iShotsFired = 0x1430,
	m_bInBombZone = 0x140d,
	m_bInBuyZone = 0x140e,
	m_vecViewOffset = 0xe8,
};