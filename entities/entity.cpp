#include <iostream>
#include <random>
#include "entity.h"

Entity::Entity(void) {}

Entity::Entity(std::string name, int max_hp, int min_dmg, int max_dmg) {
    this->name = name;
    this->hp = this->max_hp = max_hp;
    this->min_dmg = min_dmg;
    this->max_dmg = max_dmg;
}

std::string Entity::get_name(void) const {
    /**
     * Gets the name of the entity
     * @return: a string representation of the entity name
     */
    return this->name;
}

int Entity::get_hp(void) const {
    /**
     * Gets the current hit points of the entity
     * @return: a int representing the current hit points of the entity
     */
    return this->hp;
}

std::string Entity::attack(Entity& other) {
    /**
     * Lets this entity attack another entity
     * @param other: the entity being attacked
     * @return: the attack text as a string
     */
    std::random_device rd; // RNG
    std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
    std::uniform_int_distribution<int> dmg_val(this->min_dmg, this->max_dmg); // nums between min and max have equal pick chance
    int dmg = other.take_dmg(dmg_val(mt));
    if (dmg == 0) {return this->name + " cannot damage " + other.get_name() + ".\n";}
    return this->name + " hits " + other.get_name() + " for " + std::to_string(dmg) + " damage.\n";
}

int Entity::take_dmg(int amt) {
    /**
     * Deals some damage to this entity
     * @param amt: the amount of damage taken
     * @return: the amount of damage taken as an integer
     */
    if (this->hp < amt) {this->hp = 0;}
    else {this->hp -= amt;}
    return amt;
}

void Entity::print_enc_stats(void) const {
    /**
     * Prints out basic stats for combat (name, HP, and MP)
     */
    std::cout << this->name << std::endl;
    std::cout << "HP: " << this->hp << "/" << this->max_hp << std::endl;
}

bool Entity::is_dead(void) const {
    /**
     * Checks if the entity is dead or not
     * @return: true if it is, false otherwise
     */
    return this->hp <= 0;
}

void Entity::rest(void) {
    /**
     * Recovers this entity to max health
     */
    this->hp = this->max_hp;
}