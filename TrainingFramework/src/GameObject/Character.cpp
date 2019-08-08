#include "Character.h"

Character::Character(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_HP = 500;
	m_MP = 50;
	m_level = 1;
	m_isAlive = true;
}

Character::~Character()
{
}

bool Character::IsAlive() {
	return m_isAlive;
}

void Character::Update(GLfloat deltatime) {
	
}



