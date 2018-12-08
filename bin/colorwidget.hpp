/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_COLORWIDGET_HPP
#define RPGMAPPER_VIEW_COLORWIDGET_HPP

#include <QColor>
#include <QWidget>


namespace rpgmapper {
namespace view {


/**
 * A colro widget is a small cell displaying a color and able to get selected.
 */
class ColorWidget : public QWidget {

    Q_OBJECT
    
    QColor color;                   /**< color to show. */
    bool selected = false;          /**< selected flag. */

public:
    
    /**
     * Constructor.
     *
     * @param   color       The color to display.
     * @param   parent      The parent QWidget instance.
     */
    explicit ColorWidget(QColor color, QWidget * parent = nullptr);
    
    /**
     * Gets the color this widget displays.
     *
     * @return  the color of this widget.
     */
    QColor getColor() const {
        return color;
    }
    
    /**
     * Checks if this widget is selected.
     *
     * @return  returns selected flag of this widget.
     */
    bool isSelected() const {
        return selected;
    }

    /**
     * Sets a new color to display.
     *
     * @param   color       the new color to display.
     */
    void setColor(QColor color);
    
    /**
     * Sets a new selected flag.
     *
     * @param   selected        the new selected flag.
     */
    void setSelected(bool selected);

protected:
    
    /**
     * Mouse enters the widget.
     *
     * @param   event       the enter event.
     */
    void enterEvent(QEvent * event) override;
    
    /**
     * The mosue leaves the widget.
     * @param   event       the leave event.
     */
    void leaveEvent(QEvent * event) override;
    
    /**
     * Draws this widget.
     *
     * @param   event       the paint event involved.
     */
    void paintEvent(QPaintEvent * event) override;

signals:
    
    /**
     * Tells that this widget has been selected.
     */
    void selectedChanged();
};


}
}


#endif
