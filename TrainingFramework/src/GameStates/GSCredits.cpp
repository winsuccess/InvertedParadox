#include "GSCredits.h"


GSCredits::GSCredits()
{
}


GSCredits::~GSCredits()
{
}


void GSCredits::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//background
	auto texture = ResourceManagers::GetInstance()->GetTexture("credits_bg");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(screenwidth / 2, screenheight / 2);
	m_background->SetSize(screenwidth, screenheight);
	//Back
	texture = ResourceManagers::GetInstance()->GetTexture("credits_button_back");
	m_backButton = std::make_shared<Sprite2D>(model, shader, texture);
	m_backButton->Set2DPosition(screenwidth / 2, 500);
	m_backButton->SetSize(132.0f, 35.0f);
	//Handle
	texture = ResourceManagers::GetInstance()->GetTexture("menu_handle");
	m_Handle = std::make_shared<Sprite2D>(model, shader, texture);
	m_Handle->Set2DPosition(screenwidth / 2 - 100, 500);
	m_Handle->SetSize(42, 25);
#pragma region  Add Sounds

#pragma endregion

}

void GSCredits::Exit()
{

}


void GSCredits::Pause()
{

}

void GSCredits::Resume()
{

}


void GSCredits::HandleEvents()
{

}

void GSCredits::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == KEY_SPACEBAR && bIsPressed) {
		SoundManager::GetInstance()->PlaySound("startgamesound");
		SoundManager::GetInstance()->PauseSound("menumusic");
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);

	}
}

void GSCredits::HandleTouchEvents(int x, int y, bool bIsPressed)
{

}

void GSCredits::Update(float deltaTime)
{

}

void GSCredits::Draw()
{
	m_background->Draw();
	m_backButton->Draw();
	m_Handle->Draw();
}
