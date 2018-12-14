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
    QColor hoverColor = Qt::red;    /**< Color used to show hovering rectangle. */
    bool selected = false;          /**< selected flag. */
    
    int id = 0;                     /**< the ID of this widget, when used in an array. */

public:
    
    /**
     * Constructor.
     *
     * @param   color       The color to display.
     * @param   id          The id of this widget.
     * @param   parent      The parent QWidget instance.
     */
    explicit ColorWidget(QColor color, int id = 0, QWidget * parent = nullptr);
    
    /**
     * Gets the color this widget displays.
     *
     * @return  the color of this widget.
     */
    QColor getColor() const {
        return color;
    }
    
    /**
     * Gets the color used for drawing the hovering rectangle.
     *
     * @return  the hovering rectangle color.
     */
    QColor getHoverColor() const {
        return hoverColor;
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
     * Sets the color used for the hovering rectangle.
     *
     * @param   color   the color used for the hovering rectangle.
     */
    void setHoveringColor(QColor color);
    
    /**
     * Sets a new selected flag.
     *
     * @param   selected        the new selected flag.
     */
    void setSelected(bool selected);

protected:
    
    /**
     * Mouse double clicked at the widget.
     *
     * @param   event       double click event.
     */
    void mouseDoubleClickEvent(QMouseEvent * event) override;
    
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
     * The user released the mouse over this widget.
     *
     * @param   event       the mouse release event.
     */
    void mouseReleaseEvent(QMouseEvent * event);
    
    /**
     * Draws this widget.
     *
     * @param   event       the paint event involved.
     */
    void paintEvent(QPaintEvent * event) override;

signals:
    
    /**
     * Tells that the color of this widget has changed.
     *
     * @param   id              the id of this widget.
     */
    void colorChanged(int id);
    
    /**
     * Tells that this widget has been selected.
     *
     * @param   id              the id of this widget
     * @param   selected        the selection flag
     */
    void selectedChanged(int id, bool selected);
};


}
}


#endif
