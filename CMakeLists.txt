# ------------------------------------------------------------
# CMakeLists.txt for RPGMapper
#
# Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# ------------------------------------------------------------

project(rpgmapper C CXX)
cmake_minimum_required(VERSION 2.8.9)

enable_testing()

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(FindPkgConfig)


# ------------------------------------------------------------
# global compiler flags

set(VERSION "0.1")
add_definitions(-DVERSION=\"${VERSION}\")
add_definitions(-D_DEFAULT_SOURCE)

# set compile flags
if (CMAKE_COMPILER_IS_GNUCC)
    # Hence, -std=c11 might not be needed any longer.
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Werror -Wall -Wextra -pedantic -g -ggdb3 -rdynamic -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -Wextra -pedantic -g -ggdb3 -rdynamic -fPIC")
endif (CMAKE_COMPILER_IS_GNUCC)


# ------------------------------------------------------------
# check libs and packages (headers + lib)

check_include_file(stdio.h HAVE_STDIO_H)
check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(memory.h HAVE_MEMORY_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(time.h HAVE_TIME_H)
check_include_file(math.h HAVE_MATH_H)
check_include_file(stdbool.h HAVE_STDBOOL_H)
check_include_file(endian.h HAVE_ENDIAN_H)
check_include_file(math.h HAVE_MATH_H)
check_include_file(assert.h HAVE_ASSERT_H)
check_include_file(errno.h HAVE_ERRNO_H)
check_include_file(limits.h HAVE_LIMITS_H)

# boost
find_package(Boost 1.62.0 COMPONENTS filesystem program_options system)
if (Boost_FOUND)
    set(CMAKE_REQUIRED_LIBRARIES "${Boost_LIBRARIES};${CMAKE_REQUIRED_LIBRARIES}")
    include_directories(${Boost_INCLUDE_DIRS})
    set(HAVE_BOOST_LIB 1)
else (Boost_FOUND)
    message(FATAL_ERROR "Boost >= 1.62.0 library not found.")
endif (Boost_FOUND)

# Qt5
message (STATUS "Looking for Qt5")
find_package(Qt5Core REQUIRED)
message (STATUS "Looking for Qt5 - found, version ${Qt5Core_VERSION_STRING}")
include_directories(${Qt5Core_INCLUDE_DIRS})
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# quazip5
message(STATUS "Looking for QuaZip")
find_path(QUAZIP_INCLUDE quazip/quazip.h)
if (DEFINED QUAZIP_INCLUDE)
    find_library(QUAZIP_LIBRARY NAMES quazip zipOpen)
    if (DEFINED QUAZIP_LIBRARY)
        message(STATUS "Looking for QuaZip - found")
        #set(CMAKE_REQUIRED_INCLUDES "${CMAKE_REQUIRED_INCLUDES};${QUAZIP_INCLUDE}")
        #set(CMAKE_REQUIRED_LIBRARIES "quazip;${CMAKE_REQUIRED_LIBRARIES}")
        mark_as_advanced(QUAZIP_INCLUDE QUAZIP_LIBRARY)
    else (DEFINED QUAZIP_LIBRARY)
        message(FATAL_ERROR "Looking for QuaZip - Library not found")
    endif (DEFINED QUAZIP_LIBRARY)
else (DEFINED QUAZIP_INCLUDE)
    message(FATAL_ERROR "Looking for QuaZip - Header file not found")
endif (DEFINED QUAZIP_INCLUDE)


# ------------------------------------------------------------
# dump the config file

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${QUAZIP_INCLUDE})


# ------------------------------------------------------------
# go through the subs

add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(test)


# ------------------------------------------------------------
# packaging

# set(CPACK_PACKAGE_NAME "rpgmapper")
#
# set(CPACK_PACKAGE_DESCRIPTION "RPGMapper tool for gamers")
# set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "This tool lets you draw maps for Role Playing Games")
# set(CPACK_PACKAGE_CONTACT "Oliver Maurhart <dyle71@gmail.com>")
# set(CPACK_PACKAGE_VENDOR "Oliver Maurhart")
# set(CPACK_PACKAGE_VERSION_MAJOR "0")
# set(CPACK_PACKAGE_VERSION_MINOR "1")
# set(CPACK_PACKAGE_VERSION_PATCH "0")
# set(CPACK_PROJECT_VERSION_STRING "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" )
#
# set(CPACK_GENERATOR "DEB;RPM;")
# set(CPACK_SOURCE_GENERATOR "TGZ")
#
# set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CMAKE_SYSTEM_PROCESSOR}")
# set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
# set(CPACK_SOURCE_IGNORE_FILES "/build/*;/.git/")
#
# set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.13), libgcc1 (>= 1:4.4)")
# set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/deb/control/postinst;${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/deb/control/postrm;${CMAKE_CURRENT_SOURCE_DIR}/cmake/cpack/deb/control/prerm;")
#
# # debianization
# string(TOLOWER "${CPACK_PACKAGE_NAME}" CPACK_PACKAGE_NAME_LOWERCASE)
# find_program(DPKG_PROGRAM dpkg DOC "dpkg program of Debian-based systems")
# if (DPKG_PROGRAM)
#     # use dpkg to fix the package file name
#     execute_process(
#         COMMAND ${DPKG_PROGRAM} --print-architecture
#         OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
#         OUTPUT_STRIP_TRAILING_WHITESPACE
#     )
#     set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME_LOWERCASE}_${CPACK_PROJECT_VERSION_STRING}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
# else (DPKG_PROGRAM)
#     set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME_LOWERCASE}_${CPACK_PROJECT_VERSION_STRING}_${CMAKE_SYSTEM_NAME}")
# endif (DPKG_PROGRAM)
#
# # package it
# include(CPack)
