#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Character.h"

class GSMatch :
	public GameStateBase
{
public:
	GSMatch();
	~GSMatch();

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
	std::shared_ptr<Sprite2D> m_BackGround;

	std::shared_ptr<Character> m_Gumball;
	std::shared_ptr<Character> m_Darwin;
	std::shared_ptr<Character> m_Anais;

	std::shared_ptr<Sprite2D> m_PlayerStats;
	std::shared_ptr<Sprite2D> m_ChoicePanel;
	std::vector<std::shared_ptr<GameButton>>	m_listChoiceButton;

};

