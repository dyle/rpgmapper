/*
 * logdialog.cpp
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



