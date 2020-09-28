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
    FORWARDS, BACKWARDS
};

class StorageInterface {
public:
    virtual ~StorageInterface() noexcept;

    /// Gets the size of the storage space in bytes
    virtual auto size() -> expected<std::size_t, std::error_code> = 0;

    /// Gets the current position in the storage space
    virtual auto tell() -> expected<std::size_t, std::error_code> = 0;

    /// Seeks to a new position in the storage space.
    /// Note that the "sign" of the offset is encoded in the seek direction, so
    /// the offset itself is unsigned.
    virtual auto seek(SeekType type, SeekDirection direction, std::size_t offset)
        -> expected<void, std::error_code> = 0;
    // inline shorthand overload
    auto seek(std::size_t offset) -> expected<void, std::error_code> {
        return this->seek(SeekType::SET, SeekDirection::FORWARDS, offset);
    }

    /// Reads at most count byes from the storage space and stores them in buf.
    /// Returns the number of bytes read (should be greater than 0 and less than
    /// or equal to count) or an error.
    /// After each successful call to this function, the storage position is
    /// advanced to point to the next byte not yet read. If this call fails, the
    /// storage position is unspecified.
    virtual auto read_some(void* buf, std::size_t count)
        -> expected<std::size_t, std::error_code> = 0;
    /// Reads count bytes from the storage space and writes them to buf.
    /// Returns an error if unable to read the number of bytes requested.
    /// A default implementation is provided which repeatedly calls read_some.
    virtual auto read_fill(void* buf, std::size_t count)
        -> expected<void, std::error_code>;

    /// Writes at most count byes from buf to the storage space.
    /// Returns the number of bytes written (should be greater than 0 and less
    /// than or equal to count) or an error.
    /// After each successful call to this function, the storage position is
    /// advanced to point to the next byte not yet written. If this call fails,
    /// the storage position is unspecified.
    virtual auto write_some(const void* buf, std::size_t count)
        -> expected<std::size_t, std::error_code> = 0;
    // a default implementation is provided
    virtual auto write_fill(const void* buf, std::size_t count)
        -> expected<void, std::error_code>;

    /// Forces any buffered/pending operations to the underlying device to
    /// whatever extent is possible.
    virtual auto flush() -> expected<void, std::error_code>;
};

}

#endif  // PUDGY32_STORAGE_INTERFACE_HPP_INCLUDED
