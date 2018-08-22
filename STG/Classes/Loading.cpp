#include "Loading.h"
#include "GameManager.h"
#include "GameStart.h"

Loading::Loading()
{
}

Loading::~Loading()
{
}

Scene* Loading::createScene()
{
	auto scene = Scene::create();
	auto layer = Loading::create();
	scene->addChild(layer);
	return scene;
}

bool Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Loading/Loading.csb");
	auto ani = CSLoader::createTimeline("Loading/Loading.csb");
	ani->gotoFrameAndPlay(0);
	rootNode->runAction(ani);
	addChild(rootNode);

	//HRESULT hResult = ::BASS_Init(-1, 44100, 0, NULL, NULL);
	////装载一个声音文件，成功返回一个HSTREA的 变量
	//Sound = ::BASS_StreamCreateFile(FALSE, "res/BGM/bgm1.mp3", 0, 0, 0);
	//BASS_ChannelPlay(Sound, true);

	scheduleUpdate();

	return true;
}
void Loading::update(float dt)
{
	intoTime += dt;
	if (intoTime >= 1.5)
	{
		///切换menu
		//BASS_ChannelPlay(Sound, true);
		GameManager::Instance()->intoGameMenu();
	}
}


