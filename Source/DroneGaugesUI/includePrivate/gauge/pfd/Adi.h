/**
 * @file Adi.h
 * @author damien.lachouette 
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <QGraphicsScene>
#include <QGraphicsSvgItem>

namespace dg::ui::gauge::pfd {

/**
 * @brief Class ADI
 */
class ADI {
public:
    explicit ADI(QGraphicsScene *scene);

    void init(double scale);
    void update(double scale);

    void setRoll(double roll);
    void serPitch(double pitch);
private:

    void reset();
    void updateBackView();
    void updateLadderView();
    void updateRollView();

    double _scale= 1.0;
    double _scaleLow= 0.6;

    const int _originalHeight      = 120;
    const int _originalWidth       = 120;
    const double _originalPixPerDeg= 3;

    QGraphicsScene *_scene=nullptr;///< graphics scene
    QGraphicsSvgItem  *_itemBack=nullptr;       ///< background
    const double _deltaBack_max= 52.5;
    const double _deltaBack_min= -_deltaBack_max;
    QPointF _originalBackPos   = {210, 210};
    QGraphicsSvgItem  *_itemLadd=nullptr;       ///< pitch ladder
    QPointF _originalLaddPos   = {40, 300};
    QGraphicsSvgItem  *_itemRoll=nullptr;       ///< roll mask
    QPointF _originalRollPos   = {105, 250};
    QGraphicsSvgItem  *_itemMask=nullptr;       ///< adi mask
    QPointF _originalMaskPos   = {150, 125};
    double _roll=0;                       ///< [deg]
    double _pitch=0;                      ///< [deg]


};

}// namespace dg::ui::gauge::pfd
