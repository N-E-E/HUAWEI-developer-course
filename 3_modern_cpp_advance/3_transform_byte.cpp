#include <array>
#include <cstddef>
#include <cstdint>

using namespace std;

/*
 * 编写函数ToByteArray完成以下功能（练习2扩展）：
 * 通过大括号列表的方式传入一个数值型数组，构造出元素类型为std::byte的std::array对象，
 * std::array中的元素个数根据传入的数组元素类型与个数推导出来，具体要求如下：
 * 1.要求函数可以在编译期计算出结果，可以使用static_assert测试函数功能正确性。
 * 2.传入数组类型为uint8_t，则一个数值转换为1个byte。
 * 3.传入数组类型为uint16_t，则一个数值转换为2个byte。
 * 附加题（可选做）：
 * 编写函数RestoreArray将byte数组提取回原始数组，返回值为原始类型array对象。
 */

template <typename T, size_t N>
constexpr auto ToByteArray(const T (&nums)[N]) noexcept {
  constexpr size_t arraySize = N * sizeof(T);

  std::array<std::byte, arraySize> result{};

  if (sizeof(T) == 1) {
    for (size_t i = 0; i < N; ++i) {
      result[i] = static_cast<std::byte>(nums[i]);
    }
  } else if (sizeof(T) == 2) {
    for (size_t i = 0; i < N; ++i) {
      result[i * 2] = static_cast<std::byte>(nums[i] >> 8);
      result[i * 2 + 1] = static_cast<std::byte>(nums[i] & 0xFF);
    }
  }

  return result;
}

template <typename T, size_t N>
constexpr auto RestoreArray(const std::array<std::byte, N> &bytes) noexcept {
  constexpr size_t arraySize = N / sizeof(T);

  std::array<T, arraySize> arr{}; // use std::array is easy.

  if (sizeof(T) == 1) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = static_cast<T>(bytes[i]);
    }
  } else {
    for (size_t i = 0; i < N / 2; ++i) {
      arr[i] = static_cast<T>(bytes[i * 2]) << 8 |
               (static_cast<T>(bytes[i * 2 + 1]));
    }
  }
  return arr;
}

void TestForUint8() {
  constexpr uint8_t arr1[]{1, 2, 3, 4};
  constexpr auto bytes = ToByteArray(arr1);
  static_assert(bytes.size() == 4);
  static_assert(to_integer<int>(bytes[0]) == 1);
  static_assert(to_integer<int>(bytes[1]) == 2);
  static_assert(to_integer<int>(bytes[2]) == 3);
  static_assert(to_integer<int>(bytes[3]) == 4);

  constexpr auto arr2 = RestoreArray<uint8_t>(bytes);
  static_assert(arr2.size() == 4);
  static_assert(arr2[0] == 1);
  static_assert(arr2[1] == 2);
  static_assert(arr2[2] == 3);
  static_assert(arr2[3] == 4);
}

void TestForUint16() {
  constexpr uint16_t arr1[]{256, 257, 258, 259};
  constexpr auto bytes = ToByteArray(arr1);
  static_assert(bytes.size() == 8);
  static_assert(to_integer<int>(bytes[0]) == 1);
  static_assert(to_integer<int>(bytes[1]) == 0);
  static_assert(to_integer<int>(bytes[2]) == 1);
  static_assert(to_integer<int>(bytes[3]) == 1);
  static_assert(to_integer<int>(bytes[4]) == 1);
  static_assert(to_integer<int>(bytes[5]) == 2);
  static_assert(to_integer<int>(bytes[6]) == 1);
  static_assert(to_integer<int>(bytes[7]) == 3);

  constexpr auto arr2 = RestoreArray<uint16_t>(bytes);
  static_assert(arr2.size() == 4);
  static_assert(arr2[0] == 256);
  static_assert(arr2[1] == 257);
  static_assert(arr2[2] == 258);
  static_assert(arr2[3] == 259);
}

int main() {
  TestForUint8();
  TestForUint16();
  return 0;
}