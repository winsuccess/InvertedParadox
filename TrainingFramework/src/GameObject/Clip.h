#pragma once
#include "Sprite2D.h"
#include "SpriteSheet.h"
#include "DualZone.h"

class Clip : public SpriteSheet
{


public:
	Clip(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime = 1.0);
	~Clip();

	void Update(GLfloat deltatime) override;

	bool IsActive();
	void SetActive(bool status);


private:
	bool	 isActive;

};
