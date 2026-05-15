#ifndef PRICE_STRATEGY_H
#define PRICE_STRATEGY_H

#include "MenuItem.h"
#include <vector>

// Bazinė strategijos klasė
class PriceStrategy {
public:
    virtual ~PriceStrategy() = default;
    virtual double calculate(const std::vector<MenuItem*>& items) const = 0;
};

class StandardPricing : public PriceStrategy {
public:
    double calculate(const std::vector<MenuItem*>& items) const override {
        double total = 0;
        for (MenuItem* item : items) {
            total += item->getBasePrice();
        }
        return total;
    }
};

class HappyHourPricing : public PriceStrategy {
public:
    double calculate(const std::vector<MenuItem*>& items) const override {
        double total = 0;
        for (MenuItem* item : items) {
            // Štai čia paprastas patikrinimas: jei tai gėrimas, kaina pusiau
            // Naudojame dynamic_cast, kad sužinotume, ar tai gėrimas
            if (dynamic_cast<const Drink*>(item) != nullptr) {
                total += item->getBasePrice() * 0.5; // 50% nuolaida gėrimams
            } else {
                total += item->getBasePrice(); // Maistui pilna kaina
            }
        }
        return total;
    }
};

class TakeAwayPricing : public PriceStrategy {
public:
    double calculate(const std::vector<MenuItem*>& items) const override {
        double total = 0;
        for (MenuItem* item : items) {
            total += item->getBasePrice() + 1.0; // Kaina + 1 euras už dėžutę/puodelį
        }
        return total;
    }
};

#endif