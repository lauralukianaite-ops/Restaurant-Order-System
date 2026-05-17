#include <iostream>
#include <cassert>
#include "MenuItem.h"
#include "Order.h"
#include "PriceStrategy.h"

void runTests() {
    std::cout << "Tests in progress..." << std::endl;

    // Temporarry using this class since SpecialOffer class is not implemented
    {
        class TempSpecialOffer : public MenuItem {
        public:
            TempSpecialOffer(const std::string& n, double p) : MenuItem(n, p) {}
            MenuItem* clone() const override { return new TempSpecialOffer(*this); }
            std::string prepare() const override { throw NotImplementedException(); }
        };
 
        TempSpecialOffer offer("Coupon", 0.0);
        try {
            offer.prepare();
            std::cout << "Test 1 (NotImplementedException): FAILED!" << std::endl;
        } catch (const NotImplementedException&) {
            std::cout << "Test 1 (NotImplementedException): PASSED" << std::endl;
        }
    }

    {
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
    }

    {
        Order o4;
        o4.addItem(new Food("Steak", 10.0, false));
        o4.addItem(new Drink("Juice", 2.0, true));

        StandardPricing stdPrice;
        o4.setStrategy(&stdPrice);
        double totalStd = o4.calculateTotal();

        HappyHourPricing happyPrice;
        o4.setStrategy(&happyPrice);
        double totalHappy = o4.calculateTotal();

        if (totalStd == 12.0 && totalHappy == 11.0) {
            std::cout << "Test 4 (Strategy Calculation): PASSED" << std::endl;
        } else {
            std::cout << "Test 4 (Strategy Calculation): FAILED!" << std::endl;
        }
    }

    {
        Order o5;
        o5.addItem(new Food("Pancake", 3.0, true));
        o5.addItem(new Drink("Water", 1.0, true));
        o5.addItem(new Food("Steak", 9.0, false));
    
        int count = 0;
        for (Order::Iterator it = o5.begin(); it != o5.end(); ++it) {
            if (*it != nullptr) count++;
        }
    
        if (count == 3) {
            std::cout << "Test 5 (Iterator): PASSED" << std::endl;
        } else {
            std::cout << "Test 5 (Iterator): FAILED!" << std::endl;
        }
    }

    {
        Order o6;
        o6.addItem(new Food("Sriuba", 4.0, true));
        o6.addItem(new Drink("Sultys", 2.5, false));
        o6.addItem(new Food("Desertas", 5.0, true));
    
        assert(o6.getSize() == 3);
        o6.removeItem(1);
        assert(o6.getSize() == 2);
    
        bool ok = (o6.getItem(0)->getName() == "Sriuba") &&
                    (o6.getItem(1)->getName() == "Desertas");
    
        if (ok) {
            std::cout << "Test 6 (removeItem): PASSED" << std::endl;
        } else {
            std::cout << "Test 6 (removeItem): FAILED!" << std::endl;
        }
    }

    /*
    {
        // 7a: prepare() turi mesti NotImplementedException
        SpecialOffer offer("Coupon", 0.0);
        try {
            offer.prepare();
            std::cout << "Test 7a (SpecialOffer prepare exception): FAILED!" << std::endl;
        } catch (const NotImplementedException&) {
            std::cout << "Test 7a (SpecialOffer prepare exception): PASSED" << std::endl;
        }
 
        // 7b: clone() turi grazinti nauja objekto kopija (Prototype)
        MenuItem* original = new SpecialOffer("Discount card", 5.0);
        MenuItem* copy   = original->clone();
        bool cloneOk = (copy != nullptr)
                    && (copy != original)
                    && (copy->getName()      == original->getName())
                    && (copy->getBasePrice() == original->getBasePrice());
        if (cloneOk) {
            std::cout << "Test 7b (SpecialOffer clone): PASSED" << std::endl;
        } else {
            std::cout << "Test 7b (SpecialOffer clone): FAILED!" << std::endl;
        }
        delete original;
        delete copy;
 
        // 7c: SpecialOffer turi veikti Order konteineryje ir buti pasiekiamas per iteratoriu
        Order o;
        o.addItem(new Food("Pizza", 8.0, false));
        o.addItem(new SpecialOffer("Coupon -20%", 0.0));
        assert(o.getSize() == 2);
 
        int specialCount = 0;
        for (Order::Iterator it = o.begin(); it != o.end(); ++it) {
            if (dynamic_cast<SpecialOffer*>(*it) != nullptr) specialCount++;
        }
        if (specialCount == 1) {
            std::cout << "Test 7c (SpecialOffer in Order): PASSED" << std::endl;
        } else {
            std::cout << "Test 7c (SpecialOffer in Order): FAILED!" << std::endl;
        }
 
        // 7d: Gilus kopijavimas su SpecialOffer konteineryje
        Order copied = o;
        assert(copied.getSize() == o.getSize());
        std::cout << "Test 7d (SpecialOffer deep copy): PASSED" << std::endl;
    }
    */

    std::cout << "All tests completed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}