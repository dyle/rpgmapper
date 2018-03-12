/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "background_image_label.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


BackgroundImageLabel::BackgroundImageLabel(QWidget * parent) : QLabel(parent) {
}


void BackgroundImageLabel::paintEvent(UNUSED QPaintEvent * event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBackground(painter, rect());
}
