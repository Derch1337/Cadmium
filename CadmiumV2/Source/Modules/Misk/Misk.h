#pragma once
#include "../Config/Config.h"
#include "../../SDK/SDK.h"
#include "Radar.h"



class Misc
{
private:
	Config& config;
	EntityHandler& entityHandler;

	

	

public:
	Radar radar = Radar(config);


public:
	Misc(Config& cfg, EntityHandler& handler);

	void Update();


private:
	

	void DrawCrossHair();
	void DrawCrossHair2D();

	void Bhop();
	void Trigger();
	void DrawTriggerZone();

};
