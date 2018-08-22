#include "GameManager.h"
#include "GameMenu.h"
#include "GameManual.h"
#include "GameStart.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

Scene* GameManager::createScene()
{
	auto scene = Scene::create();
	auto layer = GameManager::create();
	scene->addChild(layer);
	return scene;
}

bool GameManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void GameManager::intoGameStart()
{
	auto director = Director::getInstance();
	auto scene = GameStart::createScene();
	director->replaceScene(scene);
}

void GameManager::intoGameMenu()
{
	auto director = Director::getInstance();
	auto scene = GameMenu::createScene();
	director->replaceScene(scene);
}

void GameManager::intoGameManual()
{
	auto director = Director::getInstance();
	auto scene = GameManual::createScene();
	director->replaceScene(scene);
}

void GameManager::GameQuit()
{
	Director::getInstance()->end();
}
