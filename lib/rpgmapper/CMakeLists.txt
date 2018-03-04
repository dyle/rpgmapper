# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com


include_directories(${CMAKE_SOURCE_DIR}/include)

set(RPGMAPPER_LIB_MOC

    ${CMAKE_SOURCE_DIR}/include/rpgmapper/atlas.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/map.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/region.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/selection.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/command/prozessor.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/layer/axis_layer.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/layer/background_layer.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/layer/grid_layer.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/layer/layer.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/layer/text_layer.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/layer/tile_layer.hpp
)
qt5_wrap_cpp(RPGMAPPER_LIB_MOC_CPP ${RPGMAPPER_LIB_MOC})

set(RPGMAPPER_LIB_SRC

    atlas.cpp
    atlas_impl.cpp
    atlas_io.cpp
    coordinate_system.cpp
    field.cpp
    map.cpp
    map_impl.cpp
    nameable.cpp
    region.cpp
    region_impl.cpp
    selection.cpp

    command/atlas_command.cpp
    command/composite_command.cpp
    command/create_map.cpp
    command/create_region.cpp
    command/prozessor.cpp
    command/prozessor_impl.cpp
    command/remove_map.cpp
    command/remove_region.cpp
    command/resize_map.cpp
    command/set_atlas_name.cpp
    command/set_map_name.cpp
    command/set_map_origin.cpp
    command/set_region_name.cpp

    layer/axis_layer.cpp
    layer/background_layer.cpp
    layer/grid_layer.cpp
    layer/layer.cpp
    layer/layer_impl.cpp
    layer/text_layer.cpp
    layer/tile_layer.cpp

    numeralconverter/alphabetic.cpp
    numeralconverter/alpha_big.cpp
    numeralconverter/alpha_small.cpp
    numeralconverter/numerals.cpp
    numeralconverter/numeric.cpp
    numeralconverter/roman.cpp

    zip/zip.cpp
)

add_library(rpgm STATIC ${RPGMAPPER_LIB_SRC} ${RPGMAPPER_LIB_MOC_CPP})
target_link_libraries(rpgm quazip5 Qt5::Gui Qt5::Core ${CMAKE_REQUIRED_LIBRARIES})
