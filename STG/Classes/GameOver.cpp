#include "GameOver.h"
#include "GameManager.h"

GameOver::GameOver()
{
	init();
}

GameOver::~GameOver()
{
	removeChild(rootNode);
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("GameOver/Scene.csb");
	auto ani = CSLoader::createTimeline("GameOver/Scene.csb");
	ani->gotoFrameAndPlay(0);
	rootNode->runAction(ani);
	addChild(rootNode);

	scheduleUpdate();

	return true;
}

void GameOver::update(float dt)
{
	endTime += dt;
	if (endTime > 3.0f)
	{
		GameManager::Instance()->intoGameMenu();
	}
}