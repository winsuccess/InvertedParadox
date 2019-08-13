#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime)
	:SpriteSheet(model, shader, texture, pictureSize, spriteSize, start, end, lengthTime)
{
	damage = 30;
	m_HP = 175;
	m_MP = 100;
	m_isAlive = true;
	isHurt = false;
	cooldownTimer = 0;
	isActive = false;
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

void Enemy::Hurt(GLfloat deltaTime)
{
	cooldownTimer -= deltaTime;
	if (cooldownTimer > 30)
		this->Set2DPosition(this->Get2DPosition().x - 20*deltaTime, this->Get2DPosition().y);
	else if (cooldownTimer > 20)
		this->Set2DPosition(this->Get2DPosition().x + 20*deltaTime, this->Get2DPosition().y);
	else if (cooldownTimer > 10)
	{
		this->Set2DPosition(this->Get2DPosition().x - 20*deltaTime, this->Get2DPosition().y);
	}
	else
	{
		isHurt = false;
	}
}

void Enemy::GetHurt()
{
	isHurt = true;
	cooldownTimer = 40;
}

void Enemy::SetAlive(bool isAlive)
{
	m_isAlive = isAlive;
}


bool Enemy::IsActive()
{
	return isActive;
}

void Enemy::SetActive(bool status)
{
	isActive = status;
	if (isActive)
	{
		SpriteSheet::StartAnimation();
	}
}

void Enemy::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;
	if (isHurt)
		Hurt(deltatime);
	if (isActive) {
		SpriteSheet::Update(deltatime);
	}

}

