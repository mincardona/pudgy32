#include "pudgy32/pudgy32_config.hpp"
#include "pudgy32/pudgy32.hpp"
#include <tl/expected.hpp>
#include <iostream>

int main(int [[maybe_unused]] argc, char** [[maybe_unused]] argv) {
    std::cout << "p32test version " << PUDGY32_VERSION_STR << "\n";
    std::cout << "dummy = " << pudgy32::dummy << "\n";
}
