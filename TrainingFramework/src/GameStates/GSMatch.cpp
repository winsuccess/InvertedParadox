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
	//Gumball
	texture = ResourceManagers::GetInstance()->GetTexture("match_gumball");
	m_Gumball = std::make_shared<Character>(model, shader, texture);
	m_Gumball->Set2DPosition(270, 318);
	m_Gumball->SetSize(181 / 2, 260 / 2);
	//Darwin
	texture = ResourceManagers::GetInstance()->GetTexture("match_darwin");
	m_Darwin = std::make_shared<Character>(model, shader, texture);
	m_Darwin->Set2DPosition(129, 340);
	m_Darwin->SetSize(248 / 2, 239 / 2);
	//Anais
	texture = ResourceManagers::GetInstance()->GetTexture("match_anais");
	m_Anais = std::make_shared<Character>(model, shader, texture);
	m_Anais->Set2DPosition(200, 338);
	m_Anais->SetSize(185 / 2, 202 / 2);
#pragma endregion

	//Enemys
	texture = ResourceManagers::GetInstance()->GetTexture("match_monster1");
	m_Monster = std::make_shared<Enemy>(model, shader, texture);
	m_Monster->Set2DPosition(630, 260);
	m_Monster->SetSize(508 / 1.25, 315 / 1.25);


	//Player Stats Panel
	texture = ResourceManagers::GetInstance()->GetTexture("match_demo_stats");
	m_PlayerStats = std::make_shared<Sprite2D>(model, shader, texture);
	m_PlayerStats->Set2DPosition(screenwidth / 2, 450);
	m_PlayerStats->SetSize(600, 112);

	//Turn Handle
	texture = ResourceManagers::GetInstance()->GetTexture("match_turn_handle");
	m_TurnHandle = std::make_shared<Sprite2D>(model, shader, texture);
	m_TurnHandle->Set2DPosition(-100, -100);
	m_TurnHandle->SetSize(74 / 2, 20);

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
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ttpixel");
	m_MonsterHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_MonsterHealth->Set2DPosition(550, 125);
	m_DamageToMonster = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_DamageToMonster->Set2DPosition(475, 175);

	//Characters Health

	m_GumballHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_GumballHealth->Set2DPosition(270, 218);
	m_DamageToGumball = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_DamageToGumball->Set2DPosition(290, 218);

	m_AnaisHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_AnaisHealth->Set2DPosition(200, 238);
	m_DamageToAnais = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_DamageToAnais->Set2DPosition(220, 238);

	m_DarwinHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_DarwinHealth->Set2DPosition(129, 240);
	m_DamageToDarwin = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_DamageToDarwin->Set2DPosition(150, 240);

#pragma endregion


#pragma endregion

