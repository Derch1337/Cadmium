#include "Menu.h"
#include "Icons/VisualsIcon.h"
#include "Icons/MiskIcon.h"
#include "Icons/ConfigIcon.h"
#include "Icons/CloseIcon.h"


BImage* visualImage;
BImage* miscImage;
BImage* configImage;
BImage* closeImage;

Menu::Menu(Overlay& overlay, Config& cfg) : config(cfg)
{


    visualImage = new BImage(OverlayBackgroundData::pDevice, VisualsIcon, 6694);
    miscImage = new BImage(OverlayBackgroundData::pDevice, MiskIcon, 18832);
    configImage = new BImage(OverlayBackgroundData::pDevice, ConfigIcon, 6631);
    closeImage = new BImage(OverlayBackgroundData::pDevice, CloseIcon, 4584);
    auto& io = ImGui::GetIO();

    font10 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 10);
    font12 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 12);
    font14 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 14);
    font18 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 18);


    SetStyle();
}

Menu::~Menu()
{
}

void CColorPicker(float* color, std::string tags, Vector2 size = {15, 15}) {

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(color[0], color[1], color[2], 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color[0], color[1], color[2], 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color[0], color[1], color[2], 1.0f));


    if (ImGui::Button(std::string("##ColorButton" + tags).c_str(), { size.x, size.y}))
        ImGui::OpenPopup(std::string("##ColorButton" + tags).c_str());

    if (ImGui::BeginPopup(std::string("##ColorButton" + tags).c_str())) {
        ImGui::ColorPicker4(std::string("##ColorButton" + tags).c_str(), color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoLabel);
        ImGui::EndPopup();
    }
    ImGui::PopStyleColor(3);
}



bool CustomImageButton(const char* label, ImTextureID texture, ImVec2 size) {

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));         // Прозрачный фон кнопки
    //ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));  // Прозрачный фон при наведении
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

    bool clicked = ImGui::ImageButton(label, texture, size);

    ImGui::PopStyleColor(2);
    return clicked;
}


void Menu::Draw()
{
    const float IconSize = 48;

    
    auto screen = ImGui::GetIO().DisplaySize;


    ImRender::DrawRectFilled({ 0, 0 }, { screen.x, screen.y}, ImColor(0.f, 0.f, 0.f, 0.3f));


    ImGui::SetNextWindowSize({ MenuWidth, MenuHeight }, ImGuiCond_FirstUseEver);
    ImGui::Begin("Main", nullptr, MenuFlags);

    ImGui::BeginChild("MainContent", ImVec2(IconSize * 1.8, 0), true);

    if (CustomImageButton("Visuals", (ImTextureID)visualImage->out_texture, ImVec2(IconSize, IconSize)))
        menu_tabs_item = MenuTabItem::Visuals;

    if (CustomImageButton("Misc", (ImTextureID)miscImage->out_texture, ImVec2(IconSize, IconSize)))
        menu_tabs_item = MenuTabItem::Misk;

    if (CustomImageButton("Config", (ImTextureID)configImage->out_texture, ImVec2(IconSize, IconSize)))
    {
        menu_tabs_item = MenuTabItem::ConfigItem;
        config.LoadList();
    }

    if (CustomImageButton("Close", (ImTextureID)closeImage->out_texture, ImVec2(IconSize, IconSize)))
        exit(0);

    ImGui::EndChild();


    ImGui::SameLine();

    ImGui::BeginChild("Content", ImVec2(0, 0), true);

    ImGui::PushFont(font12);
    switch (menu_tabs_item)
    {
    case MenuTabItem::Visuals:
        DrawVisualsMenu();
        break;
    case MenuTabItem::Misk:
        DrawMiskMenu();
        break;
    case MenuTabItem::ConfigItem:
        DrawConfigMenu();
        break;
    }
    ImGui::PopFont();

    ImGui::EndChild();


    ImGui::End();
}


bool CustomRadioButton(int count, std::vector<std::string> names, int& values) {

    if (names.size() != count) {
        // Ensure the sizes of the inputs match the count
        return false;
    }

    bool clicked = false;
    for (int i = 0; i < count; i++)
    {
        clicked = ImGui::RadioButton(std::string(names[i] + "##radio_button_cistom_id_" + std::to_string(i)).c_str(), values == i);

        if (clicked) values = i;
        if (i < count - 1) {
            ImGui::SameLine();
        }
    }
    return clicked;
}


