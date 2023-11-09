#pragma once

#include <cstddef>
#include <metapp/metapp.hh>

#include "pattern_scanner.hh"

namespace mem {

namespace walkers {

using WalkerPtr    = mpp::u8 *;
using WalkerPtrRef = mpp::u8 *&;

struct Increment {
  consteval Increment(std::ptrdiff_t n) : n(n) {}
  const std::ptrdiff_t n;
  auto apply(WalkerPtrRef p) -> bool;
}; // struct Increment

struct Decrement {
  consteval Decrement(std::ptrdiff_t n) : n(n) {}
  const std::ptrdiff_t n;
  auto apply(WalkerPtrRef p) -> bool;
}; // struct Decrement

namespace internal {

struct Dereference {
  static auto apply(WalkerPtrRef p) -> bool;
}; // struct Dereference

struct Rel32ToAbs {
  consteval Rel32ToAbs(mpp::u64 instrsize) : instrsize(instrsize) {}
  const mpp::u64 instrsize;
  auto apply(WalkerPtrRef p) -> bool;
};

} // namespace mem::walkers::internal

namespace external {

} // namespace mem::walkers::external

} // namespace mem::walkers

template <typename... Args>
auto walk(void * start, Args... args) -> void * {
  if (!start) {
    return nullptr;
  }

  mpp::u8 * p = reinterpret_cast<mpp::u8 *>(start);

  if (!(args.apply(p) && ...)) {
    return nullptr;
  }

  return p;
}

} // namespace mem
