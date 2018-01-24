/*
 * logdialog.hpp
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


#ifndef VIEW_LOGDIALOG_HPP
#define VIEW_LOGDIALOG_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QDialog>


// ------------------------------------------------------------
// decl


// fwd
class Ui_logdialog;


namespace rpgmapper {
namespace view {


/**
 * the rpgmapper main window
 */
class LogDialog : public QDialog {


Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent         parent widget instance
     */
    LogDialog(QWidget * cParent);


    /**
     * Clear the items in the dialog.
     */
    void clear();


    /**
     * Set the log.
     *
     * @param   cLog            the log to display
     */
    void setLog(QStringList const & cLog);


    /**
     * Set a log message.
     *
     * @param   sMessage        the message to show.
     */
    void setMessage(QString sMessage);


private:


    std::shared_ptr<Ui_logdialog> ui;       /**< User interface. */

};


}
}


#endif
