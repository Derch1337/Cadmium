#pragma once
#include <Imgui/imgui.h>
#include "../Math/Math.h"
#include <string>
#include <math.h>
#include <iostream>


class ImRender
{
public:
	static void DrawRectFilled(Vector2 position, Vector2 size, ImColor color = ImColor(255, 255, 255, 255));
	static void DrawRect(Vector2 position, Vector2 size, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, float rounding = 0.0f, bool filled = false, ImColor filled_color = ImColor(255, 255, 255, 255 / 2));
	static void DrawLine(Vector2 from, Vector2 to, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, bool draw_end_point = false, float end_point_radius = 1.0f, ImColor end_point_color = ImColor(255, 255, 255, 255));
	static void DrawTextW(std::string text, Vector2 position, ImColor color = ImColor(255, 255, 255, 255), float font_size = 15.0f, bool keep_center = true);
	static void DrawStrokeText(const std::string text, Vector2 position, ImColor text_color = ImColor(255, 255, 255, 255), ImColor stroke_color = ImColor(0, 0, 0, 255), float stroke_thickness = 1.0f, float font_size = 15.0f);
	static void DrawCircle(Vector2 position, float radius, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, int segments = 0);
	static void DrawCircleFilled(Vector2 position, float radius, ImColor color = ImColor(255, 255, 255, 128));

private:

};