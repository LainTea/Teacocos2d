#include "Player.h"

Player::Player()
{
	init();
}
Player::~Player()
{

}

bool Player::init()
{
	if (!Layer::init())
	{
		return false;
	}

	LoadingPlayer();
	
	addChild(m_Player.player);
	addChild(m_Player.dian);
	addChild(m_Player.dian_ani);

	//auto bgm2 = ComAudio::create();
	//bgm2->playBackgroundMusic("res/BGM/bgm3.wav", TRUE);

	auto _PlayerAni = EventListenerKeyboard::create();
	_PlayerAni->onKeyReleased = CC_CALLBACK_2(Player::PlayerAni, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_PlayerAni, this);

	auto _boomKey = EventListenerKeyboard::create();
	_boomKey->onKeyPressed = CC_CALLBACK_2(Player::boomKeyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_boomKey, this);

	scheduleUpdate();
	schedule(schedule_selector(Player::updatePlayerAnimation), 0.1f, kRepeatForever, 0.1f);

	return true;
}

void Player::update(float dt)
{
	m_cnt += dt;
		pos = m_Player.pos;

		if (GetAsyncKeyState(VK_LSHIFT))
		{
			m_Player.speed = 90;
			m_Player.dian->setVisible(true);
			m_Player.dian_ani->setVisible(true);
		}
		else
		{
			m_Player.speed = 250;
			m_Player.dian->setVisible(false);
			m_Player.dian_ani->setVisible(false);
		}

		m_XZ += 45 * dt;
		m_Player.dian_ani->setRotation(m_XZ);

		if (GetAsyncKeyState(0x26))
		{
			if (GetAsyncKeyState(0x25))
			{
				player_state = LEFT;
				m_Player.pos.y = m_Player.pos.y + (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x - (m_Player.speed*dt / 2 / sqrt(2));
			}
			else if (GetAsyncKeyState(0x27))
			{
				player_state = RIGHT;
				m_Player.pos.y = m_Player.pos.y + (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x + (m_Player.speed*dt / 2 / sqrt(2));
			}
			else
			{
				player_state = UP;
				m_Player.pos.y = m_Player.pos.y + m_Player.speed*dt;
			}
		}
		if (GetAsyncKeyState(0x28))
		{
			if (GetAsyncKeyState(0x25))
			{
				player_state = LEFT;
				m_Player.pos.y = m_Player.pos.y - (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x - (m_Player.speed*dt / 2 / sqrt(2));
			}
			else if (GetAsyncKeyState(0x27))
			{
				player_state = RIGHT;
				m_Player.pos.y = m_Player.pos.y - (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x + (m_Player.speed*dt / 2 / sqrt(2));
			}
			else
			{
				player_state = UP;
				m_Player.pos.y = m_Player.pos.y - m_Player.speed*dt;
			}
		}
		if (GetAsyncKeyState(0x25))
		{
			if (GetAsyncKeyState(0x26))
			{
				player_state = LEFT;
				m_Player.pos.y = m_Player.pos.y + (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x - (m_Player.speed*dt / 2 / sqrt(2));
			}
			else if (GetAsyncKeyState(0x28))
			{
				player_state = LEFT;
				m_Player.pos.y = m_Player.pos.y - (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x - (m_Player.speed*dt / 2 / sqrt(2));
			}
			else
			{
				player_state = LEFT;
				m_Player.pos.x = m_Player.pos.x - m_Player.speed*dt;
			}
		}
		if (GetAsyncKeyState(0x27))
		{
			if (GetAsyncKeyState(0x26))
			{
				player_state = RIGHT;
				m_Player.pos.y = m_Player.pos.y + (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x + (m_Player.speed*dt / 2 / sqrt(2));
			}
			else if (GetAsyncKeyState(0x28))
			{
				player_state = RIGHT;
				m_Player.pos.y = m_Player.pos.y - (m_Player.speed*dt / 2 / sqrt(2));
				m_Player.pos.x = m_Player.pos.x + (m_Player.speed*dt / 2 / sqrt(2));
			}
			else
			{
				player_state = RIGHT;
				m_Player.pos.x = m_Player.pos.x + m_Player.speed*dt;
			}
		}

		m_Player.player->setPosition(m_Player.pos);
		m_Player.dian->setPosition(m_Player.pos);
		m_Player.dian_ani->setPosition(m_Player.pos);

		{
			if (m_Player.player->getPositionY() < 80)
			{
				m_Player.pos.y = pos.y;
				if (m_Player.player->getPositionX() > 70 && m_Player.player->getPositionX() < 840)
				{
					if (GetAsyncKeyState(0x27))
					{
						m_Player.pos.x = m_Player.pos.x + (m_Player.speed*dt / 2 / sqrt(2));
					}
					else if (GetAsyncKeyState(0x25))
					{
						m_Player.pos.x = m_Player.pos.x - (m_Player.speed*dt / 2 / sqrt(2));
					}
				}
			}
			if (m_Player.player->getPositionY() > 880)
			{
				m_Player.pos.y = pos.y;
				if (m_Player.player->getPositionX() > 70 && m_Player.player->getPositionX() < 840)
				{
					if (GetAsyncKeyState(0x27))
					{
						m_Player.pos.x = m_Player.pos.x + (m_Player.speed*dt / 2 / sqrt(2));
					}
					else if (GetAsyncKeyState(0x25))
					{
						m_Player.pos.x = m_Player.pos.x - (m_Player.speed*dt / 2 / sqrt(2));
					}
				}
			}
			if (m_Player.player->getPositionX() <= 60)
			{
				m_Player.pos.x = pos.x;
				if (m_Player.player->getPositionY() > 80 && m_Player.player->getPositionY() < 850)
				{
					if (GetAsyncKeyState(0x28))
					{
						m_Player.pos.y = m_Player.pos.y - (m_Player.speed*dt / 2 / sqrt(2));
					}
					else if (GetAsyncKeyState(0x26))
					{
						m_Player.pos.y = m_Player.pos.y + (m_Player.speed*dt / 2 / sqrt(2));
					}
				}
			}
			if (m_Player.player->getPositionX() >= 845)
			{
				m_Player.pos.x = pos.x;
				if (m_Player.player->getPositionY() > 80 && m_Player.player->getPositionY() < 850)
				{
					if (GetAsyncKeyState(0x28))
					{
						m_Player.pos.y = m_Player.pos.y - (m_Player.speed*dt / 2 / sqrt(2));
					}
					else if (GetAsyncKeyState(0x26))
					{
						m_Player.pos.y = m_Player.pos.y + (m_Player.speed*dt / 2 / sqrt(2));
					}
				}
			}
		}

		///·¢Éä
		if (m_cnt > 0.5f)
		{
			if (GetAsyncKeyState('Z'))
			{
				m_currentTime += dt;
				if (m_currentTime >= m_coolDownTime)
				{
					FirteAt(m_Player.pos);
					m_currentTime = 0;
				}
			}
		}

		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (m_array_Bullet[i].isBull)
			{
				float x = m_array_Bullet[i].bull->getPositionX() + m_array_Bullet[i].speed*dt * 0;
				float y = m_array_Bullet[i].bull->getPositionY() + m_array_Bullet[i].speed*dt * 2;
				m_array_Bullet[i].bull->setPosition(x, y);
			}

			if (m_array_Bullet[i].bull->getPositionY() > 900)
			{
				m_array_Bullet[i].isBull = false;
				m_array_Bullet[i].bull->setVisible(false);
				m_array_Bullet[i].bull->setPosition(m_Player.pos.x, m_Player.pos.y + 20);
			}
		}
	
	 if (m_Player.isDead == true)
	{
		m_Player.DeadTime++;
		if (m_Player.DeadTime==1)
		{
			//addChild(m_Player.player);
			//addChild(m_Player.dian);
			//addChild(m_Player.dian_ani);
			m_Player.life--;
			//addChild(m_Player.player);
			//m_Player.player->setPosition(450.0f, 200.0f);
			//Vec2 pos;
			//m_Player.pos.x = 450.0f;
			//m_Player.pos.y = 200.0f;
			//addChild(m_Player.dian);
			//m_Player.dian->setPosition(450, 200);
			//m_Player.dian->setVisible(false);
			//addChild(m_Player.dian_ani);
			//m_Player.dian_ani->setPosition(450, 200);
			//m_Player.dian_ani->setOpacity(100);
			//m_Player.dian_ani->setVisible(false);

		}
		if (m_Player.DeadTime > 1 && m_Player.DeadTime <= 60)
		{
			switch (m_Player.DeadTime%3)
			{
			case 0:
				m_Player.player->setOpacity(0);
				break;
			case 1:
				m_Player.player->setOpacity(50);
				break;
			case 2:
				m_Player.player->setOpacity(100);
				break;
			case 3:
				m_Player.player->setOpacity(150);
				break;
			case 4:
				m_Player.player->setOpacity(200);
				break;
			}
		}
		if (m_Player.DeadTime > 60)
		{
			m_Player.player->setOpacity(255);
			m_Player.isDead = false;
			m_Player.DeadTime = 0;
		}
	}
}

void Player::FirteAt(Vec2 _vec)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!m_array_Bullet[i].isBull)
		{
			m_array_Bullet[i].isBull = true;
			m_array_Bullet[i].bull->setPosition(_vec.x, _vec.y + 20);
			m_array_Bullet[i].bull->setVisible(true);
			break;
		}
	}
}

void Player::boomKeyDown(EventKeyboard::KeyCode _key, Event*)
{
	if (_key == EventKeyboard::KeyCode::KEY_X)
	{
		if (m_Player.Boom > 0)
		{
			m_Player.isBoom = true;
			m_Player.Boom--;
		}
	}
}

void Player::PlayerAni(EventKeyboard::KeyCode _key, Event *)
{
	if (_key == EventKeyboard::KeyCode::KEY_UP_ARROW || _key == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		_key == EventKeyboard::KeyCode::KEY_LEFT_ARROW || _key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_playerIndex = 0;
		player_state = UP;
	}
}

void Player::updatePlayerAnimation(float dt)
{
	switch (player_state)
	{
	case Player::UP:
		m_Player.player->setSpriteFrame(player_Up[m_playerIndex]);

		break;
	case Player::LEFT:
		m_Player.player->setSpriteFrame(player_Left[m_playerIndex]);

		break;
	case Player::RIGHT:
		m_Player.player->setSpriteFrame(player_Right[m_playerIndex]);

		break;
	}

	if (m_playerIndex <= 6)
	{
		m_playerIndex++;
	}
}

void Player::LoadingPlayer()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Player/Player2.plist");
	for (int i = 0; i < 8; i++)
	{
		char temp[128];
		sprintf(temp, "player_%d.png", i);
		SpriteFrame* pl = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		player_Up.push_back(pl);
	}
	for (int i = 8; i < 16; i++)
	{
		char temp[128];
		sprintf(temp, "player_%d.png", i);
		SpriteFrame* pl = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		player_Left.push_back(pl);
	}
	for (int i = 16; i < 24; i++)
	{
		char temp[128];
		sprintf(temp, "player_%d.png", i);
		SpriteFrame* pl = SpriteFrameCache::getInstance()->getSpriteFrameByName(temp);
		player_Right.push_back(pl);
	}

	{
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile("res/Player/Player.xml"))
		{
			MessageBox("WARING~~", "SCENE Player XML");
		}

		tinyxml2::XMLElement* root = doc.FirstChildElement("ROOTPLAYER");
		tinyxml2::XMLElement* ele = root->FirstChildElement("PLAYER");

		for (; ele != nullptr; ele = ele->NextSiblingElement())
		{
			m_Player.player = Sprite::create(ele->Attribute("player"));
			m_Player.dian = Sprite::create(ele->Attribute("dian"));
			m_Player.dian_ani = Sprite::create(ele->Attribute("dian_ani"));
			m_Player.speed = atoi(ele->Attribute("speed"));
			m_Player.Boom = atoi(ele->Attribute("boom"));
			m_Player.life = atoi(ele->Attribute("life"));
			m_Player.pos.x = atof(ele->Attribute("x"));
			m_Player.pos.y = atof(ele->Attribute("y"));

			m_Player.dian->setVisible(false);
			m_Player.dian->setPosition(m_Player.pos);
			m_Player.dian_ani->setVisible(false);
			m_Player.dian_ani->setOpacity(100);
			m_Player.dian_ani->setPosition(m_Player.pos);
		}

		root = doc.FirstChildElement("ROOTBULLET");
		ele = root->FirstChildElement("BULLET");

		for (; ele != nullptr; ele = ele->NextSiblingElement())
		{
			for (int i = 0; i < BULLET_MAX; i++)
			{
				tagBullet bull;
				bull.bull = Sprite::create(ele->Attribute("path"));
				bull.speed = atoi(ele->Attribute("speed"));
				bull.atk = atoi(ele->Attribute("atk"));
				bull.pos.x = m_Player.pos.x;
				bull.pos.y = m_Player.pos.y + 20;

				addChild(bull.bull);
				bull.bull->setVisible(false);
				m_array_Bullet.push_back(bull);
			}
		}
	}

	m_Player.player->setPosition(m_Player.pos);
	//m_Player.pos = m_Player.player->getPosition();
	player_state = UP;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_array_Bullet[i].bull->setPosition(m_Player.pos);
	}

	m_Player.Score = 0;
}

void Player::deletPlayer()
{
	for (int i = 0; i < 200; i++)
	{
		removeChild(m_array_Bullet[i].bull);
	}
	m_array_Bullet.clear();

	removeChild(m_Player.player);
	removeChild(m_Player.dian);
	removeChild(m_Player.dian_ani);
}
