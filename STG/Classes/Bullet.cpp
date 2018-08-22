#include "Bullet.h"

Bullet::Bullet()
{
	init();
}

Bullet::~Bullet()
{
}

bool Bullet::init()
{
	if (!Layer::init())
	{
		return false;
	}

	LoadLevel();

	//auto bgm2 = ComAudio::create();
	//bgm2->playBackgroundMusic("res/BGM/bgm3.wav", TRUE);

	m_BossBulletdir.x = 0.0f;
	m_BossBulletdir.y = 0.0f;

	return true;
}

void Bullet::BossBulletKnd(float dt, int _bullknd, Vec2 _bosspos, Vec2 _playerpos, int _i)
{
	switch (_bullknd)
	{
	case 0:
	{
		m_BossBulletTime += dt;
		m_BossBulletTimeknd += dt;
		if (m_BossBulletTime >= 0.3f)
		{
			if (m_bullset < 8)
			{
				m_bullset++;
			}
			m_BossBulletTime = 0;
		}
		for (m_bullnum = 0, m_bullwave = 0; m_bullwave < m_bullset; m_bullwave++)
		{
			if (m_bullwave % 2 == 0)
			{
				dir.x = 3.0f + m_BossBulletdir.x;
				for (int i = 0; i < 25; m_bullnum += 2, i++)
				{
					m_array_BossBullet[0][m_bullnum].pos.x = m_array_BossBullet[0][m_bullnum].pos.x - m_array_BossBullet[0][m_bullnum].speed*dt*dir.x;
					m_array_BossBullet[0][m_bullnum].pos.y = m_array_BossBullet[0][m_bullnum].pos.y - m_array_BossBullet[0][m_bullnum].speed*dt*sqrtf((3.5f*3.5f) - (dir.x*dir.x));

					m_array_BossBullet[0][m_bullnum].bullet->setPosition(m_array_BossBullet[0][m_bullnum].pos);
					if (i % 25 < 12)
					{
						dir.x -= 0.5f;
					}
					else if (i % 25 == 12)
					{
						dir.x += 0.25f;
					}
					else
					{
						dir.x += 0.5f;
					}
				}
				m_bullnum = m_bullwave / 2 * 50 + 1;
			}
			else if (m_bullwave % 2 == 1)
			{
				dir.x = 3.1f + m_BossBulletdir.x;
				for (int i = 0; i < 25; m_bullnum += 2, i++)
				{
					m_array_BossBullet[0][m_bullnum].pos.x = m_array_BossBullet[0][m_bullnum].pos.x - m_array_BossBullet[0][m_bullnum].speed*dt*dir.x;
					m_array_BossBullet[0][m_bullnum].pos.y = m_array_BossBullet[0][m_bullnum].pos.y - m_array_BossBullet[0][m_bullnum].speed*dt*sqrtf((3.5f*3.5f) - (dir.x*dir.x));

					m_array_BossBullet[0][m_bullnum].bullet->setPosition(m_array_BossBullet[0][m_bullnum].pos);
					if (i % 25 < 12)
					{
						dir.x -= 0.5f;
					}
					else if (i % 25 == 12)
					{
						dir.x += 0.28f;
					}
					else
					{
						dir.x += 0.5f;
					}
				}
				m_bullnum = (m_bullwave + 1) / 2 * 50;
			}
		}
		if (m_BossBulletTimeknd >= 6.5f)
		{
			for (int num = 0; num < 200; num++)
			{
				m_array_BossBullet[0][num].pos = _bosspos;
			}
			m_BossBulletTimeknd = 0;
			m_BossBulletTime = 0;
			m_bullset = 1;
			m_BossBulletdir = _playerpos;
		}
	}
	    break;
	case 1:
	{
		m_BossBulletTime += dt;
		for (int m_bullnum = 0; m_bullnum < 64; m_bullnum++)
		{
			if (m_BossBulletTime <= m_array_BossBullet[1][m_bullnum].starttime && m_BossBulletTime >= (m_array_BossBullet[1][m_bullnum].starttime - 0.04f))
			{
				m_array_BossBullet[1][m_bullnum].dir.x = _playerpos.x + 2.0f;
				m_array_BossBullet[1][m_bullnum].pos = _bosspos;
				m_array_BossBullet[1][m_bullnum].bullet->setPosition(m_array_BossBullet[1][m_bullnum].pos);
			}

			if (m_BossBulletTime > m_array_BossBullet[1][m_bullnum].starttime)
			{
				if ((m_bullnum >= 0 && m_bullnum < 5) || (m_bullnum >= 16 && m_bullnum < 21) || (m_bullnum >= 32 && m_bullnum < 37) || (m_bullnum >= 48 && m_bullnum < 53))
				{
					m_array_BossBullet[1][m_bullnum].pos.x = m_array_BossBullet[1][m_bullnum].pos.x - m_array_BossBullet[1][m_bullnum].speed*dt*m_array_BossBullet[1][m_bullnum].dir.x;
					m_array_BossBullet[1][m_bullnum].pos.y = m_array_BossBullet[1][m_bullnum].pos.y - m_array_BossBullet[1][m_bullnum].speed*dt*sqrtf(6.0f*6.0f - m_array_BossBullet[1][m_bullnum].dir.x*m_array_BossBullet[1][m_bullnum].dir.x);

					m_array_BossBullet[1][m_bullnum].bullet->setPosition(m_array_BossBullet[1][m_bullnum].pos);
				}
				if ((m_bullnum >= 5 && m_bullnum < 10) || (m_bullnum >= 21 && m_bullnum < 26) || (m_bullnum >= 37 && m_bullnum < 42) || (m_bullnum >= 53 && m_bullnum < 58))
				{
					m_array_BossBullet[1][m_bullnum].pos.x = m_array_BossBullet[1][m_bullnum].pos.x - m_array_BossBullet[1][m_bullnum].speed*dt*(m_array_BossBullet[1][m_bullnum].dir.x - 4.0f);
					m_array_BossBullet[1][m_bullnum].pos.y = m_array_BossBullet[1][m_bullnum].pos.y - m_array_BossBullet[1][m_bullnum].speed*dt*sqrtf(6.0f*6.0f - (m_array_BossBullet[1][m_bullnum].dir.x - 4.0f)*(m_array_BossBullet[1][m_bullnum].dir.x - 4.0f));

					m_array_BossBullet[1][m_bullnum].bullet->setPosition(m_array_BossBullet[1][m_bullnum].pos);
				}
				if ((m_bullnum >= 10 && m_bullnum < 16) || (m_bullnum >= 26 && m_bullnum < 32) || (m_bullnum >= 42 && m_bullnum < 48) || (m_bullnum >= 58 && m_bullnum < 64))
				{
					m_array_BossBullet[1][m_bullnum].pos.x = m_array_BossBullet[1][m_bullnum].pos.x - m_array_BossBullet[1][m_bullnum].speed*dt*(m_array_BossBullet[1][m_bullnum].dir.x - 2.0f);
					m_array_BossBullet[1][m_bullnum].pos.y = m_array_BossBullet[1][m_bullnum].pos.y - m_array_BossBullet[1][m_bullnum].speed*dt*sqrtf(6.0f*6.0f - (m_array_BossBullet[1][m_bullnum].dir.x - 2.0f)*(m_array_BossBullet[1][m_bullnum].dir.x - 2.0f));

					m_array_BossBullet[1][m_bullnum].bullet->setPosition(m_array_BossBullet[1][m_bullnum].pos);
				}
			}
		}
		if (m_BossBulletTime > 12.5f)
		{
			m_BossBulletTime = 0;
		}
	}
		break;
	case 2:
	{
		m_BossBulletTime += dt;
		m_BossBulletinte += dt;
		if (m_BossBulletinte >= 0.185f)
		{
			if (m_bullnum < 103)
			{
				m_bullnum++;
			}
			m_BossBulletinte = 0;
		}
		if (m_BossBulletTime > 5.2f)
		{
			for (int i = 0; i < 26; i++)
			{
				m_array_BossBullet[2][i].pos.x = m_array_BossBullet[2][i].pos.x - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][25].dir.x;
				m_array_BossBullet[2][i].pos.y = m_array_BossBullet[2][i].pos.y - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][25].dir.y;

				m_array_BossBullet[2][i].bullet->setPosition(m_array_BossBullet[2][i].pos);
			}
		}
		if (m_BossBulletTime > 10.2f)
		{
			for (int i = 26; i < 52; i++)
			{
				m_array_BossBullet[2][i].pos.x = m_array_BossBullet[2][i].pos.x - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][51].dir.x;
				m_array_BossBullet[2][i].pos.y = m_array_BossBullet[2][i].pos.y - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][51].dir.y;

				m_array_BossBullet[2][i].bullet->setPosition(m_array_BossBullet[2][i].pos);
			}
		}
		if (m_BossBulletTime > 15.3f)
		{
			for (int i = 52; i < 78; i++)
			{
				m_array_BossBullet[2][i].pos.x = m_array_BossBullet[2][i].pos.x - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][77].dir.x;
				m_array_BossBullet[2][i].pos.y = m_array_BossBullet[2][i].pos.y - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][77].dir.y;

				m_array_BossBullet[2][i].bullet->setPosition(m_array_BossBullet[2][i].pos);
			}
		}
		if (m_BossBulletTime > 20.5f)
		{
			for (int i = 78; i < 104; i++)
			{
				m_array_BossBullet[2][i].pos.x = m_array_BossBullet[2][i].pos.x - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][103].dir.x;
				m_array_BossBullet[2][i].pos.y = m_array_BossBullet[2][i].pos.y - m_array_BossBullet[2][i].speed*dt*m_array_BossBullet[2][103].dir.y;

				m_array_BossBullet[2][i].bullet->setPosition(m_array_BossBullet[2][i].pos);
			}
		}

		for (; m_bullnum1 < m_bullnum + 1; m_bullnum1++)
		{
			m_array_BossBullet[2][m_bullnum1].pos = _bosspos;
			m_array_BossBullet[2][m_bullnum1].dir = _playerpos;
			m_array_BossBullet[2][m_bullnum1].bullet->setPosition(m_array_BossBullet[2][m_bullnum1].pos);
		}

		if (m_BossBulletTime >= 30.0f)
		{
			m_bullnum1 = 0;
			m_bullnum = 0;
			m_BossBulletTime = 0;
			m_BossBulletinte = 0;
		}
	}
		break;
	case 3:
	{
		m_BossBulletTime += dt;
		m_BossBulletinte += dt;
		if (m_BossBulletinte >= 0.5f)
		{
			if (m_bullset < 10)
			{
				m_bullset++;
				for (; m_bullnum4 < m_bullset * 12; m_bullnum4++)
				{
					m_array_BossBullet[3][m_bullnum4].pos = _bosspos;
				}
			}
			m_BossBulletinte = 0;
		}

		for (int i = 0; i < m_bullset * 12; i++)
		{
			m_array_BossBullet[3][i].pos.x = m_array_BossBullet[3][i].pos.x - m_array_BossBullet[3][i].speed*dt*sinf(m_array_BossBullet[3][i].angle);
			m_array_BossBullet[3][i].pos.y = m_array_BossBullet[3][i].pos.y - m_array_BossBullet[3][i].speed*dt*cosf(m_array_BossBullet[3][i].angle);

			m_array_BossBullet[3][i].bullet->setPosition(m_array_BossBullet[3][i].pos);
		}

		if (m_BossBulletTime >= 10.0f)
		{
			m_BossBulletTime = 0;
			m_BossBulletinte = 0.5f;
			m_bullset = 1;
			m_bullnum4 = 0;
		}
	}
		break;
	}
}

