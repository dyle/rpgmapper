/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <rpgmapper/resource/colorpalette.hpp>

using namespace rpgmapper::model::resource;


ColorPalette::ColorPalette(QString path, QByteArray const & data) : Resource{std::move(path), data} {
    fromJSON();
}


void ColorPalette::fromJSON() {
    
    valid = false;
    auto jsonDocument = QJsonDocument::fromJson(getData());
    if (!jsonDocument.isObject()) {
        return;
    }
    
    auto json = jsonDocument.object();
    if (json.contains("name") && json["name"].isString()) {
        setName(json["name"].toString());
    }
    
    if (json.contains("colors") && json["colors"].isArray()) {
        auto jsonArray = json["colors"].toArray();
        for (int i = 0; i < std::min(jsonArray.size(), 16 * 16); ++i) {
            if (jsonArray.at(i).isString()) {
                auto colorString = jsonArray.at(i).toString();
                palette[i] = QColor{colorString};
            }
        }
        valid = true;
    }
}


bool ColorPalette::isColorPalette(QByteArray const & data) {
    
    auto jsonDocument = QJsonDocument::fromJson(data);
    if (!jsonDocument.isObject()) {
        return false;
    }
    
    auto json = jsonDocument.object();
    bool namePresent = json.contains("name") && json["name"].isString();
    bool colorsPresent = json.contains("colors") && json["colors"].isArray();
    
    return namePresent && colorsPresent;
}


void ColorPalette::setData(QByteArray const & data) {
    Resource::setData(data);
    fromJSON();
}


QJsonDocument ColorPalette::toJSON() const {
    
    QJsonObject json;
    json["name"] = getName();
    
    QJsonArray jsonColors;
    for (auto const & color : getPalette()) {
        jsonColors.append(color.name());
    }
    json["colors"] = jsonColors;
    
    return QJsonDocument{json};
}
