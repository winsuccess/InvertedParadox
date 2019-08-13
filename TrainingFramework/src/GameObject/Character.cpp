#include "Character.h"

Character::Character(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_HP = 500;
	m_MP = 50;
	m_level = 1;
	m_isAlive = true;
	isHurt = false;
	cooldownTimer = 0;
}

Character::~Character()
{
}

bool Character::IsAlive() {
	return m_isAlive;
}

void Character::GetHurt()
{
	isHurt = true;
	cooldownTimer = 40;
}

void Character::SetHp(int x)
{
	m_HP += x;
}

int Character::GetHp()
{
	return m_HP;
}

void Character::Update(GLfloat deltatime) {
	if (isHurt)
		Hurt(deltatime);
}

void Character::Hurt( GLfloat deltaTime)
{
	cooldownTimer -= deltaTime;
	if (cooldownTimer > 30)
		this->Set2DPosition(this->Get2DPosition().x - 20 * deltaTime, this->Get2DPosition().y);
	else if (cooldownTimer > 20)
		this->Set2DPosition(this->Get2DPosition().x + 20 * deltaTime, this->Get2DPosition().y);
	else if (cooldownTimer > 10)
	{
		this->Set2DPosition(this->Get2DPosition().x - 20 * deltaTime, this->Get2DPosition().y);
	}
	else
	{
		isHurt = false;
	}
}



