#pragma once
#include "Sprite2D.h"

class Enemy : public Sprite2D
{

public:
	Enemy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Enemy();

	void SetHp(int x);
	int GetHp();
	bool	IsAlive();
	void	Update(GLfloat deltatime) override;

private:
	int		m_HP;
	int		m_MP;
	int damage;
	bool	m_isAlive;

};
