#pragma once
#include "SpriteSheet.h"

class Enemy : public SpriteSheet
{

public:
	Enemy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime = 1.0);
	~Enemy();

	void SetHp(int x);
	int GetHp();
	int GetDamage();
	bool	IsAlive();
	void Hurt(GLfloat deltaTime);
	void GetHurt();
	bool IsActive();
	void SetActive(bool status);
	void SetAlive(bool isAlive);
	void	Update(GLfloat deltatime) override;

private:
	int		m_HP;
	int		m_MP;
	int damage;
	bool	m_isAlive;
	int cooldownTimer;
	bool isHurt;
	bool	 isActive;

};
