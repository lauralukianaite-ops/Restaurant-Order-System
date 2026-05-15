#include <iostream>
#include <algorithm>
#include "MenuItem.h"
#include "Order.h"
#include "PriceStrategy.h"

int main() {
    std::cout << "=== RESTORANO VALDYMO SISTEMA DEMO ===" << std::endl;

    MenuItem* pizza = new Food("Pica Margarita", 8.50, true);
    MenuItem* steak = new Food("Kiaulienos kepsnys", 12.00, false);
    MenuItem* cola = new Drink("Coca Cola", 2.50, true);
    MenuItem* tea = new Drink("Karšta kava", 2.00, false);

    // Sukuriamas užsakymas
    Order myOrder;
    myOrder.addItem(pizza);
    myOrder.addItem(steak);
    myOrder.addItem(cola);
    myOrder.addItem(tea);

    // POLIMORFIZMO DEMONSTRACIJA
    std::cout << "\n--- Paruosiamas uzsakymas (Polimorfizmas) ---" << std::endl;
    for (size_t i = 0; i < myOrder.getSize(); ++i) {
        std::cout << myOrder.getItem(i)->prepare() << std::endl;
    }

    // DYNAMIC_CAST DEMONSTRACIJA (tikrinama ar gėrimas šaltas)
    std::cout << "\n--- Tikrinama gerimu temperatura (dynamic_cast) ---" << std::endl;
    for (size_t i = 0; i < myOrder.getSize(); ++i) {
        MenuItem* item = myOrder.getItem(i);
        Drink* drinkPtr = dynamic_cast<Drink*>(item);
        if (drinkPtr != nullptr) {
            std::cout << drinkPtr->getName() << " yra " 
                      << (drinkPtr->isCold() ? "SALTAS" : "KARSTAS") << std::endl;
        }
    }

    // STRATEGIJOS DEMONSTRACIJA
    std::cout << "\n--- Skaiciuojame kaina su skirtingomis strategijomis ---" << std::endl;
    StandardPricing stdPrice;
    HappyHourPricing happyPrice;
    TakeAwayPricing takePrice;

    try {
        // Tikriname, ar meta klaidą, jei strategija nenustatyta
        std::cout << "Bandom skaiciuoti be strategijos: " << myOrder.calculateTotal() << std::endl;
    } catch (const StrategyNotSet& e) {
        std::cout << "Pagauta isimtis: " << e.what() << std::endl;
    }

    // strategy
    myOrder.setStrategy(&stdPrice);
    std::cout << "Standartine kaina: " << myOrder.calculateTotal() << " EUR" << std::endl;

    myOrder.setStrategy(&happyPrice);
    std::cout << "Happy Hour kaina (nuolaida gerimams): " << myOrder.calculateTotal() << " EUR" << std::endl;

    myOrder.setStrategy(&takePrice);
    std::cout << "Take Away kaina (+1 EUR uz pakuote): " << myOrder.calculateTotal() << " EUR" << std::endl;

    //ITERATORIAUS DEMONSTRACIJA
    std::cout << "\n--- Naudojame musu iteratoriu ---" << std::endl;
    // iterator
    for (Order::Iterator it = myOrder.begin(); it != myOrder.end(); ++it) {
        std::cout << "- " << (*it)->getName() << " (" << (*it)->getBasePrice() << " EUR)" << std::endl;
    }

    // 5. GILUS KOPIJAVIMAS (Deep Copy)
    std::cout << "\n--- Darome gilia konteinerio kopija ---" << std::endl;
    // deep copy
    Order copiedOrder = myOrder;
    std::cout << "Originalaus uzsakymo dydis: " << myOrder.getSize() << std::endl;
    std::cout << "Kopijuoto uzsakymo dydis: " << copiedOrder.getSize() << std::endl;

    // 6. CALLBACK FILTRAVIMAS
    std::cout << "\n--- Filtruojame tik vegetariska maista (Callback) ---" << std::endl;
    // callback
    Order veganMenu = myOrder.filterItems([](MenuItem* item) {
        Food* foodPtr = dynamic_cast<Food*>(item);
        return (foodPtr != nullptr && foodPtr->getIsVegan());
    });

    for (Order::Iterator it = veganMenu.begin(); it != veganMenu.end(); ++it) {
        std::cout << "Rastas veganiskas patiekalas: " << (*it)->getName() << std::endl;
    }

    std::cout << "\n=== DEMO PABAIGA ===" << std::endl;
    return 0;
}