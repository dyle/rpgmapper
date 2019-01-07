/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_LOGDIALOG_HPP
#define RPGMAPPER_VIEW_LOGDIALOG_HPP

#include <memory>

#include <QDialog>


// fwd
class Ui_logDialog;


namespace rpgmapper::view {


/**
 * The LogDialog displays a list of log entries to the user.
 *
 * The list of log entries is also headed by some message to clarify what has been logged.
 */
class LogDialog : public QDialog {

    Q_OBJECT

    std::shared_ptr<Ui_logDialog> ui;               /**< The User Interface as created by the uic. */

public:

    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    LogDialog(QWidget * parent);

    /**
     * Clears all log entries.
     */
    void clear();

    /**
     * Sets a new list of entries.
     *
     * @param   log         the log entries to display.
     */
    void setLog(QStringList const & log);

    /**
     * Sets the heading message of the log entries.
     *
     * @param   message     the log header summarizing the activities displayed.
     */
    void setMessage(QString message);
};


}


#endif
