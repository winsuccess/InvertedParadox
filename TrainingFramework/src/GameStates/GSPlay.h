#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class Sprite2D;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D> m_healthBar;
	std::shared_ptr<Sprite2D> m_manaBar;

};

