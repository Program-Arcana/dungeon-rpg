#include "skill.h"

Skill::Skill(std::string name, std::string desc, int cost, bool unlocked) {
    this->name = name;
    this->desc = desc;
    this->cost = cost;
    this->unlocked = unlocked;
}

std::string Skill::get_desc(void) const {
    /**
     * Gets the description of the skill
     * @return: a string representing skill description
     */
    return this->desc;
}

bool Skill::is_unlocked(void) const {
    /**
     * Checks if the skill has been unlocked
     * @return: true if it has, false otherwise
     */
    return this->unlocked;
}

void Skill::unlock(void) {
    /**
     * Unlocks this skill
     */
    this->unlocked = true;
}