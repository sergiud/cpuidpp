cmake_minimum_required (VERSION 3.16)
project (cpuidpp
  LANGUAGES CXX
  DESCRIPTION "CPUID C++ Library"
  VERSION 1.0.0
  HOMEPAGE_URL https://github.com/sergiud/cpuidpp
)

list (APPEND CMAKE_MODULE_PATH ${cpuidpp_SOURCE_DIR}/cmake)

set (CMAKE_CXX_VISIBILITY_PRESET hidden)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)
set (CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set (DOXYFILE_IN ${cpuidpp_SOURCE_DIR}/cmake/Doxyfile.in)
set (DOXYGEN_INPUT ${cpuidpp_SOURCE_DIR})

include (CheckCXXSourceCompiles)
include (CheckCXXSymbolExists)
include (CMakePackageConfigHelpers)
include (CPack)
include (GenerateExportHeader)
include (GNUInstallDirs)

find_package (Doxygen 1.11.0)

if (Doxygen_FOUND)
  add_subdirectory (doc)
endif (Doxygen_FOUND)

# NOTE check_cxx_symbol_exists does not work with intrinsic functions. We need
# to use check_cxx_source_compiles.
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

check_cxx_symbol_exists (__get_cpuid cpuid.h HAVE___GET_CPUID)
check_cxx_symbol_exists (__get_cpuid_count cpuid.h HAVE___GET_CPUID_COUNT)

configure_file (include/cpuidpp/version.hpp.cmake.in
  ${cpuidpp_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/version.hpp
)

add_library (cpuidpp
  ${cpuidpp_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/export.hpp
  ${cpuidpp_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/version.hpp
  include/cpuidpp/cpuidpp.hpp
  src/cpuidpp/cpuidpp.cpp
)

if (BUILD_SHARED_LIBS)
  target_sources (cpuidpp PRIVATE src/cpuidpp/resources/cpuidpp.rc)
endif (BUILD_SHARED_LIBS)

target_compile_features (cpuidpp
  PRIVATE cxx_constexpr cxx_uniform_initialization cxx_variadic_templates
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
  $<BUILD_INTERFACE:${cpuidpp_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${cpuidpp_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

generate_export_header (cpuidpp EXPORT_FILE_NAME
  ${cpuidpp_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/export.hpp
)

set (cpuidpp_CMake_DIR cpuidpp/cmake)

# cpuidpp-config.cmake relative install directory
set (cpuidpp_CMake_INSTALLDIR ${CMAKE_INSTALL_LIBDIR}/${cpuidpp_CMake_DIR})
set (cpuidpp_CMake_LIBDIR ${CMAKE_INSTALL_LIBDIR}/cpuidpp)

configure_package_config_file (cpuidpp-config.cmake.in
  ${cpuidpp_BINARY_DIR}/cpuidpp-config.cmake
  INSTALL_DESTINATION ${cpuidpp_CMake_INSTALLDIR}
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  NO_SET_AND_CHECK_MACRO
)
write_basic_package_version_file (cpuidpp-config-version.cmake
  COMPATIBILITY SameMajorVersion)

export (TARGETS cpuidpp NAMESPACE cpuidpp:: FILE cpuidpp-targets.cmake)
export (PACKAGE cpuidpp)

install (EXPORT cpuidpp-targets NAMESPACE cpuidpp::
  DESTINATION ${cpuidpp_CMake_INSTALLDIR}
  COMPONENT Development
)

install (FILES
  ${cpuidpp_BINARY_DIR}/cpuidpp-config.cmake
  ${cpuidpp_BINARY_DIR}/cpuidpp-config-version.cmake
  DESTINATION ${cpuidpp_CMake_INSTALLDIR}
  COMPONENT Development
)

install (TARGETS cpuidpp
  EXPORT cpuidpp-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
  LIBRARY DESTINATION ${cpuidpp_CMake_LIBDIR} COMPONENT Runtime
  ARCHIVE DESTINATION ${cpuidpp_CMake_LIBDIR} COMPONENT Development
)

install (FILES
  ${cpuidpp_BINARY_DIR}/${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp/export.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cpuidpp
  COMPONENT Development
)

install (DIRECTORY ${cpuidpp_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT Development
  FILES_MATCHING PATTERN "*.hpp"
)

set_target_properties (cpuidpp PROPERTIES VERSION ${cpuidpp_VERSION_MAJOR})
set_target_properties (cpuidpp PROPERTIES SOVERSION ${cpuidpp_VERSION})

add_executable (test_cpuidpp tests/test_cpuidpp.cpp)
target_link_libraries (test_cpuidpp PRIVATE cpuidpp)
