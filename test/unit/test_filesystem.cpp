/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <QDir>

#include <rpgmapper/filesystem.hpp>

using namespace rpgmapper::model;


TEST(FileSystem, GetApplicationDataSystemFolder) {
    auto dataFolder = rpgmapper::model::getApplicationDataSystemPath();
    EXPECT_FALSE(dataFolder.absolutePath().isEmpty());
}

TEST(FileSystem, GetApplicationDataUserFolder) {
    auto dataFolder = rpgmapper::model::getApplicationDataUserPath();
    EXPECT_FALSE(dataFolder.absolutePath().isEmpty());
}
