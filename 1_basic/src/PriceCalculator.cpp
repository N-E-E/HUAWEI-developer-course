#include "PriceCalculator.h"
#include <cmath>

using namespace PriceCal;

double PriceCalculator::acceptCash(const DiscountType type, const double money) const noexcept {
  double ans = 0.f;
  switch (type) {
    case DiscountType::CASS_NORMAL:
      ans = money;
      break;
    case DiscountType::CASS_DISCOUNT_NINE:
      ans = money * 0.9;
      break;
    case DiscountType::CASS_DISCOUNT_EIGHT:
      ans = money * 0.8;
      break;
    case DiscountType::CASS_DISCOUNT_SEVEN:
      ans = money * 0.7;
      break;
    case DiscountType::CASS_DIMINISH:
      ans = money - std::floor(money / 100.0) * 20;
    default:
      break;
  }
  return ans;
}
