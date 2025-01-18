#include "Misk.h"





Misc::Misc(Config& cfg, EntityHandler& handler) : config(cfg), entityHandler(handler)
{
	
}

void Misc::Update()
{
	radar.Render();

	DrawCrossHair();
	DrawCrossHair2D();

	Bhop();
	Trigger();
	//DrawTriggerZone();



	for (int index = 0; index < MAX_PLAYER; index++)
	{
		if (entityHandler.EnemyList[index].dwEntity == entityHandler.localPlayer.dwEntity) continue;

		if (entityHandler.EnemyList[index].Health > 0 && entityHandler.EnemyList[index].lifeState == LifeState::ALIVE)
		{

			ImColor color = ImColor(0.f, 0.f, 1.f, 1.f);

			if (entityHandler.EnemyList[index].Team == 2)
				color = ImColor(1.f, 0.f, 0.f, 1.f);

			radar.AddPoint(entityHandler.localPlayer.WorldHeadPosition, entityHandler.localPlayer.ViewAngle.y, entityHandler.EnemyList[index].WorldHeadPosition, color);
		}
	}

}




void Misc::DrawCrossHair()
{
	if (!config.dynamicCrosshairConfig.Enable) return;

	auto drawList = ImGui::GetBackgroundDrawList();
	int gap = config.dynamicCrosshairConfig.Gap / 2;
	int outlineGap = gap - 1;
	float Thickness = config.dynamicCrosshairConfig.Thickness;

	ImVec2 offset1{
		config.dynamicCrosshairConfig.DotSize,
		config.dynamicCrosshairConfig.DotSize };

	ImVec2 offset2{
		config.dynamicCrosshairConfig.DotSize + 1,
		config.dynamicCrosshairConfig.DotSize + 1 };

	ImU32 color = ImGui::ColorConvertFloat4ToU32(ImVec4(
		config.dynamicCrosshairConfig.CrosshairColor[0],
		config.dynamicCrosshairConfig.CrosshairColor[1],
		config.dynamicCrosshairConfig.CrosshairColor[2],
		config.dynamicCrosshairConfig.CrosshairColor[3]
	));

	Vector2 pos = entityHandler.localPlayer.viewMatrix.screen_center;


	if (config.dynamicCrosshairConfig.drawOutLine)
	{
		//dot
		if (config.dynamicCrosshairConfig.drawDot)
			drawList->AddRectFilled(ImVec2(pos.x - offset1.x, pos.y - offset1.y), ImVec2(pos.x + offset2.x, pos.y + offset2.y), color & IM_COL32_A_MASK);

		if (config.dynamicCrosshairConfig.drawCrossline)
		{
			//left
			drawList->AddRectFilled(ImVec2(pos.x - (outlineGap + config.dynamicCrosshairConfig.BorderWidth + config.dynamicCrosshairConfig.HorizontalLength), pos.y - Thickness), ImVec2(pos.x - outlineGap, pos.y + 1 + Thickness), color & IM_COL32_A_MASK);
			//right
			drawList->AddRectFilled(ImVec2(pos.x + (outlineGap + config.dynamicCrosshairConfig.DotSize), pos.y - Thickness), ImVec2(pos.x + (outlineGap + config.dynamicCrosshairConfig.DotSize + config.dynamicCrosshairConfig.BorderWidth + config.dynamicCrosshairConfig.HorizontalLength), pos.y + 1 + Thickness), color & IM_COL32_A_MASK);
			//top
			if (!config.dynamicCrosshairConfig.tStyle)
				drawList->AddRectFilled(ImVec2(pos.x - Thickness, pos.y - (outlineGap + config.dynamicCrosshairConfig.BorderWidth + config.dynamicCrosshairConfig.VerticalLength)), ImVec2(pos.x + 1 + Thickness, pos.y - outlineGap), color & IM_COL32_A_MASK);
			//bottom
			drawList->AddRectFilled(ImVec2(pos.x - Thickness, pos.y + outlineGap + config.dynamicCrosshairConfig.DotSize), ImVec2(pos.x + 1 + Thickness, pos.y + (outlineGap + config.dynamicCrosshairConfig.DotSize + config.dynamicCrosshairConfig.BorderWidth + config.dynamicCrosshairConfig.VerticalLength)), color & IM_COL32_A_MASK);
		}

		//circle
		if (config.dynamicCrosshairConfig.drawCircle)
			drawList->AddCircle(ImVec2(pos.x, pos.y), config.dynamicCrosshairConfig.CircleRadius, color & IM_COL32_A_MASK, 0, 3.0f);
	}

	/*
	===== Crosshair =====
	*/
	// dot
	if (config.dynamicCrosshairConfig.drawDot)
		drawList->AddRectFilled(ImVec2(pos.x - offset1.x + config.dynamicCrosshairConfig.DotSize, pos.y - offset1.y + config.dynamicCrosshairConfig.DotSize), ImVec2(pos.x + offset1.x, pos.y + offset1.y), color);

	if (config.dynamicCrosshairConfig.drawCrossline)
	{
		// left
		drawList->AddRectFilled(ImVec2(pos.x - (gap + config.dynamicCrosshairConfig.HorizontalLength), pos.y - Thickness + 1), ImVec2(pos.x - gap, pos.y + Thickness), color);
		// right
		drawList->AddRectFilled(ImVec2(pos.x + gap + config.dynamicCrosshairConfig.DotSize, pos.y - Thickness + 1), ImVec2(pos.x + (gap + config.dynamicCrosshairConfig.DotSize + config.dynamicCrosshairConfig.HorizontalLength), pos.y + Thickness), color);
		// top
		if (!config.dynamicCrosshairConfig.tStyle)
			drawList->AddRectFilled(ImVec2(pos.x - Thickness + 1, pos.y - (gap + config.dynamicCrosshairConfig.VerticalLength)), ImVec2(pos.x + Thickness, pos.y - gap), color);
		// bottom
		drawList->AddRectFilled(ImVec2(pos.x - Thickness + 1, pos.y + gap + config.dynamicCrosshairConfig.DotSize), ImVec2(pos.x + Thickness, pos.y + (gap + config.dynamicCrosshairConfig.DotSize + config.dynamicCrosshairConfig.VerticalLength)), color);
	}

	// circle
	if (config.dynamicCrosshairConfig.drawCircle)
		drawList->AddCircle(ImVec2(pos.x, pos.y), config.dynamicCrosshairConfig.CircleRadius, color, 0, 1.0f);
}

