#include <iostream>
#include <cmath>
#include <random>
#include <stdexcept>
#include "player.h"

Player::Player(std::string name) {
    this->name = name;
    this->hp = this->max_hp = 100;
    this->def = this->max_def = 50;
    this->mp = this->max_mp = 100;
    this->num_coins = this->i_frames = 0;
    this->heal_pots = this->mana_pots = 5;
    this->weapon = Weapon("Broken Dagger", 5, 8, 0, 0);
    this->armor = Armor("Dusty Bandana", 0.15, 0);
    this->weapons = {this->weapon};
    this->armors = {this->armor};
    this->min_dmg = this->weapon.get_min_dmg();
    this->max_dmg = this->weapon.get_max_dmg();
    this->skills = {
                    new Skill("Great Slash", "Slashes enemies with great force.", 15, true),
                    new Skill("Life Steal", "Steals enemy lifeforce, user regains some health.", 30, false),
                    new Skill("Tough Scales", "Protects the player from damage for 5 turns.", 45, false),
                    new Skill("Soul Blast", "Blasts an enemy with soul power to instantly kill it.\n(Costs the player 50 HP per blast.)", 0, false),
                    new Skill("Mystery Key", "Unlocks the Mystery Dungeon, cannot be used otherwise.", 0, false)
                   };
}

void Player::print_stats(void) const {
    /**
     * Print out the player's stats
     */
    std::cout << "\"" << this->name << "\"" << std::endl;
    std::cout << "HP: " << this->hp << "/" << this->max_hp << std::endl;
    std::cout << "DEF: " << this->def << "/" << this->max_def << std::endl;
    std::cout << "MP: " << this->mp << "/" << this->max_mp << std::endl;
    std::cout << "WEAPON: " << this->weapon.get_name() << std::endl;
    std::cout << "ARMOR: " << this->armor.get_name() << std::endl;
    std::cout << "COINS: " << this->num_coins << std::endl;
}

void Player::print_enc_stats(void) const {
    /**
     * Prints the stats for the encounter
     */
    std::cout << this->name << std::endl;
    std::cout << "HP: " << this->hp << "/" << this->max_hp << std::endl;
    std::cout << "DEF: " << this->def << "/" << this->max_def << std::endl;
    std::cout << "MP: " << this->mp << "/" << this->max_mp << std::endl;
}

void Player::print_skills(void) const {
    /**
     * Prints out the player's skills
     */
    for (int i = 0; i < this->skills.size(); ++i) {
        std::cout << i + 1 << " - " << this->skills[i]->get_name() << " - " << this->skills[i]->get_cost() << " MP ";
        if (!this->skills[i]->is_unlocked()) {std::cout << "(LOCKED)";}
        std::cout << std::endl;
    }
}

int Player::get_num_heal(void) const {
    /**
     * Gets the number of healing potions the player currently has
     * @return: an integer representation of how many healing potions the player has
     */
    return this->heal_pots;
}

int Player::get_num_mana(void) const {
    /**
     * Gets the number of mana potions the player currently has
     * @return: an integer representation of how many mana potions the player has
     */
    return this->mana_pots;
}

int Player::get_num_coins(void) const {
    /**
     * Gets the number of coins the player currently has
     * @return: an integer representation of how many coins the player has
     */
    return this->num_coins;
}

int Player::get_rand_dmg(void) const {
    /**
     * Gets a random amount of damage the player can deal
     * @return: an integer representing the amount of damage the player can deal
     */
    std::random_device rd; // RNG
    std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
    std::uniform_int_distribution<int> dmg_val(this->min_dmg, this->max_dmg); // nums between min and max have equal pick chance
    int dmg_roll = dmg_val(mt);
    return dmg_roll;
}

Skill* Player::get_skill(int index) const {
    /**
     * Gets a skill from the player
     * @param index: the index of the skill to get
     * @return: an object representing the skill
     */
    return this->skills[index];
}

void Player::open_inventory(void) {
    /**
     * Opens the player's inventory
     */
    std::string choice;
    while (choice != "i") { // Until player closes inventory
        system("clear");
        std::cout << "INVENTORY\n" << std::endl;
        this->print_stats();
        std::cout << "\n1 - Weapons\n2 - Armors\n3 - Potions\n4 - Skills\ni - Close Inventory\n>>";
        std::getline(std::cin, choice);
        if (choice == "1") {this->view_weapons();}
        else if (choice == "2") {this->view_armors();}
        else if (choice == "3") {this->view_potions();}
        else if (choice == "4") {this->view_skills();}
    }
}

