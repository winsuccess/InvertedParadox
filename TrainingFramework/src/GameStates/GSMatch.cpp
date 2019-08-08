#include <sstream>
#include <iomanip>
#include <thread>
#include "GSMatch.h"

GSMatch::GSMatch()
{

}


GSMatch::~GSMatch()
{
}



void GSMatch::Init()
{
#pragma region  Init Objects

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	auto texture = ResourceManagers::GetInstance()->GetTexture("match_bg1");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenwidth / 2, screenheight / 2);
	m_BackGround->SetSize(screenwidth, screenheight);

#pragma region Characters

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
#pragma endregion

	//Enemys

	texture = ResourceManagers::GetInstance()->GetTexture("");
	m_Monster = std::make_shared<Enemy>(model, shader, texture);
	m_Monster->Set2DPosition(screenwidth / 2, screenheight / 2);
	m_Monster->SetSize(screenwidth, screenheight);

	//Player Stats
	texture = ResourceManagers::GetInstance()->GetTexture("match_demo_stats");
	m_PlayerStats = std::make_shared<Sprite2D>(model, shader, texture);
	m_PlayerStats->Set2DPosition(screenwidth / 2, 450);
	m_PlayerStats->SetSize(600, 112);

#pragma region ChoiceUI
	//Choice UI
	texture = ResourceManagers::GetInstance()->GetTexture("match_choice_panel");
	m_ChoicePanel = std::make_shared<Sprite2D>(model, shader, texture);
	m_ChoicePanel->Set2DPosition(425, 450);
	m_ChoicePanel->SetSize(178, 155);

	texture = ResourceManagers::GetInstance()->GetTexture("match_button_magic");
	std::shared_ptr<GameButton> magicButton = std::make_shared<GameButton>(model, shader, texture);
	magicButton->Set2DPosition(430, 435);
	magicButton->SetSize(114, 29);
	magicButton->SetOnClick([]() {
		});
	m_listChoiceButton.push_back(magicButton);

	texture = ResourceManagers::GetInstance()->GetTexture("match_button_item");
	std::shared_ptr<GameButton> itemButton = std::make_shared<GameButton>(model, shader, texture);
	itemButton->Set2DPosition(430, 463);
	itemButton->SetSize(114, 29);
	itemButton->SetOnClick([]() {

		});
	m_listChoiceButton.push_back(itemButton);

	texture = ResourceManagers::GetInstance()->GetTexture("match_button_science");
	std::shared_ptr<GameButton> sienceButton = std::make_shared<GameButton>(model, shader, texture);
	sienceButton->Set2DPosition(430, 491);
	sienceButton->SetSize(114, 29);
	sienceButton->SetOnClick([]() {

		});
	m_listChoiceButton.push_back(sienceButton);

	texture = ResourceManagers::GetInstance()->GetTexture("match_choice_handle");
	m_ChoiceHandle = std::make_shared<Sprite2D>(model, shader, texture);
	m_ChoiceHandle->Set2DPosition(365, 435);
	m_ChoiceHandle->SetSize(16, 25);
#pragma endregion

#pragma region Texts
	//Enemy Health
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_MonsterHealth = std::make_shared< Text>(shader, font,"", TEXT_COLOR::RED, 1.0);
	m_MonsterHealth->Set2DPosition(550,125);
	m_DamageToMonster = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_DamageToMonster->Set2DPosition(475, 175);

#pragma endregion


#pragma endregion

#pragma region  Init Other
	ms = MatchState::STATE_PLAYERTURN;
	playerChoice = 1;
#pragma endregion

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
	switch (ms)
	{
	case GSMatch::STATE_PLAYERTURN:
		if (key == KEY_DOWN && bIsPressed)
		{
			if (playerChoice == 3)
				playerChoice = 1;
			else
				playerChoice++;
		}
		else if (key == KEY_UP && bIsPressed)
		{
			if (playerChoice == 1)
				playerChoice = 3;
			else
				playerChoice--;
		}
		else if (key == KEY_ENTER && bIsPressed)
			ms = GSMatch::STATE_PLAYERATTACK;
		break;
	case GSMatch::STATE_PLAYERATTACK:
		break;
	case GSMatch::STATE_ENEMYTURN:
		break;
	case GSMatch::STATE_ENEMYATTACK:
		break;
	default:
		break;
	}
}

void GSMatch::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	
}

void GSMatch::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);

	m_ChoiceHandle->Set2DPosition(m_ChoiceHandle->Get2DPosition().x, m_listChoiceButton.at(playerChoice-1)->Get2DPosition().y);

	switch (ms)
	{
	case GSMatch::STATE_PLAYERTURN:
		break;
	case GSMatch::STATE_PLAYERATTACK:
		if (playerChoice == 1) {
			m_Monster->SetHp(-10);
			std::stringstream stream;
			stream << std::fixed << std::setprecision(0) << 10;
			std::string score = stream.str();
			m_DamageToMonster->setText(score);
		}
		if (playerChoice == 2) {
			m_Monster->SetHp(-20);
			std::stringstream stream;
			stream << std::fixed << std::setprecision(0) << 20;
			std::string score = stream.str();
			m_DamageToMonster->setText(score);
		}
		if (playerChoice == 3) {
			m_Monster->SetHp(-30);
			std::stringstream stream;
			stream << std::fixed << std::setprecision(0) << 30;
			std::string score = stream.str();
			m_DamageToMonster->setText(score);
		}
		ms = STATE_ENEMYTURN;
		break;
	case GSMatch::STATE_ENEMYTURN:
		break;
	case GSMatch::STATE_ENEMYATTACK:
		break;
	default:
		break;
	}

	//update Stats
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_Monster->GetHp();
	std::string score = stream.str();
	m_MonsterHealth->setText(score);
	
}

void GSMatch::Draw()
{
	m_BackGround->Draw();

	//m_Gumball->Draw();
	//m_Darwin->Draw();
	//m_Anais->Draw();

	//UI
	m_PlayerStats->Draw();
	m_MonsterHealth->Draw();
	//if (ms == MatchState::STATE_PLAYERATTACK)
		m_DamageToMonster->Draw();

	//Draw Player Choice Panel
	if (ms==MatchState::STATE_PLAYERTURN) {
		m_ChoicePanel->Draw();
		for (auto it : m_listChoiceButton)
			it->Draw();
		m_ChoiceHandle->Draw();
	}
}
