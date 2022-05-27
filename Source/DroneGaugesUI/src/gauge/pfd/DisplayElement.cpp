/**
 * @file DisplayElement.cpp
 * @author damien.lachouette 
 * @date 25/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/pfd/DisplayElement.h"

namespace dg::ui::gauge::pfd {
DisplayElement::DisplayElement(std::shared_ptr<QGraphicsScene> scene, const QPointF& position, const double& internalScale):
    _scene{std::move(scene)}, _position{position}, _internalScale{internalScale} {}

DisplayElement::~DisplayElement() {
}

}// namespace dg::ui::gauge::pfd
