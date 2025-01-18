#include "Visuals.h"

CVisuals::CVisuals(Config& cfg, EntityHandler& handle) : config(cfg), entityHandle(handle)
{
}

void CVisuals::DrawEntity()
{

	if (!config.visualConfig.Enable) return;


	for (int index = 0; index < MAX_PLAYER; index++)
	{
		if (config.visualConfig.SpecOnly && entityHandle.localPlayer.lifeState == LifeState::ALIVE) continue;

		auto& Entity = entityHandle.EnemyList[index];

		if (Entity.Dormant) continue;

		if (config.visualConfig.VisibleOnly && !Entity.IsVisible) continue;
		if (config.visualConfig.NoVisibleOnly && Entity.IsVisible) continue;

		if (config.visualConfig.EnemyOnly && Entity.Team == entityHandle.localPlayer.Team) continue;

		if (Entity.lifeState != LifeState::ALIVE) continue;

		if (Entity.Health <= 0) continue;

		if (!Entity.OnScreen) continue;


		Draw2DBox(Entity);
		Draw3DBox(Entity);
		DrawHealthBar(Entity);
		DrawEdgeHealthBar(Entity);
		DrawSkeleton(Entity);
		DrawTraceLine(Entity);

		if ((int)Entity.DistanceToPlayer <= config.visualConfig.RenderTextMaxDistance) {
			DrawHealthText(Entity);
			DrawNameText(Entity);
			DrawDistanceText(Entity);
			DrawWeaponName(Entity);
		}
	}


	
}

ImColor CVisuals::GetColorHealth(int health)
{
	if (health > 98)
		return { 0, 255, 0, 204 }; // Bright Green
	if (health > 95)
		return { 26, 255, 26, 204 }; // Light Green
	if (health > 90)
		return { 51, 255, 51, 204 }; // Green
	if (health > 80)
		return { 102, 255, 0, 204 }; // Yellow Green
	if (health > 70)
		return { 153, 255, 0, 204 }; // Light Yellow Green
	if (health > 60)
		return { 204, 255, 0, 204 }; // Yellow
	if (health > 50)
		return { 255, 255, 0, 204 }; // Bright Yellow
	if (health > 40)
		return { 255, 204, 0, 204 }; // Light Orange
	if (health > 30)
		return { 255, 153, 0, 204 }; // Orange Yellow
	if (health > 25)
		return { 255, 102, 0, 204 }; // Orange
	if (health > 15)
		return { 255, 51, 0, 204 }; // Dark Orange
	if (health > 5)
		return { 255, 0, 0, 204 }; // Red
	return { 128, 0, 0, 204 }; // Dark Red
}

void CVisuals::DrawHealthBar(Vector2 top, Vector2 bottom, int health, ImColor fill_color, float bar_width, float offset)
{
	float boxHeight = top.y - bottom.y;
	float healthHeight = (health / 100.0f) * boxHeight;
	float BGRectThickness = 1.0f;

	ImVec2 borderTopLeft(top.x - bar_width - offset - BGRectThickness, top.y - BGRectThickness);
	ImVec2 borderBottomRight(top.x - offset + BGRectThickness, bottom.x + BGRectThickness);
	ImColor BGColor = ImColor(10, 10, 10, 255);
	ImGui::GetBackgroundDrawList()->AddRectFilled(borderTopLeft, borderBottomRight, BGColor, 0.0f, ImDrawFlags_None);

	ImVec2 healthTopLeft(top.x - bar_width - offset, bottom.x - healthHeight);
	ImVec2 healthBottomRight(top.x - offset, bottom.x);
	ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, fill_color, 0.0f, ImDrawFlags_None);
}

float* CVisuals::GetColorST(int et, int lt, bool iv, Config& config)
{
	float* color;
	if (et == lt)
		color = iv ? config.visualConfig.SkeletonFriendColor : config.visualConfig.SkeletonFriendNoVisibleColor;
	else
		color = iv ? config.visualConfig.SkeletonEnemyColor : config.visualConfig.SkeletonEnemyNoVisibleColor;

	return color;
}

