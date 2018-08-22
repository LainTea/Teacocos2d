#include "Boss.h"

Boss::Boss()
{
	init();
}

Boss::~Boss()
{
	/*for (int i = 0; i < Bullet::Instance()->m_array_BossBullet->size(); i++)
	{
		for (int j = 0; j < Bullet::Instance()->m_array_BossBullet[i].size(); j++)
		{
			removeChild(Bullet::Instance()->m_array_BossBullet[i][j].bullet);
		}
		Bullet::Instance()->m_array_BossBullet[i].clear();
	}
	for (int i = 0; i < 4; i++)
	{
		Bullet::Instance()->m_array_BossBullet[i].clear();
	}

	Bullet::Instance()->m_array_BossBullet->clear();
*/
	//removeChild(m_Boss.boss);
}

bool Boss::init()
{
	if (!Layer::init())
	{
		return false;
	}

	LoadLevel();

	addChild(m_Boss.boss_back0);
	addChild(m_Boss.boss_back1);
	addChild(m_Boss.boss_back2);
	addChild(m_Boss.boss);
	for (int i = 0; i < 200; i++)
	{
		addChild(Bullet::Instance()->m_array_BossBullet[0][i].bullet);
		Bullet::Instance()->m_array_BossBullet[0][i].pos = m_Boss.pos;
	}
	for (int i = 0; i < 64; i++)
	{
		addChild(Bullet::Instance()->m_array_BossBullet[1][i].bullet);
		Bullet::Instance()->m_array_BossBullet[1][i].pos = m_Boss.pos;
	}
	for (int i = 0; i < 104; i++)
	{
		addChild(Bullet::Instance()->m_array_BossBullet[2][i].bullet);
	}
	for (int i = 0; i < 120; i++)
	{
		addChild(Bullet::Instance()->m_array_BossBullet[3][i].bullet);
		Bullet::Instance()->m_array_BossBullet[3][i].pos = m_Boss.pos;
	}

	scheduleUpdate();
	schedule(schedule_selector(Boss::updateBossAnimation), 0.5f, kRepeatForever, 0.1f);

	return true;
}

void Boss::update(float dt)
{
	m_Boss.boss_cnt++;

	//Boss 背景
	Bossback(dt);

	//Boss 受伤与模式变换
	BossInjured();

	//Boss 弹幕与玩家
	Boss_PlayerInjured();

	//Boss 移动
	BossMove(0, dt, m_BossKnd);

	//Boss 弹幕
	playerpos = m_Boss.pos - Player::Instance()->m_Player.pos;
	playerpos.normalize();
	Bullet::Instance()->BossBulletKnd(dt, m_BossKnd, m_Boss.pos, playerpos, 0);

	//Boom
	Boss_Boom();

	//Boom后处理
	BossBullUpdate();
}

void Boss::Bossback(float dt)
{
	m_Boss.angle0 += 180 * dt;
	m_Boss.angle1 -= 120 * dt;
	m_Boss.angle2 += 60 * dt;

	m_Boss.boss_back0->setRotation(m_Boss.angle0);
	m_Boss.boss_back1->setRotation(m_Boss.angle1);
	m_Boss.boss_back2->setRotation(m_Boss.angle2);

	m_Boss.boss_back0->setScale(m_Boss.scale);
	if (m_Boss.boss_cnt % 100 < 50)
	{
		m_Boss.scale += 0.3*dt;
	}
	else
	{
		m_Boss.scale -= 0.3*dt;
	}
}

void Boss::BossInjured()
{
		for (int i = 0; i < 200; i++)
		{
			if (Player::Instance()->m_array_Bullet[i].bull->isVisible() && Player::Instance()->m_array_Bullet[i].bull->getBoundingBox().intersectsRect(m_Boss.boss->getBoundingBox()))
			{
				if (m_Boss.hp > 0)
				{
					//Player::Instance()->m_array_Bullet[i].bull->setPosition(Player::Instance()->m_Player.pos);
					Player::Instance()->m_array_Bullet[i].bull->setVisible(false);
					m_Boss.hp -= 200;
					if (m_Boss.hp <= 0)
					{
						for (int i = 0; i < Bullet::Instance()->m_array_BossBullet[m_BossKnd].size(); i++)
						{
							//removeChild(Bullet::Instance()->m_array_BossBullet[m_BossKnd][i].bullet);

							Bullet::Instance()->m_array_BossBullet[m_BossKnd][i].bullet->setVisible(false);
						}
						BossKnd();
					}
				}
			}
		}
}

void Boss::Boss_Boom()
{
	if (Player::Instance()->m_Player.isBoom)
	{
		//子弹                       可能是 Boom 与 边界 同时 触发     去 登录与 删除 那里看
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < Bullet::Instance()->m_array_BossBullet[i].size(); j++)
			{
				if (Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionX() > 50 &&
					Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionX() < 850 &&
					Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionY() > 80 &&
					Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionY() < 900)
				{
					Bullet::Instance()->m_array_BossBullet[i][j].bullet->setVisible(false);
				}
			}
		}
		Player::Instance()->m_Player.isBoom = false;
	}
}

