cmake_minimum_required (VERSION 3.0)

if (POLICY CMP0063)
  cmake_policy (SET CMP0063 NEW)
endif (POLICY CMP0063)

project (cpuidpp)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set (CMAKE_CXX_VISIBILITY_PRESET hidden)
set (CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set (DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in)
set (DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR})

include (cpuidpp) # Must come before CPack
include (CheckCXXSourceCompiles)
include (CheckCXXSymbolExists)
include (CMakePackageConfigHelpers)
include (CPack)
include (GenerateExportHeader)
include (GNUInstallDirs)
include (UseDoxygen OPTIONAL)

check_cxx_source_compiles (
"
#include <intrin.h>
int main() { __cpuid(NULL, 0); }
"
  HAVE___CPUID
)

check_cxx_source_compiles (
"
#include <intrin.h>
int main() { __cpuidex(NULL, 0, 0); }
"
  HAVE___CPUIDEX
)

#check_cxx_symbol_exists (__cpuid intrin.h HAVE___CPUID)
#check_cxx_symbol_exists (__cpuidex intrin.h HAVE___CPUIDEX)
check_cxx_symbol_exists (__get_cpuid cpuid.h HAVE___GET_CPUID)
check_cxx_symbol_exists (__get_cpuid_count cpuid.h HAVE___GET_CPUID_COUNT)

add_library (cpuidpp
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/export.hpp
  include/cpuidpp/cpuidpp.hpp
  src/cpuidpp/cpuidpp.cpp
)

target_compile_features (cpuidpp
  PRIVATE cxx_constexpr cxx_uniform_initialization
  PUBLIC cxx_final cxx_deleted_functions
)

if (HAVE___CPUID)
  target_compile_definitions (cpuidpp PRIVATE HAVE___CPUID)
endif (HAVE___CPUID)

if (HAVE___CPUIDEX)
  target_compile_definitions (cpuidpp PRIVATE HAVE___CPUIDEX)
endif (HAVE___CPUIDEX)

if (HAVE___GET_CPUID)
  target_compile_definitions (cpuidpp PRIVATE HAVE___GET_CPUID)
endif (HAVE___GET_CPUID)

if (HAVE___GET_CPUID_COUNT)
  target_compile_definitions (cpuidpp PRIVATE HAVE___GET_CPUID_COUNT)
endif (HAVE___GET_CPUID_COUNT)

target_include_directories (cpuidpp PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

generate_export_header (cpuidpp EXPORT_FILE_NAME
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/export.hpp
)

set (cpuidpp_CMake_DIR cpuidpp/cmake)

# cpuidpp-config.cmake relative install directory
set (cpuidpp_CMake_INSTALLDIR ${CMAKE_INSTALL_LIBDIR}/${cpuidpp_CMake_DIR})

configure_package_config_file (cpuidpp-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cpuidpp-config.cmake
  INSTALL_DESTINATION ${cpuidpp_CMake_INSTALLDIR})
write_basic_package_version_file (cpuidpp-config-version.cmake
  VERSION ${VERSION} COMPATIBILITY SameMajorVersion)

export (TARGETS cpuidpp FILE cpuidpp-targets.cmake)
export (PACKAGE cpuidpp)

install (EXPORT cpuidpp-targets
  DESTINATION ${cpuidpp_CMake_INSTALLDIR}
  COMPONENT Development)
install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/cpuidpp-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cpuidpp-config-version.cmake
  DESTINATION ${cpuidpp_CMake_INSTALLDIR}
  COMPONENT Development)
install (TARGETS cpuidpp
  EXPORT cpuidpp-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/export.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp
  COMPONENT Development
)

install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
  DESTINATION .
  COMPONENT Development
  FILES_MATCHING PATTERN "*.hpp"
)

set_target_properties (cpuidpp PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties (cpuidpp PROPERTIES VERSION ${MAJOR_VERSION})
set_target_properties (cpuidpp PROPERTIES SOVERSION ${VERSION})

add_executable (test_cpuidpp tests/test_cpuidpp.cpp)
target_link_libraries (test_cpuidpp PRIVATE cpuidpp)
