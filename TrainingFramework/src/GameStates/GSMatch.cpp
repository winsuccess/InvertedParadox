#include <sstream>
#include <iomanip>
#include <thread>
#include "GSMatch.h"

GSMatch::GSMatch()
{
#pragma region  Init
	ms = MatchState::STATE_STARTBATTLE;
	playerChoice = 1;
	cooldownTimer = 60;
	actionOnce = false;
	attackG = false;
	attackD = false;
	attackA = false;
	cTurn = 1;
	r = 0;
	rd = 0;
	showDamageRecieved = false;
	updateHealth = true;
	m_MonsterHealthBarlength = 600;
	enemyhealthpos = 690;
	m_CharacterHealthBarlength = 220;
#pragma endregion
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

#pragma region  Characters Stats

	//Player Stats Panel
	texture = ResourceManagers::GetInstance()->GetTexture("match_demo_stats");
	m_PlayerStats = std::make_shared<Sprite2D>(model, shader, texture);
	m_PlayerStats->Set2DPosition(screenwidth / 2, 450);
	m_PlayerStats->SetSize(600, 112);

	//Gumball Stats
	texture = ResourceManagers::GetInstance()->GetTexture("match_healthbar");
	m_GumballHealthBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_GumballHealthBar->Set2DPosition(413, 422);
	m_GumballHealthBar->SetSize(220, 7);
	//Anais Stats
	texture = ResourceManagers::GetInstance()->GetTexture("match_healthbar");
	m_AnaisHealthBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_AnaisHealthBar->Set2DPosition(413, 455);
	m_AnaisHealthBar->SetSize(220, 7);
	//Darwin Stats
	texture = ResourceManagers::GetInstance()->GetTexture("match_healthbar");
	m_DarwinHealthBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_DarwinHealthBar->Set2DPosition(413, 489);
	m_DarwinHealthBar->SetSize(220, 7);
#pragma endregion

	//Enemys
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	texture = ResourceManagers::GetInstance()->GetTexture("match_monsteranim3");
	m_Monster = std::make_shared<Enemy>(model, shader, texture, Vector2(1524,158), Vector2(254, 158), 0, 0, 1);
	m_Monster->SetActive(false);
	m_Monster->Set2DPosition(625, 265);
	m_Monster->SetSize(508 / 1.25, 315 / 1.25);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("match_enemyhealthbar");
	m_MonsterHealthBar = std::make_shared<Sprite2D>(model, shader, texture);
	m_MonsterHealthBar->Set2DPosition(screenwidth / 2-50, 75);
	m_MonsterHealthBar->SetSize(690, 25);

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

	//Enemy Name
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("minecraft");
	m_MonsterName = std::make_shared< Text>(shader, font, "Carnivorous Leslie", TEXT_COLOR::PURPLE, 0.75);
	m_MonsterName->Set2DPosition(25, 105);

	//Enemy Health
	font = ResourceManagers::GetInstance()->GetFont("ttpixel");
	m_MonsterHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 0.6);
	m_MonsterHealth->Set2DPosition(690, 82);
	m_DamageToMonster = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 0.7);
	m_DamageToMonster->Set2DPosition(475, 175);

	//Characters Health

	m_GumballHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::DARKYELLOW, 0.37);
	m_GumballHealth->Set2DPosition(498, 411.5);
	m_DamageToGumball = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 0.5);
	m_DamageToGumball->Set2DPosition(300, 250);

	m_AnaisHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::DARKYELLOW, 0.37);
	m_AnaisHealth->Set2DPosition(498, 445.5);
	m_DamageToAnais = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 0.5);
	m_DamageToAnais->Set2DPosition(190, 270);

	m_DarwinHealth = std::make_shared< Text>(shader, font, "", TEXT_COLOR::DARKYELLOW, 0.37);
	m_DarwinHealth->Set2DPosition(498, 479.5);
	m_DamageToDarwin = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 0.5);
	m_DamageToDarwin->Set2DPosition(130, 255);

#pragma endregion


#pragma endregion