void Boss::BossBullUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < Bullet::Instance()->m_array_BossBullet[i].size(); j++)
		{
			if (!Bullet::Instance()->m_array_BossBullet[i][j].bullet->isVisible() &&
				(Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionX() < 50 ||
				Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionX() > 850 ||
				Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionY() < 50 ||
				Bullet::Instance()->m_array_BossBullet[i][j].bullet->getPositionY() > 900))
			{
				Bullet::Instance()->m_array_BossBullet[i][j].bullet->setVisible(true);
			}
		}
	}
}

void Boss::Boss_PlayerInjured()
{
	if (Player::Instance()->m_Player.isDead == false)
	{
		for (int i = 0; i < 4; i++)
		{
			if (Player::Instance()->m_Player.isDead == true)
			{
				break;
			}
			for (int j = 0; j < Bullet::Instance()->m_array_BossBullet[i].size(); j++)
			{
				if (Player::Instance()->m_Player.isDead == false)
				{
					if (Bullet::Instance()->m_array_BossBullet[i][j].bullet->isVisible() && Bullet::Instance()->m_array_BossBullet[i][j].bullet->getBoundingBox().intersectsRect(Player::Instance()->m_Player.dian->getBoundingBox()))
					{
						Player::Instance()->m_Player.isDead = true;
						//removeChild(Player::Instance()->m_Player.dian);
						//removeChild(Player::Instance()->m_Player.dian_ani);
						//removeChild(Player::Instance()->m_Player.player);
						break;
					}
				}
			}
		}
	}
}

void Boss::BossKnd()
{
	m_BossKnd++;
	if (m_BossKnd == 4)
	{
		///游戏通关
		Player::Instance()->isSuccess = true;
	}
	m_Boss.pos.x = 450.0f;
	m_Boss.pos.y = 750.0f;
	m_Boss.boss->setPosition(m_Boss.pos);
	m_Boss.hp = (m_BossKnd + 2) * 5000;
	m_Boss.boss_cnt = 0;
	Bullet::Instance()->m_bullnum = 0;
	Bullet::Instance()->m_bullnum1 = 0;
	Bullet::Instance()->m_bullnum2 = 0;
	Bullet::Instance()->m_bullnum3 = 0;
	Bullet::Instance()->m_BossBulletTime = 0;
	Bullet::Instance()->m_BossBulletTimeknd = 0;
	Bullet::Instance()->m_bullset = 1;
	Bullet::Instance()->m_bullwave = 0;
	Bullet::Instance()->m_BossBulletinte = 0;
}

void Boss::BossMove(int i,float dt, int num)
{
	switch (num)
	{
	case 0:
		break;
	case 1:
		if (m_Boss.boss_cnt % 720 >= 60 && m_Boss.boss_cnt % 720 < 180)
		{
			m_Boss.pos.x = m_Boss.pos.x - m_Boss.speed*dt*sqrtf(3) / 2;
			m_Boss.pos.y = m_Boss.pos.y - m_Boss.speed*dt / 3;
		}
		else if (m_Boss.boss_cnt % 720 >= 240 && m_Boss.boss_cnt % 720 < 360)
		{
			m_Boss.pos.x = m_Boss.pos.x + m_Boss.speed*dt*sqrtf(3) / 2;
			m_Boss.pos.y = m_Boss.pos.y - m_Boss.speed*dt / 3;
		}
		else if (m_Boss.boss_cnt % 720 >= 420 && m_Boss.boss_cnt % 720 < 540)
		{
			m_Boss.pos.x = m_Boss.pos.x + m_Boss.speed*dt*sqrtf(3) / 2;
			m_Boss.pos.y = m_Boss.pos.y + m_Boss.speed*dt / 3;
		}
		else if (m_Boss.boss_cnt % 720 >= 600 && m_Boss.boss_cnt % 720 < 720)
		{
			m_Boss.pos.x = m_Boss.pos.x - m_Boss.speed*dt*sqrtf(3) / 2;
			m_Boss.pos.y = m_Boss.pos.y + m_Boss.speed*dt / 3;
		}
		break;
	case 2:
		if (m_Boss.boss_cnt < 1500)
		{
			if (m_Boss.boss_cnt % 300 < 60)
			{
				m_Boss.pos.x = m_Boss.pos.x - m_Boss.speed*dt*(sqrtf(5) - 1) / 4;
				m_Boss.pos.y = m_Boss.pos.y - m_Boss.speed*dt*sqrtf(10 + 2 * sqrtf(5)) / 4;
			}
			else if (m_Boss.boss_cnt % 300 >= 60 && m_Boss.boss_cnt % 300 < 120)
			{
				m_Boss.pos.x = m_Boss.pos.x + m_Boss.speed*dt*(sqrtf(5) + 1) / 4;
				m_Boss.pos.y = m_Boss.pos.y + m_Boss.speed*dt*sqrtf(10 - 2 * sqrtf(5)) / 4;
			}
			else if (m_Boss.boss_cnt % 300 >= 120 && m_Boss.boss_cnt % 300 < 180)
			{
				m_Boss.pos.x = m_Boss.pos.x - m_Boss.speed*dt;
			}
			else if (m_Boss.boss_cnt % 300 >= 180 && m_Boss.boss_cnt % 300 < 240)
			{
				m_Boss.pos.x = m_Boss.pos.x + m_Boss.speed*dt*(sqrtf(5) + 1) / 4;
				m_Boss.pos.y = m_Boss.pos.y - m_Boss.speed*dt*sqrtf(10 - 2 * sqrtf(5)) / 4;
			}
			else if (m_Boss.boss_cnt % 300 >= 240 && m_Boss.boss_cnt % 300 < 300)
			{
				m_Boss.pos.x = m_Boss.pos.x - m_Boss.speed*dt*(sqrtf(5) - 1) / 4;
				m_Boss.pos.y = m_Boss.pos.y + m_Boss.speed*dt*sqrtf(10 + 2 * sqrtf(5)) / 4;
			}
		}
		else if (m_Boss.boss_cnt >= 1500 && m_Boss.boss_cnt < 1800) {}
		else {m_Boss.boss_cnt = 0;}
		break;
	case 3:
		if (m_Boss.boss_cnt < 480)
		{
			if (m_Boss.speed < 240.0f)
			{
				m_Boss.speed += 0.4f;
			}

			m_Boss.pos.x = m_Boss.pos.x + m_Boss.speed*dt;

			if (m_Boss.pos.x > 900)
			{
				m_Boss.pos.x = 50;
			}
		}
		else if (m_Boss.boss_cnt >= 480 && m_Boss.boss_cnt < 600){}
		else {m_Boss.boss_cnt = 0;}
		break;
	}

	m_Boss.boss->setPosition(m_Boss.pos);
	m_Boss.boss_back0->setPosition(m_Boss.pos);
	m_Boss.boss_back1->setPosition(m_Boss.pos);
	m_Boss.boss_back2->setPosition(m_Boss.pos);
}

