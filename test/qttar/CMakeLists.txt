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

# test: QtTAR
set(TEST_QTTAR_SRC                       test_qttar.cpp)
add_executable(test_qttar                ${TEST_QTTAR_SRC})
target_link_libraries(test_qttar         qttar  ${CMAKE_REQUIRED_LIBRARIES})
add_test(qttar                           test_qttar)
