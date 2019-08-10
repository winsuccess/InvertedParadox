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

	int cooldownTimer;
	bool actionOnce;
	MatchState ms;
	int playerChoice;
	int r;
	int rd;
	bool attackG;
	bool attackD;
	bool attackA;
	bool updateHealth;
	int cTurn;
	bool showDamageRecieved;


	std::shared_ptr<Sprite2D> m_BackGround;

	std::shared_ptr<Character> m_Gumball;
	std::shared_ptr<Character> m_Darwin;
	std::shared_ptr<Character> m_Anais;

	std::shared_ptr<Enemy> m_Monster;

	std::shared_ptr<Sprite2D> m_PlayerStats;
	std::shared_ptr<Sprite2D> m_ChoicePanel;
	std::shared_ptr<Sprite2D> m_ChoiceHandle;
	std::shared_ptr<Sprite2D> m_TurnHandle;
	std::vector<std::shared_ptr<GameButton>>	m_listChoiceButton;

	std::shared_ptr<Text> m_GumballHealth;
	std::shared_ptr<Text> m_DarwinHealth;
	std::shared_ptr<Text> m_AnaisHealth;
	std::shared_ptr<Text> m_DamageToGumball;
	std::shared_ptr<Text> m_DamageToDarwin;
	std::shared_ptr<Text> m_DamageToAnais;
	std::shared_ptr<Text> m_MonsterHealth;
	std::shared_ptr<Text> m_DamageToMonster;

};

