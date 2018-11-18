/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/layer/layer.hpp>
#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


TEST(LayerTest, BackgroundLayerHasColor) {
    
    Map map{"foo"};
    auto const & layer = map.getLayers().getBackgroundLayer();
    auto pair = layer->getAttributes().find("color");
    EXPECT_NE(pair, layer->getAttributes().end());
}


TEST(LayerTest, BaseLayerInvalidField) {
    
    Map map{"foo"};
    
    auto & layers = map.getLayers().getBaseLayers();
    ASSERT_GE(layers.size(), 1);

    auto field = layers.front()->getField(10, 10);

    EXPECT_FALSE(field->isValid());
}


TEST(LayerTest, BaseLayerAddFields) {
    
    Map map{"foo"};
    
    auto & layers = map.getLayers().getBaseLayers();
    ASSERT_GE(layers.size(), 1);

    int index = Field::getIndex(10, 10);
    layers.front()->addField(Field{10, 10});

    auto field1 = layers.front()->getField(index);
    auto field2 = layers.front()->getField(10, 10);
    auto field3 = layers.front()->getField(QPoint{10, 10});
    auto field4 = layers.front()->getField(Field::getIndex(10, 10));
    auto field5 = layers.front()->getField(Field::getIndex(QPoint{10, 10}));

    EXPECT_TRUE(field1->isValid());
    EXPECT_TRUE(field2->isValid());
    EXPECT_TRUE(field3->isValid());
    EXPECT_TRUE(field4->isValid());
    EXPECT_TRUE(field5->isValid());
    EXPECT_EQ(field1->getIndex(), index);
    EXPECT_EQ(field2->getIndex(), index);
    EXPECT_EQ(field3->getIndex(), index);
    EXPECT_EQ(field4->getIndex(), index);
    EXPECT_EQ(field5->getIndex(), index);
}


TEST(LayerTest, TileLayerInvalidField) {
    
    Map map{"foo"};
    
    auto & layers = map.getLayers().getTileLayers();
    ASSERT_GE(layers.size(), 1);

    auto field = layers.front()->getField(10, 10);

    EXPECT_FALSE(field->isValid());
}


TEST(LayerTest, TileLayerAddFields) {
    
    Map map{"foo"};
    
    auto & layers = map.getLayers().getTileLayers();
    ASSERT_GE(layers.size(), 1);

    int index = Field::getIndex(10, 10);
    layers.front()->addField(Field{10, 10});

    auto field1 = layers.front()->getField(index);
    auto field2 = layers.front()->getField(10, 10);
    auto field3 = layers.front()->getField(QPoint{10, 10});
    auto field4 = layers.front()->getField(Field::getIndex(10, 10));
    auto field5 = layers.front()->getField(Field::getIndex(QPoint{10, 10}));

    EXPECT_TRUE(field1->isValid());
    EXPECT_TRUE(field2->isValid());
    EXPECT_TRUE(field3->isValid());
    EXPECT_TRUE(field4->isValid());
    EXPECT_TRUE(field5->isValid());
    EXPECT_EQ(field1->getIndex(), index);
    EXPECT_EQ(field2->getIndex(), index);
    EXPECT_EQ(field3->getIndex(), index);
    EXPECT_EQ(field4->getIndex(), index);
    EXPECT_EQ(field5->getIndex(), index);
}
