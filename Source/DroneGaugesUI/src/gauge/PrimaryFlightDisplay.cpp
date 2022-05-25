/**
 * @file PrimaryFlightDisplay.cpp
 * @author Silmean
 * @date 20/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/PrimaryFlightDisplay.h"
#include "base/base.h"

#include "gauge/pfd/Adi.h"
#include "gauge/pfd/Alt.h"
#include "gauge/pfd/Asi.h"
#include "gauge/pfd/Hdg.h"
#include <gauge/moc_PrimaryFlightDisplay.cpp>
#include <iostream>

namespace dg::ui::gauge {

PrimaryFlightDisplay::PrimaryFlightDisplay(QWidget* parent):
    QGraphicsView(parent),
    _scene(std::make_shared<QGraphicsScene>(new QGraphicsScene(this))),
    adi(std::make_shared<pfd::ADI>(_scene)),
    alt(std::make_shared<pfd::ALT>(_scene, QPointF{120, 0}, 0.4)),
    asi(std::make_shared<pfd::ASI>(_scene, QPointF{-120, 0}, 0.4)),
    hdg{std::make_shared<pfd::HDG>(_scene, QPointF{0, -135},0.4)}{
    setScene(_scene.get());
    _scene->clear();
    init();
}
PrimaryFlightDisplay::~PrimaryFlightDisplay() {
    if(_scene != nullptr) {
        _scene->clear();
    }
}

void PrimaryFlightDisplay::reinit() {
    if(_scene) {
        _scene->clear();
        init();
    }
}

void PrimaryFlightDisplay::redraw() {
    if(isVisible()) {
        updateView();
    }
}

void PrimaryFlightDisplay::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);
    reinit();
}

void PrimaryFlightDisplay::setPitch(int pitch) {
    adi->setPitch(pitch);
    redraw();
}

void PrimaryFlightDisplay::setYaw(int yaw) {
    hdg->setYaw(yaw);
    redraw();
}

void PrimaryFlightDisplay::setRoll(int roll) {
    adi->setRoll(roll);
    redraw();
}

void PrimaryFlightDisplay::setAltitude(int altitude) {
    alt->setAltitude(altitude);
    redraw();
}

void PrimaryFlightDisplay::setVerticalVelocity(int verticalVelocity) {
    alt->setVerticalVelocity(verticalVelocity / 10.0);
    redraw();
}

void PrimaryFlightDisplay::setVelocity(int velocity) {
    asi->setVelocity(velocity);
    redraw();
}

void PrimaryFlightDisplay::init() {
    updateScale();
    adi->init(_scaleMax);
    alt->init(_scaleMax);
    asi->init(_scaleMax);
    hdg->init(_scaleMax);
    updateView();
}
void PrimaryFlightDisplay::updateScale() {
    _scaleX  = static_cast<double>(width()) / static_cast<double>(_originalWidth);
    _scaleY  = static_cast<double>(height()) / static_cast<double>(_originalHeight);
    _scaleMax= std::min(_scaleX, _scaleY);
}

void PrimaryFlightDisplay::updateView() {
    updateScale();
    adi->update(_scaleMax);
    alt->update(_scaleMax);
    asi->update(_scaleMax);
    hdg->update(_scaleMax);
    _scene->update();
    centerOn(0, 0);
}

}// namespace dg::ui::gauge
