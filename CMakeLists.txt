cmake_minimum_required(VERSION 3.10)

project("NVDA Emacspeak Server"
    VERSION "0.1.0"
    DESCRIPTION "Speech server for Emacspeak using NVDA as a backend"
    LANGUAGES C)

add_executable(nvdasrv src/main.c)
target_compile_definitions(nvdasrv PRIVATE -DUNICODE -D_UNICODE)
install(TARGETS nvdasrv DESTINATION bin)
