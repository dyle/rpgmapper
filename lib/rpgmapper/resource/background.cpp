/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>

#include <rpgmapper/resource/background.hpp>

using namespace rpgmapper::model::resource;


Background::Background(QString path, QByteArray const & data) : Resource{path, data} {
    QFileInfo fileInfo{path};
    auto fileName = fileInfo.fileName();
    setName(fileName.left(fileName.indexOf('.')));
}


bool Background::isBackground(QByteArray const & data) {
    
    static QMimeDatabase mimeDatabase;
    auto mimeType = mimeDatabase.mimeTypeForData(data);
    
    auto mimeTypeString = mimeType.name();
    return mimeTypeString.left(mimeTypeString.indexOf('/', 0)) == "image";
}


void Background::setData(QByteArray const & data) {
    
    Resource::setData(data);
    image = QImage::fromData(data);
    valid = image.isNull();
}
