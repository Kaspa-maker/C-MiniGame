#include "Game.h"
#include<iostream>

void Game::initializeWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Earth Demise");
	window->setFramerateLimit(60);
}

void Game::initializeScore()
{
	score = 0;
}

void Game::initializeTextures()
{
	textures["LASER"] = new sf::Texture();
	textures["LASER"]->loadFromFile("textures/laser.png");
}

void Game::initializePlayer()
{
	Player = new player();
}

void Game::initializeEnemy()
{
	spawnerMax = 50.f;
	spawner = spawnerMax;
}

void Game::initializeGUI()
{
	font.loadFromFile("fonts/American Captain.ttf");
	healthTexture.loadFromFile("textures/player1.png");
	healthTexture1.loadFromFile("textures/player1.png");
	healthTexture2.loadFromFile("textures/player1.png");

	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::Red);
	
	healthText.setFont(font);
	healthText.setCharacterSize(50);
	healthText.setFillColor(sf::Color::Red);
	healthText.setPosition(500, 0);

	healthSprite.setTexture(healthTexture);
	healthSprite1.setTexture(healthTexture1);
	healthSprite2.setTexture(healthTexture2);

	healthSprite.setScale(0.05f, 0.05f);
	healthSprite1.setScale(0.05f, 0.05f);
	healthSprite2.setScale(0.05f, 0.05f);

	healthSprite.setPosition(750, 10);
	healthSprite1.setPosition(700, 10);
	healthSprite2.setPosition(650, 10);

	healthSprite.setColor(sf::Color::Red);
	healthSprite1.setColor(sf::Color::Yellow);
	healthSprite2.setColor(sf::Color::Green);

}

void Game::initializeScene()
{
	backgroundTexture.loadFromFile("textures/background.jpg");
	backgroundSprite.setTexture(backgroundTexture);
}

void Game::initializeSoundEffect()
{
	if(!buffer.loadFromFile("sound/laserShot.ogg"))
	{
		std::cout << "ERROR";
	}

	sound.setBuffer(buffer);
}

void Game::initializeMusic()
{
	if (!music.openFromFile("music/spaceMusic.wav"))
	{
		std::cout << "ERROR"; // error
	}
	music.play();
	music.setLoop(true);
	
}

Game::Game()
{
	initializeWindow();
	initializeTextures();
	initializeGUI();
	initializeScore();
	initializePlayer();
	initializeEnemy();
	initializeScene();
	initializeSoundEffect();
	initializeMusic();
}



void Game::run()
{
	musicSound();
	while (window->isOpen()) 
	{
		updateGame();
		renderGame();
	}
}



void Game::updatePollEvents()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			window->close();
	}
}

void Game::updatePlayerInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		Player->moveShip(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		Player->moveShip(1.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		lasers.push_back(new Laser(textures["LASER"], -1.f, 10.f, Player->getPosition().x + Player->getBounds().width/3.5f, Player->getPosition().y - 20));	
		soundEffect();
	}
}

void Game::updateLaser()
{
	unsigned counter = 0;
	for (auto* laser : lasers)
	{
		laser->updateLaser();

		if (laser->getBounds().top + laser->getBounds().height < 0.f)
		{
			delete lasers.at(counter);
			lasers.erase(lasers.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateEnemy()
{

	spawner += 0.5f;
	if (spawner >= spawnerMax)
	{
		enemies.push_back(new Enemy(rand() %window->getSize().x + 2.f, 0.f));
		spawner = 0.f;
	}

	unsigned counter = 0;
	for (auto* enemy : enemies)
	{
		enemy->updateEnemy();

		if (enemy->getBounds().top > window->getSize().y)
		{
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			--counter;
		}
		else if(enemy->getBounds().intersects(Player->getBounds()))
		{
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
			
			if (healthSprite2.getColor() != sf::Color::Transparent)
			{
				healthSprite2.setColor(sf::Color::Transparent);
			}
			else if((healthSprite2.getColor() == sf::Color::Transparent) && (healthSprite1.getColor() != sf::Color::Transparent))
			{
				healthSprite1.setColor(sf::Color::Transparent);
			}
			else
			{
				healthSprite.setColor(sf::Color::Transparent);
				std::cout << "GAME OVER YOU LOSE";
				window->close();
			}
			
			--counter;
		}

		++counter;
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		bool enemyRemoved = false;
		enemies[i]->updateEnemy();

		for (size_t k = 0; k < lasers.size() && !enemyRemoved; k++)
		{
			if (lasers[k]->getBounds().intersects(enemies[i]->getBounds()))
			{
				score += enemies[i]->getScore();
				lasers.erase(lasers.begin() + k);
				enemies.erase(enemies.begin() + i);
				
				enemyRemoved = true;
			}
		}
		
		if (!enemyRemoved)
		{
			if (enemies[i]->getBounds().top > window->getSize().y)
			{
				enemies.erase(enemies.begin() + i);
				enemyRemoved = true;
			}
		}
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	std::stringstream ss1;
	ss << "Score: " << score;
	ss1 << "Health: ";
	scoreText.setString(ss.str());
	healthText.setString(ss1.str());
}

void Game::updateGame()
{
	updatePollEvents();
	updatePlayerInput();
	updateLaser();
	updateEnemy();
	updateGUI();
}

void Game::renderGame()
{
	window->clear();
	renderScene();
	Player->renderPlayer(*window);
	for (auto* laser : lasers)
	{
		laser->renderLaser(window);
	}

	for (auto* enemy : enemies)
	{
		enemy->renderEnemy(*window);
	}
	
	renderGUI();
	window->display();
}

void Game::renderGUI()
{
	window->draw(scoreText);
	window->draw(healthText);
	window->draw(healthSprite);
	window->draw(healthSprite1);
	window->draw(healthSprite2);
}

void Game::renderScene()
{
	window->draw(backgroundSprite);
}

void Game::musicSound()
{
	
}

void Game::soundEffect()
{
	sound.play();
}
