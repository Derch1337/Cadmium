#include "EntityHandler.h"
#include <algorithm>

MemoryPage page;
BoneMemoryPage bonePage;

EntityHandler::EntityHandler(Memory& mem, MapParser& parser) : memory(mem), mapParser(parser)
{



}


// exec memory read function: 4
void EntityHandler::UpdateLocalPlayer()
{
	if (!memory.GetInGame()) return;

	localPlayer.dwEntity = memory.Read<DWORD>(memory.ClientDLL.BaseAdress + MainOffsets::ptrLocalPlayer);
	localPlayer.viewMatrix = memory.Read<ViewMatrix>(memory.EngineDLL.BaseAdress + EngineOffsets::ptr_VIEW_MATRIX);


	page = memory.Read<MemoryPage>(localPlayer.dwEntity);
	//read data
	localPlayer.ID = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iClientId]);
	localPlayer.Health = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iHealth]);
	localPlayer.lifeState = (LifeState)*reinterpret_cast<const char*>(&page.bytes[PlayerOffsets::m_lifeState]);
	localPlayer.Team = (TeamNum)*reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iTeamNum]);
	localPlayer.Flags = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iFlags]);
	localPlayer.Fov = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iFov]);
	localPlayer.Armor = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iArmor]);
	localPlayer.CrosshairEntityID = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iCrosshairEntityId]) - 1;
	localPlayer.InBuyZone = *reinterpret_cast<const bool*>(&page.bytes[PlayerOffsets::m_bInBuyZone]);
	localPlayer.InBombZone = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_bInBombZone]);
	localPlayer.HeadHeight = *reinterpret_cast<const float*>(&page.bytes[PlayerOffsets::m_fHeadPosZ]);
	localPlayer.FovStart = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iFovStart]);
	localPlayer.FovTime = *reinterpret_cast<const float*>(&page.bytes[PlayerOffsets::m_fFovTime]);
	localPlayer.MaxFlashAlpha = *reinterpret_cast<const float*>(&page.bytes[PlayerOffsets::m_fMaxFlashAlpha]);
	localPlayer.FlashDuration = *reinterpret_cast<const float*>(&page.bytes[PlayerOffsets::m_flFlashDuration]);
	localPlayer.ViewAngle = *reinterpret_cast<const Vector2*>(&page.bytes[PlayerOffsets::m_fHeadingY]);
	localPlayer.WorldHeadPosition = *reinterpret_cast<const Vector3*>(&page.bytes[PlayerOffsets::m_vecPosition]) + Vector3(0, 0, localPlayer.HeadHeight);
	

	//read local data
	page = memory.Read<MemoryPage>(localPlayer.dwEntity + 0x0DDC);

	localPlayer.ShotsFired = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iShotsFired]);
	localPlayer.AimPunch = *reinterpret_cast<const Vector2*>(&page.bytes[PlayerOffsets::m_vecAimPunch]);
	localPlayer.WeaponID = GetWeaponID(localPlayer.dwEntity);

	//CSWeaponID WeaponID;
}

