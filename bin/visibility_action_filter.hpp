/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_VISIBILITY_ACTION_FILTER_HPP
#define RPGMAPPER_VIEW_VISIBILITY_ACTION_FILTER_HPP


#include <QAction>
#include <QEvent>
#include <QWidget>


namespace rpgmapper {
namespace view {


class VisibiltyActionFiler : public QObject {

    Q_OBJECT

    QWidget * widget = nullptr;
    QAction * action = nullptr;

public:

    VisibiltyActionFiler(QWidget * widget, QAction * action, QObject * parent = nullptr);

protected:

    bool eventFilter(QObject * object, QEvent * event);
};


}
}


#endif
