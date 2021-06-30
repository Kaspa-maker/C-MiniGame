#pragma once
#include "player.h"
#include<string>
#include<sstream>
#include<map>
#include "Laser.h"
#include "Enemy.h"
#include<SFML/Audio.hpp>

class Game
{
private:
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*> textures;
	std::vector<Laser*> lasers;
	player* Player;

	std::vector<Enemy*> enemies;
	Enemy* enemy;
	float spawner;
	float spawnerMax;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;

	sf::Font font;
	sf::Text scoreText;
	sf::Text healthText;
	unsigned score;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;

	sf::Sprite healthSprite;
	sf::Texture healthTexture;

	sf::Sprite healthSprite1;
	sf::Texture healthTexture1;

	sf::Sprite healthSprite2;
	sf::Texture healthTexture2;

	void initializeWindow();
	void initializeScore();
	void initializeTextures();
	void initializePlayer();
	void initializeEnemy();
	void initializeGUI();
	void initializeScene();
	void initializeSoundEffect();
	void initializeMusic();

public:
	Game();

	void run();
	void updatePollEvents();
	void updatePlayerInput();
	void updateLaser();
	void updateEnemy();
	void updateGUI();
	void updateGame();
	void renderGame();
	void renderGUI();
	void renderScene();
	void musicSound();
	void soundEffect();
};

