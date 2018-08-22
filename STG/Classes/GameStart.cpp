#include "GameStart.h"

GameStart::GameStart()
{

}

GameStart::~GameStart()
{
	Player::Instance()->m_Player.life = 2;
	Player::Instance()->isSuccess = false;

	bool isBoss = false;
	bool intoisBoss = true;
	bool isGameover = true;

	bool isBossDied = true;

	///Ê±¼ä
	float m_cnt = 0;
}

Scene* GameStart::createScene()
{
	auto scene = Scene::create();
	auto layer = GameStart::create();
	scene->addChild(layer);
	return scene;
}

bool GameStart::init()
{
	if (!Scene::init())
	{
		return false;
	}

	LoadLevel();

	m_currentLevel->setPosition(51, 50);
	addChild(m_currentLevel);
	addChild(m_Enemy);
	addChild(m_PlayerLayer,2);
	addChild(m_BulletLayer);

	GameMusic::Instance()->PlayMusic(GameMusic::Instance()->Sound3);

	startUp = Sprite::create("res/Start/Start_0.png");
	startUp->setPosition(640, 480);
	addChild(startUp,2);

	m_live = Label::createWithTTF("", "res/fonts/arial.ttf", 28);
	m_live->setPosition(1100, 635);
	m_live->setColor(Color3B::RED);
	addChild(m_live,3);
	m_boom = Label::createWithTTF("", "res/fonts/arial.ttf", 28);
	m_boom->setPosition(1100, 520);
	m_boom->setColor(Color3B::RED);
	addChild(m_boom, 3);
	m_Score = Label::createWithTTF("", "res/fonts/arial.ttf", 28);
	m_Score->setPosition(1100, 750);
	m_Score->setColor(Color3B::RED);
	addChild(m_Score, 3);

	scheduleUpdate();

	return true;
}

void GameStart::update(float dt)
{
	m_cnt += dt;

	if (isGameover && !Player::Instance()->isSuccess)
	{
		char temp1[20] = "";
		sprintf(temp1, "%d", Player::Instance()->m_Player.life);
		m_live->setString(temp1);
		char temp2[20] = "";
		sprintf(temp2, "%d", Player::Instance()->m_Player.Boom);
		m_boom->setString(temp2);
		char temp3[20] = "";
		sprintf(temp3, "%d", Player::Instance()->m_Player.Score);
		m_Score->setString(temp3);
	}

	if (intoisBoss && isGameover)
	{
		if (m_cnt >= 72.0f)
		{
			isBoss = true;
			intoisBoss = false;
		}
	}

	if (isBoss)
	{
		removeChild(m_currentLevel, true);
		removeChild(m_Enemy, true);
		m_currentLevel = m_Level_2;
		m_Enemy = m_BossLayer;
		addChild(m_currentLevel);
		addChild(m_Enemy);
		isBoss = false;
		GameMusic::Instance()->StopMusic(GameMusic::Instance()->Sound3);
		GameMusic::Instance()->PlayMusic(GameMusic::Instance()->Sound4);
	}

	//if (isGameover)
	//{
	//	if (Player::Instance()->m_Player.life == -1)
	//	{
	//		removeChild(m_currentLevel, true);
	//		removeChild(m_Enemy, true);
	//		removeChild(m_PlayerLayer, true);
	//		removeChild(m_BulletLayer, true);
	//		removeChild(m_live, true);
	//		removeChild(m_boom, true);
	//		removeChild(m_Score, true);
	//		removeChild(startUp, true);
	//		m_currentLevel = m_GameOver;
	//		addChild(m_currentLevel);
	//		isGameover = false;
	//		Bullet::Instance()->deletBullet();
	//		//Bullet::Instance()->init();
	//		Player::Instance()->deletPlayer();
	//		Player::Instance()->init();
	//	}
	//}

	if (isBossDied)
	{
		if (Player::Instance()->isSuccess)
		{
			removeChild(m_Level_1, true);
			removeChild(m_Level_2, true);
			removeChild(m_BossLayer, true);
			removeChild(m_GameEnd, true);
			removeChild(m_currentLevel, true);
			removeChild(m_Enemy, true);
			removeChild(m_PlayerLayer, true);
			removeChild(m_BulletLayer, true);
			removeChild(m_live, true);
			removeChild(m_boom, true);
			removeChild(m_Score, true);
			removeChild(startUp, true);
			m_currentLevel = m_GameEnd;
			addChild(m_currentLevel);
			isBossDied = false;

			GameMusic::Instance()->StopMusic(GameMusic::Instance()->Sound4);

			Bullet::Instance()->deletBullet();
			Player::Instance()->deletPlayer();
			Player::Instance()->init();
		}
	}
}

void GameStart::LoadLevel()
{
	m_Level_1 = new GameLevel_1();
	m_Level_2 = new GameLevel_2();

	m_BulletLayer = Bullet::Instance();
	Bullet::Instance()->init();

	m_PlayerLayer = Player::Instance();


	m_EnemyLayer = new Enemy();
	m_BossLayer = new Boss();
	m_GameOver = new GameOver();
	m_GameEnd = new GameEnd();


	m_currentLevel = m_Level_1;
	m_Enemy = m_EnemyLayer;
}