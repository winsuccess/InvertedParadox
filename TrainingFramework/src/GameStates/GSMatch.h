#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Character.h"
#include "Enemy.h"

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
	enum MatchState {
		STATE_PLAYERTURN,
		STATE_PLAYERATTACK,
		STATE_ENEMYTURN,
		STATE_ENEMYATTACK,
	};

	MatchState ms;
	int playerChoice;
	std::shared_ptr<Sprite2D> m_BackGround;

	std::shared_ptr<Character> m_Gumball;
	std::shared_ptr<Character> m_Darwin;
	std::shared_ptr<Character> m_Anais;

	std::shared_ptr<Enemy> m_Monster;

	std::shared_ptr<Sprite2D> m_PlayerStats;
	std::shared_ptr<Sprite2D> m_ChoicePanel;
	std::shared_ptr<Sprite2D> m_ChoiceHandle;
	std::vector<std::shared_ptr<GameButton>>	m_listChoiceButton;

	std::shared_ptr<Text> m_MonsterHealth;
	std::shared_ptr<Text> m_DamageToMonster;

};

