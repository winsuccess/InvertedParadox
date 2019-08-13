#pragma once
#include "GameStatebase.h"
class GSCredits :
	public GameStateBase
{
public:
	GSCredits();
	~GSCredits();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<Sprite2D> m_backButton;
	std::shared_ptr<Sprite2D> m_Handle;
};


