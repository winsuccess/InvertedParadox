#include "DualZone.h"
#include "GameManager/ResourceManagers.h"

DualZone::DualZone(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	d = 0;
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

void DualZone::MoveView(int d)
{
	this->d = d;
}

void DualZone::Update(GLfloat deltatime) {
	if (d != 0) {
		Vector2 pos = Get2DPosition();
		pos.x += d * 80 * deltatime;
		Set2DPosition(pos);
	}
}



