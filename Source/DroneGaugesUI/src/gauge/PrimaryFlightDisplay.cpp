/**
 * @file PrimaryFlightDisplay.cpp
 * @author Silmean
 * @date 20/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gauge/PrimaryFlightDisplay.h"
#include "base/base.h"

#include <gauge/moc_PrimaryFlightDisplay.cpp>
#include <iostream>
#include "gauge/pfd/Adi.h"
#include "gauge/pfd/Alt.h"

namespace dg::ui::gauge {

PrimaryFlightDisplay::PrimaryFlightDisplay(QWidget* parent):
    QGraphicsView(parent), _scene(new QGraphicsScene(this)),
    adi(new pfd::ADI(_scene)), alt(new pfd::ALT(_scene)){
    setScene(_scene);
    _scene->clear();
    init();
}
PrimaryFlightDisplay::~PrimaryFlightDisplay() {
    if(_scene != nullptr) {
        _scene->clear();
        delete _scene;
        _scene= nullptr;
        delete adi;
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

void PrimaryFlightDisplay::setYaw(int) {
}

void PrimaryFlightDisplay::setRoll(int roll) {
    adi-> setRoll(roll);
    redraw();
}

void PrimaryFlightDisplay::setAltitude(double altitude){
    alt->setAltitude(altitude);
    redraw();
}

void PrimaryFlightDisplay::setVerticalVelocity(double verticalVelocity){
    alt->setVerticalVelocity(verticalVelocity);
    redraw();
}

void PrimaryFlightDisplay::init() {
    updateScale();
    adi->init(_scaleMax);
    alt->init(_scaleMax);
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
    _scene->update();
    centerOn(0, 0);
}

}// namespace dg::ui::gauge
