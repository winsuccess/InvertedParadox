#include "Player.h"
#include "DualZone.h"

Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	dir = Direction::IDLE;
	m_speed = 80;
	m_SizeCollider = 20;
	m_isAlive = true;
}

Player::~Player()
{
}

void Player::Move(Direction d)
{
	dir = d;
}

void Player::SetColliderSize(float size)
{
	m_SizeCollider = size;
}

float Player::GetColliderSize()
{
	return m_SizeCollider;
}

bool Player::IsAlive()
{
	return m_isAlive;
}

bool Player::OnTriggerDualZone(std::vector<std::shared_ptr<DualZone>> listZone)
{
	Vector2 pos = Get2DPosition();
	for (auto zone : listZone)
	{
		//if (//zone->IsActive())
		{
			if (Distance(pos, zone->Get2DPosition()) < m_SizeCollider + zone->GetColliderSize())
			{
				return true;
			}
		}
	}
	return false;

}

float Player::Distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Player::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;
	Vector2 pos = Get2DPosition();

	switch (dir) {
	case IDLE:
		break;
	case LEFT:
	//	pos.x -= m_speed * deltatime;
		break;
	case RIGHT:
	//	pos.x += m_speed * deltatime;
		break;
	case UP:
		pos.y -= m_speed * deltatime;
		break;
	case DOWN:
		pos.y += m_speed * deltatime;
		break;
	}

	Set2DPosition(pos);
}


