#pragma once
#include "Sprite2D.h"

class DualZone : public Sprite2D
{


public:

	DualZone(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~DualZone();

	void		SetColliderSize(float size);
	float		GetColliderSize();

private:

	float	m_SizeCollider;


};
