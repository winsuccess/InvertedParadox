#include "GSMenu.h"
#include "SoundManager.h"

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");

	//BackGround
	auto texture = ResourceManagers::GetInstance()->GetTexture("menu_bg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenwidth / 2, screenheight / 2);
	m_BackGround->SetSize(screenwidth, screenheight);

	////play button
	texture = ResourceManagers::GetInstance()->GetTexture("menu_button_start");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenwidth / 2, 400);
	button->SetSize(123.0f, 37.5f);
	button->SetOnClick([]() {
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//Background music
	SoundManager::GetInstance()->PlaySound("bgmusic");
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
	if(key== KEY_SPACEBAR && bIsPressed)
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_Text_gameName->Draw();
}
