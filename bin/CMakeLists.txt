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
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# Qt resources
set(RPGMAPPER_RCC
    view/rpgmapper.qrc
)
qt5_add_resources(RPGMAPPER_RES ${RPGMAPPER_RCC})

# Qt UIC
set(RPGMAPPER_UI
    view/mainwindow.ui
)
qt5_wrap_ui(RPGMAPPER_UI_H ${RPGMAPPER_UI})

# Qt MOC
set(RPGMAPPER_MOC
    view/mainwindow.hpp
)
qt5_wrap_cpp(RPGMAPPER_MOC_CPP ${RPGMAPPER_MOC})

# sources
set(RPGMAPPER_SRC

    main.cpp

    model/atlas.cpp
    model/map.cpp
    model/region.cpp

    view/mainwindow.cpp
)

# bin definition
add_executable(rpgmapper ${RPGMAPPER_SRC} ${RPGMAPPER_MOC_CPP} ${RPGMAPPER_RES} ${RPGMAPPER_UI_H})

# linkage
target_link_libraries(rpgmapper ${CMAKE_REQUIRED_LIBRARIES} Qt5::Core Qt5::Widgets)

# install
install(TARGETS rpgmapper RUNTIME DESTINATION bin)
