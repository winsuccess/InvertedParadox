#include "Player.h"
#include "GameManager/ResourceManagers.h"

Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Camera>& camera, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	dir = Direction::IDLE;
	m_speed = 100;
	m_HP = 100;
	m_MP = 100;
	m_SizeCollider = 30;
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

void Player::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;
	Vector2 pos = Get2DPosition();

	switch (dir) {
	case IDLE:
		break;
	case LEFT:
		pos.x -= m_speed * deltatime;
		break;
	case RIGHT:
		pos.x += m_speed * deltatime;
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


