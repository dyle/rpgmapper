#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#


include_directories(${CMAKE_SOURCE_DIR}/include)

set(RPGMAPPER_LIB_MOC
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/atlas.hpp
    #${CMAKE_SOURCE_DIR}/include/rpgmapper/layer.hpp
    #${CMAKE_SOURCE_DIR}/include/rpgmapper/map.hpp
    #${CMAKE_SOURCE_DIR}/include/rpgmapper/region.hpp

    #layer/backgroundlayer.hpp
    #layer/gridlayer.hpp
)
qt5_wrap_cpp(RPGMAPPER_LIB_MOC_CPP ${RPGMAPPER_LIB_MOC})

set(RPGMAPPER_LIB_SRC

    atlas.cpp
    #field.cpp
    #file.cpp
    #layer.cpp
    #map.cpp
    #region.cpp
    #unitconverter.cpp

    #layer/backgroundlayer.cpp
    #layer/gridlayer.cpp

    #unitconverter/alphabetic.cpp
    #unitconverter/alphabeticbigcapsconverter.cpp
    #unitconverter/alphabeticsmallcapsconverter.cpp
    #unitconverter/numericconverter.cpp
    #unitconverter/romanconverter.cpp
)

add_library(rpgm STATIC ${RPGMAPPER_LIB_SRC} ${RPGMAPPER_LIB_MOC_CPP})
target_link_libraries(rpgm quazip5 Qt5::Gui Qt5::Core ${CMAKE_REQUIRED_LIBRARIES})
