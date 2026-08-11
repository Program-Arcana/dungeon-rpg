#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item {
    protected:
        std::string name;
        int cost;
    public:
        std::string get_name(void) const;
        int get_cost(void) const;
};

#endif