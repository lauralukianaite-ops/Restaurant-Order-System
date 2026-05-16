#include "Order.h"
#include "PriceStrategy.h"
#include <vector>

class OrderImpl {
public:
    std::vector<MenuItem*> items;
    PriceStrategy* currentStrategy = nullptr;
    ~OrderImpl() {
        for (MenuItem* item : items) {
            delete item;
        }
        items.clear();
    }
};

Order::Order() {
    impl = new OrderImpl();
}

Order::~Order() {
    delete impl;
}

// Deep Copy
Order::Order(const Order& other) {
    impl = new OrderImpl();
    for (MenuItem* item : other.impl->items) {
        this->impl->items.push_back(item->clone()); 
    }
}

Order& Order::operator=(const Order& other) {
    if (this != &other) {
        delete impl;
        impl = new OrderImpl();
        for (MenuItem* item : other.impl->items) {
            this->impl->items.push_back(item->clone());
        }
    }
    return *this;
}

void Order::addItem(MenuItem* item) {
    impl->items.push_back(item);
}

size_t Order::getSize() const {
    return impl->items.size();
}

MenuItem* Order::getItem(size_t index) const {
    if (index >= impl->items.size()) return nullptr;
    return impl->items[index];
}

Order::Iterator Order::begin() {
    if (impl->items.empty()) return Iterator(nullptr);
    return Iterator(&impl->items[0]);
}

Order::Iterator Order::end() {
    if (impl->items.empty()) return Iterator(nullptr);
    return Iterator(&impl->items[0] + impl->items.size());
}

void Order::setStrategy(PriceStrategy* strategy) {
    impl->currentStrategy = strategy;
}

double Order::calculateTotal() const {
    if (impl->currentStrategy == nullptr) {
        throw StrategyNotSet();
    }
    return impl->currentStrategy->calculate(impl->items);
}

Order Order::filterItems(std::function<bool(MenuItem*)> callback) const {
    Order filteredOrder;
    for (MenuItem* item : impl->items) {
        if (callback(item)) {
            filteredOrder.addItem(item->clone());
        }
    }
    return filteredOrder;
}