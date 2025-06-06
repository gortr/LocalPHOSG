#pragma once

#include <compare>
#include <stdexcept>
#include <string>

namespace phosg {

inline std::partial_ordering partial_order_for_strong_order(std::strong_ordering st_order) {
  if (st_order < 0) {
    return std::partial_ordering::less;
  } else if (st_order > 0) {
    return std::partial_ordering::greater;
  } else {
    return std::partial_ordering::equivalent;
  }
}

template <typename...>
struct always_false {
  static constexpr bool v = false;
};

template <typename T>
T enum_for_name(const char*) {
  static_assert(always_false<T>::v, "unspecialized enum_for_name should never be called");
  throw std::logic_error("unspecialized enum_for_name should never be called");
}

template <typename T>
T enum_for_name(const std::string& s) {
  return enum_for_name<T>(s.c_str());
}

template <typename T>
const char* name_for_enum(T) {
  static_assert(always_false<T>::v, "unspecialized name_for_enum should never be called");
  throw std::logic_error("unspecialized name_for_enum should never be called");
}

} // namespace phosg
