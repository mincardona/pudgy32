#include <cassert>
#include <iostream>
#include <memory>
#include <optional>

#include <pudgy32/expected.hpp>
#include <pudgy32/pudgy32_config.hpp>
#include <pudgy32/storage_interface.hpp>

class OwningMemoryStorage final : public p32::StorageInterface {
public:
    OwningMemoryStorage(std::size_t size)
    : size_(size),
      offset_(0)
    {
        // SIZE_MAX is not allowed to avoid overflow bugs that I haven't
        // worked through yet
        assert(size < std::numeric_limits<std::size_t>::max());
        buffer_ = std::make_unique<unsigned char[]>(size);
    }

    virtual ~OwningMemoryStorage() noexcept {};

    unsigned char* memory_set() {
        return buffer_.get();
    }

    unsigned char* memory_cur() {
        return this->memory_set() + offset_;
    }

    auto size() -> p32::expected<std::size_t, std::error_code> override {
        return size_;
    }

    auto tell() -> p32::expected<std::size_t, std::error_code> override {
        return offset_;
    }

    // returns errc::invalid_argument if seek is out of range
    auto seek(p32::SeekType type, p32::SeekDirection direction, std::size_t offset)
        -> p32::expected<void, std::error_code> override
    {
        std::size_t start_point = 0;
        if (type == p32::SeekType::SET) {
            // = 0
        } else if (type == p32::SeekType::CUR) {
            start_point = offset_;
        } else if (type == p32::SeekType::END) {
            start_point = size_;
        } else {
            assert(0);
        }

        std::optional<std::size_t> end_point;
        if (direction == p32::SeekDirection::FORWARDS) {
            end_point = add_check_overflow_(start_point, offset);
        } else if (direction == p32::SeekDirection::BACKWARDS) {
            end_point = subtract_check_underflow_(start_point, offset);
        } else {
            assert(0);
        }

        if (!end_point) {
            return p32::unexpected{std::make_error_code(std::errc::invalid_argument)};
        }

        offset_ = *end_point;
        return {};
    }

    // returns errc::invalid_argument if there are not count bytes available
    auto read_some(void* buf, std::size_t count)
        -> p32::expected<std::size_t, std::error_code> override
    {
        if (bytes_left_() < count) {
            return p32::unexpected{std::make_error_code(std::errc::invalid_argument)};
        }

        std::memcpy(buf, this->memory_cur(), count);
        offset_ += count;
        return {};
    }

    // returns errc::invalid_argument if there are not count bytes available
    auto write_some(const void* buf, std::size_t count)
        -> p32::expected<std::size_t, std::error_code> override
    {
        if (bytes_left_() < count) {
            return p32::unexpected{std::make_error_code(std::errc::invalid_argument)};
        }

        std::memcpy(this->memory_cur(), buf, count);
        offset_ += count;
        return {};
    }

    auto flush() -> p32::expected<void, std::error_code> override
    {
        return {};
    }

private:
    std::size_t bytes_left_() {
        return size_ - offset_;
    }

    static auto add_check_overflow_(std::size_t a, std::size_t b)
        -> std::optional<std::size_t>
    {
        auto sum = a + b;
        if (sum < a) {
            return {};
        }
        return sum;
    }

    static auto subtract_check_underflow_(std::size_t a, std::size_t b)
        -> std::optional<std::size_t>
    {
        auto diff = a - b;
        if (diff > a) {
            return {};
        }
        return diff;
    }

    std::size_t size_;
    std::size_t offset_;
    std::unique_ptr<unsigned char[]> buffer_;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::cout << "p32test version " << PUDGY32_VERSION_STR << "\n";
    std::cout << "build type is "
#ifdef NDEBUG
              << "not debug"
#else
              << "debug"
#endif
    << "\n";
}
