/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QBuffer>
#include <QColor>
#include <QJsonDocument>

#include <rpgmapper/map.hpp>


using namespace rpgmapper::model;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


static char const * BACKGROUND_COLOR_DEFAULT = "#fafaff";


BackgroundLayer::BackgroundLayer(Map * map, QObject * parent) : Layer{map, parent} {
    getAttributes()["color"] = BACKGROUND_COLOR_DEFAULT;
    getAttributes()["margins"] = R"raw({"top":0,"left":0,"right":0,"bottom":0})raw";
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


quint16 BackgroundLayer::getImageChecksum() const {
    return imageChecksum(image);
}


rpgmapper::model::ImageRenderMode BackgroundLayer::getImageRenderMode() const {

    auto pair = getAttributes().find("renderMode");
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


QMargins BackgroundLayer::getMargins() const {

    auto json = QJsonDocument::fromJson(getAttributes().at("margins").toUtf8()).object();

    int left = json.contains("left") ? static_cast<int>(json["left"].toDouble(0.0)) : 0;
    int top = json.contains("top") ? static_cast<int>(json["top"].toDouble(0.0)) : 0;
    int right = json.contains("right") ? static_cast<int>(json["right"].toDouble(0.0)) : 0;
    int bottom = json.contains("bottom") ? static_cast<int>(json["bottom"].toDouble(0.0)) : 0;

    return QMargins(left, top, right, bottom);
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
}


void BackgroundLayer::setImageRenderMode(ImageRenderMode mode) {
    getAttributes()["renderMode"] = imageRenderModeToString(mode);
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
