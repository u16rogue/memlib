#pragma once

#include <metapp/metapp.hh>

namespace mem {

auto rel32toabs(void * adr, mpp::u64 instrsz) -> void *;

} // namespace mem
