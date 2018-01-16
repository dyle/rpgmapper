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

include_directories(${CMAKE_SOURCE_DIR}/include)

set(RPGMAPPER_LIB_MOC
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/atlas.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/changeable.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/nameable.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/map.hpp
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/region.hpp
)
qt5_wrap_cpp(RPGMAPPER_LIB_MOC_CPP ${RPGMAPPER_LIB_MOC})

set(RPGMAPPER_LIB_SRC

    ${CMAKE_SOURCE_DIR}/include/rpgmapper/common_macros.h
    ${CMAKE_SOURCE_DIR}/include/rpgmapper/types.hpp

    atlas.cpp               ${CMAKE_SOURCE_DIR}/include/rpgmapper/atlas.hpp
    changeable.cpp          ${CMAKE_SOURCE_DIR}/include/rpgmapper/changeable.hpp
    controller.cpp          ${CMAKE_SOURCE_DIR}/include/rpgmapper/controller.hpp
    file.cpp                ${CMAKE_SOURCE_DIR}/include/rpgmapper/file.hpp
    map.cpp                 ${CMAKE_SOURCE_DIR}/include/rpgmapper/map.hpp
    nameable.cpp            ${CMAKE_SOURCE_DIR}/include/rpgmapper/nameable.hpp
    region.cpp              ${CMAKE_SOURCE_DIR}/include/rpgmapper/region.hpp
)

add_library(rpgm STATIC ${RPGMAPPER_LIB_SRC} ${RPGMAPPER_LIB_MOC_CPP})
target_link_libraries(rpgm quazip5 Qt5::Core ${CMAKE_REQUIRED_LIBRARIES})