#pragma region  Init Sounds
	SoundManager::GetInstance()->PauseSound("menumusic");
	SoundManager::GetInstance()->PlaySound("bgmusic");
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
			SoundManager::GetInstance()->PlaySound("changesound");
		}
		else if (key == KEY_UP && bIsPressed)
		{
			if (playerChoice == 1)
				playerChoice = 3;
			else
				playerChoice--;
			SoundManager::GetInstance()->PlaySound("changesound");
		}
		else if (key == KEY_SPACEBAR && bIsPressed)
		{
			ms = GSMatch::STATE_PLAYERATTACK;
			SoundManager::GetInstance()->PlaySound("selectsound");
		}
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
	m_Gumball->Update(deltaTime);
	m_Darwin->Update(deltaTime);
	m_Anais->Update(deltaTime);

	m_ChoiceHandle->Set2DPosition(m_ChoiceHandle->Get2DPosition().x, m_listChoiceButton.at(playerChoice - 1)->Get2DPosition().y);

	//Update Match State
	switch (ms)
	{
	case GSMatch::STATE_STARTBATTLE:
		cooldownTimer -= deltaTime;
		if (cooldownTimer <= 0) {
			cooldownTimer = 150;
			ms = STATE_PLAYERTURN;
		}
		break;
	case GSMatch::STATE_PLAYERTURN:
		//if(!actionOnce)
		//	SoundManager::GetInstance()->PlaySound("onturnsound");
		actionOnce = true;
		if (cTurn == 1) {
			m_TurnHandle->Set2DPosition(m_Gumball->Get2DPosition().x - 5, m_Gumball->Get2DPosition().y - 100);
		}
		else if (cTurn == 2) {
			m_TurnHandle->Set2DPosition(m_Anais->Get2DPosition().x, m_Anais->Get2DPosition().y - 90);
		}
		else
		{
			m_TurnHandle->Set2DPosition(m_Darwin->Get2DPosition().x - 10, m_Darwin->Get2DPosition().y - 100);
		}
		break;
	case GSMatch::STATE_PLAYERATTACK:
		if (actionOnce) {
			updateHealth = false;
			if (playerChoice == 1) {
				rd = rand() % 5 + 15;
				SoundManager::GetInstance()->PlaySound("magicattacksound");
				std::stringstream stream;
				if (m_Monster->GetHp() > rd)
					m_Monster->SetHp(-rd);
				else
					m_Monster->SetHp(-m_Monster->GetHp());
				stream << std::fixed << std::setprecision(0) << -rd;
				std::string score = stream.str();
				m_DamageToMonster->setText(score);
				if (m_Monster->GetHp() < 50)
					m_MonsterHealthBar->SetTexture(ResourceManagers::GetInstance()->GetTexture("match_enemyhealthbar2"));
				if(m_Monster->GetHp()==0)
					m_MonsterHealthBar->SetSize(0, m_MonsterHealthBar->GetSize().y);
				else 
					m_MonsterHealthBar->SetSize(m_MonsterHealthBar->GetSize().x - m_MonsterHealthBarlength / 175.0f * rd, m_MonsterHealthBar->GetSize().y);
				m_MonsterHealthBar->Set2DPosition(m_MonsterHealthBar->Get2DPosition().x - m_MonsterHealthBarlength / 175.0f / 2 * rd, m_MonsterHealthBar->Get2DPosition().y);
				m_MonsterHealth->Set2DPosition(m_MonsterHealthBar->Get2DPosition().x/2 +340, 82);
				enemyhealthpos -= 690 / 175.0f / 4 * rd;
			}
			if (playerChoice == 2) {
				SoundManager::GetInstance()->PlaySound("normalattacksound");
				if (m_Monster->GetHp() > 17)
					m_Monster->SetHp(-17);
				else
					m_Monster->SetHp(-m_Monster->GetHp());
				std::stringstream stream;
				stream << std::fixed << std::setprecision(0) << -18;
				std::string score = stream.str();
				m_DamageToMonster->setText(score);
				if (m_Monster->GetHp() < 50)
					m_MonsterHealthBar->SetTexture(ResourceManagers::GetInstance()->GetTexture("match_enemyhealthbar2"));
				if (m_Monster->GetHp() == 0)
					m_MonsterHealthBar->SetSize(0, m_MonsterHealthBar->GetSize().y);
				else
					m_MonsterHealthBar->SetSize(m_MonsterHealthBar->GetSize().x - m_MonsterHealthBarlength / 175.0f * 18, m_MonsterHealthBar->GetSize().y);
				m_MonsterHealthBar->Set2DPosition(m_MonsterHealthBar->Get2DPosition().x - m_MonsterHealthBarlength / 175.0f /2* 18, m_MonsterHealthBar->Get2DPosition().y);
				m_MonsterHealth->Set2DPosition(m_MonsterHealthBar->Get2DPosition().x/2 + 340, 82);
				enemyhealthpos -= 690 / 175.0f / 4 * 18;
			}
			if (playerChoice == 3) {
				r = rand() % 9;
				if (r <= 5)
					rd = 30;
				else
					rd = 10;
				SoundManager::GetInstance()->PlaySound("sienceattacksound");
				if (m_Monster->GetHp() > rd)
					m_Monster->SetHp(-rd);
				else
					m_Monster->SetHp(-m_Monster->GetHp());
				std::stringstream stream;
				stream << std::fixed << std::setprecision(0) << -rd;
				std::string score = stream.str();
				m_DamageToMonster->setText(score);
				if (m_Monster->GetHp() < 50)
					m_MonsterHealthBar->SetTexture(ResourceManagers::GetInstance()->GetTexture("match_enemyhealthbar2"));
				if (m_Monster->GetHp() == 0)
					m_MonsterHealthBar->SetSize(0, m_MonsterHealthBar->GetSize().y);
				else
					m_MonsterHealthBar->SetSize(m_MonsterHealthBar->GetSize().x - m_MonsterHealthBarlength / 175.0f * rd, m_MonsterHealthBar->GetSize().y);
				m_MonsterHealthBar->Set2DPosition(m_MonsterHealthBar->Get2DPosition().x - m_MonsterHealthBarlength / 175.0f / 2 * rd, m_MonsterHealthBar->Get2DPosition().y);
				m_MonsterHealth->Set2DPosition(m_MonsterHealthBar->Get2DPosition().x/2 + 340, 82);
				enemyhealthpos -= 690 / 175.0f / 4 * rd;
			}
			m_Monster->GetHurt();
			actionOnce = false;
		}
		cooldownTimer -= deltaTime;
		if (cooldownTimer <= 100) {
			showDamageRecieved = true;
			updateHealth = true;
		}
		if (cooldownTimer == 60 && m_Monster->GetHp() <= 0) {
			m_Monster->SetAnim(1, 5, 0.75);
			m_Monster->SetActive(true);
		}
		if (cooldownTimer <= 0) {
			showDamageRecieved = false;
			updateHealth = false;
			cooldownTimer = 150;
			if (m_Monster->GetHp() <= 0) {
				actionOnce = true;
				cooldownTimer = 300;
				ms = STATE_ENDBATTLE;
			}
			else if (cTurn == 1 || cTurn == 2) {
				cTurn++;
				ms = STATE_PLAYERTURN;
			}
			else {
				cTurn = 1;
				ms = STATE_ENEMYTURN;
			}
		}
		break;
	case GSMatch::STATE_ENEMYTURN:
		//if (!actionOnce)
		//	SoundManager::GetInstance()->PlaySound("onturnsound");
		actionOnce = true;
		m_TurnHandle->Set2DPosition(m_Monster->Get2DPosition().x + 10, m_Monster->Get2DPosition().y - 150);

		r = rand() % 2;
		rd = rand() % 10 + (m_Monster->GetDamage() - 5);
		ms = STATE_ENEMYATTACK;
		break;
	case GSMatch::STATE_ENEMYATTACK:
		if (actionOnce) {
			SoundManager::GetInstance()->PlaySound("enemyattacksound");
			if (r == 0) {
				r = rand() % 3;
				if (r == 0)
				{
					m_Gumball->GetHurt();
					m_Gumball->SetHp(-2 * rd);
					std::stringstream stream;
					stream << std::fixed << std::setprecision(0) << -2 * rd;
					std::string score = stream.str();
					m_DamageToGumball->setText(score);
					attackG = true;
					std::cout << m_GumballHealthBar->GetSize().x;
					m_GumballHealthBar->SetSize(m_GumballHealthBar->GetSize().x - 220 * rd / 250, m_GumballHealthBar->GetSize().y);
					m_GumballHealthBar->Set2DPosition(m_GumballHealthBar->Get2DPosition().x - m_CharacterHealthBarlength * rd / 500, m_GumballHealthBar->Get2DPosition().y);
				}
				else if (r == 1) {
					m_Anais->GetHurt();
					m_Anais->SetHp(-2 * rd);
					std::stringstream stream;
					stream << std::fixed << std::setprecision(0) << -2 * rd;
					std::string score = stream.str();
					m_DamageToAnais->setText(score);
					attackA = true;
					std::cout << m_AnaisHealthBar->GetSize().x;
					m_AnaisHealthBar->SetSize(m_AnaisHealthBar->GetSize().x - 220 * rd / 250, m_AnaisHealthBar->GetSize().y);
					m_AnaisHealthBar->Set2DPosition(m_AnaisHealthBar->Get2DPosition().x - m_CharacterHealthBarlength * rd / 500, m_AnaisHealthBar->Get2DPosition().y);
				}
				else {
					m_Darwin->GetHurt();
					m_Darwin->SetHp(-2 * rd);
					std::stringstream stream;
					stream << std::fixed << std::setprecision(0) << -2 * rd;
					std::string score = stream.str();
					m_DamageToDarwin->setText(score);
					attackD = true;
					std::cout << m_DarwinHealthBar->GetSize().x;
					m_DarwinHealthBar->SetSize(m_DarwinHealthBar->GetSize().x - 220 * rd / 250, m_DarwinHealthBar->GetSize().y);
					m_DarwinHealthBar->Set2DPosition(m_DarwinHealthBar->Get2DPosition().x - m_CharacterHealthBarlength * rd / 500, m_DarwinHealthBar->Get2DPosition().y);

				}
			}
			else
			{
				m_Gumball->GetHurt();
				m_Anais->GetHurt();
				m_Darwin->GetHurt();
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
				m_GumballHealthBar->SetSize(m_GumballHealthBar->GetSize().x - m_CharacterHealthBarlength * rd / 500, m_GumballHealthBar->GetSize().y);
				m_AnaisHealthBar->SetSize(m_AnaisHealthBar->GetSize().x - m_CharacterHealthBarlength * rd / 500, m_AnaisHealthBar->GetSize().y);
				m_DarwinHealthBar->SetSize(m_DarwinHealthBar->GetSize().x - m_CharacterHealthBarlength * rd / 500, m_DarwinHealthBar->GetSize().y);
				m_GumballHealthBar->Set2DPosition(m_GumballHealthBar->Get2DPosition().x - m_CharacterHealthBarlength * rd / 1000, m_GumballHealthBar->Get2DPosition().y);
				m_AnaisHealthBar->Set2DPosition(m_AnaisHealthBar->Get2DPosition().x - m_CharacterHealthBarlength * rd / 1000, m_AnaisHealthBar->Get2DPosition().y);
				m_DarwinHealthBar->Set2DPosition(m_DarwinHealthBar->Get2DPosition().x - m_CharacterHealthBarlength * rd / 1000, m_DarwinHealthBar->Get2DPosition().y);
			}
			actionOnce = false;
		}
		cooldownTimer -= deltaTime;
		if (cooldownTimer <= 150) {
			showDamageRecieved = true;
			updateHealth = true;
		}
		if (cooldownTimer <= 0) {
			attackG = false;
			attackA = false;
			attackD = false;
			cooldownTimer = 150;
			showDamageRecieved = false;
			updateHealth = false;
			ms = STATE_PLAYERTURN;
		}
		break;
	case GSMatch::STATE_ENDBATTLE:
		m_TurnHandle->Set2DPosition(-100, -100);
		m_Monster->SetAlive(false);
		if (actionOnce) {
			SoundManager::GetInstance()->PauseSound("bgmusic");
			SoundManager::GetInstance()->PlaySound("weditit");
			actionOnce = false;
		}
		cooldownTimer -= deltaTime;
		if (cooldownTimer <= 0) {
			SoundManager::GetInstance()->PlaySound("menumusic");
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		}
		break;
	default:
		break;
	}

