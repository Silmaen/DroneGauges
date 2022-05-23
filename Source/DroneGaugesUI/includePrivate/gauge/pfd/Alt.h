/**
 * @file Alt.h
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
 * @brief Class ALT
 */
class ALT {
public:
    explicit ALT(QGraphicsScene* scene);

    void init(double scale);
    void update(double scale);

    void setAltitude(double altitude);
    void setVerticalVelocity(double verticalVelocity);

private:
    void updateAltView();
    void updateVertVelView();

    double _scale                    = 1.0;
    QGraphicsScene* _scene           = nullptr;///< graphics scene
    const double _originalPixPerAlt  = 0.50;
    const double _originalScaleHeight= 300;
    const double _scale_factor       = 0.4;

    QPointF position= {100, 0};
    QGraphicsSvgItem* _itemBack;///<
    QPointF backpos= {20, 87.5};
    QGraphicsSvgItem* _itemScale1;///<
    QPointF scale1Pos= {20, 150};
    QGraphicsSvgItem* _itemScale2;///<
    QPointF scale2Pos= {231, -474.5};
    QGraphicsTextItem* _itemLabel1;///<
    QPointF label1Pos= {253, 50};
    QGraphicsTextItem* _itemLabel2;///<
    QPointF label2Pos= {253, 125};
    QGraphicsTextItem* _itemLabel3;///<
    QPointF label3Pos= {253, 200};
    QGraphicsSvgItem* _itemGround;///<
    QPointF groundPos= {0, -87.5};
    QGraphicsSvgItem* _itemFrame;///<
    QPointF framePos= {25, 15};
    QGraphicsTextItem* _itemAltitude;///<
    QPointF altitudePos= {254, 126};
    QGraphicsTextItem* _itemPressure;///<
    QPointF pressurePos= {254, 225};

    double _altitude        = 0;
    double _verticalVelocity= 0;
};
}// namespace dg::ui::gauge::pfd
