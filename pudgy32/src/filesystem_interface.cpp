#include <cassert>
#include <utility>

#include <pudgy32/filesystem_interface.hpp>

namespace p32 {

    auto FilesystemInterface::make(StorageInterface& istorage)
        -> expected<FilesystemInterface, std::error_code>
    {
        expected<void, std::error_code> result(unexpect, unknown_code);
        FilesystemInterface fi(istorage, result);
        if (!result) {
            return unexpected(std::move(result).error());
        }
        return std::move(fi);
    }

    FilesystemInterface::FilesystemInterface(
        StorageInterface& istorage,
        expected<void, std::error_code>& result)
    : istorage(&istorage)
    {
        // if initialization fails
        // then
        //  set result to error code
        // else
        emplace_void(result);
        // end
    }

    FilesystemInterface::FilesystemInterface(FilesystemInterface&& other)
    : istorage(nullptr)
    {
        *this = std::move(other);
    }

    FilesystemInterface::~FilesystemInterface() {}

    FilesystemInterface& FilesystemInterface::operator=(FilesystemInterface&& other) {
        using std::swap;

        swap(this->istorage, other.istorage);

        return *this;
    }
}