void CVisuals::DrawHeadCircle(const EnemyEntity& Entity, ImColor color)
{
	float Radius = abs(Entity.Bones[BoneID::HEAD].ScreenPosition.y - Entity.Bones[BoneID::NECK].ScreenPosition.y);

	ImRender::DrawCircle(Entity.Bones[BoneID::HEAD].ScreenPosition, Radius, color, config.visualConfig.SkeletonThinkness);
}

void CVisuals::Draw2DBox(const EnemyEntity& Entity)
{
	if (!config.visualConfig.Box2DEnable) return;

	static float* color;
	if (Entity.Team == entityHandle.localPlayer.Team)
		color = Entity.IsVisible ? config.visualConfig.Box2DFriendColor : config.visualConfig.Box2DFriendNoVisibleColor;
	else
		color = Entity.IsVisible ? config.visualConfig.Box2DEnemyColor : config.visualConfig.Box2DEnemyNoVisibleColor;

	ImColor imColor = ImColor(color[0], color[1], color[2], color[3]);

	if (config.visualConfig.Box2DType == 0) {
		ImRender::DrawRect(
			Entity.Corner[CornerPosition],
			Entity.Corner[CornerSize],
			imColor,
			config.visualConfig.Box2DThinkness,
			config.visualConfig.Box2DRounded,
			config.visualConfig.Box2DFilled,
			ImColor(config.visualConfig.Box2DFilledBGColor[0], config.visualConfig.Box2DFilledBGColor[1], config.visualConfig.Box2DFilledBGColor[2], config.visualConfig.Box2DFilledBGColor[3]));
	}

	if (config.visualConfig.Box2DType == 1) {
		float width = Entity.Corner[CornerSize].x / 4;

		ImRender::DrawLine(Entity.Corner[CornerTopLeft], Entity.Corner[CornerTopLeft] + Vector2(width, 0), imColor, config.visualConfig.Box2DThinkness);
		ImRender::DrawLine(Entity.Corner[CornerTopLeft], Entity.Corner[CornerTopLeft] + Vector2(0, width), imColor, config.visualConfig.Box2DThinkness);

		ImRender::DrawLine(Entity.Corner[CornerTopRight], Entity.Corner[CornerTopRight] - Vector2(width, 0), imColor, config.visualConfig.Box2DThinkness);
		ImRender::DrawLine(Entity.Corner[CornerTopRight], Entity.Corner[CornerTopRight] + Vector2(0, width), imColor, config.visualConfig.Box2DThinkness);

		ImRender::DrawLine(Entity.Corner[CornerBottomRight], Entity.Corner[CornerBottomRight] - Vector2(width, 0), imColor, config.visualConfig.Box2DThinkness);
		ImRender::DrawLine(Entity.Corner[CornerBottomRight], Entity.Corner[CornerBottomRight] - Vector2(0, width), imColor, config.visualConfig.Box2DThinkness);

		ImRender::DrawLine(Entity.Corner[CornerBottomLeft], Entity.Corner[CornerBottomLeft] + Vector2(width, 0), imColor, config.visualConfig.Box2DThinkness);
		ImRender::DrawLine(Entity.Corner[CornerBottomLeft], Entity.Corner[CornerBottomLeft] - Vector2(0, width), imColor, config.visualConfig.Box2DThinkness);
	}
}

