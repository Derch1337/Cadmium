#pragma once
#include "../../SDK/SDK.h"
#include "../Config/Config.h"

class CVisuals
{
private:
	Config& config;
	EntityHandler& entityHandle;


public:


private:
	ImColor GetColorHealth(int health);
	void DrawHealthBar(Vector2 top, Vector2 bottom, int health, ImColor fill_color, float bar_width, float offset);
	float* GetColorST(int et, int lt, bool iv, Config& config);


	void DrawHeadCircle(const EnemyEntity& Entity, ImColor color);
	void Draw2DBox(const EnemyEntity& Entity);
	void Draw3DBox(const EnemyEntity& Entity);
	void DrawHealthText(const EnemyEntity& Entity);
	void DrawNameText(const EnemyEntity& Entity);
	void DrawDistanceText(const EnemyEntity& Entity);
	void DrawWeaponName(const EnemyEntity& Entity);
	void DrawHealthBar(const EnemyEntity& Entity);
	void DrawEdgeHealthBar(const EnemyEntity& Entity);
	void DrawSkeleton(const EnemyEntity& Entity);
	void DrawTraceLine(const EnemyEntity& Entity);

public:
	CVisuals(Config& cfg, EntityHandler& handle);


	void DrawEntity();
};

