#include <iostream>
#include <random>
#include "dungeon.h"

Dungeon::Dungeon(std::string name, int length, int width, Player* player, std::vector<std::tuple<std::string, int, int, int>> enemies, int skill_index) {
    this->name = name;
    this->length = length;
    this->width = width;
    this->blank_mark = '*';
    this->enemy_mark = '!';
    this->skill_mark = '$';
    this->player_mark = '@';
    this->player = player;
    this->start_coins = this->player->get_num_coins();
    this->start_heal = this->player->get_num_heal();
    this->start_mana = this->player->get_num_mana();
    this->skill_learned = false;
    this->new_skill = this->player->get_skill(skill_index);
    this->coin_mod = skill_index - 1;
    this->enemies = enemies;
    this->encs_done = 0;
    this->generate();
    this->enter();
}

void Dungeon::generate(void) {
    /**
     * Generates the dungeon and its marks
     */
    // Generate Empty/Blank Marks
    for (int i = 0; i < this->length; ++i) {
        std::vector<char> map_line;
        for (int j = 0; j < this->width; ++j) {
            if ((i == 0) || (j == 0) || (i == this->length - 1) || (j == this->width - 1)) {map_line.push_back('#');}
            else {map_line.push_back(this->blank_mark);}
        }
        this->full_map.push_back(map_line);
    }
    // Generate Encounter Marks
    this->num_encs = length * width / 10; 
    int encs_placed = 0;
    std::random_device rd; // RNG
    std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
    std::uniform_int_distribution<int> rand_length(1, this->length - 2);
    std::uniform_int_distribution<int> rand_width(1, this->width - 2);
    while (encs_placed < this->num_encs) {
        int enc_row = rand_length(mt);
        int enc_col = rand_width(mt);
        if (this->full_map[enc_row][enc_col] != this->enemy_mark) {
            this->full_map[enc_row][enc_col] = this->enemy_mark;
            ++encs_placed;
        }
    }
    // Generate Skill Mark
    for (int i = this->length - 2; i >= this->length / 2; --i) {
        int skill_col = rand_width(mt);
        if (this->full_map[i][skill_col] != this->enemy_mark) {
            this->full_map[i][skill_col] = this->skill_mark;
            return;
        }
    }
}

void Dungeon::enter(void) {
    /**
     * Sets up the player map and puts them on it
     */
    this->player_row = 1;
    this->player_col = 1;
    for (int i = 0; i < this->length; ++i) {
        std::vector<char> map_line;
        for (int j = 0; j < this->width; ++j) {
            map_line.push_back(' ');
        }
        this->player_map.push_back(map_line);
    }
    this->reveal_view();
    this->player_map[this->player_row][this->player_col] = this->player_mark;
    this->check_tile(); // In case there is an enemy encounter immediately upon entering
}

void Dungeon::reveal_view(void) {
    /**
     * Reveal on the map what the player can see (3x3 grid around the player)
     */
    for (int i = this->player_row - 1; i <= this->player_row + 1; ++i) {
        for (int j = this->player_col - 1; j <= this->player_col + 1; ++j) {
            this->player_map[i][j] = this->full_map[i][j];
        }
    }
}

void Dungeon::enemy_enc(void) {
    /**
     * Enter a battle with an enemy
     */
    std::random_device rd; // RNG
    std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
    std::uniform_int_distribution<int> enemy_index(0, this->enemies.size() - 1);
    int e = enemy_index(mt);
    Entity enemy(std::get<0>(this->enemies[e]), std::get<1>(this->enemies[e]), std::get<2>(this->enemies[e]), std::get<3>(this->enemies[e]));
    std::string choice;
    std::string player_action;
    std::string enemy_action;
    while ((!this->player->is_dead()) && (!enemy.is_dead())) {
        std::string player_temp = "\n"; // To temporarily hold the player action text
        system("clear");
        std::cout << "ENEMY ENCOUNTER\n\n" << enemy.get_name() << " stands in your way.\n" << player_action << enemy_action << std::endl;
        enemy.print_enc_stats();
        std::cout << std::endl;
        this->player->print_enc_stats();
        std::cout << "\nPick an action:\n1 - Attack\n2 - Skills\n>>";
        std::getline(std::cin, choice);
        if (choice == "1") {player_temp += this->player->attack(enemy);}
        else if (choice == "2") {player_temp += this->player->use_skill(enemy);}
        else {continue;}
        if (player_temp != "\n") {
            player_action = player_temp;
            enemy_action = enemy.attack(*this->player);
        }
        if (enemy.is_dead()) { 
            system("clear");
            std::cout << "ENEMY ENCOUNTER\n\n" << enemy.get_name() << " stands in your way.\n" << player_action << enemy_action << std::endl;
            enemy.print_enc_stats();
            std::cout << std::endl;
            this->player->print_enc_stats();
            std::cout << "\nYou have defeated the " << enemy.get_name() << "!" << std::endl;
            std::uniform_int_distribution<int> rand_coin(2 + this->coin_mod, 5 + this->coin_mod);
            int coins_dropped = rand_coin(mt);
            std::cout << "You gain " << coins_dropped << " coins.\n\nPress Enter to Continue\n>>";
            this->player->gain_coins(coins_dropped);
            std::getline(std::cin, choice);
        }
    }
    if (!this->player->is_dead()) {
        this->full_map[this->player_row][this->player_col] = this->blank_mark;
        ++this->encs_done;
    } else {
        system("clear");
        std::cout << "ENEMY ENCOUNTER\n\n" << enemy.get_name() << " stands in your way.\n" << player_action << enemy_action << std::endl;
        enemy.print_enc_stats();
        std::cout << std::endl;
        this->player->print_enc_stats();
        std::cout << "\nYou have been knocked out.\nPress Enter to Revive\n>>";
        std::getline(std::cin, choice);
    }
    this->player->restore_def();
}

