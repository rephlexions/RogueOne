#include "./Player.h"

Player::Player(Position pos, int health, int attack, int maxHealth, int exp) : Actor(pos, health, attack)
{
    this->exp = exp;
    this->maxHealth = maxHealth;
}

Player::Player() {}

Player::~Player() {}

int Player::getExp()
{
    return this->exp;
}
void Player::setExp(int exp)
{
    this->exp = this->exp + exp;
}

int Player::getMaxHealth()
{
    return this->maxHealth;
}
