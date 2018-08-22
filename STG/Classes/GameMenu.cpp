#include "GameMenu.h"
#include "GameManager.h"

GameMenu::GameMenu()
{
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/BGM/bgm1.wav");
}

GameMenu::~GameMenu()
{
}

Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("Menu/Menu.csb");
	addChild(rootNode);

	///动画
	ani = CSLoader::createTimeline("Menu/Menu.csb");
	ani->gotoFrameAndPlay(0);
	rootNode->runAction(ani);

	///BGM
	//auto bgm = (ComAudio*)rootNode->getChildByName("Audio_1")->getComponent("Audio_1");
	//bgm->isBackgroundMusicPlaying();
	//auto bgm = ComAudio::create();
	//bgm->playBackgroundMusic("res/BGM/bgm1.wav",TRUE);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("res/BGM/bgm1.wav", true);
	//HRESULT hResult = ::BASS_Init(-1, 44100, 0, NULL, NULL);
	//装载一个声音文件，成功返回一个HSTREA的 变量
    //Sound = ::BASS_StreamCreateFile(FALSE, "res/BGM/bgm3.mp3", 0, 0, 0);
	//播放一个声音文件	
	//BASS_ChannelPlay(Gmusic.Sound1, true);
	GameMusic::Instance()->PlayMusic(GameMusic::Instance()->Sound1);
	//停止播放一个声音文件	
	//BASS_ChannelStop(Sound);
	//暂停播放一个声音文件	
	//BASS_ChannelPause(Sound);
	//释放声音库
	//BASS_Free();

	startGame = (Widget*)rootNode->getChildByName("Start_7");
	manualGame = (Widget*)rootNode->getChildByName("Manual_4");
	endGame = (Widget*)rootNode->getChildByName("Quit_6");
	sg = (Sprite*)startGame;
	mg = (Sprite*)manualGame;
	eg = (Sprite*)endGame;

	auto _xzKey = EventListenerKeyboard::create();
	_xzKey->onKeyPressed = CC_CALLBACK_2(GameMenu::xzKey, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_xzKey, this);

	auto _intoKey = EventListenerKeyboard::create();
	_intoKey->onKeyPressed = CC_CALLBACK_2(GameMenu::intoKey, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_intoKey, this);

	scheduleUpdate();	

	return true;
}

void GameMenu::update(float dt)
{
	stopTime += dt;

	if (stopTime >= 3.42)
	{
		rootNode->stopAction(ani);
	}

	switch (gs)
	{
	case GameMenu::START:		
		sg->setTexture("res/Menu3/Start2.png");
		mg->setTexture("res/Menu3/Manual.png");
		eg->setTexture("res/Menu3/Quit.png");
		break;
	case GameMenu::MANUAL:
		sg->setTexture("res/Menu3/Start.png");
		mg->setTexture("res/Menu3/Manual2.png");
		eg->setTexture("res/Menu3/Quit.png");
		break;
	case GameMenu::END:
		sg->setTexture("res/Menu3/Start.png");
		mg->setTexture("res/Menu3/Manual.png");
		eg->setTexture("res/Menu3/Quit2.png");
		break;
	}
}

void GameMenu::intoKey(EventKeyboard::KeyCode _key, Event * event)
{
	if (_key == EventKeyboard::KeyCode::KEY_Z)
	{
		switch (gs)
		{
		case GameMenu::START:
			//BASS_ChannelStop(Gmusic.Sound1);
			GameMusic::Instance()->StopMusic(GameMusic::Instance()->Sound1);
			GameManager::Instance()->intoGameStart();
			break;
		case GameMenu::MANUAL:
			GameManager::Instance()->intoGameManual();
			break;
		case GameMenu::END:
			GameManager::Instance()->GameQuit();
			break;
		}
	}
}

void GameMenu::xzKey(EventKeyboard::KeyCode _key, Event * event)
{
	if (_key == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		if (gs == START)
		{
			gs = END;
			return;
		}
		if (gs == END)
		{
			gs = MANUAL;
			return;
		}
		if (gs == MANUAL)
		{
			gs = START;
			return;
		}
	}
	if (_key == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if (gs == START)
		{
			gs = MANUAL;
			return;
		}
		if (gs == MANUAL)
		{
			gs = END;
			return;
		}
		if (gs == END)
		{
			gs = START;
			return;
		}
	}
}

