#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
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
	bool changetoPlay;
	int cooldownTimer;
	int playerChoice;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::vector<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D> m_menuHandle;
	std::shared_ptr<Text>  m_Text_gameName;

};

