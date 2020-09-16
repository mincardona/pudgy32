#ifndef PUDGY32_HPP_INCLUDED
#define PUDGY32_HPP_INCLUDED

#include "tl/expected.hpp"
#include <pudgy32/pudgy32_config.hpp>

namespace pudgy32 {

template<typename T, typename E>
using expected = tl::expected<T, E>;

template<typename E>
using unexpected = tl::unexpected<E>;

template<typename E>
const auto make_unexpected = tl::make_unexpected<E>;

using unexpect_t = tl::unexpect_t;

template<typename E>
using bad_expected_access = tl::bad_expected_access<E>;

}

#endif  // PUDGY32_HPP_INCLUDED
