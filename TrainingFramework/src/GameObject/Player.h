#pragma once
#include "Sprite2D.h"

class Player : public Sprite2D
{

public:
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Player();

	Vector2 GetPosition();
	void SetPosition(Vector2 pos);
	void Update(GLfloat deltatime) override;
	void		SetColliderSize(float size);
	float		GetColliderSize();

private:
	Vector2 m_Position;
	int		m_HP;
	int		m_MP;
	bool	m_isAlive;
	float	m_SizeCollider;


};
