#include "Radar.h"




Radar::Radar(Config& cfg) : config(cfg)
{
	
}


void Radar::AddPoint(const Vector3& LocalPos, float localYaw, const Vector3& Pos, ImColor Color)
{
	if (!config.radarConfig.Enable) return;


	Yaw = localYaw;
	Vector2 PointPos;
	float Distance;
	float Angle;

	
	Distance = Vector2Distance({ LocalPos.x, LocalPos.y }, { Pos.x, Pos.y});

	Angle = atan2(Pos.y - LocalPos.y, Pos.x - LocalPos.x) * 180.f / PI;
	Angle = (Yaw - Angle) * PI / 180.f;



	Distance = Distance / config.radarConfig.Proportion * config.radarConfig.RenderRange * 2.f;


	PointPos.x = config.radarConfig.Position[0] + Distance * sin(Angle);
	PointPos.y = config.radarConfig.Position[1] - Distance * cos(Angle);


	float halfWidth = config.radarConfig.Width / 2.0f;
	Vector2 center(config.radarConfig.Position[0], config.radarConfig.Position[1]);
	Vector2 offset = PointPos - center;

	if (std::abs(offset.x) > halfWidth || std::abs(offset.y) > halfWidth) {
		float scale = halfWidth / max(std::abs(offset.x), abs(offset.y));
		offset.x *= scale;
		offset.y *= scale;


		PointPos = center + offset;
	}
	position2DList[MaxPoints] = PointPos;
	colorList[MaxPoints] = Color;
	MaxPoints++;
}



void Radar::Render()
{
	if (!config.radarConfig.Enable) return;

	if (config.radarConfig.Width <= 0)
		return;


	lineStart1 = Vector2(config.radarConfig.Position[0] - config.radarConfig.Width / 2, config.radarConfig.Position[1]);
	lineEnd1 = Vector2(config.radarConfig.Position[0] + config.radarConfig.Width / 2, config.radarConfig.Position[1]);
	lineStart2 = Vector2(config.radarConfig.Position[0], config.radarConfig.Position[1] - config.radarConfig.Width / 2);
	lineEnd2 = Vector2(config.radarConfig.Position[0], config.radarConfig.Position[1] + config.radarConfig.Width / 2);

	if (config.radarConfig.ShowCrossLine)
	{
		ImColor color = ImColor(config.radarConfig.CrossLineColor[0], config.radarConfig.CrossLineColor[1], config.radarConfig.CrossLineColor[2], config.radarConfig.CrossLineColor[3]);

		ImRender::DrawLine(lineStart1, lineEnd1, color);
		ImRender::DrawLine(lineStart2, lineEnd2, color);
	}


	for (int index = 0; index < MaxPoints; index++) {

		ImRender::DrawCircleFilled(position2DList[index], config.radarConfig.CircleSize, colorList[index]);
	}
	MaxPoints = 0;
}

void Radar::Update()
{
   
}
