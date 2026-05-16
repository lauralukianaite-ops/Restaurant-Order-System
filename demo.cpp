#include <iostream>
#include <algorithm>
#include "MenuItem.h"
#include "Order.h"
#include "PriceStrategy.h"

void printItemInfo(MenuItem* item) {
    std::cout << "- " << item->getName() << " (" << item->getBasePrice() << " EUR)" << std::endl;
}

int main() {
    std::cout << "=== RESTAURANT'S MANAGEMENT SYSTEM DEMO ===" << std::endl;

    MenuItem* pizza = new Food("Pizza Pepperoni", 8.50, true);
    MenuItem* steak = new Food("Pork steak", 12.00, false);
    MenuItem* cola = new Drink("Coca Cola", 2.50, true);
    MenuItem* tea = new Drink("Hot coffee", 2.00, false);

    Order myOrder;
    myOrder.addItem(pizza);
    myOrder.addItem(steak);
    myOrder.addItem(cola);
    myOrder.addItem(tea);

    std::cout << "\n--- Preparint the order (Polymorphism) ---" << std::endl;
    //polymorphism
    for (size_t i = 0; i < myOrder.getSize(); ++i) {
        std::cout << myOrder.getItem(i)->prepare() << std::endl;
    }

    std::cout << "\n--- Checking temperature of the drink (dynamic_cast) ---" << std::endl;
    for (size_t i = 0; i < myOrder.getSize(); ++i) {
        MenuItem* item = myOrder.getItem(i);
        Drink* drinkPtr = dynamic_cast<Drink*>(item);
        if (drinkPtr != nullptr) {
            std::cout << drinkPtr->getName() << " is " 
                      << (drinkPtr->isCold() ? "COLD" : "HOT") << std::endl;
        }
    }

    StandardPricing stdPrice;
    HappyHourPricing happyPrice;

    std::cout << "\n--- Calculating total price with different strategies ---" << std::endl;
    //strategy
    myOrder.setStrategy(&stdPrice);
    std::cout << "Standart price: " << myOrder.calculateTotal() << " EUR" << std::endl;

    myOrder.setStrategy(&happyPrice);
    std::cout << "Happy Hour price: " << myOrder.calculateTotal() << " EUR" << std::endl;

    std::cout << "\n--- Using Iterator ---" << std::endl;
    //iterator
    std::for_each(myOrder.begin(), myOrder.end(), printItemInfo);

    std::cout << "\n--- Deep copy of the container ---" << std::endl;
    //deep copy
    Order copiedOrder = myOrder;
    std::cout << "Original order size: " << myOrder.getSize() << std::endl;
    std::cout << "Copied order size: " << copiedOrder.getSize() << std::endl;

    std::cout << "\n--- Filtering elements (Callback) ---" << std::endl;
    // callback
    // Pirmoji versija: filtruojame tik veganiska maista
    Order veganMenu = myOrder.filterItems([](MenuItem* item) {
        Food* foodPtr = dynamic_cast<Food*>(item);
        return (foodPtr != nullptr && foodPtr->getIsVegan());
    });

    // Antroji versija: filtruojame elementus, kurie kainuoja maziau nei 5 EUR
    Order cheapMenu = myOrder.filterItems([](MenuItem* item) {
        return item->getBasePrice() < 5.0;
    });

    std::cout << "Vegan orders count: " << veganMenu.getSize() << std::endl;
    std::cout << "Cheaper elements (<5 EUR) count: " << cheapMenu.getSize() << std::endl;

    return 0;
}