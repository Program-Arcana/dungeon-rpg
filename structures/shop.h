#ifndef SHOP_H
#define SHOP_H
#include <vector>
#include "../entities/player.h"
#include "../items/armor.h"
#include "../items/weapon.h"

class Shop {
    private: 
        Player* player;
        Weapon w1, w2, w3, w4;
        Armor a1, a2, a3, a4;
        std::vector<Weapon> weapons;
        std::vector<Armor> armors;
        void init_weapons(void);
        void init_armors(void);
    public:
        Shop(Player* player);
        void view_weapons(void);
        void view_armors(void);
        void view_potions(void);
};

#endif