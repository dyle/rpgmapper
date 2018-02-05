#
# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
#







# additional includes
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

# Qt resources
set(RPGMAPPER_RCC
    view/rpgmapper.qrc
)
qt5_add_resources(RPGMAPPER_RES ${RPGMAPPER_RCC})

# Qt UIC
set(RPGMAPPER_UI
    view/aboutdialog.ui
    view/coordinatewidget.ui
    view/logdialog.ui
    view/mainwindow.ui
    view/mappropertiesdialog.ui
    view/origincornerwidget.ui
)
qt5_wrap_ui(RPGMAPPER_UI_H ${RPGMAPPER_UI})

# Qt MOC
set(RPGMAPPER_MOC
    view/aboutdialog.hpp
    view/coordinatewidget.hpp
    view/logdialog.hpp
    view/mainwindow.hpp
    view/mapscrollarea.hpp
    view/maptabwidget.hpp
    view/mapwidget.hpp
    view/mappropertiesdialog.hpp
    view/origincornerwidget.hpp
    view/structuraltreewidget.hpp
)
qt5_wrap_cpp(RPGMAPPER_MOC_CPP ${RPGMAPPER_MOC})

# sources
set(RPGMAPPER_SRC

    ${CMAKE_SOURCE_DIR}/include/rpgmapper/common_macros.h

    main.cpp
    view/aboutdialog.cpp
    view/coordinatewidget.cpp
    view/logdialog.cpp
    view/mainwindow.cpp
    view/mapscrollarea.cpp
    view/maptabwidget.cpp
    view/mapwidget.cpp
    view/mappropertiesdialog.cpp
    view/origincornerwidget.cpp
    view/structuraltreewidget.cpp
)

# bin definition
add_executable(rpgmapper ${RPGMAPPER_SRC} ${RPGMAPPER_MOC_CPP} ${RPGMAPPER_RES} ${RPGMAPPER_UI_H})

# linkage
target_link_libraries(rpgmapper rpgm ${CMAKE_REQUIRED_LIBRARIES} Qt5::Core Qt5::Widgets)

# install
install(TARGETS rpgmapper RUNTIME DESTINATION bin)
