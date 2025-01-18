#pragma once
#include "../../SDK/SDK.h"
#include "../Config/Config.h"


class Radar
{
public:
	Radar(Config& cfg);

	void AddPoint(const Vector3& LocalPos, float localYaw, const Vector3& Pos, ImColor Color);

	void Render();

	void Update();


	
	


private:
	Config& config;

	Vector2 lineStart1;
	Vector2 lineEnd1;
	Vector2 lineStart2;
	Vector2 lineEnd2;

	Vector2 position2DList[MAX_PLAYER];
	ImColor colorList[MAX_PLAYER];
	int MaxPoints = 0;

	float Yaw;
};