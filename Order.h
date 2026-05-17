#ifndef ORDER_H
#define ORDER_H

#include "MenuItem.h"
#include <functional>
#include <cstddef>

class OrderImpl;
class PriceStrategy;

class StrategyNotSet : public std::logic_error {
public:
    StrategyNotSet() : std::logic_error("Error: calculation strategy is not set!") {}
};

class Order {
private:
    OrderImpl* impl;

public:
    Order();
    ~Order();

    Order(const Order& other);
    Order& operator=(const Order& other);

    void removeItem(size_t index);
    void addItem(MenuItem* item);
    size_t getSize() const;
    MenuItem* getItem(size_t index) const;
    
    void setStrategy(PriceStrategy* strategy);
    double calculateTotal() const;
    Order filterItems(std::function<bool(MenuItem*)> callback) const;

    std::vector<std::string> prepareAll() const;

    class Iterator {
    private:
        MenuItem** current;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = MenuItem*;
        using difference_type = std::ptrdiff_t;
        using pointer = MenuItem**;
        using reference = MenuItem*&;

        Iterator(MenuItem** ptr) : current(ptr) {}
        
        MenuItem* operator*() const { 
            if (current == nullptr) return nullptr;
            return *current; 
        }

        Iterator& operator++() { 
            if (current != nullptr) current++; 
            return *this;
        }

        Iterator operator++(int) { 
            Iterator tmp = *this; 
            if (current != nullptr) current++; 
            return tmp; 
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin();
    Iterator end();
};

#endif