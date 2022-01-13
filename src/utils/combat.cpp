#include "./utils.h"

int combat(Player &player, Monster &monster, int order)
{
    //player attack
    if (order == 1)
    {
        int monsterHealth = monster.getHealth();
        monster.setHealth(monsterHealth - player.getAttack());
        if (monster.getHealth() > 0)
        {
            int playerHealth = player.getHealth();
            player.setHealth(playerHealth - monster.getAttack());
        }
        else
        {
            killMonster(monster);
        }
    }
    //monster attack
    else
    {
        int playerHealth = player.getHealth();
        player.setHealth(playerHealth - monster.getAttack());
        if (player.getHealth() > 0)
        {
            int monsterHealth = monster.getHealth();
            monster.setHealth(monsterHealth - player.getAttack());
        }
    }
}