void Player::view_weapons(void) {
    /**
     * Opens the Weapons section of the player's inventory
     */
    std::string choice;
    while (choice != "b") { // Until the player goes back to main inventory
        system("clear");
        std::cout << "INVENTORY\n" << std::endl;
        this->print_stats();
        std::cout << "\nWEAPONS:" << std::endl;
        for (int i = 0; i < this->weapons.size(); ++i) {
            std::cout << i + 1 << " - " << this->weapons[i].get_name() << " (" << this->weapons[i].get_min_dmg() << "-" << this->weapons[i].get_max_dmg() << " damage)" << std::endl;
        }
        std::cout << "b - Back to Inventory\n>>";
        std::getline(std::cin, choice);
        int choice_num = 0;
        try {
            if (choice.size() == 1) {choice_num = std::stoi(choice);}
            else {continue;}
        }
        catch (std::invalid_argument const& e) {continue;}
        if ((choice_num > 0) && (choice_num <= this->weapons.size())) {
            this->weapon = this->weapons[choice_num - 1];
            this->min_dmg = this->weapon.get_min_dmg();
            this->max_dmg = this->weapon.get_max_dmg();
        }
    }
}

void Player::view_armors(void) {
    /**
     * Opens the Armors section of the player's inventory
     */
    std::string choice;
    while (choice != "b") { // Until the player goes back to main inventory
        system("clear");
        std::cout << "INVENTORY\n" << std::endl;
        this->print_stats();
        std::cout << "\nARMORS:" << std::endl;
        for (int i = 0; i < this->armors.size(); ++i) {
            std::cout << i + 1 << " - " << this->armors[i].get_name() << " (" << this->armors[i].get_prot() * 100 << "\% protection)" << std::endl;
        }
        std::cout << "b - Back to Inventory\n>>";
        std::getline(std::cin, choice);
        int choice_num = 0;
        try {
            if (choice.size() == 1) {choice_num = std::stoi(choice);}
            else {continue;}
        }
        catch (std::invalid_argument const& e) {continue;}
        if ((choice_num > 0) && (choice_num <= this->armors.size())) {this->armor = this->armors[choice_num - 1];}
    }
}

void Player::view_potions(void) {
    /**
     * Opens the Potions section of the player's inventory
     */
    std::string choice;
    while (choice != "b") { // Until the player goes back to main inventory
        system("clear");
        std::cout << "INVENTORY\n" << std::endl;
        this->print_stats();
        std::cout << "\nPOTIONS:" << std::endl;
        std::cout << "Healing Potion x " << this->heal_pots << std::endl;
        std::cout << "Mana Potion x " << this->mana_pots << std::endl;
        std::cout << "\n1 - Use Healing Potion\n2 - Use Mana Potion\nb - Back to Inventory\n>>";
        std::getline(std::cin, choice);
        if (choice == "1") {this->use_heal_pot();} 
        else if (choice == "2") {this->use_mana_pot();} 
    }
}

void Player::view_skills(void) {
    /**
     * Opens the Skills section of the player's inventory
     */
    std::string choice;
    while (choice != "b") { // Until the player goes back to main inventory
        system("clear");
        std::cout << "INVENTORY\n" << std::endl;
        this->print_stats();
        std::cout << "\nSKILLS:" << std::endl;
        this->print_skills();
        std::cout << "b - Back to Inventory\n>>";
        std::getline(std::cin, choice);
        int choice_num = 0;
        try {
            if (choice.size() == 1) {choice_num = std::stoi(choice);}
            else {continue;}
        }
        catch (std::invalid_argument const& e) {continue;}
        if ((choice_num > 0) && (choice_num <= this->skills.size()) && (this->skills[choice_num - 1]->is_unlocked())) {
            system("clear");
            std::cout << this->skills[choice_num - 1]->get_name() << ":" << std::endl;
            std::cout << this->skills[choice_num - 1]->get_desc() << std::endl;
            std::cout << "\nPress Enter to Continue\n>>";
            std::getline(std::cin, choice);
        }
    }
}

