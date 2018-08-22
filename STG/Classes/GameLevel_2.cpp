#include "GameLevel_2.h"

GameLevel_2::GameLevel_2()
{
	init();
}

GameLevel_2::~GameLevel_2()
{
}

bool GameLevel_2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto level_2 = CSLoader::createNode("res/Start/Level_2/Level_2.csb");
	addChild(level_2);

	return true;
}
