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
#include <QFileInfo>
#include <QLabel>
#include <QRadioButton>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/numerals.hpp>
#include <rpgmapper/command/composite_command.hpp>


class Ui_mapPropertiesDialog;


namespace rpgmapper {
namespace view {


class MapPropertiesDialog : public QDialog {

    Q_OBJECT

    std::shared_ptr<Ui_mapPropertiesDialog> ui;

    QWeakPointer<rpgmapper::model::Atlas> atlas;
    QWeakPointer<rpgmapper::model::Map> map;

    std::map<QString, QImage> backgroundImages;
    QLabel * backgroundPreviewLabel;

    struct {
        QSharedPointer<rpgmapper::model::NumeralConverter> alphabeticalBigCaps;
        QSharedPointer<rpgmapper::model::NumeralConverter> alphabeticalSmallCaps;
        QSharedPointer<rpgmapper::model::NumeralConverter> numerical;
        QSharedPointer<rpgmapper::model::NumeralConverter> roman;
    } numeralConverters;

    std::list<QRadioButton *> xAxisNumeralButtons;
    std::list<QRadioButton *> yAxisNumeralButtons;

public:

    explicit MapPropertiesDialog(QWidget * parent);

    void setMap(rpgmapper::model::AtlasPointer & atlas, rpgmapper::model::MapPointer & map);

public slots:

    void evaluate();

private:

    void addBackgroundImageFromFile(QFileInfo const & fileInfo);

    void applyAxisValuesToMap(rpgmapper::model::command::CompositeCommand * & commands);

    void applyDimensionValuesToMap(rpgmapper::model::command::CompositeCommand * & commands);

    void applyValuesToMap();

    void collectBackgroundImages();

    void collectBackgroundImagesFromSystem();

    void collectBackgroundImagesFromUser();

    void collectBackgroundImagesInPath(QDir const & path);

    QString getSelectedXAxisNumeral() const;

    QString getSelectedYAxisNumeral() const;

    void initNumeralConverters();

    bool isUserInputValid();

    void setAxisUiFromMap();

    void setXAxisUiFromMap();

    void setYAxisUiFromMap();

    void setBackgroundUiFromMap();

    void setDimensionUiFromMap();

private slots:

    void clickedOk();

    void heightChanged(int value);

    void selectAxisColor();

    void selectAxisFont();

    void selectBackgroundColor();

    void selectBackgroundImage();

    void setBackgroundImageRenderMode();

    void selectGridColor();

    void showSampleXAxis();

    void showSampleYAxis();

    void widthChanged(int nValue);
};


}
}


#endif
