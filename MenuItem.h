#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>
#include <stdexcept>

class NotImplementedException : public std::logic_error {
public:
    NotImplementedException() : std::logic_error("Error! This method is not supported for this type of element!") {}
};

class MenuItem {
protected:
    std::string name;
    double basePrice;

public:
    MenuItem(const std::string& name, double price);
    virtual ~MenuItem() = default;

    std::string getName() const;
    double getBasePrice() const;

    virtual MenuItem* clone() const = 0;

    virtual std::string prepare() const = 0;

    virtual bool operator<(const MenuItem& other) const;
};

class Food : public MenuItem {
private:
    bool isVegan;

public:
    Food(const std::string& name, double price, bool vegan);
    
    MenuItem* clone() const override;
    std::string prepare() const override;
    
    bool getIsVegan() const;
};

class Drink : public MenuItem {
private:
    bool cold;

public:
    Drink(const std::string& name, double price, bool isCold);
    
    MenuItem* clone() const override;
    std::string prepare() const override;

    bool isCold() const;
};

#endif