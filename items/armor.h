#ifndef ARMOR_H
#define ARMOR_H
#include "item.h"

class Armor: public Item {
    protected:
        double prot;
    public:
        Armor(void);
        Armor(std::string name, double prot, int cost);
        double get_prot(void) const;
};

#endif