#include "Clip.h"

Clip::Clip(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime)
	:SpriteSheet(model, shader, texture, pictureSize, spriteSize, start, end, lengthTime) 
{
	isActive = false;
}

Clip::~Clip()
{
}


bool Clip::IsActive()
{
	return isActive;
}

void Clip::SetActive(bool status)
{
	isActive = status;
	if (isActive)
	{
		SpriteSheet::StartAnimation();
	}
}

void Clip::Update(GLfloat deltatime)
{
	if (isActive) {
		SpriteSheet::Update(deltatime);
	}
}
