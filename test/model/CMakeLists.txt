#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR})

set(TEST_ATLAS_CHANGEABLE_SRC                   test_atlas_changeable.cpp)
add_executable(test_atlas_changeable            ${TEST_ATLAS_CHANGEABLE_SRC})
target_link_libraries(test_atlas_changeable     rpgm  ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/atlas_changeable                 test_atlas_changeable)

set(TEST_ATLAS_JSON_SRC                         test_atlas_json.cpp)
add_executable(test_atlas_json                  ${TEST_ATLAS_JSON_SRC})
target_link_libraries(test_atlas_json           rpgm  ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/atlas_json                       test_atlas_json)

set(TEST_CONVERTER_SRC                          test_converter.cpp)
add_executable(test_converter                   ${TEST_CONVERTER_SRC})
target_link_libraries(test_converter            rpgm  ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/converter                        test_converter)

set(TEST_FIELD_COORDINATE_SRC                   test_field_coordinate.cpp)
add_executable(test_field_coordinate            ${TEST_FIELD_COORDINATE_SRC})
target_link_libraries(test_field_coordinate     rpgm ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/field_coordinate                 test_field_coordinate)

set(TEST_MAP_SIZE_SRC                           test_map_size.cpp)
add_executable(test_map_size                    ${TEST_MAP_SIZE_SRC})
target_link_libraries(test_map_size             rpgm ${CMAKE_REQUIRED_LIBRARIES})
add_test(model/map_size                         test_map_size)
