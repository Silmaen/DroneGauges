/**
 * @file Asi.h
 * @author argawaen
 * @date 24/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include <utility>

#include "DisplayElement.h"

namespace dg::ui::gauge::pfd {
/**
 * @brief Class ASI
 */
class ASI : public DisplayElement {
public:
    /**
     * @brief Constructor
     * @param scene The scene where to display
     */
    explicit ASI(std::shared_ptr<QGraphicsScene> scene, const QPointF& position= {0, 0}, const double& internalScale= 1.0):
        DisplayElement(std::move(scene),position,internalScale){}

    /**
     * @brief Initialization of the display
     * @param scale The initial scal of the view
     */
    void init(double scale) override;

    /**
     * @brief Update the view port
     * @param scale The update scale of the view
     */
    void update(double scale) override;

    /**
     * @brief Define the altitude to display
     * @param velocity The altitude to display
     */
    void setVelocity(double velocity);
    void setVfe(double vfe);
    void setVne(double vne);

private:

    const double _originalPixPerSpd= 1.5;
    const double scaleSize         = 120;

    QGraphicsSvgItem* _itemBack  = nullptr;///<
    const QPointF backpos        = {18, 87.5};
    QGraphicsSvgItem* _itemScale1= nullptr;///<
    const QPointF scale1Pos      = {-31, 122};
    const uint8_t nbLabels = 7;
    std::vector<QGraphicsTextItem*> _itemLabels;

    const QPointF itemPos= {0, -15};
    QGraphicsSvgItem* _itemFrame;  ///<
    const QPointF framePos= {44, 15};
    QGraphicsRectItem* _itemVfe;     ///<
    QGraphicsSvgItem* _itemVne;      ///<
    const QPointF _VnePos = {-27,212.5};///<
    QGraphicsTextItem* _itemAirspeed;///<
    const QPointF airSpeedPos= {22, 0};

    QBrush _vfeBrush= {QColor(0xff, 0xff, 0xff), Qt::SolidPattern};///<
    QPen _vfePen    = {_vfeBrush, 1};
    const QPointF _VfePos = {34,175};///<
    const int _VfeWidth = 2;

    double _airspeed= 0.;///<
    double _vfe     = 0.;///<
    double _vne     = 100.;///<
};

}// namespace dg::ui::gauge::pfd
