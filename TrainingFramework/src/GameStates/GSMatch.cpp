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

	//Characters
	////Gumball
	//texture = ResourceManagers::GetInstance()->GetTexture("");
	//m_Gumball = std::make_shared<Sprite2D>(model, shader, texture);
	//m_Gumball->Set2DPosition(screenwidth / 2, screenheight / 2);
	//m_Gumball->SetSize(screenwidth, screenheight);
	////Darwin
	//texture = ResourceManagers::GetInstance()->GetTexture("");
	//m_Darwin = std::make_shared<Sprite2D>(model, shader, texture);
	//m_Darwin->Set2DPosition(screenwidth / 2, screenheight / 2);
	//m_Darwin->SetSize(screenwidth, screenheight);
	////Anais
	//texture = ResourceManagers::GetInstance()->GetTexture("");
	//m_Anais = std::make_shared<Sprite2D>(model, shader, texture);
	//m_Anais->Set2DPosition(screenwidth / 2, screenheight / 2);
	//m_Anais->SetSize(screenwidth, screenheight);

	//Player Stats
	texture = ResourceManagers::GetInstance()->GetTexture("match_demo_stats");
	m_PlayerStats = std::make_shared<Sprite2D>(model, shader, texture);
	m_PlayerStats->Set2DPosition(screenwidth / 2, 450);
	m_PlayerStats->SetSize(600.0f, 112.0f);

	//Choice UI
	texture = ResourceManagers::GetInstance()->GetTexture("match_choice_panel");
	m_ChoicePanel = std::make_shared<Sprite2D>(model, shader, texture);
	m_ChoicePanel->Set2DPosition(420 , 450);
	m_ChoicePanel->SetSize(178, 155);

	texture = ResourceManagers::GetInstance()->GetTexture("match_button_magic");
	std::shared_ptr<GameButton> magicButton = std::make_shared<GameButton>(model, shader, texture);
	magicButton->Set2DPosition(420, 435);
	magicButton->SetSize(114.0f, 28.8f);
	magicButton->SetOnClick([]() {

		});
	m_listChoiceButton.push_back(magicButton);

	texture = ResourceManagers::GetInstance()->GetTexture("match_button_item");
	std::shared_ptr<GameButton> itemButton = std::make_shared<GameButton>(model, shader, texture);
	itemButton->Set2DPosition(420, 463);
	itemButton->SetSize(114.0f, 28.8f);
	itemButton->SetOnClick([]() {

		});
	m_listChoiceButton.push_back(itemButton);

	texture = ResourceManagers::GetInstance()->GetTexture("match_button_science");
	std::shared_ptr<GameButton> sienceButton = std::make_shared<GameButton>(model, shader, texture);
	sienceButton->Set2DPosition(420, 491);
	sienceButton->SetSize(114.0f, 28.8f);
	sienceButton->SetOnClick([]() {
		
		});
	m_listChoiceButton.push_back(sienceButton);

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

	//m_Gumball->Draw();
	//m_Darwin->Draw();
	//m_Anais->Draw();

	m_PlayerStats->Draw();

	//Draw Choices
	m_ChoicePanel->Draw();
	for (auto it : m_listChoiceButton)
		it->Draw();
}
