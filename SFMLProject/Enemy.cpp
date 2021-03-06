#include"Entity.h"
#include <SFML/Graphics.hpp>
#include"Common.h"
#include"Collision.h"
#include<iostream>
#include"Util.h"

Enemy::Enemy(float x, float y, const int health, std::vector<Enemy*> *enemies)
	:x(x), y(y), health(health), enemies(enemies) {
	Collision::CreateTextureAndBitmask(idle, spritesPath + "monster/slime1_front.png");
	id = util::generateID();
	
	enemies->emplace_back(this);

	sprite.setTexture(idle);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	sprite.setPosition(x, y);
}

Enemy::~Enemy() {
	std::cout << "Enemy killed" << std::endl;
}

void Enemy::update() {
	//std::cout << health << std::endl;
	
	if (sprite.getPosition().y > windowY) {
		sprite.setPosition(sprite.getPosition().x, 0);
	}
}

bool Enemy::hit(const int& damage) {
	health -= damage;
	//std::cout << health << std::endl;
	if (health <= 0) {
		return true;
	}
	return false;
}

void Enemy::move(sf::Vector2f vector) {
	sprite.move(vector);
}