#pragma region Update Stats
	if (updateHealth) {
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
	}
#pragma endregion


	//When you win

	//When you lose

}

void GSMatch::Draw()
{
	m_BackGround->Draw();

	m_Gumball->Draw();
	m_Anais->Draw();
	m_Darwin->Draw();
	if (ms!= GSMatch::STATE_ENDBATTLE)
		m_Monster->Draw();

	//UI
	m_PlayerStats->Draw();
	m_TurnHandle->Draw();

	if (m_Monster->IsAlive()) {
		m_MonsterName->Draw();
		m_MonsterHealth->Draw();
		m_MonsterHealthBar->Draw();
	}

	m_GumballHealth->Draw();
	m_AnaisHealth->Draw();
	m_DarwinHealth->Draw();

	m_GumballHealthBar->Draw();
	m_AnaisHealthBar->Draw();
	m_DarwinHealthBar->Draw();

	if (ms == GSMatch::STATE_PLAYERATTACK && showDamageRecieved)
		m_DamageToMonster->Draw();
	if (showDamageRecieved) {
		if (attackG)
		{
			m_DamageToGumball->Draw();
		}
		if (attackA)
		{
			m_DamageToAnais->Draw();
		}
		if (attackD)
		{
			m_DamageToDarwin->Draw();
		}
	}

	//Draw Player Choice Panel
	if (ms == MatchState::STATE_PLAYERTURN) {
		m_ChoicePanel->Draw();
		for (auto it : m_listChoiceButton)
			it->Draw();
		m_ChoiceHandle->Draw();
	}
}
