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

# test: Atlas Changing
set(TEST_ATLAS_CHANGEABLE_SRC                   test_atlas_changeable.cpp)
add_executable(test_atlas_changeable            ${TEST_ATLAS_CHANGEABLE_SRC})
target_link_libraries(test_atlas_changeable     rpgm  ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/atlas_changeable                 test_atlas_changeable)

# test: Atlas JSON
set(TEST_ATLAS_JSON_SRC                         test_atlas_json.cpp)
add_executable(test_atlas_json                  ${TEST_ATLAS_JSON_SRC})
target_link_libraries(test_atlas_json           rpgm  ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/atlas_json                       test_atlas_json)

# test: File
set(TEST_FILE_SRC                               test_file.cpp)
add_executable(test_file                        ${TEST_FILE_SRC})
target_link_libraries(test_file                 rpgm ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/file                             test_file)

# test: Map_size
set(TEST_MAP_SIZE_SRC                           test_map_size.cpp)
add_executable(test_map_size                    ${TEST_MAP_SIZE_SRC})
target_link_libraries(test_map_size             rpgm ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/map_size                         test_map_size)
