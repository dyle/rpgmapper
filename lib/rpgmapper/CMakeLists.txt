#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#


include_directories(${CMAKE_SOURCE_DIR}/include)

set(RPGMAPPER_LIB_MOC

    ${CMAKE_SOURCE_DIR}/include/rpgmapper/atlas.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/layer.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/map.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/region.hpp

    layer/background_layer.hpp
    layer/grid_layer.hpp
)
qt5_wrap_cpp(RPGMAPPER_LIB_MOC_CPP ${RPGMAPPER_LIB_MOC})

set(RPGMAPPER_LIB_SRC

    atlas.cpp
    atlas_impl.cpp
    atlas_io.cpp
    #field.cpp
    layer.cpp
    layer_impl.cpp
    map.cpp
    map_impl.cpp
    nameable.cpp
    numerals.cpp
    region.cpp
    region_impl.cpp

    layer/background_layer.cpp
    layer/grid_layer.cpp

    numeralconverter/alphabetic.cpp
    numeralconverter/alpha_big.cpp
    numeralconverter/alpha_small.cpp
    numeralconverter/numeric.cpp
    numeralconverter/roman.cpp

    zip/zip.cpp
)

add_library(rpgm STATIC ${RPGMAPPER_LIB_SRC} ${RPGMAPPER_LIB_MOC_CPP})
target_link_libraries(rpgm quazip5 Qt5::Gui Qt5::Core ${CMAKE_REQUIRED_LIBRARIES})
