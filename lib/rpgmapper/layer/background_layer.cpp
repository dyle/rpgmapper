/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QBuffer>
#include <QColor>
#include <QJsonDocument>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>

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


BackgroundLayer::BackgroundLayer(QSharedPointer<Map> map) : Layer{map} {
    getAttributes()["color"] = BACKGROUND_COLOR_DEFAULT;
    getAttributes()["margins"] = R"raw({"top":0,"left":0,"right":0,"bottom":0})raw";
    getAttributes()["rendering"] = "color";
    getAttributes()["renderImageMode"] = "plain";
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
    if (json.contains("rendering") && json["rendering"].isString()) {
        setRendering(json["rendering"].toString());
    }
    if (json.contains("margins") && json["margins"].isObject()) {
        applyJsonMargins(json["margins"].toObject());
    }

    // TODO: load image
    return true;
}


void BackgroundLayer::draw(QPainter & painter, int tileSize) const {
    QSize size = getMap()->getCoordinateSystem()->getSize() * tileSize;
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


QJsonObject BackgroundLayer::getJSON() const {

    QJsonObject jsonObject = Layer::getJSON();

    jsonObject["color"] = getColor().name(QColor::HexArgb);
    jsonObject["renderImageMode"] = rpgmapper::model::imageRenderModeToString(getImageRenderMode());
    jsonObject["rendering"] = getRendering();

    QJsonObject jsonMargins;
    auto margins = getMargins();
    jsonMargins["left"] = margins.left();
    jsonMargins["top"] = margins.top();
    jsonMargins["right"] = margins.right();
    jsonMargins["bottom"] = margins.bottom();
    jsonObject["margins"] = jsonMargins;

    /*
     * TODO: add resources
     *
    if (!imageResourceHash.isEmpty()) {
        auto imageResource = getResourceDB()->getResource(imageResourceHash);
        if (imageResource->isEmpty()) {
            throw std::logic_error("Unable to find background image resource though a hash is available.");
        }
        jsonObject["image"] = imageResource->getName();
        content[imageResource->getName()] = imageResource->getData();
    }
    */
    
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


void BackgroundLayer::setImage(QImage image) {

    this->image = std::move(image);

    QByteArray data;
    QBuffer buf(&data);
    buf.open(QIODevice::WriteOnly);
    this->image.save(&buf, "PNG");

    imageResourceHash = Resource::getHash(data);
    auto imageResourcePath = QString("images/background/%1.png").arg(imageResourceHash);
    
    /*
     * TODO: set resources
     *
    auto backgroundResource = ResourcePointer{new Resource{imageResourcePath, data}};
    getResourceDB()->addResource(backgroundResource);
     */
}


void BackgroundLayer::setImageRenderMode(ImageRenderMode mode) {
    getAttributes()["renderImageMode"] = imageRenderModeToString(mode);
}


void BackgroundLayer::setMargins(QMargins const & margins) {
    auto json = QString(R"raw({"top":%1,"left":%2,"right":%3,"bottom":%4})raw")
        .arg(margins.top()).arg(margins.left()).arg(margins.right()).arg(margins.bottom());
    getAttributes()["margins"] = json;
}


void BackgroundLayer::setRendering(QString const & rendering) {
    if (!isValidRendering(rendering)) {
        throw std::runtime_error("Invalid background rendering value.");
    }
    getAttributes()["rendering"] = rendering;
}
