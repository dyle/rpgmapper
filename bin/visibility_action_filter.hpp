/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_VISIBILITY_ACTION_FILTER_HPP
#define RPGMAPPER_VIEW_VISIBILITY_ACTION_FILTER_HPP


#include <QAction>
#include <QEvent>
#include <QWidget>


namespace rpgmapper::view {


/**
 * This event filter triggers the show/hide event of dock windows to make actions check/uncheck.
 */
class VisibilityActionFiler : public QObject {

    Q_OBJECT

    QWidget * widget = nullptr;         /**< The widget which will be shown/hidden */
    QAction * action = nullptr;         /**< The action which will be checked/unchecked accordingly */

public:

    /**
     * Constructor
     * @param   widget          widget to be displayed (or not).
     * @param   action          action instance which will be checked on show and unchecked on hide.
     * @param   parent          parent Qt object for this filter.
     */
    VisibilityActionFiler(QWidget * widget, QAction * action, QObject * parent = nullptr);

protected:

    /**
     * Process events on the widget object.
     *
     * @param   object      the object involved.
     * @param   event       the event to check.
     * @return  true, if event was consumed.
     */
    bool eventFilter(QObject * object, QEvent * event);
};


}


#endif
