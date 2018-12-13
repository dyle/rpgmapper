/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <rpgmapper/colorpalette.hpp>

using namespace rpgmapper::model;


ColorPalette ColorPalette::load(QByteArray const & data) {
    
    ColorPalette colorPalette;
    
    auto jsonDocument = QJsonDocument::fromJson(data);
    if (!jsonDocument.isObject()) {
        return colorPalette;
    }
    
    auto json = jsonDocument.object();
    if (json.contains("name") && json["name"].isString()) {
        colorPalette.name = json["name"].toString();
    }
    
    
    if (json.contains("colors") && json["colors"].isArray()) {
        auto jsonArray = json["colors"].toArray();
        for (int i = 0; i < std::min(jsonArray.size(), 16 * 16); ++i) {
            if (jsonArray.at(i).isString()) {
                auto colorString = jsonArray.at(i).toString();
                colorPalette.palette[i] = QColor{colorString};
            }
        }
        colorPalette.valid = true;
    }
    
    return colorPalette;
}


void ColorPalette::setName(QString name) {
    this->name = name;
}


QJsonDocument ColorPalette::toJSON() const {
    
    QJsonObject json;
    json["name"] = name;
    
    QJsonArray jsonColors;
    for (auto const & color : getPalette()) {
        jsonColors.append(color.name());
    }
    json["colors"] = jsonColors;
    
    return QJsonDocument{json};
}
