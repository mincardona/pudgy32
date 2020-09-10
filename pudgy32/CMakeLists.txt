set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(SourceDir "${CMAKE_CURRENT_SOURCE_DIR}/src/")

set(IncludeFiles "pudgy32/pudgy32.hpp")
list(TRANSFORM IncludeFiles PREPEND ${IncludeDir})
set(SourceFiles "pudgy32.cpp")
list(TRANSFORM SourceFiles PREPEND ${SourceDir})
set(TemplateFileStem pudgy32_config)

configure_file("${TemplateFileStem}.hpp.in" "${TemplateFileStem}.hpp")

add_library(pudgy32 ${IncludeFiles} ${SourceFiles})

include(ExternalProject)

# https://github.com/TartanLlama/expected
find_package(tl-expected 1.0.0 REQUIRED)
ExternalProject_Get_Property(tl-expected SOURCE_DIR)
# it feels like this shouldn't be necessary, but maybe it is because we disable
# installing the external dependency
target_include_directories(pudgy32 PUBLIC "${SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include configured files from ${PROJECT_BINARY_DIR}
target_include_directories(pudgy32 PUBLIC "${IncludeDir}" PUBLIC "${PROJECT_BINARY_DIR}")
