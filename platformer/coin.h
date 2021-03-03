#pragma once
/// <summary>
/// NAMES
/// Davids jalisevs /// Aeden Moylan 
/// Platformer
/// </summary>
#pragma once

#include "Animation.h"

class Coin
{
public:
	enum class CoinAnimationState { coinflip };
	CoinAnimationState animationState = CoinAnimationState::coinflip;
	Animation animations[1];
	AnimationSheet animSheet;
	sf::Vector2f position;
	sf::Sprite& spriteSheet;

	Coin(sf::Sprite& spheet) : spriteSheet(spheet)
	{
	}
	void InitAnimationData()
	{
		animations[int(CoinAnimationState::coinflip)] = { 4,0,15,true };

		animationState = CoinAnimationState::coinflip;
		animSheet.Init(spriteSheet.getGlobalBounds().width,
			spriteSheet.getGlobalBounds().height, 1, 4);
	}
	void startAnimaton(CoinAnimationState _animationState)
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
	


		if (animationState == CoinAnimationState::coinflip)
		{
			//std::cout << "Coin is flipping" << std::endl;
		}
	}
};
