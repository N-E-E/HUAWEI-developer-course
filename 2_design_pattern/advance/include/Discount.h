#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <functional>
#include <unordered_map>

enum class DiscountType {
    CASH_NORMAL,
    CASH_PERCENTOFF_10,
    CASH_PERCENTOFF_20,
    CASH_PERCENTOFF_30,
    CASH_BACK,
};

namespace PriceCalc 
{
using DiscMap = std::unordered_map<DiscountType, std::function<double(const double)>>;

/**
* calculate price originally
*/
class Normal final {
public:
    void Reg(DiscMap& discountMap);
};

/**
* calculate price in percent-off rule
*/
class PercentOff final {
public:
    // NOTES: constructor need a type param
    explicit PercentOff(double rate, DiscountType type) : rate(rate), type(type) {}  
    void Reg(DiscMap& discountMap);

private:
    const double rate;
    DiscountType type;
};

/**
* calculate price in cash-back rule. eg. 100 - 20.
*/
class CashBack final {
public:
    explicit CashBack(double threshold = 100.0, double cashback = 20.0) : 
        threshold(threshold), cashback(cashback) {}

    void Reg(DiscMap& discountMap);

private:
    const double threshold;
    const double cashback;
};

/**
* DiscountMap Singleton. store price calculation methods
*/
class DiscountMap {
public:
    static DiscountMap& GetInstance() {
        static DiscountMap discountMap;
        return discountMap;
    }

    DiscMap& GetMap() { return map_; }
private:
    DiscMap map_;

    DiscountMap();
    ~DiscountMap();

    // forbidden move/copy operation
    DiscountMap(const DiscountMap& other) = delete;
    DiscountMap(DiscountMap&& other) = delete;
    DiscountMap& operator=(const DiscountMap& other) = delete;
    DiscountMap& operator=(DiscountMap&& other) = delete;
};

}

#endif