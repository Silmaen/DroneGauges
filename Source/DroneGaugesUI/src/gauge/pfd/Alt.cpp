/**
 * @file Alt.cpp
 * @author damien.lachouette 
 * @date 23/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/pfd/Alt.h"

namespace dg::ui::gauge::pfd {

ALT::ALT(QGraphicsScene* scene):_scene{scene} {
}

void ALT::init(double scale) {
    _scale = scale;
}

void ALT::update(double scale) {
    _scale = scale;
}

void ALT::setAltitude(double altitude) {
    _altitude = altitude;
}

void ALT::setVerticalVelocity(double verticalVelocity) {
    _verticalVelocity = verticalVelocity;
}

}
