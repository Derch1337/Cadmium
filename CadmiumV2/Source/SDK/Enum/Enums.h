#pragma once

enum ClassIndex
{
    CCSPlayer = 27,
    CSPlayerResource = 28,
    WORLD_PLANTED_C4 = 81,
    GrenadeProjectile = 7,

    WORLD_WEAPON_AK47 = 1,
    WORLD_WEAPON_C4 = 23,
    WORLD_WEAPON_DEAGLE = 31,

    WORLD_WEAPON_FLASHBANG = 49,
    WORLD_WEAPON_HEGRENADE = 65,
    WORLD_WEAPON_SMOKEGRENADE = 98,

    WORLD_WEAPON_AUG = 162,
    WORLD_WEAPON_AWP = 163,

    WORLD_WEAPON_ELITE = 167,
    WORLD_WEAPON_FAMAS = 168,
    WORLD_WEAPON_FIVESEVEN = 169,
    WORLD_WEAPON_G3SG1 = 170,
    WORLD_WEAPON_GALIL = 171,
    WORLD_WEAPON_GLOCK = 172,
    WORLD_WEAPON_M249 = 173,
    WORLD_WEAPON_M3 = 174,
    WORLD_WEAPON_M4A1 = 175,
    WORLD_WEAPON_MAC10 = 176,
    WORLD_WEAPON_MP5NAVY = 177,
    WORLD_WEAPON_P228 = 178,
    WORLD_WEAPON_P90 = 179,
    WORLD_WEAPON_SCOUT = 180,
    WORLD_WEAPON_SG550 = 181,
    WORLD_WEAPON_SG552 = 182,
    WORLD_WEAPON_TMP = 183,
    WORLD_WEAPON_UMP45 = 184,
    WORLD_WEAPON_USP = 185,
    WORLD_WEAPON_XM1014 = 186,


};


enum TeamNum {
    SPECTATOR,
    TT,
    CT
};
enum GrenadeType {
    HeGrenade,
    FlashBang,
    SmokeGrenade
};

enum BombPlantType {
    SITE_A,
    SITE_B,
    SITE_C,
    SITE_D
};

enum LifeState
{
    ALIVE = 0,				// alive
    DYING = 1,				// playing death animation or still falling off of a ledge waiting to hit ground
    DEAD = 2,				// dead. lying still.
    RESPAWNABLE = 3,
    DISCARDBODY = 4
};


enum BoneGroup {
    HeadGroup,
    BodyGroup,
    LeftHandGroup,
    RigthHandGroup,
    LeftLegGroup,
    RightLegGroup,
};



enum BoneID {
    PELVIS,
    LEFT_HIPS,
    LEFT_KNEE,
    LEFT_ANKLE,
    LEFT_FOOT,
    RIGHT_HIPS,
    RIGHT_KNEE,
    RIGHT_ANKLE,
    RIGHT_FOOT,
    STOMACH,
    BODY,
    CHEST,
    NECK,
    FACE,
    HEAD,
    LEFT_NECK,
    LEFT_SHOULDER,
    LEFT_ELBOW,
    LEFT_HAND,
    RIGHT_NECK = 28,
    RIGHT_SHOULDER,
    RIGHT_ELBOW,
    RIGHT_HAND
};






enum CSWeaponType
{
    WEAPONTYPE_KNIFE = 0,
    WEAPONTYPE_PISTOL,
    WEAPONTYPE_SUBMACHINEGUN,
    WEAPONTYPE_RIFLE,
    WEAPONTYPE_SHOTGUN,
    WEAPONTYPE_SNIPER_RIFLE,
    WEAPONTYPE_MACHINEGUN,
    WEAPONTYPE_C4,
    WEAPONTYPE_GRENADE,
    WEAPONTYPE_UNKNOWN

};


enum CSWeaponID
{
    WEAPON_NONE = 0,
    WEAPON_P228,
    WEAPON_GLOCK,
    WEAPON_SCOUT,
    WEAPON_HEGRENADE,
    WEAPON_XM1014,
    WEAPON_C4,
    WEAPON_MAC10,
    WEAPON_AUG,
    WEAPON_SMOKEGRENADE,
    WEAPON_ELITE,
    WEAPON_FIVESEVEN,
    WEAPON_UMP45,
    WEAPON_SG550,
    WEAPON_GALIL,
    WEAPON_FAMAS,
    WEAPON_USP,
    WEAPON_AWP,
    WEAPON_MP5NAVY,
    WEAPON_M249,
    WEAPON_M3,
    WEAPON_M4A1,
    WEAPON_TMP,
    WEAPON_G3SG1,
    WEAPON_FLASHBANG,
    WEAPON_DEAGLE,
    WEAPON_SG552,
    WEAPON_AK47,
    WEAPON_KNIFE,
    WEAPON_P90,
    WEAPON_SHIELDGUN,
    WEAPON_KEVLAR,
    WEAPON_ASSAULTSUIT,
    WEAPON_NVG,
    WEAPON_MAX,
};

inline const char* CSWeaponNames[] = {
    "NONE",
    "P228",
    "GLOCK",
    "SCOUT",
    "HE_GRENADE",
    "XM_1014",
    "C4",
    "MAC_10",
    "AUG",
    "SMOKE_GRENADE",
    "DUAL_ELITE",
    "FIVE_SEVEN",
    "UMP_45",
    "SG_550",
    "GALIL",
    "FAMAS",
    "USP",
    "AWP",
    "MP5 NAVY",
    "M249",
    "M3",
    "M4A1",
    "TMP",
    "G3SG1",
    "FLASHBANG",
    "DEAGLE",
    "SG_552",
    "AK47",
    "KNIFE",
    "P90",
    "SHIELD_GUN",
    "KEVLAR",
    "ASSAULTSUIT",
    "NVG",
    "MAX"
};
