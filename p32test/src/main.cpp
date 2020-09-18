#include <iostream>

#include <pudgy32/expected.hpp>
#include <pudgy32/pudgy32_config.hpp>

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
