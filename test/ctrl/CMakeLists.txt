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
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})

# test: File
set(TEST_FILE_SRC                       test_file.cpp)
add_executable(test_file                ${TEST_FILE_SRC})
target_link_libraries(test_file         rpgmapper_ctrl ${CMAKE_REQUIRED_LIBRARIES})
add_test(ctrl/file                      test_file)
