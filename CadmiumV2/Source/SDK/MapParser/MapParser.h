#pragma once
#include <string>

class Memory;
class Vector3;


class MapParser
{


public:
	MapParser(Memory& mem);
	~MapParser();

	void Update();
	const bool IsVisible(Vector3 startPosition, Vector3 endPosition);
	const bool IsMapParsed();
	const std::string GetMapName();
	const std::string GetMapFullPath(std::string map_name);

private:
	Memory& memory;

	std::string oldMap = "";
	std::string currentMap = "";
	bool parsedMap = false;
	const std::string MAPS_PATH = "maps";
	const std::string DOWNLOADS_MAPS_PATH = "download\\maps";
};
