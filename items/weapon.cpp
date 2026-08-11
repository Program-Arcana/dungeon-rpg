#include <iostream>
#include "weapon.h"

Weapon::Weapon(void) {}

Weapon::Weapon(std::string name, int min_dmg, int max_dmg, int crit_chance, int cost) {
    this->name = name;
    this->min_dmg = min_dmg;
    this->max_dmg = max_dmg;
    this->crit_chance = crit_chance;
    this->cost = cost;
}

int Weapon::get_min_dmg(void) const {
    /**
     * Gets the weapon's minimum damage
     * @return: an integer representing the weapon's min damage
     */
    return this->min_dmg;
}

int Weapon::get_max_dmg(void) const {
    /**
     * Gets the weapon's maximum damage
     * @return: an integer representing the weapon's max damage
     */
    return this->max_dmg;
}

int Weapon::get_crit_chance(void) const {
    /**
     * Gets the weapon's critical hit chance
     * @return: an int representing the weapon's crit chance
     */
    return this->crit_chance;
}