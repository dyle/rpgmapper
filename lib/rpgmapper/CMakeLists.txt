# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com


include_directories(${CMAKE_SOURCE_DIR}/include)

set(RPGMAPPER_LIB_MOC

    ${CMAKE_SOURCE_DIR}/include/rpgmapper/atlas.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/map.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/region.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/selection.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/command/processor.hpp
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
    coordinate_system.cpp
    field.cpp
    filesystem.cpp
    map.cpp
    map_impl.cpp
    nameable.cpp
    region.cpp
    region_impl.cpp
    resource.cpp
    resource_db.cpp
    selection.cpp

    command/atlas_command.cpp
    command/composite_command.cpp
    command/create_map.cpp
    command/create_region.cpp
    command/processor.cpp
    command/processor_impl.cpp
    command/remove_map.cpp
    command/remove_region.cpp
    command/resize_map.cpp
    command/set_atlas_name.cpp
    command/set_map_axis_font.cpp
    command/set_map_axis_font_color.cpp
    command/set_map_background_color.cpp
    command/set_map_background_image.cpp
    command/set_map_background_image_render_mode.cpp
    command/set_map_background_rendering.cpp
    command/set_map_grid_color.cpp
    command/set_map_margings.cpp
    command/set_map_name.cpp
    command/set_map_numeral_axis.cpp
    command/set_map_numeral_offset.cpp
    command/set_map_origin.cpp
    command/set_region_name.cpp

    io/atlas_io.cpp
    io/zip.cpp

    layer/axis_layer.cpp
    layer/background_renderer.cpp
    layer/background_layer.cpp
    layer/grid_layer.cpp
    layer/image_render_mode.cpp
    layer/layer.cpp
    layer/layer_impl.cpp
    layer/layer_stack.cpp
    layer/text_layer.cpp
    layer/tile_layer.cpp

    numeralconverter/alphabetic.cpp
    numeralconverter/alpha_big.cpp
    numeralconverter/alpha_small.cpp
    numeralconverter/numerals.cpp
    numeralconverter/numeric.cpp
    numeralconverter/roman.cpp
)

add_library(rpgm STATIC ${RPGMAPPER_LIB_SRC} ${RPGMAPPER_LIB_MOC_CPP})
target_link_libraries(rpgm quazip5 Qt5::Gui Qt5::Core ${CMAKE_REQUIRED_LIBRARIES})
