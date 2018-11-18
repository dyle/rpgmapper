/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/exception/invalid_mapname.hpp>

using namespace rpgmapper::model;


TEST(MapTest, CreateMapIsValid) {
    
    Map map{"foo"};
    ASSERT_TRUE(map.isValid());
}


TEST(MapTest, CreateInvalidMapIsNotValid) {
    EXPECT_FALSE(InvalidMap{}.isValid());
}


TEST(MapTest, MapGetAndSetName) {
    
    Map map{"foo"};
    EXPECT_EQ(map.getName().toStdString(), "foo");
    map.setName("bar");
    EXPECT_EQ(map.getName().toStdString(), "bar");
}


TEST(MapTest, GetAxisLayer) {
    
    Map map{"foo"};
    auto layer = map.getLayers().getAxisLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetBackgroundLayer) {
    
    Map map{"foo"};
    auto layer = map.getLayers().getBackgroundLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetBaseLayers) {
    
    Map map{"foo"};
    auto layers = map.getLayers().getBaseLayers();
    EXPECT_GT(layers.size(), 0);
    for (auto const & layer : layers) {
        EXPECT_TRUE(layer->isValid());
    }
}


TEST(MapTest, GetGridLayer) {
    
    Map map{"foo"};
    auto layer = map.getLayers().getGridLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, GetTileLayers) {
    
    Map map{"foo"};
    auto layers = map.getLayers().getTileLayers();
    EXPECT_GT(layers.size(), 0);
    for (auto const & layer : layers) {
        EXPECT_TRUE(layer->isValid());
    }
}


TEST(MapTest, GetTextLayer) {
    
    Map map{"foo"};
    auto layer = map.getLayers().getTextLayer();
    EXPECT_TRUE(layer->isValid());
}


TEST(MapTest, ValidNames) {

    EXPECT_TRUE(MapNameValidator::isValid("Middleearth"));
    EXPECT_TRUE(MapNameValidator::isValid("A land far far away"));
    EXPECT_TRUE(MapNameValidator::isValid("Asgard!"));
    EXPECT_FALSE(MapNameValidator::isValid("This is: invalid"));
    EXPECT_FALSE(MapNameValidator::isValid("This is also \\ invalid"));
    EXPECT_FALSE(MapNameValidator::isValid("This is invalid * as well"));
    EXPECT_FALSE(MapNameValidator::isValid("And this ? is also invalid"));
}
