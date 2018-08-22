/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
#include "ui\CocosGUI.h"
using namespace ui;

class GameManager : public cocos2d::Layer
{
private:
	GameManager();
public:
	~GameManager();

	static GameManager* Instance()
	{
		static GameManager GM;
		return &GM;
	}

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameManager);

	void intoGameStart();
	void intoGameMenu();
	void intoGameManual();
	void GameQuit();
};

