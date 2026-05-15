#include "Order.h"
#include "PriceStrategy.h"
#include <vector>

class OrderImpl {
public:
    std::vector<MenuItem*> items;
    PriceStrategy* currentStrategy = nullptr; // Iš pradžių strategijos nėra
    ~OrderImpl() {
        for (MenuItem* item : items) {
            delete item;
        }
        items.clear();
    }
    void setStrategy(PriceStrategy* strategy);
    double calculateTotal() const;


};

Order::Order() {
    impl = new OrderImpl();
}

Order::~Order() {
    delete impl;
}

// Deep Copy
// Naudojamas Prototype šablonas
Order::Order(const Order& other) {
    impl = new OrderImpl();
    for (MenuItem* item : other.impl->items) {
        // Įsidedame ne tą pačią rodyklę, o gilią objekto kopiją
        this->impl->items.push_back(item->clone()); 
    }
}

// Priskyrimo operatorius (=) - irgi gilus kopijavimas
Order& Order::operator=(const Order& other) {
    if (this != &other) {
        delete impl; // Išvalome senus duomenis
        impl = new OrderImpl();
        for (MenuItem* item : other.impl->items) {
            this->impl->items.push_back(item->clone());
        }
    }
    return *this;
}

// CRUD: Pridedamas elementas
void Order::addItem(MenuItem* item) {
    impl->items.push_back(item);
}

// CRUD: Sužinomas kiekis
size_t Order::getSize() const {
    return impl->items.size();
}

// CRUD: Gaunamas elementas pagal indeksą
MenuItem* Order::getItem(size_t index) const {
    if (index >= impl->items.size()) return nullptr;
    return impl->items[index];
}

// 4. ITERATORIAUS METODAI
// begin() grąžina iteratorių, rodantį į patį pirmą vektoriaus elementą
Order::Iterator Order::begin() {
    if (impl->items.empty()) return Iterator(nullptr);
    return Iterator(&impl->items[0]);
}

// end() grąžina iteratorių, rodantį į vietą UŽ paskutinio elemento
Order::Iterator Order::end() {
    if (impl->items.empty()) return Iterator(nullptr);
    return Iterator(&impl->items[0] + impl->items.size());
}

// Nustatome arba pakeičiame strategiją
void Order::setStrategy(PriceStrategy* strategy) {
    impl->currentStrategy = strategy;
}

// Skaičiuojama galutine suma
double Order::calculateTotal() const {
    // Jei dėstytojas nepakirto strategijos - metam klaidą!
    if (impl->currentStrategy == nullptr) {
        throw StrategyNotSet();
    }
    // Deleguojame darbą pasirinktai strategijai
    return impl->currentStrategy->calculate(impl->items);
}