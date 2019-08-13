#pragma once
#include "Sprite2D.h"

class Character : public Sprite2D
{


public:

	Character(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Character();

	void SetHp(int x);
	int GetHp();
	bool	IsAlive();
	void GetHurt();
	void	Update(GLfloat deltatime) override;
	void Hurt(GLfloat deltaTime);

private:

	int cooldownTimer;
	int m_HP;
	int m_MP;
	int m_level;
	bool	m_isAlive;
	bool isHurt;

};