#pragma region  Init Other
	ms = MatchState::STATE_PLAYERTURN;
	playerChoice = 1;
	cooldownTimer = 60;
	actionOnce = false;
	attackG = false;
	attackD = false;
	attackA = false;
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
		else if (key == KEY_SPACEBAR && bIsPressed)
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
	m_Monster->Update(deltaTime);

	m_ChoiceHandle->Set2DPosition(m_ChoiceHandle->Get2DPosition().x, m_listChoiceButton.at(playerChoice - 1)->Get2DPosition().y);

	//Update Match State
	switch (ms)
	{

	case GSMatch::STATE_PLAYERTURN:
		actionOnce = true;
		m_TurnHandle->Set2DPosition(m_Gumball->Get2DPosition().x, m_Gumball->Get2DPosition().y - 100);
		break;
	case GSMatch::STATE_PLAYERATTACK:
		if (actionOnce) {
			if (playerChoice == 1) {
				m_Monster->SetHp(-10);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(0) << -10;
				std::string score = stream.str();
				m_DamageToMonster->setText(score);
			}
			if (playerChoice == 2) {
				m_Monster->SetHp(-20);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(0) << -20;
				std::string score = stream.str();
				m_DamageToMonster->setText(score);
			}
			if (playerChoice == 3) {
				m_Monster->SetHp(-30);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(0) << -30;
				std::string score = stream.str();
				m_DamageToMonster->setText(score);
			}
			actionOnce = false;
		}
		cooldownTimer -= deltaTime;
		if (cooldownTimer <= 0) {
			cooldownTimer = 60;
			ms = STATE_ENEMYTURN;
		}
		break;
	case GSMatch::STATE_ENEMYTURN:
		actionOnce = true;
		m_TurnHandle->Set2DPosition(m_Monster->Get2DPosition().x, m_Monster->Get2DPosition().y - 180);

		r = rand() % 1;
		rd = rand() % 10 + (m_Monster->GetDamage() - 5);
		ms = STATE_ENEMYATTACK;
		break;
	case GSMatch::STATE_ENEMYATTACK:
		if (actionOnce) {
			if (r == 0) {
				r = rand() % 3;
				if (r == 0)
				{
					m_Gumball->SetHp(-2 * rd);
					std::stringstream stream;
					stream << std::fixed << std::setprecision(0) << -2 * rd;
					std::string score = stream.str();
					m_DamageToGumball->setText(score);
					attackG = true;
				}
				else if (r == 1) {
					m_Darwin->SetHp(-2 * rd);
					std::stringstream stream;
					stream << std::fixed << std::setprecision(0) << -2 * rd;
					std::string score = stream.str();
					m_DamageToDarwin->setText(score);
					attackA = true;
				}
				else {
					m_Anais->SetHp(-2 * rd);
					std::stringstream stream;
					stream << std::fixed << std::setprecision(0) << -2 * rd;
					std::string score = stream.str();
					m_DamageToAnais->setText(score);
					attackD = true;
				}
			}
			else
			{
				m_Gumball->SetHp(-rd);
				m_Darwin->SetHp(-rd);
				m_Anais->SetHp(-rd);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(0) << -rd;
				std::string score = stream.str();
				m_DamageToGumball->setText(score);
				std::stringstream stream2;
				stream2 << std::fixed << std::setprecision(0) << -rd;
				score = stream2.str();
				m_DamageToAnais->setText(score);
				std::stringstream stream3;
				stream3 << std::fixed << std::setprecision(0) << -rd;
				score = stream3.str();
				m_DamageToDarwin->setText(score);
				attackG = true;
				attackA = true;
				attackD = true;
			}
			actionOnce = false;
		}
		cooldownTimer -= deltaTime;
		if (cooldownTimer <= 0) {
			attackG = false;
			attackA = false;
			attackD = false;
			cooldownTimer = 60;
			ms = STATE_PLAYERTURN;
		}
		break;
	default:
		break;
	}

#pragma region Update Stats
	//Update Stats
	std::stringstream stream;
	std::stringstream stream1;
	std::stringstream stream2;
	std::stringstream stream3;
	std::string score;

	//Gumball Stats
	stream1 << std::fixed << std::setprecision(0) << m_Gumball->GetHp();
	score = stream1.str();
	m_GumballHealth->setText(score);

	//Anais Stats
	stream2 << std::fixed << std::setprecision(0) << m_Anais->GetHp();
	score = stream2.str();
	m_AnaisHealth->setText(score);

	//Darwin Stats
	stream3 << std::fixed << std::setprecision(0) << m_Darwin->GetHp();
	score = stream3.str();
	m_DarwinHealth->setText(score);

	//Enemy Stats
	stream << std::fixed << std::setprecision(0) << m_Monster->GetHp();
	score = stream.str();
	m_MonsterHealth->setText(score);
#pragma endregion


	//When you win
	if (!m_Monster->IsAlive())
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);

	//When you lose

}

void GSMatch::Draw()
{
	m_BackGround->Draw();

	m_Gumball->Draw();
	m_Anais->Draw();
	m_Darwin->Draw();
	m_Monster->Draw();

	//UI
	m_PlayerStats->Draw();
	m_TurnHandle->Draw();
	m_MonsterHealth->Draw();
	m_GumballHealth->Draw();
	m_AnaisHealth->Draw();
	m_DarwinHealth->Draw();
	if (ms == GSMatch::STATE_PLAYERATTACK)
		m_DamageToMonster->Draw();
	if (attackG)
		m_DamageToGumball->Draw();
	if (attackA)
		m_DamageToAnais->Draw();
	if (attackD)
		m_DamageToDarwin->Draw();

	//Draw Player Choice Panel
	if (ms == MatchState::STATE_PLAYERTURN) {
		m_ChoicePanel->Draw();
		for (auto it : m_listChoiceButton)
			it->Draw();
		m_ChoiceHandle->Draw();
	}
}
