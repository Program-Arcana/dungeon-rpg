#include "armor.h"

Armor::Armor(void) {
    this->name = "None";
    this->prot = 0;
    this->cost = 0;
}

Armor::Armor(std::string name, double prot, int cost) {
    this->name = name;
    this->prot = prot;
    this->cost = cost;
}

double Armor::get_prot(void) const {
    /**
     * Gets the protection percentage of the armor
     * @return: a double representing the protection percentage
     */
    return this->prot;
}
