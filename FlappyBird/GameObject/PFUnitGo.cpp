#include "stdafx.h"
#include "PFUnitGo.h"
#include "InputMgr.h"

PFUnitGo::PFUnitGo(const std::string n) : SpriteGo(n), speed(500),
isJump(true), isDead(false), velocity(0.f, 0.f), gravity(0.f, 0.f),
isBlockedSide(false), stepCheck(0), blockSideCheck(0)
{
}

PFUnitGo::~PFUnitGo()
{
}

void PFUnitGo::Init()
{
	SpriteGo::Init();
	gravity.y = 0.f;
	velocity.y = 0.f;
	isDead = false;
}

void PFUnitGo::Reset()
{
	SpriteGo::Reset();
	gravity.y = 0.f;
	velocity.y = 0.f;
	isDead = false;
}

void PFUnitGo::Release()
{
	SpriteGo::Release();
}

void PFUnitGo::Update(float dt)
{
	SpriteGo::Update(dt);
	stepCheck = 0;
	blockSideCheck = 0;
	if (isDead)
	{
		return;
	}


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		gravity.y = 6000;
		velocity = sf::Vector2f(0.f, -1500.f);
		isJump = true;
	}
	Jump(dt);
}

void PFUnitGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void PFUnitGo::Jump(float dt)
{
	if (isJump)
	{
		velocity += gravity * dt;
		SetPosition(position + velocity * dt);
	}
}

void PFUnitGo::CheckBlock(BlockGo* block)
{

	if (block->blockUp.frect.intersects(sprite.getGlobalBounds()))
	{
		isDead = true;
		if (velocity.y > 0)
		{
			stepCheck++;
		}
	}
	if (block->blockDown.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		isDead = true;
		if (velocity.y < 0)
		{
			velocity.y *= -1.f;
		}
	}
	if (block->blockLeft.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		isDead = true;
		if (!INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			blockSideCheck++;
		}
	}

	if (block->blockRight.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		isDead = true;
		if (!INPUT_MGR.GetKey(sf::Keyboard::Right))
		{
			blockSideCheck++;
		}
	}
}

void PFUnitGo::CheckStep()
{
	if (stepCheck > 0)
	{
		isJump = false;
	}
	else
	{
		isJump = true;
	}
}

void  PFUnitGo::CheckBlockSide()
{
	if (blockSideCheck > 0)
	{
		isBlockedSide = true;
	}
	else
	{
		isBlockedSide = false;
	}
}

bool PFUnitGo::IsDead() const
{
	return isDead;
}
