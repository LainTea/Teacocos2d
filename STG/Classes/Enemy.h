/*FOR Le-mondai*/
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
#include "ui/CocosGUI.h"
using namespace ui;
#include "tinyxml2\tinyxml2.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//声音命名空间
#include <string>
#include <vector>
using namespace std;

#define PI 3.1415

class Enemy : public cocos2d::Layer
{
public:
	~Enemy();
	Enemy();

	virtual bool init();

	///动画
	vector<SpriteFrame*> m_EnemyAni1;
	vector<SpriteFrame*> m_EnemyAni2;
	vector<SpriteFrame*> m_EnemyAni3;
	vector<SpriteFrame*> m_EnemyAni4;
	vector<SpriteFrame*> m_EnemyAni5;
	vector<SpriteFrame*> m_EnemyAni6;
	vector<SpriteFrame*> m_EnemyAni7;
	vector<SpriteFrame*> m_EnemyAni8;
	vector<SpriteFrame*> m_EnemyAni9;
	vector<SpriteFrame*> m_AllAni[9];
	int Ani1 = 0;
	int Ani2 = 0;
	int Ani3 = 0;
	int Ani4 = 0;
	int Ani5 = 0;
	int Ani6 = 0;
	int Ani7 = 0;
	int Ani8 = 0;
	int Ani9 = 0;
	int arr[9] = { Ani1,Ani2,Ani3,Ani4,Ani5,Ani6,Ani7,Ani8,Ani9 };

	struct tagEnemy
	{
		Sprite* enemy;
		Vec2 pos;
		int hp;
		float starttime;
		float endtime;
		int cnt;
		int bullknd;
		float speed;
		float angle;
		bool isDead = true;
		int enIndex;
		int enTime;
		int moveknd;
	};
    vector<tagEnemy> m_AllEnemy;
	vector<tagEnemy> m_array_Enemy;


	///时间
	float m_cnt = 0;
	int m_bullcnt = 0;
	int m_EnemyIndex = 0;
	Vec2 pos;

	void LoadLevel();
	void update(float dt);
	void updatePlayerAnimation(float dt);
	Vec2 EnemyMove(int i,float dt,int num);

};

