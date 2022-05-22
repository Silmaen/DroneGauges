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

namespace dg::ui::gauge {

PrimaryFlightDisplay::PrimaryFlightDisplay(QWidget* parent):
    QGraphicsView(parent), _scene(new QGraphicsScene(this)) {
    setScene(_scene);
    _scene->clear();
    init();
}
PrimaryFlightDisplay::~PrimaryFlightDisplay() {
    if(_scene != nullptr) {
        _scene->clear();
        delete _scene;
        _scene= nullptr;
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
    _pitch= core::base::clamp(pitch, -90, 90);
    redraw();
}

void PrimaryFlightDisplay::setYaw(int) {
}

void PrimaryFlightDisplay::setRoll(int roll) {
    _roll= core::base::clamp(roll, -180, 180);
    redraw();
}
void PrimaryFlightDisplay::init() {
    updateScale();
    _itemBack= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_back.svg");
    _itemBack->setCacheMode(QGraphicsItem::NoCache);
    _itemBack->setZValue(0);
    _itemBack->setScale(_scaleMax);
    _itemBack->setTransformOriginPoint(_originalBackPos);
    _itemBack->moveBy(-_originalBackPos.x(), -_originalBackPos.y());
    _scene->addItem(_itemBack);

    _itemLadd= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_ladd.svg");
    _itemLadd->setCacheMode(QGraphicsItem::NoCache);
    _itemLadd->setZValue(10);
    _itemLadd->setScale(_scaleMax * _scaleLow);
    _itemLadd->setTransformOriginPoint(_originalLaddPos);
    _itemLadd->moveBy(-_originalLaddPos.x(), -_originalLaddPos.y());
    _scene->addItem(_itemLadd);

    _itemRoll= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_roll.svg");
    _itemRoll->setCacheMode(QGraphicsItem::NoCache);
    _itemRoll->setZValue(30);
    _itemRoll->setScale(_scaleMax * _scaleLow);
    _itemRoll->setTransformOriginPoint(_originalRollPos);
    _itemRoll->moveBy(-_originalRollPos.x(), -_originalRollPos.y());
    _scene->addItem(_itemRoll);

    _itemMask= new QGraphicsSvgItem(":/Widgets/PrimaryFlightDisplay/pfdd_mask.svg");
    _itemMask->setCacheMode(QGraphicsItem::NoCache);
    _itemMask->setZValue(60);
    _itemMask->setScale(_scaleMax * _scaleLow);
    _itemMask->moveBy(-_scaleMax * _scaleLow * _originalMaskPos.x(), -_scaleMax * _scaleLow * _originalMaskPos.y());
    _scene->addItem(_itemMask);

    updateView();
}
void PrimaryFlightDisplay::updateScale() {
    _scaleX  = static_cast<double>(width()) / static_cast<double>(_originalWidth);
    _scaleY  = static_cast<double>(height()) / static_cast<double>(_originalHeight);
    _scaleMax= std::min(_scaleX, _scaleY);
}

void PrimaryFlightDisplay::updateView() {
    updateScale();
    updateBackView();
    updateLadderView();
    updateRollView();
    _scene->update();
    centerOn(0, 0);
}

void PrimaryFlightDisplay::updateBackView() {
    double roll_rad= M_PI * _roll / 180.0;
    _itemBack->setRotation(-_roll);
    double deltaBack= core::base::clamp(_originalPixPerDeg * _pitch, _deltaBack_min, _deltaBack_max);
    deltaBack*= _scaleMax * _scaleLow;
    QPointF roll(std::sin(roll_rad), std::cos(roll_rad));
    roll*= deltaBack;
    roll-= _originalBackPos;
    _itemBack->setPos(roll);
}
void PrimaryFlightDisplay::updateLadderView() {
    double delta   = _originalPixPerDeg * _pitch;
    double roll_rad= M_PI * _roll / 180.0;
    _itemLadd->setRotation(-_roll);
    QPointF roll(std::sin(roll_rad), std::cos(roll_rad));
    roll*= _scaleMax * _scaleLow * delta;
    roll-= _originalLaddPos;
    _itemLadd->setPos(roll);
}
void PrimaryFlightDisplay::updateRollView() {
    _itemRoll->setRotation(-_roll);
}

}// namespace dg::ui::gauge
