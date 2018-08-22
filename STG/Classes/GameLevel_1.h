/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace ui;
#include "tinyxml2\tinyxml2.h"
#include <string>
#include <vector>
using namespace std;
#include "Player.h"

class GameLevel_1 : public cocos2d::Layer
{
public:
	GameLevel_1();
	~GameLevel_1();

	virtual bool init();

};

