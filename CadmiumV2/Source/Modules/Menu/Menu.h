#pragma once
#include "../../SDK/SDK.h"
#include "../Config/Config.h"

enum MenuTabItem
{
	Visuals,
	Misk,
	ConfigItem,
	Unload
};


class Menu
{
private:
	const float MenuWidth = 800;
	const float MenuHeight = 610;
	const int MenuFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
	const ImGuiColorEditFlags ColorEditorFlags = ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_Float;//ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview

	MenuTabItem menu_tabs_item = MenuTabItem::Visuals;

	ImFont* font10;
	ImFont* font12;
	ImFont* font14;
	ImFont* font18;

	int cfg_index = 0;

	Config& config;

private:

public:

public:
	Menu(Overlay& overlay, Config& cfg);
	~Menu();


	void Draw();


	void DrawVisualsMenu();
	void DrawMiskMenu();
	void DrawConfigMenu();

	void SetStyle();

};



