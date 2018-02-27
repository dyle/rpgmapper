/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "visibility_action_filter.hpp"

using namespace rpgmapper::view;


VisibiltyActionFiler::VisibiltyActionFiler(QWidget * widget, QAction * action, QObject * parent)
        : QObject(parent), widget(widget), action(action) {

    if (widget == nullptr) {
        throw std::runtime_error("widget in VisibiltyActionFiler must not be nullptr.");
    }
    if (action == nullptr) {
        throw std::runtime_error("action in VisibiltyActionFiler must not be nullptr.");
    }

    widget->installEventFilter(this);
}


bool VisibiltyActionFiler::eventFilter(QObject * object, QEvent * event) {
    if (object == widget) {
        switch (event->type()) {
            case QEvent::Hide:
                action->setChecked(false);
                break;
            case QEvent::Show:
                action->setChecked(true);
                break;
            default:
                break;
        }
    }
    return QObject::eventFilter(object, event);
}