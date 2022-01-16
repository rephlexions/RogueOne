#ifndef COMBAT_H
#define COMBAT_H
#include "./utils.h"

int combat(Player *player, Monster *monster, int order)
{
    //player attack
    if (order == 1)
    {
        int monsterHealth = monster->getHealth();
        monster->setHealth(monsterHealth - player->getAttack());
        if (monster->getHealth() > 0)
        {
            int playerHealth = player->getHealth();
            player->setHealth(playerHealth - monster->getAttack());
        }
        else if (monster->getHealth() <= 0)
        {
            killMonster(monster);
            player->setExp(player->getExp() + 1);
        }
    }
    //monster attack
    else
    {
        int playerHealth = player->getHealth();
        player->setHealth(playerHealth - monster->getAttack());
        if (player->getHealth() > 0)
        {
            int monsterHealth = monster->getHealth();
            monster->setHealth(monsterHealth - player->getAttack());
        }
    }
}
#endif
