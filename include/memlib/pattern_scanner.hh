#pragma once

#include <cstdint>
#include <cstddef>

#include <metapp/metapp.hh>

namespace mem {

namespace details {
constexpr auto char_to_nibble(const char _c) -> mpp::u8 {
  const mpp::u8 c = static_cast<mpp::u8>(_c);
  if (c == '?') {
    return 0;
  }

  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 0xA;
  } else if (c >= 'a' && c <= 'f') {
    return c - 'a' + 0xa;
  }

  return 0;
}
} // namespace mem::details

struct PatternFragment {
  mpp::u8 byte;
  bool    masked;
};

template <std::size_t n>
struct Pattern {
  static_assert((n % 3) == 0); // [31/10/2023 - r] This can be a `requires` but maybe i'll add a assert message.
  static constexpr std::size_t nfragments = n / 3;
  consteval Pattern(const char (& str)[n]) {
    for (std::size_t i = 0; i < nfragments; ++i) {
      const auto & chunk = &str[i * 3]; 
      fragments[i] = {
        .byte   = static_cast<mpp::u8>(details::char_to_nibble(chunk[0]) << 4 | details::char_to_nibble(chunk[1])),
        .masked = chunk[0] != '?'
      };
    }
  }

  PatternFragment fragments[nfragments];
};

// [31/10/2023 - r] We're returning the offset so we can easily reuse this for external purposes.

namespace details {
auto pattern_scan(const void * const start, const void * const end, const PatternFragment * const fragments, const mpp::u32 nfragments) -> std::ptrdiff_t;
} // namespace details

template <std::size_t n>
auto pattern_scan(const void * const start, const std::size_t size, const Pattern<n> & pattern) -> std::ptrdiff_t {
  return details::pattern_scan(start, reinterpret_cast<const mpp::u8 *>(start) + size, pattern.fragments, pattern.nfragments); 
}

} // namespace mem
