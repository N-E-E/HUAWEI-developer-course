#include "Discount.h"

#include <iostream>
#include <cmath>

namespace PriceCalc 
{

double Normal::AcceptCash(const double money) const noexcept{
    return money;
}

double PercentOff::AcceptCash(const double money) const noexcept {
    return money * rate;
}

double CashBack::AcceptCash(const double money) const noexcept {
    // const double threshold = 100.0;
    // const double cashback = 20.0;
    return money - std::floor(money / threshold) * cashback;
}

DiscountMap::DiscountMap() {
    map_.emplace(DiscountType::CASH_NORMAL, std::make_unique<Normal>());
    map_.emplace(DiscountType::CASH_PERCENTOFF_10, std::make_unique<PercentOff>(0.9));
    map_.emplace(DiscountType::CASH_PERCENTOFF_20, std::make_unique<PercentOff>(0.8));
    map_.emplace(DiscountType::CASH_PERCENTOFF_30, std::make_unique<PercentOff>(0.7));
    map_.emplace(DiscountType::CASH_BACK, std::make_unique<CashBack>(100.0, 20.0));
    std::cout << "discountMap constructed" << std::endl;
};

DiscountMap::~DiscountMap() {
    std::cout << "discountMap destructed" << std::endl;
}

}  // namespace PriceCalc