#ifndef DUNGEON_H
#define DUNGEON_H
#include <string>
#include <tuple>
#include <vector>
#include "../entities/entity.h"
#include "../entities/player.h"

class Dungeon {
    protected:
        std::string name;
        int length;
        int width; 
        char blank_mark; 
        char enemy_mark;
        char skill_mark; 
        char player_mark;
        int player_row;
        int player_col;
        Player* player;
        int start_coins;
        int start_heal;
        int start_mana;
        int coin_mod;
        bool skill_learned;
        Skill* new_skill;
        std::vector<std::vector<char>> full_map; 
        std::vector<std::vector<char>> player_map; 
        std::vector<std::tuple<std::string, int, int, int>> enemies;
        int num_encs;
        int encs_done;
        void generate(void);
        void enter(void);
        void reveal_view(void);
        void enemy_enc(void);
        void print_map(void) const;
        void move_right(void);
        void move_left(void);
        void move_up(void);
        void move_down(void);
        void check_tile(void);
        bool is_skill_learned(void) const;
    public:
        Dungeon(std::string name, int length, int width, Player* player, std::vector<std::tuple<std::string, int, int, int>> enemies, int skill_index);
        void explore(void);
};

#endif