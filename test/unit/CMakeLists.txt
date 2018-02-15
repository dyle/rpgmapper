#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(TEST_UNITS_SRC
    test_numerals.cpp
    test_coordinate_system.cpp
    test_field.cpp
    test_layer.cpp
    test_map.cpp
    test_region.cpp
    test_atlas.cpp
    test_atlas_io.cpp
    test_commands.cpp
)

add_executable(test-units               ${TEST_UNITS_SRC})
target_link_libraries(test-units        gtest gtest_main  pthread rpgm ${CMAKE_REQUIRED_LIBRARIES})
gtest_add_tests(TARGET test-units       WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
