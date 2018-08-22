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
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;//…˘“Ù√¸√˚ø’º‰
#define PI 3.1415

class Bullet : public cocos2d::Layer
{
private :

public:
	Bullet();
	~Bullet();

	static Bullet* Instance()
	{
		static Bullet bull;
		return &bull;
	}

	virtual bool init();

	struct tagBullet
	{
		Sprite* bullet;
		Vec2 pos,dir;
		float starttime;
		float angle = 0;
		float endtime;
		int bullTime = 0;
		int knd;
		float speed;
		int cnt;
		bool isDead = true;
	};
	vector<tagBullet> m_array_EnemyBullet[8];
	vector<tagBullet> m_EnemyBullet1;
	vector<tagBullet> m_EnemyBullet2;
	vector<tagBullet> m_EnemyBullet3;
	vector<tagBullet> m_EnemyBullet4;
	vector<tagBullet> m_EnemyBullet5;
	vector<tagBullet> m_EnemyBullet6;
	vector<tagBullet> m_EnemyBullet7;
	vector<tagBullet> m_EnemyBullet8;
	vector<tagBullet> m_EnemyBullet9;

	vector<tagBullet> m_array_BossBullet[4];
	vector<tagBullet> m_BossBullet1;
	bool is_m_BossBullet = true;
	Vec2 dir;
	int m_bullnum = 0;
	int m_bullwave;
	int m_bullset = 1;
	float m_BossBulletTime = 0;
	float m_BossBulletTimeknd = 0;
	vector<tagBullet> m_BossBullet2;
	float m_BossBulletinte = 0;
	int m_BossBulletint = 1;
	int m_bullnum1 = 0;
	int m_bullnum2;
	int m_bullnum3;
	vector<tagBullet> m_BossBullet3;
	vector<tagBullet> m_BossBullet4;
	int m_bullnum4 = 12;
	int m_bullset2 = 2;

	vector<SpriteFrame*> m_AllBullet;
	Vec2 m_BossBulletdir;

	struct tagGift
	{
		Sprite* gift;
		Vec2 pos;
		float speed;
		bool isDead = true;
	};
	vector<tagGift> m_array_Gift;

	void LoadLevel();
	Vec2 BulletKnd(float dt,int _bullknd,Vec2 _pos,int _i);
	void BossBulletKnd(float dt, int _bullknd, Vec2 _bosspos, Vec2 _playerpos, int _i);
	void deletBullet();
};

