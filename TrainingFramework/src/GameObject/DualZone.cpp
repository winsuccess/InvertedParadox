#include "DualZone.h"

DualZone::DualZone(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime)
	:SpriteSheet(model, shader, texture, pictureSize, spriteSize, start, end, lengthTime)
{
	d = 0;
	isActive = true;
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

bool DualZone::IsActive()
{
	return isActive;
}

void DualZone::SetActive(bool status)
{
	isActive = status;
	if (isActive)
	{
		SpriteSheet::StartAnimation();
	}
}

void DualZone::Update(GLfloat deltatime) {
	if (!isActive)
		return;
	if (d != 0) {
		Vector2 pos = Get2DPosition();
		pos.x += d * 40 * deltatime;
		Set2DPosition(pos);
	}
	SpriteSheet::Update(deltatime);
}



