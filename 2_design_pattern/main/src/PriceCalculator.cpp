#include "PriceCalculator.h"
#include "Discount.h"

#include <memory>
#include <unordered_map>

namespace PriceCalc
{
double PriceCalculator::AcceptCash(const DiscountType discountType, const double money) const noexcept
{
    DiscountMap& discountMap = DiscountMap::GetIntance();
    DiscMap& innerMap = discountMap.GetMap();

    return innerMap.find(discountType)->second->AcceptCash(money);
}
}  // namespace PriceCalc