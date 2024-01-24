#include "PriceCalculator.h"
#include "Discount.h"

#include <unordered_map>

namespace PriceCalc
{
double PriceCalculator::AcceptCash(const DiscountType discountType, const double money) const noexcept
{
    DiscountMap& discountMap = DiscountMap::GetInstance();
    DiscMap& innerMap = discountMap.GetMap();
    
    return innerMap.find(discountType)->second(money);
}
}  // namespace PriceCalc