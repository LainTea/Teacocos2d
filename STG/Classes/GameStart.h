/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio\CocoStudio.h"
using namespace cocostudio;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//声音命名空间
#include "ui\CocosGUI.h"
using namespace ui;
#include "GameLevel_1.h"
#include "GameLevel_2.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Boss.h"
#include "GameOver.h"
#include "GameEnd.h"
#include "GameMusic.h"
class GameStart : public cocos2d::Scene
{
private:
	GameStart();
public:
	~GameStart();

	static GameStart* Instance()
	{
		static GameStart GS;
		return &GS;
	}

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameStart);

	///当前关卡
	Layer* m_currentLevel = nullptr;
	Layer* m_PlayerLayer = nullptr;
	Layer* m_EnemyLayer = nullptr;
	Layer* m_BulletLayer = nullptr;
	Layer* m_BossLayer = nullptr;
	Layer* m_Enemy = nullptr;
	Layer* m_GameOver = nullptr;
	Layer* m_GameEnd = nullptr;
	///加载关卡
	void LoadLevel();

	void update(float dt);

	///所有关卡
	Layer* m_Level_1 = nullptr;
	Layer* m_Level_2 = nullptr;
	Layer* m_Level_3 = nullptr;
	Layer* m_Level_4 = nullptr;
	Layer* m_Level_5 = nullptr;

	///残机
	Label* m_live = nullptr;
	///Boom
	Label* m_boom = nullptr;
	///得分
	Label* m_Score = nullptr;
	///界面
	Sprite* startUp = nullptr;

	bool isBoss = false;
	bool intoisBoss = true;
	bool isGameover = true;

	bool isBossDied = true;

	///时间
	float m_cnt = 0;
};
