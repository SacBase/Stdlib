# This file activates CPack binary packaging for different distributions
# At the moment we support only *UNIX systems (DEB, RPM, productbuild (MacOS),
# and TGZ).

IF (NOT DEFINED SAC2C_VERSION)
    MESSAGE (FATAL_ERROR "Sac2c Version not set!")
ENDIF ()

# By setting this on we can see where installation targets are specified via
# absolute paths. XXX (???) For portability purposes this should be avoided.
SET (CPACK_WARN_ON_ABSOLUTE_INSTALL_DESTINATION ON)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  SET (CPACK_GENERATOR "productbuild;TGZ")
ELSE ()
  SET (CPACK_GENERATOR "RPM;DEB;TGZ")
ENDIF ()

SET (CPACK_productbuild_COMPONENT_INSTALL ON)
SET (CPACK_RPM_COMPONENT_INSTALL ON)
SET (CPACK_DEB_COMPONENT_INSTALL ON)
SET (CPACK_TGZ_COMPONENT_INSTALL ON)
SET (CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
SET (CPACK_COMPONENTS_ALL modules trees)

# We create separate config files for different generators
#set(CPACK_PROJECT_CONFIG_FILE "${PROJECT_SOURCE_DIR}/cmake/cpack_options.cmake")

# Set default CPack Packaging options
SET (CPACK_PACKAGE_NAME              "sac-stdlib")
SET (CPACK_PACKAGE_VENDOR            "SaC Development Team")
SET (CPACK_PACKAGE_CONTACT           "info@sac-home.org")
SET (CPACK_PACKAGE_VERSION           "${PROJECT_SHORT_VERSION}")
SET (CPACK_PACKAGE_VERSION_MAJOR     "${PROJECT_MAJOR_VERSION}")
SET (CPACK_PACKAGE_VERSION_MINOR     "${PROJECT_MINOR_VERSION}")
SET (CPACK_PACKAGE_VERSION_PATCH     "${PROJECT_PATCH_VERSION}")
#SET (CPACK_PACKAGE_ICON              "${PROJECT_SOURCE_DIR}/cmake/sac_logo.png")
SET (CPACK_PACKAGING_INSTALL_PREFIX  "${CMAKE_INSTALL_PREFIX}")

# SET (CPACK_PACKAGE_DESCRIPTION_FILE ...)
SET (CPACK_PACKAGE_DESCRIPTION_SUMMARY "The standard library for a data-parallel array-based functional language SAC")
SET (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
SET (CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/cmake/cpack/README.txt")
SET (CPACK_RESOURCE_FILE_WELCOME "${PROJECT_SOURCE_DIR}/cmake/cpack/WELCOME.txt")

# Debian-specific variables
SET (CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR} <${CPACK_PACKAGE_CONTACT}>")
SET (CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
SET (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON) # non-functional?
# FIXME Can we auto-generate these dependencies?
SET (CPACK_DEBIAN_PACKAGE_DEPENDS "sac2c-compiler (= ${SAC2C_VERSION})")

# RPM-specific variables
# XXX (hans): this may not be exhaustive - does not take into account if the user
# changes the install prefix
SET (CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION /usr/local /usr/local/bin /usr/local/include /usr/local/lib /usr/local/libexec /usr/local/share)
# FIXME Can we auto-generate these dependencies?
STRING (REPLACE "-" "_" _sac2c_rpm_version ${SAC2C_VERSION})
SET (CPACK_RPM_PACKAGE_REQUIRES "sac2c-compiler = ${_sac2c_rpm_version}") # we don't need to go crazy here as rpmbuild handles most of this for us

INCLUDE (CPack)

# vim: ts=2 sw=2 et:
