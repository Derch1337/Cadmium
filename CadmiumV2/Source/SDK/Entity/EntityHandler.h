#pragma once
#include "../Enum/Enums.h"
#include "../Math/Math.h"
#include <wtypes.h>
#include "../Memory/Memory.h"
#include "../Memory/Offsets.h"
#include "../MapParser/MapParser.h"
#include "Bone.h"

constexpr int MAX_PLAYER = 32;
const float font_size_min = 5.f;
const float font_size_max = 15.f;


#define FL_ONGROUND (1<<0)
#define FL_DUCKING  (1<<1)

#define CornerTopLeft 0
#define CornerTopRight 1
#define CornerBottomRight 2
#define CornerBottomLeft 3
#define CornerHeadPosition 4
#define CornerFeetPosition 5
#define CornerPosition 6
#define CornerSize 7


struct EnemyEntity
{
	DWORD dwEntity;
	bool Dormant;
	int Health;
	LifeState lifeState;
	TeamNum Team;
	int ID;
	CSWeaponID WeaponID;
	bool IsDefusing;
	float HeadHeight;
	BoneGroupData Bones[32];
	Vector3 WorldHeadPosition;
	Vector3 WorldPosition;
	std::string DisplayName;
	DWORD BoneMatrix;

	bool IsVisible;

	Vector2 Corner[8];
	bool OnScreen;
	float DistanceToPlayer;
	float font_current_size = 30.f;
};

struct LocalPlayer
{
	DWORD dwEntity;
	int Health;
	LifeState lifeState;
	TeamNum Team;
	int ID;
	CSWeaponID WeaponID;
	int Flags;
	int Fov;
	int ShotsFired;//local data
	int Armor;
	int CrosshairEntityID;
	bool InBuyZone;
	bool InBombZone;

	float HeadHeight;
	int FovStart;
	float FovTime;
	float MaxFlashAlpha;
	float FlashDuration;

	Vector2 ViewAngle;
	Vector2 AimPunch;

	Vector3 WorldHeadPosition;

	ViewMatrix viewMatrix;

};

class EntityHandler
{
private:
	const float SOURCE_ENGINE_MAGIC_NUM_SCALE = 0.0254f;//idk


	Memory& memory;
	MapParser& mapParser;

public:
	LocalPlayer localPlayer;
	EnemyEntity EnemyList[MAX_PLAYER];
	std::string PlayerNames[MAX_PLAYER];

	
public:
	EntityHandler(Memory& mem, MapParser& parser);

	void UpdateLocalPlayer();
	void UpdateEnemyEntity();
	void UpdatePlayerNames();

private:
	
	

	CSWeaponID GetWeaponID(DWORD entity);
};

