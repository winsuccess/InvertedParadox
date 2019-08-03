#pragma once
#include "Sprite2D.h"

class Enemy : public Sprite2D
{

public:
	Enemy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Enemy();

	Vector2 GetPosition();
	void SetPosition(Vector2 pos);
	void Update(GLfloat deltatime) override;

private:
	Vector2 m_Position;
	int		m_HP;
	int		m_MP;
	bool	m_isAlive;;

};
