#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

Enemy::Enemy()
{
	init();
}

Enemy::~Enemy()
{
	//for (int i = 0; i < m_array_Enemy.size(); i++)
	//{
	//	removeChild(m_array_Enemy[i].enemy);
	//}
	//m_array_Enemy.clear();

	//for (int num = 0; num < 9; num++)
	//{
	//	m_AllAni[num].clear();
	//}
	m_cnt = 0;
}

bool Enemy::init()
{
	if (!Layer::init())
	{
		return false;
	}

	LoadLevel();

	for (int i = 0; i <  m_array_Enemy.size(); i++)
	{
		addChild(m_array_Enemy[i].enemy);
	}

	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < Bullet::Instance()->m_array_EnemyBullet[k].size(); i++)
		{
			addChild(Bullet::Instance()->m_array_EnemyBullet[k][i].bullet);
		}
	}

	//BGM
	//auto bgm2 = ComAudio::create();
	//bgm2->playBackgroundMusic("res/BGM/bgm3.wav", TRUE);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("res/BGM/bgm3.wav", true);
	//if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())    //判断当前是否播放背景音乐  
	//{
	//	SimpleAudioEngine::getInstance()->stopBackgroundMusic();//先停
	//	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/BGM/bgm3.wav", true);//再放
	//}
	//else
	//{
	//	SimpleAudioEngine::getInstance()->playBackgroundMusic("res/BGM/bgm3.wav", true);//直接放
	//}


	scheduleUpdate();
	schedule(schedule_selector(Enemy::updatePlayerAnimation), 0.1f, kRepeatForever, 0.1f);

	return true;
}

