/*
 * test_file.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


// ------------------------------------------------------------

#include <iostream>
#include <cassert>

// rpgmapper
#include <rpgmapper/file.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// defs

#define DUMMY_TEXT \
"Lorem ipsum dolor sit amet, consetetur sadipscing elitr, \n"\
"sed diam nonumy eirmod tempor invidunt ut labore et dolore \n"\
"magna aliquyam erat, sed diam voluptua.\n"


// ------------------------------------------------------------
// code

int test() {

    File cFileToWrite;

    std::string sText = DUMMY_TEXT;
    QByteArray cData1(sText.c_str(), static_cast<int>(sText.size()));
    cFileToWrite.files().insert(std::make_pair("afolder/afile/dummy.txt", cData1));
    cFileToWrite.save("test_file.zip");

    File cFileToLoad;
    cFileToLoad.load("test_file.zip");
    assert(cFileToLoad.files().size() == 1);
    auto iter = cFileToLoad.files().find("afolder/afile/dummy.txt");
    assert(iter != cFileToLoad.files().end());
    assert((*iter).second.data() == std::string(DUMMY_TEXT));

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
