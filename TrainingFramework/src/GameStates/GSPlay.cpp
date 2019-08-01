#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenwidth / 2, screenheight / 2);
	m_BackGround->SetSize(screenwidth, screenheight);

	//Player Name
	//shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	//m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	//m_BackGround->Set2DPosition(screenwidth / 2, screenheight / 2);
	//m_BackGround->SetSize(screenwidth, screenheight);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//Health Bar
	int hAlignment = 120;
	texture = ResourceManagers::GetInstance()->GetTexture("play_healthbar");
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
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_healthBar->Draw();
	m_manaBar->Draw();
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}