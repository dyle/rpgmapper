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

    QWeakPointer<rpgmapper::model::Map> map;
    QFont axisFont;
    QColor axisColor;
    QColor backgroundColor;
    QImage backgroundImage;
    QString backgroundImageFileName;
    QLabel * backgroundPreviewLabel;

    struct {
        QSharedPointer<rpgmapper::model::NumeralConverter> alphabeticalBigCaps;
        QSharedPointer<rpgmapper::model::NumeralConverter> alphabeticalSmallCaps;
        QSharedPointer<rpgmapper::model::NumeralConverter> numerical;
        QSharedPointer<rpgmapper::model::NumeralConverter> roman;
    } numeralConverters;

public:

    explicit MapPropertiesDialog(QWidget * parent);

    void setMap(rpgmapper::model::MapPointer & cMap);

public slots:

    void evaluate();

private:

    void clearUi();

    void clearUiAxisTab();

    void clearUiBackgroundTab();

    void clearUiDimensionTab();

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
