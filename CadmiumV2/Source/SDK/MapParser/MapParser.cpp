#include "MapParser.h"
#include <BSPParser/bsp_parser.hpp>
#include <filesystem>
#include "../Memory/Memory.h"
#include "../Memory/Offsets.h"
#include <iostream>
#include "../Math/Math.h"

using namespace rn;
inline bsp_parser bspParser;



struct MapName {
	char map_name[256];
};




MapParser::MapParser(Memory& mem) : memory(mem)
{
}

MapParser::~MapParser()
{
	bspParser.unload_map();
}

void MapParser::Update()
{
	if (!memory.GetInGame()) return;

	currentMap = GetMapName();

	if (currentMap.empty())
		return;

	if (currentMap != oldMap || !parsedMap)
	{
		if (parsedMap)
			bspParser.unload_map();

		parsedMap = bspParser.load_map(GetMapFullPath(currentMap), currentMap);
		std::cout << "[MapParser]: Loaded map: " << currentMap << std::endl;

		oldMap = currentMap;
	}
}

const bool MapParser::IsVisible(Vector3 startPosition, Vector3 endPosition)
{
	if (!parsedMap) return true;

	return bspParser.is_visible(
		vector3{ startPosition.x, startPosition.y, startPosition.z },
		vector3{ endPosition.x, endPosition.y, endPosition.z });
}

const bool MapParser::IsMapParsed()
{
	return parsedMap;
}

const std::string MapParser::GetMapName()
{
	return std::string(memory.Read<MapName>(memory.EngineDLL.BaseAdress + EngineOffsets::ptr_mapName).map_name);
}

const std::string MapParser::GetMapFullPath(std::string map_name)
{
	if (std::filesystem::exists(memory.GamePath + "\\" + MAPS_PATH + "\\" + map_name))
		return std::string(memory.GamePath + MAPS_PATH);

	return std::string(memory.GamePath + DOWNLOADS_MAPS_PATH);
}
