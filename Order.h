#ifndef ORDER_H
#define ORDER_H

#include "MenuItem.h"
#include <cstddef>

// Išankstinė deklaracija
class OrderImpl;
class PriceStrategy; // Reikės vėliau strategijai

class Order {
private:
    OrderImpl* impl; // PImpl

class StrategyNotSet : public std::logic_error {
public:
    StrategyNotSet() : std::logic_error("Klaida: Skaiciavimo strategija nenustatyta!") {}
};

public:
    Order();
    ~Order();
    
    // Gilus kopijavimas
    Order(const Order& other);
    Order& operator=(const Order& other);

    void addItem(MenuItem* item);
    size_t getSize() const;
    MenuItem* getItem(size_t index) const;

    // Iteratorius
    class Iterator {
    private:
        MenuItem** current; // Rodyklė į masyvo elementa
    public:
        Iterator(MenuItem** ptr) : current(ptr) {}
        
        MenuItem* operator*() const { return *current; }
        Iterator& operator++() { current++; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin();
    Iterator end();
};

#endif