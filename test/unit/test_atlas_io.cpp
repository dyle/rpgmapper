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
        R"raw({"name":"New Atlas","regions":[{"maps":[{"name":"New Map 1"}],"name":"New Region 1"}]})raw"
    };
    AtlasPointer atlas{new Atlas};
    auto json = QJsonDocument{atlas->getJsonObject()}.toJson(QJsonDocument::Compact).toStdString();

    EXPECT_EQ(json, expectedJson);
}


TEST(AtlasIO, WriteAtlasToFile) {

    AtlasPointer atlas{new Atlas};
    QFile file{"test.atlas"};
    AtlasIO atlasIO;
    auto result = atlasIO.write(atlas, file);

    EXPECT_TRUE(result.hasSuccess());
    EXPECT_FALSE(atlas->isModified());
}


TEST(AtlasIO, WriteAtlasToInvalidFile) {

    AtlasPointer atlas{new Atlas};
    QFile file{"/dev/false"};
    AtlasIO atlasIO;
    auto result = atlasIO.write(atlas, file);

    EXPECT_FALSE(result.hasSuccess());
}


TEST(AtlasIO, ReadAtlasFromFile) {

    QFile file{"test/unit/data/test.atlas"};
    AtlasIO atlasIO;
    auto result = atlasIO.read(file);

    EXPECT_TRUE(result.hasSuccess());
    EXPECT_TRUE(result.getAtlas()->isValid());
    EXPECT_FALSE(result.getAtlas()->isModified());
}


TEST(AtlasIO, ReadAtlasFromInvalidFile) {

    QFile file{"/dev/false"};
    AtlasIO atlasIO;
    auto result = atlasIO.read(file);

    EXPECT_FALSE(result.hasSuccess());
}
