#include <SFML/Graphics.hpp>
#include"Entity.h"
#include"Common.h"
#include"Util.h"
#include<iostream>
#include<math.h>
#include"Collision.h"
#include<vector>
#include"Quadtree.h"

class Bullet : public Entity {
	sf::Texture spriteTexture;
	
	std::vector<Enemy*> *enemies;

	float xVelocity;
	float yVelocity;
public:
	float x;
	float y;
	float speed;
	float damage; 
	sf::Sprite sprite;

	Bullet(const float angle, const float x, const float y, const float speed, const int& damage, std::vector<Enemy*> *enemies)
		: x(x), y(y), speed(speed), damage(damage), enemies(enemies) {
		Collision::CreateTextureAndBitmask(spriteTexture, spritesPath + "other/bulletb.png");
		sprite.setTexture(spriteTexture);
		sprite.rotate(util::radiansToDegrees(angle));
		sprite.setPosition(x, y);
		xVelocity = cos(angle);
		yVelocity = sin(angle);
	}
	
	~Bullet() {
		//std::cout << "Destroyed" << std::endl;
	}

	bool update() {
		x += xVelocity;
		y += yVelocity;
		sprite.move(xVelocity * speed, yVelocity * speed);
		return checkCollisions();
	}


	bool checkCollisions() {
		size_t size = enemies->size();
		if (size == 0) return false;
		for (std::vector<Enemy*>::size_type i = size; i > 0; --i) {
			std::vector<Enemy*>::size_type index = i - 1;
			Enemy* enemy = enemies->at(index);
			
			if (Collision::BoundingBoxTest(sprite, enemy->sprite)) {

				bool isDead = enemy->hit(damage);

				if (isDead)	{
					kill(enemy, index);
				}

				return false;
			}
		}
		return false;
	}

	template<typename T>
	void kill(T* obj, const size_t& index) {
		// everything we're gonna be calling delete on here will be a 'new' word object
		enemies->erase(enemies->begin() + index);
		delete obj;

	}

};