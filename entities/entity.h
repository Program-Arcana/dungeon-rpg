#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <vector>

class Entity {
    protected:
        std::string name;
        int hp;
        int max_hp;
        int min_dmg;
        int max_dmg;
    public:
        Entity(void);
        Entity(std::string name, int max_hp, int min_dmg, int max_dmg);
        std::string get_name(void) const;
        int get_hp(void) const;
        virtual std::string attack(Entity& other);
        virtual int take_dmg(int amt);
        virtual void print_enc_stats(void) const;
        bool is_dead(void) const;
        virtual void rest(void);
};

#endif