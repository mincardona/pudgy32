#ifndef PUDGY32_STORAGE_INTERFACE_HPP_INCLUDED
#define PUDGY32_STORAGE_INTERFACE_HPP_INCLUDED

#include <cstddef>
#include <system_error>

#include <pudgy32/expected.hpp>

namespace p32 {

class StorageInterface {
public:
    enum class SeekType {
        SET, CUR, END
    };

    enum class SeekDirection {
        BACKWARDS, FORWARDS
    };

    virtual ~StorageInterface() noexcept;

    /// Gets the size of the storage space in bytes
    virtual expected<std::size_t, std::error_code> size() = 0;

    virtual std::error_code
        seek(SeekType type, SeekDirection direction, std::size_t offset) = 0;
    /// inline shorthand overload
    std::error_code seek(std::size_t offset) {
        return this->seek(SeekType::SET, SeekDirection::FORWARDS, offset);
    }

    virtual expected<std::size_t, std::error_code>
        read_some(void* buf, std::size_t count) = 0;
    // a default implementation is provided
    virtual expected<void, std::error_code>
        read_fill(void* buf, std::size_t count);

    virtual expected<std::size_t, std::error_code>
        write_some(const void* buf, std::size_t count) = 0;
    // a default implementation is provided
    virtual expected<void, std::error_code>
        write_fill(const void* buf, std::size_t count);
};

}

#endif  // PUDGY32_STORAGE_INTERFACE_HPP_INCLUDED
