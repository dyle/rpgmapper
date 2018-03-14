/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_IMAGE_RENDER_MODE_HPP
#define RPGMAPPER_MODEL_IMAGE_RENDER_MODE_HPP

#include <QImage>
#include <QString>


namespace rpgmapper {
namespace model {


enum class ImageRenderMode { plain, scaled, tiled };

quint16 imageChecksum(QImage const & image);

QString imageRenderModeToString(rpgmapper::model::ImageRenderMode mode);

rpgmapper::model::ImageRenderMode stringToImageRenderMode(QString modeName);


}
}


#endif
