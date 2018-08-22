#include "GameManual.h"
#include "GameManager.h"

GameManual::GameManual()
{
}

GameManual::~GameManual()
{
}

Scene* GameManual::createScene()
{
	auto scene = Scene::create();
	auto layer = GameManual::create();
	scene->addChild(layer);
	return scene;
}

bool GameManual::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Manual/Manual.csb");
	addChild(rootNode);

	scheduleUpdate();

	return true;
}

void GameManual::update(float dt)
{
	if (GetAsyncKeyState('X'))
	{
		GameManual gm;
		gm.backMenu();
	}
}

void GameManual::backMenu()
{
	GameManager::Instance()->intoGameMenu();
}
