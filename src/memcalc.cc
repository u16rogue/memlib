#include <memlib/memcalc.hh>

auto mem::rel32toabs(void * adr, mpp::u64 instrsz) -> void * {
  mpp::u8 * next = reinterpret_cast<decltype(next)>(adr) + instrsz;
  return next + (*reinterpret_cast<mpp::u32 *>(next - 4));
}
