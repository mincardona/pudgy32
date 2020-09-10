ExternalProject_Add(tl-expected
    GIT_REPOSITORY https://github.com/TartanLlama/expected.git
    # UPDATE_COMMAND ""
    # disable automatically installing the dependency
    INSTALL_COMMAND ""
)
