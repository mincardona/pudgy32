#ifndef PUDGY32_FILESYSTEM_INTERFACE_HPP_INCLUDED
#define PUDGY32_FILESYSTEM_INTERFACE_HPP_INCLUDED

#include <cstddef>
#include <system_error>

#include <pudgy32/expected.hpp>
#include <pudgy32/storage_interface.hpp>

namespace p32 {

/// Interface for a filesystem located on a storage device.
/// A FilesystemInterface holds a reference to a StorageInterface which must
/// have a lifetime greater than it.
class FilesystemInterface final {
public:
    static auto make(StorageInterface& istorage)
        -> expected<FilesystemInterface, std::error_code>;
    FilesystemInterface(FilesystemInterface&& other);

    ~FilesystemInterface() noexcept;
    FilesystemInterface& operator=(FilesystemInterface&& other);

private:
    FilesystemInterface(
        StorageInterface& istorage,
        expected<void, std::error_code>& result);

    StorageInterface* istorage;
};

}

#endif  // PUDGY32_FILESYSTEM_INTERFACE_HPP_INCLUDED
