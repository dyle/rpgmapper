# ------------------------------------------------------------
# CMakeLists.txt
#
# Author: Oliver Maurhart, <oliver.maurhart@ait.ac.at>
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


# additional includes
include_directories(${CMAKE_SOURCE_DIR}/bin ${CMAKE_BINARY_DIR})


# test: Changeable object
set(TEST_CHANGEABLE_SRC
    ${CMAKE_SOURCE_DIR}/bin/model/changeable.cpp
    test_changeable.cpp)
add_executable(test_changeable              ${TEST_CHANGEABLE_SRC})
target_link_libraries(test_changeable       ${CMAKE_REQUIRED_LIBRARIES})
add_test(unit/changeable                    test_changeable)

# test: Nameable object
set(TEST_NAMEABLE_SRC
    ${CMAKE_SOURCE_DIR}/bin/model/changeable.cpp
    ${CMAKE_SOURCE_DIR}/bin/model/nameable.cpp
    test_nameable.cpp)
add_executable(test_nameable                ${TEST_NAMEABLE_SRC})
target_link_libraries(test_nameable         ${CMAKE_REQUIRED_LIBRARIES})
add_test(unit/nameable                      test_nameable)
