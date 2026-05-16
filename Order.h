#ifndef ORDER_H
#define ORDER_H

#include "MenuItem.h"
#include <functional>
#include <cstddef>

// Išankstinė deklaracija
class OrderImpl;
class PriceStrategy; // Reikės vėliau strategijai

class StrategyNotSet : public std::logic_error {
public:
    StrategyNotSet() : std::logic_error("Klaida: Skaiciavimo strategija nenustatyta!") {}
};

class Order {
private:
    OrderImpl* impl; // PImpl

public:
    Order();
    ~Order();
    
    // Gilus kopijavimas
    Order(const Order& other);
    Order& operator=(const Order& other);

    void addItem(MenuItem* item);
    size_t getSize() const;
    MenuItem* getItem(size_t index) const;
    
    void setStrategy(PriceStrategy* strategy);
    double calculateTotal() const;
    Order filterItems(std::function<bool(MenuItem*)> callback) const;

    // Iteratorius
    class Iterator {
    private:
        MenuItem** current; // Rodyklė į masyvo elementa
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = MenuItem*;
        using difference_type = std::ptrdiff_t;
        using pointer = MenuItem**;
        using reference = MenuItem*&;

        Iterator(MenuItem** ptr) : current(ptr) {}
        
        MenuItem* operator*() const { return *current; }
        Iterator& operator++() { current++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; current++; return tmp; }
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin();
    Iterator end();
};

#endif