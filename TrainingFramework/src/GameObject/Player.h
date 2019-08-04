#pragma once
#include "Sprite2D.h"
#include "DualZone.h"

class Player : public Sprite2D
{


public:
	enum Direction
	{
		IDLE,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Player();

	void Move(Direction d);
	void Update(GLfloat deltatime) override;
	void		SetColliderSize(float size);
	float		GetColliderSize();
	bool		IsAlive();
	bool OnTriggerDualZone(std::vector<std::shared_ptr<DualZone>> listZone);
	float Distance(Vector2 pos, Vector2 target);

private:
	Vector2 m_TargetPosition;
	float	m_speed;
	int		m_HP;
	int		m_MP;
	Direction dir;
	bool	m_isAlive;
	float	m_SizeCollider;


};