// exec memory read function: 3 + weaponid=5 -> 8
void EntityHandler::UpdateEnemyEntity()
{
	if (!memory.GetInGame()) return;
	
	for (int index = 0; index < MAX_PLAYER; index++)
	{
		EnemyList[index].dwEntity = memory.Read<DWORD>(memory.ClientDLL.BaseAdress + MainOffsets::ptrEntityList + (index * 0x10));
		page = memory.Read<MemoryPage>(EnemyList[index].dwEntity);
		bonePage = memory.Read<BoneMemoryPage>(0xC + *reinterpret_cast<const DWORD*>(&page.bytes[PlayerOffsets::m_BoneMatrix]));

		EnemyList[index].ID = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iClientId]);
		EnemyList[index].Dormant = *reinterpret_cast<const bool*>(&page.bytes[PlayerOffsets::m_bDormant]);
		EnemyList[index].Health = *reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iHealth]);
		EnemyList[index].lifeState = (LifeState) * reinterpret_cast<const char*>(&page.bytes[PlayerOffsets::m_lifeState]);
		EnemyList[index].Team = (TeamNum) * reinterpret_cast<const int*>(&page.bytes[PlayerOffsets::m_iTeamNum]);
		EnemyList[index].IsDefusing = *reinterpret_cast<const bool*>(&page.bytes[PlayerOffsets::m_bIsDefusing]);
		EnemyList[index].HeadHeight = *reinterpret_cast<const float*>(&page.bytes[PlayerOffsets::m_fHeadPosZ]);
		EnemyList[index].WorldPosition = *reinterpret_cast<const Vector3*>(&page.bytes[PlayerOffsets::m_vecPosition]);
		EnemyList[index].WorldHeadPosition = EnemyList[index].WorldPosition + Vector3(0, 0, EnemyList[index].HeadHeight);
		EnemyList[index].DisplayName = PlayerNames[index];

		for (int bone_index = 0; bone_index < 32; bone_index++)
		{
			BonePosition bonedata = bonePage.Page[bone_index];

			EnemyList[index].Bones[bone_index].WorldPosition = Vector3(bonedata.x, bonedata.y, bonedata.z);

			if (!localPlayer.viewMatrix.WorldToScreen(EnemyList[index].Bones[bone_index].WorldPosition, EnemyList[index].Bones[bone_index].ScreenPosition)) {
				EnemyList[index].Bones[bone_index].IsVisible = false;
			}
			else {
				EnemyList[index].Bones[bone_index].IsVisible = mapParser.IsVisible(localPlayer.WorldHeadPosition, EnemyList[index].Bones[bone_index].WorldPosition);
			}

		}


		EnemyList[index].IsVisible = EnemyList[index].Bones[BoneID::CHEST].IsVisible || EnemyList[index].Bones[BoneID::PELVIS].IsVisible;


		EnemyList[index].DistanceToPlayer = Vector3Distance(localPlayer.WorldHeadPosition, EnemyList[index].WorldHeadPosition) * SOURCE_ENGINE_MAGIC_NUM_SCALE;

		float normalized_distance = std::clamp(EnemyList[index].DistanceToPlayer, 0.0f, 1000.0f) / 1000.0f;

		EnemyList[index].font_current_size = font_size_max - (font_size_max - font_size_min) * normalized_distance;



		EnemyList[index].OnScreen =
			localPlayer.viewMatrix.WorldToScreen(EnemyList[index].WorldPosition, EnemyList[index].Corner[CornerFeetPosition]) &&
			localPlayer.viewMatrix.WorldToScreen(EnemyList[index].WorldHeadPosition, EnemyList[index].Corner[CornerHeadPosition]);


		EnemyList[index].Corner[CornerSize].y = EnemyList[index].Corner[CornerFeetPosition].y - EnemyList[index].Corner[CornerHeadPosition].y;
		EnemyList[index].Corner[CornerSize].x = (EnemyList[index].Corner[CornerSize].y / 2) * 1.2f;

		EnemyList[index].Corner[CornerPosition].x = EnemyList[index].Corner[CornerFeetPosition].x - (EnemyList[index].Corner[CornerSize].x / 2);
		EnemyList[index].Corner[CornerPosition].y = EnemyList[index].Corner[CornerHeadPosition].y;

		EnemyList[index].Corner[CornerTopLeft] = { EnemyList[index].Corner[CornerFeetPosition].x - EnemyList[index].Corner[CornerSize].x / 2, EnemyList[index].Corner[CornerHeadPosition].y };
		EnemyList[index].Corner[CornerTopRight] = { EnemyList[index].Corner[CornerFeetPosition].x + EnemyList[index].Corner[CornerSize].x / 2, EnemyList[index].Corner[CornerHeadPosition].y };
		EnemyList[index].Corner[CornerBottomRight] = { EnemyList[index].Corner[CornerFeetPosition].x + EnemyList[index].Corner[CornerSize].x / 2, EnemyList[index].Corner[CornerFeetPosition].y };
		EnemyList[index].Corner[CornerBottomLeft] = { EnemyList[index].Corner[CornerFeetPosition].x - EnemyList[index].Corner[CornerSize].x / 2, EnemyList[index].Corner[CornerFeetPosition].y };

		EnemyList[index].WeaponID = GetWeaponID(EnemyList[index].dwEntity);


	}

}
// exec memory read function: 2
void EntityHandler::UpdatePlayerNames()
{
	if (!memory.GetInGame()) return;
	auto _name_list = memory.Read<DWORD>(memory.ClientDLL.BaseAdress + MainOffsets::ptrNameList) + 0x38;

	struct EntityName
	{
		char name[0x140];
	};

	struct EntityNames
	{
		EntityName entity[MAX_PLAYER];
	};

	EntityNames names = memory.Read<EntityNames>(_name_list);

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		PlayerNames[i] = std::string(names.entity[i].name);
	}


}
// exec memory read function: 5
CSWeaponID EntityHandler::GetWeaponID(DWORD entity)
{
	auto pWeaponHandle = memory.Read<DWORD>(entity + 0xd80);

	auto weaponEntID = pWeaponHandle &= 0xFFF;
	auto pWeaponEnt = memory.Read<DWORD>(memory.ClientDLL.BaseAdress + MainOffsets::ptrEntityList + ((weaponEntID - 1) * 0x10));


	if (pWeaponEnt != NULL)
	{
		auto pWeaponVMT = memory.Read<DWORD>(pWeaponEnt);
		auto pGetWeaponID = memory.Read<DWORD>(pWeaponVMT + 0x5b4);
		auto uWeaponID = memory.Read<DWORD>(pGetWeaponID + 0x1);
		return (CSWeaponID)uWeaponID;
	}

	return CSWeaponID::WEAPON_NONE;
}