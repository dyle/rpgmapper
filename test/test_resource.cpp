/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_collection.hpp>
#include <rpgmapper/resource/resource_pointer.hpp>

using namespace rpgmapper::model::resource;


TEST(ResoucrceDB, InsertResource) {

    auto resources = QSharedPointer<ResourceCollection>{new ResourceCollection};

    auto data = QByteArray::fromHex("0102030405060708090a0b0c0d0e0f10");
    auto resource = ResourcePointer{new Resource{"data", data}};
    resources->addResource(resource);

    EXPECT_EQ(resources->getResources().size(), 1);

    auto pair = resources->getResources().find("xxx");
    bool found = (pair != resources->getResources().end());
    EXPECT_FALSE(found);

    pair = resources->getResources().find("data");
    found = (pair != resources->getResources().end());
    EXPECT_TRUE(found);
    EXPECT_EQ((*pair).second->getPath().toStdString(), "data");
    EXPECT_EQ((*pair).second->getHash(), Resource::getHash(data));
    EXPECT_EQ((*pair).second->getData().toHex().toStdString(), "0102030405060708090a0b0c0d0e0f10");
}
