#ifndef PUDGY32_EXPECTED_HPP_INCLUDED
#define PUDGY32_EXPECTED_HPP_INCLUDED

#include <tl/expected.hpp>

// re-export all expected symbols under our namespace so the implementation can
// be changed later
namespace p32 {

using tl::expected;
using tl::unexpected;
using tl::make_unexpected;
using tl::unexpect_t;
using tl::bad_expected_access;

}

#endif  // PUDGY32_EXPECTED_HPP_INCLUDED