Vec2 Bullet::BulletKnd(float dt, int _bullknd, Vec2 _pos, int _i)
{
	switch (_bullknd)
	{
	case 1:
		m_array_EnemyBullet[0][_i].pos.x = m_array_EnemyBullet[0][_i].pos.x + _pos.x*m_array_EnemyBullet[0][_i].speed*dt ;
		m_array_EnemyBullet[0][_i].pos.y = m_array_EnemyBullet[0][_i].pos.y + _pos.y*m_array_EnemyBullet[0][_i].speed*dt ;
		return 	m_array_EnemyBullet[0][_i].pos;
		break;
	case 2:
		if (m_array_EnemyBullet[1][_i].bullTime > 0)
		{
			int num = _i % 5;
			switch (num)
			{
			case 0:
				m_array_EnemyBullet[1][_i].pos.x = m_array_EnemyBullet[1][_i].pos.x + _pos.x*m_array_EnemyBullet[1][_i].speed*dt;
				m_array_EnemyBullet[1][_i].pos.y = m_array_EnemyBullet[1][_i].pos.y + _pos.y*m_array_EnemyBullet[1][_i].speed*dt;
				break;
			case 1:
				m_array_EnemyBullet[1][_i].pos.x = m_array_EnemyBullet[1][_i].pos.x + _pos.x*m_array_EnemyBullet[1][_i].speed*dt * 2 / 3;
				m_array_EnemyBullet[1][_i].pos.y = m_array_EnemyBullet[1][_i].pos.y + _pos.y*m_array_EnemyBullet[1][_i].speed*dt;
				break;
			case 2:
				m_array_EnemyBullet[1][_i].pos.x = m_array_EnemyBullet[1][_i].pos.x + _pos.x*m_array_EnemyBullet[1][_i].speed*dt * 1 / 3;
				m_array_EnemyBullet[1][_i].pos.y = m_array_EnemyBullet[1][_i].pos.y + _pos.y*m_array_EnemyBullet[1][_i].speed*dt;
				break;
			case 3:
				m_array_EnemyBullet[1][_i].pos.x = m_array_EnemyBullet[1][_i].pos.x + _pos.x*m_array_EnemyBullet[1][_i].speed*dt;
				m_array_EnemyBullet[1][_i].pos.y = m_array_EnemyBullet[1][_i].pos.y + _pos.y*m_array_EnemyBullet[1][_i].speed*dt * 2 / 3;
				break;
			case 4:
				m_array_EnemyBullet[1][_i].pos.x = m_array_EnemyBullet[1][_i].pos.x + _pos.x*m_array_EnemyBullet[1][_i].speed*dt;
				m_array_EnemyBullet[1][_i].pos.y = m_array_EnemyBullet[1][_i].pos.y + _pos.y*m_array_EnemyBullet[1][_i].speed*dt * 1 / 3;
				break;
		    }
		}
		return 	m_array_EnemyBullet[1][_i].pos;
		break;
	case 3:
		if (m_array_EnemyBullet[2][_i].bullTime < 20)
		{
			int num = _i % 5;
			switch (num)
			{
			case 0:
				m_array_EnemyBullet[2][_i].pos.y = m_array_EnemyBullet[2][_i].pos.y + m_array_EnemyBullet[2][_i].speed*dt;
				break;
			case 1:
				m_array_EnemyBullet[2][_i].pos.x = m_array_EnemyBullet[2][_i].pos.x + m_array_EnemyBullet[2][_i].speed*dt * sqrt(3) / 2;
				m_array_EnemyBullet[2][_i].pos.y = m_array_EnemyBullet[2][_i].pos.y + m_array_EnemyBullet[2][_i].speed*dt / 2;
				break;
			case 2:
				m_array_EnemyBullet[2][_i].pos.x = m_array_EnemyBullet[2][_i].pos.x - m_array_EnemyBullet[2][_i].speed*dt * sqrt(3) / 2;
				m_array_EnemyBullet[2][_i].pos.y = m_array_EnemyBullet[2][_i].pos.y + m_array_EnemyBullet[2][_i].speed*dt / 2;
				break;
			case 3:
				m_array_EnemyBullet[2][_i].pos.x = m_array_EnemyBullet[2][_i].pos.x + m_array_EnemyBullet[2][_i].speed*dt / 2;
				m_array_EnemyBullet[2][_i].pos.y = m_array_EnemyBullet[2][_i].pos.y - m_array_EnemyBullet[2][_i].speed*dt * sqrt(3) / 2;
				break;
			case 4:
				m_array_EnemyBullet[2][_i].pos.x = m_array_EnemyBullet[2][_i].pos.x - m_array_EnemyBullet[2][_i].speed*dt / 2;
				m_array_EnemyBullet[2][_i].pos.y = m_array_EnemyBullet[2][_i].pos.y - m_array_EnemyBullet[2][_i].speed*dt * sqrt(3) / 2;
				break;
			}
		}
		else if(m_array_EnemyBullet[2][_i].bullTime > 10)
		{
			m_array_EnemyBullet[2][_i].pos.x = m_array_EnemyBullet[2][_i].pos.x + _pos.x*m_array_EnemyBullet[2][_i].speed*dt;
			m_array_EnemyBullet[2][_i].pos.y = m_array_EnemyBullet[2][_i].pos.y + _pos.y*m_array_EnemyBullet[2][_i].speed*dt;
		}
		return 	m_array_EnemyBullet[2][_i].pos;
		break;
	case 4:
		m_array_EnemyBullet[3][_i].pos.x = m_array_EnemyBullet[3][_i].pos.x + _pos.x*m_array_EnemyBullet[3][_i].speed*dt;
		m_array_EnemyBullet[3][_i].pos.y = m_array_EnemyBullet[3][_i].pos.y + _pos.y*m_array_EnemyBullet[3][_i].speed*dt;
		return 	m_array_EnemyBullet[3][_i].pos;
		break;
	case 5:
		m_array_EnemyBullet[4][_i].pos.x = m_array_EnemyBullet[4][_i].pos.x + _pos.x*m_array_EnemyBullet[4][_i].speed*dt;
		m_array_EnemyBullet[4][_i].pos.y = m_array_EnemyBullet[4][_i].pos.y + _pos.y*m_array_EnemyBullet[4][_i].speed*dt;
		return 	m_array_EnemyBullet[4][_i].pos;
		break;
	case 6:
		m_array_EnemyBullet[5][_i].pos.y = m_array_EnemyBullet[5][_i].pos.y - m_array_EnemyBullet[5][_i].speed*dt;
		return 	m_array_EnemyBullet[5][_i].pos;
		break;
	case 7:
		m_array_EnemyBullet[6][_i].pos.y = m_array_EnemyBullet[6][_i].pos.y - m_array_EnemyBullet[6][_i].speed*dt;
		return 	m_array_EnemyBullet[6][_i].pos;
		break;
	case 8:
		m_array_EnemyBullet[7][_i].pos.y = m_array_EnemyBullet[7][_i].pos.y - m_array_EnemyBullet[7][_i].speed*dt * sqrt(3) / 2;
		int num = _i % 3;
		switch (num)
		{
		case 0:
			break;
		case 1:
			m_array_EnemyBullet[7][_i].pos.x = m_array_EnemyBullet[7][_i].pos.x - m_array_EnemyBullet[7][_i].speed*dt / 2;
			break;
		case 2:
			m_array_EnemyBullet[7][_i].pos.x = m_array_EnemyBullet[7][_i].pos.x + m_array_EnemyBullet[7][_i].speed*dt / 2;
			break;
		}
		return 	m_array_EnemyBullet[7][_i].pos;
		break;
	}
}

