#pragma once
#include "SpriteSheet.h"
#include "Sprite2D.h"

class DualZone : public SpriteSheet
{


public:
	DualZone(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime = 1.0);
	~DualZone();

	void		SetColliderSize(float size);
	float		GetColliderSize();

	bool IsActive();
	void SetActive(bool status);
	void MoveView(int d);
	void Update(GLfloat deltatime) override;

private:

	int d;
	bool isActive;
	float	m_SizeCollider;


};
