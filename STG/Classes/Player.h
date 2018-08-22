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

#define BULLET_MAX 200

class Player : public cocos2d::Layer
{
private:
	Player();
public:
	~Player();

	static Player* Instance()
	{
		static Player pl;
		return &pl;
	}

	virtual bool init();
	void LoadingPlayer();
	void updatePlayerAnimation(float dt);
	void update(float dt);
	void PlayerAni(EventKeyboard::KeyCode _key, Event*);
	void FirteAt(Vec2 _vec);
	void boomKeyDown(EventKeyboard::KeyCode _key, Event*);
	void deletPlayer();

	struct tagPlayer
	{
		Sprite* player;
		Sprite* dian;
		Sprite* dian_ani;
		Vec2 pos;
		float speed;
		bool isDead = false;
		int DeadTime = 0;
		int Boom;
		bool isBoom = false;
		int life;
		int Score = 0;
	};
	tagPlayer m_Player;

	std::vector<SpriteFrame*> player_Right;
	std::vector<SpriteFrame*> player_Left;
	std::vector<SpriteFrame*> player_Up;
	int m_playerIndex = 0;
	enum Player_State
	{
		UP,
		LEFT,
		RIGHT,
	};
	Player_State player_state = UP;
	Sprite * player = nullptr;
	Vec2 player_pos;

	struct tagBullet
	{
		Sprite* bull;
		Vec2 pos;
		float speed;
		int atk;
		bool isBull = false;
	};
	vector<tagBullet> m_array_Bullet;

	float m_coolDownTime = 0.08f;
	float m_currentTime = 0;
	float m_XZ = 0;
	Vec2 pos;
	float m_cnt = 0;

	bool isSuccess = false;
};