void Dungeon::print_map(void) const {
    /**
     * Prints out the current player map
     */
    for (int i = 0; i < this->length; ++i) {
        for (int j = 0; j < this->width; ++j) {
            std::cout << this->player_map[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    // Print legend
    std::cout << "\nMap Legend:" << std::endl;
    std::cout << this->player_mark << " = You" << std::endl;
    std::cout << this->enemy_mark << " = Enemy" << std::endl;
    std::cout << this->skill_mark << " = Skill Scroll" << std::endl;
}

void Dungeon::move_right(void) {
    /**
     * Move the player right by one space on the map 
     */
    if (this->player_col < this->width - 2) {
        ++this->player_col;
        this->reveal_view();
        this->player_map[this->player_row][this->player_col] = this->player_mark;
    }
}

void Dungeon::move_left(void) {
    /**
     * Move the player left by one space on the map 
     */
    if (this->player_col > 1) {
        --this->player_col;
        this->reveal_view();
        this->player_map[this->player_row][this->player_col] = this->player_mark;
    }
}

void Dungeon::move_up(void) {
    /**
     * Move the player up by one space on the map 
     */
    if (this->player_row > 1) {
        --this->player_row;
        this->reveal_view();
        this->player_map[this->player_row][this->player_col] = this->player_mark;
    }
}

void Dungeon::move_down(void) {
    /**
     * Move the player down by one space on the map 
     */
    if (this->player_row < this->length - 2) {
        ++this->player_row;
        this->reveal_view();
        this->player_map[this->player_row][this->player_col] = this->player_mark;
    }
}

void Dungeon::check_tile(void) {
    /**
     * Checks the tile the player moves on to perform the correct action/event
     */
    if (this->full_map[this->player_row][this->player_col] == this->enemy_mark) {this->enemy_enc();}
    else if (this->full_map[this->player_row][this->player_col] == this->skill_mark) {
        if (this->encs_done == this->num_encs) {this->skill_learned = true;}
        else {
            system("clear");
            std::cout << this->name << std::endl;
            std::cout << "\nYou pick up the Skill Scroll.\nUnfortunately, it is currently unreadable.\nSeems like you'll need to clear the dungeon first.\n\nPress Enter to Continue\n>>";
            std::string cont;
            std::getline(std::cin, cont);
        }
    }
}

bool Dungeon::is_skill_learned(void) const {
    /**
     * Indicates whether or not the skill of the dungeon has been learned yet
     * @return: true if learned, false otherwise
     */
    return this->skill_learned;
}

void Dungeon::explore(void) {
    /**
     * Explore the dungeon until the player dies or the skill is found
     */
    std::string choice;
    while ((!this->is_skill_learned()) && (!this->player->is_dead())) {
        system("clear");
        std::cout << this->name << std::endl;
        std::cout << "\nCompletion Percentage: " << 1.0 * this->encs_done / this->num_encs * 100 << " %" << std::endl;
        this->print_map();
        std::cout << "\nChoose a direction:\nwasd - Up, Left, Down, Right\ni - Open Inventory\n>>";
        std::getline(std::cin, choice);
        if (choice == "w") {this->move_up();}
        else if (choice == "a") {this->move_left();}
        else if (choice == "s") {this->move_down();}
        else if (choice == "d") {this->move_right();}
        else if (choice == "i") {this->player->open_inventory();}
        this->check_tile();
    }
    if (this->player->is_dead()) {
        this->player->respawn(this->start_coins, this->start_heal, this->start_mana);
    } else { 
        system("clear");
        std::cout << this->name << std::endl;
        std::cout << "\nYou have successfully cleared the dungeon! HURRAH!\nYou pick up the Skill Scroll and read its contents.\n" << std::endl;
        std::cout << "New skill unlocked: " << this->new_skill->get_name() << std::endl;
        this->new_skill->unlock();
        std::cout << "\nPress Enter to Continue\n>>";
        std::getline(std::cin, choice);
    }
}