void Bullet::LoadLevel()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Bullet/bullet2.plist");
	for (int i = 0; i < 11; i++)
	{
		char temp[128];
		sprintf(temp, "bull_%d.png", i);
		SpriteFrame* bull = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		m_AllBullet.push_back(bull);
	}
	m_array_EnemyBullet[0] = m_EnemyBullet1;
	m_array_EnemyBullet[1] = m_EnemyBullet2;
	m_array_EnemyBullet[2] = m_EnemyBullet3;
	m_array_EnemyBullet[3] = m_EnemyBullet4;
	m_array_EnemyBullet[4] = m_EnemyBullet5;
	m_array_EnemyBullet[5] = m_EnemyBullet6;
	m_array_EnemyBullet[6] = m_EnemyBullet7;
	m_array_EnemyBullet[7] = m_EnemyBullet8;

	m_array_BossBullet[0] = m_BossBullet1;
	m_array_BossBullet[1] = m_BossBullet2;
	m_array_BossBullet[2] = m_BossBullet3;
	m_array_BossBullet[3] = m_BossBullet4;

	///µÐÈËµÄµ¯Ä»
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("res/Enemy/enemy.xml"))
	{
		MessageBox("WARING~~", "SCENE BULLET XML");
	}

	tinyxml2::XMLElement* rootBullet = doc.FirstChildElement("ROOTBULLET");
	tinyxml2::XMLElement* eleBullet = rootBullet->FirstChildElement("BULLET");

	for (int j = 0,k = -1; eleBullet != nullptr; eleBullet = eleBullet->NextSiblingElement(),k++, j++)
	{
		
		tagBullet bullet;
		bullet.speed = atoi(eleBullet->Attribute("speed"));
		bullet.starttime = atof(eleBullet->Attribute("starttime"));
		bullet.cnt = atoi(eleBullet->Attribute("cnt"));
		bullet.isDead = true;

		for (int i = 0; i < bullet.cnt; i++)
		{
			bullet.bullet = Sprite::create();
			bullet.bullet->setSpriteFrame(m_AllBullet[atoi(eleBullet->Attribute("knd"))]);
			if (j>=3)
			{
				m_array_EnemyBullet[k].push_back(bullet);
			}
			else
			{
				m_array_EnemyBullet[j].push_back(bullet);
			}
		}
	}

	///µôÂä½±Àø
	tinyxml2::XMLElement* rootGift = doc.FirstChildElement("ROOTGIFT");
	tinyxml2::XMLElement* eleGift = rootGift->FirstChildElement("GIFT");
	for (; eleGift != nullptr; eleGift = eleGift->NextSiblingElement())
	{
		tagGift gift;
		gift.gift = Sprite::create();
		gift.gift->setSpriteFrame(m_AllBullet[atoi(eleGift->Attribute("knd"))]);
		gift.speed = atoi(eleGift->Attribute("speed"));
		gift.isDead = true;

		m_array_Gift.push_back(gift);
	}

	///Boss µ¯Ä»
	if (doc.LoadFile("res/Boss/Boss.xml"))
	{
		MessageBox("WARING~~", "SCENE BOSS XML");
	}

	rootBullet = doc.FirstChildElement("ROOTBULLET");
	eleBullet = rootBullet->FirstChildElement("BULLET");

	for (int j = 0, k = -1; eleBullet != nullptr; eleBullet = eleBullet->NextSiblingElement(), k++, j++)
	{
		tagBullet bullet;
		bullet.speed = atoi(eleBullet->Attribute("speed"));
		bullet.starttime = atof(eleBullet->Attribute("starttime"));
		bullet.cnt = atoi(eleBullet->Attribute("cnt"));
		bullet.isDead = true;

		if (j == 0)
		{
			for (int i = 0; i < bullet.cnt; i++)
			{
				bullet.bullet = Sprite::create();
				if (i % 2 == 0)
				{
					bullet.bullet->setSpriteFrame(m_AllBullet[0]);
				}
				else
				{
					bullet.bullet->setSpriteFrame(m_AllBullet[1]);
				}
				m_array_BossBullet[0].push_back(bullet);
			}
		}	
		if (j == 1)
		{
			for (int i = 0; i < bullet.cnt; i++)
			{
				bullet.bullet = Sprite::create();
				if (i % 16 == 15)
				{
					bullet.bullet->setSpriteFrame(m_AllBullet[8]);
				}
				else
				{
					bullet.bullet->setSpriteFrame(m_AllBullet[4]);
				}

				m_array_BossBullet[1].push_back(bullet);
			}
		}
		if (j == 2)
		{
			for (int i = 0; i < bullet.cnt; i++)
			{
				bullet.bullet = Sprite::create();
				bullet.bullet->setSpriteFrame(m_AllBullet[5]);

				m_array_BossBullet[2].push_back(bullet);
			}
		}
		if (j == 3)
		{
			for (int i = 0; i < bullet.cnt; i++)
			{
				bullet.bullet = Sprite::create();
				bullet.bullet->setSpriteFrame(m_AllBullet[6]);

				m_array_BossBullet[3].push_back(bullet);
			}
		}
	}


	///Boss µ¯Ä»2 µÇÂ¼Ê±¼ä
	for (int i = 0; i < 15; )
	{
		for (int j = 0; j < 5; i++,j++)
		{
			m_array_BossBullet[1][i].starttime = j*0.3f;
		}

		m_array_BossBullet[1][15].starttime = 1.5f;
	}
	for (int i = 16; i < 31; )
	{
		for (int j = 0; j < 5; i++, j++)
		{
			m_array_BossBullet[1][i].starttime = j*0.3f + 3.0f;
		}

		m_array_BossBullet[1][31].starttime = 1.5f + 3.0f;
	}
	for (int i = 32; i < 47; )
	{
		for (int j = 0; j < 5; i++, j++)
		{
			m_array_BossBullet[1][i].starttime = j*0.3f + 6.0f;
		}

		m_array_BossBullet[1][47].starttime = 1.5f + 6.0f;
	}
	for (int i = 48; i < 63; )
	{
		for (int j = 0; j < 5; i++, j++)
		{
			m_array_BossBullet[1][i].starttime = j*0.3f + 9.0f;
		}

		m_array_BossBullet[1][63].starttime = 1.5f + 9.0f;
	}


	///Boss µ¯Ä»4 ½Ç¶È
	for (int j = 0, i = 0; j < 10; j++)
	{
		for (int k = 0; i < (j + 1) * 12; i++,k++)
		{
			m_array_BossBullet[3][i].angle += PI / 6.0f * k;
		}
	}

}

void Bullet::deletBullet()
{
	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i <m_array_EnemyBullet[k].size(); i++)
		{
			removeChild(m_array_EnemyBullet[k][i].bullet);
		}
		m_array_EnemyBullet[k].clear();
	}
	m_array_EnemyBullet->clear();

	for (int i = 0; i < m_array_BossBullet->size(); i++)
	{
		for (int j = 0; j < m_array_BossBullet[i].size(); j++)
		{
			removeChild(m_array_BossBullet[i][j].bullet);
		}
		m_array_BossBullet[i].clear();
	}
	for (int i = 0; i < 4; i++)
	{
		m_array_BossBullet[i].clear();
	}

	m_array_BossBullet->clear();
}