void CVisuals::Draw3DBox(const EnemyEntity& Entity)
{
	if (!config.visualConfig.Box3DEnable) return;

	static float* color;
	if (Entity.Team == entityHandle.localPlayer.Team)
		color = Entity.IsVisible ? config.visualConfig.Box3DFriendColor : config.visualConfig.Box3DFriendNoVisibleColor;
	else
		color = Entity.IsVisible ? config.visualConfig.Box3DEnemyColor : config.visualConfig.Box3DEnemyNoVisibleColor;

	auto colorLines = ImGui::ColorConvertFloat4ToU32({ color[0], color[1], color[2], color[3] });

	float thinkness = config.visualConfig.Box3DThinkness;


	float h = Entity.WorldPosition.z - Entity.WorldHeadPosition.z;
	float w = h / 3.5f;

	float cx = (Entity.WorldPosition.x + Entity.WorldHeadPosition.x) / 2.0f;
	float cy = (Entity.WorldPosition.y + Entity.WorldHeadPosition.y) / 2.0f;
	float cz = (Entity.WorldPosition.z + Entity.WorldHeadPosition.z) / 2.0f;

	Vector3 vertices[8] = {
		{cx - w / 2, cy - w / 2, cz - h / 2},
		{cx + w / 2, cy - w / 2, cz - h / 2},
		{cx + w / 2, cy + w / 2, cz - h / 2},
		{cx - w / 2, cy + w / 2, cz - h / 2},
		{cx - w / 2, cy - w / 2, cz + h / 2},
		{cx + w / 2, cy - w / 2, cz + h / 2},
		{cx + w / 2, cy + w / 2, cz + h / 2},
		{cx - w / 2, cy + w / 2, cz + h / 2}
	};

	Vector2 screenCoord3DParts[8];

	for (int i = 0; i < 8; ++i) {
		entityHandle.localPlayer.viewMatrix.WorldToScreen(vertices[i], screenCoord3DParts[i]);
	}

	Vector2 tempLines[4] = {
		screenCoord3DParts[4] - screenCoord3DParts[0],
		screenCoord3DParts[5] - screenCoord3DParts[1],
		screenCoord3DParts[6] - screenCoord3DParts[2],
		screenCoord3DParts[7] - screenCoord3DParts[3],
	};

	//animation lines

	static float counter = 0;
	static float speed = 0.01;

	counter += speed;

	float sineValue = (sin(counter) + 1) / 2;
	sineValue = sineValue * sineValue * (10 - 2 * sineValue);
	sineValue = sineValue * 8 + 1;

	//down

	ImRender::DrawLine(screenCoord3DParts[0], screenCoord3DParts[1], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[1], screenCoord3DParts[2], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[2], screenCoord3DParts[3], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[3], screenCoord3DParts[0], colorLines, thinkness);

	////up

	ImRender::DrawLine(screenCoord3DParts[4], screenCoord3DParts[5], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[5], screenCoord3DParts[6], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[6], screenCoord3DParts[7], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[7], screenCoord3DParts[4], colorLines, thinkness);

	if (config.visualConfig.Box3DEnableAnimation) {
		ImRender::DrawLine(screenCoord3DParts[4] - tempLines[0] / sineValue, screenCoord3DParts[5] - tempLines[1] / sineValue, colorLines, thinkness);
		ImRender::DrawLine(screenCoord3DParts[5] - tempLines[1] / sineValue, screenCoord3DParts[6] - tempLines[2] / sineValue, colorLines, thinkness);
		ImRender::DrawLine(screenCoord3DParts[6] - tempLines[2] / sineValue, screenCoord3DParts[7] - tempLines[3] / sineValue, colorLines, thinkness);
		ImRender::DrawLine(screenCoord3DParts[7] - tempLines[3] / sineValue, screenCoord3DParts[4] - tempLines[0] / sineValue, colorLines, thinkness);
	}

	////central

	ImRender::DrawLine(screenCoord3DParts[0], screenCoord3DParts[4], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[1], screenCoord3DParts[5], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[2], screenCoord3DParts[6], colorLines, thinkness);
	ImRender::DrawLine(screenCoord3DParts[3], screenCoord3DParts[7], colorLines, thinkness);
}

void CVisuals::DrawHealthText(const EnemyEntity& Entity)
{
	if (!config.visualConfig.MiskShowHealthText) return;
	ImRender::DrawTextW(
		"HP: " + std::to_string(Entity.Health) + "%",
		{ Entity.Corner[config.visualConfig.MiskHealthOffsetCorner].x + config.visualConfig.MiskHealthTextOffset[0], Entity.Corner[config.visualConfig.MiskHealthOffsetCorner].y + config.visualConfig.MiskHealthTextOffset[1] },
		ImColor(config.visualConfig.MiskHealthTextColor[0], config.visualConfig.MiskHealthTextColor[1], config.visualConfig.MiskHealthTextColor[2], config.visualConfig.MiskHealthTextColor[3]), Entity.font_current_size, false);
}

void CVisuals::DrawNameText(const EnemyEntity& Entity)
{
	if (!config.visualConfig.MiskShowName) return;
	ImRender::DrawTextW(
		Entity.DisplayName,
		{ Entity.Corner[config.visualConfig.MiskNameOffsetCorner].x + config.visualConfig.MiskNameOffset[0], Entity.Corner[config.visualConfig.MiskNameOffsetCorner].y + config.visualConfig.MiskNameOffset[1] },
		ImColor(config.visualConfig.MiskNameColor[0], config.visualConfig.MiskNameColor[1], config.visualConfig.MiskNameColor[2], config.visualConfig.MiskNameColor[3]), Entity.font_current_size, false);
}