void Menu::DrawVisualsMenu()
{
    ImGui::Checkbox("Enable ##main_visual", &config.visualConfig.Enable);

    ImGui::SameLine();

    ImGui::Checkbox("Enemy Only ##main_visual", &config.visualConfig.EnemyOnly);

    ImGui::SameLine();

    ImGui::Checkbox("Visible Only ##main_visual", &config.visualConfig.VisibleOnly);

    ImGui::SameLine();
    
    ImGui::Checkbox("No Visible Only ##main_visual", &config.visualConfig.NoVisibleOnly);

    ImGui::SameLine();
    
    ImGui::Checkbox("Spectator Only ##main_visual", &config.visualConfig.SpecOnly);

    ImGui::Spacing();

    if (ImGui::BeginTabBar("VisualsTabs")) {

        ImGui::Spacing();

        if (ImGui::BeginTabItem("Box2D ##box2d")) {

            ImGui::Checkbox("Enable ##enable_box2d", &config.visualConfig.Box2DEnable);
            ImGui::SameLine();
            ImGui::Checkbox("Filled ##enable_box2d_filled", &config.visualConfig.Box2DFilled);

            ImGui::Spacing();
            ImGui::Text("Visual Type");
            ImGui::SameLine();
            CustomRadioButton(2, { "Flat", "Corner" }, config.visualConfig.Box2DType);

            ImGui::Spacing();

            ImGui::SliderFloat("Thinkness ##box2d_thinkness", &config.visualConfig.Box2DThinkness, 1, 7);
            ImGui::SliderFloat("Rounded ##box2d_rounded", &config.visualConfig.Box2DRounded, 0, 15);

            ImGui::Spacing();

            CColorPicker(config.visualConfig.Box2DFilledBGColor, "##box2d_filled"); ImGui::SameLine(); ImGui::ColorEdit4("Filled Color##box2d_filled", config.visualConfig.Box2DFilledBGColor, ColorEditorFlags);

            ImGui::SameLine();
            ImGui::Spacing();

            CColorPicker(config.visualConfig.Box2DEnemyColor, "##box2d_filled1"); ImGui::SameLine(); ImGui::ColorEdit4("Enemy Visible ##box2d_enemy", config.visualConfig.Box2DEnemyColor, ColorEditorFlags);
            CColorPicker(config.visualConfig.Box2DEnemyNoVisibleColor, "##box2d_filled2"); ImGui::SameLine(); ImGui::ColorEdit4("Enemy No Visible ##box2d_enemy", config.visualConfig.Box2DEnemyNoVisibleColor, ColorEditorFlags);

            ImGui::Spacing();

            CColorPicker(config.visualConfig.Box2DFriendColor, "##box2d_friend3"); ImGui::SameLine(); ImGui::ColorEdit4("Friend Visible ##box2d_friend", config.visualConfig.Box2DFriendColor, ColorEditorFlags);
            CColorPicker(config.visualConfig.Box2DFriendNoVisibleColor, "##box2d_friend4"); ImGui::SameLine(); ImGui::ColorEdit4("Friend No Visible ##box2d_friend", config.visualConfig.Box2DFriendNoVisibleColor, ColorEditorFlags);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Box3D ##box3d")) {

            ImGui::Checkbox("Enable ##enable_box3d", &config.visualConfig.Box3DEnable);

            ImGui::SameLine();

            ImGui::Checkbox("Enable Animation ##enable_box3d_anim", &config.visualConfig.Box3DEnableAnimation);

            ImGui::Spacing();

            ImGui::SliderFloat("Thinkness ##box3d_thinkness", &config.visualConfig.Box3DThinkness, 1, 5);

            ImGui::Spacing();

            CColorPicker(config.visualConfig.Box3DEnemyColor, "##box3d_friendd"); ImGui::SameLine(); ImGui::ColorEdit4("Enemy Visible ##box3d_enemy", config.visualConfig.Box3DEnemyColor, ColorEditorFlags);
            CColorPicker(config.visualConfig.Box3DEnemyNoVisibleColor, "##box3d_frdawiend"); ImGui::SameLine(); ImGui::ColorEdit4("Enemy No Visible ##box3d_enemy", config.visualConfig.Box3DEnemyNoVisibleColor, ColorEditorFlags);

            ImGui::Spacing();

            CColorPicker(config.visualConfig.Box3DFriendColor, "##box3d_frawdiend"); ImGui::SameLine(); ImGui::ColorEdit4("Friend Visible ##box3d_friend", config.visualConfig.Box3DFriendColor, ColorEditorFlags);
            CColorPicker(config.visualConfig.Box3DFriendNoVisibleColor, "##box3dawd_friend"); ImGui::SameLine(); ImGui::ColorEdit4("Friend No Visible ##box3d_friend", config.visualConfig.Box3DFriendNoVisibleColor, ColorEditorFlags);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Skeleton ##skeleton")) {

            ImGui::Checkbox("Enable ##enable_skeleton", &config.visualConfig.SkeletonEnable);

            ImGui::SameLine();

            ImGui::Checkbox("Draw Connect Point ##draw_point_skeleton", &config.visualConfig.SkeletonDrawConnectPoint);

            ImGui::SameLine();
            
            ImGui::Checkbox("Draw Head Circle ##draw_point_skeleton", &config.visualConfig.DrawEnemyHeadCircle);

            ImGui::Spacing();

            ImGui::SliderFloat("Thinkness ##skeleton_thinkness", &config.visualConfig.SkeletonThinkness, 1, 10);
            ImGui::SliderFloat("Connect Point Radius ##skeleton_ConnectPointRadius", &config.visualConfig.SkeletonConnectPointRadius, 1, 10);

            ImGui::Spacing();

            CColorPicker(config.visualConfig.SkeletonEnemyColor, "##skeleton_awdenemy"); ImGui::SameLine(); ImGui::ColorEdit4("Enemy Visible ##skeleton_enemy", config.visualConfig.SkeletonEnemyColor, ColorEditorFlags);
            CColorPicker(config.visualConfig.SkeletonEnemyNoVisibleColor, "##skeleton_eawdgemy"); ImGui::SameLine(); ImGui::ColorEdit4("Enemy No Visible ##skeleton_enemy", config.visualConfig.SkeletonEnemyNoVisibleColor, ColorEditorFlags);

            ImGui::Spacing();

            CColorPicker(config.visualConfig.SkeletonFriendColor, "##skeleton_frzcziend"); ImGui::SameLine(); ImGui::ColorEdit4("Friend Visible ##skeleton_friend", config.visualConfig.SkeletonFriendColor, ColorEditorFlags);
            CColorPicker(config.visualConfig.SkeletonFriendNoVisibleColor, "##skeletonqghase_friend"); ImGui::SameLine(); ImGui::ColorEdit4("Friend No Visible ##skeleton_friend", config.visualConfig.SkeletonFriendNoVisibleColor, ColorEditorFlags);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misk ##misk_main")) {
            static float MiskOffsetMin = -50;
            static float MiskOffsetMax = 50;

            ImGui::SliderInt("Rendered Text Max Distance##max_dist_text_render", &config.visualConfig.RenderTextMaxDistance, 1, 100);


            ImGui::Spacing();
            ImGui::Checkbox("Show Health Bar ##health_bar", &config.visualConfig.MiskShowHealthBar);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(350);
            ImGui::SliderFloat("Health Bar  Offset ##health_bar", &config.visualConfig.MiskHealthBarOffset, MiskOffsetMin, MiskOffsetMax);

            ImGui::Spacing();
            
            ImGui::Checkbox("Show Edge Health Bar ##health_bar_edge", &config.visualConfig.MiskShowEdgeHealthBar);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(350);
            ImGui::SliderFloat("Edge Health Bar Offset ##health_bar_edge", &config.visualConfig.MiskEdgeHealthBarOffset, MiskOffsetMin, MiskOffsetMax);

            ImGui::Spacing();

            ImGui::Checkbox("Show Name ##misk_show_name", &config.visualConfig.MiskShowName); 
            ImGui::SameLine();
            CColorPicker(config.visualConfig.MiskNameColor, "##misk_cdawdawdolor_name");
            ImGui::SameLine();
            CustomRadioButton(3, { "Corner Top Left##text_Name", "Corner Top Right##text_Name", "Corner Bottom Right##text_Name" }, config.visualConfig.MiskNameOffsetCorner);
            ImGui::SliderFloat2("Name Offset ##misk_offset_name", config.visualConfig.MiskNameOffset, MiskOffsetMin, MiskOffsetMax);
            
            ImGui::Spacing();

            ImGui::Checkbox("Show Health Text ##misk_show_HealthText", &config.visualConfig.MiskShowHealthText);
            ImGui::SameLine();
            CColorPicker(config.visualConfig.MiskHealthTextColor, "##misk_cawdawdolor_HealthText");
            ImGui::SameLine();
            CustomRadioButton(3, { "Corner Top Left##text_health", "Corner Top Right##text_health", "Corner Bottom Right##text_health" }, config.visualConfig.MiskHealthOffsetCorner);
            ImGui::SliderFloat2("Health Text Offset ##misk_offset_HealthText", config.visualConfig.MiskHealthTextOffset, MiskOffsetMin, MiskOffsetMax);
             
            //distance
            ImGui::Spacing();
            ImGui::Checkbox("Show Distance ##misk_show_Distance", &config.visualConfig.MiskShowDistance);
            ImGui::SameLine();
            CColorPicker(config.visualConfig.MiskDistanceColor, "##misk_colddor_Distance");
            ImGui::SameLine();
            CustomRadioButton(3, { "Corner Top Left##text_distance", "Corner Top Right##text_distance", "Corner Bottom Right##text_distance" }, config.visualConfig.MiskDistanceOffsetCorner);
            ImGui::SliderFloat2("Distance Offset ##misk_offset_Distance", config.visualConfig.MiskDistanceOffset, MiskOffsetMin, MiskOffsetMax);
            
            //weapon name
            ImGui::Spacing();
            ImGui::Checkbox("Show Weapon Name ##misk_show_name_Weapon", &config.visualConfig.MiskShowWeaponName); 
            ImGui::SameLine();
            CColorPicker(config.visualConfig.MiskWeaponNameColor, "##misk_color_nawdame_Weapon");
            ImGui::SameLine();
            CustomRadioButton(3, { "Corner Top Left##text_Weapon", "Corner Top Right##text_Weapon", "Corner Bottom Right##text_Weapon" }, config.visualConfig.MiskWeaponNameOffsetCorner);
            ImGui::SliderFloat2("Weapon Name Offset ##misk_offset_name_Weapon", config.visualConfig.MiskWeaponNameOffset, MiskOffsetMin, MiskOffsetMax);

            //traceline
            ImGui::Spacing();
            ImGui::Checkbox("Show TraceLine ##misk_show_trace_line", &config.visualConfig.MiskShowTraceLine);
            ImGui::SameLine();
            CColorPicker(config.visualConfig.MiskTraceLineColor, "##misk_show_trawdace_line");
            ImGui::Checkbox("TraceLine Draw End Point##misk_show_trace_line", &config.visualConfig.MiskTraceLineDrawEndPoint);
            ImGui::SameLine();
            CustomRadioButton(3, { "Up", "Center", "Bottom" }, config.visualConfig.MiskTraceLinePosition);
            ImGui::SliderFloat("TraceLine End Point Raidus ##misk_show_trace_line", &config.visualConfig.MiskTraceLineEndPointRadius, 0, 15);

            ImGui::EndTabItem();
        }


        ImGui::EndTabBar();
    }
}

