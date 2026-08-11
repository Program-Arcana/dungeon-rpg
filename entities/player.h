#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "entity.h"
#include "../items/armor.h"
#include "../items/skill.h"
#include "../items/weapon.h"

class Player: public Entity {
    protected:
        std::string class_name; 
        int def;
        int max_def;
        int mp;
        int max_mp;
        int num_coins;
        int heal_pots;
        int mana_pots;
        int i_frames;
        bool key_found;
        Weapon weapon;
        Armor armor;
        std::vector<Weapon> weapons;
        std::vector<Armor> armors;
        std::vector<Skill*> skills;
    public: 
        Player(std::string name);
        // Player Info
        void print_stats(void) const;
        void print_enc_stats(void) const override;
        void print_skills(void) const;
        int get_num_heal(void) const;
        int get_num_mana(void) const;
        int get_num_coins(void) const;
        int get_rand_dmg(void) const;
        Skill* get_skill(int index) const;
        // Player Inventory
        void open_inventory(void);
        void view_weapons(void);
        void view_armors(void);
        void view_potions(void);
        void view_skills(void);
        // Items and Currency
        void gain_coins(int amt);
        void buy_weapon(Weapon weapon);
        void buy_armor(Armor armor);
        void buy_heal_pot(void);
        void buy_mana_pot(void);
        void use_heal_pot(void);
        void use_mana_pot(void);
        bool has_weapon(Weapon weapon) const;
        bool has_armor(Armor armor) const;
        bool has_key(void) const;
        // Combat/Dungeon Interactions
        std::string attack(Entity& other) override;
        std::string use_skill(Entity& other);
        std::string great_slash(Entity& other);
        std::string life_steal(Entity& other);
        std::string tough_scales(void); 
        std::string soul_blast(Entity& other);
        int take_dmg(int amt) override; 
        void restore_def(void);
        void power_up(void);
        void rest(void) override;
        void respawn(int num_coins, int num_heal, int num_mana);
};

#endif