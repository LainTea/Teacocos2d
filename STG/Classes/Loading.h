/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
#include "ui\CocosGUI.h"
using namespace ui;


class Loading : public cocos2d::Layer
{
public:
	Loading();
	~Loading();

	float intoTime = 0;
	//HSTREAM Sound;

	void update(float dt);

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Loading);

};

