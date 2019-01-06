/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <tuple>

#include <gtest/gtest.h>

#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


TEST(AtlasTest, CreateAtlasIsValid) {
    
    Atlas atlas;
    ASSERT_TRUE(atlas.isValid());
}


TEST(AtlasTest, AtlasNameSet) {
    
    Atlas atlas{"foo"};
    EXPECT_EQ(atlas.getName().toStdString(), "foo");
    
    atlas.setName("bar");
    EXPECT_EQ(atlas.getName().toStdString(), "bar");
}