void Enemy::update(float dt)
{
	m_cnt += dt;

	///登录敌机
	for (int i = 0; i < m_array_Enemy.size(); i++)
	{
		if (m_cnt >= m_array_Enemy[i].starttime && m_cnt < (m_array_Enemy[i].endtime - 0.4f))
		{
			if (m_array_Enemy[i].isDead == true)
			{
				m_array_Enemy[i].enemy->setPosition(m_array_Enemy[i].pos);
				m_array_Enemy[i].isDead = false;
			}
		}
	}
	///敌人移动
	for (int i = 0; i < m_array_Enemy.size(); i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			if (m_cnt > m_array_Enemy[i].endtime)
			{
				if (m_array_Enemy[i].pos.x < 50 ||
					m_array_Enemy[i].pos.x > 850 ||
					m_array_Enemy[i].pos.y < 50 ||
					m_array_Enemy[i].pos.y > 900)
				{
					m_array_Enemy[i].isDead = true;
					continue;
				}
			}
			m_array_Enemy[i].enTime++;
			m_array_Enemy[i].enemy->setPosition(EnemyMove(m_array_Enemy[i].moveknd, dt, i));
		}
		else
		{
			///敌机死亡
			if (m_cnt > (m_array_Enemy[i].starttime))
			{
				//removeChild(m_array_Enemy[i].enemy);
				m_array_Enemy[i].enemy->setVisible(false);
			}
		}
	}

	///登录弹幕
	for (int k = 0, i = 0; k < 7; k++)
	{
		for (int j = 0, m = 0; i < (k + 1) * 10; m++, i++)
		{
			pos = Player::Instance()->m_Player.pos - m_array_Enemy[i].pos;
			pos.normalize();

			for (; j < (m + 1) * 5; j++)
			{
				if (m_cnt >= Bullet::Instance()->m_array_EnemyBullet[k][j].starttime &&
					m_cnt < Bullet::Instance()->m_array_EnemyBullet[k][j].endtime &&
					Bullet::Instance()->m_array_EnemyBullet[k][j].isDead == true &&
					m_array_Enemy[i].isDead == false)
				{
					Bullet::Instance()->m_array_EnemyBullet[k][j].dir = pos;
					Bullet::Instance()->m_array_EnemyBullet[k][j].pos = m_array_Enemy[i].pos;
					Bullet::Instance()->m_array_EnemyBullet[k][j].bullet->setPosition(m_array_Enemy[i].pos);
					Bullet::Instance()->m_array_EnemyBullet[k][j].isDead = false;
				}
			}
		}
	}
	for (int i = 70, m = 0, j = 0; i < 73; i++, m++)
	{
		for (; j < (m + 1) * 9; j++)
		{
			if (m_cnt >= Bullet::Instance()->m_array_EnemyBullet[7][j].starttime &&
				m_cnt < Bullet::Instance()->m_array_EnemyBullet[7][j].endtime &&
				Bullet::Instance()->m_array_EnemyBullet[7][j].isDead == true &&
				m_array_Enemy[i].isDead == false)
			{
				Bullet::Instance()->m_array_EnemyBullet[7][j].dir = pos;
				Bullet::Instance()->m_array_EnemyBullet[7][j].pos = m_array_Enemy[i].pos;
				Bullet::Instance()->m_array_EnemyBullet[7][j].bullet->setPosition(m_array_Enemy[i].pos);
				Bullet::Instance()->m_array_EnemyBullet[7][j].isDead = false;
			}
		}
	}
	///发射弹幕 弹幕移动
	for (int k = 0, i = 0; k < 7; k++)
	{
		for (int j = 0, m = 0; i < (k + 1) * 10; m++, i++)
		{
			for (; j < (m + 1) * 5; j++)
			{
				if (Bullet::Instance()->m_array_EnemyBullet[k][j].isDead == false)
				{
					if (m_cnt > Bullet::Instance()->m_array_EnemyBullet[k][j].endtime &&
						(Bullet::Instance()->m_array_EnemyBullet[k][j].bullet->getPositionX() < 0 ||
						Bullet::Instance()->m_array_EnemyBullet[k][j].bullet->getPositionX() > 950 ||
						Bullet::Instance()->m_array_EnemyBullet[k][j].bullet->getPositionY() < 0 ||
						Bullet::Instance()->m_array_EnemyBullet[k][j].bullet->getPositionY() > 900))
					{
						Bullet::Instance()->m_array_EnemyBullet[k][j].isDead = true;
						continue;
					}
					Bullet::Instance()->m_array_EnemyBullet[k][j].bullTime++;
					Bullet::Instance()->m_array_EnemyBullet[k][j].bullet->setPosition(Bullet::Instance()->BulletKnd(dt, m_array_Enemy[i].bullknd, 
						                                                              Bullet::Instance()->m_array_EnemyBullet[k][j].dir, j));
				}
				else
				{
					///子弹消失
					//if (m_cnt > Bullet::Instance()->m_array_EnemyBullet[k][j].starttime)
					//{
					//	removeChild(Bullet::Instance()->m_array_EnemyBullet[k][j].bullet);
					//}
				}
			}
		}
	}
	for (int i = 70, m = 0, j = 0; i < 73; i++, m++)
	{
		for (; j < (m + 1) * 9; j++)
		{
			if (Bullet::Instance()->m_array_EnemyBullet[7][j].isDead == false)
			{
				if (m_cnt > Bullet::Instance()->m_array_EnemyBullet[7][j].endtime &&
					(Bullet::Instance()->m_array_EnemyBullet[7][j].bullet->getPositionX() < 0 ||
					Bullet::Instance()->m_array_EnemyBullet[7][j].bullet->getPositionX() > 950 ||
					Bullet::Instance()->m_array_EnemyBullet[7][j].bullet->getPositionY() < 0 ||
					Bullet::Instance()->m_array_EnemyBullet[7][j].bullet->getPositionY() > 900))
				{
					Bullet::Instance()->m_array_EnemyBullet[7][j].isDead = true;
					continue;
				}
				Bullet::Instance()->m_array_EnemyBullet[7][j].bullTime++;
				Bullet::Instance()->m_array_EnemyBullet[7][j].bullet->setPosition(Bullet::Instance()->BulletKnd(dt, m_array_Enemy[i].bullknd, Bullet::Instance()->m_array_EnemyBullet[7][j].dir, j));
			}
			else
			{
				///子弹消失
				//if (m_cnt > Bullet::Instance()->m_array_EnemyBullet[7][j].starttime)
				//{
				//	removeChild(Bullet::Instance()->m_array_EnemyBullet[7][j].bullet);
				//}
			}
		}
	}

	///玩家子弹与敌人接触 ///不同层接触不到
	for (int j = 0; j < m_array_Enemy.size(); j++)
		{
			for (int i = 0; i < 200; i++)
			{
			if (Player::Instance()->m_array_Bullet[i].bull->getBoundingBox().intersectsRect(m_array_Enemy[j].enemy->getBoundingBox()))
			{
				if (m_array_Enemy[j].hp > 0)
				{
					Player::Instance()->m_array_Bullet[i].bull->setPosition(Player::Instance()->m_Player.pos);
					m_array_Enemy[j].hp -= 200;
					if (m_array_Enemy[j].hp <= 0)
					{
						m_array_Enemy[j].isDead = true;
						Player::Instance()->m_Player.Score += 1;
					}
				}
			}
		}
	}

	///玩家与敌人子弹接触
	if (Player::Instance()->m_Player.isDead == false)
	{
		for (int i = 0; i < 8; i++)
		{
			if (Player::Instance()->m_Player.isDead == true)
			{
				break;
			}
			for (int j = 0; j < Bullet::Instance()->m_array_EnemyBullet[i].size(); j++)
			{
				if (Player::Instance()->m_Player.isDead == false && Bullet::Instance()->m_array_EnemyBullet[i][j].isDead == false)
				{
					if (Bullet::Instance()->m_array_EnemyBullet[i][j].bullet->isVisible() && 
						Bullet::Instance()->m_array_EnemyBullet[i][j].bullet->getBoundingBox().intersectsRect(Player::Instance()->m_Player.dian->getBoundingBox()))
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
	
	///Boom
	if (Player::Instance()->m_Player.isBoom)
	{
		//敌人
		for (int i = 0; i < m_array_Enemy.size(); i++)
		{
			if (m_array_Enemy[i].hp > 0 &&
				(m_array_Enemy[i].pos.x > 50 &&
				m_array_Enemy[i].pos.x < 850 &&
				m_array_Enemy[i].pos.y > 50 &&
				m_array_Enemy[i].pos.y < 900))
			{
				m_array_Enemy[i].hp = 0;
				m_array_Enemy[i].isDead = true;
				Player::Instance()->m_Player.Score++;
			}
		}
		//子弹                       可能是 Boom 与 边界 同时 触发     去 登录与 删除 那里看
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < Bullet::Instance()->m_array_EnemyBullet[i].size(); j++)
			{
				if (Bullet::Instance()->m_array_EnemyBullet[i][j].isDead == false &&
					Bullet::Instance()->m_array_EnemyBullet[i][j].bullet->getPositionX() > 50 &&
					Bullet::Instance()->m_array_EnemyBullet[i][j].bullet->getPositionX() < 850 &&
					Bullet::Instance()->m_array_EnemyBullet[i][j].bullet->getPositionY() > 80 &&
					Bullet::Instance()->m_array_EnemyBullet[i][j].bullet->getPositionY() < 900)
				{
					//Bullet::Instance()->m_array_EnemyBullet[i][j].isDead = true;
					Bullet::Instance()->m_array_EnemyBullet[i][j].bullet->setVisible(false);
				}
			}
		}
		Player::Instance()->m_Player.isBoom = false;
	}
	
}

void Enemy::updatePlayerAnimation(float dt)
{
	//for (int i = 0; i < m_array_Enemy.size(); i++)
	//{
	//	if (m_array_Enemy[i].isDead == false)
	//	{
	//		m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[i][m_array_Enemy[i].enIndex]);
	//	}
	//}

	for (int i = 0; i < 10; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[0][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 10; i < 20; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[1][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 20; i < 25; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[2][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 25; i < 30; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[3][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 30; i < 40; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[4][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 40; i < 50; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[5][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 50; i < 60; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[6][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 60; i < 70; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[7][m_array_Enemy[i].enIndex]);
		}
	}
	for (int i = 70; i < 73; i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enemy->setSpriteFrame(m_AllAni[8][m_array_Enemy[i].enIndex]);
		}
	}

	for (int i = 0; i < m_array_Enemy.size(); i++)
	{
		if (m_array_Enemy[i].isDead == false)
		{
			m_array_Enemy[i].enIndex++;
			if (m_array_Enemy[i].enIndex >= 12)
			{
				m_array_Enemy[i].enIndex = 0;
			}
		}
	}

}

Vec2 Enemy::EnemyMove(int knd,float dt,int num)
{
	switch (knd)
	{
	case 1:
		m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt;
		if (m_array_Enemy[num].enTime % 180 <= 90)
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x + m_array_Enemy[num].speed*dt*0.8;
		}
		else
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x - m_array_Enemy[num].speed*dt*0.8;
		}
		return m_array_Enemy[num].pos;
		break;
	case 2:
	{
			if (m_array_Enemy[num].enTime % 300 <= 90)
			{
				m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt*0.4;
				if (num < 15)
				{
					m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x + m_array_Enemy[num].speed*dt*1.5;
				}
				else
				{
					m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x - m_array_Enemy[num].speed*dt*1.5;
				}
			}
			else if (m_array_Enemy[num].enTime % 300 > 210)
			{
				m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y + m_array_Enemy[num].speed*dt*0.4;
				if (num < 15)
				{
					m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x - m_array_Enemy[num].speed*dt*1.5;
				}
				else
				{
					m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x + m_array_Enemy[num].speed*dt*1.5;
				}
			}
		return m_array_Enemy[num].pos;
		break;
	}
	case 3:
	{
		if (m_array_Enemy[num].enTime % 300 <= 90)
		{
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt*1.2;
		}
		else if (m_array_Enemy[num].enTime % 300 > 210)
		{
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y + m_array_Enemy[num].speed*dt*1.2;
		}
		return m_array_Enemy[num].pos;
		break;
	}
	case 4:
	{
		if (m_array_Enemy[num].enTime % 300 <= 90)
		{
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt*1.4;
		}
		else if (m_array_Enemy[num].enTime % 300 > 210)
		{
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y + m_array_Enemy[num].speed*dt*1.4;
		}
		return m_array_Enemy[num].pos;
		break;
	}
	case 5:
	{
		m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt*1.2;
		if (m_array_Enemy[num].enTime % 360 <= 180)
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x + m_array_Enemy[num].speed*dt*0.5;
		}
		else
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x - m_array_Enemy[num].speed*dt*0.5;
		}
		return m_array_Enemy[num].pos;
		break;
	}
	case 6:
	{
		m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt*1.2;
		if (m_array_Enemy[num].enTime % 360 <= 180)
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x - m_array_Enemy[num].speed*dt*0.5;
		}
		else
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x + m_array_Enemy[num].speed*dt*0.5;
		}
		return m_array_Enemy[num].pos;
		break;
	}
	case 7:
	{
		if (m_array_Enemy[num].enTime % 720 <= 120)
		{
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt*1.5;
		}
		else if (m_array_Enemy[num].enTime % 720 > 120 && m_array_Enemy[num].enTime % 720 <= 135)
		{
			m_array_Enemy[num].angle -= PI / 60.0f;
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - sin(m_array_Enemy[num].angle)*dt * 150;
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x + cos(m_array_Enemy[num].angle)*dt * 150;
		}
		else
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x + m_array_Enemy[num].speed*dt*1.5;
		}
		return m_array_Enemy[num].pos;
		break;
	}
	case 8:
	{
		if (m_array_Enemy[num].enTime % 720 <= 120)
		{
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt*1.5;
		}
		else if (m_array_Enemy[num].enTime % 720 > 120 && m_array_Enemy[num].enTime % 720 <= 135)
		{
			m_array_Enemy[num].angle -= PI / 60.0f;
			m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - sin(m_array_Enemy[num].angle)*dt * 150;
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x - cos(m_array_Enemy[num].angle)*dt * 150;
		}
		else
		{
			m_array_Enemy[num].pos.x = m_array_Enemy[num].pos.x - m_array_Enemy[num].speed*dt*1.5;
		}
		return m_array_Enemy[num].pos;
		break;
	}
	case 9:
	{
		if (m_array_Enemy[num].enTime % 720 <= 90)
		{
			if (num == 72)
			{
				m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt * 2;
			}
			else
			{
				m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y - m_array_Enemy[num].speed*dt * 1.8;
			}
		}
		else if (m_array_Enemy[num].enTime % 720 > 90 && m_array_Enemy[num].enTime % 720 <= 630)
		{
		}
		else
		{
			if (num == 72)
			{
				m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y + m_array_Enemy[num].speed*dt * 2;
			}
			else
			{
				m_array_Enemy[num].pos.y = m_array_Enemy[num].pos.y + m_array_Enemy[num].speed*dt * 1.8;
			}
		}
		return m_array_Enemy[num].pos;
		break;
	}
	}
}

