#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})


set(TEST_UNITS_SRC
    test_atlas.cpp
    test_region.cpp
)
add_executable(test-units               ${TEST_UNITS_SRC})
target_link_libraries(test-units        gtest gtest_main  pthread rpgm ${CMAKE_REQUIRED_LIBRARIES})
gtest_add_tests(TARGET test-units       WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