void Player::gain_coins(int amt) {
    /**
     * Allows the player to gain some coins
     * @param amt: the amount of coins to gain
     */
    this->num_coins += amt;
}

void Player::buy_weapon(Weapon weapon) {
    /**
     * Buys a weapon for the player
     * @param weapon: the weapon the player buys
     */
    if (this->num_coins >= weapon.get_cost()) {
        this->weapons.push_back(weapon);
        this->num_coins -= weapon.get_cost();
    } 
}

void Player::buy_armor(Armor armor) {
    /**
     * Buys an armor for the player
     * @param armor: the armor the player buys
     */
    if (this->num_coins >= armor.get_cost()) {
        this->armors.push_back(armor);
        this->num_coins -= armor.get_cost();
    } 
}

void Player::buy_heal_pot(void) {
    /**
     * Buys a healing potion for the player
     */
    if (this->num_coins >= 5) {
        ++this->heal_pots;
        this->num_coins -= 5;
    }
}

void Player::buy_mana_pot(void) {
    /**
     * Buys a mana potion for the player
     */
    if (this->num_coins >= 5) {
        ++this->mana_pots;
        this->num_coins -= 5;
    }
}

void Player::use_heal_pot(void) {
    /**
     * Consume a healing potion, restoring health
     */
    if (this->hp < this->max_hp) {
        --this->heal_pots;
        if (this->max_hp - this->hp < 50) {this->hp = this->max_hp;}
        else {this->hp += 50;}
    }
}

void Player::use_mana_pot(void) {
    /**
     * Consume an mana potion, restoring mana
     */
    if (this->mp < this->max_mp) {
        --this->mana_pots;
        if (this->max_mp - this->mp < 50) {this->mp = this->max_mp;}
        else {this->mp += 50;}
    }
}

bool Player::has_weapon(Weapon weapon) const {
    /**
     * Checks if the player has a weapon
     * @param weapon: the weapon being checked for
     * @return: true if the player has it, false otherwise
     */
    for (int i = 0; i < this->weapons.size(); ++i) {
        if (this->weapons[i].get_name() == weapon.get_name()) {return true;}
    }
    return false;
}

bool Player::has_armor(Armor armor) const {
    /**
     * Checks if the player has an armor
     * @param armor: the armor being checked for
     * @return: true if the player has it, false otherwise
     */
    for (int i = 0; i < this->armors.size(); ++i) {
        if (this->armors[i].get_name() == armor.get_name()) {return true;}
    }
    return false;
}

bool Player::has_key(void) const {
    /**
     * Checks to see if the player has the Mystery Key
     * @return: true if the player does, false otherwise
     */
    return this->skills[4]->is_unlocked();
}

std::string Player::attack(Entity& other) {
    /**
     * Lets the player attack another entity
     * @param other: the entity being attacked
     * @return: the attack text as a string
     */
    std::random_device rd; // RNG
    std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
    std::uniform_int_distribution<int> crit_val(1, 100);
    int dmg_roll = this->get_rand_dmg();
    if (this->max_mp - this->mp < 10) {this->mp = this->max_mp;}
    else {this->mp += 10;}
    if (crit_val(mt) <= this->weapon.get_crit_chance()) {
        dmg_roll = other.take_dmg(2 * dmg_roll);
        return this->name + " CRITS " + other.get_name() + " for " + std::to_string(dmg_roll) + " damage.\n";
    }
    dmg_roll = other.take_dmg(dmg_roll);
    return this->name + " hits " + other.get_name() + " for " + std::to_string(dmg_roll) + " damage.\n";
}

std::string Player::use_skill(Entity& other) {
    /**
     * Use a skill on an entity
     * @param other: the entity the skill is being used on
     * @return: the skill text as a string
     */
    std::string choice;
    int choice_num = 0;
    std::string skill_text;
    while ((choice != "b") && (skill_text == "")) { // Until player returns to combat or uses a skill
        system("clear");
        this->print_enc_stats();
        std::cout << "\nSKILLS:" << std::endl;
        this->print_skills();
        std::cout << "b - Back to Combat" << std::endl;
        std::cout << ">>";
        std::getline(std::cin, choice);
        try {
            if (choice.size() == 1) {choice_num = std::stoi(choice);}
            else {continue;}
        }
        catch (std::invalid_argument const &e) {continue;}
        if ((choice_num > 0) && (choice_num <= this->skills.size()) && (this->skills[choice_num - 1]->is_unlocked())) {
            if (this->mp >= this->skills[choice_num - 1]->get_cost()) {
                if (choice_num == 1) {skill_text += this->great_slash(other);}
                else if (choice_num == 2) {skill_text += this->life_steal(other);}
                else if (choice_num == 3) {skill_text += this->tough_scales();}
                else if (choice_num == 4) {skill_text += this->soul_blast(other);}
            } else {
                system("clear");
                this->print_enc_stats();
                std::cout << "\nNot enough MP for this skill!\n\nPress Enter to Continue\n>>";
                std::getline(std::cin, choice);
            }
        }
    }
    return skill_text;
}

