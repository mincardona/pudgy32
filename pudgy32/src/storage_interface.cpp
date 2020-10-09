#include <cassert>

#include <pudgy32/storage_interface.hpp>

namespace p32 {

// a curiously unnecessary template
template<typename BufElement, typename CastedBufElement, typename Callback>
static expected<void, std::error_code> io_fill_generic(
    BufElement* buf, std::size_t count, Callback cb)
{
    assert(buf != nullptr);

    auto bytes_left = count;
    auto buf_head = static_cast<CastedBufElement*>(buf);
    while (bytes_left > 0) {
        expected result = cb(buf_head, bytes_left);
        if (!result) {
            return unexpected{std::move(result).error()};
        }

        assert(*result <= bytes_left);

        bytes_left -= *result;
        buf_head += *result;
    }

    return {};
}

expected<void, std::error_code>
    StorageInterface::read_fill(void* buf, std::size_t count)
{
    using namespace std::placeholders;
    return io_fill_generic<void, std::byte>(buf, count,
        std::bind(&StorageInterface::read_some, this, _1, _2));
}

expected<void, std::error_code>
    StorageInterface::write_fill(const void* buf, std::size_t count)
{
    using namespace std::placeholders;
    return io_fill_generic<const void, const std::byte>(buf, count,
        std::bind(&StorageInterface::write_some, this, _1, _2));
}

}  // namespace p32
