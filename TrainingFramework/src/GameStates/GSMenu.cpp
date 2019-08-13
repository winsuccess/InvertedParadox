#include "GSMenu.h"
#include "SoundManager.h"
#include "Application.h"

GSMenu::GSMenu()
{
	changetoPlay = false;
	cooldownTimer = 80;
	playerChoice = 1;
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


	//List buttons
	texture = ResourceManagers::GetInstance()->GetTexture("menu_button_start");
	std::shared_ptr<GameButton> playButton = std::make_shared<GameButton>(model, shader, texture);
	playButton->Set2DPosition(screenwidth / 2, 400);
	playButton->SetSize(132.0f, 35.0f);
	m_listButton.push_back(playButton);

	texture = ResourceManagers::GetInstance()->GetTexture("menu_button_credits");
	std::shared_ptr<GameButton> creditsButton = std::make_shared<GameButton>(model, shader, texture);
	creditsButton->Set2DPosition(screenwidth / 2, 450);
	creditsButton->SetSize(132.0f, 35.0f);
	m_listButton.push_back(creditsButton);

	texture = ResourceManagers::GetInstance()->GetTexture("menu_button_quit");
	std::shared_ptr<GameButton> quitButton = std::make_shared<GameButton>(model, shader, texture);
	quitButton->Set2DPosition(screenwidth / 2, 500);
	quitButton->SetSize(132.0f, 35.0f);
	m_listButton.push_back(quitButton);

	texture = ResourceManagers::GetInstance()->GetTexture("menu_handle");
	m_menuHandle = std::make_shared<Sprite2D>(model, shader, texture);
	m_menuHandle->Set2DPosition(screenwidth / 2- 130, 400);
	m_menuHandle->SetSize(42, 25);

	//Background music
	SoundManager::GetInstance()->PlaySound("menumusic");
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
	if (key == KEY_DOWN && bIsPressed)
	{
		if (playerChoice == 3)
			playerChoice = 1;
		else
			playerChoice++;
		m_menuHandle->Set2DPosition(m_menuHandle->Get2DPosition().x, m_listButton.at(playerChoice - 1)->Get2DPosition().y);
		SoundManager::GetInstance()->PlaySound("changesound");
	}
	else if (key == KEY_UP && bIsPressed)
	{
		if (playerChoice == 1)
			playerChoice = 3;
		else
			playerChoice--;
		m_menuHandle->Set2DPosition(m_menuHandle->Get2DPosition().x, m_listButton.at(playerChoice - 1)->Get2DPosition().y);
		SoundManager::GetInstance()->PlaySound("changesound");
	}
	else if (key == KEY_SPACEBAR && bIsPressed)
	{
		if (playerChoice == 1)
		{
			SoundManager::GetInstance()->PlaySound("startgamesound");
			changetoPlay = true;
		}
		else if (playerChoice == 2)
		{
			SoundManager::GetInstance()->PlaySound("startgamesound");
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credits);
		}
		else {
			Application::GetInstance()->Exit();
		}
	}
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
	if (changetoPlay)
	{
		cooldownTimer -= deltaTime;
	}
	if(cooldownTimer<=0)
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_menuHandle->Draw();
	//m_Text_gameName->Draw();
}
