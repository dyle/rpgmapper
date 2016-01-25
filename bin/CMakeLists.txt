# ------------------------------------------------------------
# CMakeLists.txt for RPGMapper/bin
#
# Copyright (C) 2015, 2016 Oliver Maurhart, <dyle@dyle.org>
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
    view/about_dialog.ui
    view/atlas_properties_dialog.ui
    view/atlas_properties_widget.ui
    view/main_window.ui
)
qt5_wrap_ui(RPGMAPPER_UI_H ${RPGMAPPER_UI})

# Qt MOC
set(RPGMAPPER_MOC
    model/atlas.h
    model/map.h
    view/atlas_properties_dialog.h
    view/atlas_properties_widget.h
    view/clickable_label.h
    view/main_window.h
)
qt5_wrap_cpp(RPGMAPPER_MOC_CPP ${RPGMAPPER_MOC})

# sources
set(RPGMAPPER_SRC

    main.cpp

    model/atlas.cpp
    model/map.cpp
    model/maps.cpp

    view/atlas_properties_dialog.cpp
    view/atlas_properties_widget.cpp
    view/clickable_label.cpp
    view/main_window.cpp
)

# bin definition
add_executable(rpgmapper ${RPGMAPPER_SRC} ${RPGMAPPER_MOC_CPP} ${RPGMAPPER_RES} ${RPGMAPPER_UI_H})

# linkage
target_link_libraries(rpgmapper ${CMAKE_REQUIRED_LIBRARIES} Qt5::Core Qt5::Widgets)

# install
install(TARGETS rpgmapper RUNTIME DESTINATION bin)