std::string Player::great_slash(Entity& other) {
    /**
     * Performs the Great Slash skill on an entity
     * @param other: the entity the skill is being used on
     * @return: the skill text as a string
     */
    std::random_device rd; // RNG
    std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
    std::uniform_int_distribution<int> dmg_val(this->min_dmg * 4, this->max_dmg * 4); // nums between min and max have equal pick chance
    int dmg = dmg_val(mt);
    other.take_dmg(dmg);
    this->mp -= this->skills[0]->get_cost();
    return this->name + " slashes " + other.get_name() + " for " + std::to_string(dmg) + " damage.\n";
}

std::string Player::life_steal(Entity& other) {
    /**
     * Performs the Life Steal skill on an entity
     * @param other: the entity the skill is being used on
     * @return: the skill text as a string
     */
    std::random_device rd; // RNG
    std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
    std::uniform_int_distribution<int> steal_val(this->min_dmg * 2, this->max_dmg * 2); // nums between min and max have equal pick chance
    int steal_amt = steal_val(mt);
    other.take_dmg(steal_amt);
    if (this->hp + steal_amt <= this->max_hp) {this->hp += steal_amt;}
    else {this->hp = this->max_hp;}
    this->mp -= this->skills[1]->get_cost();
    return this->name + " absorbs life from " + other.get_name() + " for " + std::to_string(steal_amt) + " damage.\n";
}

std::string Player::tough_scales(void) {
    /**
     * Performs the Tough Scales skill on the player
     * @return: the skill text as a string
     */
    this->i_frames += 5;
    this->mp -= this->skills[2]->get_cost();
    return this->name + " becomes invincible for 5 more turns.\n";
}

std::string Player::soul_blast(Entity& other) {
    /**
     * Performs the Soul Blast skill on an entity
     * @param other: the entity the skill is being performed on
     * @return: the skill text as a string
     */
    other.take_dmg(other.get_hp());
    if (this->hp < 50) {this->hp = 0;}
    else {this->hp -= 50;}
    return this->name + " blasts " + other.get_name() + " with soul energy.\n";
}

int Player::take_dmg(int amt) {
    /**
     * Allows the player to take damage based on their armor protection
     * @param amt: the amount of raw damage being dealt to the player
     * @return: the amount of damage taken as an integer
     */
    if (this->i_frames > 0) { // For the invincibility skill
        --this->i_frames;
        return 0;
    }
    int prot = std::floor(amt * this->armor.get_prot());
    if (this->def > 0) {
        if (this->def < amt - prot) {this->def = 0;}
        else {this->def -= amt - prot;}
    } else {
        if (this->hp < amt - prot) {this->hp = 0;}
        else {this->hp -= amt - prot;}
    }
    return amt - prot;
}

void Player::restore_def(void) {
    /**
     * Restores the player's defense
     */
    this->def = this->max_def;
}

void Player::power_up(void) {
    /**
     * Powers up the player, increasing their stats
     */
    this->max_hp += 50;
    this->max_def += 25;
    this->max_mp += 50;
}

void Player::rest(void) {
    /**
     * Allows player to rest, restoring HP, DEF, and MP
     */
    this->hp = this->max_hp;
    this->restore_def();
    this->mp = this->max_mp;
}

void Player::respawn(int num_coins, int num_heal, int num_mana) {
    /**
     * Player respawns outside dungeon with replenished items and coins
     * @param num_coins: the number of coins the player had before exploring
     * @param num_heal: the number of healing potions the player had before exploring
     * @param num_mana: the number of mana potions the player had before exploring
     */
    this->num_coins = num_coins;
    this->heal_pots = num_heal;
    this->mana_pots = num_mana;
}