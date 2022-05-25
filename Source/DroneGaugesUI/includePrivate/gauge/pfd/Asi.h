/**
 * @file Asi.h
 * @author argawaen
 * @date 24/05/2022
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
class ASI {
public:
    /**
     * @brief Constructor
     * @param scene The scene where to display
     */
    explicit ASI(QGraphicsScene* scene);

    /**
     * @brief Initialization of the display
     * @param scale the initial scal of the view
     */
    void init(double scale);

    /**
     * @brief Update the view port
     * @param scale The update scale of the view
     */
    void update(double scale);

    /**
     * @brief Define the altitude to display
     * @param velocity The altitude to display
     */
    void setVelocity(double velocity);
    void setVfe(double vfe);
    void setVne(double vne);

private:


    double _scale                  = 1.0;
    QGraphicsScene* _scene         = nullptr;///< graphics scene
    const double _scale_factor     = 0.4;
    const double _originalPixPerSpd= 1.5;
    const double scaleSize         = 120;

    const QPointF position       = {-120, 0};
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
