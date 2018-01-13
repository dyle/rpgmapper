# ------------------------------------------------------------
# CMakeLists.txt
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

# additional includes
include_directories(${CMAKE_SOURCE_DIR}/include)

# sources
set(RPGMAPPER_CTRL_SRC

    ${CMAKE_SOURCE_DIR}/include/rpgmapper/common_macros.h

    controller.cpp          ${CMAKE_SOURCE_DIR}/include/rpgmapper/ctrl/controller.hpp
    file.cpp                ${CMAKE_SOURCE_DIR}/include/rpgmapper/ctrl/file.hpp
)

# define library
add_library(rpgmapper_ctrl STATIC ${RPGMAPPER_CTRL_SRC})
target_link_libraries(rpgmapper_ctrl rpgmapper_model quazip5 Qt5::Core ${CMAKE_REQUIRED_LIBRARIES})
