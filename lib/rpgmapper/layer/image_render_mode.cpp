/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QBuffer>

#include <map>

#include <rpgmapper/layer/image_render_mode.hpp>

using namespace rpgmapper::model::layer;


quint16 rpgmapper::model::layer::imageChecksum(QImage const & image) {

    if (image.isNull()) {
        return 0;
    }

    QByteArray imageAsPNG;
    QBuffer buffer(&imageAsPNG);
    image.save(&buffer, "PNG");

    return qChecksum(imageAsPNG.data(), static_cast<uint>(imageAsPNG.size()));
}


QString rpgmapper::model::layer::imageRenderModeToString(rpgmapper::model::layer::ImageRenderMode mode) {

    static std::map<ImageRenderMode, QString> const modes{
        {ImageRenderMode::plain, "plain"},
        {ImageRenderMode::scaled, "scaled"},
        {ImageRenderMode::tiled, "tiled"}
    };
    auto pair = modes.find(mode);
    if (pair == modes.end()) {
        throw std::runtime_error("Cannot convert ImageRenderMode to string.");
    }

    return (*pair).second;
}


rpgmapper::model::layer::ImageRenderMode rpgmapper::model::layer::stringToImageRenderMode(QString modeName) {

    static std::map<QString, ImageRenderMode> const modes{
        {"plain", ImageRenderMode::plain},
        {"scaled", ImageRenderMode::scaled},
        {"tiled", ImageRenderMode::tiled}
    };
    auto pair = modes.find(modeName);
    if (pair == modes.end()) {
        throw std::out_of_range("Mode name string does not name a image render enum value.");
    }
    return (*pair).second;
}
