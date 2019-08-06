#include "Character.h"
#include "GameManager/ResourceManagers.h"

Character::Character(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_HP = 500;
	m_MP = 50;
	m_level = 1;
}

Character::~Character()
{
}

void Character::Update(GLfloat deltatime) {
	
}



