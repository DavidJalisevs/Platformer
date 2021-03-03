/// <summary>
/// NAMES
/// Davids jalisevs /// Aeden Moylan 
/// Platformer
/// </summary>
#pragma once

#include "Animation.h"
enum class PlayerAnimationState { walk, run, jump, idle };

class Player
{
public:
	PlayerAnimationState animationState = PlayerAnimationState::walk;
	Animation animations[5];
	AnimationSheet animSheet;
	sf::Vector2f position;
	sf::Sprite& spriteSheet;

	Player(sf::Sprite& spheet) : spriteSheet(spheet)
	{
	}
	void InitAnimationData()
	{
		animations[int(PlayerAnimationState::walk)] = { 8,36,1,true };
		animations[int(PlayerAnimationState::run)] = { 3,24,5,true };
		animations[int(PlayerAnimationState::jump)] = { 4,0,10,false };
		animations[int(PlayerAnimationState::idle)] = { 3,21,10,true };
		animationState = PlayerAnimationState::walk;
		animSheet.Init(spriteSheet.getGlobalBounds().width,
			spriteSheet.getGlobalBounds().height, 5, 9);
	}
	void startAnimaton(PlayerAnimationState _animationState)
	{
		animationState = _animationState;
		animSheet.StartAnimation(animations[int(animationState)]);
	}
	void Draw(sf::RenderWindow& win)
	{
		animSheet.nextFrame();
		spriteSheet.setTextureRect(animSheet.GetFrame());
		win.draw(spriteSheet);
	}
	void Update()
	{
		if (animationState == PlayerAnimationState::idle)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				animationState = PlayerAnimationState::jump;
				startAnimaton(animationState);
			}
		}

		if (animationState == PlayerAnimationState::walk)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				animationState = PlayerAnimationState::jump;
				startAnimaton(animationState);
			}

		}
		else if (animationState == PlayerAnimationState::jump)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				animationState = PlayerAnimationState::walk;
				startAnimaton(animationState);
			}
		}

		if (animationState == PlayerAnimationState::walk)
		{
			std::cout << "Walkin" << std::endl;
		}
		if (animationState == PlayerAnimationState::idle)
		{
			std::cout << "Idlin" << std::endl;
		}
		if (animationState == PlayerAnimationState::jump)
		{
			std::cout << "Jumpin" << std::endl;
		}
	}
};
