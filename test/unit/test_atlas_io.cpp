/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <QFile>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/atlas_io.hpp>

using namespace rpgmapper::model;


TEST(AtlasIO, GetJsonOfAtlas) {

    std::string const  expectedJson{
        "{\"name\":\"New Atlas\",\"regions\":[{\"maps\":[{\"name\":\"New Map 1\"}],\"name\":\"New Region 1\"}]}"
    };

    Atlas atlas;
    auto json = QJsonDocument{atlas.getJsonObject()}.toJson(QJsonDocument::Compact).toStdString();
    EXPECT_EQ(json, expectedJson);
}


TEST(AtlasIO, WriteAtlasToFile) {

    Atlas atlas;
    QFile file{"test.atlas"};

    AtlasIO atlasIO;
    auto result = atlasIO.write(atlas, file);
    EXPECT_TRUE(result.hasSuccess());
    EXPECT_FALSE(atlas.hasChanged());
}


TEST(AtlasIO, ReadAtlasFromFile) {

    Atlas atlas;
    QFile file{"test/data/test.atlas"};

    AtlasIO atlasIO;
    auto result = atlasIO.read(file);
    EXPECT_TRUE(result.hasSuccess());
    EXPECT_TRUE(result.getAtlas()->isValid());
    EXPECT_FALSE(result.getAtlas()->hasChanged());
}
