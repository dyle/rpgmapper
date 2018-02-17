/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "logdialog.hpp"
#include "ui_logdialog.h"

using namespace rpgmapper::view;


LogDialog::LogDialog(QWidget * parent) : QDialog{parent} {
    ui = std::make_shared<Ui_logDialog>();
    ui->setupUi(this);
}


void LogDialog::clear() {
    ui->messageLabel->setText("");
    ui->logEdit->clear();
}


void LogDialog::setLog(QStringList const & log) {
    ui->logEdit->clear();
    for (auto & line : log) {
        ui->logEdit->insertPlainText(line + "\n");
    }
}


void LogDialog::setMessage(QString message) {
    ui->messageLabel->setText(message);
}
