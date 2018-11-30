/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/resource.hpp>
#include <rpgmapper/resource_collection.hpp>

using namespace rpgmapper::model;


TEST(ResoucrceDB, InsertResource) {

    auto resources = QSharedPointer<ResourceCollection>{new ResourceCollection};

    auto data = QByteArray::fromHex("0102030405060708090a0b0c0d0e0f10");
    resources->addResource("data", data);

    EXPECT_EQ(resources->getResources().size(), 1);

    auto pair = resources->getResources().find("data");
    bool found = (pair != resources->getResources().end());
    EXPECT_FALSE(found);

    pair = resources->getResources().find(Resource::getHash(data));
    found = (pair != resources->getResources().end());
    EXPECT_TRUE(found);
    EXPECT_EQ((*pair).second->getName().toStdString(), "data");
    EXPECT_EQ((*pair).second->getHash(), Resource::getHash(data));
    EXPECT_EQ((*pair).second->getData().toHex().toStdString(), "0102030405060708090a0b0c0d0e0f10");
}
