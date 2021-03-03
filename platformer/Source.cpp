#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 
#include "Player.h"
#include "coin.h"
#include "Animation.h"
#include "ParticleSystem.h"

/// <summary>
/// NAMES
/// Davids jalisevs /// Aeden Moylan 
/// Platformer
/// </summary>

class Game
{
public:
	Player player;
	Coin coin;

	ParticleSystem particlesSystem;
	Particle particles;

	sf::Texture playerTextureSheet;
	sf::Sprite playerSpriteSheet;

	sf::Texture coinTextureSheet;
	sf::Sprite coinSpriteSheet;
	sf::Text scoreText;
	sf::Font font;

	int score = 0;
	float playerOffset = 35.0f;
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;

	bool coinIsCollected = false;
	bool stopDrawingCoin = false;

	sf::RectangleShape playerShape;


	float velocityX = 0, velocityY = 0, gravity = 0.3;
	float pixelsPerMeter = 2.4;
	sf::Vector2f pushOff{ 0, -5 * pixelsPerMeter };


	static const int numRows = 55;
	static const int numCols = 20;
	int levelData[numRows][numCols] =
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0 },
	{ 2,0,0,0,0,0,0,3,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 2,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0 },
	{ 2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,2,0,0,0,0,0,0,0,1 },
	{ 0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1 },
	{ 0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	sf::RectangleShape level[numRows][numCols];

	Game()
		: window(sf::VideoMode(800, 600, 32), "SFML Playground", sf::Style::Default),
		player(playerSpriteSheet),
		coin(coinSpriteSheet)
	{
	
		if (!font.loadFromFile("arial.ttf"))
		{
			// error...
		}

		if (!playerTextureSheet.loadFromFile("character_robot_sheet.png"))
		{
			// error...
		}
		playerSpriteSheet.setTexture(playerTextureSheet);

		if (!coinTextureSheet.loadFromFile("spr_coin_roj.png"))
		{
			// error...
		}
		coinSpriteSheet.setTexture(coinTextureSheet);

		window.setVerticalSyncEnabled(true);
		player.InitAnimationData();
		player.startAnimaton(PlayerAnimationState::walk);

		coin.InitAnimationData();
		coin.startAnimaton(Coin::CoinAnimationState::coinflip);


		playerSpriteSheet.setPosition(50, 50);
		playerSpriteSheet.setOrigin(39, 39);
		playerSpriteSheet.setScale(0.6,0.6);

		//coinSpriteSheet.setPosition(100, 100);
		coinSpriteSheet.setOrigin(39, 39);
		coinSpriteSheet.setScale(1.9, 1.9);

		scoreText.setFont(font);
		scoreText.setPosition(550, 0);
		scoreText.setString("Coins collected: " + std::to_string(score));
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Red);



	};

	void init()
	{
		stopDrawingCoin = false;
		score = 0;
		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);


		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{

				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Green);
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Red);

				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Yellow); // jumpad

				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Magenta); // boost

				}

			}
		}

	}
	void run()
	{

		float scrollSpeed = -3.7f;

		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


		sf::Time timeSinceLastUpdate = sf::Time::Zero;


		sf::Clock clock;

		clock.restart();

		while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}


			timeSinceLastUpdate += clock.restart();


			if (timeSinceLastUpdate > timePerFrame)
			{

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{

						level[row][col].move(scrollSpeed, 0);
					}

				}

				player.Update();// update the robot
				coin.Update();
				particlesSystem.Update();
				particles.Update();

				playerSpriteSheet.setPosition(playerShape.getPosition().x, playerShape.getPosition().y -playerOffset);
				coinSpriteSheet.setPosition(level[5][5].getPosition().x + 2680, level[5][5].getPosition().y+350);


				sf::Vector2f position{ playerShape.getPosition() };
				float timeChange = (float)timeSinceLastUpdate.asSeconds();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocityY == 0)
				{
					//velocityY = -11.8;
					velocityY = pushOff.y;
					position.y = velocityY;
					position = position * timeChange;
				}
				else
				{
					//update position and velocity
					position.y = position.y + velocityY;
					position = position * timeChange;
					velocityY = velocityY + gravity * timeChange;
				}


				//position.y = window.getSize().y - playerShape.getGlobalBounds().height;
				//velocity.y = 0;
				//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				//{
				//	velocity.y = jumpPushOff.y;
				//	position = position + velocity * timeChange;
				//}

				velocityY = velocityY + gravity;
				playerShape.move(0, velocityY);
				gravity = 0.6;

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (velocityY >= 0)
						{
							if (levelData[row][col] == 1)
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									scrollSpeed = -3.7;
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										if (player.animationState == PlayerAnimationState::jump)
										{
											//player.animationState = player.PlayerAnimationState::walk;
											player.startAnimaton(PlayerAnimationState::walk);
										}

										gravity = 0;
										velocityY = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);							

										break;
									}
									else {
										init();
										scrollSpeed = -3.7;
									}
								}
							}
							
							if (levelData[row][col] == 5)
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									level[row][col].setPosition(row * 9, col * 9999);
								}
							}


							if (levelData[row][col] == 3) //Jump Block
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{

										velocityY = pushOff.y * 1.5;
										position.y = velocityY;
										position = position * timeChange;
										//playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										break;
									}
									else {
										init();
										scrollSpeed = -3.7;
									}
								}
							}
							if (levelData[row][col] == 4) //Speed Block
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = 0;
										velocityY = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										scrollSpeed = -10.0;
										break;
									}
									else {
										init();
									}
								}
							}
						}
						if (velocityY < 0)
						{
							if (levelData[row][col] == 1)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();

								}

							}

						}
						if (levelData[row][col] == 2)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();

							}
						}
					}
				}

				if (playerShape.getPosition().y > window.getSize().y)
				{
					init();
				}
				/// <summary>
				/// Collision for player and coin
				/// </summary>
				
				if (playerSpriteSheet.getGlobalBounds().intersects(coinSpriteSheet.getGlobalBounds()))
				{
					particlesSystem.Initialise(sf::Vector2f{ level[5][5].getPosition().x + 2630, level[5][5].getPosition().y + 325 });

					score = 1;
					stopDrawingCoin = true;
				}

				


			
				scoreText.setString("Coins collected: " + std::to_string(score));

				window.clear();

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						window.draw(level[row][col]);

					}
				}
				//window.draw(playerShape);
				player.Draw(window);
				if (stopDrawingCoin == false)
				{
					coin.Draw(window);
				}
				particlesSystem.Draw(window);
				particles.Draw(window);
				window.draw(scoreText);

				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};


int main()
{


	Game game;


	game.init();

	game.run();



	return 0;
}

