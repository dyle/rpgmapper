/*
 * main.cpp
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


// ------------------------------------------------------------
// incs

#include <iostream>

#include <boost/program_options.hpp>

// Qt
#include <QApplication>
#include <QPixmapCache>

// rpgmapper
#include "view/mainwindow.hpp"


// ------------------------------------------------------------
// defs

#define PROGRAM_DESCRIPTION "\
This is a nifty tool to draw RPG dungeon maps.\n\
\n\
Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>\n\
Licenseed under the GNU General Public License 3\n\
See: http://www.gnu.org/licenses/ for details."


// ------------------------------------------------------------
// decl


/**
 * Parses the command line and returns true to proceed.
 *
 * @param   cVariableMap        receives parsed options and arguments
 * @param   argc                number of arguments (as for main())
 * @param   argv                vector of arguments (as for main())
 * @return  true, if we should proceed and show the main window
 */
bool parseCommandLine(boost::program_options::variables_map & cVariableMap, int argc, char ** argv);


// ------------------------------------------------------------
// code


/**
 * start
 *
 * @param   argc        as usual
 * @param   argv        as usual
 * @return  as usual
 */
int main(int argc, char ** argv) {

    boost::program_options::variables_map cVariableMap;
    if (!parseCommandLine(cVariableMap, argc, argv)) {
        return 0;
    }

    if (cVariableMap.count("ATLAS-FILE") == 1) {
        // TODO: remove this once we can load an atlas file from the cmd line
        std::cerr << "TO BE IMPLEMENTED: LOAD ATLAS FROM CMD-LINE: "
                  << cVariableMap["ATLAS-FILE"].as<std::string>()
                  << std::endl;
    }

    QApplication cApplication{argc, argv};
    cApplication.setOrganizationName("Oliver Maurhart <dyle71@gmail.com>");
    cApplication.setOrganizationDomain("");
    cApplication.setApplicationName("RPGMapper");
    cApplication.setApplicationVersion(VERSION);

    QPixmapCache::insert("atlas", QPixmap(":/icons/gfx/atlas.png"));
    QPixmapCache::insert("region", QPixmap(":/icons/gfx/region.png"));
    QPixmapCache::insert("map", QPixmap(":/icons/gfx/map.png"));

    rpgmapper::view::MainWindow cMainWindow;
    cMainWindow.show();

    return cApplication.exec();
}


/**
 * Parses the command line and returns true to proceed.
 *
 * @param   cVariableMap        receives parsed options and arguments
 * @param   argc                number of arguments (as for main())
 * @param   argv                vector of arguments (as for main())
 * @return  true, if we should proceed and show the main window
 */
bool parseCommandLine(boost::program_options::variables_map & cVariableMap, int argc, char ** argv) {

    // create the command line header
    std::string sApplication = std::string{"rpgmapper - Dyle's RPGMapper V"} + VERSION;
    std::string sDescription = std::string{PROGRAM_DESCRIPTION};
    std::string sSynopsis = std::string{"Usage: "} + argv[0] + " [OPTIONS] [ATLAS-FILE]";

    // define program options
    boost::program_options::options_description cOptions{
            sApplication + sDescription + "\n\n" + sSynopsis + "\n\nAllowed Options"};
    cOptions.add_options()("help,h", "this page");
    cOptions.add_options()("version,v", "print version string");

    // final arguments
    boost::program_options::options_description cArgs{"Arguments"};
    cArgs.add_options()("ATLAS-FILE", "atlas file to open");
    boost::program_options::positional_options_description cPositionalDescription;
    cPositionalDescription.add("ATLAS-FILE", 1);

    // construct overall options
    boost::program_options::options_description cCmdLineOptions{"Command Line"};
    cCmdLineOptions.add(cOptions);
    cCmdLineOptions.add(cArgs);

    try {
        boost::program_options::command_line_parser cParser{argc, reinterpret_cast<char const * const *>(argv)};
        boost::program_options::store(
                cParser.options(cCmdLineOptions).positional(cPositionalDescription).run(),
                cVariableMap);
        boost::program_options::notify(cVariableMap);
    }
    catch (std::exception & cException) {
        std::cerr << "error parsing command line: " <<  cException.what()
                  << "\ntype '--help' for help"
                  << std::endl;
        std::exit(1);
    }

    if (cVariableMap.count("help")) {
        std::cout << cOptions << std::endl;
        std::cout << "ATLAS-FILE: " << cArgs.find("ATLAS-FILE", false).description()
                  << "\n"
                  << std::endl;
        return false;
    }

    if (cVariableMap.count("version")) {
        std::cout << sApplication << std::endl;
        return false;
    }

    return true;
}
