#include "Config.h"
#include <Json/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

using json = nlohmann::json;

Config::Config()
{
    std::memset(str_buffer, 0, MAX_PATH_SIZE);
}

void Config::LoadList()
{
    config_name_list.clear();

    auto programDirectory = std::filesystem::current_path();

    try {
        for (const auto& entry : std::filesystem::directory_iterator(programDirectory)) {
            if (entry.is_regular_file() && entry.path().extension() == Config::configFormat) {
                config_name_list.push_back(entry.path().stem().string());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }


    std::cout << "[Config]: Config list Update!" << std::endl;
}

void Config::LoadSelected()
{
    if (config_name_list.size() <= 0) return;

    auto name = std::string(config_name_list[selected]);

    if (name.empty()) {
        std::cout << "[Config]: Config name invalid!" << std::endl;
        return;
    }
    name += configFormat;
    json data;
    std::ifstream inFile(name);


    if (inFile.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "[Config]: File is empty: " << name << std::endl;
        inFile.close();
        return;
    }

    if (inFile.is_open()) {
        inFile >> data;
        inFile.close();
    }
    else {
        std::cout << "[Config]: Config not loading." << std::endl;
        return;
    }
    
    {
        dynamicCrosshairConfig.Enable = data["DynamicCrosshair::Enable"].get<bool>();
        dynamicCrosshairConfig.drawCrossline = data["DynamicCrosshair::drawCrossline"].get<bool>();
        dynamicCrosshairConfig.Gap = data["DynamicCrosshair::Gap"].get<int>();
        dynamicCrosshairConfig.drawOutLine = data["DynamicCrosshair::drawOutLine"].get<bool>();
        dynamicCrosshairConfig.drawDot = data["DynamicCrosshair::drawDot"].get<bool>();
        dynamicCrosshairConfig.tStyle = data["DynamicCrosshair::tStyle"].get<bool>();
        dynamicCrosshairConfig.drawCircle = data["DynamicCrosshair::drawCircle"].get<bool>();
        dynamicCrosshairConfig.HorizontalLength = data["DynamicCrosshair::HorizontalLength"].get<float>();
        dynamicCrosshairConfig.CircleRadius = data["DynamicCrosshair::CircleRadius"].get<float>();
        dynamicCrosshairConfig.Thickness = data["DynamicCrosshair::Thickness"].get<float>();
        dynamicCrosshairConfig.BorderWidth = data["DynamicCrosshair::BorderWidth"].get<int>();
        dynamicCrosshairConfig.DotSize = data["DynamicCrosshair::DotSize"].get<float>();
        dynamicCrosshairConfig.CrosshairColor[0] = data["DynamicCrosshair::CrosshairColor"][0].get<float>();
        dynamicCrosshairConfig.CrosshairColor[1] = data["DynamicCrosshair::CrosshairColor"][1].get<float>();
        dynamicCrosshairConfig.CrosshairColor[2] = data["DynamicCrosshair::CrosshairColor"][2].get<float>();
        dynamicCrosshairConfig.CrosshairColor[3] = data["DynamicCrosshair::CrosshairColor"][3].get<float>();
    }

    {
        radarConfig.Enable = data["DynamicCrosshair::Enable"].get<bool>();
        radarConfig.ShowCrossLine = data["DynamicCrosshair::ShowCrossLine"].get<bool>();
        radarConfig.Proportion = data["DynamicCrosshair::Proportion"].get<float>();
        radarConfig.CircleSize = data["DynamicCrosshair::CircleSize"].get<float>();
        radarConfig.RenderRange = data["DynamicCrosshair::RenderRange"].get<float>();
        radarConfig.Width = data["DynamicCrosshair::Width"].get<float>();
        radarConfig.CrossLineColor[0] = data["Radar::CrossLineColor"][0].get<float>();
        radarConfig.CrossLineColor[1] = data["Radar::CrossLineColor"][1].get<float>();
        radarConfig.CrossLineColor[2] = data["Radar::CrossLineColor"][2].get<float>();
        radarConfig.CrossLineColor[3] = data["Radar::CrossLineColor"][3].get<float>();
        radarConfig.Position[0] = data["Radar::Position"][0].get<float>();
        radarConfig.Position[1] = data["Radar::Position"][1].get<float>();

    }

    {
        miscConfig.DrawCrosshaird2D = data["Misc::DrawCrosshaird2D"].get<bool>();
        miscConfig.CrossHair2DSize = data["Misc::CrossHair2DSize"].get<float>();

        miscConfig.CrossHair2DColor[0] = data["Misc::CrossHair2DColor"][0].get<float>();
        miscConfig.CrossHair2DColor[1] = data["Misc::CrossHair2DColor"][1].get<float>();
        miscConfig.CrossHair2DColor[2] = data["Misc::CrossHair2DColor"][2].get<float>();
        miscConfig.CrossHair2DColor[3] = data["Misc::CrossHair2DColor"][3].get<float>();

        miscConfig.BHopEnable = data["Misc::BHopEnable"].get<bool>();
        miscConfig.BHopDefaultJumpEnable = data["Misc::BHopDefaultJumpEnable"].get<bool>();
        miscConfig.BHopDelay = data["Misc::BHopDelay"].get<int>();

        miscConfig.TriggerBot = data["Misc::TriggerBot"].get<bool>();
        miscConfig.TriggerBotFriendlyFire = data["Misc::TriggerBotFriendlyFire"].get<bool>();
        miscConfig.TriggerBotFlashIgnore = data["Misc::TriggerBotFlashIgnore"].get<bool>();
        miscConfig.TriggerBotKey = data["Misc::TriggerBotKey"].get<int>();
        miscConfig.TriggerDelay = data["Misc::TriggerDelay"].get<int>();
    }



    {
        visualConfig.Enable = data["Visual::Enable"].get<bool>();
        visualConfig.EnemyOnly = data["Visual::EnemyOnly"].get<bool>();
        visualConfig.VisibleOnly = data["Visual::VisibleOnly"].get<bool>();
        visualConfig.NoVisibleOnly = data["Visual::NoVisibleOnly"].get<bool>();
        visualConfig.SpecOnly = data["Visual::SpecOnly"].get<bool>();

        visualConfig.RenderTextMaxDistance = data["Visual::RenderTextMaxDistance"].get<int>();

        visualConfig.Box2DEnable = data["Visual::Box2DEnable"].get<bool>();
        visualConfig.Box2DFilled = data["Visual::Box2DFilled"].get<bool>();
        visualConfig.Box2DType = data["Visual::Box2DType"].get<int>();

        visualConfig.Box2DFilledBGColor[0] = data["Visual::Box2DFilledBGColor"][0].get<float>();
        visualConfig.Box2DFilledBGColor[1] = data["Visual::Box2DFilledBGColor"][1].get<float>();
        visualConfig.Box2DFilledBGColor[2] = data["Visual::Box2DFilledBGColor"][2].get<float>();
        visualConfig.Box2DFilledBGColor[3] = data["Visual::Box2DFilledBGColor"][3].get<float>();

        visualConfig.Box2DEnemyColor[0] = data["Visual::Box2DEnemyColor"][0].get<float>();
        visualConfig.Box2DEnemyColor[1] = data["Visual::Box2DEnemyColor"][1].get<float>();
        visualConfig.Box2DEnemyColor[2] = data["Visual::Box2DEnemyColor"][2].get<float>();
        visualConfig.Box2DEnemyColor[3] = data["Visual::Box2DEnemyColor"][3].get<float>();

        visualConfig.Box2DEnemyNoVisibleColor[0] = data["Visual::Box2DEnemyNoVisibleColor"][0].get<float>();
        visualConfig.Box2DEnemyNoVisibleColor[1] = data["Visual::Box2DEnemyNoVisibleColor"][1].get<float>();
        visualConfig.Box2DEnemyNoVisibleColor[2] = data["Visual::Box2DEnemyNoVisibleColor"][2].get<float>();
        visualConfig.Box2DEnemyNoVisibleColor[3] = data["Visual::Box2DEnemyNoVisibleColor"][3].get<float>();

        visualConfig.Box2DFriendColor[0] = data["Visual::Box2DFriendColor"][0].get<float>();
        visualConfig.Box2DFriendColor[1] = data["Visual::Box2DFriendColor"][1].get<float>();
        visualConfig.Box2DFriendColor[2] = data["Visual::Box2DFriendColor"][2].get<float>();
        visualConfig.Box2DFriendColor[3] = data["Visual::Box2DFriendColor"][3].get<float>();

        visualConfig.Box2DFriendNoVisibleColor[0] = data["Visual::Box2DFriendNoVisibleColor"][0].get<float>();
        visualConfig.Box2DFriendNoVisibleColor[1] = data["Visual::Box2DFriendNoVisibleColor"][1].get<float>();
        visualConfig.Box2DFriendNoVisibleColor[2] = data["Visual::Box2DFriendNoVisibleColor"][2].get<float>();
        visualConfig.Box2DFriendNoVisibleColor[3] = data["Visual::Box2DFriendNoVisibleColor"][3].get<float>();

        visualConfig.Box2DThinkness = data["Visual::Box2DThinkness"].get<float>();
        visualConfig.Box2DRounded = data["Visual::Box2DRounded"].get<float>();
    }



    {
        visualConfig.Box3DEnable = data["Visual::Box3DEnable"].get<bool>();
        visualConfig.Box3DEnableAnimation = data["Visual::Box3DEnableAnimation"].get<bool>();

        visualConfig.Box3DEnemyColor[0] = data["Visual::Box3DEnemyColor"][0].get<float>();
        visualConfig.Box3DEnemyColor[1] = data["Visual::Box3DEnemyColor"][1].get<float>();
        visualConfig.Box3DEnemyColor[2] = data["Visual::Box3DEnemyColor"][2].get<float>();
        visualConfig.Box3DEnemyColor[3] = data["Visual::Box3DEnemyColor"][3].get<float>();

        visualConfig.Box3DEnemyNoVisibleColor[0] = data["Visual::Box3DEnemyNoVisibleColor"][0].get<float>();
        visualConfig.Box3DEnemyNoVisibleColor[1] = data["Visual::Box3DEnemyNoVisibleColor"][1].get<float>();
        visualConfig.Box3DEnemyNoVisibleColor[2] = data["Visual::Box3DEnemyNoVisibleColor"][2].get<float>();
        visualConfig.Box3DEnemyNoVisibleColor[3] = data["Visual::Box3DEnemyNoVisibleColor"][3].get<float>();

        visualConfig.Box3DFriendColor[0] = data["Visual::Box3DFriendColor"][0].get<float>();
        visualConfig.Box3DFriendColor[1] = data["Visual::Box3DFriendColor"][1].get<float>();
        visualConfig.Box3DFriendColor[2] = data["Visual::Box3DFriendColor"][2].get<float>();
        visualConfig.Box3DFriendColor[3] = data["Visual::Box3DFriendColor"][3].get<float>();

        visualConfig.Box3DFriendNoVisibleColor[0] = data["Visual::Box3DFriendNoVisibleColor"][0].get<float>();
        visualConfig.Box3DFriendNoVisibleColor[1] = data["Visual::Box3DFriendNoVisibleColor"][1].get<float>();
        visualConfig.Box3DFriendNoVisibleColor[2] = data["Visual::Box3DFriendNoVisibleColor"][2].get<float>();
        visualConfig.Box3DFriendNoVisibleColor[3] = data["Visual::Box3DFriendNoVisibleColor"][3].get<float>();
    }



    {
        visualConfig.Box3DThinkness = data["Visual::Box3DThinkness"].get<float>();

        visualConfig.SkeletonEnable = data["Visual::SkeletonEnable"].get<bool>();
        visualConfig.SkeletonDrawConnectPoint = data["Visual::SkeletonDrawConnectPoint"].get<bool>();
        visualConfig.SkeletonShowPenis = data["Visual::SkeletonShowPenis"].get<bool>();
        visualConfig.DrawEnemyHeadCircle = data["Visual::DrawEnemyHeadCircle"].get<bool>();

        visualConfig.SkeletonEnemyColor[0] = data["Visual::SkeletonEnemyColor"][0].get<float>();
        visualConfig.SkeletonEnemyColor[1] = data["Visual::SkeletonEnemyColor"][1].get<float>();
        visualConfig.SkeletonEnemyColor[2] = data["Visual::SkeletonEnemyColor"][2].get<float>();
        visualConfig.SkeletonEnemyColor[3] = data["Visual::SkeletonEnemyColor"][3].get<float>();

        visualConfig.SkeletonEnemyNoVisibleColor[0] = data["Visual::SkeletonEnemyNoVisibleColor"][0].get<float>();
        visualConfig.SkeletonEnemyNoVisibleColor[1] = data["Visual::SkeletonEnemyNoVisibleColor"][1].get<float>();
        visualConfig.SkeletonEnemyNoVisibleColor[2] = data["Visual::SkeletonEnemyNoVisibleColor"][2].get<float>();
        visualConfig.SkeletonEnemyNoVisibleColor[3] = data["Visual::SkeletonEnemyNoVisibleColor"][3].get<float>();

        visualConfig.SkeletonFriendColor[0] = data["Visual::SkeletonFriendColor"][0].get<float>();
        visualConfig.SkeletonFriendColor[1] = data["Visual::SkeletonFriendColor"][1].get<float>();
        visualConfig.SkeletonFriendColor[2] = data["Visual::SkeletonFriendColor"][2].get<float>();
        visualConfig.SkeletonFriendColor[3] = data["Visual::SkeletonFriendColor"][3].get<float>();

        visualConfig.SkeletonFriendNoVisibleColor[0] = data["Visual::SkeletonFriendNoVisibleColor"][0].get<float>();
        visualConfig.SkeletonFriendNoVisibleColor[1] = data["Visual::SkeletonFriendNoVisibleColor"][1].get<float>();
        visualConfig.SkeletonFriendNoVisibleColor[2] = data["Visual::SkeletonFriendNoVisibleColor"][2].get<float>();
        visualConfig.SkeletonFriendNoVisibleColor[3] = data["Visual::SkeletonFriendNoVisibleColor"][3].get<float>();

        visualConfig.SkeletonPenisColor[0] = data["Visual::SkeletonPenisColor"][0].get<float>();
        visualConfig.SkeletonPenisColor[1] = data["Visual::SkeletonPenisColor"][1].get<float>();
        visualConfig.SkeletonPenisColor[2] = data["Visual::SkeletonPenisColor"][2].get<float>();
        visualConfig.SkeletonPenisColor[3] = data["Visual::SkeletonPenisColor"][3].get<float>();

        visualConfig.SkeletonThinkness = data["Visual::SkeletonThinkness"].get<float>();
        visualConfig.SkeletonConnectPointRadius = data["Visual::SkeletonConnectPointRadius"].get<float>();
        visualConfig.SkeletonPenisLength = data["Visual::SkeletonPenisLength"].get<float>();
        visualConfig.SkeletonPenisThinkness = data["Visual::SkeletonPenisThinkness"].get<float>();
    }

    
    {
    visualConfig.MiskShowName = data["Visual::MiskShowName"].get<bool>();

    visualConfig.MiskNameOffset[0] = data["Visual::MiskNameOffset"][0].get<float>();
    visualConfig.MiskNameOffset[1] = data["Visual::MiskNameOffset"][1].get<float>();

    visualConfig.MiskNameColor[0] = data["Visual::MiskNameColor"][0].get<float>();
    visualConfig.MiskNameColor[1] = data["Visual::MiskNameColor"][1].get<float>();
    visualConfig.MiskNameColor[2] = data["Visual::MiskNameColor"][2].get<float>();
    visualConfig.MiskNameColor[3] = data["Visual::MiskNameColor"][3].get<float>();

    visualConfig.MiskNameOffsetCorner = data["Visual::MiskNameOffsetCorner"].get<int>();

    visualConfig.MiskShowHealthText = data["Visual::MiskShowHealthText"].get<bool>();

    visualConfig.MiskHealthTextOffset[0] = data["Visual::MiskHealthTextOffset"][0].get<float>();
    visualConfig.MiskHealthTextOffset[1] = data["Visual::MiskHealthTextOffset"][1].get<float>();

    visualConfig.MiskHealthTextColor[0] = data["Visual::MiskHealthTextColor"][0].get<float>();
    visualConfig.MiskHealthTextColor[1] = data["Visual::MiskHealthTextColor"][1].get<float>();
    visualConfig.MiskHealthTextColor[2] = data["Visual::MiskHealthTextColor"][2].get<float>();
    visualConfig.MiskHealthTextColor[3] = data["Visual::MiskHealthTextColor"][3].get<float>();
    visualConfig.MiskHealthOffsetCorner = data["Visual::MiskHealthOffsetCorner"].get<float>();

    visualConfig.MiskShowDistance = data["Visual::MiskShowDistance"].get<bool>();
    visualConfig.MiskDistanceOffset[0] = data["Visual::MiskDistanceOffset"][0].get<float>();
    visualConfig.MiskDistanceOffset[1] = data["Visual::MiskDistanceOffset"][1].get<float>();

    }

    {
    visualConfig.MiskDistanceColor[0] = data["Visual::MiskDistanceColor"][0].get<float>();
    visualConfig.MiskDistanceColor[1] = data["Visual::MiskDistanceColor"][1].get<float>();
    visualConfig.MiskDistanceColor[2] = data["Visual::MiskDistanceColor"][2].get<float>();
    visualConfig.MiskDistanceColor[3] = data["Visual::MiskDistanceColor"][3].get<float>();

    visualConfig.MiskDistanceOffsetCorner = data["Visual::MiskDistanceOffsetCorner"].get<float>();

    visualConfig.MiskShowWeaponName = data["Visual::MiskShowWeaponName"].get<bool>();

    visualConfig.MiskWeaponNameOffset[0] = data["Visual::MiskWeaponNameOffset"][0].get<float>();
    visualConfig.MiskWeaponNameOffset[1] = data["Visual::MiskWeaponNameOffset"][1].get<float>();

    visualConfig.MiskWeaponNameColor[0] = data["Visual::MiskWeaponNameColor"][0].get<float>();
    visualConfig.MiskWeaponNameColor[1] = data["Visual::MiskWeaponNameColor"][1].get<float>();
    visualConfig.MiskWeaponNameColor[2] = data["Visual::MiskWeaponNameColor"][2].get<float>();
    visualConfig.MiskWeaponNameColor[3] = data["Visual::MiskWeaponNameColor"][3].get<float>();
    visualConfig.MiskWeaponNameOffsetCorner = data["Visual::MiskWeaponNameOffsetCorner"].get<float>();

    visualConfig.MiskShowTraceLine = data["Visual::MiskShowTraceLine"].get<bool>();
    visualConfig.MiskTraceLineDrawEndPoint = data["Visual::MiskTraceLineDrawEndPoint"].get<bool>();
    visualConfig.MiskTraceLinePosition = data["Visual::MiskTraceLinePosition"].get<int>();
    visualConfig.MiskTraceLineEndPointRadius = data["Visual::MiskTraceLineEndPointRadius"].get<float>();
    }

    {

    visualConfig.MiskTraceLineColor[0] = data["Visual::MiskTraceLineColor"][0].get<float>();
    visualConfig.MiskTraceLineColor[1] = data["Visual::MiskTraceLineColor"][1].get<float>();
    visualConfig.MiskTraceLineColor[2] = data["Visual::MiskTraceLineColor"][2].get<float>();
    visualConfig.MiskTraceLineColor[3] = data["Visual::MiskTraceLineColor"][3].get<float>();
    visualConfig.MiskTraceLineThinkness = data["Visual::MiskTraceLineThinkness"].get<float>();

    visualConfig.MiskShowHealthBar = data["Visual::MiskShowHealthBar"].get<bool>();
    visualConfig.MiskHealthBarOffset = data["Visual::MiskHealthBarOffset"].get<float>();
    visualConfig.MiskHealthBarWidth = data["Visual::MiskHealthBarWidth"].get<float>();

    visualConfig.MiskShowEdgeHealthBar = data["Visual::MiskShowEdgeHealthBar"].get<bool>();
    visualConfig.MiskEdgeHealthBarOffset = data["Visual::MiskEdgeHealthBarOffset"].get<float>();
    visualConfig.MiskEdgeHealthBarWidth = data["Visual::MiskEdgeHealthBarWidth"].get<float>();
    }

    std::cout << "[Config]: " << config_name_list[selected] << " Config loading" << std::endl;
}

void Config::SaveSelected(std::string cfg_name)
{
    if (config_name_list.size() <= 0) return;

    auto name = std::string(cfg_name);

    if (name.empty()) {
        std::cout << "[Config]: Config name invalid!" << std::endl;
        return;
    }

    name += configFormat;
    json data;


    {
        data["DynamicCrosshair::Enable"] = dynamicCrosshairConfig.Enable;
        data["DynamicCrosshair::drawCrossline"] = dynamicCrosshairConfig.drawCrossline;
        data["DynamicCrosshair::Gap"] = dynamicCrosshairConfig.Gap;
        data["DynamicCrosshair::drawOutLine"] = dynamicCrosshairConfig.drawOutLine;
        data["DynamicCrosshair::drawDot"] = dynamicCrosshairConfig.drawDot;
        data["DynamicCrosshair::tStyle"] = dynamicCrosshairConfig.tStyle;
        data["DynamicCrosshair::drawCircle"] = dynamicCrosshairConfig.drawCircle;
        data["DynamicCrosshair::HorizontalLength"] = dynamicCrosshairConfig.HorizontalLength;
        data["DynamicCrosshair::CircleRadius"] = dynamicCrosshairConfig.CircleRadius;
        data["DynamicCrosshair::Thickness"] = dynamicCrosshairConfig.Thickness;
        data["DynamicCrosshair::BorderWidth"] = dynamicCrosshairConfig.BorderWidth;
        data["DynamicCrosshair::DotSize"] = dynamicCrosshairConfig.DotSize;
        data["DynamicCrosshair::CrosshairColor"] = { dynamicCrosshairConfig.CrosshairColor[0], dynamicCrosshairConfig.CrosshairColor[1], dynamicCrosshairConfig.CrosshairColor[2], dynamicCrosshairConfig.CrosshairColor[3] };
    }

    {
        data["DynamicCrosshair::Enable"] = radarConfig.Enable;
        data["DynamicCrosshair::ShowCrossLine"] = radarConfig.ShowCrossLine;
        data["DynamicCrosshair::Proportion"] = radarConfig.Proportion;
        data["DynamicCrosshair::CircleSize"] = radarConfig.CircleSize;
        data["DynamicCrosshair::RenderRange"] = radarConfig.RenderRange;
        data["DynamicCrosshair::Width"] = radarConfig.Width;
        data["Radar::CrossLineColor"] = { radarConfig.CrossLineColor[0], radarConfig.CrossLineColor[1], radarConfig.CrossLineColor[2], radarConfig.CrossLineColor[3] };
        data["Radar::Position"] = { radarConfig.Position[0], radarConfig.Position[1] };
    }

    {
        data["Misc::DrawCrosshaird2D"] = miscConfig.DrawCrosshaird2D;
        data["Misc::CrossHair2DSize"] = miscConfig.CrossHair2DSize;

        data["Misc::CrossHair2DColor"] = { miscConfig.CrossHair2DColor[0], miscConfig.CrossHair2DColor[1], miscConfig.CrossHair2DColor[2], miscConfig.CrossHair2DColor[3] };

        data["Misc::BHopEnable"] = miscConfig.BHopEnable;
        data["Misc::BHopDefaultJumpEnable"] = miscConfig.BHopDefaultJumpEnable;
        data["Misc::BHopDelay"] = miscConfig.BHopDelay;

        data["Misc::TriggerBot"] = miscConfig.TriggerBot;
        data["Misc::TriggerBotFriendlyFire"] = miscConfig.TriggerBotFriendlyFire;
        data["Misc::TriggerBotFlashIgnore"] = miscConfig.TriggerBotFlashIgnore;
        data["Misc::TriggerBotKey"] = miscConfig.TriggerBotKey;
        data["Misc::TriggerDelay"] = miscConfig.TriggerDelay;

    }

    {
        data["Visual::Enable"] = visualConfig.Enable;
        data["Visual::EnemyOnly"] = visualConfig.EnemyOnly;
        data["Visual::VisibleOnly"] = visualConfig.VisibleOnly;
        data["Visual::NoVisibleOnly"] = visualConfig.NoVisibleOnly;
        data["Visual::SpecOnly"] = visualConfig.SpecOnly;
        data["Visual::RenderTextMaxDistance"] = visualConfig.RenderTextMaxDistance;



        data["Visual::Box2DEnable"] = visualConfig.Box2DEnable;
        data["Visual::Box2DFilled"] = visualConfig.Box2DFilled;
        data["Visual::Box2DType"] = visualConfig.Box2DType;
        data["Visual::Box2DFilledBGColor"] = { visualConfig.Box2DFilledBGColor[0], visualConfig.Box2DFilledBGColor[1], visualConfig.Box2DFilledBGColor[2], visualConfig.Box2DFilledBGColor[3] };
        data["Visual::Box2DEnemyColor"] = { visualConfig.Box2DEnemyColor[0], visualConfig.Box2DEnemyColor[1], visualConfig.Box2DEnemyColor[2], visualConfig.Box2DEnemyColor[3] };
        data["Visual::Box2DEnemyNoVisibleColor"] = { visualConfig.Box2DEnemyNoVisibleColor[0], visualConfig.Box2DEnemyNoVisibleColor[1], visualConfig.Box2DEnemyNoVisibleColor[2], visualConfig.Box2DEnemyNoVisibleColor[3] };
        data["Visual::Box2DFriendColor"] = { visualConfig.Box2DFriendColor[0], visualConfig.Box2DFriendColor[1], visualConfig.Box2DFriendColor[2], visualConfig.Box2DFriendColor[3] };
        data["Visual::Box2DFriendNoVisibleColor"] = { visualConfig.Box2DFriendNoVisibleColor[0], visualConfig.Box2DFriendNoVisibleColor[1], visualConfig.Box2DFriendNoVisibleColor[2], visualConfig.Box2DFriendNoVisibleColor[3] };
        data["Visual::Box2DThinkness"] = visualConfig.Box2DThinkness;
        data["Visual::Box2DRounded"] = visualConfig.Box2DRounded;

        data["Visual::Box3DEnable"] = visualConfig.Box3DEnable;
        data["Visual::Box3DEnableAnimation"] = visualConfig.Box3DEnableAnimation;
        data["Visual::Box3DEnemyColor"] = { visualConfig.Box3DEnemyColor[0], visualConfig.Box3DEnemyColor[1], visualConfig.Box3DEnemyColor[2], visualConfig.Box3DEnemyColor[3] };
        data["Visual::Box3DEnemyNoVisibleColor"] = { visualConfig.Box3DEnemyNoVisibleColor[0], visualConfig.Box3DEnemyNoVisibleColor[1], visualConfig.Box3DEnemyNoVisibleColor[2], visualConfig.Box3DEnemyNoVisibleColor[3] };
        data["Visual::Box3DFriendColor"] = { visualConfig.Box3DFriendColor[0], visualConfig.Box3DFriendColor[1], visualConfig.Box3DFriendColor[2], visualConfig.Box3DFriendColor[3] };
        data["Visual::Box3DFriendNoVisibleColor"] = { visualConfig.Box3DFriendNoVisibleColor[0], visualConfig.Box3DFriendNoVisibleColor[1], visualConfig.Box3DFriendNoVisibleColor[2], visualConfig.Box3DFriendNoVisibleColor[3] };
        data["Visual::Box3DThinkness"] = visualConfig.Box3DThinkness;

        data["Visual::SkeletonEnable"] = visualConfig.SkeletonEnable;
        data["Visual::SkeletonDrawConnectPoint"] = visualConfig.SkeletonDrawConnectPoint;
        data["Visual::SkeletonShowPenis"] = visualConfig.SkeletonShowPenis;
        data["Visual::DrawEnemyHeadCircle"] = visualConfig.DrawEnemyHeadCircle;
        data["Visual::SkeletonEnemyColor"] = { visualConfig.SkeletonEnemyColor[0], visualConfig.SkeletonEnemyColor[1], visualConfig.SkeletonEnemyColor[2], visualConfig.SkeletonEnemyColor[3] };
        data["Visual::SkeletonEnemyNoVisibleColor"] = { visualConfig.SkeletonEnemyNoVisibleColor[0], visualConfig.SkeletonEnemyNoVisibleColor[1], visualConfig.SkeletonEnemyNoVisibleColor[2], visualConfig.SkeletonEnemyNoVisibleColor[3] };
        data["Visual::SkeletonFriendColor"] = { visualConfig.SkeletonFriendColor[0], visualConfig.SkeletonFriendColor[1], visualConfig.SkeletonFriendColor[2], visualConfig.SkeletonFriendColor[3] };
        data["Visual::SkeletonFriendNoVisibleColor"] = { visualConfig.SkeletonFriendNoVisibleColor[0], visualConfig.SkeletonFriendNoVisibleColor[1], visualConfig.SkeletonFriendNoVisibleColor[2], visualConfig.SkeletonFriendNoVisibleColor[3] };
        data["Visual::SkeletonThinkness"] = visualConfig.SkeletonThinkness;
        data["Visual::SkeletonConnectPointRadius"] = visualConfig.SkeletonConnectPointRadius;
        data["Visual::SkeletonPenisLength"] = visualConfig.SkeletonPenisLength;
        data["Visual::SkeletonPenisThinkness"] = visualConfig.SkeletonPenisThinkness;
        data["Visual::SkeletonPenisColor"] = { visualConfig.SkeletonPenisColor[0], visualConfig.SkeletonPenisColor[1], visualConfig.SkeletonPenisColor[2], visualConfig.SkeletonPenisColor[3] };

        data["Visual::MiskShowName"] = visualConfig.MiskShowName;
        data["Visual::MiskNameOffset"] = { visualConfig.MiskNameOffset[0], visualConfig.MiskNameOffset[1] };
        data["Visual::MiskNameColor"] = { visualConfig.MiskNameColor[0], visualConfig.MiskNameColor[1], visualConfig.MiskNameColor[2], visualConfig.MiskNameColor[3] };
        data["Visual::MiskNameOffsetCorner"] = visualConfig.MiskNameOffsetCorner;

        data["Visual::MiskShowHealthText"] = visualConfig.MiskShowHealthText;
        data["Visual::MiskHealthTextOffset"] = { visualConfig.MiskHealthTextOffset[0], visualConfig.MiskHealthTextOffset[1] };
        data["Visual::MiskHealthTextColor"] = { visualConfig.MiskHealthTextColor[0], visualConfig.MiskHealthTextColor[1], visualConfig.MiskHealthTextColor[2], visualConfig.MiskHealthTextColor[3] };
        data["Visual::MiskHealthOffsetCorner"] = visualConfig.MiskHealthOffsetCorner;

        data["Visual::MiskShowDistance"] = visualConfig.MiskShowDistance;
        data["Visual::MiskDistanceOffset"] = { visualConfig.MiskDistanceOffset[0], visualConfig.MiskDistanceOffset[1] };
        data["Visual::MiskDistanceColor"] = { visualConfig.MiskDistanceColor[0], visualConfig.MiskDistanceColor[1], visualConfig.MiskDistanceColor[2], visualConfig.MiskDistanceColor[3] };
        data["Visual::MiskDistanceOffsetCorner"] = visualConfig.MiskDistanceOffsetCorner;

        data["Visual::MiskShowWeaponName"] = visualConfig.MiskShowWeaponName;
        data["Visual::MiskWeaponNameOffset"] = { visualConfig.MiskWeaponNameOffset[0], visualConfig.MiskWeaponNameOffset[1] };
        data["Visual::MiskWeaponNameColor"] = { visualConfig.MiskWeaponNameColor[0], visualConfig.MiskWeaponNameColor[1], visualConfig.MiskWeaponNameColor[2], visualConfig.MiskWeaponNameColor[3] };
        data["Visual::MiskWeaponNameOffsetCorner"] = visualConfig.MiskWeaponNameOffsetCorner;

        data["Visual::MiskShowTraceLine"] = visualConfig.MiskShowTraceLine;
        data["Visual::MiskTraceLineDrawEndPoint"] = visualConfig.MiskTraceLineDrawEndPoint;
        data["Visual::MiskTraceLinePosition"] = visualConfig.MiskTraceLinePosition;
        data["Visual::MiskTraceLineEndPointRadius"] = visualConfig.MiskTraceLineEndPointRadius;
        data["Visual::MiskTraceLineColor"] = { visualConfig.MiskTraceLineColor[0], visualConfig.MiskTraceLineColor[1], visualConfig.MiskTraceLineColor[2], visualConfig.MiskTraceLineColor[3] };
        data["Visual::MiskTraceLineThinkness"] = visualConfig.MiskTraceLineThinkness;

        data["Visual::MiskShowHealthBar"] = visualConfig.MiskShowHealthBar;
        data["Visual::MiskHealthBarOffset"] = visualConfig.MiskHealthBarOffset;
        data["Visual::MiskHealthBarWidth"] = visualConfig.MiskHealthBarWidth;

        data["Visual::MiskShowEdgeHealthBar"] = visualConfig.MiskShowEdgeHealthBar;
        data["Visual::MiskEdgeHealthBarOffset"] = visualConfig.MiskEdgeHealthBarOffset;
        data["Visual::MiskEdgeHealthBarWidth"] = visualConfig.MiskEdgeHealthBarWidth;
    }



    std::ofstream file(name);
    if (file.is_open()) {
        file << data.dump(4);
        file.close();

        std::cout << "[Config]: " << cfg_name << " config saved." << std::endl;
    }
}

void Config::New()
{
    auto filename = std::string(str_buffer);

    if (filename.empty()) {
        std::cout << "[Config]: Name is empty!" << std::endl;
        return;
    }


    filename += configFormat;

    std::memset(str_buffer, 0, MAX_PATH_SIZE);

    if (std::filesystem::exists(filename)) {
        std::cout << "[Config]: The file " << filename << " already exists." << std::endl;
    }
    else {
        std::ofstream file(filename, std::ios::out);
        if (!file) {
            std::cerr << "[Config]: Failed to create the file " << filename << std::endl;
            return;
        }
        std::cout << "[Config]:The file " << filename << " has been created successfully." << std::endl;
    }


    LoadList();
}

void Config::DeleteSelected()
{
    auto filename = std::string(config_name_list[selected] + configFormat);


    try {
        if (std::filesystem::remove(filename)) {
            std::cout << "[Config]: The file " << filename << " has been deleted successfully." << std::endl;
        }
        else {
            std::cout << "[Config]: The file " << filename << " does not exist." << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[Config]: " << e.what() << std::endl;
    }
    LoadList();
}

void Config::UpdateConfig()
{
    SaveSelected(config_name_list[selected]);
    LoadSelected();
}
