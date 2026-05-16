#ifndef PRICE_STRATEGY_H
#define PRICE_STRATEGY_H

#include "MenuItem.h"
#include <vector>

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
            if (dynamic_cast<const Drink*>(item) != nullptr) {
                total += item->getBasePrice() * 0.5;
            } else {
                total += item->getBasePrice();
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
            total += item->getBasePrice() + 1.0;
        }
        return total;
    }
};

#endif