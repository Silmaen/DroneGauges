/**
 * @file hdg.h
 * @author damien.lachouette 
 * @date 25/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "DisplayElement.h"

namespace dg::ui::gauge::pfd {
/**
 * @brief Class HDG
 */
class HDG: public DisplayElement {
public:
    /**
     * @brief Constructor
     * @param scene The scene where to display
     */
    explicit HDG(std::shared_ptr<QGraphicsScene> scene, const QPointF& position= {0, 0}, const double& internalScale= 1.0):
        DisplayElement(scene,position,internalScale){}

    /**
     * @brief Initialization of the display
     * @param scale the initial scal of the view
     */
    void init(double scale) override;

    /**
     * @brief Update the view port
     * @param scale The update scale of the view
     */
    void update(double scale) override;

    /**
     * @brief Define the altitude to display
     * @param yaw The horizontal look at direction
     */
    void setYaw(double yaw);

private:

    void updateView();

    const double _originalPixPerDeg= 1.0;
    double _heading = 0;

    QGraphicsSvgItem* _itemBack;///<
    const QPointF backPos= {87.5, 7.5};
    QGraphicsSvgItem* _itemScale;///<
    const QPointF scalePos= {92.5, 0};
    QGraphicsSvgItem* _itemFrame;///<
    const QPointF framePos= {37.5, 15};
    QGraphicsTextItem* _itemHeading;///<
    const QPointF headingPos= {2, 0.5};
    QBrush _markerBrush             = {QColor(0xff, 0xff, 0xff), Qt::SolidPattern};///<
    QPen _markerPen                 = {_markerBrush, 0};                           ///<
};

}// namespace dg::ui::gauge::pfd
