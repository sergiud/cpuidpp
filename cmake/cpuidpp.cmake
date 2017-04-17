set (APPLICATION_NAME cpuidpp)

set (MAJOR_VERSION 1)
set (MINOR_VERSION 0)
set (VERSION_PATCH 0)

set (SHORT_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}")

if (NOT VERSION_PATCH EQUAL 0)
  set (SHORT_VERSION "${SHORT_VERSION}.${VERSION_PATCH}")
endif (NOT VERSION_PATCH EQUAL 0)

set (VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${VERSION_PATCH}")

set (PROJECT_VERSION ${SHORT_VERSION})
set (CPACK_PACKAGE_NAME ${APPLICATION_NAME})
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "CPUID C++ Library")
set (CPACK_PACKAGE_VERSION_MAJOR ${MAJOR_VERSION})
set (CPACK_PACKAGE_VERSION_MINOR ${MINOR_VERSION})
set (CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set (CPACK_PACKAGE_VERSION ${SHORT_VERSION})
set (CPACK_PACKAGE_CONTACT "sergiu.deitsch@gmail.com")

set (CPUIDPP_BUILD_NUMBER ${VERSION_PATCH})
set (CPUIDPP_MAJOR_VERSION ${MAJOR_VERSION})
set (CPUIDPP_MINOR_VERSION ${MINOR_VERSION})
set (CPUIDPP_REVISION_NUMBER 0)
set (CPUIDPP_VERSION_STRING ${SHORT_VERSION})
