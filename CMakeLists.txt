cmake_minimum_required(VERSION 3.10)

project("NVDA Emacspeak Server"
    VERSION "0.1.0"
    DESCRIPTION "Speech server for Emacspeak using NVDA as a backend"
    LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(NvdaControllerClient REQUIRED)

add_executable(nvdasrv src/main.c)
target_compile_definitions(nvdasrv PRIVATE -DUNICODE -D_UNICODE)
target_link_libraries(nvdasrv PRIVATE NvdaControllerClient)
install(TARGETS nvdasrv DESTINATION bin)
