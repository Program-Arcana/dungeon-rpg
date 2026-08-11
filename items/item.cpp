#include "item.h"

std::string Item::get_name(void) const {
    /**
     * Gets the name of the item
     * @return: a string representing the item name
     */
    return this->name;
}

int Item::get_cost(void) const {
    /**
     * Gets the cost of the item
     * @return: an int representing the item cost
     */
    return this->cost;
}
