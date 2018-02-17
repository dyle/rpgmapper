# This file is part of rpgmapper.
# See the LICENSE file for the software license.
# (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com


include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(RPGMAPPER_RCC
    rpgmapper.qrc
)
qt5_add_resources(RPGMAPPER_RES ${RPGMAPPER_RCC})


set(RPGMAPPER_UI
    aboutdialog.ui
    coordinatesoriginwidget.ui
    coordinateswidget.ui
    logdialog.ui
    mainwindow.ui
    mappropertiesdialog.ui
)
qt5_wrap_ui(RPGMAPPER_UI_H ${RPGMAPPER_UI})


set(RPGMAPPER_MOC
    aboutdialog.hpp
    coordinatesoriginwidget.hpp
    coordinateswidget.hpp
    logdialog.hpp
    mainwindow.hpp
#    view/mapscrollarea.hpp
#    view/maptabwidget.hpp
#    view/mapwidget.hpp
#    view/mappropertiesdialog.hpp
    structuraltreewidget.hpp
)
qt5_wrap_cpp(RPGMAPPER_MOC_CPP ${RPGMAPPER_MOC})


set(RPGMAPPER_SRC
    aboutdialog.cpp
    coordinatesoriginwidget.cpp
    coordinateswidget.cpp
    logdialog.cpp
    main.cpp
    mainwindow.cpp
    mainwindow_impl.cpp
#    view/mapscrollarea.cpp
    maptabwidget.cpp
    maptabwidget_impl.cpp
#    view/mapwidget.cpp
#    view/mappropertiesdialog.cpp
    structuraltreewidget.cpp
)


add_executable(rpgmapper ${RPGMAPPER_SRC} ${RPGMAPPER_MOC_CPP} ${RPGMAPPER_RES} ${RPGMAPPER_UI_H})
target_link_libraries(rpgmapper rpgm ${CMAKE_REQUIRED_LIBRARIES} Qt5::Core Qt5::Widgets)
install(TARGETS rpgmapper RUNTIME DESTINATION bin)
