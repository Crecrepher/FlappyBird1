#pragma once
#include "SpriteGo.h"
#include "BlockGo.h"

class PFUnitGo : public SpriteGo
{
private:
	float speed;
	bool isJump;
	bool isDead;
	bool isBlockedSide;
	sf::Vector2f velocity;
	sf::Vector2f gravity;

	int stepCheck;
	int blockSideCheck;

public:
	PFUnitGo(const std::string n);
	~PFUnitGo();


	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	void Jump(float dt);

	void CheckBlock(BlockGo* block);
	void CheckStep();
	void CheckBlockSide();
	bool IsDead() const;
};

