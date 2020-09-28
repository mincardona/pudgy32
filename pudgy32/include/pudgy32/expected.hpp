#ifndef PUDGY32_EXPECTED_HPP_INCLUDED
#define PUDGY32_EXPECTED_HPP_INCLUDED

#include <tl/expected.hpp>
#include <system_error>

// re-export all expected symbols under our namespace so the implementation can
// be changed later
namespace p32 {

using tl::expected;
using tl::unexpected;
using tl::make_unexpected;
using tl::unexpect;
using tl::bad_expected_access;
using tl::in_place;

// tl::expected doesn't have "void expected<void, E>::emplace()" from P0323R9
// this is a partial replacement kludge, useful for setting an existing
// expected<void, E> variable equal to a void success value without boilerplate
template<typename E>
void emplace_void(expected<void, E>& exp) {
    exp = expected<void, E>();
}

/// the code to be used as an unknown error condition or placeholder code
const std::error_code unknown_code = std::make_error_code(std::errc::state_not_recoverable);

}

#endif  // PUDGY32_EXPECTED_HPP_INCLUDED