void Boss::updateBossAnimation(float dt)
{
	m_Boss.boss->setSpriteFrame(boss_ani[m_bossIndex]);
	m_bossIndex++;
	if (m_bossIndex > 8)
	{
		m_bossIndex = 3;
	}
}

void Boss::LoadLevel()
{
	//SimpleAudioEngine::getInstance()->preloadBackgroundMusic("res/BGM/bgm4.wav");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Boss/Boss.plist");
	for (int i = 0; i < 12; i++)
	{
		char temp[128];
		sprintf(temp, "boss_%d.png", i);
		SpriteFrame* bo = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		boss_ani.push_back(bo);
	}

		tinyxml2::XMLDocument doc;
		if (doc.LoadFile("res/Boss/Boss.xml"))
		{
			MessageBox("WARING~~", "SCENE Boss XML");
		}

		tinyxml2::XMLElement* root = doc.FirstChildElement("ROOTBOSS");
		tinyxml2::XMLElement* ele = root->FirstChildElement("BOSS");

		for (; ele != nullptr; ele = ele->NextSiblingElement())
		{
			m_Boss.boss = Sprite::create();
			m_Boss.boss->setSpriteFrame(boss_ani[0]);
			m_Boss.boss_back0 = Sprite::create();
			m_Boss.boss_back0->setSpriteFrame(boss_ani[9]);
			m_Boss.boss_back1 = Sprite::create();
			m_Boss.boss_back1->setSpriteFrame(boss_ani[10]);
			m_Boss.boss_back2 = Sprite::create();
			m_Boss.boss_back2->setSpriteFrame(boss_ani[11]);
			m_Boss.speed = atoi(ele->Attribute("speed"));
			m_Boss.boss_sc = atoi(ele->Attribute("boss_sc"));
			m_Boss.angle = atof(ele->Attribute("angle"));
			m_Boss.angle0 = atof(ele->Attribute("angle"));
			m_Boss.angle1 = atof(ele->Attribute("angle"));
			m_Boss.angle2 = atof(ele->Attribute("angle"));
			m_Boss.scale = atof(ele->Attribute("scale"));
			m_Boss.pos.x = atof(ele->Attribute("x"));
			m_Boss.pos.y = atof(ele->Attribute("y"));
			m_Boss.hp = atoi(ele->Attribute("hp"));
		}

		m_Boss.boss->setPosition(m_Boss.pos.x, m_Boss.pos.y);
		m_Boss.boss->setScale(1.2f);

		m_Boss.boss_back0->setPosition(m_Boss.pos.x, m_Boss.pos.y);
		m_Boss.boss_back1->setPosition(m_Boss.pos.x, m_Boss.pos.y);
		m_Boss.boss_back2->setPosition(m_Boss.pos.x, m_Boss.pos.y);

		m_Boss.boss_back0->setOpacity(100);
		m_Boss.boss_back1->setOpacity(100);
		m_Boss.boss_back2->setOpacity(100);


}