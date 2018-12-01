/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QBuffer>
#include <QColor>
#include <QJsonDocument>

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/resource.hpp>

using namespace rpgmapper::model;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


/**
 * Default background color.
 */
static char const * BACKGROUND_COLOR_DEFAULT = "#fafaff";


BackgroundLayer::BackgroundLayer(Map * map) : Layer{map} {
    getAttributes()["color"] = BACKGROUND_COLOR_DEFAULT;
    getAttributes()["margins"] = R"raw({"top":0,"left":0,"right":0,"bottom":0})raw";
    getAttributes()["rendering"] = "color";
    getAttributes()["renderImageMode"] = "plain";
    getAttributes()["renderImageName"] = QString::null;
}


bool BackgroundLayer::applyJsonMargins(QJsonObject const & json) {

    auto margins = getMargins();

    if (json.contains("left") && json["left"].isDouble()) {
        margins.setLeft(static_cast<int>(json["left"].toDouble()));
    }
    if (json.contains("top") && json["top"].isDouble()) {
        margins.setTop(static_cast<int>(json["top"].toDouble()));
    }
    if (json.contains("right") && json["right"].isDouble()) {
        margins.setRight(static_cast<int>(json["right"].toDouble()));
    }
    if (json.contains("bottom") && json["bottom"].isDouble()) {
        margins.setBottom(static_cast<int>(json["bottom"].toDouble()));
    }

    setMargins(margins);
    return true;
}



bool BackgroundLayer::applyJSON(QJsonObject const & json) {

    Layer::applyJSON(json);

    if (json.contains("color") && json["color"].isString()) {
        setColor(QColor{json["color"].toString()});
    }
    if (json.contains("renderImageMode") && json["renderImageMode"].isString()) {
        setImageRenderMode(stringToImageRenderMode(json["renderImageMode"].toString()));
    }
    if (json.contains("renderImageName") && json["renderImageName"].isString()) {
        setImageResource(json["renderImageName"].toString());
    }
    if (json.contains("rendering") && json["rendering"].isString()) {
        setRendering(json["rendering"].toString());
    }
    if (json.contains("margins") && json["margins"].isObject()) {
        applyJsonMargins(json["margins"].toObject());
    }

    return true;
}


void BackgroundLayer::draw(QPainter & painter, int tileSize) const {
    
    auto map = getMap();
    if (!map) {
        throw exception::invalid_map{};
    }
    
    QSize size = map->getCoordinateSystem()->getSize() * tileSize;
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


rpgmapper::model::ImageRenderMode BackgroundLayer::getImageRenderMode() const {

    auto pair = getAttributes().find("renderImageMode");
    if (pair == getAttributes().end()) {
        return ImageRenderMode::plain;
    }

    auto mode = ImageRenderMode::plain;
    try {
        mode = stringToImageRenderMode((*pair).second);
    }
    catch (UNUSED std::out_of_range & ex) {}

    return mode;
}


QString BackgroundLayer::getImageResource() const {
    auto pair = getAttributes().find("renderImageName");
    if (pair == getAttributes().end()) {
        return QString::null;
    }
    return pair->second;
}


QJsonObject BackgroundLayer::getJSON() const {

    QJsonObject jsonObject = Layer::getJSON();

    jsonObject["color"] = getColor().name(QColor::HexArgb);
    jsonObject["renderImageMode"] = rpgmapper::model::imageRenderModeToString(getImageRenderMode());
    jsonObject["renderImageName"] = getImageResource();
    jsonObject["rendering"] = getRendering();

    QJsonObject jsonMargins;
    auto margins = getMargins();
    jsonMargins["left"] = margins.left();
    jsonMargins["top"] = margins.top();
    jsonMargins["right"] = margins.right();
    jsonMargins["bottom"] = margins.bottom();
    jsonObject["margins"] = jsonMargins;
    
    return jsonObject;
}


QMargins BackgroundLayer::getMargins() const {

    auto json = QJsonDocument::fromJson(getAttributes().at("margins").toUtf8()).object();

    int left = json.contains("left") ? static_cast<int>(json["left"].toDouble(0.0)) : 0;
    int top = json.contains("top") ? static_cast<int>(json["top"].toDouble(0.0)) : 0;
    int right = json.contains("right") ? static_cast<int>(json["right"].toDouble(0.0)) : 0;
    int bottom = json.contains("bottom") ? static_cast<int>(json["bottom"].toDouble(0.0)) : 0;

    return {left, top, right, bottom};
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


bool BackgroundLayer::isValidRendering(QString rendering) {
    static std::map<QString, bool> const renderingValues{
        {"color", true},
        {"image", true}
    };
    return renderingValues.find(rendering) != renderingValues.end();
}


void BackgroundLayer::setColor(QColor color) {
    
    if (getColor() != color) {
        getAttributes()["color"] = color.name(QColor::HexArgb);
        emit backgroundColorChanged(color);
    }
}


void BackgroundLayer::setImageResource(QString name) {
    if (getImageResource() != name) {
        getAttributes()["renderImageName"] = name;
        emit backgroundImageChanged(name);
    }
}


void BackgroundLayer::setImageRenderMode(ImageRenderMode mode) {
    if (getImageRenderMode() != mode) {
        getAttributes()["renderImageMode"] = imageRenderModeToString(mode);
        emit backgroundImageRenderModeChanged(mode);
    }
}


void BackgroundLayer::setMargins(QMargins margins) {
    
    if (getMargins() != margins) {
    
        auto json = QString(R"raw({"top":%1,"left":%2,"right":%3,"bottom":%4})raw")
                .arg(margins.top()).arg(margins.left()).arg(margins.right()).arg(margins.bottom());
        getAttributes()["margins"] = json;
    
        emit backgroundMarginsChanged(margins);
    }
}


void BackgroundLayer::setRendering(QString rendering) {
    
    if (getRendering() != rendering) {
    
        if (!isValidRendering(rendering)) {
            throw std::runtime_error("Invalid background rendering value.");
        }
        getAttributes()["rendering"] = rendering;
        
        emit backgroundRenderingChanged(rendering);
    }
}
