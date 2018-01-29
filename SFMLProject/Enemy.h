#pragma once
#include"Entity.h"

class Enemy : public Entity {
	std::vector<Enemy*> *enemies;

	int health;
	
public:
	float x;
	float y;

	sf::Texture idle;
	Enemy(std::vector<Enemy*> *enemies, float x, float y, const int health);
	~Enemy();
	void update();
	void move(sf::Vector2f vector);

    // returns true if enemy is dead
	bool hit(const int& damage);
};