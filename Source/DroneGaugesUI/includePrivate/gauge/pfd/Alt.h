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
    void reset();
    void updateAltView();
    void updateVertVelView();

    double _scale= 1.0;
    QGraphicsScene* _scene= nullptr;///< graphics scene

    double _altitude;
    double _verticalVelocity;
};
}// namespace dg::ui::gauge::pfd