void Menu::DrawMiskMenu()
{
    if (ImGui::BeginTabBar("MiscTabs ##misc_main")) {

        if (ImGui::BeginTabItem("Bhop ##Bhop")) {
            ImGui::Spacing();
            ImGui::Checkbox("Enable ##Bhop", &config.miscConfig.BHopEnable);
            ImGui::Checkbox("Default Jump ##Bhop", &config.miscConfig.BHopDefaultJumpEnable);

            ImGui::SliderInt("Delay ##Bhop", &config.miscConfig.BHopDelay, 5, 50);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Trigger ##Trigger")) {
            ImGui::Spacing();
            ImGui::Checkbox("Enable ##Trigger", &config.miscConfig.TriggerBot);
            ImGui::Checkbox("Friendly Fire##Trigger", &config.miscConfig.TriggerBotFriendlyFire);
            //ImGui::Checkbox("Flash Ignore ##Trigger", &config.miscConfig.TriggerBotFriendlyFire);

            ImGui::SliderInt("Delay ##Trigger", &config.miscConfig.TriggerDelay, 5, 50);

            ImGui::InputInt("KeyBind", &config.miscConfig.TriggerBotKey, 1);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Crosshair 2D ##Crosshair")) {
            ImGui::Spacing();
            ImGui::Checkbox("Enable ##Crosshair", &config.miscConfig.DrawCrosshaird2D);
            ImGui::SameLine();
            CColorPicker(config.miscConfig.CrossHair2DColor, "##CustomCrosshairCrossHair2DColor");
            ImGui::SliderFloat("Crosshaird 2D Size ##Crosshair", &config.miscConfig.CrossHair2DSize, 0, 20);
            

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Custom Crosshair ##Fuctions")) {
            ImGui::Spacing();
            ImGui::Checkbox("Enable ##CustomCrosshair", &config.dynamicCrosshairConfig.Enable);
            ImGui::SameLine();
            CColorPicker(config.dynamicCrosshairConfig.CrosshairColor, "##CustomCrosshair");
            ImGui::Spacing();



            ImGui::Checkbox("Draw Crossline ##CustomCrosshair", &config.dynamicCrosshairConfig.drawCrossline);
            ImGui::SameLine();
            ImGui::Checkbox("Draw Outline ##CustomCrosshair", &config.dynamicCrosshairConfig.drawOutLine);
            ImGui::SameLine();
            ImGui::Checkbox("Draw Dot ##CustomCrosshair", &config.dynamicCrosshairConfig.drawDot);
            ImGui::SameLine();
            ImGui::Checkbox("T Style ##CustomCrosshair", &config.dynamicCrosshairConfig.tStyle);
            ImGui::SameLine();
            ImGui::Checkbox("Draw Circle ##CustomCrosshair", &config.dynamicCrosshairConfig.drawCircle);

            ImGui::Spacing();

            ImGui::SliderInt("Gap ##CustomCrosshair", &config.dynamicCrosshairConfig.Gap, 0, 20);
            ImGui::Spacing();
            ImGui::SliderFloat("Horizontal Length ##CustomCrosshair", &config.dynamicCrosshairConfig.HorizontalLength, 0, 20);
            ImGui::SliderFloat("Vertical Length ##CustomCrosshair", &config.dynamicCrosshairConfig.VerticalLength, 0, 20);
            ImGui::SliderFloat("Circle Radius ##CustomCrosshair", &config.dynamicCrosshairConfig.CircleRadius, 0, 20);
            ImGui::SliderFloat("Thickness ##CustomCrosshair", &config.dynamicCrosshairConfig.Thickness, 0, 5);


             

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Radar ##Radar")) {
            ImGui::Spacing();

            ImGui::Checkbox("Enable ##Radar", &config.radarConfig.Enable);
            ImGui::SameLine();
            ImGui::Checkbox("Show Crossline ##Radar", &config.radarConfig.ShowCrossLine);
            ImGui::SameLine();
            CColorPicker(config.radarConfig.CrossLineColor, "##Radar");

            ImGui::Spacing();
            
            ImGui::SliderFloat2("Position ##Radar", config.radarConfig.Position, 10, 200);
            ImGui::Spacing();
            ImGui::SliderFloat("Proportion ##Radar", &config.radarConfig.Proportion, 100, 9000);
            ImGui::SliderFloat("Circle Size ##Radar", &config.radarConfig.CircleSize, 1, 10);
            ImGui::SliderFloat("Render Range ##Radar", &config.radarConfig.RenderRange, 10, 500);
            ImGui::SliderFloat("Width ##Radar", &config.radarConfig.Width, 30, 500);


            ImGui::EndTabItem();
        }

        

        ImGui::EndTabBar();
    }

}

