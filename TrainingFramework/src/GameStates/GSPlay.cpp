#include "GSPlay.h"

#include <Application.h>
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <iostream>

GSPlay::GSPlay()
{
	cooldownTimer = 30;
	enableMovement = true;
	actionOnce = true;
	animOnce = true;
	showMenu = false;
	playerChoice = 1;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	//Camera
	//Vector3 CameraPos(10, 40, 40);
	//Vector3 TargetPos(0, 0, 0);
	//float fFovY = 0.7f;
	//m_Camera = std::make_shared<Camera>();
	//m_Camera->Init(CameraPos, TargetPos, fFovY, (GLfloat)screenwidth / screenheight, 1.0f, 5000.0f, 1.0f);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//Background Map
	auto texture = ResourceManagers::GetInstance()->GetTexture("play_map");
	m_BackGround = std::make_shared<Map>(model, shader, texture);
	m_BackGround->Set2DPosition(0, screenheight / 2);
	m_BackGround->SetSize(1667, screenheight);

	//Player
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	texture = ResourceManagers::GetInstance()->GetTexture("playeranim");
	m_Player = std::make_shared<Player>(model, shader, texture, Vector2(640, 60), Vector2(40, 60), 0, 0, 1);
	m_Player->SetActive(false);
	m_Player->Set2DPosition(screenwidth / 2-60, screenheight / 2-10);
	m_Player->SetSize(40, 60);

	//DualZone
	texture = ResourceManagers::GetInstance()->GetTexture("play_portal");
	std::shared_ptr<DualZone> dz1 = std::make_shared<DualZone>(model, shader, texture,Vector2(462,261),Vector2(154,261),0,2,1);
	dz1->SetActive(true);
	dz1->Set2DPosition(-335, 370);
	dz1->SetSize(154/3, 261/3);
	m_listZone.push_back(dz1);


#pragma region UIInit
	//Health Bar
	int hAlignment = 120;
	texture = ResourceManagers::GetInstance()->GetTexture("play_healthbar");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_healthBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_healthBar->Set2DPosition(hAlignment, 50);
	m_healthBar->SetSize(240, 48);
	hAlignment += 200;

	//Mana Bar
	texture = ResourceManagers::GetInstance()->GetTexture("play_manabar");
	m_manaBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_manaBar->Set2DPosition(hAlignment, 50);
	m_manaBar->SetSize(162, 36);
	hAlignment += 160;


	//Menu Bar
	texture = ResourceManagers::GetInstance()->GetTexture("play_menubar");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(hAlignment, 50);
	button->SetSize(100, 40);
	hAlignment += 100;
	button->SetOnClick([]() {
		//
		});
	m_listButton.push_back(button);

	//Attack Bar
	texture = ResourceManagers::GetInstance()->GetTexture("play_attackbar");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(hAlignment, 50);
	button->SetSize(56, 50);
	hAlignment += 70;
	button->SetOnClick([]() {
		//
		});
	m_listButton.push_back(button);

	//Defend Bar
	texture = ResourceManagers::GetInstance()->GetTexture("play_defendbar");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(hAlignment, 50);
	button->SetSize(56, 50);
	hAlignment += 70;
	button->SetOnClick([]() {
		//
		});
	m_listButton.push_back(button);

	//Potion Bar
	texture = ResourceManagers::GetInstance()->GetTexture("play_potionbar");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(hAlignment, 50);
	button->SetSize(56, 50);
	button->SetOnClick([]() {
		//
		});
	m_listButton.push_back(button);

#pragma endregion

#pragma region MenuScreen
	//BG
	texture = ResourceManagers::GetInstance()->GetTexture("menu_blackbg");
	m_menuPanel = std::make_shared<Sprite2D>(model, shader, texture);
	m_menuPanel->Set2DPosition(screenwidth/2, screenheight/2);
	m_menuPanel->SetSize(800, 600);

	//Resume Button
	texture = ResourceManagers::GetInstance()->GetTexture("menu_rg");
	std::shared_ptr<Sprite2D> m_resumeButton = std::make_shared<Sprite2D>(model, shader, texture);
	m_resumeButton->Set2DPosition(screenwidth / 2, 200);
	m_resumeButton->SetSize(172 * 1.2, 74 * 1.2);
	m_listMenuButton.push_back(m_resumeButton);

	//Quit to Main Menu Button
	texture = ResourceManagers::GetInstance()->GetTexture("menu_etmm");
	std::shared_ptr<Sprite2D> m_exitToMenuButton = std::make_shared<Sprite2D>(model, shader, texture);
	m_exitToMenuButton->Set2DPosition(screenwidth / 2, 300);
	m_exitToMenuButton->SetSize(172* 1.2, 74* 1.2);
	m_listMenuButton.push_back(m_exitToMenuButton);

	//Exit Game Button
	texture = ResourceManagers::GetInstance()->GetTexture("menu-qg");
	std::shared_ptr<Sprite2D> m_exitGameButton = std::make_shared<Sprite2D>(model, shader, texture);
	m_exitGameButton->Set2DPosition(screenwidth / 2, 400);
	m_exitGameButton->SetSize(172 * 1.2, 74 * 1.2);
	m_listMenuButton.push_back(m_exitGameButton);

	//Menu Handle
	texture = ResourceManagers::GetInstance()->GetTexture("menu_handle");
	m_menuHandle = std::make_shared<Sprite2D>(model, shader, texture);
	m_menuHandle->Set2DPosition(screenwidth / 2-150, 200);
	m_menuHandle->SetSize(52, 33);
#pragma endregion

}


