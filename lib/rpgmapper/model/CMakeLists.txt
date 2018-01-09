# ------------------------------------------------------------
# CMakeLists.txt for RPGMapper/bin
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
set(RPGMAPPER_MODEL_SRC

    atlas.cpp
    changeable.cpp
    map.cpp
    nameable.cpp
    region.cpp
)

# define library
add_library(rpgmapper_model STATIC ${RPGMAPPER_MODEL_SRC})
target_link_libraries(rpgmapper_model Qt5::Core ${CMAKE_REQUIRED_LIBRARIES})
