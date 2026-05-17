#include "MenuItem.h"

MenuItem::MenuItem(const std::string& name, double price) : name(name), basePrice(price) {}

std::string MenuItem::getName() const { return name; }
double MenuItem::getBasePrice() const { return basePrice; }
bool MenuItem::operator<(const MenuItem& other) const { return this->basePrice < other.basePrice; }

Food::Food(const std::string& name, double price, bool vegan) 
    : MenuItem(name, price), isVegan(vegan) {}

MenuItem* Food::clone() const {
    return new Food(*this);
}

std::string Food::prepare() const {
    return "Dish preparing: " + name + " (Cooking in the kitchen...)";
}

bool Food::getIsVegan() const { return isVegan; }