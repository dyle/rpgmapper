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
namespace layer {


/**
 * Enumeration on how a single image is to be rendered on a map.
 */
enum class ImageRenderMode {
    plain,          /**< the image should be rendered 1:1 as-is. */
    scaled,         /**< the image should be stretched (or squeezed) to match the map's dimensions. */
    tiled           /**< the image should be rendered 1:1 as-is, but repeated in both dimensions. */
};


/**
 * Gets a 16 bit checksum value of an image data.
 *
 * @param   image   the image to create a hash value for.
 * @return  the hash value for the image.
 */
quint16 imageChecksum(QImage const & image);


/**
 * Converts a mode enumeration value into a human readable string.
 *
 * @param   mode    the mode to convert.
 * @return  "plain", "scaled", ...
 */
QString imageRenderModeToString(rpgmapper::model::layer::ImageRenderMode mode);


/**
 * Converts a human readable string into an image render mode.
 *
 * @param   modeName        "plain", "scaled", ...
 * @return  the image render mode enumeration value.
 */
rpgmapper::model::layer::ImageRenderMode stringToImageRenderMode(QString modeName);


}
}
}


#endif