void CVisuals::DrawDistanceText(const EnemyEntity& Entity)
{
	if (!config.visualConfig.MiskShowDistance) return;
	ImRender::DrawTextW(
		"Distance: " + std::to_string((int)Entity.DistanceToPlayer) + "M",
		{ Entity.Corner[config.visualConfig.MiskDistanceOffsetCorner].x + config.visualConfig.MiskDistanceOffset[0], Entity.Corner[config.visualConfig.MiskDistanceOffsetCorner].y + config.visualConfig.MiskDistanceOffset[1] },
		ImColor(config.visualConfig.MiskDistanceColor[0], config.visualConfig.MiskDistanceColor[1], config.visualConfig.MiskDistanceColor[2], config.visualConfig.MiskDistanceColor[3]), Entity.font_current_size, false);
}

void CVisuals::DrawWeaponName(const EnemyEntity& Entity)
{
	if (!config.visualConfig.MiskShowWeaponName) return;
	ImRender::DrawTextW(
		"Weapon: " +std::string(CSWeaponNames[Entity.WeaponID]),
		{ Entity.Corner[config.visualConfig.MiskWeaponNameOffsetCorner].x + config.visualConfig.MiskWeaponNameOffset[0], Entity.Corner[config.visualConfig.MiskWeaponNameOffsetCorner].y + config.visualConfig.MiskWeaponNameOffset[1] },
		ImColor(config.visualConfig.MiskWeaponNameColor[0], config.visualConfig.MiskWeaponNameColor[1], config.visualConfig.MiskWeaponNameColor[2], config.visualConfig.MiskWeaponNameColor[3]), Entity.font_current_size, false);
}

void CVisuals::DrawHealthBar(const EnemyEntity& Entity)
{
	if (!config.visualConfig.MiskShowHealthBar) return;

	Vector2 healthTopLeft = { Entity.Corner[CornerTopLeft].x - config.visualConfig.MiskHealthBarWidth - config.visualConfig.MiskHealthBarOffset, Entity.Corner[CornerBottomRight].y - ((Entity.Health / 100.0f) * (Entity.Corner[CornerBottomRight].y - Entity.Corner[CornerTopLeft].y)) };
	Vector2 healthBottomRight = { Entity.Corner[CornerTopLeft].x - config.visualConfig.MiskHealthBarOffset, Entity.Corner[CornerBottomRight].y };

	ImRender::DrawLine(healthTopLeft, healthBottomRight, GetColorHealth(Entity.Health));

	//DrawHealthBar(healthTopLeft, healthBottomRight, Entity.Health, GetColorHealth(Entity.Health), config.visualConfig.MiskHealthBarWidth, config.visualConfig.MiskHealthBarOffset);
}

void CVisuals::DrawEdgeHealthBar(const EnemyEntity& Entity)
{
	if (!config.visualConfig.MiskShowEdgeHealthBar) return;

	float _x = Entity.Corner[CornerPosition].x - Entity.Corner[CornerSize].x / 2 - config.visualConfig.MiskEdgeHealthBarOffset;
	float _y = Entity.Corner[CornerPosition].y + Entity.Corner[CornerSize].y;
	float _height = -Entity.Corner[CornerSize].y;

	float flBoxes = std::ceil(Entity.Health / 10.f);
	float flX = _x - 7 - _height / 4.f; float flY = _y - 1;
	float flHeight = _height / 10.f;
	float flMultiplier = 12 / 360.f;
	flMultiplier *= flBoxes - 1;

	ImColor ColHealth = ImColor(flMultiplier, 1.f, 1.f, 1.f);

	ImRender::DrawRect({ flX, flY }, { 4, _height + 2 }, ImColor(80, 80, 80, 125), 2, 5, true, ImColor(0, 1, 0, 255));
	ImRender::DrawRect({ flX + 1, flY }, { 2, flHeight * flBoxes + 1 }, GetColorHealth(Entity.Health));

	for (int i = 0; i < 10; i++)
		ImRender::DrawLine({ flX, flY + i * flHeight }, { flX + 4, flY + i * flHeight }, ImColor(0, 0, 0, 255));
}

