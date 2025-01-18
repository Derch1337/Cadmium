#pragma once
#include "../../SDK/SDK.h"



struct VisualConfig
{
	bool Enable = true;
	bool EnemyOnly = false;
	bool VisibleOnly = false;
	bool NoVisibleOnly = false;
	bool SpecOnly = false;


	int RenderTextMaxDistance = 30;//meters

	bool Box2DEnable = false;
	bool Box2DFilled = false;
	int Box2DType = 0;
	float Box2DFilledBGColor[4] = { 1.f, 1.f, 1.f, 0.5f };
	float Box2DEnemyColor[4] = { 1.f, 0.f, 0.f, 1.f };
	float Box2DEnemyNoVisibleColor[4] = { 0.2f, 0.f, 0.f, 1.f };
	float Box2DFriendColor[4] = { 0.f, 0.f, 1.f, 1.f };
	float Box2DFriendNoVisibleColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	float Box2DThinkness = 2.f;
	float Box2DRounded = 5.f;

	bool Box3DEnable = false;
	bool Box3DEnableAnimation = false;
	float Box3DEnemyColor[4] = { 1.f, 0.f, 0.f, 1.f };
	float Box3DEnemyNoVisibleColor[4] = { 0.2f, 0.f, 0.f, 1.f };
	float Box3DFriendColor[4] = { 0.f, 0.f, 1.f, 1.f };
	float Box3DFriendNoVisibleColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	float Box3DThinkness = 2.f;

	bool SkeletonEnable = true;
	bool SkeletonDrawConnectPoint = false;
	bool SkeletonShowPenis = false;
	bool DrawEnemyHeadCircle = false;
	float SkeletonEnemyColor[4] = { 1.f, 0.f, 0.f, 1.f };
	float SkeletonEnemyNoVisibleColor[4] = { 0.2f, 0.f, 0.f, 1.f };
	float SkeletonFriendColor[4] = { 0.f, 0.f, 1.f, 1.f };
	float SkeletonFriendNoVisibleColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	float SkeletonThinkness = 2.f;
	float SkeletonConnectPointRadius = 2.f;
	float SkeletonPenisLength = 2.f;
	float SkeletonPenisThinkness = 2.f;
	float SkeletonPenisColor[4] = { 0.f, 0.f, 0.2f, 1.f };

	bool MiskShowName = false;
	float MiskNameOffset[2] = { 0.f, 0.f };
	float MiskNameColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	int MiskNameOffsetCorner = 0;

	bool MiskShowHealthText = false;
	float MiskHealthTextOffset[2] = { 0.f, 0.f };
	float MiskHealthTextColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	int MiskHealthOffsetCorner = 0;

	bool MiskShowDistance = false;
	float MiskDistanceOffset[2] = { 0.f, 0.f };
	float MiskDistanceColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	int MiskDistanceOffsetCorner = 0;

	bool MiskShowWeaponName = false;
	float MiskWeaponNameOffset[2] = { 0.f, 0.f };
	float MiskWeaponNameColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	int MiskWeaponNameOffsetCorner = 0;

	bool MiskShowTraceLine = false;
	bool MiskTraceLineDrawEndPoint = true;
	int MiskTraceLinePosition = 0;
	float MiskTraceLineEndPointRadius = 0;
	float MiskTraceLineColor[4] = { 0.f, 0.f, 0.2f, 1.f };
	float MiskTraceLineThinkness = 1.f;

	bool MiskShowHealthBar = false;
	float MiskHealthBarOffset = 0.f;
	float MiskHealthBarWidth = 1.f;

	bool MiskShowEdgeHealthBar = false;
	float MiskEdgeHealthBarOffset = 0.f;
	float MiskEdgeHealthBarWidth = 1.f;

};

struct MiscConfig {

	bool DrawCrosshaird2D = false;
	float CrossHair2DSize = 1.f;
	float CrossHair2DColor[4] = { 0.f, 0.f, 0.2f, 1.f };


	bool BHopEnable = false;
	bool BHopDefaultJumpEnable = false;
	int BHopDelay = 20;

	bool TriggerBot = false;
	bool TriggerBotFriendlyFire = false;
	bool TriggerBotFlashIgnore = false;
	int TriggerBotKey = 67;
	int TriggerDelay = 20;

};

struct DynamicCrosshairConfig {
	bool Enable = false;

	bool drawCrossline = true;
	int Gap = 1;
	bool drawOutLine = true;
	bool drawDot = true;
	bool tStyle = false;
	bool drawCircle = false;

	float HorizontalLength = 4;
	float VerticalLength = 4;
	float CircleRadius = 10;
	float Thickness = 1.f;

	int BorderWidth = 2;
	float DotSize = 1.f;

	float CrosshairColor[4] = { 1.f, 1.f, 1.f, 1.f };
};



struct RadarConfig
{
	bool Enable = true;
	bool ShowCrossLine = true;
	float CrossLineColor[4] = { 1.f, 1.f, 1.f, 1.f };
	float Proportion = 6000;//default 2680
	float CircleSize = 4;
	float RenderRange = 200;

	float Position[2] = { 87, 87 };
	float Width = 140;
};

class Config
{
private:




public:
	int Key_OpenMenu = 0x24;
	int Key_CloseHack = 0x23;

	VisualConfig visualConfig;
	MiscConfig miscConfig;
	DynamicCrosshairConfig dynamicCrosshairConfig;
	RadarConfig radarConfig;

	std::vector<std::string> config_name_list;
	int selected = 0;
	static const int MAX_PATH_SIZE = 128;
	char str_buffer[MAX_PATH_SIZE];
	const std::string configFormat = ".json";

public:
	Config();

	void LoadList();

	void LoadSelected();
	void SaveSelected(std::string cfg_name);
	void New();
	void DeleteSelected();
	void UpdateConfig();


};

