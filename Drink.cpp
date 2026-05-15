#include "MenuItem.h"

Drink::Drink(const std::string& name, double price, bool isCold) 
    : MenuItem(name, price), cold(isCold) {}

MenuItem* Drink::clone() const {
    return new Drink(*this); // Prototype šablonas
}

std::string Drink::prepare() const {
    return "Pilstomas gerimas: " + name + " (Ipilama i stikline...)";
}

bool Drink::isCold() const { return cold; }