/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QColor>

#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


static char const * BACKGROUND_COLOR_DEFAULT = "#fafaff";


BackgroundLayer::BackgroundLayer(Map * map, QObject * parent) : Layer{map, parent} {
    getAttributes()["color"] = BACKGROUND_COLOR_DEFAULT;
    getAttributes()["rendering"] = "color";
    getAttributes()["renderMode"] = "plain";
}


void BackgroundLayer::draw(QPainter & painter, int tileSize) const {
    QSize size = getMap()->getSize() * tileSize;
    QColor backgroundColor = getColor();
    painter.fillRect(QRect{QPoint{0, 0}, size}, backgroundColor);
}


QColor BackgroundLayer::getColor() const {
    auto pair = getAttributes().find("color");
    if (pair == getAttributes().end()) {
        return QColor{QString{BACKGROUND_COLOR_DEFAULT}};
    }
    return QColor{pair->second};
}


QImage const & BackgroundLayer::getImage() const {
    return image;
}


BackgroundLayer::ImageRenderMode BackgroundLayer::getImageRenderMode() const {

    auto pair = getAttributes().find("renderMode");
    if (pair == getAttributes().end()) {
        return ImageRenderMode::plain;
    }

    static std::map<QString, ImageRenderMode> const modes{
        {"plain", ImageRenderMode::plain},
        {"scaled", ImageRenderMode::scaled},
        {"tiled", ImageRenderMode::tiled}
    };
    auto renderPair = modes.find((*pair).second);
    if (renderPair == modes.end()) {
        return ImageRenderMode::plain;
    }

    return (*renderPair).second;
}


QMargins const & BackgroundLayer::getMargins() const {
    return margins;
}


QString BackgroundLayer::getRendering() const {
    auto pair = getAttributes().find("rendering");
    if (pair == getAttributes().end()) {
        return QString::null;
    }
    return pair->second;
}

bool BackgroundLayer::isColorRendered() const {
    return getRendering() == "color";
}


bool BackgroundLayer::isImageRendered() const {
    return getRendering() == "image";
}


bool BackgroundLayer::isValidRendering(QString const & rendering) {
    static std::map<QString, bool> const renderingValues{
        {"color", true},
        {"image", true}
    };
    return renderingValues.find(rendering) != renderingValues.end();
}


void BackgroundLayer::setColor(QColor color) {
    getAttributes()["color"] = color.name(QColor::HexArgb);
}


void BackgroundLayer::setRendering(QString const & rendering) {
    if (!isValidRendering(rendering)) {
        throw std::runtime_error("Invalid background rendering value.");
    }
    getAttributes()["rendering"] = rendering;
}
