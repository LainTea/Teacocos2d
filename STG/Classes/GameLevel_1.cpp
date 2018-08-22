#include "GameLevel_1.h"

GameLevel_1::GameLevel_1()
{
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/BGM/bgm3.wav");
	init();
}

GameLevel_1::~GameLevel_1()
{
}

bool GameLevel_1::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto level_1 = CSLoader::createNode("res/Start/Level_1/Level_1.csb");
	addChild(level_1);

	auto anilevel_1 = CSLoader::createTimeline("res/Start/Level_1/Level_1.csb");
	anilevel_1->gotoFrameAndPlay(0);
	level_1->runAction(anilevel_1);

	//SimpleAudioEngine::getInstance()->playBackgroundMusic("res/BGM/bgm3.mp3", true);
	//auto bgm = ComAudio::create();
	//bgm->playBackgroundMusic("res/BGM/bgm1.wav", TRUE);

	return true;
}


