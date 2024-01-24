#include "Discount.h"

#include <cmath>
#include <iostream>

namespace PriceCalc {

void Normal::Reg(DiscMap& discountMap) {
    std::function<double(const double)> acceptCash = \
        [](const double money) noexcept { return money; };

    discountMap.emplace(DiscountType::CASH_NORMAL, acceptCash);
}

void PercentOff::Reg(DiscMap& discountMap){
    double rateCopy = rate;  // solve lambda escape problem
    std::function<double(const double)> acceptCash = \
        [rateCopy](const double money) noexcept { return money * rateCopy; };
    
    discountMap.emplace(type, acceptCash);
}

void CashBack::Reg(DiscMap& discountMap) {
        const double thresholdCopy = threshold;  // solve lambda escape problem
        const double cashbackCopy = cashback;

        std::function<double(const double)> acceptCash = \
            [thresholdCopy, cashbackCopy](const double money) noexcept { 
                return money - std::floor(money / thresholdCopy) * cashbackCopy; 
            };

        discountMap.emplace(DiscountType::CASH_BACK, acceptCash);
    }


DiscountMap::DiscountMap() {
    Normal normal;
    normal.Reg(map_);

    PercentOff percentOff_9(0.9, DiscountType::CASH_PERCENTOFF_10);
    percentOff_9.Reg(map_);

    PercentOff percentOff_8(0.8, DiscountType::CASH_PERCENTOFF_20);
    percentOff_8.Reg(map_);

    PercentOff percentOff_7(0.7, DiscountType::CASH_PERCENTOFF_30);
    percentOff_7.Reg(map_);

    CashBack cashBack(100.0, 20.0);
    cashBack.Reg(map_);

    std::cout << "DiscountMap constructor" << std::endl;
}

DiscountMap::~DiscountMap() {
    std::cout << "DiscountMap destructor" << std::endl;
};


}