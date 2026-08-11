#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"

class Weapon: public Item {
    protected:
        int min_dmg;
        int max_dmg;
        int crit_chance;
    public:
        Weapon(void);
        Weapon(std::string name, int min_dmg, int max_dmg, int crit_chance, int cost);
        int get_min_dmg(void) const;
        int get_max_dmg(void) const;
        int get_crit_chance(void) const;
};

#endif