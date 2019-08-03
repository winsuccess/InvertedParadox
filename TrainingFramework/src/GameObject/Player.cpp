#include "Player.h"
#include "GameManager/ResourceManagers.h"

Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_Position = Vector2(0, 0);
	m_HP = 100;
	m_MP = 100;
	m_SizeCollider = 30;
	m_isAlive = true;
}

Player::~Player()
{
}

Vector2 Player::GetPosition()
{
	return m_Position;
}

void Player::SetPosition(Vector2 pos)
{
	m_Position = pos;
}

void Player::SetColliderSize(float size)
{
	m_SizeCollider = size;
}

float Player::GetColliderSize()
{
	return m_SizeCollider;
}

void Player::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;

}


