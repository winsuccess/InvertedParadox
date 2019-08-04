#include "DualZone.h"
#include "GameManager/ResourceManagers.h"

DualZone::DualZone(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_SizeCollider = 25;
}

DualZone::~DualZone()
{
}


void DualZone::SetColliderSize(float size)
{
	m_SizeCollider = size;
}

float DualZone::GetColliderSize()
{
	return m_SizeCollider;
}



