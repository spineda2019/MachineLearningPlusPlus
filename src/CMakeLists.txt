# CMakeList.txt : CMake project for libMachineLearning, include source and define
# project specific logic here.
#

add_library(libMachineLearning SHARED ${SOURCES})

target_include_directories(libMachineLearning PUBLIC ${HEADERS})

if (WIN32)
    set_target_properties(libMachineLearning PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

# TODO: Add tests and install targets if needed.
