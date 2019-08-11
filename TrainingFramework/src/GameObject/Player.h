#pragma once
#include "Sprite2D.h"
#include "SpriteSheet.h"
#include "DualZone.h"

class Player : public SpriteSheet
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
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime = 1.0);
	~Player();

	void Move(Direction d);
	void Update(GLfloat deltatime) override;
	void		SetColliderSize(float size);
	float		GetColliderSize();
	bool		IsAlive();
	bool IsActive();
	void SetActive(bool status);
	bool OnTriggerDualZone(std::vector<std::shared_ptr<DualZone>> listZone);
	float Distance(Vector2 pos, Vector2 target);

private:
	Vector2 m_TargetPosition;
	float	m_speed;
	Direction dir;
	bool	m_isAlive;
	bool	 isActive;
	float	m_SizeCollider;


};
