/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
#include "ui/CocosGUI.h"
using namespace ui;
#include "tinyxml2\tinyxml2.h"
#include <string>
#include <vector>
using namespace std;
#include "Bullet.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//…˘“Ù√¸√˚ø’º‰

#define PI 3.1415
class Boss : public cocos2d::Layer
{
public:
	Boss();
	~Boss();

	virtual bool init();

	void LoadLevel();
	void updateBossAnimation(float dt);
	void update(float dt);
	void BossMove(int i, float dt, int num);
	void Bossback(float dt);
	void BossKnd();
	void BossInjured();
	void Boss_PlayerInjured();
	void Boss_Boom();
	void BossBullUpdate();

	struct tagBoss
	{
		Sprite* boss;
		Sprite* boss_back0;
		Sprite* boss_back1;
		Sprite* boss_back2;
		Vec2 pos;
		int hp = 0;
		float speed, angle, angle0, angle1, angle2, scale;
		int boss_cnt = 0;
		bool isDead = false;
		int DeadTime = 0;
		int boss_sc;
		bool nextSC = false;
	};
	tagBoss m_Boss;

	std::vector<SpriteFrame*> boss_ani;

	int m_bossIndex = 0;

	std::vector<Vec2> boss_BullKnd0;

	Vec2 playerpos;

	int m_BossKnd = 0;

	bool BossDied = false;
};

