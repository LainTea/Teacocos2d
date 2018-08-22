/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
#include "ui\CocosGUI.h"
using namespace ui;

class GameManual : public cocos2d::Layer
{
public:
	GameManual();
	~GameManual();

	void backMenu();
	void update(float dt);

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameManual);
};

