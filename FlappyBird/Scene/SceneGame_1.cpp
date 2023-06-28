#include "stdafx.h"
#include "SceneGame_1.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"

#include "PFUnitGo.h"
#include "TextGo.h"



SceneGame::SceneGame() : Scene(SceneId::Game1),getSco1(true), getSco2(true), score(0), 
bestScore(0), speed(0), isPause(true)
{
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/player4.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/rip.png"));
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	Release();
	AddGo(new PFUnitGo("Player"));
	AddGo(new TextGo("Score"));
	AddGo(new TextGo("BestScore"));
	for (int i = 0; i < 10; i++)
	{
		std::string str = "Block" + std::to_string(i);
		AddGo(new BlockGo(str));
	}

	for (auto go : gameObjects)
	{
		go->Init();
	}


}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();
	float rand = 0.f;
	score = 0;
	getSco1 = true;
	getSco2 = true;
	speed = 0;
	isPause = true;

	TextGo* findTGo = (TextGo*)FindGo("Score");
	findTGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	findTGo->text.setString("PRESS SPACE TO START");
	findTGo->text.setCharacterSize(75);
	findTGo->text.setFillColor(sf::Color::White);
	Utils::SetOrigin(findTGo->text, Origins::TL);
	findTGo->text.setPosition(50.f,20.f);


	findTGo = (TextGo*)FindGo("BestScore");
	findTGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	std::string bsco = "Best : " + std::to_string(bestScore);
	findTGo->text.setString(bsco);
	findTGo->text.setCharacterSize(75);
	findTGo->text.setFillColor(sf::Color::White);
	Utils::SetOrigin(findTGo->text, Origins::BL);
	findTGo->text.setPosition(50.f, FRAMEWORK.GetWindowSize().y - 100.f);

	//위
	std::string str = "Block0";
	BlockGo* findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(FRAMEWORK.GetWindowSize().x, 30.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5,
		findBGo->rectangle.getSize().y/2);
	findBGo->rectangle.setFillColor(sf::Color::White);

	//아래
	str = "Block1";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(FRAMEWORK.GetWindowSize().x, 30.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5,
		FRAMEWORK.GetWindowSize().y -(findBGo->rectangle.getSize().y / 2));
	findBGo->rectangle.setFillColor(sf::Color::White);

	//왼쪽
	str = "Block2";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(30.f, FRAMEWORK.GetWindowSize().y));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(findBGo->rectangle.getSize().x / 2,
		FRAMEWORK.GetWindowSize().y*0.5);
	findBGo->rectangle.setFillColor(sf::Color::White);

	//오른쪽
	str = "Block3";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(30.f, FRAMEWORK.GetWindowSize().y));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x - (findBGo->rectangle.getSize().x / 2),
		FRAMEWORK.GetWindowSize().y * 0.5);
	findBGo->rectangle.setFillColor(sf::Color::White);

	//나머지블록들
	str = "Block4";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(100.f, 350.f));
	findBGo->SetOrigin(Origins::MC);
	rand = Utils::RandomRange(-0.2f, 0.2f);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 1.2,
		FRAMEWORK.GetWindowSize().y * (0.05+rand));
	findBGo->rectangle.setFillColor(sf::Color::White);

	str = "Block5";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(100.f, 350.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 1.2,
		FRAMEWORK.GetWindowSize().y * (0.95+rand));
	findBGo->rectangle.setFillColor(sf::Color::White);


	str = "Block6";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(100.f, 350.f));
	findBGo->SetOrigin(Origins::MC);
	rand = Utils::RandomRange(-0.2f, 0.2f);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 1.7,
		FRAMEWORK.GetWindowSize().y * (0.05 + rand));
	findBGo->rectangle.setFillColor(sf::Color::White);

	str = "Block7";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(100.f, 350.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 1.7,
		FRAMEWORK.GetWindowSize().y * (0.95 + rand));
	findBGo->rectangle.setFillColor(sf::Color::White);



	findBGo = (BlockGo*)FindGo("Block1");
	PFUnitGo* findPlayer = (PFUnitGo*)FindGo("Player");
	findPlayer->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/player4.png"));
	findPlayer->SetSize(0.3f, 0.3f);
	findPlayer->SetOrigin(Origins::BC);
	findPlayer->SetPosition(findBGo->GetPosition().x, 
		findBGo->GetPosition().y /2);
}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	TextGo* findTGo = (TextGo*)FindGo("Score");
	PFUnitGo* findPlayer = (PFUnitGo*)FindGo("Player");

	if (isPause)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			isPause = false;
		}
		return;
	}

	if (findPlayer->IsDead())
	{
		findPlayer->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/rip.png"));
		TextGo* findTGo = (TextGo*)FindGo("Score");
		findTGo->text.setString("GameOver");
		findTGo->text.setFillColor(sf::Color::Red);
		if (INPUT_MGR.GetKey(sf::Keyboard::Space))
		{
			Enter();
		}
		return;
	}
	
	findTGo->text.setString(std::to_string(score));
	findTGo = (TextGo*)FindGo("BestScore");
	std::string bsco = "Best : " + std::to_string(bestScore);
	findTGo->text.setString(bsco);
	if (bestScore < score)
	{
		bestScore = score;
		findTGo->text.setFillColor(sf::Color::Green);
	}

	for (int i = 0; i < 8; i++)
	{
		std::string str = "Block" + std::to_string(i);
		BlockGo* findBGo = (BlockGo*)FindGo(str);
		findPlayer->CheckBlock(findBGo);
	}
	for (int i = 4; i < 8; i++)
	{
		std::string str = "Block" + std::to_string(i);
		BlockGo* findBGo = (BlockGo*)FindGo(str);
		findBGo->SetPosition(findBGo->GetPosition().x - (speed+100.f * dt),
			findBGo->GetPosition().y);
		if (findBGo->GetPosition().x < 0 && i % 2 == 0)
		{
			float rand = Utils::RandomRange(-0.2f, 0.2f);
			findBGo->SetPosition(FRAMEWORK.GetWindowSize().x,
				FRAMEWORK.GetWindowSize().y * (0.05 + rand));

			std::string str = "Block" + std::to_string(i+1);
			BlockGo* findBGo = (BlockGo*)FindGo(str);
			findBGo->SetPosition(FRAMEWORK.GetWindowSize().x,
				FRAMEWORK.GetWindowSize().y * (0.95 + rand));
			if (i == 4)
			{
				getSco1 = true;
			}
			else if (i == 6)
			{
				getSco2 = true;
			}
		}
	}
	BlockGo* findBGo = (BlockGo*)FindGo("Block4");
	if (findPlayer->sprite.getPosition().x > findBGo->GetPosition().x && getSco1)
	{
		getSco1 = false;
		score++;
		speed += 0.03f;
	}
	findBGo = (BlockGo*)FindGo("Block6");
	if (findPlayer->sprite.getPosition().x > findBGo->GetPosition().x && getSco2)
	{
		getSco2 = false;
		score++;
		speed += 0.03f;
	}

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}

