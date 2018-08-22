/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
#include "ui\CocosGUI.h"
using namespace ui;

class GameEnd : public cocos2d::Layer
{
public:
	GameEnd();
	~GameEnd();

	float endTime = 0;

	void update(float dt);

	virtual bool init();

	Node* rootNode = nullptr;
};

