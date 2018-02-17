/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_MAPPROPERTIESDIALOG_HPP
#define RPGMAPPER_VIEW_MAPPROPERTIESDIALOG_HPP


#include <memory>

#include <QDialog>
#include <QFile>
#include <QLabel>

#include <rpgmapper/map.hpp>
#include <rpgmapper/numerals.hpp>


class Ui_mapPropertiesDialog;


namespace rpgmapper {
namespace view {


class MapPropertiesDialog : public QDialog {

    Q_OBJECT

    std::shared_ptr<Ui_mapPropertiesDialog> ui;
    rpgmapper::model::MapPointer map;
    QFont axisFont;
    QColor axisColor;
    QColor backgroundColor;
    QImage backgroundImage;
    QString backgroundImageFileName;
    QLabel * backgroundPreviewLabel;

    struct {
        QSharedPointer<NumeralConverter> alphabeticalBigCaps;
        QSharedPointer<NumeralConverter> alphabeticalSmallCaps;
        QSharedPointer<NumeralConverter> numerical;
        QSharedPointer<NumeralConverter> roman;
    } numeralConverters;

public:

    explicit MapPropertiesDialog(QWidget * parent);

public slots:

    void evaluate();

    void setMap(MapPointer & cMap);

private:

    void initNumeralConverters();

private slots:

    void heightChanged(int value);

    void selectAxisColor();

    void selectAxisFont();

    void selectBackgroundColor();

    void selectBackgroundImage();

    void setBackgroundImageRenderMode();

    void showSampleXAxis();

    void showSampleYAxis();

    void widthChanged(int nValue);
};


}
}


#endif