void Enemy::LoadLevel()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Enemy/enemy.plist");
	//for (int i = 0; i < 108; i++)
	//{
	//	char temp[128];
	//	sprintf(temp, "%d.png", i);
	//	SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
	//	m_AllEnemy.push_back(en);
	//}
	for (int i = 0; i < 12; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni1.push_back(en);
	}
	for (int i = 12; i < 24; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni2.push_back(en);
	}
	for (int i = 24; i < 36; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni3.push_back(en);
	}
	for (int i = 36; i < 48; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni4.push_back(en);
	}
	for (int i = 48; i < 60; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni5.push_back(en);
	}
	for (int i = 60; i < 72; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni6.push_back(en);
	}
	for (int i = 72; i < 84; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni7.push_back(en);
	}
	for (int i = 84; i < 96; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni8.push_back(en);
	}
	for (int i = 96; i < 108; i++)
	{
		char temp[128];
		sprintf(temp, "%d.png", i);
		SpriteFrame* en = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_EnemyAni9.push_back(en);
	}

	m_AllAni[0] = m_EnemyAni1;
	m_AllAni[1] = m_EnemyAni2;
	m_AllAni[2] = m_EnemyAni3;
	m_AllAni[3] = m_EnemyAni4;
	m_AllAni[4] = m_EnemyAni5;
	m_AllAni[5] = m_EnemyAni6;
	m_AllAni[6] = m_EnemyAni7;
	m_AllAni[7] = m_EnemyAni8;
	m_AllAni[8] = m_EnemyAni9;

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("res/Enemy/enemy.xml"))
	{
		MessageBox("WARING~~", "SCENE ENEMY XML");
	}

	tinyxml2::XMLElement* rootEnemy = doc.FirstChildElement("ROOTENEMY");
	tinyxml2::XMLElement* eleEnemy = rootEnemy->FirstChildElement("ENEMY");

	for (int i = 0,k = 0; eleEnemy != nullptr,i < 9; eleEnemy = eleEnemy->NextSiblingElement(),i++)
	{
		tagEnemy enemy;
		enemy.starttime = atof(eleEnemy->Attribute("starttime"));
		enemy.hp = atoi(eleEnemy->Attribute("hp"));
		enemy.speed = atoi(eleEnemy->Attribute("speed"));
		enemy.pos.x = atof(eleEnemy->Attribute("x"));
		enemy.pos.y = atof(eleEnemy->Attribute("y"));
		enemy.bullknd = atoi(eleEnemy->Attribute("bullknd"));
		enemy.cnt = atoi(eleEnemy->Attribute("cnt"));
		enemy.enTime = atoi(eleEnemy->Attribute("enTime"));
		enemy.enIndex = atoi(eleEnemy->Attribute("enIndex"));
		enemy.angle = atoi(eleEnemy->Attribute("angle"));
		enemy.moveknd = atoi(eleEnemy->Attribute("moveknd"));
		enemy.isDead = true;

		//m_AllEnemy.push_back(enemy);
		for (int j = 0; j < enemy.cnt; j++)
		{
			enemy.enemy = Sprite::create();
			enemy.enemy->setSpriteFrame(m_AllAni[i][0]);
			k++;
			//m_AllEnemy[i].starttime += j;
			m_array_Enemy.push_back(enemy);
			m_array_Enemy[k - 1].starttime = k*0.8;
		}
	}

	//第一种
	for (int i = 5; i < 10; i++)
	{
		m_array_Enemy[i].pos.x = m_array_Enemy[i].pos.x + 600;
	}
	//第二种
	for (int i = 10,k = 0; i < 20; i++,k++)
	{
		m_array_Enemy[i].pos.y = m_array_Enemy[i].pos.y - k * 50;
		if (i>=15)
		{
			m_array_Enemy[i].pos.x = m_array_Enemy[i].pos.x + 870;
		}
	}
	//第三种
	for (int i = 20,k = 0; i < 25; i++,k++)
	{
		m_array_Enemy[i].pos.x = m_array_Enemy[i].pos.x + k*100;
	}
	//第四种
	for (int i = 25, k = 0; i < 30; i++, k++)
	{
		m_array_Enemy[i].pos.x = m_array_Enemy[i].pos.x - k * 110;
	}
	//第五种
	for (int i = 30, k = 0; i < 40; i++, k++)
	{
		m_array_Enemy[i].pos.x = m_array_Enemy[i].pos.x + k * 50;///是否调整位置
	}
	//第六种
	for (int i = 40, k = 0; i < 50; i++, k++)
	{
		m_array_Enemy[i].pos.x = m_array_Enemy[i].pos.x - k * 50;
	}
	//第七八种
	for (int i = 60, k = 0; i < 70; i++, k++)
	{
		m_array_Enemy[i].starttime = m_array_Enemy[i - 10].starttime;
	}
	//第⑨种
	{
		m_array_Enemy[71].pos.x = 750;
		m_array_Enemy[72].pos.x = 450;
	}
	//endtime
	for (int i = 0; i < 73; i++)
	{
		m_array_Enemy[i].endtime = m_array_Enemy[i].starttime + 0.45f;
	}

	//第一种弹幕
	for (int i = 0, j = 0; i < 10; i++)
	{
		for (int k = 0; k < 5; j++,k++)
		{
			Bullet::Instance()->m_array_EnemyBullet[0][j].starttime = m_array_Enemy[i].starttime + 1.0f + 0.1f*k;
		}
	}
	//第二种弹幕
	for (int i = 10, j = 0; i < 20; i++)
	{
		for (int k = 0; k < 5; j++, k++)
		{
			Bullet::Instance()->m_array_EnemyBullet[1][j].starttime = m_array_Enemy[i].starttime + 1.6f + 0.05f*k;
		}
	}
	//第三四种弹幕
	for (int i = 20, j = 0; i < 30; i++)
	{
		for (int k = 0; k < 5; j++, k++)
		{
			Bullet::Instance()->m_array_EnemyBullet[2][j].starttime = m_array_Enemy[i].starttime + 1.80f;
		}
	}
	//第五六种弹幕
	for (int i = 30, j = 0; i < 40; i++)
	{
		for (int k = 0; k < 5; j++, k++)
		{
			Bullet::Instance()->m_array_EnemyBullet[3][j].starttime = m_array_Enemy[38].starttime + 1.0f + 0.2*k;
		}
	}
	for (int i = 40, j = 0; i < 50; i++)
	{
		for (int k = 0; k < 5; j++, k++)
		{
			Bullet::Instance()->m_array_EnemyBullet[4][j].starttime = m_array_Enemy[48].starttime + 1.0f + 0.2*k;
		}
	}
	//第七八种弹幕
	for (int i = 50,n = 0, j = 0; i < 60; i++,n++)
	{
		for (int k = 0; k < 5; j++, k++)
		{
			Bullet::Instance()->m_array_EnemyBullet[5][j].starttime = m_array_Enemy[55].starttime + 1.0f + 0.50f*n + 0.2*k;
		}
	}
	for (int i = 60,n = 0, j = 0; i < 70; i++,n++)
	{
		for (int k = 0; k < 5; j++, k++)
		{
			Bullet::Instance()->m_array_EnemyBullet[6][j].starttime = m_array_Enemy[65].starttime + 1.0f + 0.50f*n + 0.2*k;
		}
	}
	//第九种弹幕
	for (int i = 70, j = 0; i < 73; i++)
	{
		for (int k = 0; k < 3;k++)
		{
			for (int n = 0; n < 3;n++,j++)
			{
				Bullet::Instance()->m_array_EnemyBullet[7][j].starttime = m_array_Enemy[i].starttime + 2.50f + 1.5f*k;
			}
		}
	}
	//endtime
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < Bullet::Instance()->m_array_EnemyBullet[i].size(); j++)
		{
			Bullet::Instance()->m_array_EnemyBullet[i][j].endtime = Bullet::Instance()->m_array_EnemyBullet[i][j].starttime + 0.02f;
		}
	}

	int a = 0;
}