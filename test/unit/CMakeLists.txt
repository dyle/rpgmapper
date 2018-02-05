#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})


set(TEST_CHANGEABLE_SRC                     test_changeable.cpp)
add_executable(test_changeable              ${TEST_CHANGEABLE_SRC})
target_link_libraries(test_changeable       rpgm ${CMAKE_REQUIRED_LIBRARIES})
add_test(unit/changeable                    test_changeable)

set(TEST_NAMEABLE_SRC                       test_nameable.cpp)
add_executable(test_nameable                ${TEST_NAMEABLE_SRC})
target_link_libraries(test_nameable         rpgm ${CMAKE_REQUIRED_LIBRARIES})
add_test(unit/nameable                      test_nameable)
