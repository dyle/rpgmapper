/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_LOGDIALOG_HPP
#define RPGMAPPER_VIEW_LOGDIALOG_HPP


#include <memory>

#include <QDialog>


class Ui_logDialog;


namespace rpgmapper {
namespace view {


class LogDialog : public QDialog {

    Q_OBJECT

    std::shared_ptr<Ui_logDialog> ui;

public:

    LogDialog(QWidget * parent);

    void clear();

    void setLog(QStringList const & log);

    void setMessage(QString message);

};


}
}


#endif
