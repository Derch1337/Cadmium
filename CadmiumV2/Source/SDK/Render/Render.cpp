#include "Render.h"

void ImRender::DrawRectFilled(Vector2 position, Vector2 size, ImColor color)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(
        ImVec2(position.x, position.y),
        ImVec2(position.x + size.x, position.y + size.y),
        color);
}

void ImRender::DrawRect(Vector2 position, Vector2 size, ImColor color, float thickness, float rounding, bool filled, ImColor filled_color)
{
    if (filled)
        ImGui::GetBackgroundDrawList()->AddRectFilled(
            ImVec2(position.x, position.y),
            ImVec2(position.x + size.x, position.y + size.y),
            filled_color, rounding, ImDrawFlags_None);

    ImGui::GetBackgroundDrawList()->AddRect(
        ImVec2(position.x, position.y),
        ImVec2(position.x + size.x, position.y + size.y),
        color, rounding, 0, thickness);
}

void ImRender::DrawLine(Vector2 from, Vector2 to, ImColor color, float thickness, bool draw_end_point, float end_point_radius, ImColor end_point_color)
{
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);

    if (draw_end_point)
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), end_point_radius, end_point_color);
}

void ImRender::DrawTextW(std::string text, Vector2 position, ImColor color, float font_size, bool keep_center)
{
    if (!keep_center)
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), font_size, { position.x, position.y }, color, text.c_str());
    else
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), font_size, { position.x - (ImGui::GetFont()->CalcTextSizeA(font_size, FLT_MAX, 0.f, text.c_str()).x) / 2, position.y }, color, text.c_str());
}

void ImRender::DrawStrokeText(const std::string text, Vector2 position, ImColor text_color, ImColor stroke_color, float stroke_thickness, float font_size)
{
    ImFont* font = ImGui::GetFont();
    auto drawlist = ImGui::GetBackgroundDrawList();

    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x - stroke_thickness, position.y), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x + stroke_thickness, position.y), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x, position.y - stroke_thickness), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x, position.y + stroke_thickness), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x - stroke_thickness, position.y - stroke_thickness), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x + stroke_thickness, position.y - stroke_thickness), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x - stroke_thickness, position.y + stroke_thickness), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x + stroke_thickness, position.y + stroke_thickness), stroke_color, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size, ImVec2(position.x, position.y), text_color, text.c_str());
}

void ImRender::DrawCircle(Vector2 position, float radius, ImColor color, float thickness, int segments)
{
    ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(position.x, position.y), radius, color, segments, thickness);
}

void ImRender::DrawCircleFilled(Vector2 position, float radius, ImColor color)
{
    ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(position.x, position.y), radius, color, 0);
}
