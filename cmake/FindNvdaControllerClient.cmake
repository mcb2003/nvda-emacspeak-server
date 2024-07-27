# Determine the architecture of the target
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
    set(ARCH "x64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86")
    set(ARCH "x86")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm64" OR CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch64")
    set(ARCH "arm64")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

message(STATUS "Detected architecture: ${ARCH}")

find_path(NvdaControllerClient_INCLUDE_DIR nvdaController.h
    HINTS $ENV{NVDA_CONTROLLER_CLIENT_DIR}
    PATH_SUFFIXES ${ARCH}
)

find_library(NvdaControllerClient_LIBRARY
    NAMES nvdaControllerClient
    HINTS $ENV{NVDA_CONTROLLER_CLIENT_DIR}
    PATH_SUFFIXES ${ARCH}
)

INCLUDE(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set NvdaControllerClient_FOUND to TRUE if
# all listed variables exist
FIND_PACKAGE_HANDLE_STANDARD_ARGS(NvdaControllerClient
	REQUIRED_VARS NvdaControllerClient_LIBRARY NvdaControllerClient_INCLUDE_DIR)

MARK_AS_ADVANCED(NvdaControllerClient_INCLUDE_DIR NvdaControllerClient_LIBRARY)

add_library(NvdaControllerClient INTERFACE IMPORTED)
target_include_directories(NvdaControllerClient INTERFACE ${NvdaControllerClient_INCLUDE_DIR})
target_link_libraries(NvdaControllerClient INTERFACE ${NvdaControllerClient_LIBRARY})
