#include "Map.h"

Map::Map(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	d = 0;
}

Map::~Map()
{
}

void Map::MoveView(int d)
{
	this->d = d;
}

void Map::Update(GLfloat deltatime) {
	if (d != 0) {
		Vector2 pos = Get2DPosition();
		pos.x += d * 80 * deltatime;
		Set2DPosition(pos);
	}
}



