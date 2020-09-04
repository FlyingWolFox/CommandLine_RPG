#define _CRT_SECURE_NO_WARNINGS // TODO: fix this
#include "loader.hpp"

char* loadMap(int* pXMapSize, int* pYMapSize)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("map.xml");
	
	if (!result)
	{
		std::cout << "Error parsing map.xml!" << std::endl;
		exit(-1);
	}

	auto mapNode = doc.child("map");
	*pXMapSize = mapNode.attribute("x").as_int();
	*pYMapSize = mapNode.attribute("y").as_int();
	size_t stringSize = strlen(mapNode.child_value());
	char* map = new char[stringSize + 1];
	strcpy(map, mapNode.child_value());
	

	doc.save_file("map.xml");
	//doc.save(std::cout); //TODO: remove debug

	return map;
}

std::list<std::tuple<int, int, char*, int>> loadSprites(size_t spriteSheet)
{
	std::list<std::tuple<int, int, char*, int>> sprites;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("sprites.xml");

	if (!result)
	{
		std::cout << "Error parsing sprites.xml!" << std::endl;
		exit(-2);
	}

	pugi::xml_node_iterator it = doc.child("sprites").child("sheet").begin();
	std::advance(it, spriteSheet);
	pugi::xml_node sheet = *it;

	for (pugi::xml_node sprite = sheet.child("sprite"); sprite; sprite = sprite.next_sibling("sprite"))
	{
		int x, y, priority;
		char* data;
		x = sprite.attribute("x").as_int();
		y = sprite.attribute("y").as_int();
		priority = sprite.attribute("priority").as_int();
		size_t stringSize = strlen(sprite.child_value());
		data = new char[stringSize + 1];
		strcpy(data, sprite.child_value());
		sprites.push_back(std::make_tuple(x, y, data, priority));
	}

	doc.save_file("sprites.xml");
	//doc.save(std::cout); //TODO: remove debug

	return sprites;
}
