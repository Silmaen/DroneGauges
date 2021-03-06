/**
 * @file Alt.h
 * @author damien.lachouette 
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "DisplayElement.h"

namespace dg::ui::gauge::pfd {
/**
 * @brief Class ALT
 */
class ALT : public DisplayElement {
public:
    /**
     * @brief Constructor
     * @param scene The scene where to display
     */
    explicit ALT(std::shared_ptr<QGraphicsScene> scene, const QPointF& position= {0, 0}, const double& internalScale= 1.0):
        DisplayElement(std::move(scene),position,internalScale){}


    /**
     * @brief Initialization of the display
     * @param scale the initial scal of the view
     */
    void init(double scale)override;

    /**
     * @brief Update the view port
     * @param scale The update scale of the view
     */
    void update(double scale)override;

    /**
     * @brief Define the altitude to display
     * @param altitude The altitude to display
     */
    void setAltitude(double altitude);
    /**
     * @brief Define the vertical velocity to display
     * @param verticalVelocity The displayed vertical velocity
     */
    void setVerticalVelocity(double verticalVelocity);

private:
    /**
     * @brief update the Altitude view
     */
    void updateAltView();

    /**
     * @brief Update the vertical velocity view
     */
    void updateVertVelView();

    const double _originalPixPerAlt= 1.5;
    const double scaleSize         = 150;

    QGraphicsSvgItem* _itemBack;///<
    const QPointF backpos= {20, 87.5};
    QGraphicsSvgItem* _itemScale1;///<
    const QPointF scale1Pos= {0, 152.0};
    const uint8_t nbLabels = 3;
    std::vector<QGraphicsTextItem*> _itemLabels;
    const QPointF itemPos= {12, 0.0};
    QGraphicsSvgItem* _itemGround; ///<
    const QPointF groundPos= {0, -87};
    QGraphicsSvgItem* _itemFrame;///<
    const QPointF framePos= {25, 15};
    QGraphicsTextItem* _itemAltitude;///<
    QGraphicsSvgItem* _itemScale;    ///< climb rate scale
    const QPointF scalePos   = {9.5, 75};
    const QPointF scaleOffset= {40, 0};
    QGraphicsRectItem* _itemMarker;///<
    const QPointF _originalMarkerPos= {10, 75};
    const int _originalMarkerWidth  = 4;
    const double _originalPixPerSpd1= 30;
    const double _originalPixPerSpd2= 20;
    const double _originalPixPerSpd4= 5;
    QBrush _markerBrush             = {QColor(0xff, 0xff, 0xff), Qt::SolidPattern};///<
    QPen _markerPen                 = {_markerBrush, 0};                           ///<

    double _altitude        = 0;
    double _verticalVelocity= 0;
};
}// namespace dg::ui::gauge::pfd
