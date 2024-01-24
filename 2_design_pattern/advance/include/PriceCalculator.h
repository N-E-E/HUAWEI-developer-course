#ifndef PRICE_CALCULATOR_H
#define PRICE_CALCULATOR_H

#include "Discount.h"

namespace PriceCalc
{

/**
* Top class of this calculator.
**/
class PriceCalculator final
{
public:
    double AcceptCash(const DiscountType discountType, const double money) const noexcept;

};

}  // namespace PriceCalc

#endif