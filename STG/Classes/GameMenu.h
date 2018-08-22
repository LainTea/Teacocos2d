/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
#include "ui\CocosGUI.h"
using namespace ui;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//…˘“Ù√¸√˚ø’º‰
#include "GameMusic.h"

class GameMenu : public cocos2d::Layer
{
public:
	GameMenu();
	~GameMenu();

	float stopTime = 0;
	Node* rootNode;
	timeline::ActionTimeline* ani;

	void xzKey(EventKeyboard::KeyCode _key, Event*);
	void intoKey(EventKeyboard::KeyCode _key, Event*);

	void update(float dt);

	enum GameState
	{
		START,
		MANUAL,
		END,
	};
	GameState gs = START;

	Vec2 vec;
	Sprite* getButton;
	bool isStart = false;
	Node* startGame;
	Node* manualGame;
	Node* endGame;
	Sprite* sg;
	Sprite* mg;
	Sprite* eg;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameMenu);
};

