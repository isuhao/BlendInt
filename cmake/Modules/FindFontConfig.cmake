# - Try to find Fontconfig
# Once done this will define
#
# FONTCONFIG_FOUND - system has Fontconfig
# FONTCONFIG_INCLUDE_DIR - the Fontconfig include directory
# FONTCONFIG_LIBRARY - Link these to use Fontconfig
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


if ( FONTCONFIG_INCLUDE_DIR AND FONTCONFIG_LIBRARY )
# in cache already
SET(Fontconfig_FIND_QUIETLY TRUE)
endif ( FONTCONFIG_INCLUDE_DIR AND FONTCONFIG_LIBRARY )

# use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
if( NOT WIN32 )
find_package(PkgConfig)

pkg_check_modules(FONTCONFIG_PKG QUIET fontconfig)
endif( NOT WIN32 )

FIND_PATH(FONTCONFIG_INCLUDE_DIR NAMES fontconfig/fontconfig.h
    PATHS
    /usr/local/include
    /usr/X11/include
    /usr/include
    HINTS
    ${FONTCONFIG_PKG_INCLUDE_DIRS} # Generated by pkg-config
)

FIND_LIBRARY(FONTCONFIG_LIBRARY NAMES fontconfig ${FONTCONFIG_PKG_LIBRARY}
    PATHS
    /usr/local
    /usr/X11
    /usr
    HINTS
    ${FONTCONFIG_PKG_LIBRARY_DIRS} # Generated by pkg-config
    PATH_SUFFIXES
    lib64
    lib
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Fontconfig DEFAULT_MSG FONTCONFIG_LIBRARY FONTCONFIG_INCLUDE_DIR )

# show the FONTCONFIG_INCLUDE_DIR and FONTCONFIG_LIBRARY variables only in the advanced view
MARK_AS_ADVANCED(FONTCONFIG_INCLUDE_DIR FONTCONFIG_LIBRARY )