void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == KEY_TAB && bIsPressed) {
		enableMovement = false;
		showMenu = true;
	}

	if (showMenu) {
			if (key == KEY_DOWN && bIsPressed)
			{
				if (playerChoice == 3)
					playerChoice = 1;
				else
					playerChoice++;
				m_menuHandle->Set2DPosition(m_menuHandle->Get2DPosition().x, m_listMenuButton.at(playerChoice - 1)->Get2DPosition().y);
				SoundManager::GetInstance()->PlaySound("changesound");
			}
			else if (key == KEY_UP && bIsPressed)
			{
				if (playerChoice == 1)
					playerChoice = 3;
				else
					playerChoice--;
				m_menuHandle->Set2DPosition(m_menuHandle->Get2DPosition().x, m_listMenuButton.at(playerChoice - 1)->Get2DPosition().y);
				SoundManager::GetInstance()->PlaySound("changesound");
			}
			else if (key == KEY_SPACEBAR && bIsPressed)
			{
				SoundManager::GetInstance()->PlaySound("startgamesound");
				if (playerChoice == 1)
				{
					showMenu = false;
					enableMovement = true;
				}
				else if (playerChoice == 2)
				{
					SoundManager::GetInstance()->PauseSound("menumusic");
					GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
				}
				else {
					Application::GetInstance()->Exit();
				}
			}
	}

	if (enableMovement) {
		if (bIsPressed) {
			if (key == KEY_LEFT) {
			//	direction = 1;
				if (animOnce)
				{
					m_Player->SetAnim(0, 3, 0.5);
					m_Player->SetActive(true);
					animOnce = false;
				}
				m_Player->Move(Player::Direction::LEFT);
				m_BackGround->MoveView(1);
				for (auto it : m_listZone)
				{
					it->MoveView(1);
				}
			}
			if (key == KEY_RIGHT) {
			//	direction = 2;
				if (animOnce)
				{
					m_Player->SetAnim(4, 7, 0.5);
					m_Player->SetActive(true);
					animOnce = false;
				}
				m_Player->Move(Player::Direction::RIGHT);
				m_BackGround->MoveView(-1);
				for (auto it : m_listZone)
				{
					it->MoveView(-1);
				}
			}
			if (key == KEY_UP) {
			//	direction = 3;
				if (animOnce)
				{
					m_Player->SetAnim(8, 12, 0.5);
					m_Player->SetActive(true);
					animOnce = false;
				}
				m_Player->Move(Player::Direction::UP);
			}
			if (key == KEY_DOWN){
			//	direction = 4;
				if (animOnce)
				{
					m_Player->SetAnim(12, 15, 0.5);
					m_Player->SetActive(true);
					animOnce = false;
				}
				m_Player->Move(Player::Direction::DOWN);
				}
		}
		if (!bIsPressed)
		{
			animOnce = true;
			m_Player->SetActive(false);
			m_Player->Move(Player::Direction::IDLE);
			m_BackGround->MoveView(0);
			for (auto it : m_listZone)
			{
				it->MoveView(0);
			}
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto dz : m_listZone)
	{
		if (dz->IsActive())
		{
			dz->Update(deltaTime);
		}
	}

	if (m_Player->IsAlive()) {
		m_Player->Update(deltaTime);
		//m_BackGround->Update(deltaTime);
		for (auto it : m_listZone)
		{
			it->Update(deltaTime);
		}
		if (m_Player->OnTriggerDualZone(m_listZone)) {
			cooldownTimer -= deltaTime;
			enableMovement = false;
			m_Player->Move(Player::Direction::IDLE);
			m_BackGround->MoveView(0);
			for (auto it : m_listZone)
			{
				it->MoveView(0);
			}
		if (actionOnce && !enableMovement) {
			SoundManager::GetInstance()->PlaySound("entermatchsound");
			actionOnce = false;
		}
		}
		if (cooldownTimer <= 0) {
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Match);
		}
	}

}

void GSPlay::Draw()
{
	//BG
	m_BackGround->Draw();

	//Player
		m_Player->Draw();

	//Zones
	for (auto it : m_listZone)
	{
		it->Draw();
	}

	//UI
	m_healthBar->Draw();
	m_manaBar->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	//Menu Panel
	if (showMenu)
	{
		m_menuPanel->Draw();
		for (auto it : m_listMenuButton)
			it->Draw();
		m_menuHandle->Draw();
	}
}
