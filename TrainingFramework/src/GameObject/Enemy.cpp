#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	damage = 30;
	m_HP = 375;
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

int Enemy::GetDamage()
{
	return damage;
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
	if (m_HP <= 0)
		m_isAlive = false;

}

