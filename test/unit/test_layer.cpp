/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <rpgmapper/layer.hpp>
#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


TEST(LayerTest, BackgroundLayerHasColor) {

    Map map{"foo"};
    auto layer = map.getBackgroundLayer();

    auto iter = layer->attributes.find("color");


    ASSERT_TRUE(map.isValid());
}
