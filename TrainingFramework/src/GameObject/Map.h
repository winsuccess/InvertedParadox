#pragma once
#include "Sprite2D.h"

class Map : public Sprite2D
{


public:

	Map(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Map();

	void MoveView(int d);
	void Update(GLfloat deltatime);

private:

	int d;

};
