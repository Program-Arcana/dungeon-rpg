#include <iostream>
#include "shop.h"

Shop::Shop(Player* player) {
    this->player = player;
    this->init_weapons();
    this->init_armors();
}

void Shop::init_weapons(void) {
    /**
     * Initialize the shop weapons
     */
    w1 = Weapon("Shiny Dagger", 10, 16, 5, 25);
    w2 = Weapon("Flaming Sword", 15, 24, 10, 50);
    w3 = Weapon("Lightning Spear", 20, 32, 20, 100);
    w4 = Weapon("Meteor Axe", 25, 45, 40, 200);
    this->weapons = {w1, w2, w3, w4};
}

void Shop::init_armors(void) {
    /**
     * Initialize shop armors
     */
    a1 = Armor("Red Amulet", 0.3, 25);
    a2 = Armor("Crystal Ring", 0.45, 50);
    a3 = Armor("Shadowy Choker", 0.6, 100);
    a4 = Armor("Golden Crown", 0.75, 200);
    this->armors = {a1, a2, a3, a4};
}

void Shop::view_weapons(void) { // Fix buy logic
    /**
     * View the shop weapons
     */
    std::string choice;
    int choice_num = 0;
    while (choice != "b") { // until player goes back to shop menu
        system("clear");
        std::cout << "SHOP WEAPONS\n" << std::endl;
        std::cout << "Your Coins: " << this->player->get_num_coins() << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < this->weapons.size(); ++i) {
            std::cout << i + 1 << " - " << this->weapons[i].get_name() << std::endl;
            std::cout << "    Damage: " << this->weapons[i].get_min_dmg() << "-" << this->weapons[i].get_max_dmg() << std::endl;
            std::cout << "    Cost: " << this->weapons[i].get_cost() << " coins" << std::endl;
        }
        std::cout << "b - Back to Shop\n>>";
        std::getline(std::cin, choice);
        try {choice_num = std::stoi(choice);}
        catch (std::invalid_argument const& e) {continue;}
        if ((choice_num > 0) && (choice_num <= this->weapons.size())) {
            player->buy_weapon(this->weapons[choice_num - 1]);
            if (this->player->has_weapon(this->weapons[choice_num - 1])) {this->weapons.erase(this->weapons.begin() + choice_num - 1);}
        }
    }
}

void Shop::view_armors(void) { // Fix buy logic
    /**
     * View the shop armors
     */
    std::string choice;
    int choice_num = 0;
    while (choice != "b") { // until player goes back to shop menu
        system("clear");
        std::cout << "SHOP ARMORS\n" << std::endl;
        std::cout << "Your Coins: " << this->player->get_num_coins() << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < this->armors.size(); ++i) {
            std::cout << i + 1 << " - " << this->armors[i].get_name() << std::endl;
            std::cout << "    Protection: " << this->armors[i].get_prot() * 100 << "%" << std::endl;
            std::cout << "    Cost: " << this->armors[i].get_cost() << " coins" << std::endl;
        }
        std::cout << "b - Back to Shop\n>>";
        std::getline(std::cin, choice);
        try {choice_num = std::stoi(choice);}
        catch (std::invalid_argument const& e) {continue;}
        if ((choice_num > 0) && (choice_num <= this->armors.size())) {
            player->buy_armor(this->armors[choice_num - 1]);
            if (this->player->has_armor(this->armors[choice_num - 1])) {this->armors.erase(this->armors.begin() + choice_num - 1);}
        }
    }
}

void Shop::view_potions(void) { 
    /**
     * View the shop potions
     */
    std::string choice;
    while (choice != "b") { // until player goes back to shop menu
        system("clear");
        std::cout << "SHOP POTIONS\n" << std::endl;
        std::cout << "Your Coins: " << this->player->get_num_coins() << std::endl;
        std::cout << "Your Healing Potions: " << this->player->get_num_heal() << std::endl;
        std::cout << "Your Mana Potions: " << this->player->get_num_mana() << std::endl;
        std::cout << "\n1 - Buy Healing Potion (5 coins)" << std::endl;
        std::cout << "2 - Buy Mana Potion (5 coins)" << std::endl;
        std::cout << "b - Back to Shop\n>>";
        std::getline(std::cin, choice);
        if (choice == "1") {this->player->buy_heal_pot();} 
        else if (choice == "2") {this->player->buy_mana_pot();}
    }
}