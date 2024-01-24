#pragma once

namespace PriceCal {

enum DiscountType { CASS_NORMAL, CASS_DISCOUNT_NINE, CASS_DISCOUNT_EIGHT, CASS_DISCOUNT_SEVEN, CASS_DIMINISH };

class PriceCalculator final {
public:
  double acceptCash(const DiscountType type, const double money) const noexcept;
};

} // namespace PriceCal
