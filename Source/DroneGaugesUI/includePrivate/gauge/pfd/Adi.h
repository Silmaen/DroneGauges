/**
 * @file Adi.h
 * @author damien.lachouette 
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "DisplayElement.h"

namespace dg::ui::gauge::pfd {

/**
 * @brief Class ADI
 */
class ADI : public DisplayElement {
public:
    explicit ADI(std::shared_ptr<QGraphicsScene> scene, const QPointF& position= {0, 0}, const double& internalScale= 1.0):
        DisplayElement(scene,position,internalScale){}

    void init(double scale) override;
    void update(double scale) override;

    void setRoll(double roll);
    void setPitch(double pitch);
private:

    void updateBackView();
    void updateLadderView();
    void updateRollView();

    double _scaleLow= 0.6;

    const double _originalPixPerDeg= 3;

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