void Misc::DrawCrossHair2D()
{
	if (!config.miscConfig.DrawCrosshaird2D) return;

	ImColor CrossHairColor = ImColor(config.miscConfig.CrossHair2DColor[0], config.miscConfig.CrossHair2DColor[1], config.miscConfig.CrossHair2DColor[2], config.miscConfig.CrossHair2DColor[3]);

	ImRender::DrawLine(
		{ entityHandler.localPlayer.viewMatrix.screen_center.x - config.miscConfig.CrossHair2DSize, entityHandler.localPlayer.viewMatrix.screen_center.y },
		{ entityHandler.localPlayer.viewMatrix.screen_center.x + config.miscConfig.CrossHair2DSize, entityHandler.localPlayer.viewMatrix.screen_center.y }, CrossHairColor, 1);

	ImRender::DrawLine(
		{ entityHandler.localPlayer.viewMatrix.screen_center.x, entityHandler.localPlayer.viewMatrix.screen_center.y - config.miscConfig.CrossHair2DSize },
		{ entityHandler.localPlayer.viewMatrix.screen_center.x , entityHandler.localPlayer.viewMatrix.screen_center.y + config.miscConfig.CrossHair2DSize }, CrossHairColor, 1);
}

void Misc::Bhop()
{
	if (!config.miscConfig.BHopEnable) return;
	if (entityHandler.localPlayer.Health <= 0) return;

	static std::chrono::time_point bhop_lastTimePoint = std::chrono::steady_clock::now();

	if (config.miscConfig.BHopDefaultJumpEnable) {
		if (GetAsyncKeyState(0x56) & 1)
			Input::SendMouseScroll();
	}
	else {
		auto curTimePoint = std::chrono::steady_clock::now();

		if (GetAsyncKeyState(0x56) && entityHandler.localPlayer.Flags & FL_ONGROUND)
		{
			if (curTimePoint - bhop_lastTimePoint >= std::chrono::milliseconds(config.miscConfig.BHopDelay)) {
				bhop_lastTimePoint = curTimePoint;

				Input::SendMouseScroll();
			}
		}

		

	}
}

void Misc::Trigger()
{
	if (!config.miscConfig.TriggerBot) return;
	if(!GetAsyncKeyState(config.miscConfig.TriggerBotKey)) return;

	auto crosshairEntityId = entityHandler.localPlayer.CrosshairEntityID - 1;
	if (crosshairEntityId < 0) return;

	auto enemyEntity = entityHandler.EnemyList[crosshairEntityId];

	if (enemyEntity.Health < 0) return;

	if(!config.miscConfig.TriggerBotFriendlyFire && enemyEntity.Team == entityHandler.localPlayer.Team)
		return;

	
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();
	if (CurTimePoint - LastTimePoint >= std::chrono::milliseconds(config.miscConfig.TriggerDelay))
	{
		const bool isAlreadyShooting = GetAsyncKeyState(VK_LBUTTON) < 0;
		if (!isAlreadyShooting)
		{
			Input::MouseLeftClick();
		}

		LastTimePoint = CurTimePoint;
	}


}




void Misc::DrawTriggerZone()
{
	float size_multiplier = 1.f;

	auto crosshairEntityId = entityHandler.localPlayer.CrosshairEntityID - 1;
	if (crosshairEntityId < 0) return;

	auto enemyEntity = entityHandler.EnemyList[crosshairEntityId];

	if (enemyEntity.Health < 0) return;


	const auto& bone1 = enemyEntity.Bones[BoneID::HEAD];
	const auto& bone2 = enemyEntity.Bones[BoneID::NECK];

	float radius = (bone1.ScreenPosition.y - bone2.ScreenPosition.y);

	Vector2 middlePos;
	middlePos.x = (bone1.ScreenPosition.x + bone2.ScreenPosition.x) / 2;
	middlePos.y = (bone1.ScreenPosition.y + bone2.ScreenPosition.y) / 2;


	float distance = Vector2Distance(middlePos, entityHandler.localPlayer.viewMatrix.screen_center);
	float distance2 = Vector2Distance(bone1.ScreenPosition, bone2.ScreenPosition);

	ImRender::DrawCircle(bone1.ScreenPosition, distance2);
	ImRender::DrawCircle(bone2.ScreenPosition, distance2);


	if (distance <= radius)
	{
		//Input::MouseLeftClick();
		ImRender::DrawCircle(middlePos, radius, ImColor(1.f, 0.f, 0.f, 1.f));
	}
	else {
		ImRender::DrawCircle(middlePos, radius);
	}
			





}
