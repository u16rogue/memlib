#include <memlib/pattern_scanner.hh>

auto mem::details::pattern_scan(const void * const start, const void * const end, const PatternFragment * const fragments, const mpp::u32 nfragments) -> std::ptrdiff_t {
  const mpp::u8 *   baseu8 = reinterpret_cast<const mpp::u8 *>(start);
  for (std::ptrdiff_t offset = 0; &baseu8[offset] < end; ++offset) {
    for (mpp::u32 ifrag = 0; ifrag < nfragments; ++ifrag) {
      const PatternFragment & fragment = fragments[ifrag];
      if (!fragment.masked) {
        continue;
      }

      if (baseu8[offset + ifrag] != fragment.byte) {
        break;
      }

      if (ifrag == (nfragments - 1)) {
        return offset;
      }
    }
  }

  return 0;
}
