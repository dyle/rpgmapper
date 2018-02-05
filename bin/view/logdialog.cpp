/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// incs

// rpgmapper
#include "logdialog.hpp"
#include "ui_logdialog.h"

using namespace rpgmapper::view;


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent         parent widget instance
 */
LogDialog::LogDialog(QWidget * cParent) : QDialog{cParent} {
    ui = std::make_shared<Ui_logdialog>();
    ui->setupUi(this);
}


/**
 * Clear the items in the dialog.
 */
void LogDialog::clear() {
    ui->lbMessage->setText("");
    ui->edPlainLog->clear();
}


/**
 * Set the log.
 *
 * @param   cLog            the log to display
 */
void LogDialog::setLog(QStringList const & cLog) {
    ui->edPlainLog->clear();
    for (auto & sLogLine : cLog) {
        ui->edPlainLog->insertPlainText(sLogLine);
        ui->edPlainLog->insertPlainText("\n");
    }
}


/**
 * Set a log message.
 *
 * @param   sMessage        the message to show.
 */
void LogDialog::setMessage(QString sMessage) {
    ui->lbMessage->setText(sMessage);
}
