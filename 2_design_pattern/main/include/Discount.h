#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <unordered_map>
#include <memory>

enum class DiscountType {
    CASH_NORMAL,
    CASH_PERCENTOFF_10,
    CASH_PERCENTOFF_20,
    CASH_PERCENTOFF_30,
    CASH_BACK,
};

namespace PriceCalc 
{
/* 
* Discount: base class of calculate methods
* new methods must inherit Discount
*/
class Discount {
public:
    virtual double AcceptCash(const double money) const noexcept = 0;

    virtual ~Discount() {}
};

using DiscMap = std::unordered_map<DiscountType, std::unique_ptr<Discount>>;

/*
* normal method
*/
class Normal final : public Discount {
public:
    double AcceptCash(const double money) const noexcept;
};

/*
* percent-off method
*/
class PercentOff final : public Discount {
public:
    explicit PercentOff(double rate) : rate(rate) {}

    double AcceptCash(const double money) const noexcept;

private:
    const double rate;
};

/*
* cash-back method. eg. 100 - 20.
*/
class CashBack final : public Discount {
public:
    explicit CashBack(double threshold, double cashback) : threshold(threshold), cashback(cashback) {}

    double AcceptCash(const double money) const noexcept;

private:
    const double threshold;
    const double cashback;
};

/*
* DiscountMap: Singleton implemetation for table-driven mode.
**/
class DiscountMap {  // Singleton.
public:
    static DiscountMap& GetIntance() {
        static DiscountMap discountMap;
        return discountMap;
    };

    DiscMap& GetMap() { return map_; }
private:
    DiscMap map_;

    DiscountMap();
    ~DiscountMap();

    // forbidden the copy/move of class.
    DiscountMap(const DiscountMap& other) = delete;
    DiscountMap& operator=(const DiscountMap& other) = delete;
    DiscountMap(DiscountMap &&other) = delete;
    DiscountMap& operator=(DiscountMap&& other) = delete;
    
};

}  // namespace PriceCalc


#endif