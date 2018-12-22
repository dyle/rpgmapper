/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <rpgmapper/resource/shape_catalog.hpp>

using namespace rpgmapper::model::resource;


ShapeCatalog::ShapeCatalog(QString name, QByteArray const & data) : Resource{std::move(name), data} {
    fromJSON();
}


void ShapeCatalog::fromJSON() {
    
    valid = false;
    
    auto jsonDocument = QJsonDocument::fromJson(getData());
    if (!jsonDocument.isObject()) {
        return;
    }
    
    auto json = jsonDocument.object();
    if (json.contains("name") && json["name"].isString()) {
        setName(json["name"].toString());
    }
    
    auto catalogBase = getCatalogBase();
    if (json.contains("shapes") && json["shapes"].isArray()) {
        auto jsonArray = json["shapes"].toArray();
        for (int i = 0; i < jsonArray.size(); ++i) {
            if (jsonArray.at(i).isObject()) {
                
                auto jsonShape = jsonArray.at(i).toObject();
                
                QString shapeName;
                if (jsonShape.contains("name") && jsonShape["name"].isString()) {
                    shapeName = jsonShape["name"].toString();
                }
                
                QString shapePath;
                if (jsonShape.contains("file") && jsonShape["file"].isString()) {
                    shapePath = catalogBase + "/" + jsonShape["file"].toString();
                }
                
                if (!shapeName.isEmpty() && !shapePath.isEmpty()) {
                    shapes.emplace(shapeName, shapePath);
                }
            }
        }
        valid = true;
    }
}


QString ShapeCatalog::getCatalogBase() const {
    QFileInfo fileInfo{getPath()};
    return fileInfo.dir().path();
}


bool ShapeCatalog::isShapeCatalog(QByteArray const & data) {
    
    auto jsonDocument = QJsonDocument::fromJson(data);
    if (!jsonDocument.isObject()) {
        return false;
    }
    
    auto json = jsonDocument.object();
    bool namePresent = json.contains("name") && json["name"].isString();
    bool shapesPresent = json.contains("shapes") && json["shapes"].isArray();
    
    return namePresent && shapesPresent;
}


void ShapeCatalog::setData(QByteArray const & data) {
    Resource::setData(data);
    fromJSON();
}
