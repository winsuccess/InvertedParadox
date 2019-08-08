#include "Enemy.h"
#include "GameManager/ResourceManagers.h"

Enemy::Enemy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	damage = 50;
	m_HP = 100;
	m_MP = 100;
	m_isAlive = true;
}

Enemy::~Enemy()
{
}

void Enemy::SetHp(int x)
{
	m_HP += x;
}

int Enemy::GetHp()
{
	return m_HP;
}

bool Enemy::IsAlive() {
	return m_isAlive;
}



void Enemy::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;

}

