/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <QFile>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/atlas_writer.hpp>

using namespace rpgmapper::model;


TEST(AtlasWriter, GetJsonOfAtlas) {

    std::string const  expectedJson{
        "{\"name\":\"New Atlas\",\"regions\":[{\"maps\":[{\"name\":\"New Map 1\"}],\"name\":\"New Region 1\"}]}"
    };

    Atlas atlas;
    auto json = QJsonDocument{atlas.getJsonObject()}.toJson(QJsonDocument::Compact).toStdString();
    EXPECT_EQ(json, expectedJson);
}


TEST(AtlasWriter, WriteAtlasJsonToFile) {

    Atlas atlas;
    QFile file{"test-write.atlas"};

    AtlasWriter atlasWriter;
    auto result = atlasWriter.write(atlas, file);
    EXPECT_TRUE(result.success);
    EXPECT_FALSE(atlas.hasChanged());
}
