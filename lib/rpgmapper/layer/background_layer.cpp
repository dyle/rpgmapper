/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QBuffer>
#include <QColor>
#include <QJsonDocument>

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/resource/background.hpp>
#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::layer;
using namespace rpgmapper::model::resource;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


/**
 * Default background color.
 */
static char const * BACKGROUND_COLOR_DEFAULT = "#dddddd";


BackgroundLayer::BackgroundLayer(Map * map) : Layer{map}, backgroundPixmap{nullptr} {
    getAttributes()["color"] = BACKGROUND_COLOR_DEFAULT;
    getAttributes()["rendering"] = "color";
    getAttributes()["renderImageMode"] = "plain";
    getAttributes()["renderImageName"] = QString::null;
}


BackgroundLayer::~BackgroundLayer() {
    if (backgroundPixmap) {
        delete backgroundPixmap;
    }
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

    return true;
}

void BackgroundLayer::draw(QPainter & painter, int tileSize) const {
    
    auto map = getMap();
    if (!map) {
        throw exception::invalid_map{};
    }
    
    if (isColorRendered()) {
        drawColor(painter, tileSize);
    }
    if (isImageRendered()) {
        drawImage(painter, tileSize);
    }
}


void BackgroundLayer::drawColor(QPainter & painter, int tileSize) const {
    auto rect = getMap()->getCoordinateSystem()->getInnerRect(tileSize);
    QColor backgroundColor = getColor();
    painter.fillRect(rect, backgroundColor);
}


void BackgroundLayer::drawImage(QPainter & painter, int tileSize) const {
    auto rect = getMap()->getCoordinateSystem()->getOuterRect(tileSize);
    drawBackground(painter, rect);
}


QPixmap const * BackgroundLayer::getBackgroundPixmap() const {
    return backgroundPixmap;
}


QColor BackgroundLayer::getColor() const {
    auto pair = getAttributes().find("color");
    if (pair == getAttributes().end()) {
        return QColor{QString{BACKGROUND_COLOR_DEFAULT}};
    }
    return QColor{pair->second};
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
    jsonObject["renderImageMode"] = imageRenderModeToString(getImageRenderMode());
    jsonObject["renderImageName"] = getImageResource();
    jsonObject["rendering"] = getRendering();

    return jsonObject;
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
    
    static std::map<QString, bool> const renderingValues {
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


void BackgroundLayer::setImageResource(QString path) {
    
    if (getImageResource() != path) {
        
        getAttributes()["renderImageName"] = path;
        
        auto resource = ResourceDB::getResource(path);
        if (resource) {
    
            if (backgroundPixmap) {
                delete backgroundPixmap;
                backgroundPixmap = nullptr;
            }
    
            auto backgroundResource = dynamic_cast<rpgmapper::model::resource::Background *>(resource.data());
            if (backgroundResource->isValid()) {
                backgroundPixmap = new QPixmap{QPixmap::fromImage(backgroundResource->getImage())};
            }
        }
        
        emit backgroundImageChanged(path);
    }
}


void BackgroundLayer::setImageRenderMode(ImageRenderMode mode) {
    
    if (getImageRenderMode() != mode) {
        BackgroundRenderer::setImageRenderMode(mode);
        emit backgroundImageRenderModeChanged(mode);
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
