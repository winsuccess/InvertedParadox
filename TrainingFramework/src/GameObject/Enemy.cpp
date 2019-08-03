#include "Enemy.h"
#include "GameManager/ResourceManagers.h"

Enemy::Enemy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_Position = Vector2(0, 0);
	m_HP = 100;
	m_MP = 100;
	m_isAlive = true;
}

Enemy::~Enemy()
{
}

Vector2 Enemy::GetPosition()
{
	return m_Position;
}

void Enemy::SetPosition(Vector2 pos)
{
	m_Position = pos;
}



void Enemy::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;

}

