/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QJsonArray>
#include <QJsonDocument>

#include <rpgmapper/colorpalette.hpp>

using namespace rpgmapper::model;


ColorPalette ColorPalette::load(QByteArray const & data) {
    
    ColorPalette colorPalette;
    
    auto json = QJsonDocument::fromJson(data);
    if (!json.isArray()) {
        return colorPalette;
    }
    
    auto jsonArray = json.array();
    for (int i = 0; i < std::min(jsonArray.size(), 16*16); ++i) {
        if (jsonArray.at(i).isString()) {
            auto colorString = jsonArray.at(i).toString();
            colorPalette.palette[i / 16][i % 16] = QColor{colorString};
        }
    }
    colorPalette.valid = true;
    
    return colorPalette;
}
