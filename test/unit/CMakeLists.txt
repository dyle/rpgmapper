#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})


set(TEST_ATLAS_SRC                      test_atlas.cpp)
add_executable(test-atlas               ${TEST_ATLAS_SRC})
target_link_libraries(test-atlas        gtest gtest_main  pthread rpgm ${CMAKE_REQUIRED_LIBRARIES})
gtest_add_tests(TARGET test-atlas       WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
