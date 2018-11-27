/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <iostream>

#include <boost/program_options.hpp>

#include <QApplication>
#include <QPixmapCache>

#include <rpgmapper/session.hpp>

#include "mainwindow.hpp"
#include "startupdialog.hpp"

using namespace rpgmapper::model;


#define PROGRAM_DESCRIPTION "\
This is a nifty tool to draw RPG dungeon maps.\n\
\n\
Copyright (C) 2018 Oliver Maurhart, <dyle71@gmail.com>\n\
Licenseed under the GNU General Public License 3\n\
See: http://www.gnu.org/licenses/ for details."


/**
 * Parses the command line arguments.
 *
 * @param   programOptions      this will hold the parsed result.
 * @param   argc                argc as passed on by main().
 * @param   argv                argv as passed on by main().
 * @return  return true, if the command line arguments have been parsed successfully.
 */
bool parseCommandLine(boost::program_options::variables_map & programOptions, int argc, char ** argv);


int main(int argc, char ** argv) {

    boost::program_options::variables_map programOptions;
    if (!parseCommandLine(programOptions, argc, argv)) {
        return 0;
    }

    if (programOptions.count("ATLAS-FILE") == 1) {
        // TODO: remove this once we can load an atlas file from the cmd line
        std::cerr << "TO BE IMPLEMENTED: LOAD ATLAS FROM CMD-LINE: "
                  << programOptions["ATLAS-FILE"].as<std::string>()
                  << std::endl;
    }
    
    QApplication application{argc, argv};
    QApplication::setOrganizationName("Oliver Maurhart <dyle71@gmail.com>");
    QApplication::setOrganizationDomain("");
    QApplication::setApplicationName("RPGMapper");
    QApplication::setApplicationVersion(VERSION);

    QPixmapCache::insert("atlas", QPixmap(":/icons/gfx/atlas.png"));
    QPixmapCache::insert("region", QPixmap(":/icons/gfx/region.png"));
    QPixmapCache::insert("map", QPixmap(":/icons/gfx/map.png"));
    
    Session::setCurrentSession(Session::init());
    
    rpgmapper::view::MainWindow mainWindow;
    rpgmapper::view::StartupDialog startupDialog{&mainWindow};
    startupDialog.show();
    
    application.setQuitOnLastWindowClosed(true);
    return application.exec();
}


bool parseCommandLine(boost::program_options::variables_map & programOptions, int argc, char ** argv) {

    std::string applicationHeader = std::string{"rpgmapper - Dyle's RPGMapper V"} + VERSION;
    std::string description = std::string{PROGRAM_DESCRIPTION};
    std::string synopsis = std::string{"Usage: "} + argv[0] + " [OPTIONS] [ATLAS-FILE]";

    boost::program_options::options_description options{
            applicationHeader + description + "\n\n" + synopsis + "\n\nAllowed Options"};
    options.add_options()("help,h", "this page");
    options.add_options()("version,v", "print version string");

    boost::program_options::options_description arguments{"Arguments"};
    arguments.add_options()("ATLAS-FILE", "atlas file to open");
    boost::program_options::positional_options_description positionalArgumentDescriptions;
    positionalArgumentDescriptions.add("ATLAS-FILE", 1);

    boost::program_options::options_description commandLineOptions{"Command Line"};
    commandLineOptions.add(options);
    commandLineOptions.add(arguments);

    try {
        boost::program_options::command_line_parser parser{argc, reinterpret_cast<char const * const *>(argv)};
        boost::program_options::store(
                parser.options(commandLineOptions).positional(positionalArgumentDescriptions).run(),
                programOptions);
        boost::program_options::notify(programOptions);
    }
    catch (std::exception & exception) {
        std::cerr << "error parsing command line: " <<  exception.what()
                  << "\ntype '--help' for help"
                  << std::endl;
        std::exit(1);
    }

    if (programOptions.count("help")) {
        std::cout << options << std::endl;
        std::cout << "ATLAS-FILE: " << arguments.find("ATLAS-FILE", false).description()
                  << "\n"
                  << std::endl;
        return false;
    }

    if (programOptions.count("version")) {
        std::cout << applicationHeader << std::endl;
        return false;
    }

    return true;
}
