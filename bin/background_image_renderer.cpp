/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "background_image_renderer.hpp"


using namespace rpgmapper::model;
using namespace rpgmapper::view;


BackgroundImageRenderer::BackgroundImageRenderer(QWidget * parent) : QLabel{parent} {
}


void BackgroundImageRenderer::paintEvent(QPaintEvent * event) {
    QLabel::paintEvent(event);
}


void BackgroundImageRenderer::setImageRenderMode(rpgmapper::model::BackgroundLayer::ImageRenderMode renderMode) {
    if (this->renderMode == renderMode) {
        return;
    }
    this->renderMode = renderMode;
    update();
}
