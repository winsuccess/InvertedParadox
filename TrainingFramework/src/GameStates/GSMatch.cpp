#include "GSMatch.h"

GSMatch::GSMatch()
{

}


GSMatch::~GSMatch()
{
}



void GSMatch::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	auto texture = ResourceManagers::GetInstance()->GetTexture("match_bg1");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenwidth / 2, screenheight / 2);
	m_BackGround->SetSize(screenwidth, screenheight);

	////Player Stats
	texture = ResourceManagers::GetInstance()->GetTexture("match_demo_stats");
	m_PlayerStats = std::make_shared<Sprite2D>(model, shader, texture);
	m_PlayerStats->Set2DPosition(screenwidth / 2, 450);
	m_PlayerStats->SetSize(600.0f, 112.0f);

}

void GSMatch::Exit()
{
}


void GSMatch::Pause()
{

}

void GSMatch::Resume()
{

}


void GSMatch::HandleEvents()
{

}

void GSMatch::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMatch::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	
}

void GSMatch::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	
}

void GSMatch::Draw()
{
	m_BackGround->Draw();
	m_PlayerStats->Draw();
}
