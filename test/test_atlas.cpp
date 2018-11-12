/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <tuple>

#include <gtest/gtest.h>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


TEST(AtlasTest, CreateAtlasIsValid) {
    
    Session::setCurrentSession(Session::init());
    auto atlas = Session::getCurrentSession()->getAtlas();
    
    ASSERT_TRUE(atlas->isValid());
}


TEST(AtlasTest, AtlasNameSet) {
    
    Session::setCurrentSession(Session::init());
    auto atlas = Session::getCurrentSession()->getAtlas();

    atlas->setName("foo");
    EXPECT_EQ(atlas->getName().toStdString(), "foo");
}
