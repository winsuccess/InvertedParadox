#pragma once
#include "Sprite2D.h"

class Character : public Sprite2D
{


public:

	Character(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Character();

	void Update(GLfloat deltatime);

private:

	int m_HP;
	int m_MP;
	int m_level;

};
