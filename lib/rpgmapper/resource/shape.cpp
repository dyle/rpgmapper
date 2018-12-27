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


void Shape::addCache(QString index, QImage image, QPixmap pixmap, QIcon icon) const {
    icons.emplace(index, icon);
    images.emplace(index, image);
    pixmaps.emplace(index, pixmap);
}


QIcon Shape::getIcon(unsigned int tileSize, double rotation, double stretch) const {
    return icons.at(prepare(tileSize, rotation, stretch));
}


QImage Shape::getImage(unsigned int tileSize, double rotation, double stretch) const {
    return images.at(prepare(tileSize, rotation, stretch));
}


QString Shape::getIndex(unsigned int tileSize, double rotation, double stretch) {
    return QString{"%1@%2-%3"}.arg(tileSize).arg(rotation).arg(stretch);
}


QPixmap Shape::getPixmap(unsigned int tileSize, double rotation, double stretch) const {
    return pixmaps.at(prepare(tileSize, rotation, stretch));
}


bool Shape::isShape(QByteArray const & data) {
    
    static QMimeDatabase mimeDatabase;
    auto mimeType = mimeDatabase.mimeTypeForData(data);
    
    auto mimeTypeString = mimeType.name();
    return mimeTypeString == "image/svg+xml";
}


QString Shape::prepare(unsigned int tileSize, double rotation, double stretch) const {
    
    auto index = getIndex(tileSize, rotation, stretch);
    
    auto iconPresent = icons.find(index) != icons.end();
    auto imagePresent = images.find(index) != images.end();
    auto pixmapPresent = pixmaps.find(index) != pixmaps.end();
    
    if (!iconPresent || !imagePresent || !pixmapPresent) {
    
        auto image = render(tileSize, rotation, stretch);
        auto pixmap = QPixmap::fromImage(image);
        auto icon = QIcon{pixmap};
        addCache(index, image, pixmap, icon);
    }
    
    return index;
}


QImage Shape::render(unsigned int tileSize, double rotation, double stretch) const {
    
    QSize size{static_cast<int>(tileSize), static_cast<int>(tileSize)};
    QImage image{size, QImage::Format_ARGB32_Premultiplied};
    image.fill(0);

    QPainter painter{&image};
    QSvgRenderer svgRenderer{getData()};
    svgRenderer.render(&painter);
    
    QMatrix matrix;
    matrix.rotate(rotation);
    matrix.scale(stretch, stretch);
    
    return image.transformed(matrix, Qt::SmoothTransformation);
}


void Shape::setData(QByteArray const & data) {
    Resource::setData(data);
}


Shape::TargetLayer Shape::targetLayerFromString(QString layer) {
    
    if (layer == "base") {
        return TargetLayer::base;
    }
    if (layer == "tile") {
        return TargetLayer::tile;
    }
    
    return TargetLayer::unknown;
}
