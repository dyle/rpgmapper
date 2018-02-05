/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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
 * A log dialog displays a plain text of logs (some errors) to the user.
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
