#include "GSIntro.h"
#include "SoundManager.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


GSIntro::GSIntro()
{
	m_time = 0;
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//background
	auto texture = ResourceManagers::GetInstance()->GetTexture("intro_bg");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(screenwidth / 2, screenheight / 2);
	m_background->SetSize(screenwidth, screenheight);
	//logo
	texture = ResourceManagers::GetInstance()->GetTexture("px_logo");
	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(screenwidth/2, screenheight/3);
	m_logo->SetSize(140.0f, 200/1.5f);

#pragma region  Add Sounds

	SoundManager::GetInstance()->AddSound("introsound");
	SoundManager::GetInstance()->PlaySound("introsound");

	SoundManager::GetInstance()->AddSound("menumusic", true);
	SoundManager::GetInstance()->AddSound("bgmusic", true);
	SoundManager::GetInstance()->AddSound("startgamesound");
	SoundManager::GetInstance()->AddSound("changesound");
	SoundManager::GetInstance()->AddSound("selectsound");
	SoundManager::GetInstance()->AddSound("onturnsound");

	SoundManager::GetInstance()->AddSound("normalattacksound");
	SoundManager::GetInstance()->AddSound("sienceattacksound");
	SoundManager::GetInstance()->AddSound("itemattacksound");
	SoundManager::GetInstance()->AddSound("magicattacksound");

	SoundManager::GetInstance()->AddSound("enemyattacksound");
	SoundManager::GetInstance()->AddSound("entermatchsound");
	SoundManager::GetInstance()->AddSound("weditit"); 
#pragma endregion

}

void GSIntro::Exit()
{
	
}


void GSIntro::Pause()
{
	
}

void GSIntro::Resume()
{
	
}


void GSIntro::HandleEvents()
{
	
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{

}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 3)
	{
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_background->Draw();
	m_logo->Draw();
}
