#ifndef PUDGY32_STORAGE_INTERFACE_HPP_INCLUDED
#define PUDGY32_STORAGE_INTERFACE_HPP_INCLUDED

#include <cstddef>
#include <system_error>

#include <pudgy32/expected.hpp>

namespace p32 {

enum class SeekType {
    /// From the beginning
    SET,
    /// From the current seek location
    CUR,
    /// From the end
    END
};

enum class SeekDirection {
    BACKWARDS, FORWARDS
};

class StorageInterface {
public:
    virtual ~StorageInterface() noexcept;

    /// Gets the size of the storage space in bytes
    virtual expected<std::size_t, std::error_code> size() = 0;

    /// Gets the current position in the storage space.
    virtual expected<std::size_t, std::error_code> tell() = 0;

    /// Seeks to a new position in the storage space.
    /// Note that the "sign" of the offset is encoded in the seek direction, so
    /// the offset itself is unsigned.
    virtual std::error_code
        seek(SeekType type, SeekDirection direction, std::size_t offset) = 0;
    // inline shorthand overload
    std::error_code seek(std::size_t offset) {
        return this->seek(SeekType::SET, SeekDirection::FORWARDS, offset);
    }

    /// Reads at most count byes from the storage space and stores them in buf.
    /// Returns the number of bytes read (should be greater than 0 and less than
    /// or equal to count) or an error.
    /// After each successful call to this function, the storage position is
    /// advanced to point to the next byte not yet read. If this call fails, the
    /// storage position is unspecified.
    virtual expected<std::size_t, std::error_code>
        read_some(void* buf, std::size_t count) = 0;
    /// Reads count bytes from the storage space and writes them to buf.
    /// Returns an error if unable to read the number of bytes requested.
    /// A default implementation is provided which repeatedly calls read_some.
    virtual expected<void, std::error_code>
        read_fill(void* buf, std::size_t count);

    /// Writes at most count byes from buf to the storage space.
    /// Returns the number of bytes written (should be greater than 0 and less
    /// than or equal to count) or an error.
    /// After each successful call to this function, the storage position is
    /// advanced to point to the next byte not yet written. If this call fails,
    /// the storage position is unspecified.
    virtual expected<std::size_t, std::error_code>
        write_some(const void* buf, std::size_t count) = 0;
    // a default implementation is provided
    virtual expected<void, std::error_code>
        write_fill(const void* buf, std::size_t count);
};

}

#endif  // PUDGY32_STORAGE_INTERFACE_HPP_INCLUDED
