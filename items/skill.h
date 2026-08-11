#ifndef SKILL_H
#define SKILL_H
#include "item.h"

class Skill: public Item {
    private:
        std::string desc;
        bool unlocked;
    public:
        Skill(std::string name, std::string desc, int cost, bool unlocked);
        std::string get_desc(void) const;
        bool is_unlocked(void) const;
        void unlock(void);

};

#endif