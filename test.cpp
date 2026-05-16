#include <iostream>
#include <cassert>
#include "MenuItem.h"
#include "Order.h"
#include "PriceStrategy.h"

class SpecialOffer : public MenuItem {
public:
    SpecialOffer(const std::string& name, double price) : MenuItem(name, price) {}
    MenuItem* clone() const override { return new SpecialOffer(*this); }
    
    std::string prepare() const override {
        throw NotImplementedException();
    }
};

void runTests() {
    std::cout << "Tests in progress..." << std::endl;

    SpecialOffer offer("Coupon", 0.0);
    try {
        offer.prepare();
        std::cout << "Test 1 (Exception): FAILED!" << std::endl;
    } catch (const NotImplementedException& e) {
        std::cout << "Test 1 (Exception): PASSED" << std::endl;
    }

    Order o1;
    o1.addItem(new Food("Pancakes", 5.0, true));
    Order o2 = o1;
    assert(o1.getSize() == o2.getSize());
    std::cout << "Test 2 (Deep Copy): PASSED" << std::endl;

    Order o3;
    o3.addItem(new Drink("Water", 1.0, true));
    try {
        o3.calculateTotal();
        std::cout << "Test 3 (Strategy Error): FAILED!" << std::endl;
    } catch (const StrategyNotSet& e) {
        std::cout << "Test 3 (Strategy Error): PASSED" << std::endl;
    }

    std::cout << "All tests completed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}