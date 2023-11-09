#include <memlib/memwalker.hh>
#include <memlib/memcalc.hh>

auto mem::walkers::Increment::apply(WalkerPtrRef p) -> bool {
  p += n;
  return true;
}

auto mem::walkers::Decrement::apply(WalkerPtrRef p) -> bool {
  p -= n;
  return true;
}

auto mem::walkers::internal::Dereference::apply(WalkerPtrRef p) -> bool {
  p = *reinterpret_cast<mpp::u8 **>(p);
  if (!p) return false;
  return true;
}

auto mem::walkers::internal::Rel32ToAbs::apply(WalkerPtrRef p) -> bool {
  p = reinterpret_cast<mpp::u8 *>(mem::rel32toabs(p, instrsize));
  return p;
}
