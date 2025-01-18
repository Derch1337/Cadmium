#include "SDK/SDK.h"

#include "Modules/Config/Config.h"
#include "Modules/Menu/Menu.h"
#include "Modules/Visuals/Visuals.h"
#include "Modules/Misk/Misk.h"
#include <random>

bool OpenMenu = false;




int main() {
	Memory memory = Memory();
	Overlay overlay = Overlay(memory.GetProcessID());
	Time time = Time(300);
	Time time2 = Time(100);
	MapParser mapParser = MapParser(memory);
	EntityHandler entityHandle = EntityHandler(memory, mapParser);
	
	Config config = Config();
	Menu menu = Menu(overlay, config);
	CVisuals visuals = CVisuals(config, entityHandle);
	Misc misc = Misc(config, entityHandle);


	while (true)
	{
		if (time2.IsUpdated()) {
			if (GetAsyncKeyState(config.Key_CloseHack))
				exit(0);

			if (GetAsyncKeyState(config.Key_OpenMenu) & 1) {
				OpenMenu = !OpenMenu;
				overlay.EnableInputMode(OpenMenu);
			}

			memory.Update();
			mapParser.Update();
		}

		if (time.IsUpdated()) {
			entityHandle.UpdatePlayerNames();
			entityHandle.UpdateLocalPlayer();
			entityHandle.localPlayer.viewMatrix.SetScreenData(overlay.GetScreenSize());
			entityHandle.UpdateEnemyEntity();
			
			
			overlay.BeginDrawing();


			ImRender::DrawTextW(std::string("FPS: " + std::to_string(ImGui::GetIO().Framerate)), { 100, 100 });


			if (memory.GetInGame()) {
				visuals.DrawEntity();
				misc.Update();
			}
			

			if (OpenMenu) {
				menu.Draw();
			}


			

					
			




			overlay.EndDrawing();
		}


		
	}

}

