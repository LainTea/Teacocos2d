#include "GameEnd.h"
#include "GameManager.h"

GameEnd::GameEnd()
{
	init();
}

GameEnd::~GameEnd()
{
}

bool GameEnd::init()
{
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("GameEnd/GameEnd.csb");
	auto ani = CSLoader::createTimeline("GameEnd/GameEnd.csb");
	ani->gotoFrameAndPlay(0);
	rootNode->runAction(ani);
	addChild(rootNode);

	scheduleUpdate();

	return true;
}

void GameEnd::update(float dt)
{
	endTime += dt;
	if (endTime>=5.0f)
	{
		GameManager::Instance()->intoGameMenu();
	}
}