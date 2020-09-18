add_executable(p32test src/main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    target_compile_options(p32test PRIVATE /W4 /WX)
else()
    target_compile_options(p32test PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(p32test PUBLIC pudgy32)
