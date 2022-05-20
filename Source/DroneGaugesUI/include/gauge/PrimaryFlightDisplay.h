/**
 * @file PrimaryFlightDisplay.h
 * @author Silmean
 * @date 20/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>
#include <QGraphicsView>

namespace dg::ui::gauge {

/**
 * @brief Base Object for flight data display
 */
class PrimaryFlightDisplay: public QGraphicsView {
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent Parent Widget
     */
    explicit PrimaryFlightDisplay(QWidget* parent= nullptr);
    /**
     * @brief Destructor
     */
    ~PrimaryFlightDisplay();

    /** Reinitiates widget. */
    void reinit();

    /** Refreshes (redraws) widget. */
    void redraw();
public slots:
    /**
     * @brief Defines internal pitch.
     */
    void setPitch(int);
    /**
     * @brief Defines the internal yaw.
     */
    void setYaw(int);
    /**
     * @brief Defines the internal roll.
     */
    void setRoll(int);

protected:
    /** */
    void resizeEvent(QResizeEvent* event);

private:
    void init();
    void reset();
    void updateView();

    void updateBackView();
    void updateLadderView();
    void updateRollView();

    double _scaleX  = 1.0;///<
    double _scaleY  = 1.0;///<
    double _scaleMax= 1.0;///<
    double _scaleLow= 0.6;///<

    const int _originalHeight      = 200;///< [px]
    const int _originalWidth       = 150;///< [px]
    const double _originalPixPerDeg= 6.0;

    QGraphicsScene* _scene= nullptr;///< graphics scene

    ///  background
    QGraphicsSvgItem* _itemBack= nullptr;
    const double _deltaBack_max= 100;            ///< [px] max pitch ladder background deflection
    const double _deltaBack_min= -_deltaBack_max;///< [px] min pitch ladder background deflection
    double _backDeltaX_old     = 0;
    double _backDeltaY_old     = 0;
    QPointF _originalBackPos   = {105, 210};///<
    /// ladder
    QGraphicsSvgItem* _itemLadd= nullptr;
    QPointF _originalLaddPos   = {40, 300};
    double _laddDeltaX_old     = 0;
    double _laddDeltaY_old     = 0;

    /// roll
    QGraphicsSvgItem  *_itemRoll = nullptr;
    QPointF _originalRollPos   = {105, 105};///<

    /// Mask
    QGraphicsSvgItem  *_itemMask = nullptr;
    QPointF _originalMaskPos= {150, 125};

    double _roll = 0;///< [deg]
    double _pitch= 0;///< [deg]
};

}// namespace dg::ui::gauge