#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Player.h"
#include "Map.h"
#include "DualZone.h"

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

private:

	int cooldownTimer;
	bool enableMovement;
	bool actionOnce;
	int direction = 0;
	bool animOnce;
	std::shared_ptr<Camera> m_Camera;
	std::shared_ptr<Map> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::vector<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D> m_healthBar;
	std::shared_ptr<Sprite2D> m_manaBar;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<DualZone>>	m_listZone;
};