void DrawCapsule(const Vector2& p1, const Vector2& p2, float radius, ImU32 color) {
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	// Вычисляем направление между двумя точками
	Vector2 dir = p2 - p1;
	float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length > 0.0f) {
		dir.x /= length; // Нормализуем направление
		dir.y /= length;
	}

	// Вычисляем перпендикулярное направление для ширины капсулы
	Vector2 perp(-dir.y * radius, dir.x * radius);

	// Вычисляем угловые точки прямоугольника (тела капсулы)
	Vector2 rect_p1 = p1 + perp;
	Vector2 rect_p2 = p2 + perp;
	Vector2 rect_p3 = p2 - perp;
	Vector2 rect_p4 = p1 - perp;

	

	// Рисуем тело (цилиндр) капсулы
	draw_list->AddQuadFilled(Vector2ToImVec2(rect_p1), Vector2ToImVec2(rect_p2), Vector2ToImVec2(rect_p3), Vector2ToImVec2(rect_p4), color);

	// Рисуем полусферы на концах
	draw_list->AddCircleFilled(Vector2ToImVec2(p1), radius, color, 32); // Левая полусфера
	draw_list->AddCircleFilled(Vector2ToImVec2(p2), radius, color, 32); // Правая полусфера
}

void CVisuals::DrawSkeleton(const EnemyEntity& Entity)
{
	if (!config.visualConfig.SkeletonEnable) return;

	if (config.visualConfig.DrawEnemyHeadCircle) {
		float* color = GetColorST(Entity.Team, entityHandle.localPlayer.Team, Entity.Bones[BoneID::HEAD].IsVisible, config);
		DrawHeadCircle(Entity, ImColor(color[0], color[1], color[2], color[3]));
	}

	for (int index = 0; index < 20; index++)
	{
		auto& bone1 = Entity.Bones[BonePair[index][0]];
		auto& bone2 = Entity.Bones[BonePair[index][1]];

		bool is_visible = bone1.IsVisible || bone2.IsVisible;

		float* color = GetColorST(Entity.Team, entityHandle.localPlayer.Team, is_visible, config);

		

		auto colIm = ImGui::ColorConvertFloat4ToU32(ImColor(color[0], color[1], color[2], color[3]));

		DrawCapsule(bone1.ScreenPosition, bone2.ScreenPosition, config.visualConfig.SkeletonConnectPointRadius, colIm);

		/*ImRender::DrawLine(
			bone1.ScreenPosition,
			bone2.ScreenPosition,
			ImColor(color[0], color[1], color[2], color[3]),
			config.visualConfig.SkeletonThinkness,
			config.visualConfig.SkeletonDrawConnectPoint,
			config.visualConfig.SkeletonConnectPointRadius,
			ImColor(color[0], color[1], color[2], color[3])
		);*/
	}
}

void CVisuals::DrawTraceLine(const EnemyEntity& Entity)
{
	if (!config.visualConfig.MiskShowTraceLine) return;

	float y = 0;

	if (config.visualConfig.MiskTraceLinePosition == 0)
		y = 0;

	if (config.visualConfig.MiskTraceLinePosition == 1)
		y = entityHandle.localPlayer.viewMatrix.screen_center.y;

	if (config.visualConfig.MiskTraceLinePosition == 2)
		y = entityHandle.localPlayer.viewMatrix.screen_size.y;


	ImRender::DrawLine(
		{ entityHandle.localPlayer.viewMatrix.screen_center.x , y },
		Entity.Corner[CornerHeadPosition],
		ImColor(config.visualConfig.MiskTraceLineColor[0], config.visualConfig.MiskTraceLineColor[1], config.visualConfig.MiskTraceLineColor[2], config.visualConfig.MiskTraceLineColor[3]),
		config.visualConfig.MiskTraceLineThinkness,
		config.visualConfig.MiskTraceLineDrawEndPoint,
		config.visualConfig.MiskTraceLineEndPointRadius,
		ImColor(config.visualConfig.MiskTraceLineColor[0], config.visualConfig.MiskTraceLineColor[1], config.visualConfig.MiskTraceLineColor[2], config.visualConfig.MiskTraceLineColor[3])
	);
}
