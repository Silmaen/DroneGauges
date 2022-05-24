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

    double _scale                  = 1.0;
    QGraphicsScene* _scene         = nullptr;///< graphics scene
    const double _originalPixPerAlt= 1.5;
    const double _scale_factor     = 0.4;
    const double scaleSize         = 150;

    const QPointF position= {100, 0};
    QGraphicsSvgItem* _itemBack;///<
    const QPointF backpos= {20, 87.5};
    QGraphicsSvgItem* _itemScale1;///<
    const QPointF scale1Pos= {0, 152.0};
    QGraphicsTextItem* _itemLabel1;///<
    QGraphicsTextItem* _itemLabel2;///<
    QGraphicsTextItem* _itemLabel3;///<
    QGraphicsSvgItem* _itemGround; ///<
    const QPointF groundPos= {0, -87};
    QGraphicsSvgItem* _itemFrame;///<
    const QPointF framePos= {25, 15};
    QGraphicsTextItem* _itemAltitude;///<

    double _altitude        = 0;
    double _verticalVelocity= 0;
};
}// namespace dg::ui::gauge::pfd
