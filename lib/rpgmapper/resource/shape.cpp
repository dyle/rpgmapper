/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QMimeDatabase>
#include <QMimeType>
#include <QPainter>
#include <QSvgRenderer>

#include <rpgmapper/resource/shape.hpp>

using namespace rpgmapper::model::resource;


Shape::Shape(QString name, QByteArray const & data) : Resource{std::move(name), data} {
}


void Shape::addCache(unsigned int tileSize, QImage image, QPixmap pixmap, QIcon icon) const {
    icons.emplace(tileSize, icon);
    images.emplace(tileSize, image);
    pixmaps.emplace(tileSize, pixmap);
}


QIcon Shape::getIcon(unsigned int tileSize) const {
    prepare(tileSize);
    return icons.at(tileSize);
}


QImage Shape::getImage(unsigned int tileSize) const {
    prepare(tileSize);
    return images.at(tileSize);
}


QPixmap Shape::getPixmap(unsigned int tileSize) const {
    prepare(tileSize);
    return pixmaps.at(tileSize);
}


bool Shape::isShape(QByteArray const & data) {
    
    static QMimeDatabase mimeDatabase;
    auto mimeType = mimeDatabase.mimeTypeForData(data);
    
    auto mimeTypeString = mimeType.name();
    return mimeTypeString == "image/svg+xml";
}


void Shape::prepare(unsigned int tileSize) const {

    auto iconPresent = icons.find(tileSize) != icons.end();
    auto imagePresent = images.find(tileSize) != images.end();
    auto pixmapPresent = pixmaps.find(tileSize) != pixmaps.end();
    if (!iconPresent || !imagePresent || !pixmapPresent) {
    
        auto image = render(tileSize);
        auto pixmap = QPixmap::fromImage(image);
        auto icon = QIcon{pixmap};
        addCache(tileSize, image, pixmap, icon);
    }
}


QImage Shape::render(unsigned int tileSize) const {
    
    QSize size{static_cast<int>(tileSize), static_cast<int>(tileSize)};
    QImage image{size, QImage::Format_ARGB32_Premultiplied};

    QPainter painter{&image};
    painter.setBackgroundMode(Qt::TransparentMode);
    
    QRect rect{{0, 0}, image.size()};
    painter.eraseRect(rect);
    
    QSvgRenderer svgRenderer{getData()};
    svgRenderer.render(&painter);
    return image;
}


void Shape::setData(QByteArray const & data) {
    Resource::setData(data);
}