void Menu::DrawConfigMenu()
{
    ImGui::BeginChild("##ConfigTabs", ImVec2(460, 0));

    int count = config.config_name_list.size();
    if (count != 0) {
        for (int i = 0; i < count; i++)
        {
            if (ImGui::Selectable(config.config_name_list[i].c_str(), config.selected == i)) config.selected = i;
            ImGui::Spacing();
        }
    }




    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("ConfigTabsBtns", ImVec2(80, 0), false);

    if (ImGui::Button("Get List")) config.LoadList();
    if (ImGui::Button("Load")) config.LoadSelected();
    if (ImGui::Button("Save")) config.SaveSelected(config.config_name_list[config.selected]);

    ImGui::Spacing();

    if (ImGui::Button("Delete")) config.DeleteSelected();

    ImGui::Spacing();

    ImGui::SetNextItemWidth(150);
    ImGui::InputText("##cfgname", config.str_buffer, config.MAX_PATH_SIZE);

    if (ImGui::Button("New")) {
        config.New();
    }

    ImGui::EndChild();
}

void Menu::SetStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(15, 15);
    style.WindowRounding = 5.0f;
    style.FramePadding = ImVec2(5, 2);
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(8, 8);
    style.ItemInnerSpacing = ImVec2(4, 6);
    style.IndentSpacing = 30.0f;//20
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 16.0f;
    style.GrabMinSize = 20.0f;
    style.GrabRounding = 5.0f;
    style.ChildRounding = 10.f;
    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 5.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.CellPadding = ImVec2(4.0f, 2.0f);
    style.ColumnsMinSpacing = 6.0f;
    style.TabRounding = 4.0f;
    style.TabBorderSize = 1.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
    style.ColorButtonPosition = ImGuiDir_Left;//old ImGuiDir_Right



    style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TabSelected] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TabDimmed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style.Colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_TextLink] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.80f, 0.80f, 0.83f, 1.f);
}
